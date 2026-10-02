"""UT-PY-013 and UT-PY-028: the checks before any native call."""

from __future__ import annotations

import decimal
import fractions
import functools
import math
import unittest.mock
from collections.abc import Callable
from typing import Any

import numpy
import pytest

import mp305
from mp305 import Limits, Mp305, SetpointRangeError, _checks, _native, testing
from tests.unit import frames

Factory = Callable[..., Mp305]


def wrapped(dev: Mp305) -> unittest.mock.Mock:
    """Replaces the native session with a recording wrapper."""
    spy = unittest.mock.Mock(wraps=dev._session)
    dev._session = spy
    return spy


@pytest.mark.spec("UT-PY-013")
def test_a_rejected_before_any_native_call(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-013-a", record=rec)
    spy = wrapped(dev)
    for value in (math.nan, math.inf, -0.01, 30.01, 30.005, 10**400):
        with pytest.raises(SetpointRangeError) as info:
            dev.set_voltage(value)
        if value == 30.01:
            e = info.value
            assert (e.field, e.value, e.minimum, e.maximum) == ("voltage", 30.01, 0.0, 30.0)
            assert str(e) == "voltage 30.01 is outside 0 to 30"
        if value == 10**400:
            assert info.value.value == math.inf
    for bad in (True, "5", decimal.Decimal("5"), numpy.bool_(True)):
        with pytest.raises(TypeError):
            dev.set_voltage(bad)  # type: ignore[arg-type]
    with pytest.raises(SetpointRangeError) as current:
        dev.set_current_limit(5.001)
    assert current.value.maximum == 5.0
    with pytest.raises(TypeError):
        dev.set_current_limit(True)
    for value in (math.nan, -0.001):
        with pytest.raises(SetpointRangeError):
            dev.set_current_limit(value)
    assert spy.mock_calls == []
    assert frames.sent(rec.sent(), 0xC8) == []


@pytest.mark.spec("UT-PY-013")
def test_b_accepted_values(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-013-b", record=rec)
    for value in (30.004, fractions.Fraction(1, 2), numpy.float32(5.0), numpy.int64(5)):
        dev.set_voltage(value)  # type: ignore[arg-type]
    sent = [c.set_voltage for c in frames.c8(rec.sent()) if c.remote_con == 1]
    assert sent == [3000, 50, 500, 500]


@pytest.mark.spec("UT-PY-013")
def test_c_a_voltage_limit(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-013-c", record=rec)
    dev.set_limits(max_voltage=12.0, max_current=None)
    with pytest.raises(SetpointRangeError) as info:
        dev.set_voltage(12.01)
    assert info.value.maximum == 12.0
    assert str(info.value) == "voltage 12.01 is outside 0 to 12"
    dev.set_voltage(12.004)
    dev.set_voltage(12.0)
    sent = [c.set_voltage for c in frames.c8(rec.sent()) if c.remote_con == 1]
    assert sent == [1200, 1200]
    assert dev.limits == Limits(12.0, None)


@pytest.mark.spec("UT-PY-013")
def test_d_set_limits(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-013-d", record=rec)
    with pytest.raises(TypeError):
        dev.set_limits(max_current=1.0)  # type: ignore[call-arg]
    assert dev.limits == Limits(None, None)
    spy = wrapped(dev)
    with pytest.raises(SetpointRangeError) as info:
        dev.set_limits(max_voltage=31.0, max_current=1.0)
    assert str(info.value) == "voltage limit 31 is outside 0 to 30"
    assert dev.limits == Limits(None, None)
    assert spy.set_limits.call_count == 0
    dev.set_limits(max_voltage=12.0, max_current=1.0)
    assert dev.limits == Limits(12.0, 1.0)
    with pytest.raises(SetpointRangeError) as current:
        dev.set_current_limit(1.001)
    assert current.value.maximum == 1.0
    dev.set_limits(max_voltage=None, max_current=None)
    assert dev.limits == Limits(None, None)
    dev.set_voltage(12.01)
    sent = [c.set_voltage for c in frames.c8(rec.sent()) if c.remote_con == 1]
    assert sent == [1201]


@pytest.mark.spec("UT-PY-013")
def test_e_a_bad_limit_at_connect() -> None:
    rec = testing.MockRecord()
    with pytest.raises(SetpointRangeError) as info:
        Mp305._from_mock(
            [testing.default_script()],
            identifier="UT-PY-013-e",
            record=rec,
            max_voltage=math.nan,
        )
    assert str(info.value) == "voltage limit NaN is outside 0 to 30"
    assert rec.attempts() == 0
    assert mp305.VOLTAGE_RANGE == (0.0, 30.0)
    assert mp305.CURRENT_RANGE == (0.0, 5.0)


VOLTAGES = [
    0.0,
    -0.0,
    0.004,
    0.005,
    1.005,
    12.004,
    12.005,
    29.995,
    30.0,
    30.004,
    30.005,
    30.01,
    -0.001,
    math.nan,
    math.inf,
    1e300,
]
CURRENTS = [0.0005, 1.0005, 4.9995, 5.0004, 5.0005]


def outcome(call: Callable[[], Any]) -> tuple[str, Any]:
    """("ok", value) or ("range", (text, field, value, minimum, maximum))."""
    try:
        return ("ok", call())
    except SetpointRangeError as e:
        value = "nan" if math.isnan(e.value) else e.value
        return ("range", (str(e), e.field, value, e.minimum, e.maximum))


@pytest.mark.spec("UT-PY-028")
def test_python_and_core_accept_the_same_set() -> None:
    cases = [
        ("voltage", v, 100, 3000, lim, _native.raw_voltage)
        for v in VOLTAGES
        for lim in (None, 12.0)
    ]
    cases += [
        ("current", a, 1000, 5000, lim, _native.raw_current)
        for a in CURRENTS
        for lim in (None, 1.0)
    ]
    for field, value, scale, top, limit, core in cases:

        def mine_raw(field=field, value=value, scale=scale, top=top, limit=limit) -> int:
            return _checks.to_raw(_checks.setpoint(field, value, scale, top, limit), scale)

        mine = outcome(mine_raw)
        theirs = outcome(functools.partial(core, value, limit))
        assert mine == theirs, (field, value, limit)
    assert _native.raw_voltage(0.005, None) == 1
    assert _native.raw_voltage(1.005, None) == 101
    assert _native.raw_voltage(30.004, None) == 3000
    assert _native.raw_current(0.0005, None) == 1
    assert _native.raw_current(4.9995, None) == 5000
    for value, limit in ((30.005, None), (30.01, None), (12.005, 12.0)):
        assert outcome(functools.partial(_native.raw_voltage, value, limit))[0] == "range"


@pytest.mark.spec("UT-PY-028")
def test_texts_and_number_checks() -> None:
    text = _native.setpoint_range_text
    assert text("voltage", 31.0, 0.0, 30.0) == "voltage 31 is outside 0 to 30"
    assert text("voltage", 12.01, 0.0, 12.0) == "voltage 12.01 is outside 0 to 12"
    assert text("voltage limit", math.nan, 0.0, 30.0) == "voltage limit NaN is outside 0 to 30"
    assert text("voltage", 1e-07, 0.0, 30.0) == "voltage 0.0000001 is outside 0 to 30"
    with pytest.raises(ValueError):
        _checks.number("duration", 0.0, 0.0, math.inf, above_minimum=True)
    assert _checks.number("duration", 0.001, 0.0, math.inf, above_minimum=True) == 0.001
    assert _checks.number("dwell", 0.0, 0.0, math.inf) == 0.0
    assert _checks.number("rate", numpy.float64(4.0), 0.1, 4.0) == 4.0
    assert _checks.setpoint("voltage", numpy.int64(5), 100, 3000, None) == 5.0
