"""The Python side of the log bridge.

Implements: DD-PY-006.

The native module queues the Rust log records; they reach `logging` only on
Python threads: in the pump of a blocking call, or on the daemon thread
`mp305-log`, which this module starts on the first `discover`, `connect`,
`_from_mock`, `host_id`, `default_state_dir` or `set_log_level` call, so that
records also arrive while no blocking call runs.
"""

from __future__ import annotations

import atexit
import logging
import threading

from mp305 import _native

TRACE = 5
"""The level of the frame log, below DEBUG."""

logging.addLevelName(TRACE, "TRACE")

_lock = threading.Lock()
_stop = threading.Event()
_thread: threading.Thread | None = None


def _deliver() -> None:
    """The delivery thread: waits for records and delivers them."""
    while not _stop.is_set():
        try:
            _native.log_wait(0.25)
        except Exception:
            # The thread must outlive a failing call; pause so that a
            # persistent failure cannot spin.
            _stop.wait(0.25)


def ensure_started() -> None:
    """Starts the delivery thread once per process."""
    global _thread
    with _lock:
        if _thread is not None:
            return
        _thread = threading.Thread(target=_deliver, name="mp305-log", daemon=True)
        _thread.start()


def _stop_at_exit() -> None:
    """Ends the delivery thread before the interpreter finalizes.

    A daemon thread that is inside a native wait when the interpreter
    finalizes would end inside Rust frames; stopping it first avoids that.
    Registered at import, so it runs after the exit hook of `mp305.device`.
    """
    _stop.set()
    thread = _thread
    if thread is not None:
        thread.join(1.0)


atexit.register(_stop_at_exit)


def set_log_level(level: int) -> None:
    """Sets how much of the library's log reaches `logging`.

    `set_log_level(5)` switches the frame log (`mp305.core.frames`, level
    TRACE) on in one call. A level above WARNING acts as WARNING: the
    library never switches off its own WARNING and ERROR records, although
    the user's `logging` configuration still can. Records of the Bluetooth
    dependencies (`mp305.deps.`) arrive only at DEBUG and above, whatever
    the level.

    Args:
        level: A `logging` level; 5 is TRACE.
    """
    ensure_started()
    _native.set_gate(level)
    logging.getLogger("mp305.core").setLevel(min(level, logging.WARNING))
