"""ST-017 step 1, ST-039 and ST-047: checks of the frame logs kept earlier in the same run.

These tests send nothing. They read the frame logs that ST-006, ST-008,
ST-013 and ST-018 kept in this session (the `frame_log` fixture keeps the
log of every HIL test under its ST ID), so they carry the `hil` marker and
run in the HIL session after those entries; this module's name sorts after
the other test modules. Without the logs of their sources they skip.
"""

from __future__ import annotations

from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

from tests.system.support import (
    AF01_UUID,
    AF02_UUID,
    REQUEST_LENGTHS,
    FrameLog,
    overlaps,
)

if TYPE_CHECKING:
    from tests.system.conftest import RunRecord, Unit


def _logs(
    run_record: RunRecord, specs: tuple[str, ...], transport: str | None = None
) -> dict[str, list[FrameLog]]:
    """The kept frame logs of `specs`, by ST ID, leaving out the IDs without one."""
    found = {spec: run_record.logs_of(spec, transport) for spec in specs}
    return {spec: logs for spec, logs in found.items() if logs}


@pytest.mark.hil
@pytest.mark.spec("ST-017")
def test_st017_step1_no_overlapping_requests_in_the_log_of_st013(
    hil_unit: Unit, run_record: RunRecord
) -> None:
    """Step 1: the frame log of ST-013 has no request sent while another was in flight."""
    logs = _logs(run_record, ("ST-013",))
    if not logs:
        pytest.skip("needs the frame log of ST-013 from this run")
    for log in logs["ST-013"]:
        assert overlaps(log.frames()) == []


@pytest.mark.hil
@pytest.mark.spec("ST-039")
def test_st039_bluetooth_frames_have_the_stated_shape(
    ble_unit: Unit, run_record: RunRecord, observe: Callable[[str, object], None]
) -> None:
    """The frame logs of ST-008 and ST-013 over Bluetooth.

    Requests: `12 op payload` on AF01, `op payload` on AF02. Notifications:
    `31 op payload` on AF01, `op payload` on AF02, each decoded as one frame.
    One write in flight: no request before the previous reply (or its timeout).
    The log may end between a frame's two lines (`tx` before `wire tx`,
    `wire rx` before `rx`), so one unmatched last line is allowed.
    """
    logs = _logs(run_record, ("ST-008", "ST-013"), "ble")
    if not logs:
        pytest.skip("needs the Bluetooth frame log of ST-008 or ST-013 from this run")
    observe("logs_checked", sorted(logs))
    for spec, kept in logs.items():
        for log in kept:
            frames = log.frames()
            wire = [w for w in log.wire() if w.transport == "ble"]
            requests = [f for f in frames if f.direction == "tx"]
            writes = [w for w in wire if w.direction == "tx"]
            assert 0 <= len(requests) - len(writes) <= 1, spec
            for f, w in zip(requests, writes, strict=False):
                if f.route == "ble AF01":
                    assert w.characteristic == AF01_UUID, (spec, f, w)
                    assert w.data == bytes([0x12, f.opcode]) + f.payload, (spec, f, w)
                else:
                    assert w.characteristic == AF02_UUID, (spec, f, w)
                    assert w.data == bytes([f.opcode]) + f.payload, (spec, f, w)
            replies = [f for f in frames if f.direction == "rx"]
            notifications = [w for w in wire if w.direction == "rx"]
            assert log.receive_errors() == [], spec
            assert 0 <= len(notifications) - len(replies) <= 1, spec
            for f, w in zip(replies, notifications, strict=False):
                if f.route == "ble AF01":
                    assert w.characteristic == AF01_UUID, (spec, f, w)
                    assert w.data == bytes([0x31, f.opcode]) + f.payload, (spec, f, w)
                else:
                    assert w.characteristic == AF02_UUID, (spec, f, w)
                    assert w.data == bytes([f.opcode]) + f.payload, (spec, f, w)
            assert overlaps(frames) == [], spec


@pytest.mark.hil
@pytest.mark.spec("ST-047")
def test_st047_every_request_carries_its_full_payload(
    hil_unit: Unit, run_record: RunRecord, observe: Callable[[str, object], None]
) -> None:
    """Every request in the frame logs of ST-006, ST-008 and ST-018 against protocol.md 3 and 4."""
    logs = _logs(run_record, ("ST-006", "ST-008", "ST-018"))
    if not logs:
        pytest.skip("needs the frame log of ST-006, ST-008 or ST-018 from this run")
    observe("logs_checked", sorted(logs))
    for spec, kept in logs.items():
        for log in kept:
            for frame in log.sent():
                assert len(frame.payload) == REQUEST_LENGTHS[frame.opcode], (spec, frame)
