"""The one place the Python layer checks numbers.

Implements: DD-PY-053, DD-PY-041 (the setpoint and limit checks).

The checks are Python's own, while the rounding equals the core's, so the
Python layer and the core accept the same set of values (defense in depth,
ADR-0008).
"""

from __future__ import annotations

import math
import numbers

from mp305 import _native
from mp305.errors import SetpointRangeError

_SCAN_FIELD = "scan time (s)"


def real(name: str, value: object) -> float:
    """`value` as a float when it is a real number and not a bool.

    Args:
        name: The argument's name, for the error.
        value: The value to check.

    Returns:
        The value as a float; an int beyond the float range becomes an
        infinity of its sign.

    Raises:
        TypeError: When the value is not a real number, or is a bool.
    """
    if not isinstance(value, numbers.Real) or isinstance(value, bool):
        raise TypeError(f"{name} must be a real number, got {type(value).__name__}")
    try:
        return float(value)
    except OverflowError:
        # `math.copysign(math.inf, value)` would convert `value` to a float
        # and overflow again; the sign is taken by comparison instead.
        return -math.inf if value < 0 else math.inf


def half_up(v: float) -> int:
    """Rounds half up; equals Rust's `f64::round` for values not negative."""
    floor = math.floor(v)
    return floor + (1 if v - floor >= 0.5 else 0)


def to_raw(x: float, scale: int) -> int:
    """The core's `units::to_raw`: six decimals first, then an integer.

    Args:
        x: A finite value from 0 to 1e9.
        scale: Raw steps per unit: 100 for a voltage, 1000 for a current.

    Returns:
        The raw value.
    """
    return half_up(half_up(x * scale * 1e6) / 1e6)


def _range_error(field: str, value: float, minimum: float, maximum: float) -> SetpointRangeError:
    """A `SetpointRangeError` with the core's text."""
    return SetpointRangeError(
        _native.setpoint_range_text(field, value, minimum, maximum),
        field=field,
        value=value,
        minimum=minimum,
        maximum=maximum,
    )


def setpoint(
    field: str, value: object, scale: int, supply_max_raw: int, limit: float | None
) -> float:
    """Checks a setpoint as the core does.

    Args:
        field: "voltage" or "current".
        value: The setpoint in V or A.
        scale: Raw steps per unit: 100 for a voltage, 1000 for a current.
        supply_max_raw: The supply's maximum as a raw value.
        limit: The user's limit in V or A, or None for no user limit.

    Returns:
        The setpoint as a float.

    Raises:
        TypeError: When the value is not a real number.
        SetpointRangeError: When the value is not finite, is negative, is
            above 1e9, or rounds above the supply's range or the limit.
    """
    v = real(field, value)
    maximum = supply_max_raw / scale
    if not math.isfinite(v) or v < 0.0 or v > 1e9 or to_raw(v, scale) > supply_max_raw:
        raise _range_error(field, v, 0.0, maximum)
    if limit is not None and to_raw(v, scale) > to_raw(limit, scale):
        raise _range_error(field, v, 0.0, limit)
    return v


def limit(field: str, value: object, supply_max: float) -> float | None:
    """Checks a user limit: None, or a real number from 0 to the supply's maximum.

    Args:
        field: "voltage limit" or "current limit".
        value: The limit in V or A, or None for no limit.
        supply_max: The supply's maximum in V or A.

    Returns:
        The limit as a float, or None.

    Raises:
        TypeError: When the value is not None and not a real number.
        SetpointRangeError: When the value is not finite or outside 0 to the
            supply's maximum.
    """
    if value is None:
        return None
    v = real(field, value)
    if not (math.isfinite(v) and 0.0 <= v <= supply_max):
        raise _range_error(field, v, 0.0, supply_max)
    return v


def scan_time(value: object) -> float:
    """Checks a scan time: finite and from 1 to 60 s.

    Args:
        value: The scan time in s.

    Returns:
        The scan time as a float.

    Raises:
        TypeError: When the value is not a real number.
        SetpointRangeError: Outside 1 to 60 s, with the field "scan time (s)".
    """
    v = real("scan_time", value)
    lowest, highest = _native.SCAN_MIN_S, _native.SCAN_MAX_S
    if not (math.isfinite(v) and lowest <= v <= highest):
        raise _range_error(_SCAN_FIELD, v, lowest, highest)
    return v


def number(
    name: str, value: object, minimum: float, maximum: float, *, above_minimum: bool = False
) -> float:
    """Checks a finite number from `minimum` to `maximum`.

    Args:
        name: The argument's name, for the error.
        value: The value to check.
        minimum: The lowest allowed value.
        maximum: The highest allowed value; may be `math.inf`.
        above_minimum: Whether `minimum` itself is excluded.

    Returns:
        The value as a float.

    Raises:
        TypeError: When the value is not a real number.
        ValueError: When it is not finite or outside the range.
    """
    v = real(name, value)
    low_ok = v > minimum if above_minimum else v >= minimum
    if not (math.isfinite(v) and low_ok and v <= maximum):
        raise ValueError(f"{name} must be a finite number from {minimum} to {maximum}, got {v}")
    return v


def wait_slice(remaining: float) -> float:
    """The next wait of a loop: never negative and at most 0.1 s."""
    return min(max(remaining, 0.0), 0.1)
