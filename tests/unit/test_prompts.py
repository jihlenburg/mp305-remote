"""UT-PY-007: prompts reach the callback and `logging` while a call waits."""

from __future__ import annotations

import logging
import threading
import time
from collections.abc import Callable
from typing import Any

import pytest

from mp305 import Event, EventKind, Mp305, testing
from tests.unit import frames
from tests.unit.support import messages, records, reply, script

Factory = Callable[..., Mp305]
CONFIRM = "Confirm the connection on the supply's screen within 30 seconds"
ALLOW = "Allow remote control on the supply's screen"


def prompt_bind_script() -> dict[str, Any]:
    """Fast bind answered `19 FF`, the prompt bind `19 00` after 600 ms."""
    return script(replies=[reply(0x18, b"\xff", repeat=1), reply(0x18, b"\x00", after_s=0.6)])


class Recorder:
    """An `on_prompt` that records each call."""

    def __init__(self, error: BaseException | None = None) -> None:
        self.calls: list[tuple[Event, float, int]] = []
        self.error = error

    def __call__(self, event: Event) -> None:
        self.calls.append((event, time.monotonic(), threading.get_ident()))
        if self.error is not None:
            raise self.error


def text_records(caplog: pytest.LogCaptureFixture, text: str) -> list[logging.LogRecord]:
    """Every captured record whose message is `text`."""
    return [r for r in caplog.records if r.getMessage() == text]


@pytest.mark.spec("UT-PY-007")
def test_a_confirm_connection(mock_device: Factory, caplog: pytest.LogCaptureFixture) -> None:
    cb = Recorder()
    dev = mock_device([prompt_bind_script()], identifier="UT-PY-007-a", on_prompt=cb)
    returned = time.monotonic()
    found = text_records(caplog, CONFIRM)
    assert len(cb.calls) == 1
    event, at, thread = cb.calls[0]
    assert event.kind is EventKind.PROMPT
    assert event.prompt == "confirm_connection"
    assert event.bound_s == 30
    assert thread == threading.get_ident()
    assert returned - at >= 0.3
    assert len(found) == 1
    assert found[0].levelno == logging.WARNING
    assert found[0].name == "mp305.core.session"
    assert dev.link_state == "ready"


@pytest.mark.spec("UT-PY-007")
def test_b_allow_remote_control(mock_device: Factory, caplog: pytest.LogCaptureFixture) -> None:
    cb = Recorder()
    rec = testing.MockRecord()
    s = testing.default_script()
    s["replies"].insert(0, reply(0xC8, b"\x00", after_s=0.6, repeat=1))  # type: ignore[typeddict-item]
    dev = mock_device([s], identifier="UT-PY-007-b", on_prompt=cb, record=rec)
    dev.set_voltage(1.0)
    returned = time.monotonic()
    assert len(cb.calls) == 1
    event, at, thread = cb.calls[0]
    assert event.prompt == "allow_remote_control"
    assert event.bound_s == 70
    assert thread == threading.get_ident()
    assert returned - at >= 0.3
    found = text_records(caplog, ALLOW)
    assert len(found) == 1
    assert (found[0].levelno, found[0].name) == (logging.WARNING, "mp305.core.session")
    sent = frames.c8(rec.sent())
    assert [(c.remote_con, c.set_voltage) for c in sent] == [(2, 1300), (1, 100)]


@pytest.mark.spec("UT-PY-007")
def test_c_a_failing_callback_does_not_abort_the_bind(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    cb = Recorder(RuntimeError("cb"))
    dev = mock_device([prompt_bind_script()], identifier="UT-PY-007-c", on_prompt=cb)
    assert dev.link_state == "ready"
    errors = messages(caplog, "mp305", logging.ERROR)
    assert len(errors) == 1
    assert errors[0].startswith("on_prompt failed: RuntimeError")
    assert records(caplog, "mp305", logging.ERROR)[0].name == "mp305"
