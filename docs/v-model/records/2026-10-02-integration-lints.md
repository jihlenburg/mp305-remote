# Verification record: integration inspection, the lint settings

Date: 2026-10-02. Level: integration (IT-004). Method: inspection.

Commit: uncommitted. Diff summary: the lint attributes added to the crate roots
(`crates/mp305-core/src/lib.rs`, `crates/mp305-app/src/lib.rs` and `main.rs`,
`crates/mp305-py/src/lib.rs`), where before only the manifests' `[lints]`
tables set them.

The inspection was made by a delegated agent that read the files without
changing them and gave file and line for every point; its tables were
checked in the main session, and the points that the fixes of this commit
touch were inspected again there on the final tree.

## IT-004 (AR-004): pass with the notes below

| Point | Result |
|---|---|
| `cargo clippy --workspace --all-targets -- -D warnings` | clean (main session, on the final tree) |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` (the core without its `mock` feature) | clean |
| `forbid(unsafe_code)` in the core and the app | present as crate-root attributes and in the workspace manifest |
| `deny(unsafe_code)` in the Python crate | present |
| `unsafe` in the Python crate | none; no `allow(unsafe_code)` anywhere, note 1 |
| `deny(missing_docs)`, `warn(clippy::missing_docs_in_private_items)` and the five clippy lints in all three crates | present as crate-root attributes and in the manifests, note 2 |
| The crate roots relax the five clippy lints for test builds only | present (`cfg_attr(test, allow(..))`) |

## Notes and open points

1. The Python crate has no `ffi` module: PyO3's macros need no `unsafe`
   in the crate's own code. AR-004 and IT-004 speak of an `allow` "only on
   `ffi`"; the corrected wording is drafted, approval pending.
2. The inspection first found most lints only in the manifests' `[lints]`
   tables. The attributes were added to the crate roots with this commit,
   so that AR-004, ADR-0008 and AGENTS.md hold as written; the manifest
   tables stay.
3. The entry's method says "inspection plus CI". The repository has no
   CI run on pushes; the clippy gates are run locally before every commit
   and recorded in the verification records.
