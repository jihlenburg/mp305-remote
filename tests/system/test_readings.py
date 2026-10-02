"""ST-012 to ST-017 and ST-033: state, readings, dropped frames and dispatch.

SR-012 to SR-017 and SR-033. The parts on the mock transport run without a
supply (`mp305.testing`, DD-PY-045); the mock runs on the real clock, so its
delays are milliseconds and the waits are polled with an upper bound.
"""

from __future__ import annotations

import dataclasses
import logging
import math
import time
from collections.abc import Callable
from typing import TYPE_CHECKING, Any

import pytest

from mp305 import (
    CommandRejectedError,
    EventKind,
    LiveMode,
    Mode,
    Mp305,
    Mp305Error,
    Mp305TimeoutError,
    Reading,
    Settings,
    testing,
)
from mp305.types import Fault
from tests.system.support import (
    FrameLog,
    c3_with_out_state,
    first_reading,
    reply,
    script,
    settled_reading,
    wait_until,
)

if TYPE_CHECKING:
    from tests.system.conftest import Guard, Person, Unit

Factory = Callable[..., Mp305]

C3_CAPTURE = testing.fixtures()["C3_CAPTURE"]
C5_SETTINGS = testing.fixtures()["C5_SETTINGS"]

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


def _collect(dev: Mp305, seconds: float) -> list[Reading]:
    """Every reading that arrives in the next `seconds`."""
    got: list[Reading] = []
    end = time.monotonic() + seconds
    for reading in dev.readings():
        got.append(reading)
        if time.monotonic() >= end:
            break
    return got


# ST-012


@pytest.mark.hil
@pytest.mark.spec("ST-012")
def test_st012_reported_values_match_the_supply_screens(
    hil_unit: Unit, person: Person, supply: Guard, observe: Callable[[str, object], None]
) -> None:
    """Model, versions, live mode and setpoints against the supply's screens."""
    dev = supply.connect()
    info = dev.info
    reading = dev.reading
    assert reading is not None
    shown = (
        f"model {info.model}, application version {info.version}, hardware revision "
        f"{info.hardware}, name {info.name}, live mode {reading.live_mode.value}, "
        f"set voltage {reading.set_voltage:.2f} V, current limit {reading.set_current:.3f} A"
    )
    observe("reported", shown)
    person.say(f"The library reports: {shown}.")
    match = person.ask(
        "Do these match the supply's information screen (System Version, hardware) and the "
        "setpoints on its main screen?"
    )
    assert match


@pytest.mark.hil
@pytest.mark.spec("ST-012")
def test_st012_a_control_call_before_the_first_reading_waits_or_refuses(
    hil_unit: Unit, supply: Guard, frame_log: FrameLog, observe: Callable[[str, object], None]
) -> None:
    """A control call before the first reading, through the two-step connect (DD-PY-031).

    The native connect returns before the connect flow ran, which is the
    hook that delays the first reading; the call is an output-off, which
    changes nothing on a supply whose output is off.
    """
    native = supply.native_connect()
    early: Exception | None = None
    try:
        native.output_off(None)
    except Mp305Error as error:
        early = error
    reading_when_answered = native.latest_reading() is not None
    info = native.ready(supply.native_dispatch())
    reading = native.latest_reading()
    frame_log.settle()
    observe("early_call", "returned" if early is None else f"{type(early).__name__}: {early}")
    # The values are there once ready returned (SR-012).
    assert info[0].startswith("MP305")
    assert reading is not None
    # The early call refused, or waited until a reading was there.
    if early is None:
        assert reading_when_answered
    else:
        assert str(early) == "the session is not ready for control"
    first_c3 = frame_log.received(0xC3)[0]
    assert [f for f in frame_log.sent(0xC8) if f.index < first_c3.index] == []


# ST-013


@pytest.mark.hil
@pytest.mark.spec("ST-013")
def test_st013_readings_for_60_s_with_the_output_off(
    hil_unit: Unit, supply: Guard, frame_log: FrameLog, observe: Callable[[str, object], None]
) -> None:
    """60 s of readings with the output off; the frame log keeps 100 ms after each reply."""
    dev = supply.connect()
    reading = dev.reading
    assert reading is not None
    assert not reading.output_on
    start = frame_log.mark()
    got = _collect(dev, 60.0)
    frame_log.settle()
    gaps = []
    last_reply = None
    for frame in frame_log.frames(start):
        if frame.direction == "rx":
            last_reply = frame
        elif last_reply is not None:
            gaps.append(frame.offset_ms - last_reply.offset_ms)
    observe("readings", len(got))
    observe("shortest_gap_ms", min(gaps) if gaps else None)
    assert len(got) >= 120
    assert gaps
    assert min(gaps) >= 100


# ST-014


@pytest.mark.hil
@pytest.mark.spec("ST-014")
def test_st014_readings_with_load_a(
    hil_unit: Unit,
    load_a: str,
    person: Person,
    controls: Person,
    supply: Guard,
    observe: Callable[[str, object], None],
) -> None:
    """Step 1 on the front panel, step 2 with Load A and the output on; for TBD-011."""
    dev = supply.connect()
    # Step 1: 5.00 V, 0.100 A on the front panel.
    person.say("On the supply's front panel, set 5.00 V and 0.100 A now; leave the output off.")

    def set_on_panel() -> bool:
        r = dev.reading
        return r is not None and r.set_voltage == 5.0 and r.set_current == 0.1

    assert wait_until(set_on_panel, 180.0, step=0.5), "5.00 V and 0.100 A not seen within 180 s"
    # Step 2: Load A, output on, ten readings.
    dev.output_on()
    assert first_reading(dev, lambda r: r.output_on, 5.0) is not None
    got = [dev.read() for _ in range(10)]
    observe("readings", [(r.voltage, r.current, r.power, r.working_time) for r in got])
    for r in got:
        assert (r.set_voltage, r.set_current) == (5.0, 0.1)
        assert abs(r.voltage - 5.0) <= 0.05 * 5.0, r.voltage
        assert abs(r.current - 0.05) <= 0.05 * 0.05, r.current
        assert abs(r.power - 0.25) <= 0.05 * 0.25, r.power
    stamps = [r.timestamp for r in got]
    assert all(b > a for a, b in zip(stamps, stamps[1:], strict=False))
    times = [r.working_time for r in got]
    assert all(b >= a for a, b in zip(times, times[1:], strict=False))
    # One per second: the rise over the ten readings matches their time span within 1 s.
    assert abs((times[-1] - times[0]) - (stamps[-1] - stamps[0])) <= 1.0


# ST-015


@pytest.mark.hil
@pytest.mark.spec("ST-015")
def test_st015_regulation_modes_with_load_a(
    hil_unit: Unit, load_a: str, person: Person, controls: Person, supply: Guard
) -> None:
    """Off, then CV at 5 V and 0.1 A, then CC at 5 V and 0.02 A, with Load A."""
    selected = person.ask("Is CC (not OCP) selected on the supply's front panel?")
    assert selected, "select CC (not OCP) on the front panel before this test"
    dev = supply.connect()
    off = dev.read()
    assert not off.output_on
    assert off.mode is Mode.OFF
    assert off.mode_text == "off"
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    dev.output_on()
    cv = settled_reading(dev, 1.0)
    assert cv.output_on
    assert cv.mode is Mode.CV
    assert cv.mode_text == "CV"
    dev.set_current_limit(0.02)
    cc = settled_reading(dev, 1.0)
    assert cc.output_on
    assert cc.mode is Mode.CC
    assert cc.mode_text == "CC"


@pytest.mark.spec("ST-015")
@pytest.mark.parametrize(
    ("out_state", "mode", "text"),
    [(3, Mode.HELD_ABOVE, "held above setpoint"), (9, Mode.UNKNOWN, "unknown (9)")],
)
def test_st015_mock_out_state_3_and_9(
    mock_device: Factory, out_state: int, mode: Mode, text: str
) -> None:
    """The mock part: `outState` 3 and 9."""
    s = script(replies=[reply(0xC2, c3_with_out_state(out_state), after_s=0.01)])
    dev = mock_device([s], identifier=f"ST-015-out-state-{out_state}")
    r = dev.read()
    assert r.mode is mode
    assert r.mode_raw == out_state
    assert r.mode_text == text


# ST-016


def _dropped(dev: Mp305) -> int:
    """The dropped-frame counter of the link."""
    counters = dev.counters
    return 0 if counters is None else counters.dropped_frames


@pytest.mark.spec("ST-016")
def test_st016_a_short_c3_is_dropped(mock_device: Factory, frame_log: FrameLog) -> None:
    """A `0xC3` two bytes short."""
    short = C3_CAPTURE[:-2]
    s = script(
        replies=[
            reply(0xC2, C3_CAPTURE, after_s=0.01, repeat=1),
            reply(0xC2, short, after_s=0.01, repeat=1),
            reply(0xC2, C3_CAPTURE, after_s=0.01),
        ]
    )
    dev = mock_device([s], identifier="ST-016-short")
    got = _collect(dev, 2.0)
    frame_log.settle()
    assert _dropped(dev) == 1
    assert any(
        m.startswith("dropped 0xc3: ") for m in frame_log.texts("mp305.core.link", logging.WARNING)
    )
    assert got
    assert all(r.raw == C3_CAPTURE for r in got)


@pytest.mark.spec("ST-016")
def test_st016_an_af01_notification_without_0x31_is_dropped(
    mock_device: Factory, frame_log: FrameLog
) -> None:
    """An `AF01` notification that does not start with `0x31`."""
    marked = testing.c3(set_voltage=1234)
    bad = bytes([0x32, 0xC3]) + marked
    s = script(injections=[{"at_s": 0.4, "delivery": bad, "route": "af01"}])
    dev = mock_device([s], identifier="ST-016-af01")
    got = _collect(dev, 1.5)
    frame_log.settle()
    assert _dropped(dev) == 1
    assert any(
        m.startswith("rx ble AF01 ") and " error: " in m
        for m in frame_log.texts("mp305.core.frames", logging.WARNING)
    )
    assert got
    assert all(r.raw != marked for r in got)


@pytest.mark.spec("ST-016")
def test_st016_a_usb_frame_with_a_wrong_checksum_is_dropped(
    mock_device: Factory, frame_log: FrameLog
) -> None:
    """A USB frame with a wrong checksum."""
    marked = testing.c3(set_voltage=1234)
    good = testing.hid_stream(0xC3, marked)
    assert good[-1] != 0xAA and good[-2] != 0xAA
    bad = good[:-1] + bytes([(good[-1] + 1) & 0xFF])
    assert bad[-1] != 0xAA
    s = script("hid", injections=[{"at_s": 0.4, "delivery": bad}])
    dev = mock_device([s], identifier="ST-016-hid")
    got = _collect(dev, 1.5)
    frame_log.settle()
    assert _dropped(dev) == 1
    assert any(
        m.startswith("rx hid ") and " error: " in m
        for m in frame_log.texts("mp305.core.frames", logging.WARNING)
    )
    assert got
    assert all(r.raw != marked for r in got)


# ST-017 step 2 (step 1 is in test_wire_checks.py)


@pytest.mark.spec("ST-017")
def test_st017_a_c5_then_the_c3_while_a_c2_is_in_flight(
    mock_device: Factory, frame_log: FrameLog
) -> None:
    """The `0xC5` is a settings event and the `0xC3` completes the read."""
    marked = testing.c3(set_voltage=1234)
    both: dict[str, Any] = {
        "request": 0xC2,
        "after_s": 0.01,
        "deliveries": [testing.ble_frame(0xC5, C5_SETTINGS), testing.ble_frame(0xC3, marked)],
        "repeat": 1,
        "from_s": 0.4,
    }
    s = script(replies=[reply(0xC2, C3_CAPTURE, after_s=0.01), both])
    dev = mock_device([s], identifier="ST-017-c5")
    seen = first_reading(dev, lambda r: r.raw == marked, 3.0)
    assert seen is not None, "the 0xC3 after the 0xC5 did not complete the read"
    # The poll goes on at once: the read was not left to time out.
    following = dev.read(timeout=0.5)
    assert following.wall_ns > seen.wall_ns
    events = [e for e in dev.events() if e.kind is EventKind.SETTINGS_CHANGED]
    expected = Settings(
        charge_limit=C5_SETTINGS[0],
        volume=C5_SETTINGS[1],
        screen_off=C5_SETTINGS[2],
        shutdown=C5_SETTINGS[3],
        screen_direction=C5_SETTINGS[4],
        ramp_step=int.from_bytes(C5_SETTINGS[5:7], "little"),
        ocp_delay=int.from_bytes(C5_SETTINGS[7:9], "little"),
        usb_line_drop=int.from_bytes(C5_SETTINGS[9:11], "little"),
    )
    assert [e.settings for e in events] == [expected]
    counters = dev.counters
    assert counters is not None
    assert (counters.dropped_frames, counters.ignored, counters.late_replies) == (0, 0, 0)


@pytest.mark.spec("ST-017")
def test_st017_a_c9_with_no_request_in_flight_is_reported(
    mock_device: Factory, frame_log: FrameLog
) -> None:
    """A stray `0xC9`: counted as a late reply and reported at WARNING.

    The library has no `Event` kind for it (DD-PY-021); the core reports it
    through the `late_replies` counter and its WARNING records.
    """
    s = script(injections=[{"at_s": 0.4, "delivery": testing.ble_frame(0xC9, b"\x00")}])
    dev = mock_device([s], identifier="ST-017-stray")

    def late() -> int:
        counters = dev.counters
        return 0 if counters is None else counters.late_replies

    assert wait_until(lambda: late() >= 1, 3.0)
    frame_log.settle()
    assert late() == 1
    warnings = frame_log.texts("mp305.core", logging.WARNING)
    assert any(m.startswith("late reply 0xc9") for m in warnings), warnings


@pytest.mark.spec("ST-017")
def test_st017_a_late_c9_is_not_the_reply_to_the_next_c8(mock_device: Factory) -> None:
    """A `0xC9` after a `0xC8` timed out, then a new `0xC8`."""
    s = script(
        replies=[
            reply(0xC8, b"\x00", repeat=1),  # the remote-control request is granted
            reply(0xC8, b"\x00", after_s=1.3, repeat=1),  # late: after the 1 s timeout
            reply(0xC8, b"\x07"),  # the reply to the new 0xC8
        ]
    )
    dev = mock_device([s], identifier="ST-017-late")
    with pytest.raises(Mp305TimeoutError):
        dev.set_voltage(1.0)

    def late() -> int:
        counters = dev.counters
        return 0 if counters is None else counters.late_replies

    assert wait_until(lambda: late() >= 1, 3.0), "the late 0xC9 did not arrive"
    with pytest.raises(CommandRejectedError) as info:
        dev.set_voltage(1.5)
    assert info.value.status == 7


# ST-033


@pytest.mark.hil
@pytest.mark.spec("ST-033")
def test_st033_a_reading_is_typed_and_immutable(hil_unit: Unit, supply: Guard) -> None:
    """Read a reading, inspect it, try to change a field."""
    dev = supply.connect()
    before = time.time()
    r = dev.read()
    after = time.time()
    for name, kind in SR_033.items():
        assert isinstance(getattr(r, name), kind), name
    assert all(isinstance(f, Fault) for f in r.faults)
    # Units: seconds since the epoch, V, A, W, Wh, s, degrees Celsius.
    assert before - 0.5 <= r.timestamp <= after + 0.5
    for value in (r.voltage, r.current, r.power, r.energy):
        assert math.isfinite(value)
        assert value >= 0.0
    assert 0.0 <= r.set_voltage <= 30.5
    assert 0.0 <= r.set_current <= 5.1
    assert r.working_time >= 0
    assert -128 <= r.temperature <= 127
    for name in SR_033:
        with pytest.raises(dataclasses.FrozenInstanceError):
            setattr(r, name, getattr(r, name))
