# Offline firmware verification spike

Question: which reconstructed MP305B V51 behaviors match the original
instructions, and which hardware interfaces can be recovered from them?

This is research tooling outside the production workspace. It performs
no device I/O. Firmware inputs, restored images, Ghidra projects and
compiled libraries stay in a separate scratch directory. The repository
contains scripts, reconstructed C, text exports and verification records.

## Run the instruction and C comparisons

Requirements: Python 3.12, the pinned packages in requirements.txt, and
clang. The recorded run used macOS arm64. The shared-library command also
supports Unix clang; other platforms have not been verified.

```sh
python3 -m venv /tmp/mp305-analysis-venv
/tmp/mp305-analysis-venv/bin/pip install -r spikes/firmware_verify/requirements.txt
python3 spikes/firmware_verify/scripts/prepare_run.py \
  --scratch /tmp/mp305-v51-new-run \
  --firmware /absolute/path/to/MP305B-V51.fwd \
  --plain /absolute/path/to/MP305B-V51.plain.bin
MP305_PYTHON=/tmp/mp305-analysis-venv/bin/python \
  sh /tmp/mp305-v51-new-run/scripts/verify_offline.sh
```

Use a new scratch directory. `--plain` is optional and adds a comparison
with the previous WebLink restoration. The container hash is checked before
staging. Restore and scatter-load checks precede instruction execution.
The final run-summary.json reports all case groups and hashes their records.
Do not add the scratch directory or firmware binaries to the repository.

The comparisons cover framing, settings, control validation, reply fields,
deferred records, BLE routing and host IDs, USB chunking, settings
normalization, storage command formatting, kernel primitives, permission
paths and selected readable C. Every record states its substitutions and
scope. Synthetic memory and substituted I/O do not establish hardware
timing, electrical behavior or end-to-end safety.

## Ghidra exports

The retained Setup/Refine/Recover/Discover scripts document the original
analysis pipeline. `rebuild_analysis.sh` and `check_rebuild.py` are research
scripts for an external workspace with the expected inputs and reference
files. Inspect their paths before using them; the portable runner above
does not require Ghidra or the external SDK.

The memory-access pass uses Ghidra 12.1.3 and Java 21:

```sh
analyzeHeadless /absolute/scratch/ghidra main \
  -process main-arm.bin -readOnly -noanalysis \
  -scriptPath /absolute/repo/spikes/firmware_verify/scripts \
  -postScript ExportMemoryAccesses.java /absolute/scratch/exports/access-main
```

Repeat for BLE and PD projects. Build the indexes with:

```sh
python3 spikes/firmware_verify/scripts/index_memory_accesses.py \
  /absolute/scratch/exports /absolute/scratch/reference \
  /absolute/scratch/access-index
```

The reference directory supplies downloaded vendor SVDs and CH583SFR.h.
These are comparison sources, not exact chip identifications. The
[source manifest](../../docs/research/firmware/v51/canonical/sources.md) records them.
The [verification ledger](../../docs/research/firmware/verification.md)
contains the actual run, limitations and corrected earlier conclusions.
