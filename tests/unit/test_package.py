"""UT-PY-020: packaging, typing, lints and the build setup."""

from __future__ import annotations

import importlib.resources
import importlib.util
import os
import re
import shutil
import subprocess
import sys
from typing import Any

import pytest

import mp305
from tests.unit.support import ROOT


if sys.version_info >= (3, 11):
    import tomllib
else:  # pragma: no cover - only on Python 3.10
    import tomli as tomllib

ALL = [
    "Mp305",
    "discover",
    "host_id",
    "default_state_dir",
    "set_log_level",
    "stream",
    "to_csv",
    "ramp",
    "VOLTAGE_RANGE",
    "CURRENT_RANGE",
    "Reading",
    "Info",
    "Found",
    "Limits",
    "Settings",
    "Counters",
    "Event",
    "EventKind",
    "Mode",
    "LiveMode",
    "Fault",
    "Mp305Error",
    "NotFoundError",
    "ConnectionDeniedError",
    "SetpointRangeError",
    "CommandRejectedError",
    "RemoteControlDeniedError",
    "RemoteControlLostError",
    "ModeError",
    "FaultActiveError",
    "Mp305TimeoutError",
    "LinkLostError",
    "Transport",
    "LinkStateName",
    "RemoteStateName",
    "PromptKind",
    "Quantity",
    "__version__",
]
CRATE = ROOT / "crates" / "mp305-py"


def run(args: list[str], env: dict[str, str] | None = None) -> subprocess.CompletedProcess[str]:
    """Runs a tool from the repository root."""
    return subprocess.run(
        args, cwd=ROOT, capture_output=True, text=True, timeout=900, env=env
    )


def needs(module: str) -> None:
    """Skips the test when a development tool is not installed.

    The wheel jobs run `tests/unit` in a clean environment without the
    development tools; the repository's own gates run them.
    """
    if importlib.util.find_spec(module) is None:
        pytest.skip(f"{module} is not installed (a clean wheel environment)")


@pytest.mark.spec("UT-PY-020")
def test_mypy_and_ruff_are_clean() -> None:
    needs("mypy")
    needs("ruff")
    mypy = run([sys.executable, "-m", "mypy"])
    assert mypy.returncode == 0, mypy.stdout + mypy.stderr
    ruff = run([sys.executable, "-m", "ruff", "check"])
    assert ruff.returncode == 0, ruff.stdout + ruff.stderr


@pytest.mark.spec("UT-PY-020")
def test_the_stub_matches_the_module() -> None:
    needs("mypy")
    # The allowlist names the tuple aliases that exist only in the stub.
    allowlist = str(ROOT / "tests" / "unit" / "stubtest-allowlist.txt")
    stubtest = run(
        [sys.executable, "-m", "mypy.stubtest", "mp305._native", "--allowlist", allowlist]
    )
    assert stubtest.returncode == 0, stubtest.stdout + stubtest.stderr


@pytest.mark.spec("UT-PY-020")
def test_the_public_names_and_the_typing_files() -> None:
    assert mp305.__all__ == ALL
    for name in ALL:
        assert hasattr(mp305, name), name
    assert not hasattr(mp305, "testing") or "testing" not in mp305.__all__
    files = importlib.resources.files("mp305")
    assert files.joinpath("py.typed").is_file()
    assert files.joinpath("_native.pyi").is_file()


def crate_sources() -> list[tuple[str, str]]:
    """The Rust sources of the binding crate: (name, text)."""
    return [(p.name, p.read_text()) for p in sorted((CRATE / "src").glob("*.rs"))]


@pytest.mark.spec("UT-PY-020")
def test_no_unsafe_and_frozen_classes() -> None:
    unsafe = re.compile(
        r"\bunsafe\s*(\{|fn\b|impl\b|extern\b|trait\b)|allow\s*\(\s*unsafe_code\s*\)"
    )
    sources = crate_sources()
    assert sources
    for name, text in sources:
        code = "\n".join(line.split("//")[0] for line in text.splitlines())
        assert not unsafe.search(code), name
        for attribute in re.findall(r"#\[pyclass[^\]]*\]", code):
            assert "frozen" in attribute, (name, attribute)
    lib = (CRATE / "src" / "lib.rs").read_text()
    assert "#![deny(unsafe_code)]" in lib


@pytest.mark.spec("UT-PY-020")
def test_clippy_config_and_clippy() -> None:
    clippy = tomllib.loads((CRATE / "clippy.toml").read_text())
    paths = {entry["path"] for entry in clippy["disallowed-methods"]}
    assert paths == {
        f"core::time::Duration::{m}"
        for m in ("from_secs_f64", "from_secs_f32", "mul_f64", "mul_f32", "div_f64", "div_f32")
    }
    manifest = tomllib.loads((CRATE / "Cargo.toml").read_text())
    assert manifest["lints"]["clippy"]["disallowed_methods"] == "deny"
    needs("maturin")
    if shutil.which("cargo") is None:
        pytest.skip("cargo is not installed (a clean wheel environment)")
    # The coverage gate (`cargo llvm-cov show-env`) instruments the build
    # through these variables, its own `RUSTC_WRAPPER` included; the lint run
    # uses the plain build.
    instrumented = "__CARGO_LLVM_COV_RUSTC_WRAPPER" in os.environ
    env = {
        k: v
        for k, v in os.environ.items()
        if not k.startswith(("CARGO_LLVM_COV", "__CARGO_LLVM_COV", "LLVM_PROFILE"))
        and not (instrumented and k == "RUSTC_WRAPPER")
    }
    result = run(
        ["cargo", "clippy", "-p", "mp305-py", "--all-targets", "--", "-D", "warnings"], env
    )
    assert result.returncode == 0, result.stderr[-4000:]


@pytest.mark.spec("UT-PY-020")
def test_the_readme() -> None:
    text = " ".join((CRATE / "README.md").read_text().split())
    for part in (
        "Set a hardware current limit and OCP mode on the supply's front panel",
        "Keep only a safe load on the output",
        "The supply keeps the output on when the link drops",
        "Prefer USB over Bluetooth for unattended runs",
        "A second Ctrl-C while `close` or `output_off` is finishing, or a killed process, "
        "can leave the output on, and the next connect then warns",
        "start method spawn or forkserver",
    ):
        assert part in text, part


@pytest.mark.spec("UT-PY-020")
def test_pyproject() -> None:
    data: dict[str, Any] = tomllib.loads((ROOT / "pyproject.toml").read_text())
    build = data["build-system"]
    assert build["requires"] == ["maturin>=1.9.4,<2.0"]
    assert build["build-backend"] == "maturin"
    project = data["project"]
    assert project["name"] == "mp305"
    assert project["dynamic"] == ["version"]
    assert project["description"]
    assert project["readme"] == "crates/mp305-py/README.md"
    assert project["requires-python"] == ">=3.10"
    assert project["license"] == "LicenseRef-GPL-3.0-only-with-Commons-Clause-1.0"
    assert project["license-files"] == ["LICENSE"]
    assert project.get("dependencies", []) == []
    classifiers = project["classifiers"]
    for os_name in ("MacOS", "POSIX :: Linux", "Microsoft :: Windows"):
        assert f"Operating System :: {os_name}" in classifiers
    for minor in range(10, 15):
        assert f"Programming Language :: Python :: 3.{minor}" in classifiers
    maturin = data["tool"]["maturin"]
    assert maturin["manifest-path"] == "crates/mp305-py/Cargo.toml"
    assert maturin["module-name"] == "mp305._native"
    assert maturin["python-source"] == "python"
    assert maturin["exclude"] == ["**/__pycache__/**"]
    assert "strip" not in maturin
    dev = data["dependency-groups"]["dev"]
    for package in ("maturin>=1.9.4", "pytest", "pytest-cov", "ruff", "mypy", "numpy"):
        assert package in dev
    assert "tomli; python_version < '3.11'" in dev
    pytest_options = data["tool"]["pytest"]["ini_options"]
    assert {m.split(":")[0].split("(")[0] for m in pytest_options["markers"]} == {"hil", "spec"}
    assert pytest_options["addopts"] == "-m 'not hil' --strict-markers"
    assert pytest_options["testpaths"] == ["tests"]
    ruff = data["tool"]["ruff"]
    assert (ruff["target-version"], ruff["line-length"]) == ("py310", 100)
    # DD-PY-060 names ["spikes"]; docs/research is excluded as well because its
    # research scripts may not be edited with the implementation (reported).
    assert ruff["extend-exclude"] == ["spikes", "docs/research"]
    assert ruff["lint"]["select"] == ["E", "W", "F", "B", "S", "D"]
    assert ruff["lint"]["pydocstyle"]["convention"] == "google"
    assert ruff["lint"]["per-file-ignores"]["tests/**"] == ["S101", "S603", "D"]
    mypy = data["tool"]["mypy"]
    assert (mypy["strict"], mypy["python_version"], mypy["files"]) == (
        True,
        "3.10",
        ["python/mp305"],
    )
    coverage = data["tool"]["coverage"]
    assert coverage["run"] == {"source": ["mp305"], "parallel": True, "patch": ["subprocess"]}
    assert coverage["report"]["fail_under"] == 90


@pytest.mark.spec("UT-PY-020")
def test_the_build_setup_and_the_layout() -> None:
    manifest = (CRATE / "Cargo.toml").read_text()
    data = tomllib.loads(manifest)
    assert data["lib"]["crate-type"] == ["cdylib", "rlib"]
    assert data["lib"]["name"] == "mp305_py"
    assert "extension-module" not in manifest
    assert "abi3-py310" in data["dependencies"]["pyo3"]["features"]
    assert "add_libpython_rpath_link_args" in (CRATE / "build.rs").read_text()
    workspace = tomllib.loads((ROOT / "Cargo.toml").read_text())
    assert workspace["profile"]["release"]["strip"] == "none"
    assert (ROOT / ".python-version").read_text().strip() == "3.10"
    for level in ("", "unit", "integration", "system", "acceptance"):
        assert (ROOT / "tests" / level / "__init__.py").is_file(), level


@pytest.mark.spec("UT-PY-020")
def test_the_wheel_workflow() -> None:
    text = (ROOT / ".github" / "workflows" / "wheels.yml").read_text()
    on = text.split("\non:", 1)[1].split("\njobs:", 1)[0]
    assert "workflow_dispatch" in on
    assert "tags:" in on
    assert "pull_request" not in on
    assert "branches" not in on
    for target in (
        "aarch64-apple-darwin",
        "x86_64-apple-darwin",
        "x86_64-unknown-linux-gnu",
        "aarch64-unknown-linux-gnu",
        "x86_64-pc-windows-msvc",
    ):
        assert f"target: {target}" in text, target
    assert 'MACOSX_DEPLOYMENT_TARGET: "13.0"' in text
    assert "--compatibility manylinux_2_35" in text
    assert "ubuntu-22.04" in text
    for step in ("python-version: \"3.10\"", "import mp305", "pytest tests/unit"):
        assert step in text, step
    assert "upload-artifact" in text
