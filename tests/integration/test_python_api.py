"""IT-040: the synchronous Python API on the scripted mock (AR-040).

Every test runs through `Mp305._from_mock` or, for `connect()` without an
identifier, `Mp305.connect()` inside `testing.mock_discovery`, whose seams
replace the native discovery and connect; no test reaches a real transport.
The mock runs on the real clock, so waits are polled conditions with an
upper bound.
"""

from __future__ import annotations

import dataclasses
import logging
import math
import pathlib
import re
import threading
import time
from collections.abc import Callable

import pytest

import mp305
from mp305 import (
    CommandRejectedError,
    ConnectionDeniedError,
    Event,
    EventKind,
    FaultActiveError,
    Found,
    Info,
    LinkLostError,
    LiveMode,
    Mode,
    ModeError,
    Mp305,
    Mp305Error,
    Mp305TimeoutError,
    NotFoundError,
    Reading,
    RemoteControlDeniedError,
    RemoteControlLostError,
    SetpointRangeError,
    ramp,
    stream,
    testing,
    to_csv,
)
from mp305.types import Fault
from tests.integration import core_errors
from tests.unit import frames
from tests.unit.support import c3_reply, messages, reply, run_child, script, wait_until

Factory = Callable[..., Mp305]

C3_CAPTURE = testing.fixtures()["C3_CAPTURE"]
CONFIRM = "Confirm the connection on the supply's screen within 30 seconds"
FEWER = "the supply delivers fewer readings than the requested rate"
HEADER = "time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n"


def control(
    reading: bytes,
    remote_con: int,
    *,
    set_voltage: int | None = None,
    set_current: int | None = None,
    output: int | None = None,
) -> bytes:
    """The `0xC8` payload that copies the `0xC3` payload `reading` with the named fields set.

    The layout of `protocol::ops::control`: `remoteCon`, `setVoltage` and
    `setCurrent` (u16, little endian), `realChange`, `voltageSlow`,
    `currentOver`, `output`, then `model` 0 and `refresh` 0. The copied
    fields sit at offsets 5, 9, 22, 23, 21 and 24 of the reading
    (`protocol::ops::telemetry`).
    """
    voltage = reading[5:7] if set_voltage is None else set_voltage.to_bytes(2, "little")
    current = reading[9:11] if set_current is None else set_current.to_bytes(2, "little")
    out = reading[24] if output is None else output
    return (
        bytes([remote_con])
        + voltage
        + current
        + bytes([reading[22], reading[23], reading[21], out, 0, 0])
    )


def found(identifier: str, transport: str = "ble") -> Found:
    """A supply that the mock discovery reports."""
    return Found(
        transport=transport,  # type: ignore[arg-type]
        identifier=identifier,
        unit_id="E!K",
        name="MP305B",
        rssi=-61 if transport == "ble" else None,
        remote_flag=True if transport == "ble" else None,
        description=f"MP305B E!K over {transport} ({identifier})",
    )


def output_on_script() -> dict[str, object]:
    """The default script with the reading showing the output on."""
    return script(replies=[c3_reply(testing.c3(output=1))])


# The DC session of IT-025.


@pytest.mark.spec("IT-040")
def test_the_dc_session_of_it_025(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device([testing.default_script()], identifier="IT-040-dc", record=rec)
    assert dev.info == Info(
        model="MP305B", version="1.6.0.40", hardware="2.0.2.0", bootloader=None, name=None
    )
    first = dev.reading
    assert first is not None
    assert first.raw == C3_CAPTURE
    assert (first.set_voltage, first.set_current, first.output_on) == (13.0, 1.0, False)
    dev.set_voltage(1.7)
    dev.set_current_limit(0.1)
    dev.output_on()
    dev.output_off()
    dev.release_remote_control()
    dev.close()
    sent = rec.sent()
    # The connect: the fast bind with the host ID on AF02, then the info
    # request and the first poll.
    assert [(f.opcode, f.route) for f in sent[:3]] == [
        (0x18, "af02"),
        (0xE0, "af01"),
        (0xC2, "af01"),
    ]
    assert sent[0].payload == testing.MOCK_HOST_ID + b"\x00\x01"
    assert {f.opcode for f in sent} <= {0x18, 0xE0, 0xC2, 0xC8}
    # Every `0xC8` copies all fields from the latest reading (the capture),
    # changes one, has `model` 0 and `refresh` 0, and only the one of
    # `output_on` carries `output` 1.
    assert [f.payload for f in frames.sent(sent, 0xC8)] == [
        control(C3_CAPTURE, 2),  # the remote-control request before set_voltage
        control(C3_CAPTURE, 1, set_voltage=170),
        control(C3_CAPTURE, 1, set_current=100),
        control(C3_CAPTURE, 1, output=1),
        control(C3_CAPTURE, 1, output=0),
        control(C3_CAPTURE, 0),  # release_remote_control
        control(C3_CAPTURE, 0, output=0),  # the release of close (SR-029)
    ]
    assert rec.closes() == 1
    assert dev.closed is True


# connect() without an identifier.


@pytest.mark.spec("IT-040")
def test_connect_without_an_identifier_and_one_supply() -> None:
    supply = found("IT-040-one")
    with testing.mock_discovery([supply]) as record:
        with Mp305.connect() as dev:
            assert dev.identifier == "IT-040-one"
            assert dev.link_state == "ready"
            assert dev.transport == "ble"
    assert record.attempts() == 1
    assert frames.sent(record.sent(), 0x18)


@pytest.mark.spec("IT-040")
def test_connect_without_an_identifier_and_two_supplies() -> None:
    supplies = [found("IT-040-two-a"), found("IT-040-two-b", "hid")]
    with testing.mock_discovery(supplies) as record:
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    text = str(info.value)
    for supply in supplies:
        assert supply.description in text
    assert info.value.found == tuple(supplies)
    assert record.attempts() == 0


# The context manager.


def check_safe_end(rec: testing.MockRecord) -> None:
    """The block ended with `0xC8` output 0, then `0xC8` remoteCon 0, then the close."""
    sent = rec.sent()
    c8 = [i for i, f in enumerate(sent) if f.opcode == 0xC8]
    off, release = (frames.control(sent[i].payload) for i in c8[-2:])
    assert (off.remote_con, off.output) == (1, 0)
    assert (release.remote_con, release.output) == (0, 0)
    assert all(f.opcode == 0xC2 for f in sent[c8[-1] + 1 :])
    assert rec.closes() == 1


@pytest.mark.spec("IT-040")
def test_a_with_block_that_ends_normally() -> None:
    rec = testing.MockRecord()
    with Mp305._from_mock([output_on_script()], identifier="IT-040-with-a", record=rec) as dev:
        dev.set_voltage(1.0)
        assert rec.closes() == 0
    check_safe_end(rec)
    assert dev.closed is True


@pytest.mark.spec("IT-040")
def test_a_with_block_that_raises() -> None:
    rec = testing.MockRecord()
    error = RuntimeError("raised in the block")
    with pytest.raises(RuntimeError) as info:
        with Mp305._from_mock([output_on_script()], identifier="IT-040-with-b", record=rec) as dev:
            dev.set_voltage(1.0)
            assert rec.closes() == 0
            raise error
    assert info.value is error
    check_safe_end(rec)
    assert dev.closed is True


# Python-side validation.


@pytest.mark.spec("IT-040")
def test_invalid_setpoints_raise_before_any_frame(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="IT-040-range", record=rec)
    before = len(rec.sent())
    with pytest.raises(SetpointRangeError) as nan:
        dev.set_voltage(math.nan)
    with pytest.raises(SetpointRangeError) as high:
        dev.set_voltage(30.01)
    for info in (nan, high):
        assert type(info.value) is SetpointRangeError
        assert info.value.field == "voltage"
    assert str(high.value) == "voltage 30.01 is outside 0 to 30"
    # Only the session's own polls went out meanwhile, not even the
    # remote-control request.
    assert {f.opcode for f in rec.sent()[before:]} <= {0xC2}
    assert dev.remote_state == "none"


# Prompts.


@pytest.mark.spec("IT-040")
def test_a_prompt_reaches_logging_and_the_callback(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    calls: list[Event] = []
    s = script(replies=[reply(0x18, b"\xff", repeat=1), reply(0x18, b"\x00", after_s=0.5)])
    dev = mock_device([s], identifier="IT-040-prompt", on_prompt=calls.append)
    assert dev.link_state == "ready"
    assert CONFIRM in messages(caplog, level=logging.WARNING)
    assert len(calls) == 1
    event = calls[0]
    assert event.kind is EventKind.PROMPT
    assert event.prompt == "confirm_connection"
    assert event.bound_s == 30
    assert event.text == CONFIRM


# Each core error.

SR_032: dict[str, type[Mp305Error]] = {
    "NotFound": NotFoundError,
    "ConnectionDenied": ConnectionDeniedError,
    "RemoteControlDenied": RemoteControlDeniedError,
    "RemoteControlLost": RemoteControlLostError,
    "SetpointRange": SetpointRangeError,
    "CommandRejected": CommandRejectedError,
    "Mode": ModeError,
    "FaultActive": FaultActiveError,
    "NotReady": Mp305Error,
    "Timeout": Mp305TimeoutError,
    "LinkLost": LinkLostError,
    "Transport": LinkLostError,
    "Store": Mp305Error,
    "Protocol": Mp305Error,
    "AlreadyOpen": Mp305Error,
    "Cancelled": Mp305Error,
}
"""Each core error variant with the exception of SR-032 it raises (AR-050)."""

BUILT_IN: dict[type[Mp305Error], type[Exception]] = {
    SetpointRangeError: ValueError,
    Mp305TimeoutError: TimeoutError,
    LinkLostError: ConnectionError,
}
"""The built-in base SR-032 gives three of the exceptions."""


@pytest.mark.spec("IT-040")
@pytest.mark.parametrize("variant", list(core_errors.VARIANTS))
def test_each_core_error_raises_its_exception_of_sr_032(variant: str) -> None:
    trigger, text = core_errors.VARIANTS[variant]
    error = trigger(f"IT-040-{variant}")
    assert re.fullmatch(text, str(error)), (variant, str(error))
    expected = SR_032[variant]
    assert type(error) is expected
    assert isinstance(error, mp305.Mp305Error)
    assert getattr(mp305, expected.__name__) is expected
    assert expected.__name__ in mp305.__all__
    if expected in BUILT_IN:
        assert isinstance(error, BUILT_IN[expected])


# Readings.

SR_033: dict[str, type | tuple[type, ...]] = {
    "timestamp": float,
    "voltage": float,
    "current": float,
    "power": float,
    "set_voltage": float,
    "set_current": float,
    "output_on": bool,
    "mode": Mode,
    "live_mode": LiveMode,
    "faults": frozenset,
    "temperature": int,
    "energy": float,
    "working_time": int,
}
"""The fields of a reading that SR-033 lists, with their types."""


@pytest.mark.spec("IT-040")
def test_readings_are_immutable_with_the_fields_of_sr_033(mock_device: Factory) -> None:
    raw = testing.c3(output=1, set_voltage=500, set_current=250, charge_error=1 << 5)
    dev = mock_device([script(replies=[c3_reply(raw)])], identifier="IT-040-reading")
    called = time.time()
    r = dev.read()
    returned = time.time()
    assert isinstance(r, Reading)
    for name, kind in SR_033.items():
        assert isinstance(getattr(r, name), kind), name
    # The arrival time of a reading newer than the call; 10 ms for the float
    # seconds and the clock reads.
    assert called - 0.01 <= r.timestamp <= returned + 0.01
    assert (r.voltage, r.current, r.power) == (0.0, 0.0, 0.0)
    assert (r.set_voltage, r.set_current, r.output_on) == (5.0, 0.25, True)
    assert r.mode is Mode.OFF
    assert r.live_mode is LiveMode.DC
    assert r.faults == frozenset({Fault.OVER_CURRENT})
    assert (r.temperature, r.energy, r.working_time) == (26, 0.0, 1)
    assert {m.name for m in Mode} == {"OFF", "CV", "CC", "HELD_ABOVE", "UNKNOWN"}
    assert {"DC", "PROGRAM", "PD", "CHARGE"} <= {m.name for m in LiveMode}
    for name in SR_033:
        with pytest.raises(dataclasses.FrozenInstanceError):
            setattr(r, name, getattr(r, name))
    # No attribute can be added either. On CPython 3.10 the `__setattr__` of a
    # frozen dataclass with slots raises TypeError for an unknown name, on
    # later versions AttributeError; both reject it.
    with pytest.raises((AttributeError, TypeError)):
        r.extra = 1  # type: ignore[attr-defined]
    assert hash(r) == hash(dataclasses.replace(r))


# stream() (SR-034).


@pytest.mark.spec("IT-040")
def test_stream_at_the_requested_rate(mock_device: Factory) -> None:
    dev = mock_device(identifier="IT-040-stream")
    for rate in (0.05, 4.1):
        with pytest.raises(ValueError):
            stream(dev, rate)
    for rate in (0.1, 4.0):
        stream(dev, rate)
    start = time.monotonic()
    got = list(stream(dev, 2.0, duration=2.0))
    took = time.monotonic() - start
    # Ticks at 0, 0.5, 1.0 and 1.5 s.
    assert len(got) == 4
    assert all(isinstance(r, Reading) for r in got)
    stamps = [r.wall_ns for r in got]
    assert stamps == sorted(set(stamps))
    gaps = [b.timestamp - a.timestamp for a, b in zip(got, got[1:], strict=False)]
    assert all(0.3 <= g <= 0.7 for g in gaps), gaps
    assert 1.3 <= took <= 2.3


@pytest.mark.spec("IT-040")
def test_stream_from_a_slow_supply_delivers_what_it_gets_and_warns_once(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    s = script(replies=[c3_reply(C3_CAPTURE, after_s=0.6)])
    dev = mock_device([s], identifier="IT-040-slow")
    got = list(stream(dev, 4.0, duration=2.0))
    # Eight ticks, one reading about every 0.7 s.
    assert 1 <= len(got) < 8
    stamps = [r.wall_ns for r in got]
    assert stamps == sorted(set(stamps))
    assert messages(caplog, "mp305", logging.WARNING).count(FEWER) == 1


# to_csv() (SR-034, SR-037).

ROW = re.compile(
    r"\d{4}-\d\d-\d\dT\d\d:\d\d:\d\d\.\d{3}Z,\d+\.\d{3},"
    r"0\.00,0\.000,0\.00,13\.00,1\.000,0,off,\n"
)
"""A row of the capture reading: UTF-8, commas, `.` as the decimal point."""


def check_csv(text: str) -> list[str]:
    """Checks the header and every row; returns the rows."""
    lines = text.splitlines(keepends=True)
    assert lines[0] == HEADER
    for line in lines[1:]:
        assert ROW.fullmatch(line), line
    return lines[1:]


@pytest.mark.spec("IT-040")
def test_to_csv_for_a_duration(mock_device: Factory, tmp_path: pathlib.Path) -> None:
    dev = mock_device(identifier="IT-040-csv")
    path = tmp_path / "log.csv"
    count = to_csv(dev, path, rate=4.0, duration=1.0)
    data = path.read_bytes()
    assert b"\r" not in data
    rows = check_csv(data.decode("utf-8"))
    assert count == len(rows) == 4
    assert rows[0].split(",")[1] == "0.000"


@pytest.mark.spec("IT-040")
def test_to_csv_flushes_while_it_records(mock_device: Factory, tmp_path: pathlib.Path) -> None:
    dev = mock_device(identifier="IT-040-csv-flush")
    path = tmp_path / "log.csv"
    result: dict[str, object] = {}

    def record() -> None:
        try:
            result["count"] = to_csv(dev, path, rate=2.0, duration=3.0)
        except Exception as error:
            result["error"] = error

    thread = threading.Thread(target=record)
    thread.start()

    def rows_on_disk() -> int:
        try:
            return max(0, len(path.read_text(encoding="utf-8").splitlines()) - 1)
        except FileNotFoundError:
            return 0

    # Rows are due at 0 and 0.5 s; both are on disk by 1.5 s, while the
    # recording still runs until 3 s.
    assert wait_until(lambda: rows_on_disk() >= 2, 1.5)
    assert thread.is_alive()
    thread.join(5.0)
    assert result == {"count": 6}
    assert len(check_csv(path.read_text(encoding="utf-8"))) == 6


TO_CSV_UNTIL_INTERRUPTED = """
import pathlib
dev = Mp305._from_mock([testing.default_script()], identifier="IT-040-csv-interrupt")
sigint_after(0.8)
outcome = None
latency = None
try:
    mp305.to_csv(dev, PATH)
    outcome = "returned"
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
dev.close()
report(outcome=outcome, latency=latency, text=pathlib.Path(PATH).read_text(encoding="utf-8"))
"""


@pytest.mark.spec("IT-040")
def test_to_csv_until_interrupted(tmp_path: pathlib.Path) -> None:
    # A child process, since Ctrl-C acts on the main thread only.
    path = tmp_path / "log.csv"
    report, proc = run_child(f"PATH = {str(path)!r}\n" + TO_CSV_UNTIL_INTERRUPTED)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    rows = check_csv(report["text"])
    assert len(rows) >= 2


# ramp() (SR-035).


@pytest.mark.spec("IT-040")
def test_ramp_of_the_voltage_and_of_the_current_limit(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="IT-040-ramp", record=rec)
    assert ramp(dev, "voltage", 1.0, 2.0, 0.25, 0.05) == [1.0, 1.25, 1.5, 1.75, 2.0]
    assert ramp(dev, "current", 0.3, 0.1, 0.1, 0.0) == [0.3, 0.2, 0.1]
    sent = frames.c8(rec.sent())
    assert sent[0].remote_con == 2
    commands = [(c.set_voltage, c.set_current) for c in sent if c.remote_con == 1]
    assert commands == [(100, 1000), (125, 1000), (150, 1000), (175, 1000), (200, 1000)] + [
        (1300, 300),
        (1300, 200),
        (1300, 100),
    ]
    # The output stays as the reading has it.
    assert {c.output for c in sent} == {C3_CAPTURE[24]}


@pytest.mark.spec("IT-040")
def test_ramp_checks_every_point_before_the_first(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="IT-040-ramp-check", record=rec, max_voltage=12.0)
    for args in (
        ("voltage", 1.0, 12.5, 0.5, 0.0),  # above the user limit
        ("current", 0.1, 5.001, 0.1, 0.0),  # above the supply's range
        ("voltage", math.nan, 2.0, 0.5, 0.0),
    ):
        with pytest.raises(SetpointRangeError):
            ramp(dev, *args)  # type: ignore[arg-type]
    assert frames.sent(rec.sent(), 0xC8) == []


@pytest.mark.spec("IT-040")
def test_ramp_stops_at_the_first_error(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    s = script(
        replies=[
            c3_reply(testing.c3(output=1)),
            reply(0xC8, b"\x00", repeat=2),
            reply(0xC8, b"\xff", repeat=1),
            reply(0xC8, b"\x00"),
        ]
    )
    dev = mock_device([s], identifier="IT-040-ramp-error", record=rec)
    with pytest.raises(CommandRejectedError):
        ramp(dev, "voltage", 1.0, 2.0, 0.25, 0.0)
    time.sleep(0.3)
    sent = frames.c8(rec.sent())
    # The request, 1.00 V, then 1.25 V, which was rejected; nothing after it,
    # and the output stays on as the reading has it.
    assert [(c.remote_con, c.set_voltage) for c in sent] == [(2, 1300), (1, 100), (1, 125)]
    assert {c.output for c in sent} == {1}


RAMP_UNTIL_INTERRUPTED = """
rec = testing.MockRecord()
s = script(replies=[c3_reply(testing.c3(output=1))])
dev = Mp305._from_mock([s], identifier="IT-040-ramp-interrupt", record=rec)
sigint_after(0.6)
outcome = None
latency = None
try:
    mp305.ramp(dev, "voltage", 1.0, 2.0, 0.25, 1.0)
    outcome = "returned"
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
time.sleep(0.3)
sent = frames.as_dicts(rec.sent())
dev.close()
report(outcome=outcome, latency=latency, sent=sent)
"""


@pytest.mark.spec("IT-040")
def test_ramp_stops_at_keyboard_interrupt() -> None:
    # A child process, since Ctrl-C acts on the main thread only. The first
    # point is set within about 0.3 s; the signal comes 0.6 s in, during its
    # 1 s dwell.
    report, proc = run_child(RAMP_UNTIL_INTERRUPTED)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    sent = frames.c8(frames.from_dicts(report["sent"]))
    assert [(c.remote_con, c.set_voltage) for c in sent] == [(2, 1300), (1, 100)]
    assert {c.output for c in sent} == {1}
