# Firmware architecture and companion behavior

Reconstructed from MP305B V51. Updated 2026-09-30 after merging and
verifying both scratchpads. [Readable guide](readable.md),
[command details](../firmware.md), [verification ledger](verification.md).

## Evidence and addresses

**Confirmed in code** means the finding is visible in the supplied firmware bytes, disassembly, or a reviewed decompilation. **Confirmed by offline execution** adds a check against original instructions running in synthetic memory. It is not hardware confirmation. **Inferred** marks an interpretation, a heuristic function entry, or a name not established by the bytes alone.

Main addresses are processor addresses: add `0x10000` to an `app.bin` file offset. PD addresses are `pd-8051.bin` offset plus `0x1000`. BLE addresses are `ble-riscv.bin` offset plus `0x1000`, or `data.bin` offset minus `0xa000`. RAM addresses are stated explicitly.

The firmware inputs, restored images, reference downloads and exports have separate provenance. See [restoration results](v51/canonical/restoration.json), [original input hashes](v51/canonical/verification/input-sha256.json), and [reference sources](v51/canonical/sources.md).

## Three programs in one update

Confirmed in code:

| Image | Position in restored body | Bytes | Processor mapping | Entry |
|---|---:|---:|---|---|
| Main application | `0x00000` | 476,160 | Cortex-M Thumb, `0x10000` through `0x843ff` | Reset vector `0x10359`, Thumb entry `0x10358` |
| PD companion | `0x74400`; first part of `data.bin` | 45,056 | 8051 code space, `0x1000` through `0xbfff` | `0x1000` jumps to `0xaf88` |
| BLE and USB companion | `0x7f400`; `data.bin + 0xb000` | 34,432 | RV32 with compressed instructions, `0x1000` through `0x967f` | `0x1000` jumps to `0x1c48` |

The PD role is inferred from the 8051 program's power-control operations and explicit PD, PPS, EPR and AVS messages. The instruction set and split are confirmed. The string `P829 v%d.%d Bat=%d-%d` is at PD file offset `0xa3ba`, processor address `0xb3ba`. It does not establish an exact chip model. Other strings include source/sink transitions, Safe5V/Safe0V, GoodCRC, SrcCap, EPR Mode and EPR Request. The 8051 startup clears internal RAM and external data memory, sets SP to `0xd2`, processes an initialization table at code address `0xb022`, and reaches the application loop through `0xa7c0`.

The BLE program identifies WCH's `CH58x_BLE_LIB_V1.8`. Startup reaches a library entry at `0x40000`, which is absent from the ISDT update. A separately downloaded official WCH v1.8 library provides a useful reference. Its bytes have not been matched to the physical unit. The exact BLE chip variant remains unconfirmed.

### Main processor identity

Cortex-M Thumb, FPU support and BASEPRI critical sections are confirmed in the main code. An HDSC HC32 family attribution is inferred from register layouts. The code uses clock registers around `0x40054026` and `0x40054100`. These resemble HC32F460, but the application's RAM layout does not fit an ordinary F460. F4A0 and F467 have a closer RAM range but a different CMU base. Vendor packs for F448, F451, F452, F460, F467, F472 and F4A0 were inspected. No exact main MCU model is established.

Generic peripheral names produced by Ghidra's 8051 language are not evidence for the PD chip's register names. Prefer their numeric addresses until the chip is identified.

## Independent container restoration

[restore.py](../../../spikes/firmware_verify/scripts/restore.py) restores the original container without WebLink's identity mutation. The eight little-endian header words are:

| Field | Value |
|---|---|
| Running key | `0x15f7e6f5` |
| Body checksum / initial running state | `0x7689ffe3` |
| Application destination | `0x10000` |
| Data destination | `0` |
| Application size | `0x74400` |
| Data size | `0x13680` |
| Original and rapid baud rates | Both 115200 |

For each encrypted 32-bit word, the restored word is `word XOR state`. Update `state = ((state + key) XOR key) mod 2^32`. The sum of restored words modulo `2^32` equals the checksum. The restored body is 555,648 bytes.

The identity block is at main file offset `0x6afc8`, processor address `0x7afc8`. Its magic is **`0xaa55cc33`**, stored as `33 cc 55 aa`. The following fields are `MP305B\0\0`, hardware bytes `02 00 02 00`, and application version `01 06 00 33`. The existing plain image differs from the independent restoration at exactly the four magic bytes, which WebLink replaced with `ff`.

## Runtime memory recovered

### Main application

The scatter table at `0x83fa8` contains two rows:

| Source | Destination | Output size | Routine |
|---|---|---:|---|
| `0x83fc8` | `0x1ffe0000` | `0xb5c` | Decompress initialized data, `0x11652` |
| `0x84384` | `0x1ffe0b5c` | `0x5eabc` | Zero BSS, `0x202cc` |

The initial stack pointer is `0x2003f618`, also the end of that BSS range. [recover_ram.py](../../../spikes/firmware_verify/scripts/recover_ram.py) executes these original routines in Unicorn. The recovered 2,908 initialized bytes are in `inputs/main-initialized-ram.bin`; [the execution record](v51/canonical/main-scatter-load.json) includes their hash. These bytes were imported into Ghidra. Mutable RAM remains writable, avoiding false constant folding.

### BLE program

Confirmed by startup copy loops:

| Flash source | RAM destination | Size | Purpose |
|---|---|---:|---|
| `0x1008` | `0x20002000` | `0xc40` | Vectors and executable code |
| `0x9318` | `0x20002c40` | `0x310` | Initialized data and GATT tables |
| none | `0x20002f50` | `0x3ea0` | Zeroed BSS, ending at `0x20006df0` |

Startup sets SP to `0x20007800`, GP to `0x20002000`, and mtvec to `0x20002003`. Ghidra contains the RAM copies and GP context. Some mapped uninitialized blocks extend beyond the exact observed BSS for analysis convenience; the memory export is not a declaration of installed RAM capacity.

## Tasks and subsystem boundaries

Main [Start_Task at `0x1d7a0`](v51/canonical/main/functions/0001d7a0_Start_Task.c) creates four named tasks:

| Task | Entry | Stack argument | Priority argument | Observed work |
|---|---|---:|---:|---|
| `lvgl_task` | `0x53338` | `0x400` | 0 | UI service |
| `User_task` | `0x1f208` | `0x200` | 3 | Command dispatch, companion transmit scheduling, communication services |
| `Time_task` | `0x1e020` | `0x200` | 2 | Repeating 10-tick loop and scheduled work |
| `Power_task` | `0x1b494` | `0x200` | 4 | Event mask 3; bit 1 calls `0x19f18`, bit 2 calls `0x1a620` |

These names, entry pointers and call arguments are confirmed. Original task-creation instructions establish four bytes per stack word. The configured tick is 1 kHz, with five priorities and equal-priority time slicing. Critical sections use BASEPRI `0x50`. See the [complete task, heap and resource map](rtos.md), including Idle, Start_Task, Tmr Svc, mutexes and event groups.

Main callback discovery uses stored Thumb pointers plus an existing instruction or common function prologue. The candidate list is saved in [main-callback-seeds.tsv](v51/canonical/main-callback-seeds.tsv). Those automatically discovered entries remain inferred until reviewed.

## Framing and bridge routing

Confirmed in code and, for the main frame encoder/decoder, by offline execution:

1. A decoded internal slot holds source nibble, destination nibble, length, one unused byte, then opcode and payload.
2. The encoded address is `(source << 4) | (destination & 15)`.
3. The wire frame starts with one `aa`, followed by address, length, opcode/payload and an additive 8-bit checksum over address, length and opcode/payload.
4. Every `aa` in the body, including address, length and checksum, is doubled. De-stuff in pairs. The decoder cannot receive address `aa` from a fresh state: its initial marker recognition requires a non-`aa` byte. This edge case was executed for all 256 addresses. Zero length also fails to form an accepted empty frame. The leading frame marker is not doubled.
5. The original decoder rejects a changed checksum. Runs of repeated `aa` round-trip in the exercised cases.

Main encoder wrapper: `0x15430`; encoder body: `0x1fedc`; stuffing helper: `0x1fff0`; decoder wrapper: `0x146b8`. The compiled reconstruction is in [protocol.c](../../../spikes/firmware_verify/reconstructed/protocol.c).

### The type 6 suffix is a route byte

The BLE bridge [queue routine at `0x4074`](v51/canonical/ble/functions/ram_00004074_queue_gatt_to_main.c) appends `31` to commands from AF01 and `00` to commands from AF02. Main handlers usually echo this final request byte on route type 6. The [reply bridge at `0x3fac`](v51/canonical/ble/functions/ram_00003fac_route_main_reply_to_gatt.c) removes it:

- `31` selects AF01; the bridge prepends address `31` to the BLE notification.
- The other route selects AF02 and sends opcode/payload without that leading address.

This explains the tail byte through both processors. Calling it an arbitrary correlation ID loses its routing purpose. Update handlers sometimes use a fixed `31` suffix; inspect each handler.

## Settings writes can partly succeed before an error

The [C6 handler at `0x1caa4`](v51/canonical/main/functions/0001caa4_cmd_c6_write_settings.c) validates and writes fields in order. It does not stage a complete update or roll back earlier writes. State base `S` is `0x1fffaacc`; request offset zero is the opcode.

| Request offset | Width | Accepted value | Stored at | Interpretation |
|---:|---:|---|---|---|
| 1 | 1 | 80 to 100 inclusive | `S+0x2d` | Charge limit; parser accepts intermediate values |
| 2 | 1 | 0 to 3 | `S+0x32` | Volume |
| 3 | 1 | 0 to 1 | `S+0x2e` | Screen-off setting |
| 4 | 1 | 0 to 30 | `S+0x33` | Shutdown setting |
| 5 | 1 | 0 to 1 | **No store** | Direction is validated but not copied to `S+0x2f` |
| 6 | 2, little endian | 0 to 1000 | `S+0x96` | Slope |
| 8 | 2, little endian | 0 to 1000 | `S+0x98` | OCP delay |
| 10 | 1 | 0 to 1 | `S+0x35` | Flag named systemCheck by WebLink |
| 11 | 1 | 0 to 1 | `S+0x36` | Flag named recover by WebLink |
| 12 | 2, little endian | 0 to 1000 | `S+0xa4` | Setting named usbLine by WebLink |

The numeric tests and stores are confirmed in firmware. The friendly field names use the existing WebLink interpretation where indicated; this table assigns no new physical units.

Success sets `S+0x48` and returns `c7 00`. Failure returns `c7 ff`; earlier stores remain. For example, a valid charge limit followed by volume 4 changes the charge-limit state and returns failure before setting the dirty flag. There is no remote-grant, current-mode or output-off guard inside C6. Caller-level behavior must be reviewed separately for a complete permission model.

The later worker at `0x128a4` rounds charge limit, shutdown, slope, OCP delay and USB compensation up to menu-table values. See [the normalization table](../firmware.md#0xc6-command-handler-0xcaa4). Thus the parser range does not describe every eventual setting.

The direction omission, boundaries and partial writes were checked against original instructions. The compiled C reconstruction matches the original reply and all 512 bytes of the compared state region in 400 randomized cases.

## DC control has separate mode, grant and setpoint behavior

The [C8 handler at `0x1b7f4`](v51/canonical/main/functions/0001b7f4_cmd_c8_dc_control.c) uses current mode at `S+0x30`, requested mode at `S+0x31`, remote grant at `S+0x42`, remote request at `S+0x45`, and connection type at `S+3`.

Confirmed in code and exercised offline:

- Remote selector 0 releases remote control. Selector 1 requires a grant and can return `c9 01` when absent.
- Selector 2 can grant immediately for connection type 2. Connection type 1 or 0 can leave the request pending with zero immediate reply length.
- Normal DC control requires current mode 0. A failure can still reach the common epilogue; a rejected request is not a guarantee of no state change.
- Accepted raw voltage is at most 3050, raw current at most 5100. The voltage setter can run before an invalid current returns `c9 ff`.
- With output off, a change to requested mode 1, 2 or 3 takes a separate path. It stores the mode and skips the voltage/current checks and writes. Synthetic setpoints of 65535 were ignored on those successful mode-change paths.

Voltage and current setters at `0x1af64` and `0x1aea4` write globals `0x1fffa940` and `0x1fffa944` inside critical sections. Output-enabled state is at `0x1fffaa2e`; output faults at `0x1fffaa1e`. The output branch also consults `S+0x4b`. The epilogue tests bit 2 of the word at `0x1fff9550`. These observations do not establish all effects of interrupts, later tasks or physical output circuitry.

## Reply builders and information layouts

[read_replies.c](../../../spikes/firmware_verify/reconstructed/read_replies.c) reconstructs C2, C4, DC, DE, E4, EA and EC as compilable C. Its tables give exact reply offsets, byte widths and RAM source addresses. All seven matched the original ARM code in 896 synthetic-state comparisons, including route suffixes and conditional fields.

Notable conditional fields:

- C2 reply offset 32 becomes 1 when the word at `0x1ffe02a0` is zero; otherwise it comes from `S+0x11`.
- DE uses a 16-bit field zero-extended to four bytes in mode 1, and a different 32-bit field in other modes.
- DE clamps a negative signed 32-bit field at `0x1fffab84` to zero. Its selected-index field uses a signed 16-bit comparison at `0x1fffab48`.
- EC combines the low 16 bits of the flag word at `0x1fffaca8` with the halfword at `0x1fffab6a` using bitwise OR.

These are exact byte layouts, not a finished assignment of physical meaning and units to every field.

### E0 has two different layouts

The [E0 handler at `0x1b634`](v51/canonical/main/functions/0001b634_cmd_e0_device_info.c) uses an optimized calling convention: r0=request, r1=reply, r2=route type, r3=request length.

- Type 6: `e1`, application version (4 bytes), model (8 bytes), hardware/version field (4 bytes), route suffix. Internal length 18, length 17 after suffix removal.
- Other route types: `e1`, model (8), boot identity bytes (8), application version (4), name (10). Length 31.

The second layout obtains a pointer from address `0x1c` in the missing main bootloader and reads bytes 12 to 19 through that pointer. Those identity bytes are not recovered from this update. The offline experiment uses a clearly marked synthetic pointer and identity sequence to exercise the layout; it does not discover the unit's identity.

The user's previously captured unit reported application 1.6.0.40. This reconstruction concerns 1.6.0.51 and cannot silently replace hardware observations from the other version.

## Binding in the BLE program

Relevant functions: AF02 write `0x40dc`, AF01 write `0x4224`, load hosts `0x7618`, save host `0x7696`, host lookup `0x773c`, AF02 notify `0x6f6c`.

Confirmed in code:

- For AF02 opcode `18`, a nonzero final request byte selects a lookup of 16 bytes starting at request offset 1. The immediate reply is `19 00` for a match or `19 ff` otherwise.
- A zero final byte copies those 16 bytes to pending-host storage at RAM `0x20005130` and forwards the request to the main processor/UI.
- A successful main-processor `19 00` result saves the pending ID and updates connection state to 2 only when the guard byte at `0x20002f88` is zero.
- Host storage is 80 bytes at storage offset `0x6f00`, holding five 16-byte IDs. All-`ff` slots are unused. When full, the code shifts old entries and appends the new ID.

The earlier WebLink field boundaries around class, host ID and fastBinding remain a separate interpretation. The firmware's exact operations above are clearer than assuming that those field names establish the layout. No fast-bind frame was sent to hardware.

Binding and permission to control power use distinct state. Main UI service `0x54688` handles the bind prompt; decline callback `0x2483c` clears the decision/pending bytes and schedules a reply. Allow callback `0x2478c` sets the decision byte; deny callback `0x2483c` clears it. Both clear pending and set transmit bit 1. Physical button mapping, timeout behavior and persistent-store failure handling remain open.

## USB and GATT tables

[usb-descriptors.json](v51/canonical/usb-descriptors.json) and [gatt-table.json](v51/canonical/gatt-table.json) retain raw descriptor/table bytes and addresses.

| USB object | BLE processor address | `data.bin` offset |
|---|---|---|
| HID report descriptor, 35 bytes | `0x8f4c` | `0x12f4c` |
| Configuration, 41 bytes | `0x8f70` | `0x12f70` |
| Device descriptor, 18 bytes | `0x8f9c` | `0x12f9c` |

The device descriptor contains VID `0x28e9`, PID `0x028a`. Endpoint 1 IN and OUT have 64-byte packets and interval 1. Output report ID 1 and input report ID 2 each have 63 bytes after the report ID.

Queue service `0x3e1a` limits chunks to **62** stream bytes. Transmit routine `0x4eca` forms a 64-byte USB packet as report ID 2, one count byte, then the supplied bytes. The sender has no local bound check; the queue supplies the limit. Receive routine `0x4e86` takes its count from byte 1 and feeds bytes beginning at byte 2 into the frame decoder. Keep this firmware transmit maximum separate from the previously observed WebLink host-side 61-byte stride.

The initialized GATT tables contain AF00/AF01/AF02, DB00/DB01, and Device Information 180A. The AF and DB characteristics have properties `0x1a` (read, write, notify). Attribute handles start at zero and are assigned at runtime, so static table indexes are not observed ATT handles. Some generic UUID pointers address the missing WCH library; their UUID bytes are obtained from the separately sourced SDK reference and are marked as such in the export.

The initialized BLE name contains `0030MP305B`. The running unit previously advertised `0000MP305B`. The path that chooses or rewrites the prefix remains unresolved.

## Other command families

The [command map](command-map.md) covers dispatcher cases, handler addresses, immediate/deferred reply behavior, mode guards, program transfer, charging and update commands. It also records several differences from the earlier notes:

- Opcodes 51, 53 and F1 test route type 3, not a payload length of 3.
- Opcode 20 replies with opcode 20, not necessarily request plus one.
- D2 and D6 have output-off effects in the dispatcher.
- DA accepts program IDs 1 through 9, while D6 accepts 1 through 10.
- D0 uses a request-derived index without a local range guard. No malformed request was sent to hardware.

The charger handler uses six rows of 11 little-endian halfwords in recovered RAM at `0x1ffe07e0`. [charger-limits.json](v51/canonical/charger-limits.json) exports every value. The voltage bounds begin with 4250-4450, 4150-4250, 4050-4150, 3600-3700, 2350-2450, and 3-13, with steps 20, 10, 10, 10, 10, and 1 respectively. Chemistry names are not assigned here without tracing the corresponding UI/enum mappings.

## Verification and limits

The [verification guide](verification.md) records commands, environment and per-suite results. [analysis-summary.json](v51/canonical/analysis-summary.json) records current function counts and warning counts. [decompiler-warnings.tsv](v51/canonical/decompiler-warnings.tsv) makes the remaining diagnostics searchable.

A discovered function is not a reviewed function. A successful Ghidra decompilation can still have a bad control-flow graph, unresolved indirect calls, incorrect types or misleading C syntax. The 8051 compiler's shared tails and jump tables need particular care. The helper at `0xae53` reads triples of target address and case byte, with a zero-address terminator and default target. Helpers at `0xad79` and `0xad92` consume four constant bytes after the call and continue after them. [Recover8051Tables.java](../../../spikes/firmware_verify/scripts/Recover8051Tables.java) recovers these layouts and three indexed jump tables; [pd-tables.tsv](v51/canonical/pd-tables.tsv) records every recovered target or continuation. The repeated-call seed pass remains heuristic, with its candidates in [pd-call-seeds.tsv](v51/canonical/pd-call-seeds.tsv). RAM copies contain code also present in flash and must not be counted as independent firmware bytes. The compiled reconstructions cover selected protocol behavior only.

The update omits the main bootloader below `0x10000`, the BLE library at `0x40000`, per-unit calibration and persistent runtime data. Original source names, types, comments and build options are not generally recoverable exactly. Full reproducible firmware rebuilding, complete UI/graphics/font extraction, exact MCU identification and a reviewed power-control implementation remain unfinished. See [TODO.md](../../../TODO.md). New execution results and corrections are in the verification ledger; the original summary retains the earlier pass counts as provenance.
