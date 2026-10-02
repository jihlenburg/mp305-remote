"""UT-PY-024: `output_off` and `close` finish after an interrupt."""

from __future__ import annotations

import json
import logging
import signal
import sys
import time
from collections.abc import Callable
from typing import Any

import pytest

from mp305 import Event, Mp305, Mp305TimeoutError, _native, device, testing
from tests.unit import frames
from tests.unit.support import (
    c3_reply,
    messages,
    records,
    reply,
    run_child,
    script,
    silent,
    wait_until,
)

Factory = Callable[..., Mp305]

SCRIPT = """
def safety_script():
    # Output on; 0xC8 answered after 5 ms twice (the request and a set_voltage),
    # then after 400 ms once (the next output-off, inside the core's 500 ms
    # bound), then after 5 ms.
    return script(replies=[
        c3_reply(testing.c3(output=1)),
        reply(0xC8, b"\\x00", repeat=2),
        reply(0xC8, b"\\x00", after_s=0.4, repeat=1),
        reply(0xC8, b"\\x00"),
    ])
def prompting_script(request_after):
    # Output on; the remoteCon 2 request answered after `request_after`, then 5 ms.
    return script(replies=[
        c3_reply(testing.c3(output=1)),
        reply(0xC8, b"\\x00", after_s=request_after, repeat=1),
        reply(0xC8, b"\\x00"),
    ])
rec = testing.MockRecord()
"""

SETUP = SCRIPT + """
handler = ListHandler()
logging.getLogger().addHandler(handler)
"""

WAIT_PENDING = """
deadline = time.monotonic() + 2.0
while mp305._native.pending_safety() and time.monotonic() < deadline:
    time.sleep(0.02)
"""


def tail(report: dict[str, Any]) -> list[tuple[int, int]]:
    """The `(remoteCon, output)` of the last two `0xC8` frames."""
    sent = frames.c8(frames.from_dicts(report["sent"]))
    return [(c.remote_con, c.output) for c in sent[-2:]]


def logged(report: dict[str, Any], level: int, name: str | None = None) -> list[str]:
    """The messages the child's handler kept at `level`."""
    return [m for (n, lv, m, _) in report["log"] if lv == level and (name is None or n == name)]


A = SETUP + """
# The gate passes INFO; the INFO record of `mp305.native.safety` also needs a
# logging configuration that accepts INFO, as `basicConfig(level=INFO)` would.
logging.getLogger().setLevel(logging.INFO)
mp305.set_log_level(20)
dev = Mp305._from_mock([safety_script()], identifier="UT-PY-024-a", record=rec)
dev.set_voltage(1.0)
sigint_after(0.2)
outcome = None
try:
    dev.output_off()
except KeyboardInterrupt:
    pending_now = mp305._native.pending_safety()
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
""" + WAIT_PENDING + """
finished = "output-off UT-PY-024-a finished"
deadline = time.monotonic() + 1.0
while finished not in [m for (_, _, m, _) in handler.items] and time.monotonic() < deadline:
    time.sleep(0.02)
report(
    outcome=outcome,
    latency=latency,
    pending_now=pending_now,
    sent=frames.as_dicts(rec.sent()),
    log=handler.items,
)
dev.close()
"""


@pytest.mark.spec("UT-PY-024")
def test_a_output_off_finishes_after_ctrl_c() -> None:
    report, proc = run_child(A)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    assert report["pending_now"] == ["output-off UT-PY-024-a"]
    assert "output_off interrupted; the output-off continues in the background" in logged(
        report, logging.WARNING, "mp305"
    )
    sent = frames.c8(frames.from_dicts(report["sent"]))
    assert (sent[-1].remote_con, sent[-1].output) == (1, 0)
    assert "output-off UT-PY-024-a finished" in logged(report, logging.INFO, "mp305.native.safety")


B = SETUP + """
dev = Mp305._from_mock([safety_script()], identifier="{identifier}", record=rec)
dev.set_voltage(1.0)
sigint_after(0.2)
outcome = None
try:
    dev.close()
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
closed_after_interrupt = dev.closed
"""

B_AGAIN = B + """
second = time.monotonic()
result = repr(dev.close())
report(
    outcome=outcome,
    latency=latency,
    closed_after_interrupt=closed_after_interrupt,
    result=result,
    second_took=time.monotonic() - second,
    closed=dev.closed,
    sent=frames.as_dicts(rec.sent()),
    closes=rec.closes(),
    log=handler.items,
)
"""


@pytest.mark.spec("UT-PY-024")
def test_b_close_finishes_after_ctrl_c() -> None:
    report, proc = run_child(B_AGAIN.format(identifier="UT-PY-024-b"))
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    assert report["closed_after_interrupt"] is False
    assert logged(report, logging.ERROR, "mp305") == [
        "close of UT-PY-024-b interrupted; the close continues in the background "
        "and the process waits for it at exit"
    ]
    assert report["result"] == "None"
    assert report["second_took"] < 1.5
    assert report["closed"] is True
    assert tail(report) == [(1, 0), (0, 0)]
    assert report["closes"] == 1


# Registered before `import mp305`, so it runs after the library's exit hook.
PRINT_AT_EXIT = """
import atexit, json, time
HELD = {}
def print_record():
    rec = HELD["rec"]
    marks = HELD["marks"]
    print(json.dumps({"sent": HELD["frames"].as_dicts(rec.sent()), "closes": rec.closes(),
                      "at": time.monotonic(), "marks": marks}), flush=True)
atexit.register(print_record)
"""

EXIT = SCRIPT + """
HELD.update(rec=rec, marks=MARKS, frames=frames)
dev = Mp305._from_mock([{script}], identifier="{identifier}", record=rec)
{prepare}
sigint_after(0.2)
{second}
dev.{call}()
"""


@pytest.mark.skipif(sys.platform == "win32", reason="checks the POSIX exit by SIGINT")
@pytest.mark.spec("UT-PY-024")
def test_c_the_process_waits_at_exit_for_a_close() -> None:
    code = EXIT.format(
        script="safety_script()",
        identifier="UT-PY-024-c",
        prepare="dev.set_voltage(1.0)",
        second="",
        call="close",
    )
    report, proc = run_child(code, before=PRINT_AT_EXIT)
    assert proc.returncode == -signal.SIGINT
    assert "waiting for close UT-PY-024-c to finish before exit" in proc.stderr
    assert tail(report) == [(1, 0), (0, 0)]
    assert report["closes"] == 1


@pytest.mark.skipif(sys.platform == "win32", reason="checks the POSIX exit by SIGINT")
@pytest.mark.spec("UT-PY-024")
def test_d_a_second_ctrl_c_abandons_the_wait() -> None:
    code = EXIT.format(
        script="prompting_script(3.0)",
        identifier="UT-PY-024-d",
        prepare="",
        second='sigint_after(0.7, "second")',
        call="close",
    )
    _, proc = run_child(code, before=PRINT_AT_EXIT)
    ended = time.monotonic()
    assert proc.returncode == -signal.SIGINT
    assert "abandoned close UT-PY-024-d; the output may still be on" in proc.stderr
    printed = [json.loads(line) for line in proc.stdout.splitlines() if line.startswith("{")]
    second = printed[-1]["marks"]["second"]
    # The record is printed by the last exit hook, right before the process
    # ends; `ended` also holds the return from `subprocess.run` in this
    # process, so it gets a wider bound.
    assert printed[-1]["at"] - second < 0.5
    assert ended - second < 1.5


E = B + """
del dev
import gc
gc.collect()
""" + WAIT_PENDING + """
report(
    outcome=outcome,
    pending=mp305._native.pending_safety(),
    sent=frames.as_dicts(rec.sent()),
    log=handler.items,
)
"""


@pytest.mark.spec("UT-PY-024")
def test_e_dropping_a_closing_device_is_silent() -> None:
    report, proc = run_child(E.format(identifier="UT-PY-024-e"))
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert not [m for m in logged(report, logging.WARNING) if "was not closed" in m]
    assert report["pending"] == []
    assert tail(report) == [(1, 0), (0, 0)]


F = SETUP + """
dev = Mp305._from_mock([safety_script()], identifier="UT-PY-024-f", record=rec)
dev.set_voltage(1.0)
context = None
try:
    with dev:
        sigint_after(0.2)
        raise RuntimeError("first")
except KeyboardInterrupt as error:
    context = repr(error.__context__)
""" + WAIT_PENDING + """
report(context=context, closed=dev.closed, pending=mp305._native.pending_safety())
"""


@pytest.mark.spec("UT-PY-024")
def test_f_ctrl_c_during_exit_keeps_the_first_exception() -> None:
    report, proc = run_child(F)
    assert proc.returncode == 0, proc.stderr
    assert report["context"] == "RuntimeError('first')"
    assert report["closed"] is False
    assert report["pending"] == []


class Stop(BaseException):
    """A test exception that is not an `Exception`."""


def prompting_script() -> dict[str, Any]:
    """Output on; the `remoteCon` 2 request answered after 600 ms, then 5 ms."""
    return script(
        replies=[
            c3_reply(testing.c3(output=1)),
            reply(0xC8, b"\x00", after_s=0.6, repeat=1),
            reply(0xC8, b"\x00"),
        ]
    )


def stop_on_prompt(times: list[float]) -> Callable[[Event], None]:
    """An `on_prompt` that notes the time and raises `Stop`."""

    def on_prompt(event: Event) -> None:
        times.append(time.monotonic())
        raise Stop()

    return on_prompt


@pytest.mark.spec("UT-PY-024")
def test_g_a_base_exception_from_on_prompt_during_close(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    rec = testing.MockRecord()
    prompted: list[float] = []
    dev = mock_device(
        [prompting_script()],
        identifier="UT-PY-024-g",
        record=rec,
        on_prompt=stop_on_prompt(prompted),
    )
    with pytest.raises(Stop):
        dev.close()
    assert time.monotonic() - prompted[0] < 0.3
    assert dev.closed is False
    assert messages(caplog, "mp305", logging.ERROR) == [
        "close of UT-PY-024-g interrupted; the close continues in the background "
        "and the process waits for it at exit"
    ]
    assert wait_until(lambda: not _native.pending_safety(), 2.0)
    sent = frames.c8(rec.sent())
    assert [c.remote_con for c in sent] == [2, 1, 0]
    assert [c.output for c in sent[1:]] == [0, 0]


@pytest.mark.spec("UT-PY-024")
def test_h_a_base_exception_from_on_prompt_during_output_off(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    rec = testing.MockRecord()
    prompted: list[float] = []
    dev = mock_device(
        [prompting_script()],
        identifier="UT-PY-024-h",
        record=rec,
        on_prompt=stop_on_prompt(prompted),
    )
    with pytest.raises(Stop):
        dev.output_off()
    assert time.monotonic() - prompted[0] < 0.3
    assert "output_off interrupted; the output-off continues in the background" in messages(
        caplog, "mp305", logging.WARNING
    )
    assert wait_until(lambda: not _native.pending_safety(), 2.0)
    sent = frames.c8(rec.sent())
    assert [c.remote_con for c in sent] == [2, 1]
    assert sent[1].output == 0


@pytest.mark.skipif(sys.platform == "win32", reason="checks the POSIX exit by SIGINT")
@pytest.mark.spec("UT-PY-024")
def test_i_the_process_waits_at_exit_for_an_output_off() -> None:
    code = EXIT.format(
        script="safety_script()",
        identifier="UT-PY-024-i",
        prepare="dev.set_voltage(1.0)",
        second="",
        call="output_off",
    )
    report, proc = run_child(code, before=PRINT_AT_EXIT)
    assert proc.returncode == -signal.SIGINT
    assert "waiting for output-off UT-PY-024-i to finish before exit" in proc.stderr
    sent = frames.c8(frames.from_dicts(report["sent"]))
    assert (sent[-1].remote_con, sent[-1].output) == (1, 0)


J = SETUP + """
dev = Mp305._from_mock([prompting_script(0.6)], identifier="UT-PY-024-j", record=rec)
sigint_after(0.2)
outcome = None
try:
    dev.output_off()
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
del dev
import gc
gc.collect()
""" + WAIT_PENDING + """
report(outcome=outcome, pending=mp305._native.pending_safety(), sent=frames.as_dicts(rec.sent()))
"""


@pytest.mark.spec("UT-PY-024")
def test_j_the_output_off_outlives_its_object() -> None:
    report, proc = run_child(J)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["pending"] == []
    sent = frames.c8(frames.from_dicts(report["sent"]))
    assert [c.remote_con for c in sent] == [2, 1]
    assert sent[1].output == 0


@pytest.mark.spec("UT-PY-024")
def test_k_a_failed_output_off_is_recorded(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), silent(0xC8)])
    dev = mock_device([s], identifier="UT-PY-024-k")
    with pytest.raises(Mp305TimeoutError) as info:
        dev.output_off()
    expected = f"output-off UT-PY-024-k failed: {info.value}"

    def failed() -> list[logging.LogRecord]:
        return [r for r in records(caplog, "mp305.native.safety") if r.getMessage() == expected]

    found = wait_until(failed, 1.0)
    assert len(found) == 1
    assert found[0].levelno == logging.ERROR


@pytest.mark.spec("UT-PY-024")
def test_exit_hook_an_interrupt_during_its_warning(
    monkeypatch: pytest.MonkeyPatch, caplog: pytest.LogCaptureFixture
) -> None:
    # DD-PY-008 (rev 3): a KeyboardInterrupt that arrives while the exit hook
    # logs its WARNING still gives the ERROR "abandoned ...".
    monkeypatch.setattr(_native, "pending_safety", lambda: ["close X"])
    monkeypatch.setattr(_native, "wait_safety", lambda dispatch=None: None)

    class InterruptOnce(logging.Handler):
        def emit(self, record: logging.LogRecord) -> None:
            if record.getMessage().startswith("waiting for close X"):
                raise KeyboardInterrupt

    handler = InterruptOnce()
    logging.getLogger("mp305").addHandler(handler)
    try:
        device._wait_at_exit()
    except KeyboardInterrupt:
        pytest.fail("the interrupt during the WARNING escaped the exit hook")
    finally:
        logging.getLogger("mp305").removeHandler(handler)
    assert messages(caplog, "mp305", logging.ERROR) == [
        "abandoned close X; the output may still be on"
    ]
