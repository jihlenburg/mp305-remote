"""Test support for the mp305 library: the scripted mock transport.

Implements: DD-PY-045, DD-PY-034 (the Python wrapper of `MockHandles`).

This module is test support. It is outside `mp305.__all__` and carries no
stability promise: its names may change in any release. Nothing here can
reach a real supply.

A script drives one mock connection attempt; times are seconds from the
creation of that attempt's mock. `Mp305._from_mock` takes one script per
attempt (the first connect, then each reconnection).
"""

from __future__ import annotations

import contextlib
from collections.abc import Iterator
from typing import Literal, TypedDict, Union

from mp305 import _native, device
from mp305.errors import NotFoundError
from mp305.types import Event, Found, SentFrame, Transport, event_from_native, sent_from_native

RouteName = Literal["af01", "af02", "hid"]
"""A route of the mock: the two Bluetooth characteristics or USB."""


class _ReplyRequired(TypedDict):
    """The required keys of a reply."""

    request: int
    after_s: float
    deliveries: list[bytes]


class ReplyDict(_ReplyRequired, total=False):
    """A scripted reply to requests with one opcode.

    `deliveries` are on-air units; `repeat` None means forever; `from_s` is
    when the reply becomes eligible; `route` None means the default route.
    """

    repeat: int | None
    from_s: float
    route: RouteName | None


class _InjectionRequired(TypedDict):
    """The required keys of an injection."""

    at_s: float
    delivery: bytes


class InjectionDict(_InjectionRequired, total=False):
    """A delivery at a fixed time; `route` None means AF01 or USB."""

    route: RouteName | None


class _SendErrorRequired(TypedDict):
    """The required key of a send error."""

    opcode: int


class SendErrorDict(_SendErrorRequired, total=False):
    """A send failure for one opcode from `from_s` on."""

    from_s: float


class _MockScriptRequired(TypedDict):
    """The required key of a mock script."""

    kind: Transport


class MockScript(_MockScriptRequired, total=False):
    """One mock connection attempt."""

    replies: list[ReplyDict]
    injections: list[InjectionDict]
    send_errors: list[SendErrorDict]
    stop_replying_at_s: float
    close_at_s: float


class ErrorScript(TypedDict):
    """An attempt that fails with `transport: <error>`."""

    error: str


class NotFoundScript(TypedDict):
    """An attempt that fails with "no supply found"."""

    not_found: bool


ScriptDict = Union[MockScript, ErrorScript, NotFoundScript]
"""What one connection attempt does."""

MOCK_HOST_ID: bytes = _native.MOCK_HOST_ID
"""The host ID of a mock session without a state directory."""


class MockRecord:
    """The record of the frames a mock session's transports were given.

    Attributes:
        handles: The native handle list `_native.Session.from_mock` takes.
    """

    def __init__(self) -> None:
        """Creates an empty record."""
        self.handles = _native.MockHandles()

    def sent(self) -> list[SentFrame]:
        """Every frame sent, over every attempt, in order."""
        return [sent_from_native(t) for t in self.handles.sent()]

    def closes(self) -> int:
        """How often a mock was closed."""
        return self.handles.closes()

    def attempts(self) -> int:
        """How many mocks were made (failed attempts are not counted)."""
        return self.handles.attempts()


def ble_frame(opcode: int, payload: bytes) -> bytes:
    """The on-air bytes of a Bluetooth frame from the supply.

    `31 op payload` on AF01; `op payload` for the bind reply `0x19` on AF02.
    """
    return _native.on_air("ble", opcode, payload)


def hid_stream(opcode: int, payload: bytes) -> bytes:
    """The USB reply stream of a frame from the supply.

    `AA 21 len op payload sum`, every later `AA` doubled.
    """
    return _native.on_air("hid", opcode, payload)


def c3(
    output: int = 0,
    model: int = 0,
    charge_error: int = 0,
    set_voltage: int = 1300,
    set_current: int = 1000,
) -> bytes:
    """A `0xC3` payload: the capture with these raw fields replaced.

    Args:
        output: 0 off, 1 on.
        model: The live mode: 0 DC, 1 program, 2 PD, 3 charge.
        charge_error: The fault bits.
        set_voltage: The voltage setpoint in 10 mV.
        set_current: The current limit in mA.

    Returns:
        The 36 payload bytes.
    """
    return _native.c3(output, model, charge_error, set_voltage, set_current)


def fixtures() -> dict[str, bytes]:
    """The capture payloads: C3_CAPTURE, E1_BLE, E1_USB and C5_SETTINGS."""
    return _native.fixtures()


def sample_events() -> list[Event]:
    """One event of each kind, both prompts included, numbered from 1."""
    return [event_from_native(t) for t in _native.sample_events()]


def _reply(kind: Transport, request: int, after_s: float, payload: bytes) -> ReplyDict:
    """A reply on the default route, forever."""
    frame = ble_frame if kind == "ble" else hid_stream
    return {
        "request": request,
        "after_s": after_s,
        "deliveries": [frame(request + 1, payload)],
        "repeat": None,
    }


def default_script(kind: Transport = "ble") -> MockScript:
    """A script that connects and polls without trouble.

    Over Bluetooth it answers `0x18` with `19 00` after 5 ms, `0xE0` with
    `E1_BLE` after 5 ms, `0xC2` with `C3_CAPTURE` after 10 ms and `0xC8` with
    `C9 00` after 5 ms, each forever and on the default route; over USB the
    same without `0x18` and with `E1_USB`.

    Args:
        kind: "ble" or "hid".

    Returns:
        A fresh script dict.
    """
    payloads = fixtures()
    replies: list[ReplyDict] = []
    if kind == "ble":
        replies.append(_reply(kind, 0x18, 0.005, b"\x00"))
    info = payloads["E1_BLE"] if kind == "ble" else payloads["E1_USB"]
    replies.append(_reply(kind, 0xE0, 0.005, info))
    replies.append(_reply(kind, 0xC2, 0.010, payloads["C3_CAPTURE"]))
    replies.append(_reply(kind, 0xC8, 0.005, b"\x00"))
    return {"kind": kind, "replies": replies}


@contextlib.contextmanager
def mock_discovery(
    found: list[Found], scripts: list[ScriptDict] | None = None
) -> Iterator[MockRecord]:
    """Replaces discovery and the connect with the mock while active.

    `Mp305.connect()` and `discover()` then see `found`, and a connect to an
    identifier in it runs `scripts` (or the default script of its transport)
    on the mock; any other identifier raises `NotFoundError`. Process-wide
    and not thread-safe; both seams are restored on exit, also on an
    exception.

    Args:
        found: What discovery returns.
        scripts: The scripts of a connection; None for the default script.

    Yields:
        The record of the mock connections.
    """
    record = MockRecord()
    by_identifier = {f.identifier: f for f in found}

    def fake_discover(scan_time: float, bluetooth: bool, usb: bool) -> list[Found]:
        return list(found)

    def fake_open(
        identifier: str,
        state_dir: device.StatePath | None,
        reconnect: bool,
        max_voltage: float | None,
        max_current: float | None,
    ) -> _native.Session:
        supply = by_identifier.get(identifier)
        if supply is None:
            raise NotFoundError(_native.not_found_text())
        return _native.Session.from_mock(
            scripts or [default_script(supply.transport)],
            state_dir,
            reconnect,
            max_voltage,
            max_current,
            identifier,
            record.handles,
        )

    saved = (device._discover, device._open_session)
    device._discover = fake_discover
    device._open_session = fake_open
    try:
        yield record
    finally:
        device._discover, device._open_session = saved
