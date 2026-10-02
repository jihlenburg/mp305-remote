"""ST-001 to ST-004: discovery and connecting by identifier (SR-001 to SR-004).

The HIL tests scan for supplies and connect only to the unit
`MP305_HIL_DEVICE` names. The parts without a supply run on the mock
discovery of `mp305.testing` (DD-PY-045), which never reaches a transport.
"""

from __future__ import annotations

import time
from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

import mp305
from mp305 import Found, Mp305, NotFoundError, testing

if TYPE_CHECKING:
    from tests.system.conftest import Guard, Person, Unit


def _found(unit: Unit, *, bluetooth: bool, usb: bool, scan: float = 10.0) -> list[Found]:
    """What discovery reports for the unit of this run."""
    return [
        f
        for f in mp305.discover(scan, bluetooth=bluetooth, usb=usb)
        if f.identifier == unit.identifier
    ]


def _simulated(identifier: str, transport: str = "ble") -> Found:
    """A second supply as the mock discovery reports it (ST-004 step 2)."""
    return Found(
        transport=transport,  # type: ignore[arg-type]
        identifier=identifier,
        unit_id="X9Z",
        name="0000MP305BS000X9Z" if transport == "ble" else "MP305B",
        rssi=-70 if transport == "ble" else None,
        remote_flag=True if transport == "ble" else None,
        description=f"{transport} {identifier} MP305B (unit X9Z)",
    )


@pytest.mark.hil
@pytest.mark.spec("ST-001")
def test_st001_bluetooth_discovery_with_remote_control_on_and_off(
    ble_unit: Unit, person: Person, supply: Guard, observe: Callable[[str, object], None]
) -> None:
    """Discovery over Bluetooth with remote control enabled, then disabled, on the supply.

    Changes on the supply: remote control is disabled by the person and
    enabled again in teardown.
    """
    # With remote control enabled (the run found the unit advertising, so it is).
    found = _found(ble_unit, bluetooth=True, usb=False)
    assert len(found) == 1
    supply_found = found[0]
    observe("enabled", str(supply_found))
    assert supply_found.transport == "ble"
    assert supply_found.identifier == ble_unit.identifier
    assert supply_found.name.startswith("0000MP305B")
    assert len(supply_found.unit_id) == 3
    assert supply_found.unit_id == supply_found.name[-3:]
    assert supply_found.remote_flag is True
    # An RSSI in dBm: an integer, below 0 for any received advertisement.
    assert isinstance(supply_found.rssi, int)
    assert -128 <= supply_found.rssi < 0

    # With remote control disabled.
    supply.restore_by_person(
        "Enable remote control on the supply's front panel again.",
        verify=lambda: bool(_found(ble_unit, bluetooth=True, usb=False, scan=5.0)),
    )
    person.wait_enter("On the supply's front panel, DISABLE remote control now.")
    disabled = _found(ble_unit, bluetooth=True, usb=False)
    observe("disabled", [str(f) for f in disabled])
    assert disabled == []


@pytest.mark.hil
@pytest.mark.spec("ST-002")
def test_st002_scan_times(ble_unit: Unit, observe: Callable[[str, object], None]) -> None:
    """Steps 1 to 3: the default scan time, 1 s and 60 s timed, 0.5 s and 61 s refused."""
    # Step 1: the default scan time.
    start = time.monotonic()
    mp305.discover()
    default = time.monotonic() - start
    observe("default_s", round(default, 3))
    # Step 2: 1 s and 60 s.
    took = {}
    for scan in (1.0, 60.0):
        start = time.monotonic()
        mp305.discover(scan)
        took[scan] = time.monotonic() - start
    observe("took_s", {str(k): round(v, 3) for k, v in took.items()})
    # Step 3: out of range.
    for scan in (0.5, 61.0):
        with pytest.raises(ValueError):
            mp305.discover(scan)
    # "About 10 s" with the 0.5 s of step 2.
    assert abs(default - 10.0) <= 0.5
    for scan, seconds in took.items():
        assert abs(seconds - scan) <= 0.5, (scan, seconds)


@pytest.mark.spec("ST-002")
def test_st002_step3_out_of_range_scan_times_raise_value_error() -> None:
    """Step 3 without a supply: the check runs before any scan.

    The mock discovery stands in for the scan, so that nothing could reach a
    transport even if the check were missing.
    """
    with testing.mock_discovery([]):
        for scan in (0.5, 61.0):
            with pytest.raises(ValueError):
                mp305.discover(scan)


@pytest.mark.hil
@pytest.mark.spec("ST-003")
def test_st003_usb_discovery(hid_unit: Unit, observe: Callable[[str, object], None]) -> None:
    """Discovery over USB with the supply plugged in.

    `Found` does not carry the vendor and product IDs: discovery reports a
    HID device only when both match (SR-003), so its presence is their
    check. The library does not expose the serial string, so this test
    cannot record for TBD-013 whether the OS reports one.
    """
    found = _found(hid_unit, bluetooth=False, usb=True, scan=1.0)
    assert len(found) == 1
    usb = found[0]
    observe("product_string", usb.name)
    observe("serial_string", "not exposed by the library")
    assert usb.transport == "hid"
    assert "MP305" in usb.name
    assert usb.identifier == hid_unit.identifier
    assert usb.unit_id == hid_unit.identifier
    assert usb.rssi is None
    assert usb.remote_flag is None


@pytest.mark.hil
@pytest.mark.spec("ST-004")
def test_st004_connect_by_identifier_and_refuse_two_supplies(hil_unit: Unit, supply: Guard) -> None:
    """Step 1 on the supply; step 2 with the supply and a simulated second discovery result."""
    # Step 1: connect by the identifier from discovery.
    found = _found(
        hil_unit,
        bluetooth=hil_unit.transport == "ble",
        usb=hil_unit.transport == "hid",
        scan=10.0 if hil_unit.transport == "ble" else 1.0,
    )
    assert len(found) == 1
    dev = supply.connect()
    assert dev.identifier == found[0].identifier
    assert dev.link_state == "ready"
    assert dev.transport == found[0].transport
    assert dev.info.model.startswith("MP305")
    dev.close()

    # Step 2: without an identifier while a second (simulated) supply is present.
    second = _simulated("ST-004-second")
    with testing.mock_discovery([found[0], second]) as record:
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    text = str(info.value)
    assert found[0].description in text
    assert second.description in text
    assert info.value.found == (found[0], second)
    assert record.attempts() == 0


@pytest.mark.spec("ST-004")
def test_st004_step2_two_simulated_supplies_raise_an_error_listing_both() -> None:
    """Step 2 on the mock: a simulated discovery result of two supplies."""
    supplies = [_simulated("ST-004-a"), _simulated("ST-004-b", "hid")]
    with testing.mock_discovery(supplies) as record:
        with pytest.raises(NotFoundError) as info:
            Mp305.connect()
    text = str(info.value)
    for found in supplies:
        assert found.description in text
    assert info.value.found == tuple(supplies)
    assert record.attempts() == 0
