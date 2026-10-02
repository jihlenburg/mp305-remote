"""UT-PY-004: every core error reaches Python as its class, text and attributes."""

from __future__ import annotations

import pathlib
import threading
import time
from collections.abc import Callable
from typing import Any

import pytest

from mp305 import Mp305, _native, testing
from mp305.errors import (
    CommandRejectedError,
    ConnectionDeniedError,
    FaultActiveError,
    LinkLostError,
    ModeError,
    Mp305Error,
    Mp305TimeoutError,
    NotFoundError,
    RemoteControlDeniedError,
    RemoteControlLostError,
    SetpointRangeError,
)
from mp305.types import EventKind, Fault
from tests.unit import frames
from tests.unit.support import c3_reply, reply, script, silent, wait_until

Factory = Callable[..., Mp305]


def raised(call: Callable[[], Any]) -> BaseException:
    """The exception `call` raises."""
    with pytest.raises(BaseException) as info:
        call()
    return info.value


@pytest.mark.spec("UT-PY-004")
def test_a_connection_denied() -> None:
    s = script(replies=[reply(0x18, b"\xff")])
    e = raised(lambda: Mp305._from_mock([s], identifier="UT-PY-004-a"))
    assert type(e) is ConnectionDeniedError
    assert str(e) == "the supply denied the connection"


@pytest.mark.spec("UT-PY-004")
def test_b_remote_control_denied(mock_device: Factory) -> None:
    dev = mock_device([script(replies=[reply(0xC8, b"\x01", repeat=1)])], identifier="UT-PY-004-b")
    e = raised(lambda: dev.set_voltage(1.0))
    assert type(e) is RemoteControlDeniedError
    assert str(e) == "the supply denied remote control"


@pytest.mark.spec("UT-PY-004")
def test_c_remote_control_lost(mock_device: Factory) -> None:
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\x01")])
    dev = mock_device([s], identifier="UT-PY-004-c")
    e = raised(lambda: dev.set_voltage(1.0))
    assert type(e) is RemoteControlLostError
    assert str(e) == "remote control is not held; request it again"


@pytest.mark.spec("UT-PY-004")
def test_d_command_rejected(mock_device: Factory) -> None:
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\xff")])
    dev = mock_device([s], identifier="UT-PY-004-d")
    e = raised(lambda: dev.set_voltage(1.0))
    assert type(e) is CommandRejectedError
    assert str(e) == "the supply rejected the command (status 0xff, busy)"
    assert e.status == 255
    assert e.reason == "busy"


@pytest.mark.spec("UT-PY-004")
def test_e_timeout(mock_device: Factory) -> None:
    s = script(
        replies=[reply(0xC8, b"\x00", repeat=1), silent(0xC8, repeat=1), reply(0xC8, b"\x00")]
    )
    dev = mock_device([s], identifier="UT-PY-004-e")
    start = time.monotonic()
    e = raised(lambda: dev.set_voltage(1.0))
    elapsed = time.monotonic() - start
    assert type(e) is Mp305TimeoutError
    assert str(e) == "no reply to 0xc8 within 1.0 s"
    assert 0.9 <= elapsed <= 1.8


@pytest.mark.spec("UT-PY-004")
def test_f_mode(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    s = script(replies=[c3_reply(testing.c3(model=2))])
    dev = mock_device([s], identifier="UT-PY-004-f", record=rec)
    e = raised(lambda: dev.set_voltage(1.0))
    assert type(e) is ModeError
    assert str(e).startswith("the supply is not in DC mode")
    assert e.live_mode_raw == 2
    assert frames.sent(rec.sent(), 0xC8) == []


@pytest.mark.spec("UT-PY-004")
def test_g_fault_active(mock_device: Factory) -> None:
    s = script(replies=[c3_reply(testing.c3(charge_error=1 << 5))])
    dev = mock_device([s], identifier="UT-PY-004-g")
    e = raised(dev.output_on)
    assert type(e) is FaultActiveError
    assert str(e) == "the supply reports a fault: over current"
    assert e.faults == frozenset({Fault.OVER_CURRENT})


@pytest.mark.spec("UT-PY-004")
def test_h_link_lost(mock_device: Factory) -> None:
    dev = mock_device([script(close_at_s=0.3)], identifier="UT-PY-004-h", reconnect=False)
    seen: list[EventKind] = []
    assert wait_until(
        lambda: seen.extend(e.kind for e in dev.events()) or EventKind.LINK_LOST in seen, 3.0
    )
    e = raised(lambda: dev.set_voltage(1.0))
    assert type(e) is LinkLostError
    assert str(e).startswith("link lost: The transport reported the link closed.")


@pytest.mark.spec("UT-PY-004")
def test_i_transport() -> None:
    e = raised(lambda: Mp305._from_mock([{"error": "boom"}], identifier="UT-PY-004-i"))
    assert type(e) is LinkLostError
    assert str(e) == "transport: boom"


@pytest.mark.spec("UT-PY-004")
def test_j_not_found() -> None:
    e = raised(lambda: Mp305._from_mock([{"not_found": True}], identifier="UT-PY-004-j"))
    assert type(e) is NotFoundError
    assert str(e) == _native.not_found_text()
    assert e.found == ()


@pytest.mark.spec("UT-PY-004")
def test_k_already_open(mock_device: Factory) -> None:
    mock_device(identifier="UT-PY-004-k")
    e = raised(lambda: Mp305._from_mock([testing.default_script()], identifier="UT-PY-004-k"))
    assert type(e) is Mp305Error
    assert str(e) == "a session to UT-PY-004-k is already open in this process"


@pytest.mark.spec("UT-PY-004")
def test_l_not_ready() -> None:
    rec = testing.MockRecord()
    s = script(replies=[reply(0x18, b"\x00", after_s=0.3)])
    native = _native.Session.from_mock([s], None, False, None, None, "UT-PY-004-l", rec.handles)
    try:
        e = raised(lambda: native.set_voltage(1.0, None))
        assert type(e) is Mp305Error
        assert str(e) == "the session is not ready for control"
        assert frames.sent(rec.sent(), 0xC8) == []
    finally:
        native.ready(None)
        native.close(True, None)


@pytest.mark.spec("UT-PY-004")
def test_m_protocol() -> None:
    s = script(replies=[reply(0xE0, b"\x01\x06\x00")])
    e = raised(lambda: Mp305._from_mock([s], identifier="UT-PY-004-m"))
    assert type(e) is Mp305Error
    assert str(e).startswith("protocol: ")


@pytest.mark.spec("UT-PY-004")
def test_n_store(tmp_path: pathlib.Path) -> None:
    blocker = tmp_path / "file"
    blocker.write_text("x")
    e = raised(lambda: _native.host_id(blocker / "state"))
    assert type(e) is Mp305Error
    assert str(e).startswith("store: ")


@pytest.mark.spec("UT-PY-004")
def test_o_cancelled_by_output_off(mock_device: Factory) -> None:
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\x00", after_s=0.3)])
    dev = mock_device([s], identifier="UT-PY-004-o")
    dev.request_remote_control()
    outcome: dict[str, BaseException | None] = {}

    def call_a() -> None:
        try:
            dev.set_voltage(1.0)
            outcome["a"] = None
        except BaseException as error:
            outcome["a"] = error

    a = threading.Thread(target=call_a)
    a.start()
    time.sleep(0.05)
    dev.output_off()
    a.join(5.0)
    e = outcome["a"]
    assert type(e) is Mp305Error
    assert str(e) == (
        "the command was cancelled: superseded by an output-off; it may have been applied"
    )


@pytest.mark.spec("UT-PY-004")
def test_p_setpoint_range_from_the_core() -> None:
    rec = testing.MockRecord()
    native = _native.Session.from_mock(
        [testing.default_script()], None, False, None, None, "UT-PY-004-p", rec.handles
    )
    try:
        native.ready(None)
        e = raised(lambda: native.set_voltage(31.0, None))
        assert type(e) is SetpointRangeError
        assert str(e) == "voltage 31 is outside 0 to 30"
        assert (e.field, e.value, e.minimum, e.maximum) == ("voltage", 31.0, 0.0, 30.0)
    finally:
        native.close(True, None)
