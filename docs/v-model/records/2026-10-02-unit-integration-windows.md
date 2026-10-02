# Verification record: unit and integration tests on Windows

Date: 2026-10-02. Level: unit and integration (every UT and IT entry
with an automated test, and the system tests that need no supply). Scope:
the whole workspace and the Python library, built and run on Windows for
the first time.

Commit: `6250dd0`. The run was made on the source archive of that commit
from the public repository. Two findings of the earlier attempts were
fixed in the commits `b92d669` and `6250dd0` (below).

OS: Windows 11 Pro 22H2 (10.0.22621), ARM64, a Parallels VM on the
user's Mac (4 cores, 16 GB). The toolchain is the x86_64 one, the
project's Windows target (SR-036), running under Windows' x64 emulation:
Rust 1.99.0 (`stable-x86_64-pc-windows-msvc`), clippy 0.1.99, Visual
Studio Build Tools 2022 (C++ workload), CPython 3.10.22 x86_64 through uv
0.12.22, pytest 9.1.1. Transport: the mock. No Bluetooth adapter was
attached to the VM during the run, no scan was started and no device was
opened. Firmware: not applicable.

## Commands

In PowerShell, with the interpreter's directory on the `PATH` and
`PYO3_PYTHON` and `UV_PYTHON` set to that interpreter:

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo clippy -p mp305-core --all-targets -- -D warnings
cargo test -p mp305-core
cargo test -p mp305-app
cargo test -p mp305-py --lib
cargo build --release -p mp305-app
uv run maturin develop -m crates/mp305-py/Cargo.toml
uv run --no-sync pytest -q -rs
uv run --no-sync ruff check
uv run --no-sync mypy python/mp305
```

## Results

| Gate | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| `cargo clippy --workspace --all-targets -- -D warnings` | pass |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | pass |
| `cargo test -p mp305-core` | pass: 268 in-crate, 6 earlier external and 67 integration, 14 doctests (355) |
| `cargo test -p mp305-app` | pass: 129 unit and 3 integration |
| `cargo test -p mp305-py --lib` | 34 tests; pass in 18 runs, one test failed in 4 runs, finding 3 |
| `cargo build --release -p mp305-app` | pass (`mp305-app.exe`, 18 MB; not run) |
| `maturin develop` | pass |
| `pytest` | pass: 196 tests, 6 skipped, the 52 HIL tests deselected |
| `ruff check`, `mypy` | pass |

Not run on Windows: `cargo doc`, the coverage measurements and the
traceability check (they do not depend on the OS).

Tests that do not run on Windows, each with its reason in the code:

| Entry | Test | Reason |
|---|---|---|
| UT-STORE-003 | the unreadable `host_id` case | Unix file modes (`cfg(unix)`); the entry's other test runs |
| UT-PY-025 | the fork test | Windows has no `fork` |
| UT-PY-026 (a) | the fresh-home subprocess | Windows takes its known folders from the shell, not from the environment |
| UT-PY-024 (c), (d), (i) | the child process that ends by `SIGINT` | checks the POSIX exit by a signal |
| ST-037 | the CSV comparison | skipped on every OS until it is given its two files |

So the wait at exit for a running output-off or close after an uncaught
Ctrl-C (DD-PY-008) is not verified on Windows at this level.

## Findings

1. Windows keeps system time in steps of 100 ns. A test of UT-PY-021 (d)
   round-tripped a time ending in 999 ns and got 900 ns back. The test
   value is now a multiple of 100 ns (commit `b92d669`); the library is
   unchanged. On Windows a reading's wall time has that resolution.
2. A test of UT-APP-023 compared the recording placeholder with a string
   that had a forward slash written into it; on Windows the app joins the
   directory and the name with a backslash, as it should. The test now
   builds its expectation with the path API (commit `6250dd0`); the app is
   unchanged.
3. `feed::tests::waiters_wake_at_the_end_of_the_source` (UT-PY-022 (e))
   failed four times and passed 18 times. Every failure was the first run
   of a freshly built test binary; every later run passed. Its entry asks
   that both waiters wake "within 10 ms" of the close. Under the x64
   emulation a new binary is translated at its first execution, which
   fits the pattern, so this may never show on a native x86_64 Windows.
   The test is unchanged. Py DD revision 6, drafted and pending approval,
   would allow 100 ms (the entry's point is that the waiters do not run
   into their 1 s timeout).
4. The binding crate's test binary needs the Python DLL on the `PATH`
   (the interpreter's directory). Without it the binary ends with
   `STATUS_DLL_NOT_FOUND` (exit code -1073741515) before any test runs.
   AGENTS.md's Commands section now says so.
5. A procedure note, not a code finding: files extracted from a source
   archive carry the commit's time, which can be older than the last
   build, and cargo then takes a changed file for unchanged. One round of
   this run tested a stale binary that way; the files are now stamped
   after extraction.

Findings 1 and 2 were errors in tests, not in the products. Every UT, IT
and supply-free ST test that runs on Windows passes there, apart from the
intermittent case of finding 3.

## Not covered

- Nothing on the supply: discovery and the transports on the Windows
  Bluetooth stack and HID are untested apart from the scan of the spike
  `vm_dongle_scan`.
- The app was built, not run.
- A native x86_64 machine, a native ARM64 build, Windows 10 (SR-036 names
  Windows 10 22H2 as the minimum; this was Windows 11 22H2), and the
  wheel build.
