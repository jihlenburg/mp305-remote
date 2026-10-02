"""UT-PY-014: control calls, the current reading, `read()` and `reconnect`."""

from __future__ import annotations

import logging
import math
import time
from collections.abc import Callable

import pytest

from mp305 import Counters, EventKind, LinkLostError, Mp305, Mp305TimeoutError, testing
from tests.unit import frames
from tests.unit.support import c3_reply, messages, script, wait_until

Factory = Callable[..., Mp305]


@pytest.mark.spec("UT-PY-014")
def test_a_a_dc_session(mock_device: Factory, caplog: pytest.LogCaptureFixture) -> None:
    caplog.set_level(logging.INFO, logger="mp305")
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-014-a", record=rec)
    states: list[tuple[str, str]] = []
    for call in (
        lambda: dev.set_voltage(1.7),
        lambda: dev.set_current_limit(0.1),
        dev.output_on,
        dev.output_off,
        dev.release_remote_control,
        dev.request_remote_control,
    ):
        call()
        states.append((dev.remote_state, dev.link_state))
        if call == dev.output_off:
            off = time.monotonic()
    sent = [(c.remote_con, c.set_voltage, c.set_current, c.output) for c in frames.c8(rec.sent())]
    assert [s[0] for s in sent] == [2, 1, 1, 1, 1, 0, 2]
    assert sent[1] == (1, 170, 1000, 0)
    assert sent[2] == (1, 1300, 100, 0)
    assert sent[3] == (1, 1300, 1000, 1)
    assert sent[4] == (1, 1300, 1000, 0)
    assert sent[5][3] == 0
    assert [s[0] for s in states] == ["granted"] * 4 + ["none", "granted"]
    assert {s[1] for s in states} == {"ready"}
    changed = []
    wait_until(
        lambda: changed.extend(
            e for e in dev.events() if e.kind is EventKind.SETPOINTS_CHANGED
        )
        or changed,
        max(0.0, off + 1.0 - time.monotonic()),
    )
    assert len(changed) == 1
    event = changed[0]
    assert (event.set_voltage, event.set_current) == (13.0, 1.0)
    assert (event.expected_voltage, event.expected_current) == (1.7, 0.1)
    assert messages(caplog, "mp305", logging.INFO).count(
        "setpoints differ: set 13.0 V 1.0 A, expected 1.7 V 0.1 A"
    ) == 1
    counters = dev.counters
    assert isinstance(counters, Counters)
    assert all(
        isinstance(v, int)
        for v in (counters.dropped_frames, counters.ignored, counters.late_replies)
    )


@pytest.mark.spec("UT-PY-014")
def test_b_the_current_reading_without_a_call(mock_device: Factory) -> None:
    s = script()
    s["replies"].append(c3_reply(testing.c3(set_voltage=500), from_s=0.3))
    dev = mock_device([s], identifier="UT-PY-014-b")
    time.sleep(0.6)
    reading = dev.reading
    assert reading is not None
    assert reading.set_voltage == 5.0
    assert time.time() - reading.timestamp < 0.5
    before = dev.reading
    assert before is not None
    r = dev.read()
    assert r.wall_ns > before.wall_ns


@pytest.mark.spec("UT-PY-014")
def test_c_read_timeout_checked(mock_device: Factory) -> None:
    dev = mock_device(identifier="UT-PY-014-c")
    for timeout in (0.05, math.nan, 61):
        with pytest.raises(ValueError):
            dev.read(timeout=timeout)


@pytest.mark.spec("UT-PY-014")
def test_d_no_new_reading(mock_device: Factory) -> None:
    dev = mock_device([script(stop_replying_at_s=0.2)], identifier="UT-PY-014-d")
    time.sleep(0.4)
    with pytest.raises(Mp305TimeoutError) as info:
        dev.read(timeout=0.3)
    assert str(info.value) == "no new reading within 0.3 s"


@pytest.mark.spec("UT-PY-014")
def test_e_read_on_a_lost_link(mock_device: Factory) -> None:
    dev = mock_device([script(close_at_s=0.2)], identifier="UT-PY-014-e", reconnect=False)
    kinds: list[EventKind] = []
    assert wait_until(
        lambda: kinds.extend(e.kind for e in dev.events()) or EventKind.LINK_LOST in kinds, 3.0
    )
    t = time.monotonic()
    with pytest.raises(LinkLostError) as info:
        dev.read(timeout=2.0)
    assert time.monotonic() - t < 0.2
    assert str(info.value).startswith("link lost: The transport reported the link closed.")


@pytest.mark.spec("UT-PY-014")
def test_f_the_reconnect_flag(mock_device: Factory) -> None:
    dev = mock_device(identifier="UT-PY-014-f")
    with pytest.raises(TypeError):
        dev.reconnect = 1  # type: ignore[assignment]
    dev.reconnect = True
    assert dev.reconnect is True
