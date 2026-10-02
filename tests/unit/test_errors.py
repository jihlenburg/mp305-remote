"""UT-PY-003: the exception classes."""

from __future__ import annotations

import copy
import math
import pickle

import pytest

from mp305 import errors
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
from mp305.types import Fault, Found

FOUND = Found(
    transport="ble",
    identifier="id1",
    unit_id="E!K",
    name="0000MP305B  S             E!K",
    rssi=-61,
    remote_flag=True,
    description="ble id1 0000MP305B  S             E!K (unit E!K)",
)

CASES: list[tuple[Mp305Error, dict[str, object]]] = [
    (Mp305Error("m"), {}),
    (NotFoundError("m", found=(FOUND,)), {"found": (FOUND,)}),
    (ConnectionDeniedError("m"), {}),
    (CommandRejectedError("m", status=255, reason="busy"), {"status": 255, "reason": "busy"}),
    (RemoteControlDeniedError("m"), {}),
    (RemoteControlLostError("m"), {}),
    (ModeError("m", live_mode_raw=2), {"live_mode_raw": 2}),
    (
        FaultActiveError("m", faults=frozenset({Fault.OVER_CURRENT})),
        {"faults": frozenset({Fault.OVER_CURRENT})},
    ),
    (
        SetpointRangeError("m", field="voltage", value=31.0, minimum=0.0, maximum=30.0),
        {"field": "voltage", "value": 31.0, "minimum": 0.0, "maximum": 30.0},
    ),
    (Mp305TimeoutError("m"), {}),
    (LinkLostError("m"), {}),
]


@pytest.mark.spec("UT-PY-003")
def test_classes_bases_messages_and_round_trips() -> None:
    assert len(CASES) == 11
    assert errors.__name__ == "mp305.errors"
    for error, attributes in CASES:
        cls = type(error)
        assert issubclass(cls, Mp305Error)
        assert error.args == ("m",)
        assert str(error) == "m"
        for name, value in attributes.items():
            assert getattr(error, name) == value
        for twin in (pickle.loads(pickle.dumps(error)), copy.copy(error)):  # noqa: S301
            assert type(twin) is cls
            assert twin.args == ("m",)
            for name, value in attributes.items():
                assert getattr(twin, name) == value
    assert issubclass(SetpointRangeError, ValueError)
    assert issubclass(Mp305TimeoutError, TimeoutError)
    assert issubclass(LinkLostError, ConnectionError)
    assert Mp305TimeoutError("m").errno is None
    assert LinkLostError("m").errno is None


@pytest.mark.spec("UT-PY-003")
def test_attribute_defaults() -> None:
    rejected = CommandRejectedError("m")
    assert rejected.status == 0
    assert rejected.reason == ""
    out_of_range = SetpointRangeError("m")
    assert out_of_range.field == ""
    assert out_of_range.minimum == 0.0
    assert math.isnan(out_of_range.value)
