"""UT-PY-009: the log bridge from the Rust core to `logging`."""

from __future__ import annotations

import logging
import math
import pathlib
import re
import time
from collections.abc import Callable

import pytest

import mp305
from mp305 import Mp305, _native
from tests.unit.support import messages, records, reply, script, wait_until

Factory = Callable[..., Mp305]
FRAMES = [
    r"^tx ble AF02 \+\d+ 18 ",
    r"^rx ble AF02 \+\d+ 19 00$",
    r"^tx ble AF01 \+\d+ e0$",
    r"^rx ble AF01 \+\d+ e1 ",
    r"^tx ble AF01 \+\d+ c2$",
    r"^rx ble AF01 \+\d+ c3 ",
]
NATIVE = ("mp305.core", "mp305.native", "mp305.deps")


def in_order(lines: list[str], patterns: list[str]) -> bool:
    """Whether `patterns` match a subsequence of `lines`, in order."""
    position = 0
    for pattern in patterns:
        while position < len(lines) and not re.search(pattern, lines[position]):
            position += 1
        if position == len(lines):
            return False
        position += 1
    return True


@pytest.mark.spec("UT-PY-009")
def test_a_b_the_frame_log(mock_device: Factory, caplog: pytest.LogCaptureFixture) -> None:
    caplog.set_level(5)
    mp305.set_log_level(5)
    mock_device(identifier="UT-PY-009-a")
    # The records may still be on their way from the delivery thread.
    wait_until(lambda: in_order(messages(caplog, "mp305.core.frames", 5), FRAMES), 2.0)
    frames = messages(caplog, "mp305.core.frames", 5)
    assert in_order(frames, FRAMES), frames[:12]
    assert logging.getLevelName(5) == "TRACE"
    assert logging.getLogger("mp305.core").level == 5
    # (b): with the gate back at WARNING, the second device's native records
    # stay at WARNING and above. The library's own INFO records on `mp305`
    # come from Python logging and are not gated by `set_log_level`.
    mp305.set_log_level(30)
    # Let every TRACE record queued before the gate closed be delivered (the
    # delivery thread waits at most 0.25 s per turn), then start afresh.
    time.sleep(0.5)
    _native.log_wait(0.0)
    caplog.clear()
    mock_device(identifier="UT-PY-009-b")
    _native.log_wait(0.0)
    native = [r for r in caplog.records if r.name.startswith(NATIVE)]
    assert [r for r in native if r.levelno < logging.WARNING] == []


@pytest.mark.spec("UT-PY-009")
def test_c_records_arrive_without_a_blocking_call(
    tmp_path: pathlib.Path, caplog: pytest.LogCaptureFixture
) -> None:
    (tmp_path / "host_id").write_text("zz\n")
    mp305.host_id(tmp_path)

    def replaced() -> list[logging.LogRecord]:
        return [
            r
            for r in records(caplog, "mp305.core.store", logging.WARNING)
            if r.getMessage() == "host id replaced: length 2"
        ]

    found = wait_until(replaced, 1.0)
    assert len(found) == 1
    assert found[0].threadName == "mp305-log"


@pytest.mark.spec("UT-PY-009")
def test_d_warnings_cannot_be_switched_off(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    mp305.set_log_level(50)
    assert logging.getLogger("mp305.core").level == 30
    s = script(replies=[reply(0x18, b"\xff", repeat=1), reply(0x18, b"\x00", after_s=0.6)])
    mock_device([s], identifier="UT-PY-009-d")
    text = "Confirm the connection on the supply's screen within 30 seconds"
    assert wait_until(
        lambda: text in messages(caplog, "mp305.core.session", logging.WARNING), 1.0
    )


@pytest.mark.spec("UT-PY-009")
def test_e_a_burst_beyond_the_queue(caplog: pytest.LogCaptureFixture) -> None:
    mp305.set_log_level(30)
    # Let every TRACE record queued before the gate closed be delivered (the
    # delivery thread waits at most 0.25 s per turn), then start afresh.
    time.sleep(0.5)
    _native.log_wait(0.0)
    caplog.clear()
    _native.log_test("mp305_py::test", 30, "burst", 5000)

    def burst() -> int:
        return len(records(caplog, "mp305.native.test"))

    wait_until(lambda: burst() >= 4096 and messages(caplog, "mp305.native"), 2.0)
    assert burst() == 4096
    assert set(messages(caplog, "mp305.native.test")) == {"burst"}
    assert messages(caplog, "mp305.native", logging.WARNING) == ["904 log records were dropped"]


@pytest.mark.spec("UT-PY-009")
def test_f_log_wait() -> None:
    start = time.monotonic()
    _native.log_wait(0.3)
    elapsed = time.monotonic() - start
    assert 0.3 <= elapsed <= 0.45
    with pytest.raises(ValueError):
        _native.log_wait(math.nan)
    with pytest.raises(ValueError):
        _native.log_wait(61)
