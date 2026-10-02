"""The helpers `stream()`, `to_csv()` and `ramp()`.

Implements: DD-PY-050, DD-PY-051, DD-PY-052.
"""

from __future__ import annotations

import logging
import math
import os
import time
from collections.abc import Iterator
from typing import Union

from mp305 import _checks, _native
from mp305.device import Mp305
from mp305.errors import LinkLostError
from mp305.types import Quantity, Reading

_log = logging.getLogger("mp305")

_CLOSED = "link lost: closed by the host"


def stream(device: Mp305, rate: float, duration: float | None = None) -> Iterator[Reading]:
    """Readings at a fixed rate, for a given duration or until interrupted.

    Tick k is due `k / rate` seconds after the first `next()`; at each tick
    the generator yields the current reading if it is newer than the last
    one yielded, or waits for one until the next tick. When the supply
    delivers fewer readings than the rate asks for, one WARNING says so.

    Args:
        device: The connection.
        rate: Readings per second, 0.1 to 4.
        duration: How long in s, more than 0; None for no end.

    Returns:
        An iterator over the readings.

    Raises:
        ValueError: For a rate or a duration out of range (at the call).
        LinkLostError: For a closed device (at the call), and when the link
            is lost (while iterating).
    """
    rate = _checks.number("rate", rate, 0.1, 4.0)
    duration_ms: int | None = None
    if duration is not None:
        seconds = _checks.number("duration", duration, 0.0, math.inf, above_minimum=True)
        duration_ms = round(seconds * 1000)
        if duration_ms == 0:
            raise ValueError(f"duration {duration} rounds to 0 ms")
    if device.closed:
        raise LinkLostError(_CLOSED)
    return _ticks(device, round(rate * 1000), duration_ms)


def _ticks(device: Mp305, rate_mhz: int, duration_ms: int | None) -> Iterator[Reading]:
    """The generator of `stream()`; `rate_mhz` in millihertz."""
    t0 = time.monotonic()
    current = device.reading
    last = None if current is None else current.wall_ns
    ticks = None if duration_ms is None else (rate_mhz * duration_ms + 999_999) // 1_000_000
    end = None if duration_ms is None else t0 + duration_ms / 1000
    warned = False
    k = 0
    while ticks is None or k < ticks:
        device._wait(t0 + k * 1000 / rate_mhz - time.monotonic())
        if end is not None and ticks is not None and k + 1 >= ticks:
            next_due = end
        else:
            next_due = t0 + (k + 1) * 1000 / rate_mhz
        reading = device._newer(last)
        if reading is None:
            reading = device._wait_newer(last, next_due)
        if reading is not None:
            last = reading.wall_ns
            yield reading
        else:
            state = device.link_state
            if device.closed or state == "closed":
                return
            if state in ("lost", "denied"):
                raise device._lost()
            if state != "reconnecting" and not warned:
                warned = True
                _log.warning("the supply delivers fewer readings than the requested rate")
        k += 1


def to_csv(
    device: Mp305,
    path: Union[str, os.PathLike[str]],
    *,
    rate: float = 4.0,
    duration: float | None = None,
    overwrite: bool = False,
) -> int:
    """Records readings to a CSV file (SR-037) through `stream()`.

    Every check runs before the file is opened. The file is flushed after
    every row, so after any exception it is complete up to the last row.
    To record until Ctrl-C and then go on::

        try:
            to_csv(dev, "log.csv")
        except KeyboardInterrupt:
            pass

    Args:
        device: The connection.
        path: The file; it must not exist unless `overwrite` is true.
        rate: Readings per second, 0.1 to 4.
        duration: How long in s; None until interrupted.
        overwrite: Whether to replace an existing file.

    Returns:
        The number of rows written.

    Raises:
        ValueError: For a rate or a duration out of range.
        TypeError: When `overwrite` is not a bool.
        FileExistsError: When the file exists and `overwrite` is false.
        LinkLostError: When the link is lost while recording.
    """
    rows = stream(device, rate, duration)
    if not isinstance(overwrite, bool):
        raise TypeError("overwrite must be a bool")
    count = 0
    with open(path, "w" if overwrite else "x", encoding="utf-8", newline="") as sink:
        try:
            sink.write(_native.csv_header())
            sink.flush()
            origin: int | None = None
            for reading in rows:
                if origin is None:
                    origin = reading.wall_ns
                sink.write(_native.format_csv_row(reading.raw, reading.wall_ns, origin))
                sink.flush()
                count += 1
        except BaseException as error:
            _log.info("recording stopped after %d rows: %s", count, type(error).__name__)
            raise
    return count


def ramp(
    device: Mp305,
    quantity: Quantity,
    start: float,
    stop: float,
    step: float,
    dwell: float,
) -> list[float]:
    """Steps the voltage or the current limit from `start` to `stop`.

    Every point is checked before the first frame is sent. The first error,
    Ctrl-C included, stops the ramp; no output command is sent, so the output
    stays as it is.

    Args:
        device: The connection.
        quantity: "voltage" or "current".
        start: The first point in V or A.
        stop: The last point in V or A.
        step: The step in V or A, a multiple of 0.01 V or 0.001 A.
        dwell: The time at each point in s.

    Returns:
        The points that were set.

    Raises:
        ValueError: For a bad quantity, step or dwell.
        TypeError: For a start or stop that is not a real number.
        SetpointRangeError: For a start or stop out of range.
    """
    if quantity == "voltage":
        scale, supply_max_raw = 100, _native.SUPPLY_MAX_RAW_VOLTAGE
        limit, resolution = device.limits.max_voltage, "0.01 V"
    elif quantity == "current":
        scale, supply_max_raw = 1000, _native.SUPPLY_MAX_RAW_CURRENT
        limit, resolution = device.limits.max_current, "0.001 A"
    else:
        raise ValueError(f"quantity must be 'voltage' or 'current', got {quantity!r}")
    first = _checks.setpoint(quantity, start, scale, supply_max_raw, limit)
    last = _checks.setpoint(quantity, stop, scale, supply_max_raw, limit)
    step_value = _checks.number("step", step, 0.0, supply_max_raw / scale, above_minimum=True)
    dwell_s = _checks.number("dwell", dwell, 0.0, math.inf)
    step_raw = _checks.to_raw(step_value, scale)
    if step_raw == 0:
        raise ValueError(f"step {step} is below the resolution of {resolution}")
    if abs(step_value * scale - step_raw) > 1e-6:
        raise ValueError(f"step {step} is not a multiple of {resolution}")
    start_raw = _checks.to_raw(first, scale)
    stop_raw = _checks.to_raw(last, scale)
    direction = 1 if stop_raw >= start_raw else -1
    points_raw = [start_raw]
    point = start_raw + direction * step_raw
    while (point < stop_raw) if direction > 0 else (point > stop_raw):
        points_raw.append(point)
        point += direction * step_raw
    if stop_raw != start_raw:
        points_raw.append(stop_raw)
    points = [p / scale for p in points_raw]
    setter = device.set_voltage if quantity == "voltage" else device.set_current_limit
    for value in points:
        setter(value)
        device._wait(dwell_s)
    return points
