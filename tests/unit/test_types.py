"""UT-PY-005: the typed readings and events, and the native boundary."""

from __future__ import annotations

import dataclasses
from collections.abc import Callable

import pytest

from mp305 import Mp305, _native, testing
from mp305.types import (
    EventKind,
    Fault,
    LiveMode,
    Mode,
    Settings,
    event_from_native,
)
from tests.unit.support import c3_reply, script

Factory = Callable[..., Mp305]

FIELDS = (
    "reading",
    "faults",
    "settings",
    "recognised",
    "remote_state",
    "prompt",
    "bound_s",
    "text",
    "set_voltage",
    "set_current",
    "expected_voltage",
    "expected_current",
    "since",
)


@pytest.mark.spec("UT-PY-005")
def test_a_sample_events() -> None:
    events = testing.sample_events()
    assert [e.kind for e in events] == [
        EventKind.FAULTS_CHANGED,
        EventKind.SETTINGS_CHANGED,
        EventKind.BIND_RESULT,
        EventKind.REMOTE_CONTROL,
        EventKind.PROMPT,
        EventKind.PROMPT,
        EventKind.SETPOINTS_CHANGED,
        EventKind.UNCLEAN_EXIT_WARNING,
        EventKind.LINK_LOST,
        EventKind.RECONNECTED,
        EventKind.RECONNECT_GAVE_UP,
    ]
    assert [e.seq for e in events] == list(range(1, 12))
    expected: list[dict[str, object]] = [
        {"faults": frozenset({Fault.REVERSED_OUTPUT, Fault.OVER_CURRENT, Fault.UNKNOWN_BIT_11})},
        {"settings": Settings(90, 2, 0, 0, 1, 500, 50, 0)},
        {"recognised": False},
        {"remote_state": "granted"},
        {
            "prompt": "confirm_connection",
            "bound_s": 30,
            "text": "Confirm the connection on the supply's screen within 30 seconds",
        },
        {
            "prompt": "allow_remote_control",
            "bound_s": 70,
            "text": "Allow remote control on the supply's screen",
        },
        {"set_voltage": 1.5, "set_current": 1.0, "expected_voltage": 1.7, "expected_current": 1.0},
        {"since": 1790845200.0, "text": "u"},
        {"text": "t"},
        {},
        {"text": "g"},
    ]
    for event, fields in zip(events, expected, strict=True):
        for name in FIELDS:
            if name == "reading" and event.kind is EventKind.FAULTS_CHANGED:
                continue
            assert getattr(event, name) == fields.get(name), (event.kind, name)
        hash(event)
    first = events[0].reading
    assert first is not None
    assert first.set_voltage == 13.0


@pytest.mark.spec("UT-PY-005")
def test_b_the_decoder_is_strict() -> None:
    with pytest.raises(ValueError, match="nope"):
        event_from_native((1, "nope", {}))
    with pytest.raises(ValueError, match="text"):
        event_from_native((1, "link_lost", {}))
    with pytest.raises(ValueError, match="x"):
        event_from_native((1, "link_lost", {"text": "t", "x": 1}))


def patched(**fields: int) -> bytes:
    """The capture with raw fields replaced at their offsets."""
    payload = bytearray(testing.fixtures()["C3_CAPTURE"])
    layout = {
        "out_state": (0, 1),
        "voltage": (3, 2),
        "current": (7, 2),
        "energy": (15, 4),
        "power": (19, 2),
        "model": (25, 1),
    }
    for name, value in fields.items():
        offset, size = layout[name]
        payload[offset : offset + size] = value.to_bytes(size, "little")
    return bytes(payload)


@pytest.mark.spec("UT-PY-005")
def test_c_reading_fields(mock_device: Factory) -> None:
    raw = patched(out_state=9, voltage=1234, current=567, energy=89, power=700, model=7)
    dev = mock_device([script(replies=[c3_reply(raw)])], identifier="UT-PY-005-c")
    r = dev.reading
    assert r is not None
    assert r.voltage == 12.34
    assert r.current == 0.567
    assert r.energy == 8.9
    assert r.power == 7.0
    assert r.set_voltage == 13.0
    assert r.set_current == 1.0
    assert r.output_on is False
    assert r.mode is Mode.UNKNOWN
    assert r.mode_raw == 9
    assert r.mode_text == "unknown (9)"
    assert r.live_mode is LiveMode.UNKNOWN
    assert r.live_mode_raw == 7
    assert r.faults == frozenset()
    assert r.temperature == 26
    assert r.working_time == 1
    assert len(r.raw) == 36
    assert r.timestamp == r.wall_ns / 1e9
    with pytest.raises(dataclasses.FrozenInstanceError):
        r.voltage = 0  # type: ignore[misc]
    hash(r)
    held = mock_device(
        [script(replies=[c3_reply(patched(out_state=3))])], identifier="UT-PY-005-c2"
    )
    r2 = held.reading
    assert r2 is not None
    assert r2.mode is Mode.HELD_ABOVE
    assert r2.mode_text == "held above setpoint"


@pytest.mark.spec("UT-PY-005")
def test_d_fault_columns() -> None:
    for bit in range(16):
        row = _native.format_csv_row(testing.c3(charge_error=1 << bit), 0, 0)
        assert row.rstrip("\n").split(",")[-1] == Fault(bit).text
