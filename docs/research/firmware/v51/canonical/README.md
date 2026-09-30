# MP305B V51 firmware evidence

This directory preserves reconstructed interoperability information from
all three images. Firmware binaries and Ghidra projects remain in external
scratchpads. Start with the [readable guide](../../readable.md),
[verification ledger](../../verification.md) or
[source provenance](sources.md).

## Function indexes

| Image | Discovered functions | Functions with warnings | Entry convention |
|---|---:|---:|---|
| [Main ARM](main/README.md) | 2455 | 203 | Processor address, image base `0x10000` |
| [PD 8051](pd/README.md) | 1007 | 102 | CODE address, image base `0x1000` |
| [BLE RV32](ble/README.md) | 232 | 53 | RAM/flash address, image base `0x1000` |
| [External WCH reference](sdk-reference/README.md) | 1047 | 68 | Separate reference image at `0x40000` |

The three ISDT images contain **3694 discovered function entries**. Two
BLE functions retain bad-data diagnostics. “Discovered” includes heuristic
entries and shared tails; it is not a count of original source functions
or a claim of complete semantic reconstruction. Ghidra completion is not
proof that its C output is correct.

Each image has per-function C, an instruction listing, function/call/
reference/symbol indexes and memory mappings. Canonical exports were
copied without silently fixing decompiler text. Address-derived filenames
replace colons with underscores for portability. Combined duplicate C
exports were omitted because every per-function file is retained.
[export-manifest.json](export-manifest.json) fingerprints canonical files.

## Other evidence

- [Memory-access index](../../../device/registers.md): raw records, resolved
  candidates, store expressions and unresolved pointers for all three images.
- [Current analysis summary](analysis-summary.json): function and instruction
  counts, warning counts and current offline case totals.
- [Portable verification result](verification/run-summary.json): 2835 passing
  cases, with scope and hashes per group.
- [Input comparisons](verification/input-verification.json): 16 additional
  merge-specific input and image-layout checks.
- [Restoration](verification/restoration.json) and
  [scatter-load recovery](verification/main-scatter-load.json).
- [Display initialization](verification/display-initialization.json),
  [settings normalization](settings-normalization.json),
  [charger tables](charger-limits.json), [USB descriptors](usb-descriptors.json),
  [GATT tables](gatt-table.json) and [8051 tables](pd-tables.tsv).

Latest executable records are in verification/. Earlier root-level result
files preserve the first pass and may contain fewer cases. The prior
analysis summary is retained as verification/analysis-summary-prior.json.
Do not add both old and new copies when counting checks.

Strings and candidate literals are navigation aids. A string does not
prove feature reachability, and a numeric literal does not by itself prove
a register access. All physical-chip names must carry their evidence level.
