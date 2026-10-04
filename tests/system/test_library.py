"""ST-031, ST-032, ST-034, ST-035: the Python library's calls and helpers.

SR-031 to SR-035. Ctrl-C acts on the main thread only, so step 1 of ST-031
runs in a child process that raises SIGINT itself, as the integration tests
do. ST-034 writes its CSV file next to the run's record when
`MP305_HIL_RECORD` is set, so that ST-037 can compare it with the app's.
"""

from __future__ import annotations

import logging
import pathlib
import threading
import time
from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

import mp305
from mp305 import (
    CommandRejectedError,
    ConnectionDeniedError,
    FaultActiveError,
    LinkLostError,
    ModeError,
    Mp305,
    Mp305Error,
    Mp305TimeoutError,
    NotFoundError,
    RemoteControlDeniedError,
    RemoteControlLostError,
    SetpointRangeError,
    testing,
)
from tests.system.support import (
    FrameLog,
    control,
    csv_problems,
    reply,
    run_child,
    script,
)

if TYPE_CHECKING:
    from tests.system.conftest import Guard, OptIns, Person, RunRecord, Unit

Factory = Callable[..., Mp305]

FEWER = "the supply delivers fewer readings than the requested rate"


# ST-031


@pytest.mark.hil
@pytest.mark.spec("ST-031")
def test_st031_step1_ctrl_c_during_the_bind_wait(
    ble_unit: Unit,
    person: Person,
    fresh_state_dir: pathlib.Path,
    observe: Callable[[str, object], None],
) -> None:
    """Step 1, in a child process: Ctrl-C 1 s into the bind wait (fresh host ID).

    The child connects and, when the supply shows the confirmation prompt,
    raises SIGINT after 1 s, which is what Ctrl-C does.
    """
    person.say(
        "The supply will ask to confirm a connection: do NOT press anything; the test "
        "interrupts the connection itself. Afterwards press DENY if the prompt is still shown."
    )
    report, proc = run_child(
        """
        def on_prompt(event):
            if event.prompt == "confirm_connection" and "signal" not in MARKS:
                sigint_after(1.0)
        outcome = None
        latency = None
        try:
            dev = Mp305.connect(
                os.environ["MP305_ST031_DEVICE"],
                state_dir=os.environ["MP305_ST031_STATE"],
                on_prompt=on_prompt,
            )
            outcome = "connected"
            dev.close()
        except KeyboardInterrupt:
            outcome = "KeyboardInterrupt"
            latency = time.monotonic() - MARKS["signal"]
        report(outcome=outcome, latency=latency)
        """,
        env={
            "MP305_ST031_DEVICE": ble_unit.identifier,
            "MP305_ST031_STATE": str(fresh_state_dir),
        },
        timeout=120.0,
    )
    observe("child", report)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5


@pytest.mark.hil
@pytest.mark.spec("ST-031")
def test_st031_step2_a_thread_counts_while_a_call_blocks(hil_unit: Unit, supply: Guard) -> None:
    """Step 2: a Python thread counts while `read()` blocks."""
    dev = supply.connect()
    count = [0]
    stop = threading.Event()

    def counter() -> None:
        while not stop.is_set():
            count[0] += 1

    thread = threading.Thread(target=counter, name="ST-031 counter")
    thread.start()
    advanced = []
    try:
        for _ in range(5):
            before = count[0]
            dev.read(timeout=5.0)
            advanced.append(count[0] - before)
    finally:
        stop.set()
        thread.join(5.0)
    assert all(n > 0 for n in advanced), advanced


# ST-032


@pytest.mark.spec("ST-032")
def test_st032_the_exception_classes_and_their_bases() -> None:
    """Inspect the exception classes: all of SR-032 exist with the stated bases.

    The analysis part of the entry (which test raises which class) belongs
    to the run's record: the HIL tests raise most of them, ST-023's mock
    part `CommandRejectedError` and ST-048 `RemoteControlDeniedError`.
    """
    assert issubclass(mp305.Mp305Error, Exception)
    for cls in (
        NotFoundError,
        ConnectionDeniedError,
        SetpointRangeError,
        CommandRejectedError,
        RemoteControlDeniedError,
        RemoteControlLostError,
        ModeError,
        FaultActiveError,
        Mp305TimeoutError,
        LinkLostError,
    ):
        assert issubclass(cls, Mp305Error), cls
        assert getattr(mp305, cls.__name__) is cls
    assert issubclass(SetpointRangeError, ValueError)
    assert issubclass(Mp305TimeoutError, TimeoutError)
    assert issubclass(LinkLostError, ConnectionError)


# ST-034


def _csv_path(opt_ins: OptIns, tmp_path: pathlib.Path) -> pathlib.Path:
    """Where step 2 writes: next to the run's record, else the test's temporary directory."""
    if opt_ins.record is not None:
        stamp = time.strftime("%Y%m%dT%H%M%S")
        return opt_ins.record.parent / f"{opt_ins.record.stem}-ST-034-{stamp}.csv"
    return tmp_path / "ST-034.csv"


SLOW_TEXT = "the supply delivers fewer readings than the requested rate"
"""The warning of SR-034 for a transport that cannot keep up."""

SR013_RATE = 2.0
"""The readings per second every transport delivers at least (SR-013)."""


@pytest.mark.hil
@pytest.mark.spec("ST-034")
def test_st034_stream_at_three_rates_and_write_csv(
    hil_unit: Unit,
    supply: Guard,
    opt_ins: OptIns,
    run_record: RunRecord,
    tmp_path: pathlib.Path,
    observe: Callable[[str, object], None],
    caplog: pytest.LogCaptureFixture,
) -> None:
    """Steps 1 to 3 on the supply (step 4 is the mock test below)."""
    dev = supply.connect()
    # Step 1: 0.1, 2 and 4 per second for 30 s each.
    counts = {}
    warnings = {}
    for rate in (0.1, 2.0, 4.0):
        caplog.clear()
        counts[rate] = len(list(mp305.stream(dev, rate, duration=30.0)))
        warnings[rate] = sum(
            1
            for r in caplog.records
            if r.name == "mp305" and r.levelno == logging.WARNING and SLOW_TEXT in r.getMessage()
        )
    observe("counts", {str(k): v for k, v in counts.items()})
    observe("slow_warnings", {str(k): v for k, v in warnings.items()})
    # Step 2: 30 s to CSV.
    path = _csv_path(opt_ins, tmp_path)
    path.parent.mkdir(parents=True, exist_ok=True)
    rows = mp305.to_csv(dev, path, duration=30.0)
    run_record.csv_files.append(str(path))
    observe("csv", str(path))
    data = path.read_bytes()
    # Step 3: 4.1 per second.
    with pytest.raises(ValueError):
        mp305.stream(dev, 4.1)
    for rate, count in counts.items():
        full = rate * 30.0
        if warnings[rate] == 0:
            # The stream kept up: the count is within 10 % of the rate.
            assert abs(count - full) <= 0.1 * full, (rate, count)
        else:
            # The link cannot keep up with the rate (SR-034): what it
            # delivers, not below the 2 per second of SR-013, one warning.
            assert warnings[rate] == 1, (rate, warnings[rate])
            assert 0.9 * min(rate, SR013_RATE) * 30.0 <= count < full, (rate, count)
    assert csv_problems(data) == []
    assert len(data.decode("utf-8").splitlines()) - 1 == rows


@pytest.mark.spec("ST-034")
def test_st034_step4_a_slow_supply_yields_what_it_gets_and_warns_once(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    """Step 4 on the mock: one reply per second, 4 readings per second asked for."""
    capture = testing.fixtures()["C3_CAPTURE"]
    # 0.9 s to the reply plus the 100 ms pause before the next poll.
    s = script(replies=[reply(0xC2, capture, after_s=0.9)])
    dev = mock_device([s], identifier="ST-034-slow")
    got = list(mp305.stream(dev, 4.0, duration=5.0))
    warnings = [
        r.getMessage() for r in caplog.records if r.name == "mp305" and r.levelno == logging.WARNING
    ]
    assert 4 <= len(got) <= 6, len(got)
    assert warnings.count(FEWER) == 1


# ST-035


@pytest.mark.hil
@pytest.mark.spec("ST-035")
def test_st035_ramp_and_a_ramp_above_the_user_limit(
    hil_unit: Unit, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Step 1: 1 to 5 V, step 1 V, 1 s dwell, no load. Step 2: an end above the user limit."""
    dev = supply.connect()
    start = frame_log.mark()
    points = mp305.ramp(dev, "voltage", 1.0, 5.0, 1.0, 1.0)
    frame_log.settle()
    assert points == [1.0, 2.0, 3.0, 4.0, 5.0]
    commands = [f for f in frame_log.sent(0xC8, start) if control(f.payload).remote_con == 1]
    assert [control(f.payload).set_voltage for f in commands] == [100, 200, 300, 400, 500]
    gaps = [b.created - a.created for a, b in zip(commands, commands[1:], strict=False)]
    assert all(0.8 <= g <= 1.6 for g in gaps), gaps
    # Step 2.
    dev.set_limits(max_voltage=4.0, max_current=0.1)
    second = frame_log.mark()
    with pytest.raises(SetpointRangeError):
        mp305.ramp(dev, "voltage", 1.0, 4.5, 0.5, 0.0)
    frame_log.settle()
    assert frame_log.sent(0xC8, second) == []
