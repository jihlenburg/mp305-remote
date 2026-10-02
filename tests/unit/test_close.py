"""UT-PY-015: `close`, the context manager and the finalizer."""

from __future__ import annotations

import gc
import logging
import time
import types
import typing
from collections.abc import Callable

import pytest

from mp305 import LinkLostError, Mp305, Mp305Error, Mp305TimeoutError, testing
from mp305.types import SentFrame
from tests.unit import frames
from tests.unit.support import c3_reply, messages, reply, script

Factory = Callable[..., Mp305]


def output_on_script() -> dict[str, object]:
    """The default script with the output reported on."""
    return script(replies=[c3_reply(testing.c3(output=1))])


def check_close_frames(sent: list[SentFrame]) -> None:
    """After the voltage's `0xC8`: the output-off, then the release, each
    preceded by at least one `0xC2`."""
    voltage = next(
        i
        for i, f in enumerate(sent)
        if f.opcode == 0xC8 and frames.control(f.payload).remote_con == 1
    )
    rest = sent[voltage + 1 :]
    c8 = [(i, frames.control(f.payload)) for i, f in enumerate(rest) if f.opcode == 0xC8]
    assert [(c.remote_con, c.output) for _, c in c8] == [(1, 0), (0, 0)]
    (off, _), (release, _) = c8
    assert any(f.opcode == 0xC2 for f in rest[:off])
    assert any(f.opcode == 0xC2 for f in rest[off + 1 : release])


@pytest.mark.spec("UT-PY-015")
def test_a_with_block(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    with Mp305._from_mock([output_on_script()], identifier="UT-PY-015-a", record=rec) as dev:
        dev.set_voltage(1.0)
    check_close_frames(rec.sent())
    assert rec.closes() == 1
    assert dev.closed is True


@pytest.mark.spec("UT-PY-015")
def test_b_with_block_and_an_exception() -> None:
    rec = testing.MockRecord()
    with pytest.raises(RuntimeError, match="boom"):
        with Mp305._from_mock([output_on_script()], identifier="UT-PY-015-b", record=rec) as dev:
            dev.set_voltage(1.0)
            raise RuntimeError("boom")
    check_close_frames(rec.sent())
    assert rec.closes() == 1
    assert dev.closed is True


def unanswered_close_script() -> dict[str, object]:
    """Output on; `0xC8` answered twice (the request and the voltage), then never."""
    return script(
        replies=[c3_reply(testing.c3(output=1)), reply(0xC8, b"\x00", repeat=2)]
    )


@pytest.mark.spec("UT-PY-015")
def test_c_a_failing_close(caplog: pytest.LogCaptureFixture) -> None:
    with pytest.raises(RuntimeError, match="first"):
        with Mp305._from_mock([unanswered_close_script()], identifier="UT-PY-015-c1") as dev:
            dev.set_voltage(1.0)
            raise RuntimeError("first")
    errors = messages(caplog, "mp305", logging.ERROR)
    assert sum("no reply to 0xc8 within 500 ms" in m for m in errors) == 1
    assert dev.closed is True
    start = time.monotonic()
    with pytest.raises(Mp305TimeoutError) as info:
        with Mp305._from_mock([unanswered_close_script()], identifier="UT-PY-015-c2") as other:
            other.set_voltage(1.0)
            start = time.monotonic()
    assert str(info.value) == "no reply to 0xc8 within 500 ms"
    assert 1.0 <= time.monotonic() - start <= 3.5
    assert other.closed is True


@pytest.mark.spec("UT-PY-015")
def test_d_after_close(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    dev = mock_device(identifier="UT-PY-015-d", record=rec)
    info = dev.info
    dev.close()
    assert dev.close() is None
    count = len(rec.sent())
    with pytest.raises(LinkLostError) as error:
        dev.set_voltage(1.0)
    assert str(error.value) == "link lost: closed by the host"
    assert len(rec.sent()) == count
    assert dev.link_state == "closed"
    assert dev.info == info
    assert dev.reading is not None
    assert dev.identifier == "UT-PY-015-d"
    assert isinstance(dev.events(), list)


@pytest.mark.spec("UT-PY-015")
def test_e_the_finalizer(caplog: pytest.LogCaptureFixture) -> None:
    dev = Mp305._from_mock([testing.default_script()], identifier="UT-PY-015-e")
    del dev
    gc.collect()
    assert messages(caplog, "mp305", logging.WARNING) == [
        "Mp305 UT-PY-015-e was not closed; the output stays as it is"
    ]
    deadline = time.monotonic() + 0.5
    while True:
        try:
            again = Mp305._from_mock([testing.default_script()], identifier="UT-PY-015-e")
            break
        except Mp305Error:
            assert time.monotonic() < deadline
            time.sleep(0.02)
    again.close()


@pytest.mark.spec("UT-PY-015")
def test_f_exit_returns_none() -> None:
    hints = typing.get_type_hints(Mp305.__exit__)
    assert hints["return"] is types.NoneType


class FailingClose:
    """A session object whose `close` raises `error`; the rest is the real one."""

    def __init__(self, inner: object, error: BaseException) -> None:
        self._inner = inner
        self._error = error

    def __getattr__(self, name: str) -> object:
        return getattr(self._inner, name)

    def close(self, output_off: bool, dispatch: object) -> None:
        raise self._error


@pytest.mark.spec("UT-PY-015")
def test_close_ends_only_the_wait_on_another_exception(
    mock_device: Factory, caplog: pytest.LogCaptureFixture
) -> None:
    # DD-PY-043: only an `Mp305Error` from the close marks the object closed
    # and is logged and not raised in `__exit__`; any other exception ends only
    # the wait, as an interrupt does.
    dev = mock_device(identifier="UT-PY-015-g")
    real = dev._session
    dev._session = FailingClose(real, RuntimeError("boom"))  # type: ignore[assignment]
    try:
        with pytest.raises(RuntimeError, match="boom"):
            dev.close()
        assert dev.closed is False
        assert messages(caplog, "mp305", logging.ERROR) == [
            "close of UT-PY-015-g interrupted; the close continues in the background "
            "and the process waits for it at exit"
        ]
        with pytest.raises(RuntimeError, match="boom") as info:
            with dev:
                raise ValueError("first")
        assert isinstance(info.value.__context__, ValueError)
        assert dev.closed is False
    finally:
        dev._session = real
