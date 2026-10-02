"""UT-PY-026: the state directory of a mock session and the unclean-exit marker."""

from __future__ import annotations

import logging
import os
import pathlib
import sys
from collections.abc import Callable

import pytest

from mp305 import Mp305, testing
from tests.unit import frames
from tests.unit.support import messages, run_child

Factory = Callable[..., Mp305]
UNCLEAN = "A previous session may have left the output on (marker written "


def first_bind_payload(rec: testing.MockRecord) -> bytes:
    """The payload of the first `0x18` sent."""
    return frames.sent(rec.sent(), 0x18)[0].payload


@pytest.mark.spec("UT-PY-026")
def test_a_no_state_dir_touches_no_file(mock_device: Factory) -> None:
    rec = testing.MockRecord()
    mock_device(identifier="UT-PY-026-a", record=rec)
    assert first_bind_payload(rec).startswith(testing.MOCK_HOST_ID)


CHILD_A = """
rec = testing.MockRecord()
dev = Mp305._from_mock([testing.default_script()], identifier="UT-PY-026-a2", record=rec)
payload = [f.payload for f in rec.sent() if f.opcode == 0x18][0]
dev.close()
report(starts=payload.startswith(testing.MOCK_HOST_ID))
"""


# Windows takes its known folders from the shell, not from the environment.
@pytest.mark.skipif(
    sys.platform == "win32", reason="POSIX only: the home is not from the environment"
)
@pytest.mark.spec("UT-PY-026")
def test_a_no_state_dir_in_a_fresh_home(tmp_path: pathlib.Path) -> None:
    home = tmp_path / "home"
    home.mkdir()
    env = dict(os.environ)
    env.update(
        HOME=str(home),
        XDG_STATE_HOME=str(home / "state"),
        XDG_DATA_HOME=str(home / "data"),
    )
    report, proc = run_child(CHILD_A, env=env)
    assert proc.returncode == 0, proc.stderr
    assert report["starts"] is True
    assert list(home.iterdir()) == []


@pytest.mark.spec("UT-PY-026")
def test_b_a_state_dir(mock_device: Factory, tmp_path: pathlib.Path) -> None:
    import mp305

    rec = testing.MockRecord()
    mock_device(identifier="UT-PY-026-b", record=rec, state_dir=tmp_path)
    assert (tmp_path / "host_id").exists()
    assert first_bind_payload(rec).startswith(mp305.host_id(tmp_path))


CHILD_C = """
import os, pathlib
d = pathlib.Path(STATE)
s = script(replies=[c3_reply(testing.c3(output=1))])
dev = Mp305._from_mock([s], state_dir=d, identifier="UT-PY-026-c")
dev.request_remote_control()
deadline = time.monotonic() + 2.0
while time.monotonic() < deadline:
    if list((d / "markers").glob("*.marker")) if (d / "markers").exists() else []:
        break
    time.sleep(0.02)
os._exit(0)
"""


@pytest.mark.spec("UT-PY-026")
def test_c_d_the_marker_of_a_killed_session(
    mock_device: Factory, tmp_path: pathlib.Path, caplog: pytest.LogCaptureFixture
) -> None:
    _, proc = run_child(f"STATE = {str(tmp_path)!r}\n" + CHILD_C)
    assert proc.returncode == 0, proc.stderr
    assert list((tmp_path / "markers").glob("*.marker"))
    dev = mock_device(identifier="UT-PY-026-c", state_dir=tmp_path)
    warning = dev.unclean_exit_warning
    assert warning is not None and warning.startswith(UNCLEAN)
    assert [m for m in messages(caplog, "mp305", logging.WARNING) if m.startswith(UNCLEAN)] == [
        warning
    ]
    # (d)
    dev.close()
    assert list((tmp_path / "markers").glob("*.marker")) == []
    again = mock_device(identifier="UT-PY-026-c", state_dir=tmp_path)
    assert again.unclean_exit_warning is None
