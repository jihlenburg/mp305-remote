"""UT-PY-023: the dispatcher, nested calls and reference cycles."""

from __future__ import annotations

import gc
import logging
import threading
import time
import weakref
from collections.abc import Callable
from typing import Any

import pytest

import mp305
from mp305 import Event, LinkLostError, Mp305, Reading, testing
from tests.unit.support import messages, reply, script

Factory = Callable[..., Mp305]


def slow_request_script() -> dict[str, Any]:
    """`remoteCon` 2 answered after 500 ms once, then every `0xC8` after 5 ms."""
    return script(replies=[reply(0xC8, b"\x00", after_s=0.5, repeat=1), reply(0xC8, b"\x00")])


@pytest.mark.spec("UT-PY-023")
def test_a_calls_from_the_callback(mock_device: Factory) -> None:
    calls: dict[str, object] = {}
    holder: list[Mp305] = []

    def on_prompt(event: Event) -> None:
        dev = holder[0]
        calls["events"] = dev.events()
        calls["reading"] = dev.reading
        calls["read"] = dev.read(timeout=1.0)
        calls["close"] = dev.close()

    dev = mock_device([slow_request_script()], identifier="UT-PY-023-a", on_prompt=on_prompt)
    holder.append(dev)
    outcome: dict[str, object] = {}

    def call() -> None:
        start = time.monotonic()
        try:
            dev.set_voltage(1.0)
            outcome["result"] = "returned"
        except BaseException as error:
            outcome["result"] = error
        outcome["took"] = time.monotonic() - start

    worker = threading.Thread(target=call)
    worker.start()
    worker.join(10.0)
    assert not worker.is_alive(), "the 10 s guard was reached"
    assert isinstance(calls["events"], list)
    assert isinstance(calls["reading"], Reading)
    assert isinstance(calls["read"], Reading)
    assert calls["close"] is None
    error = outcome["result"]
    assert isinstance(error, LinkLostError)
    assert str(error) == "link lost: closed by the host"
    assert isinstance(outcome["took"], float) and outcome["took"] < 2.0


@pytest.mark.spec("UT-PY-023")
def test_b_a_slow_callback_does_not_block_readers(mock_device: Factory) -> None:
    dev = mock_device(
        [slow_request_script()], identifier="UT-PY-023-b", on_prompt=lambda e: time.sleep(1.0)
    )
    done = threading.Event()
    results: list[object] = []

    def reader() -> None:
        while not done.is_set():
            try:
                results.append(dev.read(timeout=0.5))
            except BaseException as error:
                results.append(error)

    thread = threading.Thread(target=reader)
    thread.start()
    try:
        dev.set_voltage(1.0)
    finally:
        done.set()
        thread.join(2.0)
    assert results
    assert all(isinstance(r, Reading) for r in results), results


@pytest.mark.spec("UT-PY-023")
def test_c_order_across_threads_with_a_slow_handler(mock_device: Factory) -> None:
    class Slow(logging.Handler):
        def emit(self, record: logging.LogRecord) -> None:
            time.sleep(0.02)

    handler = Slow()
    frames_log = logging.getLogger("mp305.core.frames")
    frames_log.addHandler(handler)
    mp305.set_log_level(5)
    try:
        dev = mock_device(identifier="UT-PY-023-c")
        collected: list[int] = []
        sampled: list[float] = []
        seqs: list[int] = []
        stop = time.monotonic() + 2.0

        def collect() -> None:
            for reading in dev.readings():
                collected.append(reading.wall_ns)
                if time.monotonic() > stop:
                    return

        def command() -> None:
            while time.monotonic() < stop:
                dev.set_voltage(1.0)
                reading = dev.reading
                assert reading is not None
                sampled.append(reading.timestamp)
                seqs.extend(e.seq for e in dev.events())

        threads = [threading.Thread(target=collect), threading.Thread(target=command)]
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join(15.0)
        assert not any(thread.is_alive() for thread in threads)
    finally:
        mp305.set_log_level(30)
        frames_log.removeHandler(handler)
    assert collected and all(a < b for a, b in zip(collected, collected[1:], strict=False))
    assert sampled and all(a <= b for a, b in zip(sampled, sampled[1:], strict=False))
    assert all(a < b for a, b in zip(seqs, seqs[1:], strict=False))


def device_in_a_cycle() -> Mp305:
    """A device whose `on_prompt` is a closure over the device itself."""
    dev: Mp305 | None = None

    def on_prompt(event: Event) -> None:
        assert dev is not None
        dev.reading  # noqa: B018 - the closure refers to the device

    dev = Mp305._from_mock(
        [testing.default_script()], identifier="UT-PY-023-d", on_prompt=on_prompt
    )
    return dev


@pytest.mark.spec("UT-PY-023")
def test_d_a_cycle_through_the_callback_is_collected(caplog: pytest.LogCaptureFixture) -> None:
    dev = device_in_a_cycle()
    r = weakref.ref(dev)
    del dev
    gc.collect()
    assert r() is None
    warned = [m for m in messages(caplog, "mp305", logging.WARNING) if "was not closed" in m]
    assert len(warned) == 1
