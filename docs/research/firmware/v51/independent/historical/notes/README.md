> Historical source note. Superseded by the reviewed notes and corrections
> in the recovery README. Workflow instructions here describe the old pass.

# MP305B firmware 1.6.0.51 reconstruction workspace

Scratch workspace outside the repository (`~/mp305b-fw-re`). Nothing here is
written into `~/mp305b`. The repository's earlier findings are in
`~/mp305b/docs/research/` (`firmware.md`, `protocol.md`, `README.md`,
`captures/`). Read them, but never edit anything under `~/mp305b`.

## Images

| File | What | Load address | Tool language |
|---|---|---|---|
| `bin/app.bin` | Main MCU, HC32F4A0-class Cortex-M4F, Keil ARMCC + microlib, FreeRTOS, LVGL v9 | `0x10000` (64 KB bootloader below, not available) | `ARM:LE:32:Cortex` |
| `bin/ch58x.bin` | `data.bin[0xB000:]`, WCH CH58x (RISC-V, BLE + USB) | `0x1000` (WCH jump-IAP below, not available) | `RISCV:LE:32:default` (RV32IMAC) |
| `bin/pd8051.bin` | `data.bin[0:0xB000]`, 8051 USB-PD controller, Keil C51 | CODE `0x1000` (boot area below, not available) | `8051:BE:16:default` |
| `bin/ram_rw_init.bin` | app RW data after `__scatterload` decompression, lives at `0x1FFE0000` | | |

Main MCU memory: RW init `0x1FFE0000..0x1FFE0B5C`, ZI `0x1FFE0B5C..0x2003F618`,
initial SP `0x2003F618`. `__scatterload` table at `0x83FA8`. `SystemInit`
`0x1DB74` writes VTOR = `0x10000`. `main` is `0x533C0`.

CH58x: highcode (vector table and RAM code) copied from flash `0x1008..0x1C48`
to RAM `0x20002000..0x20002C40`; `.data` from flash `0x9318` (slice offset
`0x8318`) to `0x20002C40..0x20002F50`; bss to `0x20006DF0`; `handle_reset` at
`0x1C48`. Vector table in RAM at `0x20002000` (absolute handler addresses,
WCH magic `0xF5F9BDA9` in word 4).

8051: vectors at CODE `0x1000 + n`. Reset `LJMP 0xAF88` is Keil `STARTUP.A51`
(IDATA clear, XDATA clear `0x0000..0x0BEF`, SP = `0xD2`). The zero block at
CODE `0xBA00..0xBFF9` and the trailer `01 02 55 A5 5A AA` at CODE `0xBFFA`.

## Address conventions (important when comparing)

- This workspace uses absolute addresses everywhere.
- `docs/research/firmware.md` gives `app.bin` addresses as FILE OFFSETS for
  functions and handlers (for example "dispatcher `0x2F34`" is absolute
  `0x12F34`, "`0xC8` handler `0xB7F4`" is `0x1B7F4`, "`0x1478C`" there is
  probably offset too, check it). RAM addresses there (`0x1FFFAACC`) are
  absolute. `data.bin` addresses there are offsets into `data.bin`.

## Generated outputs (`out/`)

- `<tag>_decomp.c`: Ghidra decompilation of every function. Each function
  starts with `// ==== NAME @ ADDR size N callers [...]`. Search with
  `rg -n "@ 0001b7f4" out/app_decomp.c`.
- `<tag>_functions.tsv`: addr, name, size, callers, callees.
- `<tag>_refs.tsv`: every reference: from address, containing function,
  to address, target symbol, type (READ, WRITE, DATA, CALL...). Use it to find
  every reader or writer of a RAM field, e.g.
  `rg "\t1fffab12\t" out/app_refs.tsv`. Note: accesses through a base
  register plus offset (e.g. `S+0x46` via `fp`) are NOT separate refs; grep the
  decompiled C or disassembly for those.
- `<tag>_strings.tsv`: strings with referencing functions.
- `hc32f4a0_regs.txt`, `ch58x_regs.txt`: register maps (from HC32F4A0.svd and
  CH583SFR.h in `svd/`). Peripheral registers are labelled in Ghidra and appear
  by name in the decompiled C (e.g. `USART1_TDR`).

## Tools

- Python venv: `~/mp305b-fw-re/.venv/bin/python` (capstone, unicorn, pyghidra).
- `scripts/tdis.py ADDR [N]`: Thumb disassembly of app.bin with literal values.
- `scripts/emu_app.py`: Unicorn harness for app.bin. `App().call(addr, args...)`
  runs a real firmware function (flash + RAM init image, peripherals as plain
  RAM). Use it to execute command handlers on crafted requests and confirm
  byte-exact behaviour. Import with `sys.path.insert(0, "~/mp305b-fw-re/scripts")`
  (expand the path). Hook callees with `hook_func`.
- Ghidra 12.1.3 headless: `/opt/homebrew/Cellar/ghidra/12.1.3/libexec/support/analyzeHeadless`.
  Projects in `ghidra/` (`mp305b_app`, `mp305b_ch58x`, `mp305b_pd8051`).
  DO NOT open the shared projects for writing; the original projects are preserved. If you need a custom Ghidra script, copy the project first:
  `cp -R ghidra/mp305b_app.gpr ghidra/mp305b_app.rep /tmp/<you>/` and run
  against the copy with `-process -noanalysis`. Keep your scripts in
  `scripts/<area>_*.java|py`.
- For RISC-V and 8051 disassembly, capstone supports RISC-V; for 8051 use the
  Ghidra listing or write a small table disassembler.

## Output rules for each analysis area

1. Write your findings to `notes/<area>.md`. Absolute addresses, byte-exact
   layouts as tables, and for each claim how you know it (decompiled C,
   disassembly check, emulation run). Mark uncertain items as inferred and say
   why.
2. Write function and data names you are confident about to
   `names/<tag>_<area>.tsv` (`addr<TAB>name<TAB>short comment`, addr as hex
   without `0x`, e.g. `1b7f4\tcmd_C8_dc_control\t...`). tag is app, ch58x or
   pd8051. Only names you are confident about.
3. End your notes with a section "Comparison with docs/research" listing, for
   every relevant statement in `~/mp305b/docs/research/*.md`: confirmed,
   corrected (with evidence), or new (not in the docs). Be exhaustive.
4. Prose: plain English, no em dashes or en dashes, headings in sentence case.
5. Never talk to hardware, never run anything that could reach a device, never
   write under `~/mp305b`.
