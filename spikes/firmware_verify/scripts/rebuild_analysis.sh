#!/bin/sh
# Rebuild the Ghidra analyses into a new directory. No hardware is accessed.
set -eu
MP305_SCRATCH=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
MP305_HEADLESS=${MP305_GHIDRA_HEADLESS:-/opt/homebrew/opt/ghidra/libexec/support/analyzeHeadless}
MP305_DEST=${1:-"$MP305_SCRATCH/rebuild-$(date +%Y%m%d-%H%M%S)"}
case "$MP305_DEST" in /*) ;; *) echo 'Use an absolute output-directory path.' >&2; exit 1;; esac
if [ -e "$MP305_DEST" ]; then echo 'Output directory already exists; choose a new directory.' >&2; exit 1; fi
mkdir -p "$MP305_DEST/projects" "$MP305_DEST/exports" "$MP305_DEST/logs"
cd "$MP305_SCRATCH"
.venv/bin/python scripts/restore.py > "$MP305_DEST/logs/restore.log"
.venv/bin/python scripts/recover_ram.py > "$MP305_DEST/logs/ram.log"
.venv/bin/python scripts/sdk_reference.py > "$MP305_DEST/logs/sdk.log"
"$MP305_HEADLESS" "$MP305_DEST/projects" main -import inputs/main-arm.bin \
  -loader BinaryLoader -loader-baseAddr 0x10000 -processor ARM:LE:32:Cortex \
  -scriptPath scripts -preScript SetupFirmware.java arm -max-cpu 4 > "$MP305_DEST/logs/main-import.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" main -process main-arm.bin -noanalysis -scriptPath scripts \
  -postScript RefineFirmware.java arm -postScript FinalizeMain.java inputs/main-initialized-ram.bin \
  -postScript DiscoverCallbacks.java "$MP305_DEST/exports/main-callback-seeds.tsv" \
  -postScript ApplyAnnotations.java notes/main-annotations.tsv \
  -postScript ExportFirmware.java "$MP305_DEST/exports/arm" \
  -postScript FinalEvidence.java "$MP305_DEST/exports/arm" -max-cpu 4 > "$MP305_DEST/logs/main-refine.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" ble -import inputs/ble-riscv.bin \
  -loader BinaryLoader -loader-baseAddr 0x1000 -processor RISCV:LE:32:default \
  -scriptPath scripts -preScript SetupFirmware.java riscv -max-cpu 4 > "$MP305_DEST/logs/ble-import.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" ble -process ble-riscv.bin -noanalysis -scriptPath scripts \
  -postScript RefineFirmware.java riscv -postScript ApplyAnnotations.java notes/ble-annotations.tsv \
  -postScript ExportFirmware.java "$MP305_DEST/exports/ble" \
  -postScript FinalEvidence.java "$MP305_DEST/exports/ble" -max-cpu 4 > "$MP305_DEST/logs/ble-refine.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" pd -import inputs/pd-8051.bin \
  -loader BinaryLoader -loader-baseAddr 0x1000 -processor 8051:BE:16:default \
  -scriptPath scripts -preScript SetupFirmware.java 8051 -max-cpu 4 > "$MP305_DEST/logs/pd-import.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" pd -process pd-8051.bin -noanalysis -scriptPath scripts \
  -postScript RefineFirmware.java 8051 \
  -postScript Discover8051Calls.java "$MP305_DEST/exports/pd-call-seeds.tsv" \
  -postScript Recover8051Tables.java "$MP305_DEST/exports/pd-tables.tsv" \
  -postScript ExportFirmware.java "$MP305_DEST/exports/pd" \
  -postScript FinalEvidence.java "$MP305_DEST/exports/pd" -max-cpu 4 > "$MP305_DEST/logs/pd-refine.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" sdk -import reference/wch-sdk-rom-v1.8.bin \
  -loader BinaryLoader -loader-baseAddr 0x40000 -processor RISCV:LE:32:default \
  -scriptPath scripts -preScript SupplementSdk.java exports/wch-sdk-api.tsv -max-cpu 4 > "$MP305_DEST/logs/sdk-import.log" 2>&1
"$MP305_HEADLESS" "$MP305_DEST/projects" sdk -process wch-sdk-rom-v1.8.bin -noanalysis -scriptPath scripts \
  -postScript RefineSdk.java exports/wch-sdk-api.tsv \
  -postScript ExportFirmware.java "$MP305_DEST/exports/sdk" \
  -postScript FinalEvidence.java "$MP305_DEST/exports/sdk" -max-cpu 4 > "$MP305_DEST/logs/sdk-refine.log" 2>&1
# Headless Ghidra can return success after a script error; check logs explicitly.
if rg -n 'ERROR|SCRIPT ERROR' "$MP305_DEST/logs"; then
  echo 'Inspect the reported Ghidra errors before using this rebuild.' >&2; exit 1
fi
printf 'Rebuilt analyses in %s\n' "$MP305_DEST"
