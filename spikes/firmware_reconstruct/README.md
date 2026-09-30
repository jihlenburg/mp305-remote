# Independent firmware reconstruction spike

Question: when the V51 update is rebuilt from scratch, without reusing the
earlier exports, do the protocol facts in `docs/research/` hold up? And what
else about the host interface does the firmware show?

This is throwaway research tooling. It performs no device I/O. It runs the
original firmware code only inside an emulator, in synthetic memory.
Firmware images and Ghidra projects stay in `~/mp305b-fw-re`, outside the
repository. Reviewed notes, named decompilations and run records are now in
[the recovered research bundle](../../docs/research/firmware/v51/independent/README.md).
The original helpers expect that workspace path. The recovery runners accept
explicit paths and keep repaired copies separate.

Findings from this spike go into `docs/research/`, and a LOGBOOK entry
describes the run. Production code never imports or copies these scripts.

For another release or to restore archived Ghidra metadata, start with the
[reusable workflow](../firmware_workflow/README.md). The original reconstruction
helpers below are specific to V51.

## Requirements

- Python 3.12 with the packages in `requirements.txt`.
- Ghidra 12.1.3 with Java 21. Set `GHIDRA_HOME` to the Ghidra `libexec`
  directory if it is not the Homebrew default.
- `uv`, `curl` and a POSIX shell.
- `app.bin` and `data.bin` restored from `MP305B-V51.fwd` (see
  `docs/research/firmware.md`, "Image container").

## Run

### Recover existing work

The completed run is in `~/mp305b-fw-re/recovery-2026-09-30`. It preserves
the original projects and notes. To reproduce the offline probes in a new
scratch directory:

```sh
python3 spikes/firmware_reconstruct/scripts/recover_jobs.py \
  ~/mp305b-fw-re ~/mp305b-fw-re/recovery-new --prepare
MP305_RE_WORKSPACE=~/mp305b-fw-re \
MP305_RE_REPO="$PWD" \
MP305_RE_SCRIPTS=~/mp305b-fw-re/recovery-new/scripts \
  ~/mp305b-fw-re/.venv/bin/python \
  spikes/firmware_reconstruct/scripts/verify_recovery.py \
  ~/mp305b-fw-re/recovery-new/results/assertions.json
```

The ledger distinguishes completed diagnostic jobs from asserted comparisons.
Use `--only commands-c8 bridge-t2` to rerun selected jobs. Previous logs are
retained. Environment variables select only local research files; there is
no transport or HIL support.

To reproduce the named Ghidra exports, choose another fresh scratch directory
and set `JAVA_HOME` to a Java 21 installation:

```sh
JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home \
  python3 spikes/firmware_reconstruct/scripts/recover_exports.py \
  ~/mp305b-fw-re ~/mp305b-fw-re/exports-new
```

This copies the projects, merges all name aliases, runs the pending function
helpers, marks the verified reset chain non-returning and checks the export
logs. `--ghidra` selects another Ghidra installation. Candidate function
boundaries and register names remain subject to review.

### Original import pipeline

The original command below **overwrites the workspace imports and outputs**.
It is retained for provenance. Use the recovery commands above for existing
work; the completed recovery did not rerun this command.

```sh
sh spikes/firmware_reconstruct/scripts/run_pipeline.sh /path/to/app.bin /path/to/data.bin
```

The pipeline:

1. Copies the scripts and both images into the workspace and creates a
   Python virtual environment there.
2. Downloads the public HDSC HC32F4 SVD files and headers and WCH's
   `CH583SFR.h` (`fetch_references.sh`). These are not stored in the
   repository.
3. Splits `data.bin` into the 8051 slice (first `0xB000` bytes) and the
   CH58x slice (the rest).
4. Runs the main image's own `__decompress` routine in Unicorn to recover
   the initialized RAM image (`emu_scatter.py`).
5. Builds register label tables and scores the HC32 variants against the
   peripheral addresses the image uses (`gen_symbols.py`, `svd_score.py`,
   `gen_ch58x_regs.py`). Finds the 8051 load address (`pd8051_base.py`).
6. Imports the three programs into Ghidra with their memory maps
   (`Setup.java`, `SetupCH58x.java`, `Setup8051.java`). It then exports
   decompiled C, function indexes, strings and every cross-reference
   (`Export.java`, `ExportRefs.java`).

| Program | Ghidra language | Load address |
|---|---|---|
| Main application | `ARM:LE:32:Cortex` | `0x10000` |
| CH58x Bluetooth and USB bridge | `RISCV:LE:32:default` | `0x1000` |
| 8051 USB-PD controller | `8051:BE:16:default` | CODE `0x1000` |

## Scripts

| Script | Purpose |
|---|---|
| `run_pipeline.sh` | End-to-end rebuild of the workspace |
| `fetch_references.sh` | Download public vendor register descriptions |
| `emu_scatter.py` | Run the main image's scatter-load decompressor to recover initialized RAM |
| `gen_symbols.py`, `svd_score.py` | HC32F4A0 register labels; score HC32 variants by matching literal addresses |
| `gen_ch58x_regs.py` | CH58x register labels from `CH583SFR.h` |
| `pd8051_base.py` | Solve the 8051 load address from vector targets and ISR prologues |
| `Setup.java`, `SetupCH58x.java`, `Setup8051.java` | Ghidra pre-scripts: memory maps, register labels, vectors |
| `Export.java`, `ExportRefs.java` | Ghidra post-scripts: decompiled C, function index, strings, references |
| `ApplyNames.java` | Apply reviewed names from `names/*.tsv` back into a Ghidra project |
| `tdis.py` | Thumb disassembly of the main image with literal pool values |
| `emu_app.py` | Unicorn harness that calls main-image functions with crafted inputs |
| `commands_emu.py` | Command-handler emulation cases built on `emu_app.py` |
| `hostlink_emu_tests.py`, `hostlink_emu_ch58x.py` | Host link emulation cases for the main image and the CH58x bridge |
| `hostlink_xref.py`, `hostlink_rvdis.py`, `ch58x_dis.py` | Reference search and RISC-V disassembly helpers |
| `ch58x_BridgeFix.java` | Ghidra fix-ups for the CH58x bridge functions |
| `power_dis.py`, `power_xref.py`, `power_Fix.java` | General helpers: recursive-descent Thumb disassembly, base-plus-offset field cross-reference, tail-call function repair |

Some scripts were written for one analysis pass and read files that pass
produced in the workspace. Read a script before relying on it.

## Limits

Emulation substitutes hardware, interrupts and library calls. A passing
emulation case shows what the code does with the inputs it was given. It
does not show what the unit does at the bench. The user's unit reported
application version 1.6.0.40, not the 1.6.0.51 analysed here.
