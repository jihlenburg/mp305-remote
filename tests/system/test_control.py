"""ST-018 to ST-025, ST-046, ST-048, ST-049: control commands and remote control.

SR-018 to SR-025, SR-051, SR-053 and SR-054. Over Bluetooth the first control
call of a connection opens the supply's "Allow Remote Control" prompt, so
every HIL test here needs a person there (the `controls` fixture). Nothing is
connected to the output unless the entry names Load A; setpoints stay at
5 V and 0.1 A or less, and the `supply` fixture switches the output off and
restores the setpoints in teardown.
"""

from __future__ import annotations

import contextlib
import logging
import math
import threading
import time
from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

import mp305
from mp305 import (
    CommandRejectedError,
    Event,
    LinkLostError,
    LiveMode,
    ModeError,
    Mp305,
    Mp305Error,
    Mp305TimeoutError,
    RemoteControlDeniedError,
    RemoteControlLostError,
    SetpointRangeError,
    testing,
)
from tests.system.support import (
    ALLOW_TEXT,
    Frame,
    FrameLog,
    control,
    first_reading,
    reply,
    script,
    silent,
    telemetry,
    wait_until,
)

if TYPE_CHECKING:
    from tests.system.conftest import Guard, Person, Unit

Factory = Callable[..., Mp305]


def _after(frames: list[Frame], index: int) -> list[Frame]:
    """The frames logged after record `index`."""
    return [f for f in frames if f.index > index]


# ST-018


@pytest.mark.hil
@pytest.mark.spec("ST-018")
def test_st018_the_first_command_requests_remote_control(
    hil_unit: Unit,
    controls: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Connect, then set 1.00 V with the frame log on; over Bluetooth the person allows.

    Over Bluetooth the person waits 3 s before pressing allow, so that "no
    reply until the person presses allow" shows as a reply at least 2 s
    after the request; a reply within 1 s would be the supply's own. The
    result is recorded for TBD-012.
    """
    prompted: list[float] = []

    def on_prompt(event: Event) -> None:
        if event.prompt == "allow_remote_control":
            prompted.append(time.time())
            controls.say("The supply asks to allow remote control. Do not press yet; wait 3 s.")
            controls.countdown(3, "Press ALLOW now.")
        else:
            supply.default_prompt(event)

    dev = supply.connect(on_prompt=on_prompt)
    start = frame_log.mark()
    dev.set_voltage(1.0)
    frame_log.settle()
    commands = frame_log.sent(0xC8, start)
    assert len(commands) >= 2
    request = commands[0]
    assert control(request.payload).remote_con == 2
    replies = _after(frame_log.received(0xC9, start), request.index)
    assert replies
    grant = replies[0]
    observe("reply_ms", grant.offset_ms - request.offset_ms)
    observe("status", grant.payload.hex())
    assert grant.payload == b"\x00"
    if hil_unit.transport == "hid":
        assert grant.offset_ms - request.offset_ms <= 1000
    else:
        assert prompted
        assert grant.created - request.created >= 2.0
        assert grant.created > prompted[0]
    command = commands[1]
    assert command.index > grant.index
    assert control(command.payload).remote_con == 1
    assert control(command.payload).set_voltage == 100


# ST-019


@pytest.mark.hil
@pytest.mark.spec("ST-019")
def test_st019_a_command_copies_the_front_panel_change(
    hil_unit: Unit, person: Person, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Steps 1 to 3: 3 V, 0.05 A, output off; 4 V on the front panel; 0.08 A within 2 s."""
    dev = supply.connect()
    # Step 1.
    dev.set_voltage(3.0)
    dev.set_current_limit(0.05)
    dev.output_off()
    # Step 2.
    person.say("On the supply's front panel, change the voltage to 4.00 V now.")

    def four_volts() -> bool:
        r = dev.reading
        return r is not None and r.set_voltage == 4.0

    assert wait_until(four_volts, 180.0, step=0.05), "4.00 V not seen within 180 s"
    seen = time.monotonic()
    # Step 3: within 2 s.
    start = frame_log.mark()
    dev.set_current_limit(0.08)
    assert time.monotonic() - seen <= 2.0
    frame_log.settle()
    command = frame_log.sent(0xC8, start)[-1]
    readings = [f for f in frame_log.received(0xC3) if f.index < command.index]
    c = control(command.payload)
    t = telemetry(readings[-1].payload)
    assert (c.set_voltage, c.set_current, c.output) == (400, 80, 0)
    assert (c.real_change, c.voltage_slow, c.current_over) == (
        t.real_change,
        t.voltage_slow,
        t.current_over,
    )
    assert (c.model, c.refresh, c.remote_con) == (t.model, 0, 1)


# ST-020


@pytest.mark.hil
@pytest.mark.spec("ST-020")
def test_st020_the_output_stays_off_through_20_changes(
    hil_unit: Unit, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Voltage, current and a reading, 20 times, with the output off."""
    dev = supply.connect()
    first = dev.reading
    assert first is not None
    assert not first.output_on
    start = frame_log.mark()
    for i in range(20):
        dev.set_voltage(round(1.0 + 0.2 * i, 2))
        dev.set_current_limit(round(0.01 + 0.004 * i, 3))
        assert not dev.read().output_on
    frame_log.settle()
    commands = frame_log.sent(0xC8, start)
    assert len(commands) >= 40
    assert [f for f in commands if control(f.payload).output == 1] == []
    assert not dev.read().output_on


# ST-021


@pytest.mark.hil
@pytest.mark.spec("ST-021")
def test_st021_no_command_outside_dc_mode(
    hil_unit: Unit, person: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Program or PD mode on the front panel, output off; connect; `set_voltage(1.0)`."""
    person.wait_enter(
        "Put the supply in program or PD mode on its front panel, with the output off."
    )
    dev = supply.connect()
    supply.restore_by_person(
        "Switch the supply back to DC mode on its front panel.",
        verify=lambda: dev.read(timeout=3.0).live_mode is LiveMode.DC,
    )
    reading = dev.reading
    assert reading is not None
    assert reading.live_mode in (LiveMode.PROGRAM, LiveMode.PD)
    assert not reading.output_on
    start = frame_log.mark()
    with pytest.raises(ModeError):
        dev.set_voltage(1.0)
    frame_log.settle()
    assert frame_log.sent(0xC8, start) == []


# ST-022


def _queue_changes(dev: Mp305, outcomes: dict[float, object]) -> list[threading.Thread]:
    """Starts the five voltage changes of step 2, each on its own thread."""

    def change(volts: float) -> None:
        try:
            dev.set_voltage(volts)
            outcomes[volts] = "sent"
        except Mp305Error as error:
            outcomes[volts] = error

    threads = [
        threading.Thread(target=change, args=(v,), name=f"ST-022 {v} V")
        for v in (1.0, 1.5, 2.0, 2.5, 3.0)
    ]
    for thread in threads:
        thread.start()
    return threads


@pytest.mark.hil
@pytest.mark.spec("ST-022")
def test_st022_output_off_goes_first_and_is_acknowledged_within_0_5_s(
    hil_unit: Unit,
    load_a: str,
    controls: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Steps 1 to 3 with Load A.

    The changes are queued right after the output-on was acknowledged: for
    100 ms after a `0xC9` no command may be built (SR-019), so all five are
    still queued when the output-off arrives, as "at once" asks.
    """
    dev = supply.connect()
    # Step 1.
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    start = frame_log.mark()
    dev.output_on()
    # Step 2.
    outcomes: dict[float, object] = {}
    threads = _queue_changes(dev, outcomes)
    called_wall = time.time()
    called = time.monotonic()
    dev.output_off()
    returned = time.monotonic()
    for thread in threads:
        thread.join(5.0)
    # Step 3.
    off_reading = first_reading(dev, lambda r: not r.output_on, 5.0)
    off_seen = time.monotonic()
    frame_log.settle()
    commands = frame_log.sent(0xC8, start)
    on_command = commands[0]
    assert control(on_command.payload).output == 1
    after_on = commands[1:]
    off = after_on[0]
    ack = _after(frame_log.received(0xC9, start), off.index)[0]
    observe("call_to_ack_s", round(ack.created - called_wall, 3))
    observe("call_returned_s", round(returned - called, 3))
    observe("call_to_reading_off_s", round(off_seen - called, 3))
    observe("queued_outcomes", {str(k): str(v) for k, v in outcomes.items()})
    assert control(off.payload).output == 0
    assert ack.payload == b"\x00"
    assert ack.created - called_wall <= 0.5
    assert off_reading is not None
    assert not off_reading.output_on
    assert off_reading.voltage < 0.5


@pytest.mark.hil
@pytest.mark.spec("ST-022")
def test_st022_step4_output_off_after_remote_control_was_released(
    ble_unit: Unit,
    load_a: str,
    person: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Step 4: steps 1 to 3 again after a link loss and a reconnect (ST-028), over Bluetooth.

    The link loss is Bluetooth switched off on the host: switching the supply
    off would also switch its output off.
    """
    dev = supply.connect()
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    dev.output_on()
    assert first_reading(dev, lambda r: r.output_on, 5.0) is not None
    supply.restore_by_person("Make sure Bluetooth is on on this computer.")
    person.say("Switch Bluetooth OFF on this computer now (the output stays on with Load A).")
    assert wait_until(lambda: dev.link_state == "lost", 60.0, step=0.2), "no link loss seen"
    # The lost session holds its place in the registry until closed (AR-030);
    # the close of a lost link reports the loss (DD-PY-043).
    with contextlib.suppress(LinkLostError):
        dev.close()
    person.wait_enter("Switch Bluetooth ON again on this computer.")
    again = supply.connect_when_back()
    reading = again.reading
    assert reading is not None
    assert reading.output_on, "the supply did not keep the output on after the link loss"
    assert again.remote_state == "none"
    start = frame_log.mark()
    outcomes: dict[float, object] = {}
    threads = _queue_changes(again, outcomes)
    again.output_off()
    for thread in threads:
        thread.join(80.0)
    off_reading = first_reading(again, lambda r: not r.output_on, 5.0)
    frame_log.settle()
    commands = frame_log.sent(0xC8, start)
    request = commands[0]
    assert control(request.payload).remote_con == 2
    grant = [f for f in _after(frame_log.received(0xC9, start), request.index)][0]
    assert grant.payload == b"\x00"
    off = _after(commands, grant.index)[0]
    ack = _after(frame_log.received(0xC9, start), off.index)[0]
    observe("grant_to_ack_s", round(ack.created - grant.created, 3))
    assert ALLOW_TEXT in frame_log.texts("mp305.core.session", logging.WARNING)
    assert control(off.payload).output == 0
    assert ack.payload == b"\x00"
    assert ack.created - grant.created <= 0.5
    assert off_reading is not None
    assert off_reading.voltage < 0.5


# ST-023


@pytest.mark.hil
@pytest.mark.spec("ST-023")
def test_st023_step1_a_normal_command_is_accepted(
    hil_unit: Unit, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Step 1: a normal command."""
    dev = supply.connect()
    start = frame_log.mark()
    dev.set_voltage(1.0)
    frame_log.settle()
    command = frame_log.sent(0xC8, start)[-1]
    assert control(command.payload).set_voltage == 100
    assert _after(frame_log.received(0xC9, start), command.index)[0].payload == b"\x00"


@pytest.mark.hil
@pytest.mark.spec("ST-023")
def test_st023_step2_remote_control_taken_away_on_the_front_panel(
    hil_unit: Unit,
    person: Person,
    controls: Person,
    supply: Guard,
    observe: Callable[[str, object], None],
) -> None:
    """Step 2: remote control taken away on the front panel, if the supply allows it (TBD-012)."""
    dev = supply.connect()
    dev.set_voltage(1.0)
    possible = person.ask(
        "The test holds remote control now. Does the supply let you take it away on its front "
        "panel? If it does, do it now and answer y; if not, answer n."
    )
    observe("front_panel_can_take_remote_control", possible)
    if not possible:
        pytest.skip("the supply offers no way to take remote control away (recorded for TBD-012)")
    with pytest.raises(RemoteControlLostError):
        dev.set_voltage(1.5)


@pytest.mark.spec("ST-023")
def test_st023_step3_no_reply_is_a_timeout_after_1_s(mock_device: Factory) -> None:
    """Step 3 on the mock: no reply."""
    s = script(
        replies=[reply(0xC8, b"\x00", repeat=1), silent(0xC8, repeat=1), reply(0xC8, b"\x00")]
    )
    dev = mock_device([s], identifier="ST-023-timeout")
    dev.request_remote_control()
    start = time.monotonic()
    with pytest.raises(Mp305TimeoutError) as info:
        dev.set_voltage(1.0)
    took = time.monotonic() - start
    assert "within 1.0 s" in str(info.value)
    assert took >= 1.0


@pytest.mark.spec("ST-023")
def test_st023_step3_ff_after_a_blocked_setpoint_is_rejected_with_a_reason(
    mock_device: Factory,
) -> None:
    """Step 3 on the mock: a setpoint above the range is blocked, then `0xFF`.

    The setpoint above the range never reaches the transport (the library
    refuses it first, SR-024); the next command is answered `0xFF`.
    """
    record = testing.MockRecord()
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\xff", repeat=1)])
    dev = mock_device([s], identifier="ST-023-ff", record=record)
    with pytest.raises(SetpointRangeError):
        dev.set_voltage(30.01)
    assert [f for f in record.sent() if f.opcode == 0xC8] == []
    with pytest.raises(CommandRejectedError) as info:
        dev.set_voltage(1.0)
    assert info.value.status == 0xFF
    assert info.value.reason in ("mode", "range", "fault", "busy")
    assert info.value.reason in str(info.value)


@pytest.mark.spec("ST-023")
def test_st023_step3_a_reply_of_7_is_rejected_naming_7(mock_device: Factory) -> None:
    """Step 3 on the mock: a reply of 7."""
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\x07")])
    dev = mock_device([s], identifier="ST-023-seven")
    with pytest.raises(CommandRejectedError) as info:
        dev.set_voltage(1.0)
    assert info.value.status == 7
    assert "7" in str(info.value)


# ST-024


@pytest.mark.hil
@pytest.mark.spec("ST-024")
def test_st024_invalid_setpoints_send_nothing_and_valid_ones_are_rounded(
    hil_unit: Unit, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """NaN, infinity, -0.01, 30.01 and 4.5 under a 4 V user limit; then 1.004 and 1.006."""
    dev = supply.connect(max_voltage=4.0)
    start = frame_log.mark()
    for volts in (math.nan, math.inf, -0.01, 30.01, 4.5):
        with pytest.raises(SetpointRangeError):
            dev.set_voltage(volts)
    frame_log.settle()
    assert frame_log.sent(0xC8, start) == []
    dev.set_voltage(1.004)
    dev.set_voltage(1.006)
    frame_log.settle()
    commands = [control(f.payload) for f in frame_log.sent(0xC8, start)]
    assert [c.set_voltage for c in commands if c.remote_con == 1] == [100, 101]


@pytest.mark.spec("ST-025")
def test_st025_the_range_and_a_current_above_it(mock_device: Factory) -> None:
    """The range the library reports; `set_current_limit(5.001)`."""
    assert mp305.VOLTAGE_RANGE == (0.0, 30.0)
    assert mp305.CURRENT_RANGE == (0.0, 5.0)
    record = testing.MockRecord()
    dev = mock_device([script()], identifier="ST-025", record=record)
    with pytest.raises(SetpointRangeError):
        dev.set_current_limit(5.001)
    assert [f for f in record.sent() if f.opcode == 0xC8] == []


# ST-046


@pytest.mark.hil
@pytest.mark.spec("ST-046")
def test_st046_usb_sends_a_frame_every_2_s_and_keeps_the_grant(
    hid_unit: Unit, supply: Guard, frame_log: FrameLog, observe: Callable[[str, object], None]
) -> None:
    """Over USB: remote control, 20 s of readings, then `set_voltage(1.0)`."""
    dev = supply.connect()
    start = frame_log.mark()
    dev.request_remote_control()
    end = time.monotonic() + 20.0
    for _ in dev.readings():
        if time.monotonic() >= end:
            break
    dev.set_voltage(1.0)
    frame_log.settle()
    sent = frame_log.sent(start=start)
    gaps = [b.offset_ms - a.offset_ms for a, b in zip(sent, sent[1:], strict=False)]
    observe("longest_gap_ms", max(gaps))
    assert max(gaps) <= 2000
    command = frame_log.sent(0xC8, start)[-1]
    assert control(command.payload).remote_con == 1
    assert control(command.payload).set_voltage == 100
    assert _after(frame_log.received(0xC9, start), command.index)[0].payload == b"\x00"


# ST-048


@pytest.mark.hil
@pytest.mark.spec("ST-048")
def test_st048_run1_a_denied_remote_control_request(
    ble_unit: Unit, person: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Run 1: the person presses deny."""

    def on_prompt(event: Event) -> None:
        if event.prompt == "allow_remote_control":
            person.say("The supply asks to allow remote control: press DENY now.")
        else:
            supply.default_prompt(event)

    dev = supply.connect(on_prompt=on_prompt)
    start = frame_log.mark()
    with pytest.raises(RemoteControlDeniedError):
        dev.set_voltage(1.0)
    frame_log.settle()
    request = frame_log.sent(0xC8, start)[0]
    assert control(request.payload).remote_con == 2
    replies = _after(frame_log.received(0xC9, start), request.index)
    assert [f.payload for f in replies][:1] == [b"\x01"]
    assert ALLOW_TEXT in frame_log.texts("mp305.core.session", logging.WARNING)


@pytest.mark.hil
@pytest.mark.spec("ST-048")
def test_st048_run2_no_answer_is_a_denial_within_70_s(
    ble_unit: Unit,
    person: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Run 2: nobody presses anything."""

    def on_prompt(event: Event) -> None:
        if event.prompt == "allow_remote_control":
            person.say(
                "The supply asks to allow remote control: do NOT press anything (about 60 s)."
            )
        else:
            supply.default_prompt(event)

    dev = supply.connect(on_prompt=on_prompt)
    start = frame_log.mark()
    with pytest.raises(RemoteControlDeniedError):
        dev.set_voltage(1.0)
    raised = time.time()
    frame_log.settle()
    request = frame_log.sent(0xC8, start)[0]
    assert control(request.payload).remote_con == 2
    replies = _after(frame_log.received(0xC9, start), request.index)
    # Decided by the supply's `C9 01`, or by the library's own 70 s bound,
    # which reaches Python within one wait slice.
    decided = replies[0].created if replies else raised - mp305._native.WAIT_SLICE_S
    observe("seconds_to_denial", round(decided - request.created, 3))
    observe("supply_replied", [f.payload.hex() for f in replies])
    assert decided - request.created <= 70.0
    assert ALLOW_TEXT in frame_log.texts("mp305.core.session", logging.WARNING)


@pytest.mark.hil
@pytest.mark.spec("ST-048")
def test_st048_run3_nothing_is_sent_while_the_request_is_pending(
    ble_unit: Unit, person: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Run 3: the person presses allow after 10 s while a second control call is queued."""
    prompted = threading.Event()

    def on_prompt(event: Event) -> None:
        if event.prompt == "allow_remote_control":
            prompted.set()
            person.say("The supply asks to allow remote control. Do not press yet; wait 10 s.")
            person.countdown(10, "Press ALLOW now.")
        else:
            supply.default_prompt(event)

    dev = supply.connect(on_prompt=on_prompt)
    start = frame_log.mark()
    second: dict[str, object] = {}

    def queue_second() -> None:
        if prompted.wait(80.0):
            try:
                dev.set_current_limit(0.05)
                second["outcome"] = "sent"
            except Mp305Error as error:
                second["outcome"] = error

    thread = threading.Thread(target=queue_second, name="ST-048 second call")
    thread.start()
    dev.set_voltage(1.0)
    thread.join(90.0)
    frame_log.settle()
    assert second == {"outcome": "sent"}
    commands = frame_log.sent(0xC8, start)
    request = commands[0]
    assert control(request.payload).remote_con == 2
    grant = [f for f in _after(frame_log.received(0xC9, start), request.index)][0]
    assert grant.payload == b"\x00"
    assert [f for f in commands if request.index < f.index < grant.index] == []
    later = [control(f.payload) for f in _after(commands, grant.index)]
    assert [(c.remote_con, c.set_current) for c in later if c.set_current == 50] == [(1, 50)]
    assert ALLOW_TEXT in frame_log.texts("mp305.core.session", logging.WARNING)


# ST-049


@pytest.mark.hil
@pytest.mark.spec("ST-049")
def test_st049_no_release_outside_dc_mode(
    hil_unit: Unit, person: Person, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Remote control, PD mode on the front panel, then close."""
    dev = supply.connect()
    dev.request_remote_control()
    supply.restore_by_person(
        "Switch the supply back to DC mode on its front panel.",
        verify=lambda: (r := supply.peek()) is not None and r.live_mode is LiveMode.DC,
    )
    person.say("Put the supply in PD mode on its front panel now (output off).")

    def pd() -> bool:
        r = dev.reading
        return r is not None and r.live_mode is LiveMode.PD

    assert wait_until(pd, 180.0, step=0.2), "PD mode not seen within 180 s"
    changed = [f for f in frame_log.received(0xC3) if telemetry(f.payload).model == 2][0]
    dev.close()
    frame_log.settle()
    releases = [
        f for f in _after(frame_log.sent(0xC8), changed.index) if control(f.payload).remote_con == 0
    ]
    assert releases == []
    warnings = frame_log.texts("mp305.core.session", logging.WARNING)
    assert any("not in DC mode" in m for m in warnings), warnings
