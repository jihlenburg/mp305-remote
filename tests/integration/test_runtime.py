"""IT-003 step 1: the runtime of `mp305-py` under threads and Ctrl-C (AR-003).

Steps 2 (`mp305-app`) and 3 (`mp305-core`) of IT-003 are Rust tests in
`crates/mp305-app/tests/it_worker.rs` and `crates/mp305-core/tests/it_clock.rs`.
The mock runs on the real clock, so waits are polled conditions with an upper
bound.
"""

from __future__ import annotations

import threading
import time
from collections.abc import Callable

import pytest

from mp305 import Mp305, testing
from tests.unit import frames
from tests.unit.support import reply, run_child, script

Factory = Callable[..., Mp305]


def delayed_commands(after_s: float) -> dict[str, object]:
    """The default script with the remote-control request answered at once and
    every later `0xC8` answered after `after_s` seconds."""
    return script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\x00", after_s=after_s)])


@pytest.mark.spec("IT-003")
def test_step_1_two_threads_call_a_blocking_method_at_once(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device([delayed_commands(0.3)], identifier="IT-003-1a", record=rec)
    start = threading.Barrier(2)
    results: dict[str, object] = {}
    spans: dict[str, tuple[float, float]] = {}

    def call(name: str, volts: float) -> None:
        start.wait()
        began = time.monotonic()
        try:
            results[name] = dev.set_voltage(volts)
        except Exception as error:
            results[name] = error
        spans[name] = (began, time.monotonic())

    threads = [
        threading.Thread(target=call, args=("a", 1.0)),
        threading.Thread(target=call, args=("b", 2.0)),
    ]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join(5.0)
    assert not any(thread.is_alive() for thread in threads)
    # Both calls complete.
    assert results == {"a": None, "b": None}
    # They ran at once: each started before the other returned.
    assert max(s[0] for s in spans.values()) < min(s[1] for s in spans.values())
    sent = frames.c8(rec.sent())
    assert [c.remote_con for c in sent] == [2, 1, 1]
    assert sorted(c.set_voltage for c in sent[1:]) == [100, 200]


@pytest.mark.spec("IT-003")
def test_step_1_a_thread_counts_while_a_third_blocks(mock_device: Factory) -> None:
    dev = mock_device([delayed_commands(0.6)], identifier="IT-003-1b")
    count = 0
    running = True
    inside = threading.Event()
    returned = threading.Event()

    def counter() -> None:
        nonlocal count
        while running:
            count += 1

    def blocker() -> None:
        inside.set()
        try:
            dev.set_voltage(1.0)
        finally:
            returned.set()

    counting = threading.Thread(target=counter)
    blocking = threading.Thread(target=blocker)
    counting.start()
    try:
        blocking.start()
        assert inside.wait(2.0)
        # The call waits about 0.7 s (the settle time, a poll and the 0.6 s
        # reply); the samples at 0.1 s and 0.2 s leave at least 0.4 s.
        time.sleep(0.1)
        first, first_inside = count, not returned.is_set()
        time.sleep(0.1)
        second, second_inside = count, not returned.is_set()
        blocking.join(5.0)
    finally:
        running = False
        counting.join(5.0)
    assert not blocking.is_alive()
    # This thread could read the counter while the third thread was still in
    # its call, and the counter had advanced in between.
    assert first_inside and second_inside
    assert second > first


INTERRUPT = """
rec = testing.MockRecord()
s = script(replies=[reply(0xC8, b"\\x00", after_s=5.0, repeat=1), reply(0xC8, b"\\x00")])
dev = Mp305._from_mock([s], identifier="IT-003-1c", record=rec)
sigint_after(0.2)
outcome = None
caught = None
try:
    dev.set_voltage(1.0)
    outcome = "returned"
except KeyboardInterrupt:
    caught = time.monotonic()
    outcome = "KeyboardInterrupt"
except BaseException as error:
    caught = time.monotonic()
    outcome = type(error).__name__
latency = None if caught is None else caught - MARKS["signal"]
at_interrupt = len(rec.sent())
deadline = time.monotonic() + 7.0
while dev.remote_state != "granted" and time.monotonic() < deadline:
    time.sleep(0.02)
remote_state = dev.remote_state
time.sleep(0.4)
sent = frames.as_dicts(rec.sent())
dev.close()
report(
    outcome=outcome,
    latency=latency,
    at_interrupt=at_interrupt,
    remote_state=remote_state,
    sent=sent,
)
"""


@pytest.mark.spec("IT-003")
def test_step_1_ctrl_c_during_a_5_s_mock_delay() -> None:
    # A child process, since the interrupt acts on the main thread only. Its
    # daemon timer thread raises SIGINT 0.2 s into `set_voltage`, whose
    # remote-control request the mock answers only after 5 s. The child
    # waits for that answer and 0.4 s more before it reports, so a `0xC8`
    # of the cancelled command would be seen.
    report, proc = run_child(INTERRUPT)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert isinstance(report["latency"], float)
    assert report["latency"] < 0.5
    # The request itself still completed (the grant is tracked).
    assert report["remote_state"] == "granted"
    sent = frames.from_dicts(report["sent"])
    # The pending command was cancelled: only the request went out, and no
    # `0xC8` for the command followed the grant.
    assert [c.remote_con for c in frames.c8(sent)] == [2]
    after = sent[report["at_interrupt"] :]
    assert frames.sent(after, 0xC8) == []
    # The session keeps polling.
    assert frames.sent(after, 0xC2)
