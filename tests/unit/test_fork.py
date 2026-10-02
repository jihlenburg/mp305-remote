"""UT-PY-025: the library refuses to work in a forked child."""

from __future__ import annotations

import gc
import json
import os
import sys
import time
import warnings

import pytest

from mp305 import Mp305, Mp305Error, testing

FORKED = "mp305 cannot be used in a process forked after it started"


def refused(call: str, dev: Mp305) -> str:
    """The text of the error one call raises in the child."""
    try:
        if call == "set_voltage":
            dev.set_voltage(1.0)
        elif call == "from_mock":
            Mp305._from_mock([testing.default_script()], identifier="UT-PY-025-child")
        else:
            dev.reading  # noqa: B018 - the property access is the call under test
        return "returned"
    except Mp305Error as error:
        return str(error)
    except BaseException as error:
        return f"{type(error).__name__}: {error}"


# Windows has no `fork`.
@pytest.mark.skipif(sys.platform == "win32", reason="POSIX only: Windows has no fork")
@pytest.mark.spec("UT-PY-025")
def test_a_forked_child_is_refused() -> None:
    # Not the `mock_device` fixture: its list would keep the device alive in
    # the child, and the child must drop the last reference.
    dev = Mp305._from_mock([testing.default_script()], identifier="UT-PY-025")
    try:
        read, write = os.pipe()
        with warnings.catch_warnings():
            # Python 3.12 warns that forking a multi-threaded process may
            # deadlock; the refusal tested here keeps the child from doing so.
            warnings.simplefilter("ignore", DeprecationWarning)
            pid = os.fork()
        if pid == 0:  # pragma: no cover - the child ends with os._exit, so no coverage is written
            try:
                os.close(read)
                outcomes = [refused(call, dev) for call in ("set_voltage", "from_mock", "reading")]
                del dev
                gc.collect()
                os.write(write, json.dumps({"outcomes": outcomes, "collected": True}).encode())
                os.close(write)
            finally:
                os._exit(0)
        os.close(write)
        start = time.monotonic()
        data = b""
        while chunk := os.read(read, 65536):
            data += chunk
        os.close(read)
        _, status = os.waitpid(pid, 0)
        assert time.monotonic() - start < 5.0
        assert os.waitstatus_to_exitcode(status) == 0
        report = json.loads(data)
        assert report["collected"] is True
        assert len(report["outcomes"]) == 3
        for outcome in report["outcomes"]:
            assert outcome.startswith(FORKED), outcome
        assert dev.set_voltage(1.0) is None
    finally:
        dev.close()
