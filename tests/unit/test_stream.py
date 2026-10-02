"""UT-PY-017: `stream()` at a fixed rate."""

from __future__ import annotations

import logging
import math
import threading
import time
from collections.abc import Callable

import pytest

from mp305 import LinkLostError, Mp305, Reading, stream, testing
from tests.unit.support import c3_reply, messages, script

Factory = Callable[..., Mp305]
FEWER = "the supply delivers fewer readings than the requested rate"


@pytest.mark.spec("UT-PY-017")
def test_a_four_readings_in_two_seconds(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    dev = mock_device(identifier="UT-PY-017-a")
    start = time.monotonic()
    got = list(stream(dev, 2.0, duration=2.0))
    took = time.monotonic() - start
    assert len(got) == (2000 * 2000 + 999_999) // 1_000_000 == 4
    stamps = [r.wall_ns for r in got]
    assert stamps == sorted(stamps) and len(set(stamps)) == 4
    gaps = [b.timestamp - a.timestamp for a, b in zip(got, got[1:], strict=False)]
    assert all(0.3 <= g <= 0.7 for g in gaps), gaps
    assert 1.5 <= took <= 2.1
    assert FEWER not in messages(caplog, "mp305", logging.WARNING)


@pytest.mark.spec("UT-PY-017")
def test_b_a_slow_supply_warns_once(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    capture = testing.fixtures()["C3_CAPTURE"]
    dev = mock_device([script(replies=[c3_reply(capture, after_s=0.6)])], identifier="UT-PY-017-b")
    got = list(stream(dev, 4.0, duration=2.0))
    assert 2 <= len(got) <= 4
    assert messages(caplog, "mp305", logging.WARNING).count(FEWER) == 1


@pytest.mark.spec("UT-PY-017")
def test_c_checked_at_the_call(mock_device: Factory) -> None:
    dev = mock_device(identifier="UT-PY-017-c")
    for rate, duration in (
        (4.1, None),
        (0.05, None),
        (math.nan, None),
        (2.0, 0),
        (2.0, 0.0004),
        (2.0, math.nan),
        (2.0, math.inf),
    ):
        start = time.monotonic()
        with pytest.raises(ValueError):
            stream(dev, rate, duration=duration)
        assert time.monotonic() - start < 0.05


@pytest.mark.spec("UT-PY-017")
def test_d_the_first_tick_is_newer_than_the_call(mock_device: Factory) -> None:
    s = script()
    s["replies"].append(c3_reply(testing.c3(set_voltage=500), from_s=0.3))
    dev = mock_device([s], identifier="UT-PY-017-d")
    time.sleep(0.6)
    t = time.time()
    first = next(stream(dev, 4.0, duration=0.5))
    assert first.set_voltage == 5.0
    assert first.timestamp >= t - 0.01


@pytest.mark.spec("UT-PY-017")
def test_e_a_lost_link(mock_device: Factory) -> None:
    dev = mock_device([script(close_at_s=0.8)], identifier="UT-PY-017-e", reconnect=False)
    with pytest.raises(LinkLostError) as info:
        list(stream(dev, 4.0))
    assert str(info.value).startswith("link lost: The transport reported the link closed.")


@pytest.mark.spec("UT-PY-017")
def test_f_a_closed_device(mock_device: Factory) -> None:
    closed = mock_device(identifier="UT-PY-017-f1")
    closed.close()
    with pytest.raises(LinkLostError) as info:
        stream(closed, 2.0)
    assert str(info.value) == "link lost: closed by the host"
    dev = mock_device(identifier="UT-PY-017-f2")
    ended: dict[str, object] = {}
    got: list[Reading] = []

    def iterate() -> None:
        try:
            for reading in stream(dev, 2.0):
                got.append(reading)
            ended["outcome"] = "ended"
        except BaseException as error:
            ended["outcome"] = error
        ended["at"] = time.monotonic()

    thread = threading.Thread(target=iterate)
    thread.start()
    time.sleep(0.5)
    dev.close()
    returned = time.monotonic()
    thread.join(3.0)
    assert ended["outcome"] == "ended"
    assert isinstance(ended["at"], float)
    assert ended["at"] - returned < 0.6
