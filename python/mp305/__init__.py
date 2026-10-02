"""Remote control for the ISDT MP305B bench power supply.

Implements: DD-PY-061 (the public names).

Example::

    import mp305

    with mp305.Mp305.connect() as dev:
        dev.set_current_limit(0.1)
        dev.set_voltage(5.0)
        dev.output_on()
        print(dev.read())

Leaving the `with` block switches the output off, releases remote control
and disconnects, also when an exception is in flight. `mp305.testing` holds
the mock transport for tests and is not part of the public API.
"""

from __future__ import annotations

import importlib.metadata

from mp305._logs import set_log_level
from mp305.device import CURRENT_RANGE, VOLTAGE_RANGE, Mp305, default_state_dir, discover, host_id
from mp305.errors import (
    CommandRejectedError,
    ConnectionDeniedError,
    FaultActiveError,
    LinkLostError,
    ModeError,
    Mp305Error,
    Mp305TimeoutError,
    NotFoundError,
    RemoteControlDeniedError,
    RemoteControlLostError,
    SetpointRangeError,
)
from mp305.helpers import ramp, stream, to_csv
from mp305.types import (
    Counters,
    Event,
    EventKind,
    Fault,
    Found,
    Info,
    Limits,
    LinkStateName,
    LiveMode,
    Mode,
    PromptKind,
    Quantity,
    Reading,
    RemoteStateName,
    Settings,
    Transport,
)

__version__: str = importlib.metadata.version("mp305")
"""The version of the installed package."""

__all__ = [
    "Mp305",
    "discover",
    "host_id",
    "default_state_dir",
    "set_log_level",
    "stream",
    "to_csv",
    "ramp",
    "VOLTAGE_RANGE",
    "CURRENT_RANGE",
    "Reading",
    "Info",
    "Found",
    "Limits",
    "Settings",
    "Counters",
    "Event",
    "EventKind",
    "Mode",
    "LiveMode",
    "Fault",
    "Mp305Error",
    "NotFoundError",
    "ConnectionDeniedError",
    "SetpointRangeError",
    "CommandRejectedError",
    "RemoteControlDeniedError",
    "RemoteControlLostError",
    "ModeError",
    "FaultActiveError",
    "Mp305TimeoutError",
    "LinkLostError",
    "Transport",
    "LinkStateName",
    "RemoteStateName",
    "PromptKind",
    "Quantity",
    "__version__",
]
