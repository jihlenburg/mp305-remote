"""Helpers of the system tests: the frame log, frame layouts, mock scripts and child processes.

Nothing here talks to a supply. The frame log is read from the library's
`logging` records (`mp305.set_log_level(5)` switches it on, DD-PY-006); the
line formats are those of the core's frames target (`tx`, `rx`, `wire tx`,
`wire rx` and the negotiated MTU, DD-TRANS-005 and DD-TRANS-010).
"""

from __future__ import annotations

import dataclasses
import json
import logging
import os
import pathlib
import re
import subprocess
import sys
import textwrap
import threading
import time
from collections.abc import Callable, Iterable
from typing import Any

from mp305 import testing

ROOT = pathlib.Path(__file__).resolve().parents[2]
"""The repository root."""

SAFE_VOLTAGE = 5.0
"""The highest voltage setpoint a test uses (AGENTS.md, "Working with the real device")."""

SAFE_CURRENT = 0.1
"""The highest current limit a test uses."""

CONFIRM_TEXT = "Confirm the connection on the supply's screen within 30 seconds"
"""The bind prompt text of SR-008."""

ALLOW_TEXT = "Allow remote control on the supply's screen"
"""The remote-control prompt text of SR-053."""

AFTER_LOSS = "The output is still in its last state and the supply has released remote control."
"""The sentence of SR-028 every loss text carries."""

USB_HOST_HINT = "A USB host talking to the supply is one possible cause."
"""The hint of SR-048 the library gives with a silent Bluetooth link."""

UNCLEAN_PREFIX = "A previous session may have left the output on"
"""The start of the unclean-exit warning of SR-046."""

CSV_HEADER = (
    "time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n"
)
"""The header row of SR-037, with its line end."""

WEBLINK_HOST_ID = bytes([0x00] + [0x08] * 14 + [0x00])
"""WebLink's constant host ID, which SR-049 forbids."""

REQUEST_LENGTHS = {0x18: 18, 0xE0: 0, 0xC2: 0, 0xC8: 11}
"""The payload length of every request the system may send (protocol.md 3 and 4)."""

ROUTES = ("ble AF01", "ble AF02", "hid")
"""The route names of the frame log."""

AF01_UUID = "0000af01-0000-1000-8000-00805f9b34fb"
"""The command characteristic."""

AF02_UUID = "0000af02-0000-1000-8000-00805f9b34fb"
"""The bind characteristic."""

_HEX = r"[0-9a-f]{2}(?: [0-9a-f]{2})*"
_FRAME = re.compile(rf"^(tx|rx) (ble AF01|ble AF02|hid) \+(\d+) ({_HEX})$")
_RX_ERROR = re.compile(r"^rx (ble AF01|ble AF02|hid) \+(\d+) error: (.*)$")
_CLOSED = re.compile(r"^rx (ble AF01|ble AF02|hid) \+(\d+) link closed$")
_MTU = re.compile(r"^ble (.+): negotiated ATT MTU (\d+)$")
_WIRE_BLE = re.compile(rf"^wire (tx|rx) ble (\S+) ({_HEX})$")
_WIRE_HID = re.compile(rf"^wire (tx|rx) hid ({_HEX})$")


# Frames and their fields.


@dataclasses.dataclass(frozen=True)
class Frame:
    """One `tx` or `rx` line of the frame log (the guard's view, DD-TRANS-005).

    `offset_ms` counts from the creation of the connection's guard, so it
    restarts with every connection; `index` is the record's position in the
    captured log and `created` its wall time in seconds since the epoch.
    """

    index: int
    created: float
    direction: str
    route: str
    offset_ms: int
    opcode: int
    payload: bytes


@dataclasses.dataclass(frozen=True)
class Wire:
    """One `wire tx` or `wire rx` line: the bytes as the OS saw them."""

    index: int
    created: float
    direction: str
    transport: str
    characteristic: str
    data: bytes


@dataclasses.dataclass(frozen=True)
class Control:
    """The fields of a `0xC8` payload (protocol.md 4.2)."""

    remote_con: int
    set_voltage: int
    set_current: int
    real_change: int
    voltage_slow: int
    current_over: int
    output: int
    model: int
    refresh: int


def control(payload: bytes) -> Control:
    """The fields of an 11-byte `0xC8` payload."""
    return Control(
        remote_con=payload[0],
        set_voltage=int.from_bytes(payload[1:3], "little"),
        set_current=int.from_bytes(payload[3:5], "little"),
        real_change=payload[5],
        voltage_slow=payload[6],
        current_over=payload[7],
        output=payload[8],
        model=payload[9],
        refresh=payload[10],
    )


@dataclasses.dataclass(frozen=True)
class Telemetry:
    """The fields of a `0xC3` payload that the control command copies (protocol.md 4.1)."""

    out_state: int
    set_voltage: int
    set_current: int
    current_over: int
    real_change: int
    voltage_slow: int
    output: int
    model: int


def telemetry(payload: bytes) -> Telemetry:
    """The copied fields of a 36-byte `0xC3` payload."""
    return Telemetry(
        out_state=payload[0],
        set_voltage=int.from_bytes(payload[5:7], "little"),
        set_current=int.from_bytes(payload[9:11], "little"),
        current_over=payload[21],
        real_change=payload[22],
        voltage_slow=payload[23],
        output=payload[24],
        model=payload[25],
    )


def is_deferred(frame: Frame) -> bool:
    """Whether a request's reply comes later and is not waited for in flight.

    Over Bluetooth the prompt bind (fast flag clear) and the remote-control
    request (`0xC8` with `remoteCon` 2) are answered when the person presses
    a button (SR-007, SR-018).
    """
    if not frame.route.startswith("ble"):
        return False
    if frame.opcode == 0x18:
        return frame.payload[-1:] == b"\x00"
    return frame.opcode == 0xC8 and frame.payload[:1] == b"\x02"


def overlaps(frames: Iterable[Frame]) -> list[str]:
    """The requests sent while another one was in flight (SR-017).

    A request is in flight from its `tx` until the `rx` with its reply
    opcode; the next request may follow once that reply arrived or once its
    timeout passed (1 s, 0.5 s for a `0xC8`, SR-022 and SR-023). Deferred
    requests (`is_deferred`) are never in flight. The offsets of one
    connection are compared; a new connection starts when the offset falls.
    """
    problems: list[str] = []
    in_flight: Frame | None = None
    last_offset = -1
    for frame in frames:
        if frame.offset_ms < last_offset:
            in_flight = None
        last_offset = frame.offset_ms
        if frame.direction == "rx":
            if in_flight is not None and frame.opcode == in_flight.opcode + 1:
                in_flight = None
            continue
        if in_flight is not None:
            bound = 500 if in_flight.opcode == 0xC8 else 1000
            if frame.offset_ms - in_flight.offset_ms < bound:
                problems.append(
                    f"0x{frame.opcode:02x} at +{frame.offset_ms} ms while 0x{in_flight.opcode:02x}"
                    f" of +{in_flight.offset_ms} ms was in flight"
                )
        in_flight = None if is_deferred(frame) else frame
    return problems


# The frame log.


class FrameLog(logging.Handler):
    """Collects the library's log records, the frame log among them.

    Attach it with `start()` (which switches the frame log on with
    `mp305.set_log_level(5)`) and detach it with `stop()`. Records reach
    `logging` from the library's delivery thread, so `settle()` waits for
    the ones still on their way.
    """

    def __init__(self) -> None:
        super().__init__(level=0)
        self.records: list[logging.LogRecord] = []
        self._lock = threading.Lock()
        self._level = logging.NOTSET

    def emit(self, record: logging.LogRecord) -> None:
        with self._lock:
            self.records.append(record)

    def start(self) -> FrameLog:
        """Attaches the handler to the `mp305` logger and switches the frame log on.

        The `mp305` logger itself goes down to TRACE too, so that the
        library's own INFO records (the bind result, the faults) arrive.
        """
        import mp305

        logger = logging.getLogger("mp305")
        self._level = logger.level
        logger.setLevel(5)
        logger.addHandler(self)
        mp305.set_log_level(5)
        return self

    def stop(self) -> None:
        """Switches the frame log off and detaches the handler."""
        import mp305

        mp305.set_log_level(logging.WARNING)
        logger = logging.getLogger("mp305")
        logger.removeHandler(self)
        logger.setLevel(self._level)

    def settle(self, seconds: float = 0.6) -> None:
        """Waits for records still on their way from the delivery thread."""
        time.sleep(seconds)

    def snapshot(self) -> list[logging.LogRecord]:
        """The records so far."""
        with self._lock:
            return list(self.records)

    def mark(self) -> int:
        """The number of records so far, to look at what came after."""
        with self._lock:
            return len(self.records)

    def lines(self, start: int = 0) -> list[str]:
        """Every record from `start` as one text line, for the run's record."""
        out = []
        for r in self.snapshot()[start:]:
            stamp = time.strftime("%H:%M:%S", time.localtime(r.created))
            out.append(f"{stamp}.{int(r.msecs):03d} {r.name} {r.levelname} {r.getMessage()}")
        return out

    def frames(self, start: int = 0) -> list[Frame]:
        """The `tx` and `rx` lines of the frames target from record `start` on."""
        out = []
        for index, r in enumerate(self.snapshot()):
            if index < start or r.name != "mp305.core.frames":
                continue
            m = _FRAME.match(r.getMessage())
            if m is None:
                continue
            out.append(
                Frame(
                    index=index,
                    created=r.created,
                    direction=m.group(1),
                    route=m.group(2),
                    offset_ms=int(m.group(3)),
                    opcode=int(m.group(4)[:2], 16),
                    payload=bytes.fromhex(m.group(4)[2:].replace(" ", "")),
                )
            )
        return out

    def sent(self, opcode: int | None = None, start: int = 0) -> list[Frame]:
        """The requests (`tx`), all or those with `opcode`."""
        return [
            f
            for f in self.frames(start)
            if f.direction == "tx" and (opcode is None or f.opcode == opcode)
        ]

    def received(self, opcode: int | None = None, start: int = 0) -> list[Frame]:
        """The replies and device frames (`rx`), all or those with `opcode`."""
        return [
            f
            for f in self.frames(start)
            if f.direction == "rx" and (opcode is None or f.opcode == opcode)
        ]

    def wire(self, start: int = 0) -> list[Wire]:
        """The `wire tx` and `wire rx` lines from record `start` on."""
        out = []
        for index, r in enumerate(self.snapshot()):
            if index < start or r.name != "mp305.core.frames":
                continue
            text = r.getMessage()
            m = _WIRE_BLE.match(text)
            if m is not None:
                out.append(Wire(index, r.created, m.group(1), "ble", m.group(2), _hex(m.group(3))))
                continue
            m = _WIRE_HID.match(text)
            if m is not None:
                out.append(Wire(index, r.created, m.group(1), "hid", "", _hex(m.group(2))))
        return out

    def mtu(self) -> list[tuple[int, int]]:
        """Each negotiated MTU line as (record index, MTU)."""
        out = []
        for index, r in enumerate(self.snapshot()):
            if r.name != "mp305.core.frames":
                continue
            m = _MTU.match(r.getMessage())
            if m is not None:
                out.append((index, int(m.group(2))))
        return out

    def receive_errors(self, start: int = 0) -> list[str]:
        """The `rx ... error:` lines (frames the transport could not decode)."""
        return [
            r.getMessage()
            for r in self.snapshot()[start:]
            if r.name == "mp305.core.frames" and _RX_ERROR.match(r.getMessage())
        ]

    def link_closed(self, start: int = 0) -> list[logging.LogRecord]:
        """The `rx ... link closed` records."""
        return [
            r
            for r in self.snapshot()[start:]
            if r.name == "mp305.core.frames" and _CLOSED.match(r.getMessage())
        ]

    def messages(
        self, name: str | None = None, level: int | None = None, start: int = 0
    ) -> list[logging.LogRecord]:
        """The records of logger `name` (or its children) at `level`."""
        out = []
        for r in self.snapshot()[start:]:
            if name is not None and r.name != name and not r.name.startswith(name + "."):
                continue
            if level is not None and r.levelno != level:
                continue
            out.append(r)
        return out

    def texts(self, name: str | None = None, level: int | None = None) -> list[str]:
        """The messages of `messages`."""
        return [r.getMessage() for r in self.messages(name, level)]


def _hex(text: str) -> bytes:
    """The bytes of a space-separated hex text."""
    return bytes.fromhex(text.replace(" ", ""))


# USB HID framing, written from protocol.md 2.2 for the checks of ST-040.


def hid_stream(address: int, opcode: int, payload: bytes) -> bytes:
    """The framed stream `AA address len opcode payload sum`, every later `AA` doubled."""
    body = bytes([opcode]) + payload
    length = len(body)
    total = (address + length + sum(body)) & 0xFF
    out = bytearray([0xAA])
    for byte in bytes([address, length]) + body + bytes([total]):
        out.append(byte)
        if byte == 0xAA:
            out.append(0xAA)
    return bytes(out)


def hid_reports(stream: bytes) -> list[bytes]:
    """The 65-byte output reports of a request stream: `01, n, n bytes`, zero padded."""
    out = []
    for start in range(0, len(stream), 62):
        chunk = stream[start : start + 62]
        out.append(bytes([0x01, len(chunk)]) + chunk + bytes(63 - len(chunk)))
    return out


def hid_decode(stream: bytes) -> list[tuple[int, int, bytes, bool]]:
    """The frames of a reply stream as (address, opcode, payload, checksum ok).

    As protocol.md 2.2 describes the device's parser: an `AA` sets a pending
    flag; a byte other than `AA` with the flag set starts a frame with that
    byte as the address; `AA` with the flag set is the data byte `AA`. A
    frame ends after its length field's body and the checksum.
    """
    frames = []
    data: list[int] | None = None
    pending = False
    for byte in stream:
        if byte == 0xAA and not pending:
            pending = True
            continue
        if pending and byte != 0xAA:
            data = [byte]
        elif data is not None:
            data.append(byte)
        pending = False
        if data is not None and len(data) >= 2 and len(data) == data[1] + 3:
            frames.append(_hid_frame(data))
            data = None
    return frames


def _hid_frame(data: list[int]) -> tuple[int, int, bytes, bool]:
    """(address, opcode, payload, checksum ok) of the unstuffed bytes after `AA`."""
    address, length = data[0], data[1]
    body = bytes(data[2 : 2 + length])
    ok = len(data) == length + 3 and (address + length + sum(body)) & 0xFF == data[-1]
    return address, body[0] if body else -1, body[1:], ok


# Waiting.


def settled_reading(dev: Any, seconds: float = 1.0) -> Any:
    """The newest reading after `seconds`, for a steady state after a command."""
    deadline = time.monotonic() + seconds
    reading = dev.read(timeout=5.0)
    while time.monotonic() < deadline:
        reading = dev.read(timeout=5.0)
    return reading


def first_reading(dev: Any, condition: Callable[[Any], bool], timeout: float) -> Any:
    """The first new reading that satisfies `condition`, or None after `timeout`."""
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        reading = dev.read(timeout=5.0)
        if condition(reading):
            return reading
    return None


def wait_until(condition: Callable[[], Any], timeout: float, step: float = 0.05) -> Any:
    """Polls `condition` every `step` s until it is truthy or `timeout` passed.

    Returns the last value of the condition.
    """
    deadline = time.monotonic() + timeout
    while True:
        value = condition()
        if value or time.monotonic() >= deadline:
            return value
        time.sleep(step)


# Mock scripts (`mp305.testing`, DD-PY-045).


def reply(
    request: int,
    payload: bytes,
    after_s: float = 0.005,
    repeat: int | None = None,
    kind: str = "ble",
    **extra: Any,
) -> dict[str, Any]:
    """A reply to `request` with `payload` under the reply opcode."""
    frame = testing.ble_frame if kind == "ble" else testing.hid_stream
    return {
        "request": request,
        "after_s": after_s,
        "deliveries": [frame(request + 1, payload)],
        "repeat": repeat,
        **extra,
    }


def silent(request: int, repeat: int | None = None) -> dict[str, Any]:
    """A reply to `request` that delivers nothing."""
    return {"request": request, "after_s": 0.005, "deliveries": [], "repeat": repeat}


def script(
    kind: str = "ble", replies: Iterable[dict[str, Any]] = (), **extra: Any
) -> dict[str, Any]:
    """The default script with `replies` added after it and `extra` keys set.

    Replies of an opcode that `replies` names replace the default ones, so
    the script answers exactly as the test says.
    """
    s: dict[str, Any] = dict(testing.default_script(kind))  # type: ignore[arg-type]
    added = list(replies)
    named = {r["request"] for r in added}
    s["replies"] = [r for r in s["replies"] if r["request"] not in named] + added
    s.update(extra)
    return s


def c3_with_out_state(out_state: int, **fields: int) -> bytes:
    """A `0xC3` payload whose `outState` (byte 0) is `out_state`."""
    return bytes([out_state]) + testing.c3(**fields)[1:]


# Child processes.

CHILD_PRELUDE = '''
import json, os, signal, sys, threading, time
import mp305
from mp305 import Mp305

MARKS = {}

def report(**fields):
    """Prints the observations as one JSON line."""
    print(json.dumps(fields), flush=True)

def sigint_after(delay, key="signal"):
    """Raises SIGINT after `delay` s from a daemon timer, as Ctrl-C does; notes the time."""
    def fire():
        MARKS[key] = time.monotonic()
        signal.raise_signal(signal.SIGINT)
    timer = threading.Timer(delay, fire)
    timer.daemon = True
    timer.start()
    return timer
'''


def child_env(extra: dict[str, str] | None = None) -> dict[str, str]:
    """The environment of a child Python: this one plus `extra`."""
    env = dict(os.environ)
    env["PYTHONPATH"] = str(ROOT)
    env.update(extra or {})
    return env


def run_child(
    code: str, env: dict[str, str] | None = None, timeout: float = 120.0
) -> tuple[dict[str, Any], subprocess.CompletedProcess[str]]:
    """Runs the prelude, then `code`, in a child Python and waits for it.

    Returns the last JSON line the child printed (an empty dict when there
    is none) and the completed process.
    """
    proc = subprocess.run(
        [sys.executable, "-c", CHILD_PRELUDE + textwrap.dedent(code)],
        capture_output=True,
        text=True,
        timeout=timeout,
        cwd=ROOT,
        env=child_env(env),
    )
    return last_json(proc.stdout.splitlines()), proc


def start_child(code: str, env: dict[str, str] | None = None) -> subprocess.Popen[str]:
    """Starts the prelude, then `code`, in a child Python without waiting."""
    return subprocess.Popen(
        [sys.executable, "-c", CHILD_PRELUDE + textwrap.dedent(code)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        cwd=ROOT,
        env=child_env(env),
    )


class ChildLines:
    """The stdout lines of a running child, read on a helper thread."""

    def __init__(self, proc: subprocess.Popen[str]) -> None:
        import queue

        self._queue: queue.Queue[str | None] = queue.Queue()
        self.seen: list[str] = []

        def pump() -> None:
            assert proc.stdout is not None
            for line in proc.stdout:
                self._queue.put(line.rstrip("\n"))
            self._queue.put(None)

        threading.Thread(target=pump, name="child stdout", daemon=True).start()

    def get(self, timeout: float) -> str | None:
        """The next line, or None at the end of the output or after `timeout`."""
        import queue

        try:
            line = self._queue.get(timeout=max(timeout, 0.0))
        except queue.Empty:
            return None
        if line is not None:
            self.seen.append(line)
        return line


def last_json(lines: Iterable[str]) -> dict[str, Any]:
    """The last line that is a JSON object, as a dict; empty when there is none."""
    found: dict[str, Any] = {}
    for line in lines:
        if line.startswith("{"):
            found = json.loads(line)
    return found


# CSV (SR-037).

CSV_ROW = re.compile(
    r"\d{4}-\d\d-\d\dT\d\d:\d\d:\d\d\.\d{3}Z,-?\d+\.\d{3},"
    r"\d+\.\d{2},\d+\.\d{3},\d+\.\d{2},\d+\.\d{2},\d+\.\d{3},[01],"
    r"(off|cv|cc|held_above|unknown_\d+),[a-z0-9 ;]*\n"
)
"""One data row of SR-037 as `mp305-core`'s `csv::format_row` writes it."""


def csv_problems(data: bytes) -> list[str]:
    """What in the file `data` breaks SR-037: encoding, header, separators, decimal point."""
    problems = []
    try:
        text = data.decode("utf-8")
    except UnicodeDecodeError as error:
        return [f"not UTF-8: {error}"]
    if "\r" in text:
        problems.append("a line ends with CR")
    lines = text.splitlines(keepends=True)
    if not lines or lines[0] != CSV_HEADER:
        problems.append(f"header is {lines[0] if lines else ''!r}")
    for number, line in enumerate(lines[1:], start=2):
        if not CSV_ROW.fullmatch(line):
            problems.append(f"line {number} is {line!r}")
    return problems
