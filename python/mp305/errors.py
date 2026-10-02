"""The exceptions of the mp305 library.

Implements: DD-PY-010.

Every class takes exactly one positional argument, the message, and its
attributes as keyword arguments with defaults. So `args == (message,)` and
`str(e) == message` hold for every class, also for the two `OSError`
subclasses (whose `errno` stays None), and `pickle` and `copy` round-trip
every class with its attributes.
"""

from __future__ import annotations

import math

from mp305.types import Fault, Found


class Mp305Error(Exception):
    """The base class of every error the library raises."""

    def __init__(self, message: str) -> None:
        """Creates the error.

        Args:
            message: What went wrong.
        """
        super().__init__(message)


class NotFoundError(Mp305Error):
    """No supply, or more than one, was found to connect to.

    Attributes:
        found: The supplies that were found (empty when none was).
    """

    found: tuple[Found, ...]

    def __init__(self, message: str, *, found: tuple[Found, ...] = ()) -> None:
        """Creates the error.

        Args:
            message: What went wrong.
            found: The supplies that were found.
        """
        super().__init__(message)
        self.found = found


class ConnectionDeniedError(Mp305Error):
    """The supply denied the connection."""


class CommandRejectedError(Mp305Error):
    """The supply rejected a command.

    Attributes:
        status: The status byte of the reply.
        reason: "mode", "range", "fault", "busy" or "status <n>".
    """

    status: int
    reason: str

    def __init__(self, message: str, *, status: int = 0, reason: str = "") -> None:
        """Creates the error.

        Args:
            message: What went wrong.
            status: The status byte of the reply.
            reason: Why the supply rejected the command.
        """
        super().__init__(message)
        self.status = status
        self.reason = reason


class RemoteControlDeniedError(Mp305Error):
    """The supply denied remote control, or its prompt timed out."""


class RemoteControlLostError(Mp305Error):
    """Remote control is not held; request it again."""


class ModeError(Mp305Error):
    """The supply is not in DC mode, the only mode this version controls.

    Attributes:
        live_mode_raw: The raw live mode the supply reported (-1 if unknown).
    """

    live_mode_raw: int

    def __init__(self, message: str, *, live_mode_raw: int = -1) -> None:
        """Creates the error.

        Args:
            message: What went wrong.
            live_mode_raw: The raw live mode the supply reported.
        """
        super().__init__(message)
        self.live_mode_raw = live_mode_raw


class FaultActiveError(Mp305Error):
    """The supply reports a fault, so the output is not switched on.

    Attributes:
        faults: The active faults.
    """

    faults: frozenset[Fault]

    def __init__(self, message: str, *, faults: frozenset[Fault] = frozenset()) -> None:
        """Creates the error.

        Args:
            message: What went wrong.
            faults: The active faults.
        """
        super().__init__(message)
        self.faults = faults


class SetpointRangeError(Mp305Error, ValueError):
    """A value outside its allowed range.

    Attributes:
        field: What the value is, for example "voltage" or "current limit".
        value: The value that was given.
        minimum: The lowest allowed value.
        maximum: The highest allowed value (the supply's or the user's).
    """

    field: str
    value: float
    minimum: float
    maximum: float

    def __init__(
        self,
        message: str,
        *,
        field: str = "",
        value: float = math.nan,
        minimum: float = 0.0,
        maximum: float = math.nan,
    ) -> None:
        """Creates the error.

        Args:
            message: What went wrong.
            field: What the value is.
            value: The value that was given.
            minimum: The lowest allowed value.
            maximum: The highest allowed value.
        """
        super().__init__(message)
        self.field = field
        self.value = value
        self.minimum = minimum
        self.maximum = maximum


class Mp305TimeoutError(Mp305Error, TimeoutError):
    """No reply, or no new reading, arrived within its bound."""


class LinkLostError(Mp305Error, ConnectionError):
    """The link to the supply ended, or the connection was closed."""
