"""Typed readings, events and records of the mp305 library.

Implements: DD-PY-020, DD-PY-021, DD-PY-022 (the Python side of the native
boundary).

Every dataclass here is immutable and hashable. The enum values are pinned,
so that the native side and the CSV agree on them.
"""

from __future__ import annotations

import enum
from collections.abc import Mapping
from dataclasses import dataclass
from typing import TYPE_CHECKING, Literal, cast

if TYPE_CHECKING:
    from mp305._native import (
        CountersTuple,
        EventTuple,
        FoundTuple,
        InfoTuple,
        ReadingTuple,
        SentTuple,
    )

Transport = Literal["ble", "hid"]
"""The link a supply is reached over: Bluetooth LE or USB HID."""

LinkStateName = Literal[
    "connecting",
    "connected",
    "binding",
    "allowed",
    "ready",
    "denied",
    "lost",
    "reconnecting",
    "closed",
]
"""The link states of a connection."""

RemoteStateName = Literal["none", "requested", "granted", "denied", "lost"]
"""The remote-control states of a connection."""

PromptKind = Literal["confirm_connection", "allow_remote_control"]
"""The prompts the supply shows on its screen."""

Quantity = Literal["voltage", "current"]
"""The quantity a ramp steps through."""


class Mode(enum.Enum):
    """How the output regulates (the `mode` column of the CSV)."""

    OFF = "off"
    CV = "cv"
    CC = "cc"
    HELD_ABOVE = "held_above"
    UNKNOWN = "unknown"


class LiveMode(enum.Enum):
    """The supply's live mode; only DC is controlled in this version."""

    DC = "dc"
    PROGRAM = "program"
    PD = "pd"
    CHARGE = "charge"
    UNKNOWN = "unknown"


_FAULT_TEXTS = {
    0: "reversed output",
    1: "low battery",
    2: "battery too cold",
    3: "battery overheat",
    4: "system overheat",
    5: "over current",
    6: "over voltage",
    7: "power stage start failure",
    8: "output voltage sensor failure",
}


class Fault(enum.Enum):
    """One fault bit of the supply; the value is the bit number."""

    REVERSED_OUTPUT = 0
    LOW_BATTERY = 1
    BATTERY_TOO_COLD = 2
    BATTERY_OVERHEAT = 3
    SYSTEM_OVERHEAT = 4
    OVER_CURRENT = 5
    OVER_VOLTAGE = 6
    POWER_STAGE_START_FAILURE = 7
    OUTPUT_VOLTAGE_SENSOR_FAILURE = 8
    UNKNOWN_BIT_9 = 9
    UNKNOWN_BIT_10 = 10
    UNKNOWN_BIT_11 = 11
    UNKNOWN_BIT_12 = 12
    UNKNOWN_BIT_13 = 13
    UNKNOWN_BIT_14 = 14
    UNKNOWN_BIT_15 = 15

    @property
    def text(self) -> str:
        """The fault as the core names it, for example "over current"."""
        bit: int = self.value
        return _FAULT_TEXTS.get(bit, f"unknown fault bit {bit}")


def faults_from_word(word: int) -> frozenset[Fault]:
    """The faults of a fault word, one member per set bit.

    Args:
        word: The 16-bit `chargeError` word of a reading.

    Returns:
        The faults whose bits are set.
    """
    return frozenset(Fault(bit) for bit in range(16) if (word >> bit) & 1)


@dataclass(frozen=True, slots=True)
class Reading:
    """One reading of the supply (SR-033).

    Attributes:
        timestamp: Arrival time in seconds since the epoch (`wall_ns / 1e9`).
        voltage: Measured output voltage in V.
        current: Measured output current in A.
        power: Output power in W.
        set_voltage: Voltage setpoint in V.
        set_current: Current limit in A.
        output_on: Whether the power stage output is on.
        mode: How the output regulates.
        mode_raw: The raw `outState` value (SR-015).
        mode_text: The regulation as the core names it ("CV", "unknown (9)").
        live_mode: The supply's live mode.
        live_mode_raw: The raw `model` value.
        faults: The active faults.
        temperature: Battery protection temperature in °C.
        energy: Energy delivered in Wh.
        working_time: Output-on time in s.
        raw: The 36 payload bytes as received.
        wall_ns: The exact arrival time in ns since the epoch; per session it
            increases with the arrival.
    """

    timestamp: float
    voltage: float
    current: float
    power: float
    set_voltage: float
    set_current: float
    output_on: bool
    mode: Mode
    mode_raw: int
    mode_text: str
    live_mode: LiveMode
    live_mode_raw: int
    faults: frozenset[Fault]
    temperature: int
    energy: float
    working_time: int
    raw: bytes
    wall_ns: int


def reading_from_native(t: ReadingTuple) -> Reading:
    """Builds a `Reading` from the native reading tuple.

    Args:
        t: The tuple `convert::reading` builds.

    Returns:
        The reading.
    """
    (
        wall_ns,
        raw,
        voltage,
        current,
        power,
        set_voltage,
        set_current,
        output_on,
        mode,
        mode_raw,
        mode_text,
        live_mode,
        live_mode_raw,
        faults,
        temperature,
        energy,
        working_time,
    ) = t
    return Reading(
        timestamp=wall_ns / 1e9,
        voltage=voltage,
        current=current,
        power=power,
        set_voltage=set_voltage,
        set_current=set_current,
        output_on=output_on,
        mode=Mode(mode),
        mode_raw=mode_raw,
        mode_text=mode_text,
        live_mode=LiveMode(live_mode),
        live_mode_raw=live_mode_raw,
        faults=faults_from_word(faults),
        temperature=temperature,
        energy=energy,
        working_time=working_time,
        raw=raw,
        wall_ns=wall_ns,
    )


@dataclass(frozen=True, slots=True)
class Info:
    """What the supply reports about itself.

    Attributes:
        model: The model string, "MP305B".
        version: The firmware version as "a.b.c.d".
        hardware: The hardware revision (Bluetooth only).
        bootloader: Eight raw bytes from the bootloader (USB only).
        name: The name field (USB only).
    """

    model: str
    version: str
    hardware: str | None
    bootloader: bytes | None
    name: str | None


def info_from_native(t: InfoTuple) -> Info:
    """Builds an `Info` from the native info tuple.

    Args:
        t: The tuple `(model, version, hardware, bootloader, name)`.

    Returns:
        The info.
    """
    model, version, hardware, bootloader, name = t
    return Info(model=model, version=version, hardware=hardware, bootloader=bootloader, name=name)


@dataclass(frozen=True, slots=True)
class Found:
    """A supply that discovery found.

    Attributes:
        transport: The link it was found on.
        identifier: What `Mp305.connect` takes.
        unit_id: The unit characters (Bluetooth) or the HID path (USB).
        name: The advertised name or the USB product string.
        rssi: The signal strength in dBm, over Bluetooth when reported.
        remote_flag: Whether the advertised name carries the remote flag.
        description: One line naming the supply.
    """

    transport: Transport
    identifier: str
    unit_id: str
    name: str
    rssi: int | None
    remote_flag: bool | None
    description: str

    def __str__(self) -> str:
        """The description line."""
        return self.description


def found_from_native(t: FoundTuple) -> Found:
    """Builds a `Found` from the native found tuple.

    Args:
        t: The tuple `(transport, identifier, unit_id, name, rssi,
            remote_flag, description)`.

    Returns:
        The found supply.
    """
    transport, identifier, unit_id, name, rssi, remote_flag, description = t
    return Found(
        transport=cast(Transport, transport),
        identifier=identifier,
        unit_id=unit_id,
        name=name,
        rssi=rssi,
        remote_flag=remote_flag,
        description=description,
    )


@dataclass(frozen=True)
class Limits:
    """The user's own limits on top of the supply's range (UR-007).

    Attributes:
        max_voltage: The highest voltage setpoint allowed in V, or None.
        max_current: The highest current limit allowed in A, or None.
    """

    max_voltage: float | None
    max_current: float | None


@dataclass(frozen=True, slots=True)
class Settings:
    """The supply's settings as it reports them.

    Attributes:
        charge_limit: Battery charge limit in %.
        volume: Buzzer volume, 0 to 3.
        screen_off: Screen-off setting.
        shutdown: Auto shutdown in min.
        screen_direction: Display orientation.
        ramp_step: Ramp step in mV per 100 ms.
        ocp_delay: OCP delay in ms.
        usb_line_drop: USB line drop compensation.
    """

    charge_limit: int
    volume: int
    screen_off: int
    shutdown: int
    screen_direction: int
    ramp_step: int
    ocp_delay: int
    usb_line_drop: int


@dataclass(frozen=True)
class Counters:
    """The link's counters.

    Attributes:
        dropped_frames: Frames dropped as malformed.
        ignored: Frames that were neither a reply nor an event.
        late_replies: Replies that arrived after their bound.
    """

    dropped_frames: int
    ignored: int
    late_replies: int


def counters_from_native(t: CountersTuple) -> Counters:
    """Builds `Counters` from the native counters tuple.

    Args:
        t: The tuple `(dropped_frames, ignored, late_replies)`.

    Returns:
        The counters.
    """
    dropped_frames, ignored, late_replies = t
    return Counters(dropped_frames=dropped_frames, ignored=ignored, late_replies=late_replies)


@dataclass(frozen=True)
class SentFrame:
    """A frame the mock transport was given (test support).

    Attributes:
        attempt: The index of the mock, one per connection attempt.
        time: Seconds after the record was made.
        route: "af01", "af02" or "hid".
        opcode: The request opcode.
        payload: The payload bytes.
    """

    attempt: int
    time: float
    route: str
    opcode: int
    payload: bytes


def sent_from_native(t: SentTuple) -> SentFrame:
    """Builds a `SentFrame` from the native sent tuple.

    Args:
        t: The tuple `(attempt, time_s, route, opcode, payload)`.

    Returns:
        The sent frame.
    """
    attempt, time, route, opcode, payload = t
    return SentFrame(attempt=attempt, time=time, route=route, opcode=opcode, payload=payload)


class EventKind(enum.Enum):
    """The kinds of events a connection reports (all but readings)."""

    FAULTS_CHANGED = "faults_changed"
    SETTINGS_CHANGED = "settings_changed"
    BIND_RESULT = "bind_result"
    REMOTE_CONTROL = "remote_control"
    PROMPT = "prompt"
    SETPOINTS_CHANGED = "setpoints_changed"
    UNCLEAN_EXIT_WARNING = "unclean_exit_warning"
    LINK_LOST = "link_lost"
    RECONNECTED = "reconnected"
    RECONNECT_GAVE_UP = "reconnect_gave_up"


@dataclass(frozen=True, slots=True)
class Event:
    """One event of a connection; fields the kind does not set are None.

    Attributes:
        seq: The sequence number among all events of the connection.
        kind: What happened.
        reading: The reading that shows changed faults.
        faults: The active faults after a change.
        settings: The settings after a change on the front panel.
        recognised: Whether the supply recognised this host at the bind.
        remote_state: The new remote-control state.
        prompt: Which prompt the supply shows.
        bound_s: How long the prompt waits, in s.
        text: The prompt, warning, loss or give-up text.
        set_voltage: The voltage setpoint the supply reports, in V.
        set_current: The current limit the supply reports, in A.
        expected_voltage: The voltage setpoint expected, in V.
        expected_current: The current limit expected, in A.
        since: When the unclean-exit marker was written, in seconds since
            the epoch.
    """

    seq: int
    kind: EventKind
    reading: Reading | None = None
    faults: frozenset[Fault] | None = None
    settings: Settings | None = None
    recognised: bool | None = None
    remote_state: RemoteStateName | None = None
    prompt: PromptKind | None = None
    bound_s: int | None = None
    text: str | None = None
    set_voltage: float | None = None
    set_current: float | None = None
    expected_voltage: float | None = None
    expected_current: float | None = None
    since: float | None = None


_PAYLOAD_KEYS: dict[EventKind, frozenset[str]] = {
    EventKind.FAULTS_CHANGED: frozenset({"faults", "reading"}),
    EventKind.SETTINGS_CHANGED: frozenset({"settings"}),
    EventKind.BIND_RESULT: frozenset({"recognised"}),
    EventKind.REMOTE_CONTROL: frozenset({"remote_state"}),
    EventKind.PROMPT: frozenset({"prompt", "bound_s", "text"}),
    EventKind.SETPOINTS_CHANGED: frozenset(
        {"set_voltage", "set_current", "expected_voltage", "expected_current"}
    ),
    EventKind.UNCLEAN_EXIT_WARNING: frozenset({"since", "text"}),
    EventKind.LINK_LOST: frozenset({"text"}),
    EventKind.RECONNECTED: frozenset(),
    EventKind.RECONNECT_GAVE_UP: frozenset({"text"}),
}

_SETTINGS_KEYS = (
    "charge_limit",
    "volume",
    "screen_off",
    "shutdown",
    "screen_direction",
    "ramp_step",
    "ocp_delay",
    "usb_line_drop",
)

_REMOTE_STATES = ("none", "requested", "granted", "denied", "lost")
_PROMPTS = ("confirm_connection", "allow_remote_control")


def _keys(where: str, payload: Mapping[str, object], expected: frozenset[str]) -> None:
    """Raises ValueError naming a missing or an extra key."""
    for key in sorted(expected):
        if key not in payload:
            raise ValueError(f"{where} lacks the key {key!r}")
    for key in payload:
        if key not in expected:
            raise ValueError(f"{where} has the extra key {key!r}")


def _int(where: str, payload: Mapping[str, object], key: str) -> int:
    """The int under `key`, or ValueError."""
    value = payload[key]
    if not isinstance(value, int) or isinstance(value, bool):
        raise ValueError(f"{where}: {key!r} is not an int")
    return value


def _float(where: str, payload: Mapping[str, object], key: str) -> float:
    """The float under `key`, or ValueError."""
    value = payload[key]
    if not isinstance(value, float):
        raise ValueError(f"{where}: {key!r} is not a float")
    return value


def _str(where: str, payload: Mapping[str, object], key: str) -> str:
    """The str under `key`, or ValueError."""
    value = payload[key]
    if not isinstance(value, str):
        raise ValueError(f"{where}: {key!r} is not a str")
    return value


def _settings(where: str, value: object) -> Settings:
    """The settings dict as `Settings`, or ValueError."""
    if not isinstance(value, dict):
        raise ValueError(f"{where}: 'settings' is not a dict")
    payload = cast("dict[str, object]", value)
    _keys(f"{where} settings", payload, frozenset(_SETTINGS_KEYS))
    return Settings(*(_int(where, payload, key) for key in _SETTINGS_KEYS))


def event_from_native(t: EventTuple) -> Event:
    """Builds an `Event` from the native event tuple, strictly.

    Args:
        t: The tuple `(seq, kind, payload)` `convert::event` builds.

    Returns:
        The event.

    Raises:
        ValueError: For an unknown kind, a missing or an extra payload key,
            or a value of the wrong type, naming it.
    """
    seq, kind_name, payload = t
    try:
        kind = EventKind(kind_name)
    except ValueError:
        raise ValueError(f"unknown event kind {kind_name!r}") from None
    where = f"event {kind_name}"
    _keys(where, payload, _PAYLOAD_KEYS[kind])
    if kind is EventKind.FAULTS_CHANGED:
        reading = payload["reading"]
        if not isinstance(reading, tuple):
            raise ValueError(f"{where}: 'reading' is not a tuple")
        return Event(
            seq=seq,
            kind=kind,
            faults=faults_from_word(_int(where, payload, "faults")),
            reading=reading_from_native(cast("ReadingTuple", reading)),
        )
    if kind is EventKind.SETTINGS_CHANGED:
        return Event(seq=seq, kind=kind, settings=_settings(where, payload["settings"]))
    if kind is EventKind.BIND_RESULT:
        recognised = payload["recognised"]
        if not isinstance(recognised, bool):
            raise ValueError(f"{where}: 'recognised' is not a bool")
        return Event(seq=seq, kind=kind, recognised=recognised)
    if kind is EventKind.REMOTE_CONTROL:
        state = _str(where, payload, "remote_state")
        if state not in _REMOTE_STATES:
            raise ValueError(f"{where}: unknown remote state {state!r}")
        return Event(seq=seq, kind=kind, remote_state=cast(RemoteStateName, state))
    if kind is EventKind.PROMPT:
        prompt = _str(where, payload, "prompt")
        if prompt not in _PROMPTS:
            raise ValueError(f"{where}: unknown prompt {prompt!r}")
        return Event(
            seq=seq,
            kind=kind,
            prompt=cast(PromptKind, prompt),
            bound_s=_int(where, payload, "bound_s"),
            text=_str(where, payload, "text"),
        )
    if kind is EventKind.SETPOINTS_CHANGED:
        return Event(
            seq=seq,
            kind=kind,
            set_voltage=_float(where, payload, "set_voltage"),
            set_current=_float(where, payload, "set_current"),
            expected_voltage=_float(where, payload, "expected_voltage"),
            expected_current=_float(where, payload, "expected_current"),
        )
    if kind is EventKind.UNCLEAN_EXIT_WARNING:
        return Event(
            seq=seq,
            kind=kind,
            since=_float(where, payload, "since"),
            text=_str(where, payload, "text"),
        )
    if kind is EventKind.RECONNECTED:
        return Event(seq=seq, kind=kind)
    # LINK_LOST and RECONNECT_GAVE_UP carry only their text.
    return Event(seq=seq, kind=kind, text=_str(where, payload, "text"))
