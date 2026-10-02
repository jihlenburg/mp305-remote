"""UT-PY-018: `ramp()`."""

from __future__ import annotations

import math
from collections.abc import Callable
from typing import Any

import pytest

from mp305 import CommandRejectedError, Mp305, SetpointRangeError, ramp, testing
from tests.unit import frames
from tests.unit.support import reply, run_child, script

Factory = Callable[..., Mp305]


def voltages(rec: testing.MockRecord) -> list[int]:
    """The `set_voltage` of every command after the request."""
    return [c.set_voltage for c in frames.c8(rec.sent()) if c.remote_con == 1]


@pytest.mark.spec("UT-PY-018")
@pytest.mark.parametrize(
    ("case", "args", "raw", "points"),
    [
        ("a", (1.0, 2.0, 0.25, 0.01), [100, 125, 150, 175, 200], [1.0, 1.25, 1.5, 1.75, 2.0]),
        ("b", (2.0, 1.0, 0.4, 0.0), [200, 160, 120, 100], [2.0, 1.6, 1.2, 1.0]),
        ("c", (1.0, 1.0, 0.1, 0.0), [100], [1.0]),
        ("d", (1.0, 2.0, 30.0, 0.0), [100, 200], [1.0, 2.0]),
        ("e", (1.005, 1.005, 0.01, 0.0), [101], [1.01]),
    ],
)
def test_a_to_e_points(
    mock_device: Factory, case: str, args: tuple[float, ...], raw: list[int], points: list[float]
) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier=f"UT-PY-018-{case}", record=rec)
    assert ramp(dev, "voltage", *args) == points
    sent = frames.c8(rec.sent())
    assert sent[0].remote_con == 2
    assert voltages(rec) == raw


BAD: list[tuple[str, Any, type[BaseException]]] = [
    ("current 0 to 6", ("current", 0.0, 6.0, 1.0, 0.0), SetpointRangeError),
    ("power", ("power", 1.0, 2.0, 0.25, 0.0), ValueError),
    ("step 0", ("voltage", 1.0, 2.0, 0, 0.0), ValueError),
    ("step 0.004", ("voltage", 1.0, 2.0, 0.004, 0.0), ValueError),
    ("step 0.015", ("voltage", 1.0, 2.0, 0.015, 0.0), ValueError),
    ("step nan", ("voltage", 1.0, 2.0, math.nan, 0.0), ValueError),
    ("step 31", ("voltage", 1.0, 2.0, 31.0, 0.0), ValueError),
    ("dwell -1", ("voltage", 1.0, 2.0, 0.25, -1), ValueError),
    ("dwell inf", ("voltage", 1.0, 2.0, 0.25, math.inf), ValueError),
    ("current step", ("current", 0.1, 0.2, 0.0004, 0.0), ValueError),
    ("start nan", ("voltage", math.nan, 2.0, 0.25, 0.0), SetpointRangeError),
    ("stop 30.005", ("voltage", 1.0, 30.005, 0.25, 0.0), SetpointRangeError),
    ("start True", ("voltage", True, 2.0, 0.25, 0.0), TypeError),
]


@pytest.mark.spec("UT-PY-018")
def test_f_every_check_before_the_first_frame(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-018-f", record=rec)
    for name, args, error in BAD:
        with pytest.raises(error) as info:
            ramp(dev, *args)
        assert type(info.value) is error or isinstance(info.value, error), name
        if error is ValueError:
            assert not isinstance(info.value, SetpointRangeError), name
    assert frames.sent(rec.sent(), 0xC8) == []


@pytest.mark.spec("UT-PY-018")
def test_g_the_first_error_stops_the_ramp(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    s = script(replies=[reply(0xC8, b"\x00", repeat=2), reply(0xC8, b"\xff")])
    dev = mock_device([s], identifier="UT-PY-018-g", record=rec)
    with pytest.raises(CommandRejectedError):
        ramp(dev, "voltage", 1.0, 2.0, 0.25, 0.0)
    sent = frames.c8(rec.sent())
    assert sent[0].remote_con == 2
    assert [c.set_voltage for c in sent[1:]] == [100, 125]
    assert {c.output for c in sent} == {0}


INTERRUPTED = """
rec = testing.MockRecord()
dev = Mp305._from_mock([testing.default_script()], identifier="UT-PY-018-h", record=rec)
sigint_after(0.3)
outcome = None
try:
    mp305.ramp(dev, "voltage", 1.0, 2.0, 0.25, 1.0)
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
sent = frames.as_dicts(rec.sent())
dev.close()
report(outcome=outcome, latency=latency, sent=sent)
"""


@pytest.mark.spec("UT-PY-018")
def test_h_ctrl_c_stops_the_ramp() -> None:
    report, proc = run_child(INTERRUPTED)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    sent = frames.c8(frames.from_dicts(report["sent"]))
    assert [c.set_voltage for c in sent if c.remote_con == 1] == [100]
