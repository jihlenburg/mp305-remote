# App commit verification

Date: 2026-10-05. Commit: staged, uncommitted on
`2528dabe26ca43a08994e11ed2367fa2647b401f`; the resulting approved app DD
revision 5 commit is identified by tag `g4-app-rev5-approved`.
OS: macOS 27.0.1, arm64. Transport: mock or none. Firmware: not applicable.

Scope: the UI, local names, tests, fonts, baselines and their documentation.
The separate uncommitted HID owner-thread change and its spike were excluded
from the index. The earlier hardware evidence used that local HID change,
as already stated in its record; this commit does not claim to deliver it.

The staged tree was exported with `git checkout-index --all` to
`/var/folders/0z/2bt3mdt16rv35drymm52hl_m0000gn/T/mp305-commit-1iysoqtk/`.
Commands below ran there, with `CARGO_TARGET_DIR=/Users/jihlenburg/mp305b/target`
for the Cargo commands. Its generated traceability matrix was staged directly
from this clean copy so that it describes the committed source set.

| Command | Result |
|---|---|
| `python3 scripts/check_traceability.py` | pass, zero defects |
| `python3 scripts/check_traceability.py --check` | pass |
| `cargo test -p mp305-app` | pass, 140 app unit tests and 3 integration tests |
| `cargo clippy -p mp305-app --all-targets -- -D warnings` | pass |
| `cargo fmt --all --check` | pass |

The app tests cover UT-APP-001 to UT-APP-033 where automated, including the
15 reviewed screenshots of UT-APP-031. UT-APP-020 remains the inspection in
the [decimal correction record](2026-10-05-unit-app-decimals.md).
IT-041 passes through the three external app tests. No hardware was operated
for this commit check.
