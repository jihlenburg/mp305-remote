"""UT-PY-016: the CSV format and `to_csv()`."""

from __future__ import annotations

import logging
import pathlib
from collections.abc import Callable

import pytest

from mp305 import LinkLostError, Mp305, _native, testing, to_csv
from tests.unit.support import messages, run_child, script

Factory = Callable[..., Mp305]
HEADER = "time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n"


@pytest.mark.spec("UT-PY-016")
def test_a_header_and_rows() -> None:
    capture = testing.fixtures()["C3_CAPTURE"]
    assert _native.csv_header() == HEADER
    assert _native.format_csv_row(capture, 1790848800250000000, 1790848800000000000) == (
        "2026-10-01T10:00:00.250Z,0.250,0.00,0.000,0.00,13.00,1.000,0,off,\n"
    )
    assert _native.format_csv_row(capture, 1790848800123999999, 1790848800000000000) == (
        "2026-10-01T10:00:00.123Z,0.123,0.00,0.000,0.00,13.00,1.000,0,off,\n"
    )
    with pytest.raises(ValueError, match="^not a 0xC3 payload"):
        _native.format_csv_row(b"short", 0, 0)
    with pytest.raises(ValueError):
        _native.format_csv_row(capture, -1, 0)


def check_rows(lines: list[str]) -> None:
    """Every line is a complete row ending in a newline."""
    for line in lines:
        assert line.endswith("\n")
        assert len(line.rstrip("\n").split(",")) == 10


@pytest.mark.spec("UT-PY-016")
def test_b_four_rows_in_one_second(mock_device: Factory, tmp_path: pathlib.Path) -> None:
    dev = mock_device(identifier="UT-PY-016-b")
    path = tmp_path / "log.csv"
    count = to_csv(dev, path, rate=4.0, duration=1.0)
    data = path.read_bytes()
    assert b"\r" not in data
    lines = data.decode().splitlines(keepends=True)
    assert lines[0] == HEADER
    assert len(lines) == 5
    check_rows(lines[1:])
    assert lines[1].split(",")[1] == "0.000"
    assert count == 4


@pytest.mark.spec("UT-PY-016")
def test_c_checks_before_the_file(mock_device: Factory, tmp_path: pathlib.Path) -> None:
    dev = mock_device(identifier="UT-PY-016-c")
    existing = tmp_path / "existing.csv"
    existing.write_bytes(b"keep\n")
    new = tmp_path / "new.csv"
    for path in (existing, new):
        with pytest.raises(ValueError):
            to_csv(dev, path, rate=4.1)
    assert existing.read_bytes() == b"keep\n"
    assert not new.exists()
    with pytest.raises(FileExistsError):
        to_csv(dev, existing)
    with pytest.raises(TypeError):
        to_csv(dev, new, overwrite=1)  # type: ignore[arg-type]
    assert not new.exists()
    assert to_csv(dev, existing, duration=0.5, overwrite=True) == 2
    lines = existing.read_text().splitlines(keepends=True)
    assert lines[0] == HEADER
    assert len(lines) == 3


INTERRUPTED = """
import pathlib
handler = ListHandler()
logging.getLogger("mp305").addHandler(handler)
logging.getLogger("mp305").setLevel(logging.INFO)
dev = Mp305._from_mock([testing.default_script()], identifier="UT-PY-016-d")
sigint_after(0.6)
outcome = None
try:
    mp305.to_csv(dev, PATH)
except KeyboardInterrupt:
    outcome = "KeyboardInterrupt"
    latency = time.monotonic() - MARKS["signal"]
dev.close()
report(
    outcome=outcome,
    latency=latency,
    text=pathlib.Path(PATH).read_text(),
    info=[m for (_, level, m, _) in handler.items if level == logging.INFO],
)
"""


@pytest.mark.spec("UT-PY-016")
def test_d_ctrl_c_leaves_a_complete_file(tmp_path: pathlib.Path) -> None:
    path = tmp_path / "log.csv"
    report, proc = run_child(f"PATH = {str(path)!r}\n" + INTERRUPTED)
    assert proc.returncode == 0, proc.stderr
    assert report["outcome"] == "KeyboardInterrupt"
    assert report["latency"] < 0.5
    lines = report["text"].splitlines(keepends=True)
    assert lines[0] == HEADER
    check_rows(lines[1:])
    stopped = [m for m in report["info"] if m.startswith("recording stopped")]
    assert stopped == [f"recording stopped after {len(lines) - 1} rows: KeyboardInterrupt"]


@pytest.mark.spec("UT-PY-016")
def test_e_a_lost_link_stops_the_recording(
    mock_device: Factory, tmp_path: pathlib.Path, caplog: pytest.LogCaptureFixture
) -> None:
    caplog.set_level(logging.INFO, logger="mp305")
    dev = mock_device([script(close_at_s=0.8)], identifier="UT-PY-016-e", reconnect=False)
    path = tmp_path / "log.csv"
    with pytest.raises(LinkLostError):
        to_csv(dev, path, rate=4.0)
    lines = path.read_text().splitlines(keepends=True)
    assert lines[0] == HEADER
    check_rows(lines[1:])
    stopped = [m for m in messages(caplog, "mp305", logging.INFO) if m.startswith("recording")]
    assert stopped == [f"recording stopped after {len(lines) - 1} rows: LinkLostError"]
