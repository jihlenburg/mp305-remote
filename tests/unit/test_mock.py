"""UT-PY-019: the mock bridge and reconnection on the mock."""

from __future__ import annotations

import logging
import math
import threading
import time
from collections.abc import Callable
from typing import Any

import pytest

from mp305 import EventKind, LinkLostError, Mp305, Reading, testing
from tests.unit import frames
from tests.unit.support import reply, script, wait_until

Factory = Callable[..., Mp305]
UNRECOGNISED = "The supply did not recognise this host; connect again to confirm on its screen."


@pytest.mark.spec("UT-PY-019")
def test_a_bad_scripts() -> None:
    rec = testing.MockRecord()
    bad_reply = script()
    bad_reply["replies"][0]["deliveries"] = "abc"
    late = script()
    late["replies"][0]["after_s"] = -0.1
    cases: list[tuple[dict[str, Any], str]] = [
        ({"kind": "ble", "replyz": []}, "replyz"),
        (bad_reply, "deliveries"),
        (late, "after_s"),
        (script(close_at_s=math.nan), "close_at_s"),
        (script(replies=[reply(0xC2, b"", route="hid")]), "route"),
        ({"kind": "usb"}, "kind"),
    ]
    for s, key in cases:
        with pytest.raises(ValueError) as info:
            Mp305._from_mock([s], identifier="UT-PY-019-a", record=rec)
        assert "script 0" in str(info.value), key
        assert key in str(info.value)
    assert rec.attempts() == 0


@pytest.mark.spec("UT-PY-019")
def test_b_on_air_bytes() -> None:
    fixtures = testing.fixtures()
    capture = fixtures["C3_CAPTURE"]
    assert testing.ble_frame(0xC3, capture) == b"\x31\xc3" + capture
    assert testing.ble_frame(0x19, b"\xff") == b"\x19\xff"
    usb = fixtures["E1_USB"]
    assert testing.hid_stream(0xE1, usb) == bytes([0xAA, 0x21, 0x1F, 0xE1]) + usb + b"\x6d"
    stream = testing.hid_stream(0xC3, testing.c3(set_voltage=170))
    assert stream.startswith(bytes.fromhex("aa 21 25 c3 00 00 5a 00 00 aa aa 00"))
    assert stream.endswith(b"\x5e")
    payload = testing.c3(output=1, set_voltage=500)
    assert len(payload) == 36
    assert payload[24] == 1
    assert payload[5:7] == b"\xf4\x01"


def loss_and_events(dev: Mp305, kinds: list[EventKind], kind: EventKind, timeout: float) -> float:
    """Polls `events()` every 50 ms until `kind` arrives; returns its time."""
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        for event in dev.events():
            kinds.append(event.kind)
            if event.kind is kind:
                return time.monotonic()
        time.sleep(0.05)
    raise AssertionError(f"no {kind} within {timeout} s; saw {kinds}")


@pytest.mark.spec("UT-PY-019")
def test_c_reconnection(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    first = script(close_at_s=1.0)
    dev = mock_device(
        [first, testing.default_script()], identifier="UT-PY-019-c", reconnect=True, record=rec
    )
    got: list[Reading] = []
    errors: list[BaseException] = []
    stop = threading.Event()

    def iterate() -> None:
        try:
            for reading in dev.readings():
                got.append(reading)
                if stop.is_set():
                    return
        except BaseException as error:
            errors.append(error)

    thread = threading.Thread(target=iterate)
    thread.start()
    kinds: list[EventKind] = []
    lost = loss_and_events(dev, kinds, EventKind.LINK_LOST, 3.0)
    reconnected = loss_and_events(dev, kinds, EventKind.RECONNECTED, 7.5)
    assert reconnected - lost <= 7.0
    count = len(got)
    time.sleep(0.5)
    stop.set()
    thread.join(2.0)
    assert errors == []
    assert len(got) > count
    assert rec.attempts() == 2
    second = [f for f in rec.sent() if f.attempt == 1]
    opcodes = [f.opcode for f in second]
    assert {0x18, 0xE0, 0xC2} <= set(opcodes)
    bind = frames.sent(second, 0x18)[0]
    assert bind.payload[-1] == 1


@pytest.mark.spec("UT-PY-019")
def test_d_the_reconnection_gives_up(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    second = script(replies=[reply(0x18, b"\xff")])
    dev = mock_device(
        [script(close_at_s=1.0), second], identifier="UT-PY-019-d", reconnect=True
    )
    kinds: list[EventKind] = []
    gave_up_events = []
    lost = loss_and_events(dev, kinds, EventKind.LINK_LOST, 3.0)
    deadline = lost + 7.0
    while time.monotonic() < deadline and not gave_up_events:
        gave_up_events = [e for e in dev.events() if e.kind is EventKind.RECONNECT_GAVE_UP]
        time.sleep(0.05)
    assert gave_up_events and gave_up_events[0].text == UNRECOGNISED
    with pytest.raises(LinkLostError) as info:
        for _ in dev.readings():
            pass
    assert "The output is still in its last state" in str(info.value)
    assert "did not recognise this host" in str(info.value)
    t = time.monotonic()
    with pytest.raises(LinkLostError):
        dev.read()
    assert time.monotonic() - t < 0.2
    loss = "The transport reported the link closed. The output is still in its last state"
    # The core's records may still be on their way from the delivery thread.
    wait_until(
        lambda: any(UNRECOGNISED in r.getMessage() for r in caplog.records)
        and any(loss in r.getMessage() for r in caplog.records),
        1.0,
    )
    texts = [r.getMessage() for r in caplog.records]
    assert sum(loss in m for m in texts) == 1
    assert sum(UNRECOGNISED in m for m in texts) == 1


@pytest.mark.spec("UT-PY-019")
def test_e_reconnection_switched_off(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(
        [script(close_at_s=1.0)], identifier="UT-PY-019-e", reconnect=True, record=rec
    )
    kinds: list[EventKind] = []
    lost = loss_and_events(dev, kinds, EventKind.LINK_LOST, 3.0)
    time.sleep(max(0.0, lost + 2.0 - time.monotonic()))
    dev.reconnect = False
    events = []
    deadline = lost + 7.0
    while time.monotonic() < deadline and not events:
        events = [e for e in dev.events() if e.kind is EventKind.RECONNECT_GAVE_UP]
        time.sleep(0.05)
    assert events and events[0].text == "Reconnection switched off."
    assert rec.attempts() == 1
    logging.getLogger("tests").debug("gave up after %s s", time.monotonic() - lost)
