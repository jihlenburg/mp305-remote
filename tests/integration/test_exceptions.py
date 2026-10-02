"""IT-050 (Python part): every core `Error` variant reaches Python as AR-050 maps it.

The other part of IT-050, each variant to the app's message, is
`crates/mp305-core/tests/it_errors.rs` and not in this file.
"""

from __future__ import annotations

import re

import pytest

from mp305 import (
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
from tests.integration import core_errors

AR_050: dict[str, type[Mp305Error]] = {
    # The first eleven map to the exceptions of SR-032 one to one, NotReady
    # to the base class.
    "NotFound": NotFoundError,
    "ConnectionDenied": ConnectionDeniedError,
    "RemoteControlDenied": RemoteControlDeniedError,
    "RemoteControlLost": RemoteControlLostError,
    "SetpointRange": SetpointRangeError,
    "CommandRejected": CommandRejectedError,
    "Mode": ModeError,
    "FaultActive": FaultActiveError,
    "NotReady": Mp305Error,
    "Timeout": Mp305TimeoutError,
    "LinkLost": LinkLostError,
    # The other five.
    "Transport": LinkLostError,
    "Store": Mp305Error,
    "Protocol": Mp305Error,
    "AlreadyOpen": Mp305Error,
    "Cancelled": Mp305Error,
}
"""The `Error` variants of AR-050, in its order, with the class each maps to."""


@pytest.mark.spec("IT-050")
def test_the_mapping_is_total() -> None:
    assert len(AR_050) == 16
    assert list(core_errors.VARIANTS) == list(AR_050)
    first_eleven = list(AR_050.values())[:11]
    assert first_eleven.count(Mp305Error) == 1
    assert len(set(first_eleven)) == 11
    assert all(issubclass(c, Mp305Error) for c in AR_050.values())


@pytest.mark.spec("IT-050")
@pytest.mark.parametrize("variant", list(AR_050))
def test_every_variant_occurs_and_maps_as_ar_050_says(variant: str) -> None:
    trigger, text = core_errors.VARIANTS[variant]
    error = trigger(f"IT-050-{variant}")
    # The text is the core's for this variant, so this variant occurred.
    assert re.fullmatch(text, str(error)), (variant, str(error))
    assert type(error) is AR_050[variant]


@pytest.mark.spec("IT-050")
def test_not_found_carries_the_four_causes() -> None:
    trigger, _ = core_errors.VARIANTS["NotFound"]
    error = trigger("IT-050-causes")
    assert type(error) is NotFoundError
    text = str(error)
    positions = [text.find(cause) for cause in core_errors.SR_005_CAUSES]
    assert all(p >= 0 for p in positions), text
    assert positions == sorted(positions)
