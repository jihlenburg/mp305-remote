"""UT-PY-006: blocking calls release the GIL, serialise, and stop on Ctrl-C."""

from __future__ import annotations

import threading
from collections.abc import Callable

import pytest

from mp305 import Mp305, testing
from tests.unit import frames
from tests.unit.support import reply, run_child, script

Factory = Callable[..., Mp305]


@pytest.mark.spec("UT-PY-006")
def test_a_the_gil_is_released(mock_device: Factory) -> None:
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\x00", after_s=0.3)])
    dev = mock_device([s], identifier="UT-PY-006-a")
    count = 0
    running = True

    def counter() -> None:
        nonlocal count
        while running:
            count += 1

    thread = threading.Thread(target=counter)
    thread.start()
    try:
        before = count
        dev.set_voltage(1.0)
        during = count - before
    finally:
        running = False
        thread.join()
    assert during > 100


@pytest.mark.spec("UT-PY-006")
def test_b_concurrent_calls_serialise(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-006-b", record=rec)
    results: dict[str, object] = {}
    start = threading.Barrier(2)

    def call(name: str, f: Callable[[], None]) -> None:
        start.wait()
        results[name] = f()

    a = threading.Thread(target=call, args=("a", lambda: dev.set_voltage(1.0)))
    b = threading.Thread(target=call, args=("b", lambda: dev.set_current_limit(0.1)))
    a.start()
    b.start()
    a.join(5.0)
    b.join(5.0)
    assert results == {"a": None, "b": None}
    sent = frames.c8(rec.sent())
    assert len(sent) == 3
    assert sent[0].remote_con == 2
    assert {(c.remote_con, c.set_voltage, c.set_current) for c in sent[1:]} == {
        (1, 100, 1000),
        (1, 1300, 100),
    }


INTERRUPT = """
mp305.set_log_level({level})
{handler}
rec = testing.MockRecord()
s = script(replies=[reply(0xC8, b"\\x00", after_s=1.5)])
dev = Mp305._from_mock([s], identifier="{identifier}", record=rec)
sigint_after(0.2)
outcome = None
try:
    dev.set_voltage(1.0)
    outcome = "returned"
except KeyboardInterrupt:
    caught = time.monotonic()
    outcome = "KeyboardInterrupt"
except BaseException as error:
    caught = time.monotonic()
    outcome = type(error).__name__
latency = caught - MARKS["signal"]
deadline = time.monotonic() + 3.0
while dev.remote_state != "granted" and time.monotonic() < deadline:
    time.sleep(0.02)
time.sleep(0.4)
report(
    outcome=outcome,
    latency=latency,
    remote_state=dev.remote_state,
    sent=frames.as_dicts(rec.sent()),
)
"""


def check_interrupt(report: dict[str, object]) -> None:
    """The expectations of cases (c) and (d)."""
    assert report["outcome"] == "KeyboardInterrupt"
    assert isinstance(report["latency"], float)
    assert report["latency"] < 0.5
    assert report["remote_state"] == "granted"
    sent = frames.c8(frames.from_dicts(report["sent"]))  # type: ignore[arg-type]
    assert [c.remote_con for c in sent] == [2]


@pytest.mark.spec("UT-PY-006")
def test_c_ctrl_c_on_the_main_thread() -> None:
    report, proc = run_child(INTERRUPT.format(level=30, handler="", identifier="UT-PY-006-c"))
    assert proc.returncode == 0, proc.stderr
    check_interrupt(report)


@pytest.mark.spec("UT-PY-006")
def test_d_ctrl_c_with_the_frame_log_on() -> None:
    handler = 'logging.getLogger("mp305.core.frames").addHandler(logging.StreamHandler())'
    report, proc = run_child(INTERRUPT.format(level=5, handler=handler, identifier="UT-PY-006-d"))
    assert proc.returncode == 0, proc.stderr
    assert "tx ble" in proc.stderr
    check_interrupt(report)


WORKER = """
s = script(replies=[reply(0xC8, b"\\x00", after_s=1.5, repeat=1), reply(0xC8, b"\\x00")])
dev = Mp305._from_mock([s], identifier="UT-PY-006-e")
seen = {}
def work():
    try:
        dev.set_voltage(1.0)
        seen["outcome"] = "returned"
    except BaseException as error:
        seen["at"] = time.monotonic()
        seen["outcome"] = type(error).__name__
        seen["text"] = str(error)
worker = threading.Thread(target=work)
worker.start()
sigint_after(0.2)
main = None
try:
    while worker.is_alive():
        worker.join(0.05)
except KeyboardInterrupt:
    main = "KeyboardInterrupt"
    started = time.monotonic()
    dev.close()
    closed = time.monotonic()
worker.join(5.0)
report(
    main=main,
    outcome=seen.get("outcome"),
    text=seen.get("text"),
    worker_after_close=seen["at"] - started,
    close_took=closed - started,
)
"""


@pytest.mark.spec("UT-PY-006")
def test_e_ctrl_c_does_not_reach_a_worker_thread() -> None:
    report, proc = run_child(WORKER)
    assert proc.returncode == 0, proc.stderr
    assert report["main"] == "KeyboardInterrupt"
    assert report["outcome"] == "LinkLostError"
    assert report["text"] == "link lost: closed by the host"
    assert report["worker_after_close"] < 0.3
    assert report["close_took"] < 2.0
