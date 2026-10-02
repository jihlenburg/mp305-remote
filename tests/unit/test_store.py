"""UT-PY-010: the host ID and the default state directory."""

from __future__ import annotations

import pathlib
import re

import pytest

import mp305


@pytest.mark.spec("UT-PY-010")
def test_host_id_and_default_state_dir(tmp_path: pathlib.Path) -> None:
    here = tmp_path / "here"
    other = tmp_path / "other"
    first = mp305.host_id(here)
    second = mp305.host_id(here)
    assert len(first) == 16
    assert first == second
    assert first != bytes(16)
    content = (here / "host_id").read_text()
    assert re.fullmatch(r"[0-9a-f]{32}\n", content)
    assert bytes.fromhex(content.strip()) == first
    assert mp305.host_id(str(other)) != first
    state = mp305.default_state_dir()
    assert isinstance(state, pathlib.Path)
    assert state.is_absolute()
    assert "mp305" in state.parts
