# V51 evidence inventory

Analyzed published firmware: 1.6.0.51. Existing hardware captures concern a
unit reporting 1.6.0.40; those captures do not validate V51 electrical behavior.

| Bundle | Contents and status |
|---|---|
| [Canonical reconstruction](canonical/README.md) | 2455 main, 232 BLE and 1007 PD function exports, plus 1047 separate WCH reference entries; readable C, register accesses and the earlier verification run |
| [Recovered independent analysis](independent/README.md) | 2453 main, 255 CH58x and 380 PD entries; reviewed command/host-link/bridge notes; 33 completed probe jobs, 657 asserted cases and 324 observed command rows |
| [Ghidra snapshots](ghidra/README.md) | All seven program interpretations as XML and JSON without firmware bytes, with mappings and restoration results |
| [Reference registers](../../reference/registers/README.md) | Original textual SVD/header inputs used for candidate peripheral naming |

These entry sets overlap and differ in function boundaries, callback recovery,
RAM aliases and naming. Their counts cannot be added as code coverage. Keep
both interpretations when comparing another release. The canonical PD analysis
has substantially more recovered table targets; independent main/bridge work
adds reviewed names and behavioral evidence.

The WebLink main application copy differs from the restored container in four
identity bytes. Its companion slices match. Exact hashes and comparison details
are in the [recovery record](independent/verification/input-comparison.json).
No firmware images or Ghidra project databases are stored here.

Use [the workflow](../../workflow/README.md) for restoration, future imports,
manual comparison and evidence publication. Historical logs retain their
recorded paths; [the relocation map](../../structure-map.json) resolves them.
