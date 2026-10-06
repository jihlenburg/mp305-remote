"""The `Mp305` class, `discover()` and the exit hook.

Implements: DD-PY-005 (the Python wrappers), DD-PY-008 (the exit hook),
DD-PY-040, DD-PY-041, DD-PY-042, DD-PY-043, DD-PY-044, DD-PY-045 (the mock
constructor).

`_discover` and `_open_session` are the two module-level seams that
`mp305.testing.mock_discovery` replaces.
"""

from __future__ import annotations

import atexit
import itertools
import logging
import os
import pathlib
import time
from collections.abc import Callable, Iterator, Sequence
from types import TracebackType
from typing import TYPE_CHECKING, Union, cast

from mp305 import _checks, _logs, _native
from mp305.errors import LinkLostError, Mp305Error, Mp305TimeoutError, NotFoundError
from mp305.types import (
    Counters,
    Event,
    EventKind,
    Found,
    Info,
    Limits,
    LinkStateName,
    Reading,
    RemoteStateName,
    SentFrame,
    Transport,
    counters_from_native,
    event_from_native,
    found_from_native,
    info_from_native,
    reading_from_native,
)

if TYPE_CHECKING:
    from mp305._native import EventTuple
    from mp305.testing import MockRecord, ScriptDict

_log = logging.getLogger("mp305")

StatePath = Union[str, os.PathLike[str]]
"""A state directory: a `str` or any `os.PathLike`."""

SCAN_DEFAULT_S: float = _native.SCAN_DEFAULT_S
"""The default scan time in s."""

VOLTAGE_RANGE: tuple[float, float] = (0.0, _native.SUPPLY_MAX_RAW_VOLTAGE / 100)
"""The supply's voltage range in V."""

CURRENT_RANGE: tuple[float, float] = (0.0, _native.SUPPLY_MAX_RAW_CURRENT / 1000)
"""The supply's current range in A."""

_VOLT_SCALE = 100
_AMP_SCALE = 1000
_CLOSED = "link lost: closed by the host"
_TERMINAL = ("lost", "denied")
_mock_numbers = itertools.count(1)


def _native_discover(scan_time: float, bluetooth: bool, usb: bool) -> list[Found]:
    """The default discovery seam: the native scan, converted."""
    return [found_from_native(t) for t in _native.discover(scan_time, bluetooth, usb)]


_discover: Callable[[float, bool, bool], list[Found]] = _native_discover

_open_session: Callable[
    [str, StatePath | None, bool, float | None, float | None], _native.Session
] = _native.Session.connect


def discover(
    scan_time: float = SCAN_DEFAULT_S, *, bluetooth: bool = True, usb: bool = True
) -> list[Found]:
    """Finds supplies over Bluetooth LE and USB.

    Args:
        scan_time: How long the Bluetooth scan runs, 1 to 60 s.
        bluetooth: Whether to scan over Bluetooth LE.
        usb: Whether to enumerate USB HID devices.

    Returns:
        The supplies found; an empty list when there is none.

    Raises:
        TypeError: For a scan time that is not a real number, or a flag
            that is not a bool.
        SetpointRangeError: For a scan time outside 1 to 60 s.
        LinkLostError: When every backend that ran failed.
    """
    scan = _checks.scan_time(scan_time)
    if not isinstance(bluetooth, bool) or not isinstance(usb, bool):
        raise TypeError("bluetooth and usb must be bools")
    _logs.ensure_started()
    return _discover(scan, bluetooth, usb)


def _several_text(found: Sequence[Found]) -> str:
    """The text of `NotFoundError` when discovery found more than one supply.

    One `hid` and one `ble` entry are most likely one unit: a supply on a
    USB cable keeps advertising until a USB host talks to it. The supply has
    no USB serial number, so the two cannot be proven to be one unit, and
    the text names the cause and the remedy instead of choosing (SR-004).
    """
    listing = "; ".join(f.description for f in found)
    transports = sorted(f.transport for f in found)
    if transports == ["ble", "hid"]:
        return (
            "found one supply on USB and one over Bluetooth; a supply on a USB cable is"
            " also seen over Bluetooth until a USB host talks to it. Pass usb=False or"
            " bluetooth=False to choose a transport, or pass one identifier: " + listing
        )
    return "several supplies found; pass one identifier: " + listing


def host_id(state_dir: StatePath | None = None) -> bytes:
    """The 16-byte host ID of this installation, created on first use.

    Args:
        state_dir: The state directory; None for the default.

    Returns:
        The host ID the bind presents to the supply.

    Raises:
        Mp305Error: When the store cannot be read or written.
    """
    _logs.ensure_started()
    return _native.host_id(state_dir)


def default_state_dir() -> pathlib.Path:
    """The default state directory of the user (host ID and markers).

    Returns:
        The directory; it is created on first use.

    Raises:
        Mp305Error: When the OS gives no home directory.
    """
    _logs.ensure_started()
    return pathlib.Path(_native.default_state_dir())


def _wait_at_exit() -> None:
    """Waits at exit for the output-offs and closes that still run."""
    names = _native.pending_safety()
    if not names:
        return
    joined = ", ".join(names)
    try:
        # Inside the `try`: a second Ctrl-C while the WARNING is being logged
        # also abandons the wait with the ERROR (DD-PY-008).
        _log.warning(
            "waiting for %s to finish before exit; press Ctrl-C again to abandon them "
            "(the output may stay on)",
            joined,
        )
        _native.wait_safety()
    except KeyboardInterrupt:
        _log.error("abandoned %s; the output may still be on", joined)


atexit.register(_wait_at_exit)


class Mp305:
    """A connection to one ISDT MP305B bench power supply.

    Open one with `Mp305.connect()` and use it as a context manager, so that
    leaving the block switches the output off, releases remote control and
    disconnects (SR-029), also when an exception is in flight.

    Ctrl-C raises `KeyboardInterrupt` in a waiting call within 0.5 s, on the
    main thread only: a call on another thread ends at its own bound or when
    another thread closes the device. `output_off` and `close` finish their sequence after an
    interrupt; the process waits for them at exit unless Ctrl-C is pressed
    again. The library cannot be used in a process forked after it started;
    use the multiprocessing start method spawn or forkserver.

    The constructor is not public API.
    """

    def __init__(
        self,
        native: _native.Session,
        on_prompt: Callable[[Event], None] | None,
        record: MockRecord | None,
        limits: Limits,
        reconnect: bool,
    ) -> None:
        """Wraps a native session; use `Mp305.connect` instead.

        Args:
            native: The native session.
            on_prompt: Called once per prompt of the supply.
            record: The mock record of a mock session.
            limits: The user's limits.
            reconnect: Whether a lost link is reconnected.
        """
        self._session = native
        self._on_prompt = on_prompt
        self._record = record
        self._limits = limits
        self._reconnect = reconnect
        self._identifier: str = native.identifier()
        self._info: Info | None = None
        self._transport: Transport | None = None
        self._unclean: str | None = None
        self._skipped = 0
        self._closed = False
        self._closing = False

    # Opening.

    @classmethod
    def connect(
        cls,
        identifier: str | None = None,
        *,
        on_prompt: Callable[[Event], None] | None = None,
        reconnect: bool = False,
        max_voltage: float | None = None,
        max_current: float | None = None,
        state_dir: StatePath | None = None,
        scan_time: float = SCAN_DEFAULT_S,
        bluetooth: bool = True,
        usb: bool = True,
    ) -> Mp305:
        """Connects to a supply and waits until it is ready.

        Without an identifier, discovery runs first over the transports that
        `bluetooth` and `usb` choose, and the connection is made only when
        exactly one supply was found. A supply on a USB cable is also seen
        over Bluetooth until a USB host talks to it, so it is found twice;
        pass `usb=False` or `bluetooth=False` to choose one transport.

        Args:
            identifier: The supply's identifier as `discover()` reports it.
            on_prompt: Called once per prompt of the supply (confirm the
                connection, allow remote control) while a call waits.
            reconnect: Whether a lost link is reconnected.
            max_voltage: The user's voltage limit in V, or None.
            max_current: The user's current limit in A, or None.
            state_dir: The state directory; None for the default.
            scan_time: The scan time in s when no identifier is given.
            bluetooth: Whether the scan without an identifier covers
                Bluetooth LE; must stay True when an identifier is given.
            usb: Whether the scan without an identifier covers USB HID;
                must stay True when an identifier is given.

        Returns:
            The ready connection.

        Raises:
            TypeError: For an argument of the wrong type.
            ValueError: For an identifier together with `bluetooth=False`
                or `usb=False`.
            SetpointRangeError: For a limit or scan time out of range.
            NotFoundError: When no supply, or several, were found. With one
                supply on USB and one over Bluetooth, the text explains that
                these are likely one unit and how to choose a transport.
            Mp305Error: Or one of its subclasses, when the connection fails.
        """
        max_voltage, max_current = _limits(max_voltage, max_current)
        scan = _checks.scan_time(scan_time)
        if not isinstance(reconnect, bool):
            raise TypeError("reconnect must be a bool")
        if identifier is not None and not isinstance(identifier, str):
            raise TypeError("identifier must be a str or None")
        if not isinstance(bluetooth, bool) or not isinstance(usb, bool):
            raise TypeError("bluetooth and usb must be bools")
        if identifier is not None and not (bluetooth and usb):
            raise ValueError(
                "bluetooth and usb choose the transports of the scan without an identifier;"
                " leave them at True when an identifier is given"
            )
        _logs.ensure_started()
        if identifier is None:
            found = _discover(scan, bluetooth, usb)
            if not found:
                raise NotFoundError(_native.not_found_text(), found=())
            if len(found) > 1:
                raise NotFoundError(_several_text(found), found=tuple(found))
            identifier = found[0].identifier
        native = _open_session(identifier, state_dir, reconnect, max_voltage, max_current)
        return cls._attach(native, on_prompt, None, Limits(max_voltage, max_current), reconnect)

    @classmethod
    def _from_mock(
        cls,
        scripts: Sequence[ScriptDict],
        *,
        on_prompt: Callable[[Event], None] | None = None,
        reconnect: bool = False,
        max_voltage: float | None = None,
        max_current: float | None = None,
        state_dir: StatePath | None = None,
        identifier: str | None = None,
        record: MockRecord | None = None,
    ) -> Mp305:
        """Connects over the scripted mock transport (test support).

        Args:
            scripts: One script per connection attempt.
            on_prompt: As for `connect`.
            reconnect: As for `connect`.
            max_voltage: As for `connect`.
            max_current: As for `connect`.
            state_dir: A state directory, or None for an in-memory store and
                `MOCK_HOST_ID`.
            identifier: The identifier; None gives "mock-<n>".
            record: Where the mock's frames are recorded; None creates one.

        Returns:
            The ready connection.
        """
        from mp305.testing import MockRecord

        max_voltage, max_current = _limits(max_voltage, max_current)
        if not isinstance(reconnect, bool):
            raise TypeError("reconnect must be a bool")
        if identifier is not None and not isinstance(identifier, str):
            raise TypeError("identifier must be a str or None")
        if identifier is None:
            identifier = f"mock-{next(_mock_numbers)}"
        if record is None:
            record = MockRecord()
        _logs.ensure_started()
        native = _native.Session.from_mock(
            list(scripts),
            state_dir,
            reconnect,
            max_voltage,
            max_current,
            identifier,
            record.handles,
        )
        return cls._attach(native, on_prompt, record, Limits(max_voltage, max_current), reconnect)

    @classmethod
    def _attach(
        cls,
        native: _native.Session,
        on_prompt: Callable[[Event], None] | None,
        record: MockRecord | None,
        limits: Limits,
        reconnect: bool,
    ) -> Mp305:
        """Builds the object and waits until the session is ready.

        On an `Exception`, the session is closed (output off) and the first
        exception propagates. On any other `BaseException` (a Ctrl-C, also
        one from `on_prompt`), the close starts in the background and the
        exception propagates at once.
        """
        device = cls(native, on_prompt, record, limits, reconnect)
        try:
            info = native.ready(device._handle)
        except Exception:
            device._closed = True
            try:
                native.close(True, None)
            except Exception as error:
                _log.error(
                    "close after the failed connect of %s failed: %s", device._identifier, error
                )
            raise
        except BaseException:
            device._closing = True
            native.close_start(True)
            raise
        device._info = info_from_native(info)
        device._transport = cast(Transport, native.transport())
        return device

    # Properties.

    @property
    def info(self) -> Info:
        """What the supply reported about itself at connect."""
        if self._info is None:
            raise Mp305Error("the device is not connected")
        return self._info

    @property
    def identifier(self) -> str:
        """The identifier the connection was opened with."""
        return self._identifier

    @property
    def transport(self) -> Transport:
        """The link of the connection: "ble" or "hid"."""
        if self._transport is None:
            raise Mp305Error("the device is not connected")
        return self._transport

    @property
    def link_state(self) -> LinkStateName:
        """The link state; "closed" after `close`."""
        return cast(LinkStateName, self._session.link_state())

    @property
    def remote_state(self) -> RemoteStateName:
        """The remote-control state."""
        return cast(RemoteStateName, self._session.remote_state())

    @property
    def reading(self) -> Reading | None:
        """The session's current reading; never None once connected."""
        t = self._session.latest_reading()
        return None if t is None else reading_from_native(t)

    @property
    def limits(self) -> Limits:
        """The user's limits last accepted."""
        return self._limits

    @property
    def dropped_readings(self) -> int:
        """Readings dropped: the core's count plus those `readings()` skipped."""
        return self._session.dropped_readings() + self._skipped

    @property
    def dropped_events(self) -> int:
        """Events dropped before `events()` returned them."""
        return self._session.events_overwritten()

    @property
    def counters(self) -> Counters | None:
        """The link's counters, once a link exists."""
        t = self._session.counters()
        return None if t is None else counters_from_native(t)

    @property
    def unclean_exit_warning(self) -> str | None:
        """The unclean-exit warning of this connection, or None."""
        return self._unclean

    @property
    def reconnect(self) -> bool:
        """Whether a lost link is reconnected; settable."""
        return self._reconnect

    @reconnect.setter
    def reconnect(self, on: bool) -> None:
        if not isinstance(on, bool):
            raise TypeError("reconnect must be a bool")
        self._check_open()
        self._session.set_reconnect(on)
        self._reconnect = on

    @property
    def closed(self) -> bool:
        """Whether `close` completed."""
        return self._closed

    # Control.

    def _check_open(self) -> None:
        """Raises `LinkLostError` on a closed object, without a native call."""
        if self._closed:
            raise LinkLostError(_CLOSED)

    def set_voltage(self, volts: float) -> None:
        """Sets the voltage setpoint.

        Requests remote control first when it is not held.

        Args:
            volts: The setpoint in V, from 0 to 30 and within the user limit.

        Raises:
            TypeError: When `volts` is not a real number.
            SetpointRangeError: When it is out of range; nothing is sent.
            Mp305Error: Or one of its subclasses, as the supply answers.
        """
        self._check_open()
        value = _checks.setpoint(
            "voltage", volts, _VOLT_SCALE, _native.SUPPLY_MAX_RAW_VOLTAGE, self._limits.max_voltage
        )
        self._session.set_voltage(value, self._handle)

    def set_current_limit(self, amps: float) -> None:
        """Sets the current limit.

        Requests remote control first when it is not held.

        Args:
            amps: The limit in A, from 0 to 5 and within the user limit.

        Raises:
            TypeError: When `amps` is not a real number.
            SetpointRangeError: When it is out of range; nothing is sent.
            Mp305Error: Or one of its subclasses, as the supply answers.
        """
        self._check_open()
        value = _checks.setpoint(
            "current", amps, _AMP_SCALE, _native.SUPPLY_MAX_RAW_CURRENT, self._limits.max_current
        )
        self._session.set_current_limit(value, self._handle)

    def set_limits(self, *, max_voltage: float | None, max_current: float | None) -> None:
        """Replaces both user limits; None means no user limit.

        Both arguments are required, so that a limit cannot be dropped by
        omission. On any error neither changes.

        Args:
            max_voltage: The highest voltage setpoint in V, or None.
            max_current: The highest current limit in A, or None.

        Raises:
            TypeError: For a limit that is not a real number or None.
            SetpointRangeError: For a limit outside the supply's range.
        """
        self._check_open()
        voltage, current = _limits(max_voltage, max_current)
        self._session.set_limits(voltage, current)
        self._limits = Limits(voltage, current)

    def output_on(self) -> None:
        """Switches the output on.

        Raises:
            FaultActiveError: While the supply reports a fault.
            Mp305Error: Or one of its subclasses, as the supply answers.
        """
        self._check_open()
        self._session.output_on(self._handle)

    def output_off(self) -> None:
        """Switches the output off, ahead of every queued command.

        After an interrupt the output-off continues in the background.

        Raises:
            Mp305Error: Or one of its subclasses, as the supply answers.
        """
        self._check_open()
        try:
            self._session.output_off(self._handle)
        except BaseException as error:
            if not isinstance(error, Exception):
                _log.warning("output_off interrupted; the output-off continues in the background")
            raise

    def request_remote_control(self) -> None:
        """Requests remote control; returns at once when it is held.

        Raises:
            RemoteControlDeniedError: When the supply denies it.
            Mp305Error: Or another subclass, as the supply answers.
        """
        self._check_open()
        self._session.request_remote_control(self._handle)

    def release_remote_control(self) -> None:
        """Releases remote control; returns at once when it was not requested.

        Raises:
            Mp305Error: Or one of its subclasses, as the supply answers.
        """
        self._check_open()
        self._session.release_remote_control(self._handle)

    # Readings and events.

    def _lost(self) -> LinkLostError:
        """The error of a lost or denied link, with the loss text."""
        return LinkLostError("link lost: " + (self._session.loss_text() or self.link_state))

    def _ended(self) -> bool:
        """Whether the object or the link is closed."""
        return self._closed or self._session.link_state() == "closed"

    def read(self, timeout: float = 2.0) -> Reading:
        """Waits for a reading newer than the current one and returns it.

        Args:
            timeout: How long to wait, 0.1 to 60 s.

        Returns:
            The first reading that arrives after the call.

        Raises:
            ValueError: For a timeout outside 0.1 to 60 s.
            LinkLostError: When the link is lost or closed.
            Mp305TimeoutError: When no reading arrives in time.
        """
        timeout = _checks.number("timeout", timeout, 0.1, 60.0)
        self._check_open()
        deadline = time.monotonic() + timeout
        current = self._session.latest_reading()
        base = None if current is None else current[0]
        while True:
            seq = self._session.feed_seq()
            t = self._session.latest_reading()
            if t is not None and (base is None or t[0] > base):
                return reading_from_native(t)
            state = self._session.link_state()
            if self._closed or state == "closed":
                raise LinkLostError(_CLOSED)
            if state in _TERMINAL:
                raise LinkLostError("link lost: " + (self._session.loss_text() or state))
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                raise Mp305TimeoutError(f"no new reading within {timeout} s")
            self._session.wait_feed(seq, _checks.wait_slice(remaining))

    def readings(self) -> Iterator[Reading]:
        """Every reading that arrives after the call, in arrival order.

        The iterator ends when the connection is closed, and raises
        `LinkLostError` with the loss text after everything queued before a
        loss was yielded.

        Returns:
            An iterator over the readings.

        Raises:
            LinkLostError: On a closed object.
        """
        self._check_open()
        return self._readings_from(self._session.newest_reading())

    def _readings_from(self, cursor: int) -> Iterator[Reading]:
        """The generator of `readings()` from reading number `cursor`."""
        warned = False
        while True:
            seq = self._session.feed_seq()
            items, cursor, skipped = self._session.readings_after(cursor, 64)
            if skipped > 0:
                self._skipped += skipped
                if not warned:
                    warned = True
                    _log.warning("readings() fell behind; %d readings were skipped", skipped)
            if items:
                for t in items:
                    yield reading_from_native(t)
                continue
            state = self._session.link_state()
            if self._closed or state == "closed":
                return
            if state in _TERMINAL:
                self._session.flush()
                while True:
                    items, cursor, skipped = self._session.readings_after(cursor, 64)
                    self._skipped += skipped
                    if not items:
                        break
                    for t in items:
                        yield reading_from_native(t)
                raise self._lost()
            self._session.wait_feed(seq, _native.WAIT_SLICE_S)

    def events(self) -> list[Event]:
        """Every event other than a reading not yet returned, in order.

        Returns:
            The events; each is returned once, also across threads.
        """
        self._session.pump(self._handle)
        return [event_from_native(t) for t in self._session.events_take(1024)]

    def _newer(self, last: int | None) -> Reading | None:
        """The current reading if it is newer than `last` (ns)."""
        t = self._session.latest_reading()
        if t is None or (last is not None and t[0] <= last):
            return None
        return reading_from_native(t)

    def _wait(self, seconds: float) -> None:
        """Waits `seconds` while pumping; returns early on a closed object or link."""
        deadline = time.monotonic() + seconds
        while not self._ended():
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                return
            self._session.wait_feed(self._session.feed_seq(), _checks.wait_slice(remaining))
            self._session.pump(self._handle)

    def _wait_newer(self, last: int | None, deadline: float) -> Reading | None:
        """Pumps until a reading newer than `last` arrives or `deadline` passes."""
        while True:
            seq = self._session.feed_seq()
            reading = self._newer(last)
            if reading is not None:
                return reading
            if self._ended():
                return None
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                return None
            self._session.wait_feed(seq, _checks.wait_slice(remaining))
            self._session.pump(self._handle)

    # The dispatcher.

    def _handle(self, t: EventTuple) -> None:
        """The dispatcher: called by the pump once per event, in order."""
        event = event_from_native(t)
        kind = event.kind
        if kind is EventKind.PROMPT:
            if self._on_prompt is not None:
                try:
                    self._on_prompt(event)
                except Exception as error:
                    _log.error("on_prompt failed: %r", error)
        elif kind is EventKind.UNCLEAN_EXIT_WARNING:
            self._unclean = event.text
            _log.warning("%s", event.text)
        elif kind is EventKind.BIND_RESULT:
            if event.recognised:
                _log.info("bind: host recognised")
            else:
                _log.info("bind: host confirmed on the supply")
        elif kind is EventKind.SETTINGS_CHANGED:
            _log.info("settings changed: %r", event.settings)
        elif kind is EventKind.SETPOINTS_CHANGED:
            _log.info(
                "setpoints differ: set %s V %s A, expected %s V %s A",
                event.set_voltage,
                event.set_current,
                event.expected_voltage,
                event.expected_current,
            )
        elif kind is EventKind.FAULTS_CHANGED:
            faults = sorted(event.faults or (), key=lambda f: cast(int, f.value))
            _log.info("faults: %s", ", ".join(f.text for f in faults) or "none")
        # REMOTE_CONTROL, LINK_LOST, RECONNECTED and RECONNECT_GAVE_UP are
        # logged by the core (DD-SESS-062), so every text reaches `logging`
        # once.

    # Closing.

    def close(self, output_off: bool = True) -> None:
        """Switches the output off, releases remote control and disconnects.

        With `output_off=False` the output is left as it is: the library only
        releases remote control and disconnects, and logs a warning, since the
        supply then keeps its output on with no host attached. The end of a
        `with` block, an interrupt and the exit hook always switch the output
        off; to leave it on, call `close(output_off=False)` as the last
        statement inside the block.

        Idempotent. After an interrupt, or any other exception that is not an
        `Mp305Error`, the close continues in the background, the object is
        closing (not closed), and a later `close` waits for the same sequence.

        Args:
            output_off: Whether to switch the output off before the release.

        Raises:
            TypeError: When `output_off` is not a bool.
            Mp305Error: Or one of its subclasses, when a step failed; the
                object is closed anyway.
        """
        if not isinstance(output_off, bool):
            raise TypeError("output_off must be a bool")
        if self._closed:
            return None
        if not output_off:
            _log.warning("close of %s leaves the output as it is", self._identifier)
        try:
            self._session.close(output_off, self._handle)
        except Mp305Error as error:
            self._closed = True
            _log.error("close of %s failed: %s", self._identifier, error)
            raise
        except BaseException:
            # Any other exception ends only the wait, as an interrupt does
            # (DD-PY-043): the close still runs on the runtime.
            self._closing = True
            _log.error(
                "close of %s interrupted; the close continues in the background "
                "and the process waits for it at exit",
                self._identifier,
            )
            raise
        self._closed = True
        return None

    def __enter__(self) -> Mp305:
        """Returns the device itself."""
        return self

    def __exit__(
        self,
        exc_type: type[BaseException] | None,
        exc: BaseException | None,
        tb: TracebackType | None,
    ) -> None:
        """Closes the device; never swallows the exception in flight.

        With an exception in flight, an `Mp305Error` of the close is logged
        (by `close`) and not raised, so the original exception propagates; any
        other exception propagates with the original as its `__context__`.
        """
        if exc_type is None:
            self.close()
            return None
        try:
            self.close()
        except Mp305Error:
            # `close` logged the error at ERROR; the original propagates.
            return None
        return None

    def __del__(self) -> None:
        """Warns when the device was neither closed nor closing; no device I/O."""
        try:
            if not getattr(self, "_closed", True) and not getattr(self, "_closing", True):
                _log.warning(
                    "Mp305 %s was not closed; the output stays as it is",
                    getattr(self, "_identifier", "?"),
                )
        except Exception:
            # A finalizer must not raise, also during interpreter shutdown.
            return

    # Test support.

    def _mock_sent(self) -> list[SentFrame]:
        """The frames the mock was given (test support)."""
        return [] if self._record is None else self._record.sent()

    def _mock_closes(self) -> int:
        """How often the mock was closed (test support)."""
        return 0 if self._record is None else self._record.closes()


def _limits(max_voltage: object, max_current: object) -> tuple[float | None, float | None]:
    """Checks both user limits; neither is used when one fails."""
    return (
        _checks.limit("voltage limit", max_voltage, VOLTAGE_RANGE[1]),
        _checks.limit("current limit", max_current, CURRENT_RANGE[1]),
    )
