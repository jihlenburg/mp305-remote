"""ST-040: the USB HID framing (SR-045), on the supply and on the mock.

The HIL part reads the `wire tx hid` and `wire rx hid` lines of the frame
log, the reports as `hidapi` wrote and read them, and checks them against
the frames the transport logged. A setpoint of 1.70 V (raw 170, `0xAA`)
makes every later `0xC3` carry a doubled byte.

The mock part checks a 70-byte frame from the supply split over two input
reports. A request longer than one report cannot be made through the
library: no allowed request has more than 18 payload bytes (SR-006), and
the mock records a request as one stream, not as reports.
"""

from __future__ import annotations

import logging
from collections.abc import Callable
from typing import TYPE_CHECKING, Any

import pytest

from mp305 import Mp305, testing
from tests.system.support import (
    FrameLog,
    first_reading,
    hid_decode,
    hid_reports,
    hid_stream,
    overlaps,
    reply,
    script,
    wait_until,
)

if TYPE_CHECKING:
    from tests.system.conftest import Guard, Person, Unit

Factory = Callable[..., Mp305]

C3_CAPTURE = testing.fixtures()["C3_CAPTURE"]


@pytest.mark.hil
@pytest.mark.spec("ST-040")
def test_st040_usb_reports_on_the_supply(
    hid_unit: Unit,
    controls: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """A USB session with a reply that contains `0xAA` (setpoint 1.70 V); for TBD-013."""
    dev = supply.connect()
    dev.set_voltage(1.7)
    assert first_reading(dev, lambda r: r.set_voltage == 1.7, 5.0) is not None
    dev.read()
    # Closed, so that the log holds whole exchanges and stops growing.
    dev.close()
    frame_log.settle()
    frames = frame_log.frames()
    wire = frame_log.wire()
    requests = [f for f in frames if f.direction == "tx"]
    written = [w for w in wire if w.direction == "tx"]
    read = [w for w in wire if w.direction == "rx"]
    observe("reports_written", len(written))
    observe("reports_read", len(read))
    observe("report_lengths_read", sorted({len(w.data) for w in read}))
    # Every frame starts in a new report, and the byte after the report ID is
    # the number of stream bytes in that report: the reports written are
    # exactly those of each logged request, one frame after the other.
    expected: list[bytes] = []
    for f in requests:
        expected.extend(hid_reports(hid_stream(0x12, f.opcode, f.payload)))
    assert [w.data for w in written] == expected
    # No request before the previous reply.
    assert overlaps(frames) == []
    # The replies: report ID 2, a count of at most 62 that the report holds,
    # and the stream bytes decode to the frames the transport logged, each
    # with address 0x21.
    assert all(w.data[0] == 0x02 and w.data[1] <= 62 for w in read)
    assert all(len(w.data) >= 2 + w.data[1] for w in read)
    stream = b"".join(w.data[2 : 2 + w.data[1]] for w in read)
    decoded = hid_decode(stream)
    assert all(ok for _, _, _, ok in decoded)
    assert {address for address, _, _, _ in decoded} == {0x21}
    replies = [(f.opcode, f.payload) for f in frames if f.direction == "rx"]
    assert [(op, payload) for _, op, payload, _ in decoded] == replies
    # The doubled byte decodes correctly: the setpoint 1.70 V is raw 0xAA 0x00.
    assert b"\xaa\xaa" in stream
    assert any(op == 0xC3 and payload[5:7] == b"\xaa\x00" for _, op, payload, _ in decoded)
    starts = [w.data[2] == 0xAA for w in read]
    observe("replies_start_at_a_report", all(starts))


@pytest.mark.spec("ST-040")
def test_st040_mock_a_70_byte_frame_over_two_reports_and_a_doubled_byte(
    mock_device: Factory, frame_log: FrameLog
) -> None:
    """A 70-byte frame from the supply in two input reports; then a `0xC3` with `0xAA`.

    `0xDF`, the longest reply (device-model.md 2.1), is not one the library
    asks for, so a whole frame is counted as ignored; a broken one would be
    counted as dropped.
    """
    long_frame = testing.hid_stream(0xDF, bytes(range(1, 70)))
    assert len(long_frame) == 74
    doubled = testing.c3(set_voltage=170)
    both: dict[str, Any] = {
        "request": 0xC2,
        "after_s": 0.01,
        "deliveries": [long_frame[:62], long_frame[62:], testing.hid_stream(0xC3, doubled)],
        "repeat": 1,
        "from_s": 0.4,
    }
    s = script("hid", replies=[reply(0xC2, C3_CAPTURE, after_s=0.01, kind="hid"), both])
    dev = mock_device([s], identifier="ST-040-mock")
    seen = first_reading(dev, lambda r: r.raw == doubled, 3.0)
    assert seen is not None
    assert seen.set_voltage == 1.7

    def counted() -> bool:
        counters = dev.counters
        return counters is not None and counters.ignored >= 1

    assert wait_until(counted, 2.0)
    frame_log.settle()
    counters = dev.counters
    assert counters is not None
    assert (counters.ignored, counters.dropped_frames) == (1, 0)
    assert "ignored 0xdf" in frame_log.texts("mp305.core.link", logging.WARNING)
