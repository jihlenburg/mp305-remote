"""UT-PY-008: the event queue, `readings()` and their ends."""

from __future__ import annotations

import logging
import threading
import time
from collections.abc import Callable

import pytest

from mp305 import EventKind, LinkLostError, Mp305, Reading, Settings, testing
from mp305.types import Fault
from tests.unit.support import c3_reply, messages, script, wait_until

Factory = Callable[..., Mp305]
LOSS = (
    "link lost: The transport reported the link closed. The output is still in its last state "
    "and the supply has released remote control. A USB host talking to the supply is one "
    "possible cause."
)


@pytest.mark.spec("UT-PY-008")
def test_a_events_in_order_once(mock_device: Factory, caplog: pytest.LogCaptureFixture) -> None:
    caplog.set_level(logging.INFO, logger="mp305")
    fixtures = testing.fixtures()
    s = script(
        injections=[{"at_s": 0.3, "delivery": testing.ble_frame(0xC5, fixtures["C5_SETTINGS"])}]
    )
    s["replies"].append(c3_reply(testing.c3(charge_error=1 << 5), from_s=0.6))
    dev = mock_device([s], identifier="UT-PY-008-a")
    deadline = time.monotonic() + 3.0
    while time.monotonic() < deadline:
        dev.read()
        reading = dev.reading
        if reading is not None and reading.faults:
            break
    first = dev.events()
    assert [e.kind for e in first] == [
        EventKind.BIND_RESULT,
        EventKind.SETTINGS_CHANGED,
        EventKind.FAULTS_CHANGED,
    ]
    assert first[0].recognised is True
    assert first[1].settings == Settings(90, 2, 0, 0, 1, 500, 50, 0)
    assert first[2].faults == frozenset({Fault.OVER_CURRENT})
    assert first[2].reading is not None
    assert first[2].reading.faults == frozenset({Fault.OVER_CURRENT})
    assert first[0].seq < first[1].seq < first[2].seq
    info = messages(caplog, "mp305", logging.INFO)
    assert "bind: host recognised" in info
    assert any(m.startswith("settings changed: Settings(charge_limit=90") for m in info)
    assert "faults: over current" in info
    assert dev.events() == []


@pytest.mark.spec("UT-PY-008")
def test_b_readings_after_the_call(mock_device: Factory) -> None:
    dev = mock_device(identifier="UT-PY-008-b")
    t = time.time()
    it = dev.readings()
    got = [next(it) for _ in range(5)]
    stamps = [r.wall_ns for r in got]
    assert stamps == sorted(stamps)
    assert len(set(stamps)) == 5
    assert all(r.timestamp >= t - 0.01 for r in got)


@pytest.mark.spec("UT-PY-008")
def test_c_readings_end_on_a_lost_link(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    rec = testing.MockRecord()
    made = time.monotonic()
    dev = mock_device(
        [script(close_at_s=1.0)], identifier="UT-PY-008-c", reconnect=False, record=rec
    )
    # The mock closes 1.0 s after its own creation, which is no later than its
    # first send; measured from there, not from before the connect call.
    closed_at = made + rec.sent()[0].time + 1.0
    time.sleep(max(0.0, closed_at - 0.8 - time.monotonic()))
    got: list[Reading] = []
    with pytest.raises(LinkLostError) as info:
        for reading in dev.readings():
            got.append(reading)
    raised = time.monotonic()
    assert str(info.value) == LOSS
    assert got
    assert raised - closed_at < 0.5
    assert got[-1] == dev.reading
    loss = LOSS.removeprefix("link lost: ")

    def holding() -> int:
        return sum(loss in r.getMessage() for r in caplog.records)

    # The core's record may still be on its way from the delivery thread.
    wait_until(holding, 1.0)
    assert holding() == 1


@pytest.mark.spec("UT-PY-008")
def test_d_readings_end_on_close(mock_device: Factory) -> None:
    dev = mock_device(identifier="UT-PY-008-d")
    ended: dict[str, object] = {}

    def iterate() -> None:
        try:
            for _ in dev.readings():
                pass
            ended["outcome"] = "ended"
        except BaseException as error:
            ended["outcome"] = error
        ended["at"] = time.monotonic()

    thread = threading.Thread(target=iterate)
    thread.start()
    time.sleep(0.3)
    dev.close()
    closed = time.monotonic()
    thread.join(2.0)
    assert ended["outcome"] == "ended"
    assert isinstance(ended["at"], float)
    assert ended["at"] - closed < 0.3


@pytest.mark.spec("UT-PY-008")
def test_e_readings_and_events_from_two_threads(mock_device: Factory) -> None:
    dev = mock_device(identifier="UT-PY-008-e")
    readings: list[int] = []
    seqs: list[int] = []
    stop = time.monotonic() + 1.0

    def read() -> None:
        for reading in dev.readings():
            readings.append(reading.wall_ns)
            if time.monotonic() > stop:
                return

    def take() -> None:
        while time.monotonic() < stop:
            seqs.extend(e.seq for e in dev.events())
            time.sleep(0.01)

    threads = [threading.Thread(target=read), threading.Thread(target=take)]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join(3.0)
    assert len(seqs) == len(set(seqs))
    assert readings == sorted(readings)
    assert readings
    assert dev.dropped_events == 0
    assert dev.dropped_readings == 0


def flood_script() -> dict[str, object]:
    """The default script plus 1100 `0xC5` injections from 0.5 s, 1 ms apart."""
    c5 = testing.ble_frame(0xC5, testing.fixtures()["C5_SETTINGS"])
    return script(injections=[{"at_s": 0.5 + i * 0.001, "delivery": c5} for i in range(1100)])


@pytest.mark.spec("UT-PY-008")
def test_f_dropped_events(mock_device: Factory) -> None:
    start = time.monotonic()
    dev = mock_device([flood_script()], identifier="UT-PY-008-f")
    time.sleep(max(0.0, start + 2.5 - time.monotonic()))
    events = dev.events()
    assert len(events) == 1024
    assert {e.kind for e in events} == {EventKind.SETTINGS_CHANGED}
    assert dev.dropped_events == 77


class SkippingSession:
    """A session object whose first `readings_after` reports 76 skipped readings.

    The link ignores an unsolicited `0xC3` (DD-LINK-021), so readings cannot
    be injected; the feed's own skipping is UT-PY-022 (a).
    """

    def __init__(self, inner: object) -> None:
        self._inner = inner
        self._first = True

    def __getattr__(self, name: str) -> object:
        return getattr(self._inner, name)

    def readings_after(self, cursor: int, limit: int) -> tuple[list[object], int, int]:
        items, cursor, skipped = self._inner.readings_after(cursor, limit)  # type: ignore[attr-defined]
        if self._first:
            self._first = False
            skipped = 76
        return items, cursor, skipped


@pytest.mark.spec("UT-PY-008")
def test_f_dropped_readings(mock_device: Factory, caplog: pytest.LogCaptureFixture) -> None:
    dev = mock_device(identifier="UT-PY-008-f2")
    dev._session = SkippingSession(dev._session)  # type: ignore[assignment]
    before = dev.dropped_readings
    it = dev.readings()
    next(it)
    assert messages(caplog, "mp305", logging.WARNING) == [
        "readings() fell behind; 76 readings were skipped"
    ]
    assert dev.dropped_readings == before + 76
