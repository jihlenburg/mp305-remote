# Register and memory-access inventory

Updated 2026-09-30. This inventory preserves every memory operation
reported by Ghidra's instruction p-code for the decoded instructions in
the three analyzed images. A second pass adds decompiler-derived address
expressions. It is a starting point for tracing all hardware accesses,
not a claim that every register has been identified or every byte decoded.

## Coverage and files

| Image | Instruction access records | Instructions represented | Unresolved raw addresses | Decompiler access records | Unresolved decompiler addresses | Distinct peripheral candidates |
|---|---:|---:|---:|---:|---:|---:|
| Main ARM | 54,975 | 37,034 | 50,413 | 41,349 | 12,392 | 75 |
| BLE RV32 | 3,517 | 3,516 | 3,500 | 1,692 | 672 | 102 |
| PD 8051 | 10,445 | 6,865 | 9,759 | 7,717 | 772 | 103 |

The **68,937 raw records** include RAM, stack, code-literal and CPU-register
space accesses as well as hardware registers. They are static operations,
not runtime read/write counts. Several operations may belong to one
instruction. High-pcode and raw counts are not additive or directly
comparable: decompilation folds operations, follows shared tails and can
introduce aliases or omit inaccessible code.

| Image | All instruction accesses | Address expressions | Candidate register index | Remaining unresolved accesses |
|---|---|---|---|---|
| Main | [raw](../firmware/v51/canonical/accesses/main/memory-accesses-raw.tsv) | [high](../firmware/v51/canonical/accesses/main/memory-accesses-high.tsv) | [registers](../firmware/v51/canonical/accesses/main/registers.tsv) | [unresolved](../firmware/v51/canonical/accesses/main/unresolved-high.tsv) |
| BLE | [raw](../firmware/v51/canonical/accesses/ble/memory-accesses-raw.tsv) | [high](../firmware/v51/canonical/accesses/ble/memory-accesses-high.tsv) | [registers](../firmware/v51/canonical/accesses/ble/registers.tsv) | [unresolved](../firmware/v51/canonical/accesses/ble/unresolved-high.tsv) |
| PD | [raw](../firmware/v51/canonical/accesses/pd/memory-accesses-raw.tsv) | [high](../firmware/v51/canonical/accesses/pd/memory-accesses-high.tsv) | [registers](../firmware/v51/canonical/accesses/pd/registers.tsv) | [unresolved](../firmware/v51/canonical/accesses/pd/unresolved-high.tsv) |

Each record includes function, instruction address, disassembly, direction,
access width, address expression, resolved address where available and
store-value expression. The [summary](../firmware/v51/canonical/accesses/summary.json)
contains source hashes and decompiler completion counts. Completion does
not establish correctness; warnings remain in the canonical exports.

## Main processor regions

The following combines resolved accesses with reviewed parameterized
drivers. A driver can accept a peripheral base as an argument, so its
real hardware accesses may appear only in the unresolved index.

| Region | Observed use or candidate interpretation | Detail |
|---|---|---|
| `0x40010400`, `0x400106xx` | Embedded flash control candidate | HDSC EFM comparison; do not confuse with serial storage offsets |
| `0x4001C000` | Display SPI | [Panel and DMA paths](ui-and-analog.md) |
| `0x4001C800` | Serial storage SPI | [Storage commands](hardware.md#serial-nonvolatile-storage) |
| `0x4001CC00`, `0x4001D400`, `0x40021000` | Three UART paths | [Baud, pins and routing](buses.md#main-processor-uarts) |
| `0x40024000`, `0x40026000`, `0x40026C00` | Timers | Periodic IRQ, PWM, RGB-like DMA waveform |
| `0x4003A000`, `0x4003A400`, `0x4003AC00` | Timers and compare outputs | Analog fine-control candidate, tones, PWM |
| `0x40040000` | ADC channels 3 and 6 | Analog GPIO and scaling traced |
| `0x40041000` | Dual DAC candidate | Two halfword values, 12-bit clamps; conflicts with F460 TRNG assignment |
| `0x40048000`, `0x400543xx` | Power/clock-control candidates | Initialization and low-level access; exact family field map unresolved |
| `0x40049000` | Watchdog candidate | Vendor map agreement, complete feed/failure policy unreviewed |
| `0x4004CC00` | Reset-control candidate | F467/F4A0 comparison |
| `0x4004E000`, `0x4004E400` | Two hardware I²C controllers | Touch and power-device buses respectively |
| `0x40050800` | SRAM controller candidate | Vendor map comparison |
| `0x40051000`, `0x400108xx` | Interrupt/event routing candidates | Callback registration and DMA trigger setup |
| `0x40053000`, `0x40053400` | DMA controllers | Display/RGB and UART paths |
| `0x40053800` through `0x40053Bxx` | GPIO, pin configuration | Parameterized port and mask helpers |
| `0x40054000`, `0x400541xx` | Clock-control registers | F460-style CMU mapping; exact MCU unresolved |
| `0x422083xx` | Peripheral bit-band aliases | Cortex mapping points into the `0x400104xx` area; verify alias bit per access |
| `0xE000E000` and `0xE000EDxx/EFxx` | Cortex system registers | SysTick, interrupt controller, exception and FPU setup |

For example, clear-mask helper `0x15384` reads and writes
`0x4005380A + port*0x10`. The index preserves that expression. Assigning
it just to `0x4005380A` would lose every nonzero port. Set-mask helper
`0x153E0` similarly uses `0x40053808 + port*0x10`. Traced constant callers
are recorded in the [bus](buses.md) and
[UI/analog](ui-and-analog.md) maps.

Vendor names in registers.tsv are **comparison candidates**, not installed
part identification. They can conflict. SVD inheritance is resolved for
peripheral registers; complex array expansions and every field definition
are not reproduced. A missing vendor name does not imply an unknown
operation in the firmware.

## BLE companion regions

The official WCH CH583 header supplies comparison names:

| Region | Candidate role |
|---|---|
| `0x400010xx` | Clock, reset, watchdog, safe-access unlock, GPIO mux, ADC and RTC controls |
| `0x400018xx` | Flash access control/data |
| `0x400020xx`, `0x400024xx`, `0x400028xx` | Timer 0, 1 and 2 |
| `0x400030xx`, `0x400034xx` | UART 0 and 1 |
| `0x40003Cxx` | UART 3 status access; usage/reachability needs review |
| `0x400050xx` | PWM controller and channel values |
| `0x400080xx` | USB controller, endpoints and DMA addresses |
| `0xE000E1xx`, `0xE000E4xx`, `0xE000EDxx`, `0xE000F0xx` | WCH core/interrupt/system controls; do not apply ARM register names to this RISC-V image |

An included UART/PWM routine need not be used on this board. Distinguish
driver presence from reachable initialization and peripheral activity.
Radio behavior also depends on the separately installed WCH library,
whose actual device bytes are absent from the ISDT update. The external
SDK reference is kept separate from these three-image counts.

## PD companion address spaces

The 8051 has separate code, internal RAM, external-data, SFR and bit
spaces. Identical numeric addresses in different spaces are not aliases.
The index includes 39 distinct SFR byte addresses and 22 SFR bit addresses,
plus 42 candidate XDATA addresses in the `0x1000` and `0x2000` through
`0x24FF` regions. Those XDATA regions may contain RAM and peripherals;
their inclusion is deliberately conservative.

Some SFRs are CPU state such as accumulator, stack pointer and data
pointer. Ghidra's generic 8051 names do not establish a PD controller's
custom peripheral map. Register banks, paged SFRs, indirect accesses and
MOVX through dynamic DPTR require more analysis before assigning CC,
PD PHY, UART, ADC or power-switch semantics.

## Reproduction and limitations

[ExportMemoryAccesses.java](../../../spikes/firmware_verify/scripts/ExportMemoryAccesses.java)
runs read-only against each existing Ghidra project. It exports every
decoded instruction's LOAD/STORE and direct memory-space operations,
then performs a bounded decompiler expression pass. Immutable firmware
literals may be resolved; mutable initialized RAM is never assumed
constant. Long expressions are explicitly truncated.

[index_memory_accesses.py](../../../spikes/firmware_verify/scripts/index_memory_accesses.py)
preserves the records and builds address, caller and unresolved indexes.
Unresolved includes ordinary RAM/stack operations and unresolved hardware
pointers; it is not a count of missing peripherals. Conversely, a resolved
address is not automatically a verified register purpose.

Remaining work includes interprocedural argument propagation, indirect
call recovery, MMIO register-field decoding, 8051 memory-map identification
and runtime capture comparisons. Undecoded bytes and missing boot/SDK
images remain outside this inventory. The index makes these gaps
searchable instead of silently dropping them.
