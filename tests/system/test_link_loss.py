"""ST-028, ST-029, ST-041, ST-050: link loss, closing, unclean exit and reconnection.

SR-028, SR-029, SR-046 and SR-055. The person breaks the link (supply off,
Bluetooth off on the host, USB cable pulled) when the test says so and undoes
it in teardown. Nothing is connected to the output; where an entry switches
it on, it is at 5.00 V and 0.100 A, and the `supply` fixture switches it off
again, reconnecting when the entry's own link is gone.
"""

from __future__ import annotations

import time
from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

import mp305
from mp305 import EventKind, LinkLostError, Reading
from tests.system.support import (
    AFTER_LOSS,
    UNCLEAN_PREFIX,
    ChildLines,
    FrameLog,
    control,
    first_reading,
    start_child,
    wait_until,
)

if TYPE_CHECKING:
    from tests.system.conftest import Guard, Person, Unit

BREAK = {
    "supply": "Switch the supply OFF now with its power button.",
    "bluetooth": "Switch Bluetooth OFF on this computer now.",
    "cable": "Pull the supply's USB cable now.",
}
"""How the person breaks the link, per cause of ST-028."""

MEND = {
    "supply": "Switch the supply on again, with remote control enabled.",
    "bluetooth": "Switch Bluetooth on again on this computer.",
    "cable": "Plug the supply's USB cable in again.",
}
"""How the person mends it again."""


def _reachable(unit: Unit) -> bool:
    """Whether discovery sees the unit again (after the person mended the link)."""
    bluetooth = unit.transport == "ble"
    found = mp305.discover(5.0 if bluetooth else 1.0, bluetooth=bluetooth, usb=not bluetooth)
    return any(f.identifier == unit.identifier for f in found)


# ST-028


@pytest.mark.hil
@pytest.mark.spec("ST-028")
@pytest.mark.parametrize("cause", ["supply", "bluetooth", "cable"])
def test_st028_a_lost_link_is_reported_within_4_s(
    hil_unit: Unit,
    person: Person,
    supply: Guard,
    frame_log: FrameLog,
    cause: str,
    observe: Callable[[str, object], None],
) -> None:
    """Steps 1 to 3: streaming with the output off; the supply off, Bluetooth off, the cable out."""
    if cause == "bluetooth" and hil_unit.transport != "ble":
        pytest.skip("switching Bluetooth off on the host breaks only a Bluetooth link")
    if cause == "cable" and hil_unit.transport != "hid":
        pytest.skip("pulling the USB cable breaks only a USB link")
    # Step 1: streaming, output off.
    dev = supply.connect()
    reading = dev.reading
    assert reading is not None
    assert not reading.output_on
    supply.restore_by_person(MEND[cause], verify=lambda: _reachable(hil_unit))
    readings = dev.readings()
    got: list[Reading] = [next(readings) for _ in range(3)]
    # Step 2 or 3: break the link.
    person.say(BREAK[cause])
    with pytest.raises(LinkLostError) as info:
        for r in readings:
            got.append(r)
    raised = time.time()
    # Nothing is sent afterwards and there is no reconnection, also after the
    # 5 s a reconnection would wait.
    time.sleep(6.0)
    frame_log.settle()
    last_reply = [f for f in frame_log.received() if f.created < raised][-1]
    after = [f for f in frame_log.sent() if f.created > raised]
    events = [e.kind for e in dev.events()]
    observe(f"{cause}_reported_after_last_reply_s", round(raised - last_reply.created, 3))
    observe(f"{cause}_text", str(info.value))
    assert raised - last_reply.created <= 4.0
    assert AFTER_LOSS in str(info.value)
    assert after == []
    assert dev.link_state == "lost"
    assert EventKind.RECONNECTED not in events


# ST-029


@pytest.mark.hil
@pytest.mark.spec("ST-029")
@pytest.mark.parametrize("ending", ["raises", "normal"])
def test_st029_a_with_block_ends_with_output_off_then_release(
    hil_unit: Unit, controls: Person, supply: Guard, frame_log: FrameLog, ending: str
) -> None:
    """Case 1: a `with` block switches the output on (no load), then raises. Case 2: normal end."""
    dev = supply.connect()
    error = RuntimeError("raised in the with block (ST-029 case 1)")
    start = frame_log.mark()
    if ending == "raises":
        with pytest.raises(RuntimeError) as info:
            with dev:
                dev.set_voltage(5.0)
                dev.set_current_limit(0.1)
                dev.output_on()
                assert first_reading(dev, lambda r: r.output_on, 5.0) is not None
                raise error
        assert info.value is error
    else:
        with dev:
            dev.set_voltage(5.0)
            dev.set_current_limit(0.1)
            dev.output_on()
            assert first_reading(dev, lambda r: r.output_on, 5.0) is not None
    frame_log.settle()
    sent = frame_log.sent(start=start)
    commands = [f for f in sent if f.opcode == 0xC8]
    off, release = (control(f.payload) for f in commands[-2:])
    assert (off.remote_con, off.output) == (1, 0)
    assert (release.remote_con, release.output) == (0, 0)
    assert {f.opcode for f in sent if f.index > commands[-1].index} <= {0xC2}
    assert dev.closed


# ST-041

ST041_CHILD = """
def on_prompt(event):
    print("PROMPT " + event.prompt, flush=True)

dev = Mp305.connect(
    os.environ["MP305_ST041_DEVICE"], on_prompt=on_prompt, max_voltage=5.0, max_current=0.1
)
dev.set_voltage(5.0)
dev.set_current_limit(0.1)
dev.output_on()
deadline = time.monotonic() + 10.0
while time.monotonic() < deadline and not dev.read().output_on:
    pass
# The marker is refreshed about once per second while the output is on (SR-046).
time.sleep(2.5)
print("ON", flush=True)
time.sleep(600.0)
"""
"""Steps 1 and 2: connect, 5.00 V, 0.100 A, nothing connected, output on; then wait for SIGKILL."""


@pytest.mark.hil
@pytest.mark.spec("ST-041")
def test_st041_an_unclean_exit_is_reported_at_the_next_connect(
    hil_unit: Unit,
    controls: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Steps 1 to 3, then a control run with an orderly close."""
    # The setpoints the teardown restores, before the child changes them.
    supply.peek()
    # Steps 1 and 2 in a child process, ended with SIGKILL.
    supply.mark_energized()
    proc = start_child(ST041_CHILD, env={"MP305_ST041_DEVICE": hil_unit.identifier})
    lines = ChildLines(proc)
    deadline = time.monotonic() + 180.0
    try:
        while True:
            line = lines.get(deadline - time.monotonic())
            if line is None:
                break
            if line.startswith("PROMPT "):
                controls.say("The supply asks for a confirmation: press ALLOW now.")
            if line == "ON":
                break
    finally:
        proc.kill()
        proc.wait(10.0)
    assert "ON" in lines.seen, (lines.seen, proc.stderr.read() if proc.stderr else "")
    # Step 3: reconnect and read the marker state.
    start = frame_log.mark()
    dev = supply.connect_when_back()
    warning = dev.unclean_exit_warning
    sent_before = frame_log.sent(0xC8, start)
    kinds = [e.kind for e in dev.events()]
    observe("warning", warning)
    assert warning is not None
    assert warning.startswith(UNCLEAN_PREFIX)
    assert EventKind.UNCLEAN_EXIT_WARNING in kinds
    assert sent_before == []
    dev.output_off()
    dev.close()
    # The control run: output on, then an orderly close; no marker remains.
    dev = supply.connect()
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    dev.output_on()
    assert first_reading(dev, lambda r: r.output_on, 5.0) is not None
    time.sleep(2.5)
    dev.close()
    dev = supply.connect()
    assert dev.unclean_exit_warning is None
    dev.close()


# ST-050


def _event_times(dev: mp305.Mp305, kinds: dict[EventKind, float]) -> None:
    """Notes the first arrival time of every event kind not yet seen."""
    for event in dev.events():
        kinds.setdefault(event.kind, time.time())


@pytest.mark.hil
@pytest.mark.spec("ST-050")
@pytest.mark.parametrize("step", ["1 bluetooth", "2 usb"])
def test_st050_steps_1_and_2_reconnection_after_the_link_is_back(
    hil_unit: Unit,
    person: Person,
    supply: Guard,
    frame_log: FrameLog,
    step: str,
    observe: Callable[[str, object], None],
) -> None:
    """Step 1 (Bluetooth off for 20 s) and step 2 (USB cable out and in), reconnection on.

    The remembered-host path: the default state directory, whose host ID the
    supply recognises. Step 3 (the remembered host ID deleted) is not
    implemented: the session reads the host ID once at connect, so deleting
    it from the state directory does not change what the reconnection
    presents, and the library has no way to make the supply forget a host.
    """
    bluetooth = step.endswith("bluetooth")
    if bluetooth and hil_unit.transport != "ble":
        pytest.skip("step 1 runs over Bluetooth")
    if not bluetooth and hil_unit.transport != "hid":
        pytest.skip("step 2 runs over USB")
    cause = "bluetooth" if bluetooth else "cable"
    dev = supply.connect(reconnect=True)
    supply.restore_by_person(MEND[cause], verify=lambda: _reachable(hil_unit))
    dev.read()
    dev.events()
    start = frame_log.mark()
    seen: dict[EventKind, float] = {}
    person.say(BREAK[cause])
    assert wait_until(
        lambda: _event_times(dev, seen) or EventKind.LINK_LOST in seen, 60.0, step=0.2
    ), "no loss reported within 60 s"
    if bluetooth:
        person.countdown(20, "Keep Bluetooth off for 20 s ...")
    back = person.wait_enter(MEND[cause])
    assert wait_until(
        lambda: _event_times(dev, seen) or EventKind.RECONNECTED in seen, 60.0, step=0.2
    ), "no reconnection within 60 s"
    resumed = dev.read(timeout=10.0)
    frame_log.settle()
    observe(f"step {step[0]} reconnected_after_s", round(seen[EventKind.RECONNECTED] - back, 3))
    assert seen[EventKind.RECONNECTED] - back <= 30.0
    assert resumed.wall_ns > int(back * 1e9)
    assert frame_log.sent(0xC8, start) == []


@pytest.mark.hil
@pytest.mark.spec("ST-050")
def test_st050_step4_no_retry_with_reconnection_off(
    ble_unit: Unit, person: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Step 4: step 1 with reconnection disabled."""
    dev = supply.connect(reconnect=False)
    supply.restore_by_person(MEND["bluetooth"], verify=lambda: _reachable(ble_unit))
    readings = dev.readings()
    next(readings)
    person.say(BREAK["bluetooth"])
    with pytest.raises(LinkLostError):
        for _ in readings:
            pass
    lost = time.time()
    # Longer than the 5 s between two attempts of a reconnection.
    time.sleep(12.0)
    frame_log.settle()
    kinds = [e.kind for e in dev.events()]
    assert dev.link_state == "lost"
    assert EventKind.RECONNECTED not in kinds
    assert [f for f in frame_log.sent() if f.created > lost] == []
    assert [
        r for r in frame_log.messages("mp305.core.session") if "reconnect attempt" in r.getMessage()
    ] == []
