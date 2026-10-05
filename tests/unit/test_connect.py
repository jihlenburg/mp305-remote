"""UT-PY-011, UT-PY-012 and UT-PY-029: discovery, connect and the connect flow."""

from __future__ import annotations

import math
import time
from collections.abc import Callable
from typing import Any

import pytest

from mp305 import (
    Found,
    Info,
    Mp305,
    Mp305Error,
    Mp305TimeoutError,
    NotFoundError,
    SetpointRangeError,
    _native,
    device,
    discover,
    testing,
)
from tests.unit import frames
from tests.unit.support import reply, run_child, script

Factory = Callable[..., Mp305]


def found(identifier: str, transport: str = "ble") -> Found:
    """A found supply over `transport`."""
    return Found(
        transport=transport,  # type: ignore[arg-type]
        identifier=identifier,
        unit_id="E!K",
        name="MP305B",
        rssi=-60 if transport == "ble" else None,
        remote_flag=None,
        description=f"{transport} {identifier} MP305B (unit E!K)",
    )


@pytest.mark.spec("UT-PY-011")
def test_a_scan_time_is_checked_first(monkeypatch: pytest.MonkeyPatch) -> None:
    calls: list[Any] = []
    monkeypatch.setattr(device, "_discover", lambda *args: calls.append(args) or [])
    for value in (0.5, 61, -1.0, math.nan, math.inf):
        with pytest.raises(SetpointRangeError) as info:
            discover(scan_time=value)
        assert info.value.field == "scan time (s)"
        assert (info.value.minimum, info.value.maximum) == (1.0, 60.0)
        if value == 0.5:
            assert str(info.value) == "scan time (s) 0.5 is outside 1 to 60"
    assert calls == []
    with pytest.raises(TypeError):
        discover(True)
    with pytest.raises(TypeError):
        discover("10")  # type: ignore[arg-type]
    for value in (-1.0, math.nan):
        with pytest.raises(SetpointRangeError):
            _native.discover(value, True, True)


@pytest.mark.spec("UT-PY-011")
def test_b_none_found() -> None:
    with testing.mock_discovery([]):
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    assert str(info.value) == _native.not_found_text()
    assert str(info.value).startswith("no supply found: the supply is off or out of range;")
    assert info.value.found == ()


@pytest.mark.spec("UT-PY-011")
def test_c_one_found() -> None:
    with testing.mock_discovery([found("UT-PY-011-c")]) as record:
        with Mp305.connect() as dev:
            assert dev.identifier == "UT-PY-011-c"
            assert dev.link_state == "ready"
            assert dev.transport == "ble"
            assert frames.sent(record.sent(), 0x18)
    with testing.mock_discovery([found("UT-PY-011-c-hid", "hid")]) as record:
        with Mp305.connect() as dev:
            assert dev.transport == "hid"
            assert frames.sent(record.sent(), 0x18) == []
            assert frames.sent(record.sent(), 0xE0)


@pytest.mark.spec("UT-PY-011")
def test_d_several_found() -> None:
    # Two over Bluetooth: one hid and one ble entry get the text of UT-PY-029.
    supplies = [found("UT-PY-011-d1"), found("UT-PY-011-d2")]
    with testing.mock_discovery(supplies) as record:
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    assert str(info.value) == (
        "several supplies found; pass one identifier: "
        + "; ".join(f.description for f in supplies)
    )
    assert info.value.found == tuple(supplies)
    assert record.attempts() == 0


@pytest.mark.spec("UT-PY-011")
def test_e_the_seams_are_restored() -> None:
    before = (device._discover, device._open_session)
    with pytest.raises(RuntimeError):
        with testing.mock_discovery([found("UT-PY-011-e")]):
            raise RuntimeError("inside")
    assert (device._discover, device._open_session) == before
    assert device._open_session is _native.Session.connect


@pytest.mark.spec("UT-PY-029")
def test_a_one_unit_on_usb_and_over_bluetooth_is_explained() -> None:
    supplies = [found("UT-PY-029-a-ble"), found("UT-PY-029-a-hid", "hid")]
    with testing.mock_discovery(supplies) as record:
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    assert str(info.value) == (
        "found one supply on USB and one over Bluetooth; a supply on a USB cable is"
        " also seen over Bluetooth until a USB host talks to it. Pass usb=False or"
        " bluetooth=False to choose a transport, or pass one identifier: "
        + "; ".join(f.description for f in supplies)
    )
    assert info.value.found == tuple(supplies)
    assert record.attempts() == 0
    # Two over USB and one over Bluetooth keep the plain text.
    three = [*supplies, found("UT-PY-029-a-hid2", "hid")]
    with testing.mock_discovery(three):
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    assert str(info.value).startswith("several supplies found; pass one identifier: ")


@pytest.mark.spec("UT-PY-029")
def test_b_a_chosen_transport_is_the_only_one_scanned(monkeypatch: pytest.MonkeyPatch) -> None:
    supplies = [found("UT-PY-029-b-ble"), found("UT-PY-029-b-hid", "hid")]
    with testing.mock_discovery(supplies):
        with Mp305.connect(bluetooth=False) as dev:
            assert dev.identifier == "UT-PY-029-b-hid"
            assert dev.transport == "hid"
        with Mp305.connect(usb=False) as dev:
            assert dev.identifier == "UT-PY-029-b-ble"
            assert dev.transport == "ble"
        with pytest.raises(NotFoundError) as info:
            Mp305.connect(bluetooth=False, usb=False)
        assert info.value.found == ()
    calls: list[Any] = []
    monkeypatch.setattr(device, "_discover", lambda *args: calls.append(args) or [])
    for bluetooth, usb in ((True, True), (False, True), (True, False), (False, False)):
        with pytest.raises(NotFoundError):
            Mp305.connect(bluetooth=bluetooth, usb=usb, scan_time=2.0)
    assert calls == [
        (2.0, True, True),
        (2.0, False, True),
        (2.0, True, False),
        (2.0, False, False),
    ]


@pytest.mark.spec("UT-PY-029")
def test_c_an_identifier_with_a_transport_choice_is_refused(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    calls: list[Any] = []
    monkeypatch.setattr(device, "_discover", lambda *args: calls.append(args) or [])
    monkeypatch.setattr(device, "_open_session", lambda *args: calls.append(args))
    for flags in ({"usb": False}, {"bluetooth": False}, {"bluetooth": False, "usb": False}):
        with pytest.raises(ValueError) as info:
            Mp305.connect("UT-PY-029-c", **flags)
        assert not isinstance(info.value, SetpointRangeError)
        assert str(info.value) == (
            "bluetooth and usb choose the transports of the scan without an identifier;"
            " leave them at True when an identifier is given"
        )
    for wrong in ({"usb": 0}, {"bluetooth": 1}, {"usb": None}, {"bluetooth": "no"}):
        with pytest.raises(TypeError, match="bluetooth and usb must be bools"):
            Mp305.connect(**wrong)
        with pytest.raises(TypeError, match="bluetooth and usb must be bools"):
            Mp305.connect("UT-PY-029-c", **wrong)
    assert calls == []


@pytest.mark.spec("UT-PY-012")
def test_a_ble(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device([testing.default_script()], identifier="UT-PY-012-a", record=rec)
    assert dev.info == Info(
        model="MP305B", version="1.6.0.40", hardware="2.0.2.0", bootloader=None, name=None
    )
    assert dev.transport == "ble"
    assert dev.link_state == "ready"
    assert dev.reading is not None
    assert dev.unclean_exit_warning is None
    first = rec.sent()[0]
    assert (first.opcode, first.route) == (0x18, "af02")
    assert first.payload == testing.MOCK_HOST_ID + bytes([0, 1])


@pytest.mark.spec("UT-PY-012")
def test_b_hid(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device([testing.default_script("hid")], identifier="UT-PY-012-b", record=rec)
    assert dev.info == Info(
        model="MP305B",
        version="1.6.0.51",
        hardware=None,
        bootloader=bytes(range(1, 9)),
        name="MP305B",
    )
    assert dev.transport == "hid"
    assert frames.sent(rec.sent(), 0x18) == []
    first = rec.sent()[0]
    assert (first.opcode, first.route) == (0xE0, "hid")


@pytest.mark.spec("UT-PY-012")
def test_c_a_failed_connect_releases_the_session(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    s = script(drop=[0xE0])
    start = time.monotonic()
    with pytest.raises(Mp305TimeoutError) as info:
        Mp305._from_mock([s], identifier="UT-PY-012-c", record=rec)
    elapsed = time.monotonic() - start
    assert str(info.value) == "no reply to 0xe0 within 1.0 s"
    assert 0.9 <= elapsed <= 2.0
    assert rec.closes() >= 1
    # "At once": no retry is needed and the connect takes its own few round
    # trips; 1 s leaves room for a loaded machine.
    again = time.monotonic()
    mock_device(identifier="UT-PY-012-c")
    assert time.monotonic() - again < 1.0


@pytest.mark.spec("UT-PY-012")
def test_d_control_before_ready() -> None:
    rec = testing.MockRecord()
    s = script(replies=[reply(0x18, b"\x00", after_s=0.3)])
    native = _native.Session.from_mock([s], None, False, None, None, "UT-PY-012-d", rec.handles)
    try:
        with pytest.raises(Mp305Error) as info:
            native.set_voltage(1.0, None)
        assert type(info.value) is Mp305Error
        assert str(info.value) == "the session is not ready for control"
        assert frames.sent(rec.sent(), 0xC8) == []
        assert native.ready(None) == ("MP305B", "1.6.0.40", "2.0.2.0", None, None)
    finally:
        native.close(True, None)


INTERRUPTED_BIND = """
rec = testing.MockRecord()
s = script(replies=[reply(0x18, b"\\xff", repeat=1), reply(0x18, b"\\x00", after_s=5.0)])
sigint_after(0.2)
outcome = None
try:
    Mp305._from_mock([s], identifier="UT-PY-012-e", record=rec)
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
second = time.monotonic()
deadline = second + 1.0
while True:
    try:
        dev = Mp305._from_mock([testing.default_script()], identifier="UT-PY-012-e")
        break
    except mp305.Mp305Error:
        if time.monotonic() > deadline:
            raise
        time.sleep(0.02)
reopened = time.monotonic() - second
dev.close()
report(outcome=outcome, latency=latency, reopened=reopened, closes=rec.closes())
"""


@pytest.mark.spec("UT-PY-012")
def test_e_ctrl_c_during_the_bind() -> None:
    report, proc = run_child(INTERRUPTED_BIND)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    assert report["reopened"] < 1.0
    assert report["closes"] == 1


class Stop(BaseException):
    """A test exception that is not an `Exception`."""


@pytest.mark.spec("UT-PY-012")
def test_f_a_base_exception_from_on_prompt(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    s = script(replies=[reply(0x18, b"\xff", repeat=1), reply(0x18, b"\x00", after_s=2.0)])
    prompted: list[float] = []

    def on_prompt(event: object) -> None:
        prompted.append(time.monotonic())
        raise Stop()

    with pytest.raises(Stop):
        Mp305._from_mock([s], identifier="UT-PY-012-f", record=rec, on_prompt=on_prompt)
    raised = time.monotonic()
    assert raised - prompted[0] < 0.3
    deadline = raised + 1.0
    while True:
        try:
            mock_device(identifier="UT-PY-012-f")
            break
        except Mp305Error:
            assert time.monotonic() < deadline
            time.sleep(0.02)
    assert rec.closes() == 1
