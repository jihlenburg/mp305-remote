"""Fixtures of the Python unit tests (DD-PY-064)."""

from __future__ import annotations

import itertools
import logging
from collections.abc import Callable, Iterator
from typing import Any

import pytest

import mp305
from mp305 import Mp305, testing

_log = logging.getLogger("tests")


@pytest.fixture
def mock_device(request: pytest.FixtureRequest) -> Iterator[Callable[..., Mp305]]:
    """A factory over `Mp305._from_mock` that closes every device at teardown.

    The identifier defaults to the test's spec ID plus a counter; a close
    error at teardown is logged at WARNING, not raised.
    """
    marker = request.node.get_closest_marker("spec")
    spec = marker.args[0] if marker is not None else request.node.name
    numbers = itertools.count(1)
    devices: list[Mp305] = []

    def make(scripts: list[Any] | None = None, **kwargs: Any) -> Mp305:
        kwargs.setdefault("identifier", f"{spec}-{next(numbers)}")
        if scripts is None:
            scripts = [testing.default_script()]
        device = Mp305._from_mock(scripts, **kwargs)
        devices.append(device)
        return device

    yield make
    for device in devices:
        try:
            device.close()
        except Exception as error:
            _log.warning("close of %s at teardown failed: %s", device.identifier, error)


@pytest.fixture(autouse=True)
def _restore_log_level() -> Iterator[None]:
    """Restores `set_log_level(30)` after each test."""
    yield
    mp305.set_log_level(30)
