"""Helpers of the Python unit tests: scripts, polling waits and child processes.

The mock runs on the real clock, so waits are conditions polled every 20 ms
with an upper bound, not fixed sleeps (py DD, section 9).
"""

from __future__ import annotations

import json
import logging
import os
import pathlib
import subprocess
import sys
import textwrap
import time
from collections.abc import Callable, Iterable
from typing import Any

from mp305 import testing

ROOT = pathlib.Path(__file__).resolve().parents[2]
"""The repository root."""


def reply(
    request: int,
    payload: bytes,
    after_s: float = 0.005,
    repeat: int | None = None,
    kind: str = "ble",
    **extra: Any,
) -> dict[str, Any]:
    """A reply to `request` with `payload` under the reply opcode."""
    frame = testing.ble_frame if kind == "ble" else testing.hid_stream
    return {
        "request": request,
        "after_s": after_s,
        "deliveries": [frame(request + 1, payload)],
        "repeat": repeat,
        **extra,
    }


def silent(request: int, after_s: float = 0.005, repeat: int | None = None) -> dict[str, Any]:
    """A reply to `request` that delivers nothing."""
    return {"request": request, "after_s": after_s, "deliveries": [], "repeat": repeat}


def script(
    kind: str = "ble",
    replies: Iterable[dict[str, Any]] = (),
    drop: Iterable[int] = (),
    **extra: Any,
) -> dict[str, Any]:
    """The default script with the replies of every opcode in `replies` or
    `drop` taken out, `replies` appended and `extra` keys set."""
    s: dict[str, Any] = dict(testing.default_script(kind))
    replies = list(replies)
    gone = {r["request"] for r in replies} | set(drop)
    s["replies"] = [r for r in s["replies"] if r["request"] not in gone] + replies
    s.update(extra)
    return s


def c3_reply(payload: bytes, after_s: float = 0.010, **extra: Any) -> dict[str, Any]:
    """A `0xC2` reply with the `0xC3` payload `payload`."""
    return reply(0xC2, payload, after_s=after_s, **extra)


def wait_until(condition: Callable[[], Any], timeout: float, step: float = 0.02) -> Any:
    """Polls `condition` every `step` s until it is truthy or `timeout` passed.

    Returns the last value of the condition.
    """
    deadline = time.monotonic() + timeout
    while True:
        value = condition()
        if value or time.monotonic() >= deadline:
            return value
        time.sleep(step)


def records(
    caplog: Any, name: str | None = None, level: int | None = None
) -> list[logging.LogRecord]:
    """The captured records, filtered by logger name and level."""
    return [
        r
        for r in caplog.records
        if (name is None or r.name == name) and (level is None or r.levelno == level)
    ]


def messages(caplog: Any, name: str | None = None, level: int | None = None) -> list[str]:
    """The messages of `records`."""
    return [r.getMessage() for r in records(caplog, name, level)]


PRELUDE = '''
import json, logging, signal, sys, threading, time
import mp305
from mp305 import Mp305, testing
from tests.unit import frames
from tests.unit.support import c3_reply, reply, script, silent

MARKS = {}

def sigint_after(delay, key="signal"):
    """Raises SIGINT after `delay` s from a daemon timer; notes the time."""
    def fire():
        MARKS[key] = time.monotonic()
        signal.raise_signal(signal.SIGINT)
    timer = threading.Timer(delay, fire)
    timer.daemon = True
    timer.start()
    return timer

class ListHandler(logging.Handler):
    """Keeps the records."""
    def __init__(self):
        super().__init__(level=0)
        self.items = []
    def emit(self, record):
        self.items.append((record.name, record.levelno, record.getMessage(), record.threadName))

def report(**fields):
    """Prints the observations as one JSON line."""
    print(json.dumps(fields), flush=True)
'''


def run_child(
    code: str, env: dict[str, str] | None = None, timeout: float = 30, before: str = ""
) -> tuple[dict[str, Any], subprocess.CompletedProcess[str]]:
    """Runs `before`, the prelude, then `code` in a child Python.

    `before` runs ahead of the prelude's `import mp305`. Returns the last
    JSON line the child printed (an empty dict when there is none) and the
    completed process.
    """
    full = textwrap.dedent(before) + PRELUDE + textwrap.dedent(code)
    child_env = dict(os.environ if env is None else env)
    child_env["PYTHONPATH"] = str(ROOT)
    proc = subprocess.run(
        [sys.executable, "-c", full],
        capture_output=True,
        text=True,
        timeout=timeout,
        cwd=ROOT,
        env=child_env,
    )
    report: dict[str, Any] = {}
    for line in proc.stdout.splitlines():
        if line.startswith("{"):
            report = json.loads(line)
    return report, proc
