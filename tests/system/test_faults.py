"""ST-026 and ST-027: faults (SR-026, SR-027).

The trip follows AT-009: OCP mode selected on the front panel, 5.00 V and
0.100 A, Load B (22 ohm, about 230 mA at 5 V) on the output, output on. The
person selects OCP mode and selects CC mode again in teardown.
"""

from __future__ import annotations

import time
from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

from mp305 import EventKind, FaultActiveError, Mp305, Reading, testing
from mp305.types import Fault
from tests.system.support import FrameLog, control, reply, script, wait_until

if TYPE_CHECKING:
    from tests.system.conftest import Guard, Person, Unit

Factory = Callable[..., Mp305]


def _select_ocp(person: Person, supply: Guard) -> None:
    """AT-009 step 1, undone by the person in teardown."""
    supply.restore_by_person("On the supply's front panel, select CC mode again (instead of OCP).")
    person.wait_enter("On the supply's front panel, select OCP mode instead of CC.")


@pytest.mark.hil
@pytest.mark.spec("ST-026")
def test_st026_output_on_is_refused_while_a_fault_is_active(
    hil_unit: Unit,
    load_b: str,
    person: Person,
    controls: Person,
    supply: Guard,
    frame_log: FrameLog,
) -> None:
    """Trip OCP as in AT-009, then call `output_on()`."""
    _select_ocp(person, supply)
    dev = supply.connect()
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    dev.output_on()

    def tripped() -> bool:
        r = dev.reading
        return r is not None and Fault.OVER_CURRENT in r.faults

    assert wait_until(tripped, 5.0, step=0.05), "no over-current fault within 5 s"
    start = frame_log.mark()
    with pytest.raises(FaultActiveError):
        dev.output_on()
    frame_log.settle()
    assert [f for f in frame_log.sent(0xC8, start) if control(f.payload).output == 1] == []


@pytest.mark.hil
@pytest.mark.spec("ST-027")
def test_st027_step1_the_trip_shows_in_the_first_reading_and_is_reported_once(
    hil_unit: Unit,
    load_b: str,
    person: Person,
    controls: Person,
    supply: Guard,
    observe: Callable[[str, object], None],
) -> None:
    """Step 1: trip OCP as in AT-009 while streaming.

    "The first reading after the trip" is the first reading, from 100 ms
    after the output-on was acknowledged (before that a reading may not yet
    show the command, SR-019), that shows the output off again or any fault.
    """
    _select_ocp(person, supply)
    dev = supply.connect()
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    readings = dev.readings()
    dev.events()
    dev.output_on()
    settled_ns = time.time_ns() + 100_000_000
    got: list[Reading] = []
    end = time.monotonic() + 3.0
    for reading in readings:
        got.append(reading)
        if time.monotonic() >= end:
            break
    events = [e for e in dev.events() if e.kind is EventKind.FAULTS_CHANGED]
    observe("readings", [(r.output_on, sorted(f.text for f in r.faults)) for r in got])
    observe("fault_events", [sorted(f.text for f in e.faults or ()) for e in events])
    after = [r for r in got if r.wall_ns > settled_ns]
    trip = next((r for r in after if r.faults or not r.output_on), None)
    assert trip is not None, "no trip within 3 s"
    assert Fault.OVER_CURRENT in trip.faults
    added = [e for e in events if e.faults is not None and Fault.OVER_CURRENT in e.faults]
    assert len(added) == 1


@pytest.mark.spec("ST-027")
def test_st027_step2_an_unknown_fault_bit(mock_device: Factory) -> None:
    """Step 2 on the mock: a `0xC3` with bit 11 set."""
    s = script(replies=[reply(0xC2, testing.c3(charge_error=1 << 11), after_s=0.01)])
    dev = mock_device([s], identifier="ST-027-bit-11")
    r = dev.read()
    assert r.faults == frozenset({Fault.UNKNOWN_BIT_11})
    assert [f.text for f in r.faults] == ["unknown fault bit 11"]
