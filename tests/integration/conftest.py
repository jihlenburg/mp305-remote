"""Fixtures of the Python integration tests (IT-003, IT-040, IT-050)."""

from __future__ import annotations

import logging
from collections.abc import Callable, Iterator
from typing import Any

import pytest

from mp305 import Mp305, testing

_log = logging.getLogger("tests")


@pytest.fixture
def mock_device() -> Iterator[Callable[..., Mp305]]:
    """A factory over `Mp305._from_mock` that closes every device at teardown.

    Each test passes its own identifier, since the session registry is
    process-wide; a close error at teardown is logged at WARNING, not raised.
    """
    devices: list[Mp305] = []

    def make(scripts: list[Any] | None = None, **kwargs: Any) -> Mp305:
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
