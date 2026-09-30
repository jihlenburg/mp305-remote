# Firmware analysis workflow

This workflow preserves the V51 work and provides a starting point for a future
release. It uses local files and offline tools. Original firmware and Ghidra
project databases stay in a scratch directory outside the repository.

Start with [the research index](../README.md) for findings and
[the V51 inventory](../firmware/v51/README.md) for existing evidence.
The maintained tools are in [firmware_workflow](../../../spikes/firmware_workflow/README.md).

## What is preserved

- Decompiled C, per-function exports, entry lists, references, strings,
  register-access inventories, name aliases and review notes.
- Seven [Ghidra analysis snapshots](../firmware/v51/ghidra/README.md): the
  canonical main, BLE and PD programs; the WCH reference; and all three
  independently recovered programs. These are separate interpretations.
- Standard Ghidra XML with memory contents disabled, plus JSON for memory
  mappings, byte hashes, original input slices, function bodies and attributes,
  variable metadata, program options and comparison fingerprints.
- Analysis and repair scripts, probe inputs, expected results, logs, dependency
  versions, input hashes and restoration checks.
- [Historical workspace material](../firmware/v51/independent/historical/README.md),
  retained for provenance. Use the reviewed notes and maintained runners first.

The snapshots preserve the exported analysis without embedding executable
images. They are not full Ghidra database backups. XML import changes some
storage and symbol metadata; exact differences and restoration results are
recorded beside the snapshots. Keep the private projects as well when available.

## Analyze a new release

### 1. Stage and identify the inputs

Run from the repository root. Choose a fresh directory outside it:

```sh
python3 spikes/firmware_workflow/scripts/stage_release.py \
  --firmware /path/to/MP305B-next.fwd \
  --scratch /path/to/scratch/mp305b-next \
  --release next
```

The script implements the documented 32-byte FWD header and word transform,
checks sizes and checksum, and checks the main Thumb reset vector against the
header's load address. It records the header, input hashes, restored images,
printable strings and candidate companion split offsets. It rejects incompatible
containers; investigate a format change before changing the decoder.

Inspect `release.json` and the companion start-up instructions. V51 has a
`0xB000` PD slice followed by CH58x code; **this size is not a future-release
assumption**. Once the boundary is established, stage again into a different
fresh directory with `--pd-size 0x...`. `--companion-base` defaults to the V51
candidate `0x1000`; verify both companion mappings before relying on addresses.
The discovery record explicitly labels these configured bases as candidates.

Do not equate a file name with the version installed on a device. Record image
identity bytes and version replies separately, including the transport and date
for any later hardware capture.

### 2. Import fresh Ghidra programs

Set `JAVA_HOME` for the selected Ghidra version, then:

```sh
python3 spikes/firmware_workflow/scripts/import_release.py \
  /path/to/scratch/mp305b-next \
  --ghidra /path/to/ghidra
```

Use `--image main-arm.bin`, `--image ble-riscv.bin` or `--image pd-8051.bin`
to restrict the import. The tool verifies staged hashes, refuses existing
projects and exports the initial analysis. It does not apply V51 addresses.
A successful import is only a starting point: raw auto-analysis misses code
copied to RAM, callbacks and table-driven control flow.

### 3. Reconstruct memory and execution entry points

For each image, record the instructions supporting every load address and copy:

| Image | First checks | V51 evidence to consult |
|---|---|---|
| Main ARM | Vectors and VTOR, reset chain, initialized RAM, compressed scatter loader, Thumb context, callbacks, scheduler and non-returning paths | [Firmware](../firmware.md), [architecture](../firmware/architecture.md), [scatter record](../firmware/v51/canonical/main-scatter-load.json) |
| CH58x RISC-V | PC-relative global pointer, flash-to-RAM copies, traps, callbacks, ROM call table, task events and transport buffers | [Bridge notes](../firmware/v51/independent/notes/ch58x.md), [SDK map](../firmware/v51/canonical/wch-sdk-api.tsv) |
| PD 8051 | CODE/XDATA/SFR spaces, LJMP vectors, register banks, computed dispatch tables and interrupt entry points | [PD tables](../firmware/v51/canonical/pd-tables.tsv), [register inventory](../device/registers.md) |

V51's exact main MCU and PD part are unresolved. Vendor SVD matches are
candidate register names, not silicon identification. Unobserved peripherals
and board connections remain inferred. The SDK reference is a comparison
input, not a dump of the library installed in the device.

Port the existing Ghidra helpers only after reviewing their embedded addresses,
lengths, processor assumptions and function-boundary decisions. Keep imported
and reviewed states separate in the external workspace.

### 4. Compare and promote names with evidence

Export the new project using `ExportAnalysis.java` and every external input
needed to identify its initialized memory blocks. Then compare it with an
appropriate V51 snapshot:

```sh
python3 spikes/firmware_workflow/scripts/compare_analysis.py \
  docs/research/firmware/v51/ghidra/canonical-ble/program.json \
  /path/to/scratch/mp305b-next/exports/ble-riscv/program.json \
  /path/to/scratch/mp305b-next/function-candidates.json
```

The comparison requires the same processor language. Exact instruction hashes,
short-function matches, mnemonic candidates, ambiguities and unmatched entries
are distinguished. Relocations may invalidate an exact hash even if behavior
is unchanged. A unique hash does not establish the same callers, data layout or
physical role. Zero-instruction entries do not receive a match.

Review instructions, constants, callers, references and memory roles before
transferring names. Ghidra Version Tracking can assist this review. Preserve
old names as aliases with their source. Prefer the richer canonical PD table
analysis and the reviewed independent main/bridge names where justified;
there is no automatic union of the two entry sets.

### 5. Reproduce behavior and document differences

Port address-specific probes only after the relevant functions and layouts
are established. V51 replay tools and their hash checks are a baseline, not
proof that a new release behaves identically. At minimum, revisit:

- framing, escaping, checksums, fragmentation, mailboxes and acknowledgments;
- identity, read replies, units, lengths and bounds;
- binding, permission checks, UI events, denial and link loss;
- setters, mode transitions, persistence and deferred replies;
- RTOS tasks, priorities, queues, mutexes, timers and allocation paths;
- interrupt dispatch, MMIO accesses, bus transfers and companion routing;
- fault producers, protection thresholds and update/reset paths.

Require emulator termination and explicit expected values. Record modeled
external calls and synthetic state. Diagnostic output is not an assertion.
Use the [recovered probe runner](../../../spikes/firmware_reconstruct/README.md)
and [earlier verification record](../firmware/verification.md) as examples.
Hardware tests follow AGENTS.md separately; this workflow does no device I/O.

Label findings **confirmed in code**, **confirmed on hardware** or **inferred**.
Use "cross-checked" only for independent WebLink derivation. Preserve disagreements
and unresolved questions, and avoid describing entry counts as source coverage.

### 6. Publish a reviewable research bundle

Create `docs/research/firmware/<release>/` with an inventory, evidence notes,
exports, snapshots, manifests and verification records. Record exact input
hashes, tool versions, commands, timeouts, model assumptions and failures.
Keep the firmware, generated RAM images, SDK binaries and `.gpr`/`.rep` project
files external. Export XML with memory contents disabled and check that it
contains no `MEMORY_CONTENTS` elements or accompanying byte files.

Run `python3 spikes/firmware_workflow/scripts/audit_research.py --write-manifest`
after reviewing the final bundle, then run it without that flag to verify the
current hashes. Historical manifests keep their original scope.

Run the restore/re-export comparison, resolve broken local links and inspect
rendered reports. Preserve raw captures unchanged in `captures/`. Update the
reviewed topic documents, TODO and append-only LOGBOOK. A research verification
record does not pass a V-model gate or authorize production implementation.

## Restore an existing V51 analysis

Supply the exact inputs listed by the chosen snapshot's `program.json`:

```sh
python3 spikes/firmware_workflow/scripts/restore_analysis.py \
  --snapshot docs/research/firmware/v51/ghidra/recovered-main \
  --scratch /path/to/scratch/restored-v51-main \
  --input /path/to/app.bin \
  --input /path/to/ram_rw_init.bin \
  --ghidra /path/to/ghidra
```

All required SHA-256 hashes must match before a project is created. The
canonical main input and WebLink's application copy differ in four identity
bytes and are not interchangeable. Initialized RAM can be recovered with the
existing scatter loader; its expected hash is also recorded. Function metadata
alone is not sufficient to reconstruct the firmware bytes.

Inspect `result.json`, `restore.log` and `reexport/`. The result explicitly
separates core restoration from XML symbol/function storage differences. A
passing core comparison must not be presented as a lossless database restore.

## Relocated evidence

[structure-map.json](../structure-map.json) maps the earlier paths to the
current tree by longest matching prefix. Historical commands, source snapshots
and manifests retain their original paths and hashes. Current documentation
links and maintained tools use the new layout.
