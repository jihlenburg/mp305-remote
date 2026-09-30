# Preserved Ghidra analysis

Seven program snapshots exported on 2026-09-30 using Ghidra 12.1.3 and
OpenJDK 21. The [index](index.json) records input and export hashes.
[Export commands](export-jobs.json) retain the original external project paths.

**No firmware memory contents are included.** Each snapshot has:

- `analysis.xml`: Ghidra's standard analysis XML, with memory contents disabled;
- `program.json`: memory ranges, permissions and hashes, external input offsets,
  function definitions and bodies, signature provenance, comments, no-return and
  thunk attributes, variable metadata, program options and function fingerprints.

Types, labels, references, instruction ranges, defined data, context, comments,
bookmarks and equates are preserved in the XML. The JSON supplements properties
that the XML importer changes or omits. Original project databases remain in
the external scratchpads because they contain firmware bytes.

## Snapshot inventory and restoration checks

| Snapshot | Functions | Core restore comparison | Functions with variable differences |
|---|---:|---|---:|
| [Canonical main](canonical-main/program.json) | 2455 | Pass | 0 |
| [Canonical BLE](canonical-ble/program.json) | 232 | Pass | 0 |
| [Canonical PD](canonical-pd/program.json) | 1007 | Pass | 0 |
| [Recovered main](recovered-main/program.json) | 2453 | Pass | 64 |
| [Recovered BLE](recovered-ble/program.json) | 255 | Pass | 1 |
| [Recovered PD](recovered-pd/program.json) | 380 | Pass | 0 |
| [SDK reference](sdk-reference/program.json) | 1047 | Pass | 3 |

The 7829 entries represent seven overlapping interpretations, including a
separate SDK image. This is an archival count, not firmware coverage.

All seven snapshots were restored into fresh external projects and re-exported.
The core comparison requires identical mapped-byte hashes, memory permissions,
function names/prototypes/bodies/attributes and instruction fingerprints. It
also requires equality of XML types, defined data, code ranges, references,
external entry points, register context, comments, bookmarks and equates.
See [the summary](verification/summary.json) and each snapshot's JSON/log under
[verification](verification/).

### Remaining importer differences

These are **not lossless database restores**:

- Ghidra's importer emits a `FunctionPurgeAnalysisCmd` unsupported-operation
  diagnostic and, in some programs, null-function diagnostics. The restoration
  script reconciles function entries, bodies, thunks and signature provenance
  before comparing the result. Unexpected errors fail the run.
- XML import can infer extra functions, widen bodies, or infer a thunk where
  the saved interpretation was a normal function. Explicit metadata corrects
  those changes. The canonical PD import also reports three failed function
  creations; their final restored entries and definitions pass comparison.
- The SDK has a zero-instruction placeholder at `ram:20000010` over defined
  data. Restoration preserves that original inconsistency. It is not proof
  of an executable function there.
- Every restored symbol table differs from its original XML: it contains extra
  function symbols after explicit thunk restoration. Main also has a changed
  switch-default symbol. The exact original/restored rows are in the
  `*-symbol-differences.json` files.
- Local-variable and stack metadata differ in 64 recovered main functions,
  one recovered bridge function and three SDK functions. The original XML
  and JSON retain the saved values. Ghidra can add inferred locals or reject
  overlapping variable storage; the restore script does not silently call
  these equivalent. The affected entries are listed in each result JSON.
- Primitive program options are restored. Other option values remain archived
  in JSON, but automatic restoration does not apply them. Project history,
  undo state, UI layout and other database-only state are not XML exports.

The recorded `passed` field applies to the explicitly listed core checks;
`symbol_table_xml_equal`, `functions_xml_equal` and `variable_metadata_equal`
report the additional differences separately. Keep these qualifiers when
citing the results.

## Use the archive

Follow [the restore procedure](../../../workflow/README.md#restore-an-existing-v51-analysis).
Supply every required original input by its SHA-256 hash. The two main images
are different: the WebLink copy has four `FF` identity bytes where the decoded
container has its identity magic. Initialized RAM and the SDK reference image
also remain external. The importer rejects missing or changed hashes before
creating its new project.

For future firmware, start with a fresh import and
[review suggested function matches](../../../workflow/README.md#4-compare-and-promote-names-with-evidence).
Do not restore these address-specific annotations onto different bytes.
The [workflow check](verification/workflow.json) decoded V51, imported a fresh
BLE program, produced 203 unique instruction-hash suggestions and 14 short
function suggestions, left 15 entries unmatched, and verified rejection of
wrong input hashes and a corrupted container. No names were transferred.
