# ADR-0015: Coverage of the Python binding crate, home of the Python unit tests, and the build settings they need

- Status: Accepted
- Date: 2026-10-01
- Decided by: user, on the agent's recommendation (G4 py, 2026-10-01)
- Related: ADR-0006, ADR-0008, AR-015, AR-040, DD-PY-062, DD-PY-063, the
  py DD's section 8 (decisions 1, 2, 4 and 14), IT-042, ST-036

## Context

ADR-0008 sets the coverage targets per component and the places where
tests of each level live, and says that changing either needs a new ADR.
The Python library design (docs/v-model/4-detailed-design/py.md) meets
four gaps in it:

1. ADR-0008 has no coverage row for the binding crate `mp305-py`. Its code
   (the blocking wait, the event feed, the conversions, the safety calls)
   runs only inside a Python interpreter, so `cargo llvm-cov --workspace`
   cannot exercise it, and it would dilute the figure for the rest of
   `mp305-core`.
2. The level table gives Python tests only `tests/integration/`,
   `tests/system/` and `tests/acceptance/`. The pure Python package has
   unit test entries (UT-PY) that belong to none of them.
3. The wheel always enables the core's `mock` feature (py DD, decision 1).
   Cargo unifies features within one invocation, so a workspace build
   compiles the core with `mock`, and a missing `cfg` gate in the core
   would go unnoticed.
4. Two settings of the user's machine break the documented commands: a
   stripped `cdylib` does not load on the user's macOS ("mis-aligned
   LINKEDIT string pool"), and maturin refuses to run while `CONDA_PREFIX`
   is set.

## Decision

- Coverage: the binding crate `mp305-py` gets the target of 80 % of
  lines, measured through the Python tests with an instrumented extension
  (`cargo llvm-cov show-env`, then `maturin develop`, then pytest over
  `tests/unit` and `tests/integration`, then `cargo llvm-cov report -p
  mp305-py --fail-under-lines 80`). The paths that only run with a supply
  count inside the 80 %. The workspace coverage command excludes the
  crate (`--exclude mp305-py`), so its files are counted once. The pure
  Python code keeps ADR-0008's 90 %, measured with `pytest --cov`.
- Test layout: Python unit tests live in `tests/unit/`, one
  `@pytest.mark.spec("UT-PY-nnn")` per test. Every directory under
  `tests/` is a package (`__init__.py`).
- Commands: `cargo clippy -p mp305-core --all-targets -- -D warnings`
  joins the gates; it builds the core without the `mock` feature. The
  app's release binary is built with `cargo build --release -p mp305-app`
  for the same reason. `cargo test`, `clippy` and `llvm-cov` over the
  workspace need a Python 3.10 or later interpreter, which PyO3 links into
  the binding crate's test binary.
- Build settings: the workspace `Cargo.toml` sets
  `[profile.release] strip = "none"`, and the maturin command is
  `env -u CONDA_PREFIX uv run maturin develop -m crates/mp305-py/Cargo.toml`.

AGENTS.md's Commands section, level table and repository layout carry
these changes.

## Alternatives considered

- Exclude `crates/mp305-py/src/` from coverage and verify it only through
  the behaviour of the Python tests: the glue is where conversions go
  wrong silently, and without a number nobody sees a path that no test
  reaches. Lost on visibility.
- Put the Python unit tests into `tests/integration/` with UT IDs: the
  directory would no longer say what level a test verifies, against the
  table's purpose. Lost on clarity.
- Keep the mock behind a cargo feature that only `maturin develop`
  enables: the tested wheel would differ from the shipped one, and the
  acceptance tests run the library's mock test on the installed release
  wheel (AT-034). Lost on "test what ships".
- Keep cargo's default strip and build release wheels only on CI runners:
  the user's Mac could then not test a release wheel locally, which ST-036
  and the acceptance tests need.

## Consequences

The gates grow by one clippy run, one coverage block for the binding
crate and one pytest coverage run. The instrumented extension must not
stay installed, so the coverage block ends with a clean and a plain
`maturin develop`. Subprocess tests must let the child exit normally, or
its coverage profile is not written. Release binaries are larger because
they keep their symbols; the profile also governs the app's binary. A
change of the 80 % target or of the test directories needs a further ADR.
