#!/bin/sh
# Rebuild the reconstruction workspace from the restored V51 images.
# Inputs: app.bin and data.bin restored from MP305B-V51.fwd (see
# docs/research/firmware.md, "Image container"). No device I/O.
# Usage: run_pipeline.sh /path/to/app.bin /path/to/data.bin
set -eu
RE="${HOME}/mp305b-fw-re"
GH="${GHIDRA_HOME:-/opt/homebrew/Cellar/ghidra/12.1.3/libexec}"
SRC="$(cd "$(dirname "$0")" && pwd)"
mkdir -p "$RE/bin" "$RE/out" "$RE/ghidra" "$RE/notes" "$RE/names" "$RE/scripts"
cp "$SRC"/*.py "$SRC"/*.java "$SRC"/*.sh "$RE/scripts/"
cp "$1" "$RE/bin/app.bin"
cp "$2" "$RE/bin/data.bin"
cd "$RE"
[ -d .venv ] || { uv venv -q .venv && uv pip install -q --python .venv/bin/python -r "$SRC/../requirements.txt"; }
PY="$RE/.venv/bin/python"
[ -f svd/HC32F4A0.svd ] || sh scripts/fetch_references.sh
# Split the companion image: 8051 slice, then the CH58x slice at 0xB000.
dd if=bin/data.bin of=bin/pd8051.bin bs=1 count=45056 2>/dev/null
dd if=bin/data.bin of=bin/ch58x.bin bs=1 skip=45056 2>/dev/null
# Main MCU initialized RAM: run the original __decompress routine.
"$PY" scripts/emu_scatter.py
"$PY" scripts/gen_symbols.py
"$PY" scripts/gen_ch58x_regs.py
"$PY" scripts/pd8051_base.py
"$PY" scripts/svd_score.py
AH="$GH/support/analyzeHeadless"
"$AH" ghidra mp305b_app -import bin/app.bin -overwrite -processor ARM:LE:32:Cortex \
  -loader BinaryLoader -loader-baseAddr 0x10000 -scriptPath scripts \
  -preScript Setup.java -postScript Export.java app -max-cpu 8 > out/ghidra_app.log 2>&1
"$AH" ghidra mp305b_ch58x -import bin/ch58x.bin -overwrite -processor RISCV:LE:32:default \
  -loader BinaryLoader -loader-baseAddr 0x1000 -scriptPath scripts \
  -preScript SetupCH58x.java -postScript Export.java ch58x > out/ghidra_ch58x.log 2>&1
"$AH" ghidra mp305b_pd8051 -import bin/pd8051.bin -overwrite -processor 8051:BE:16:default \
  -loader BinaryLoader -loader-baseAddr 0x1000 -scriptPath scripts \
  -preScript Setup8051.java -postScript Export.java pd8051 > out/ghidra_pd8051.log 2>&1
for t in app ch58x pd8051; do
  "$AH" ghidra "mp305b_$t" -process -noanalysis -readOnly -scriptPath scripts \
    -postScript ExportRefs.java "$t" > "out/refs_$t.log" 2>&1
done
grep -h "EXPORT" out/ghidra_*.log
