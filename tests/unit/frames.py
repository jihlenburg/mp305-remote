"""Reads the fields of sent `0xC8` frames for the unit tests.

The payload layout of `protocol::ops::control`: `remoteCon` at 0,
`set_voltage` at 1 and 2, `set_current` at 3 and 4, `output` at 8, little
endian.
"""

from __future__ import annotations

from collections.abc import Iterable
from dataclasses import dataclass

from mp305.types import SentFrame


@dataclass(frozen=True)
class Control:
    """The fields of one sent `0xC8`."""

    remote_con: int
    set_voltage: int
    set_current: int
    output: int


def control(payload: bytes) -> Control:
    """The fields of a `0xC8` payload."""
    return Control(
        remote_con=payload[0],
        set_voltage=int.from_bytes(payload[1:3], "little"),
        set_current=int.from_bytes(payload[3:5], "little"),
        output=payload[8],
    )


def sent(frames: Iterable[SentFrame], opcode: int) -> list[SentFrame]:
    """The frames with `opcode`, in order."""
    return [f for f in frames if f.opcode == opcode]


def c8(frames: Iterable[SentFrame]) -> list[Control]:
    """The fields of every sent `0xC8`, in order."""
    return [control(f.payload) for f in sent(frames, 0xC8)]


def as_dicts(frames: Iterable[SentFrame]) -> list[dict[str, object]]:
    """Sent frames as JSON-friendly dicts, for a child process's report."""
    return [
        {"attempt": f.attempt, "route": f.route, "opcode": f.opcode, "payload": f.payload.hex()}
        for f in frames
    ]


def from_dicts(items: Iterable[dict[str, object]]) -> list[SentFrame]:
    """The inverse of `as_dicts` (the times are lost)."""
    return [
        SentFrame(
            attempt=int(str(d["attempt"])),
            time=0.0,
            route=str(d["route"]),
            opcode=int(str(d["opcode"])),
            payload=bytes.fromhex(str(d["payload"])),
        )
        for d in items
    ]
