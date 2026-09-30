# Firmware recovery and independent comparison

MP305B V51, 2026-09-30. Research revision: uncommitted.

## Outcome

The recoverable host-interface work in `~/mp305b-fw-re` is complete. All
33 probe jobs finish with checked emulator returns. There are 657 asserted
cases: 305 encoder comparisons, 300 decoder comparisons, eight bridge-route
scenarios and 44 targeted recovery cases. The 324 command-table rows are
recorded observations and are counted separately.

The recovered bundle contains 2453 main, 255 CH58x and 380 PD function
exports, plus 322 named locations and preserved aliases. Different function
entry sets prevent treating these totals as coverage or adding them to the
existing canonical exports. Both analyses remain available.

The original binary inputs, projects and notes are preserved. No hardware
commands, commits, production implementation or V-model gate approval are
part of this work. Complete sources, results, logs and regeneration commands
are linked from [the recovery record](README.md).

## Evidence and independence

Instruction inspection, decompiled code and original-instruction execution
are **confirmed in code** evidence. Emulator checks use synthetic memory,
modeled peripherals and selected external-call substitutes. **Inferred**
meanings retain that label. Existing capture comparisons are evidence from
older recorded hardware sessions; no new hardware confirmation is claimed.

The recovered notes began from independent Ghidra imports. Their comparison
sections also use the previous research and the existing WCH API map.
They are not independent rediscoveries of every SDK symbol or hardware role.
A firmware-to-firmware comparison is distinct from the project's use of
"cross-checked" for independent derivation from WebLink JavaScript.

The statement tables in the appendices compare the source documents as
seen during the original independent pass. Earlier files have since been
corrected. Recovery corrections below take precedence over the historical
verdict wording. Full vectors and implementation notes are in the linked
Markdown files rather than compressed into the printed tables.

## Corrections verified during recovery

| Subject | Reviewed result | Evidence |
|---|---|---|
| Startup VTOR | SystemInit writes `0x10000` at `0x1DB8C` | Instructions and executed write |
| Main decoder | State `+0x208`, fill index `+0x20C`, escape count `+0x213` | Instructions and stepped execution; rejects the independent note's proposed offset correction |
| CH58x global pointer | `0x20002000`; AUIPC is relative to its own PC | First two startup instructions executed |
| Reset path | Mailbox `0x2005F000 = 0x1234`, then AIRCR reset request | Original instruction write trace; reset helpers marked non-returning |
| AF01 prefix | First incoming byte discarded; outgoing `31` is a route marker | Bridge probes and asserted byte traces |
| Waveform flag | Timer absent: 1; timer present: `S+0x11` | Four reply-builder cases |
| Fault addresses | Source `0x1FFFAA1E`, published copy `0x1FFFAB6A` | Producer and publisher inspection |
| Fault meanings | Software OCP/OVP paths, specific thresholds and hysteresis | Producer inspection and 12 boundary cases |
| Permission scope | Four control-mode cases reject absent grant; BE accessory input reaches an enable request separately | Dispatcher and worker execution with a recorded actuator call |
| USB reassembly | 127 stream bytes split into 62, 62 and 3; two frames in one OUT report lose the first in the tested path | Original bridge instructions |

The BE result describes a command reaching the output request. It does not
establish physical activation, electrical behavior, or the response of a
real unit after its user presses Deny. The project continues to disconnect
after denial under UR-008.

## Completed jobs and remaining work

| Job | Completion evidence |
|---|---|
| Recover source material | SHA-256 snapshot of 110 original workspace files; original notes and projects retained |
| Compare input images | Companion slices and initialized RAM match; main differs from restored image only in WebLink's four identity-magic bytes |
| Main command analysis | 12 probe groups, 324 regenerated table rows, reviewed command and state notes |
| Host link | 12 probe groups, including the 605 asserted framing comparisons |
| CH58x bridge | Eight diagnostic groups and eight asserted scenarios in the routing job |
| Additional verification | 44 asserted cases with actual and expected results |
| Ghidra completion | Pending main and bridge helpers, deterministic naming, three corrected reset attributes, all requested decompilations complete |
| PD baseline | Existing 380-function export recovered; canonical 1007-entry table recovery retained |
| Register-map comparison | Seven vendor SVDs rescored; exact main MCU still unresolved |
| Report | Markdown, LaTeX and inspected PDF |

The import of the pending main helper adds 143 candidate entries; the bridge
helper adds 12 callbacks. These counts do not establish that every entry is
a distinct source function. Main register labels retain the original
HC32F4A0 SVD assumptions. Multiple HC32 variants match similar addresses;
the clock-controller conflict at `0x40054000` remains unresolved.

The original host-interface scope did not include complete PD or power-stage
internals, bootloader execution, physical pin tracing or replacement firmware.
Those remain on the repository research list. The recovered update vectors
use a synthetic flash array; they are not a validated device-update recipe.

## Coverage of the repository research documents

| Document | Recovery treatment |
|---|---|
| firmware.md | Detailed comparison in appendices; VTOR, D2 layout, companion identity and reset text corrected |
| protocol.md | Detailed comparison in appendices; route marker, waveform field and fault descriptions corrected |
| firmware-architecture.md | Host, bridge, startup and transport sections compared; RTOS conclusions retained |
| firmware-command-map.md | Dispatcher routes and handlers supplemented by the complete command notes |
| firmware-permissions.md | Shared control checks and accessory-input path added; policy retained |
| firmware-readable.md | Existing readable-C reconstruction retained; recovered named decompilation is an additional view |
| firmware-rtos.md | Existing scheduling/resource reconstruction retained; no new timing, stack or heap-lifetime measurement |
| firmware-verification.md | Earlier 2835-case run and manifest retained as historical evidence |
| hardware.md | Bus-role evidence retained; recovered labels do not identify exact silicon |
| hardware-buses.md | Main UART routing and CH58x endpoints compared and expanded in host-link notes |
| hardware-registers.md | Existing three-image access inventory retained; no claim to resolve every indirect access |
| hardware-ui-and-analog.md | Fault thresholds and local waveform semantics supplemented; physical topology remains inferred |
| device.md | Manufacturer specifications and rear-port distinction retained; no new unit inspection |
| README.md and captures | New bundle indexed; all four immutable capture hashes checked |

For documents outside host interoperability this is an explicit scope review,
not a claim that every statement was independently re-proved. Canonical
per-function artifacts were checked for preservation, rather than represented
as thousands of newly analyzed documents.

## How to read the appendices

C or Confirmed means agreement with the cited code evidence. X or Corrected
identifies a corrected earlier statement. N or New identifies an addition
relative to the source snapshot. Inferred interpretations and unresolved
hardware questions remain visible. The annotations refer to the original
analysis methods described in the full command, host-link and CH58x notes.



## Command and telemetry comparison

Full source: [commands analysis](notes/commands.md).


Scope: `firmware.md` from "Command dispatcher" through "Block write and the
`0xF0` to `0xFE` commands", and `protocol.md` sections 3 and 4. Addresses in
`firmware.md` are file offsets; `+0x10000` gives the processor addresses used
here. "Confirmed" means the statement was re-derived from the disassembly or
by execution in this pass.

### firmware.md, "Command dispatcher"

| Statement | Verdict |
|---|---|
| Function at `0x2F34`, watches four flag bytes, first set flag selects a record in `0x1FFF9660`, stride 260 | Confirmed (`0x12F34`, flags `0x1FFE01AC..AF`) |
| Byte 0 is the type byte, byte 2 the length, byte 4 the opcode | Confirmed. New: byte 0 is the high nibble and byte 1 the low nibble of the frame's address byte; type 1 = USB host, 3 = CH58x system, 5 = CH58x BLE-central side, 6 = BLE host (section 1) |
| A request the switch does not recognise falls through without a reply | Confirmed, with the full list of ignored opcodes (2.1) |
| Most handlers write `opcode + 1`; `0x20` stores `0x20` | Confirmed |
| Type 6 appends one extra byte copied from the end of the request | Confirmed; it is the BLE route byte (`31` AF01, `00` AF02) added by the CH58x |
| `F2`, `F4`, `F6`, `FC`, `20` append the constant `0x31` | Confirmed |
| Type 6 is not by itself a transport name; `BD` treats types 5 and 6 differently | Corrected: type 6 is the BLE host route (CH58x `ram:0x4074` addresses every GATT write `06 02`); type 5 is the CH58x's own BLE-central side |
| Shape `(request, length, reply, type)` for `A2 C2 C4 C6 C8 D0 D2 D4 D6 DA DC DE E1 E2 E4 E8 EA EC EE` | Confirmed at every call site |
| Shape `(request, reply, type, length)` for `00 20 E0 F0 F2 F4 F6 FC FE` | Confirmed (`F2`, `F4`, `F6` ignore the length) |
| `BB`, `BD`, `BE` get the length in `r1` and no reply buffer | Confirmed; `BD` also gets the type in `r2` |
| Payload byte N is request byte N+1 | Confirmed |
| `E2` and `E8` each have a block the decompiler dropped | Confirmed; both blocks are written out from the disassembly in 5.18 and 5.20 and executed |

### "Opcodes with their own compare"

| Row | Verdict |
|---|---|
| `00` `0xDFFC`, `01 91 67 01` | Confirmed |
| `18` inline `0x3126`, sets `S+0x47`, stores the type, no reply | Confirmed (type goes to `K+6`) |
| `20` `0x16A8` block write, reply opcode `20` | Confirmed |
| `51` inline `0x312E`, type 3 and payload 0, clears a flag, stores 1000 | Confirmed; new: it acknowledges main's `50` link-state message (2.3) |
| `53` same shape, the other flag | Confirmed; acknowledges main's `52` |
| `A0` inline `0x307E` | Confirmed |
| `A2` `0x8368` | Confirmed |
| `BB` `0x5AA0` list ingest | Confirmed; it is the CH58x's BLE scan list |
| `BD` `0x4660` connection state and peer metadata | Confirmed; type 6 sets the host link `S+3` |
| `BE` `0x855C` | Confirmed |
| `C2 C4 C6 C8 D0 D2 D4 D6 DA` handlers | Confirmed |
| `D8` inline `0x31F0` | Confirmed |

### "Opcodes `0xDC` to `0xFE`"

| Statement | Verdict |
|---|---|
| Table branch at `0x304E` covers `DC..FE` | Confirmed (`TBB` at `0x1304E`, 35 entries at `0x13052`) |
| The response opcodes in that range go to the no-reply path | Confirmed, plus `E6`, `E7`, `F8..FB` |
| `DC` `0x565C` two payload bytes | Confirmed: id and step count of the selected slot |
| `DE` `0x5694` 69 bytes | Confirmed |
| `E0` `0xB634` two layouts | Confirmed; layout chosen by route (6 = BLE short, else long) |
| `E1` `0x3C40` acts only for type 3, no reply | Confirmed; it stores the CH58x's version |
| `E2` `0xB4D0`, `E4` `0x5630`, `E8` `0xD520`, `EA` `0x54AC`, `EC` `0x555C`, `EE` `0x3D44` | Confirmed |
| `F0` replies `F1 00` only for payload `AC` | Confirmed |
| `F1` inline `0x30D8`, type 3 and payload 0, no reply | Confirmed |
| `F2` `F3 00` + status | Confirmed |
| `F4` `F5 00`, four echoed bytes, status | Confirmed (the four bytes are the SPI address) |
| `F6` `F7 00` + status | Confirmed |
| `FC` log slot only for payload `CA` | Confirmed; the slot holds the update request code 1/3/7 |
| `FD` inline `0x32C0`, payload 3 or `FF`, no reply | Confirmed |
| `FE` `0xDB94`, `FF AA 55` or `FF 00 00` | Confirmed |
| WebLink does not name `00 20 51 53 A0 BB BE F0..FE`; they are in the image | Confirmed (not re-checked against WebLink) |

### "`0xC2` reply, handler `0x58BC`"

| Statement | Verdict |
|---|---|
| Always writes through payload 35 and returns 37 (38-byte BLE frame with address) | Confirmed (emu) |
| Field table payload 0..32 and sources | Confirmed byte for byte (emu) |
| Payload 31: 1 if a global word is 0, otherwise `S+17` | Confirmed; the global is the device waveform-page timer `0x1FFE02A0` |
| Payload 32: offset 76 of a second global | Confirmed: `0x1FFFA934 + 0x4C` = `0x1FFFA980`, raw output-on time in ms |
| Little-endian | Confirmed |
| "The scale of each field is not in this copy loop" | Resolved: section 7.1 gives the producer and unit of every field |

### "`0xC4` reply, handler `0x5EF8`"

Confirmed entirely (12 bytes, table, `usbLine` always present). New: the
same builder is also sent unsolicited when `FLAGS` bit 12 is set.

### "`0xC8` command, handler `0xB7F4`"

| Statement | Verdict |
|---|---|
| `r5[0]` is the opcode; reply opcode + status; 0 applied, 1 remote not granted, `FF` rejected; length 2 or 3 | Confirmed (emu) |
| Mode not 0: `FF`, the common epilogue still runs, an existing request value 0 clears the grant | Confirmed. New: `rc = 0` then does not release the grant (the request byte is not written), so release must use the mode's own command |
| `rc` above 2: `FF` | Confirmed |
| `rc` 1 without grant: status 1, nothing applied | Confirmed |
| `rc` 0 clears `S+66` | Confirmed (through the epilogue) |
| `rc` 2: if `S+3 == 2` both set to 1, otherwise length 0 | Confirmed. New: `S+3 == 2` means a USB host; over BLE the request waits for the front-panel prompt and is answered later by a deferred `C9 00`/`C9 01` (section 3) |
| Different requested mode: output off, transfer state not 1, target below 4, stores `S+0x31`, skips the other checks | Confirmed (emu with `FFFF` setpoints) |
| Writes are sequential; a valid voltage can be stored before a bad current | Confirmed (emu #8) |
| Field table (3050, 5100, `realChange` 3 -> `S+24`, `voltageSlow` 1 -> `S+16`, `currentOver` 1 -> `S+18`, output via `0xA128/0xA134/0xAEBC/0xCB8C`, model 3, refresh -> `0xA5FC`) | Confirmed. Corrections: model is only compared, `0xA128` is not "called for a different model" but used as the output-off guard; `0xCB8C` is the buzzer, not output control |
| 3050 = 30.50 V, 5100 = 5.100 A | Confirmed by the units of the targets `0x1FFFA940` (10 mV) and `0x1FFFA944` (1 mA); new: an output voltage of 33.001 V or more for 500 ms sets fault bit 6 |
| Bit 2 of the word at `+264` skips the setpoint update and still builds a reply | Confirmed; new meaning: it is the deferred-reply mode set by the remote prompt callbacks, used when the transmit service calls the handler with `C8 31` |

### "State blocks"

| Row | Verdict |
|---|---|
| `S` = `0x1FFFAACC`, the dispatcher's `fp` | Confirmed |
| `0x1FFFA354` program table, ten slots | Confirmed; layout in 6.3 |
| `0x1FFFA138` PD profile table | Confirmed; layout in 6.4 |
| `0x1FFFA340` PD class byte per index | Confirmed; it is the profile wattage |
| `0x1FFFA8C4` program working bytes | Corrected: storage-worker request flags (`+0` PD save, `+1` last `D2` index, `+2` header save, `+3` op, `+4` steps save, `+5` step-save clears busy, `+6` load for `D8`, `+7` slot, `+8` `DA` cursor, `+9` table re-save check) |
| `0x1FFF8F7C` step records, stride 12 | Confirmed; transfer buffer of 100 records |
| `0x1FFE0184` slot structure `K` | Confirmed; it is the link/transmit control block (1, 2.3, 5.12) |
| `0x1FFF9660` four records, stride 260 | Confirmed |
| `0x1FFFA0B8` language byte at `+0x16` | Confirmed; the block is the persistent configuration |
| `0x1FFF9448` remote-control gate word at `+0x108` | Corrected: `0x1FFF9550` is the general event/transmit flag word (section 8); only bit 2 concerns remote control |
| `0x1FFE07E0` charge limit table, stride `0x16` | Confirmed |
| `0x1FFFA00C` block used by `20`, `F0`, `FC` | Confirmed; also `F2`, `F4`, `F6` (update state) |

### "`0xE0` reply, handler `0xB634`"

| Statement | Verdict |
|---|---|
| Reply byte 0 is the constant `E1` | Confirmed |
| "Nothing in this function says which transport a type belongs to" | Corrected by the route analysis: type 6 = BLE, type 1 = USB host (section 1) |
| Type 6 returns 18 bytes: `01 06 00 33`, `MP305B 00 00`, `02 00 02 00`, request's last byte | Confirmed (emu) |
| Other types return 31 bytes with the listed fields | Confirmed (emu for types 1, 3, 5); no suffix in this layout |
| The handler reads the word at absolute `0x1C` and copies 8 bytes from it + `0x0C` | Confirmed |
| The app's vector word is `0x0007AFC8`, `+0x0C` gives hardware revision then version; the 8 bytes are not in `app.bin` | Confirmed. New (inferred): the bootloader's vector 7 points to its identity block the same way (the update verifier `0x1FE0C` relies on vector 7 of an image), so the 8 bytes are the bootloader's hardware revision and bootloader version |
| "WebLink's USB field names do not line up with either layout" | Corrected: the long layout is exactly serial 8 (the model string), hardware 4, bootloader 4, application 4, name 10 |
| Bluetooth captures match the type 6 order with `01 06 00 28` | Consistent with the short layout (not re-checked against the captures) |

### "`0xC6` command, handler `0xCAA4`"

| Statement | Verdict |
|---|---|
| Reply `0` or `FF`, length 2 or 3; first failing check stops later stores; output byte not read | Confirmed (emu at every bound) |
| Check/store table rows 0..11 | Confirmed, including `screenDirection` validated but not stored |
| Payload 9, 10 not in `C4`; `usbLine` at 11; WebLink's view | Confirmed for the image side |
| Settings worker `0x128A4` and the normalisation tables | Not re-checked in this pass (settings area) |

### "`0x18` bind"

| Statement | Verdict |
|---|---|
| `S+0x47 = 1`, type at `K+6`, no-reply path | Confirmed (emu) |
| `19` built at `0x2690`, called from `0x3836`; `0` if `S+0x46 != 0` else `FF`; zero byte for caller type 6 | Confirmed (`0x12690`, from the transmit service `0x133BC`; emu) |
| `0x1478C` and `0x1483C` set/clear `S+0x46`, `S+0x47`, bit 1; which front-panel action calls which is open | Resolved: processor `0x2478C` and `0x2483C` are the allow and deny button callbacks of the bind prompt (buttons `0x1FFE06C0` and `0x1FFE06C4`, registered in `0x21A50`) |
| After `0x2690` returns, `0x3836` clears bit 1 | Confirmed; it also clears `S+0x46` and `S+0x47` |

### "Language, `0xA0` and `0xA2`"

Confirmed. Clarification: all `A2` side effects (store, output off or
charger stop, configuration save, `S+0 = 1`) happen only when the value
changes (emu).

### "`0x00`, handler `0xDFFC`"

Confirmed.

### "Remote-control tail"

| Statement | Verdict |
|---|---|
| `C8`, `E2`, `E8`, `EE` share one skeleton | Confirmed |
| Bit 2 skips the body and still builds a reply | Confirmed (deferred-reply mode) |
| `rc` must be below 3; mode 0/1/2/3 or `FF` | Confirmed |
| `rc` 2 stores `S+0x45`; with `S+3 == 2` both set; else length 0 | Confirmed |
| `rc` 0 clears `S+0x42` | Confirmed, only in the matching mode |
| `rc` 1 requires the grant or status 1 | Confirmed |
| `E2` and `E8` are where Ghidra dropped a block | Confirmed |

### "Program table"

| Statement | Verdict |
|---|---|
| Ten slots, ids at `+0xAA`, per-slot flag at `+0xA0`, count at `+0xB5`, selected at `+0xB4`, 16-byte record per slot | Confirmed. The "flag" is the step count and the 16-byte record is the program name |
| `D4` reply: count, then for ids 1..count the slot's 16 bytes and flag; variable length | Confirmed; new: ids not contiguous from 1 are omitted |
| `DC` | Confirmed |
| `D8`: `r3 = 0` at `0x2FB0`, scan from slot 0, `K+4`, `0x1FFFA8C4+6`, `K+5` | Confirmed; also `K+3 = 0`. New: an unknown id produces no `D9` at all |
| Worker `0x1D380` reads `0x4B0` bytes from `0x162000 + slot*0x1000` into `0x1FFF8F7C`, sets bit 7; service `0x133BC` calls `0x15CA0`; `D9`, id, up to ten 12-byte records, cursor `0x1FFE0187`; route suffix for type 6; full chunks 122 bytes; bit 7 cleared at the step count | Confirmed (emu with 3 and 12 steps). New: the destination and suffix come from `S+3`, not from the route of the `D8` |
| `D6`: id 1..10, find or allocate, increments the count, copies 16 bytes and a flag, two further bytes, second == 1 deletes and renumbers; `0`/`FF`; dispatcher clears `+8` and calls `0xAEBC(0)` | Confirmed. New: the first of the two bytes is the save flag, the second the operation (0 write, 1 delete, 2 write with steps to follow), see 5.11 |
| `DA`: id 1..9, looked up, up to ten steps of three words, 30500, 5100 unless the third is 0, third at most 99990 | Confirmed (emu at each bound). New: exactly ten records are read every call, an id without a slot is `FF`, the cursor only resets on `D6` |
| 5100 = 5.100 A; 30500 reads as 30.500 V if a step is 1 mV | Confirmed: the runner divides the first word by 10 before setting the 10 mV target, and the UI prints it as mV |
| "99990 is the constant only" | Resolved: the third word is the step duration in seconds |
| Accepted steps at `0x1FFF8F7C`, stride 12; filling the count returns 0 | Confirmed; the deferred `DB 00` follows the flash write |
| A rejected value sets `FF` and 2 at `S+0x4B`; the dispatcher writes 1 afterwards | Confirmed. New consequence: the busy flag stays 1 until a later successful save |
| `DE` table rows 0..64 | Confirmed byte for byte (emu). Names and units in 5.15 |
| `E2` layout offsets 0..3, mode change guard, action to `S+0x4C`, enabling needs steps and no faults, output off clears `S+0x4C`, sets `S+6`, calls `0xCB8C(1)`; disabling can call `0xAEBC(0)`; success sets `S+0x49`; status 0/1/`FF` | Confirmed (emu). New: action 1 previous step, 2 pause/resume, 3 next step; `S+6` starts the program runner; `0xCB8C` is a beep |

### "PD profiles"

| Statement | Verdict |
|---|---|
| `D0`: echoes payload 0, index = byte - 1, class `< 0x65` -> 7 groups else 9, 16 bytes, class, count, groups from `+0xA0 + index*0x24` | Confirmed (emu); no index check |
| `D2`: index below 10 or `FF`, 16 bytes, class, a count, up to 9 groups, groups past the count masked `0xFFF8`, dispatcher writes 1 at `S+0x4B` | Confirmed, with one correction: a **save byte follows the count** before the groups (`D2, id, name[16], class, count, save, groups`). New: the dispatcher also requests the output off; without the save byte the busy flag stays set |
| `E4`: `0x1FFFA138+0x212` plus 1 | Confirmed; also sent unsolicited (bit 10) |
| `E8`: offsets 0..5, mode-change path, enable requires no faults, sets selector, `S+0x2A`, `S+0x2C`; disable can call `0xAEBC(0)`; dirty flag | Confirmed (emu). New: `S+0x9C` and `0x1FFF9BB9` are stored before any check; `S+0x9C` is a PDO enable mask; the output is switched on only after the PD companion acknowledges (5.20) |

### "Charge"

| Statement | Verdict |
|---|---|
| `EA` returns `0x15`/`0x16`, table | Confirmed; names in 5.21 |
| `EC` returns `0x1F`/`0x20`, table, payload 26 low half ORed with `S+0x9E`, 28 high half | Confirmed; names in 5.22 |
| `EE` payload offsets, type below 6, voltage between table entries 0 and 10, cells limits 7/9/13, type 5 not stored, current below 5001, output bit with `S+0x4B` | Confirmed (emu at every bound) |
| Output 1 calls `0xA134` and `0xD6FC` when `S+0x7B == 0` and `S+0x9E == 0`; output 0 calls `0xD858` when `S+0x7B != 0`; both call `0xCB8C(1)` | Confirmed, except that the beep only happens when the charger is actually started or stopped (emu) |
| Mapping each numeric type to a chemistry needs a UI trace | Resolved: 0 LiHv, 1 LiPo, 2 Lilon (Li-ion), 3 LiFe, 4 Pb, 5 NiMH/Cd; for type 5 the u16 is the -dV threshold in mV |

### "Connection state and list ingest"

`BD`, `BE`, `BB` statements: confirmed (emu). Additions: `BD` from type 6
is the CH58x reporting whether a BLE host is bound (`BD 01`/`BD 00`); `BE`
selector 0 also copies pending flags to `S+0x1D`/`S+0x1E`.

### "`0x51`, `0x53`, `0xF1` and `0xFD`"

Confirmed. Additions: the meanings in 2.3 and 5.25; `FD 03` also sets
`0x1FFF9438 = 1`; `F1` completes the pre-update handshake.

### "`0xE1` received"

Confirmed; the four bytes are the CH58x's application version (bytes 17..20
of the long `E1` layout).

### "Block write and the `0xF0` to `0xFE` commands"

| Statement | Verdict |
|---|---|
| `20` subcommand 5: offset at 5..8, length at 9..12, data at `0x1D`; offset 0 erases `0x100000..0x130000` via `0xBDC6` and clears the checksum; length must be `0x80` and `offset + 0x1000 < 0x44000`; counter `+0x0C` += `0x80`; write, read back, add each byte; reply opcode, subcommand, offset, status, length 7 | Confirmed (emu) |
| Subcommand 6 compares the word at `0x0D..0x10`; match echoes 6, mismatch `0x86` and clears the counter; bytes 2..5 checksum, byte 6 zero | Confirmed (emu) |
| Type 6 appends `0x31` | Confirmed. New: any other subcommand returns the single byte `31` for type 6 |
| `0xBDC6` sends `0xD8` to `0xBF9C` between `0xF420(6,4)` and `0xF3CC` | Confirmed: 64 KB sector erase (`06` write enable, `D8`, `04` write disable) |
| `F0`: byte `AC`, sets `0x1FFFA00C = 1`, `F1 00` | Confirmed |
| `F2`: clears `0x98` bytes, first byte 1, `0xFC24`, status | Confirmed. New: `0x1FC24` erases block 0 and the target range, and loops 65536 times for a length below `0x10000` |
| `F4`: `0xFC94`, `F5 00` + request bytes 2..5 + status | Confirmed. New: it programs 128 bytes and sums the read-back words |
| `F6`: `0xFE0C`, failure erases `0xF0000` | Confirmed. New: success writes the identity magic `AA55CC33` into the staged image |
| `FC`: byte `CA`, walks `0x1F0000` in 16 blocks of `0x100`, status 1, 3 or 7 from the counter, four records through `0xBF3A`, `FD 00` | Confirmed; the four records are the update header at SPI 0 (length, sum, count, magic), written only when `0x1FFFA010 != 0` |
| `FE`: `AA 55` -> `0xDBE8`, `0xCA60(200)`; `0xDBE8` sets `0x1FFE01CC` bytes, calls `0xD868`; no reset register; not a bootloader entry | Corrected: `FE AA 55` is a factory reset followed by a reboot. `0xCA60(200)` starts a countdown in `0x12850`, which ends in `0x1B71C`: `0x1234` written to `0x2005F000` and `AIRCR = 0x05FA0004` |

### protocol.md section 3, "Opcode matrix"

| Statement | Verdict |
|---|---|
| Response = request + 1, except `20`; `D8` and `18` answered by deferred `D9` and `19` | Confirmed. New: `C9`/`E3`/`E9`/`EF` (remote prompt), `DB` (after the last `DA` chunk) are also deferred, and `C5`, `DD`, `E5`, `EB` can arrive unsolicited (section 8) |
| Matrix rows `E0`, `18`, `C2`, `C4`, `C6`, `C8`, `D0`..`EE`, `A2` | Confirmed. Refinements: `BD` is the CH58x's link report, not a host command; `DE` serves modes 1 and 2 as listed; `E2` "run/pause/step" is action 1 previous, 2 pause/resume, 3 next plus output start/stop |
| `18` "BLE (AF02)" | The main firmware accepts `18` on any route; the CH58x forwards it from AF02 |
| `0x18` sets a flag; `0x12690` emits `19` after a UI decision | Confirmed |
| The switch also accepts `00 20 51 53 A0 BB BE F0..FE` | Confirmed |
| Unrecognised requests get no reply | Confirmed |

### protocol.md 4.1, `C2` -> `C3`

| Row | Verdict |
|---|---|
| Handler `0x58BC`, 37 bytes | Confirmed |
| `outState` 1 CV, 2 CC | Confirmed; 0 = output off (confirmed in code), 3 = output held above the setpoint (inferred) |
| `batteryState` internal enum | Refined: 0 on battery, 1 external input charging, 2 charge held (7.1) |
| `percentage` 0..100 % | Confirmed as the battery state-of-charge byte |
| `voltage` 10 mV | Confirmed in code (INA226 mV / 10); reads 0 with the output off below 0.501 V |
| `setVoltage` 10 mV, `current` 1 mA, `setCurrent` 1 mA | Confirmed in code; current reads 0 with the output off |
| `workingTime` s | Confirmed in code (calibrated ms counter / 1000) |
| `energy` 0.1 Wh | Confirmed in code (mWh / 100, rounded) |
| `power` 10 mW | Confirmed in code (µW / 10000, rounded) |
| `currentOver`: setting, 0 CC, 1 OCP | Confirmed: 1 trips fault bit 5 after the OCP delay |
| `realChange` bit 0 voltage, bit 1 current live updates | Confirmed in code: the bits select live knob editing per field (`0x5A270`, `0x57064`); while the output is on, any nonzero value also sets the UI refresh period to 100 ms instead of 200 ms (`0x1E284`) |
| `voltageSlow` step or ramp at the settings' ramp rate | Confirmed: ramp of `slopeSteps` mV per 100 ms, also at switch-on from 0 V |
| `output` 0/1 | Confirmed; it is the actual power-stage state, not the request |
| `model` 0..3 | Confirmed |
| `voltageBoard`, `currentBoard` UI keypad input flags | Consistent: persisted UI entry-mode flags, default 1 (inferred) |
| `temperature` °C | Refined: signed int8, the companion's first temperature, which the firmware uses for the battery protections |
| `chargeError` bitmask, see 4.5 | Confirmed; producer and every bit in 7.2 |
| `wavePause` waveform streaming active flag | Corrected: 1 if the device waveform page timer pointer is zero, otherwise S+0x11. The reply field alone does not identify host streaming |
| `waveTime` timestamp in ms | Refined: raw output-on time in ms, the uncalibrated counter behind `workingTime`, reset by refresh and mode change |
| `outState` 0 probably "neither, output off" (inferred) | Confirmed in code |

### protocol.md 4.2, `C8` -> `C9`

| Statement | Verdict |
|---|---|
| WebLink sends `rc = 2` then full `rc = 1` frames | Consistent with the handler |
| Payload 11 bytes, field table | Confirmed |
| `refresh` 1 = reset cumulative counters | Confirmed: energy and time (`0x1A5FC`) |
| `model` target mode (0 = DC) | Confirmed; 1..3 request a mode change while the output is off |
| Status 0, 1, `FF` | Confirmed; the deferred reply uses 0 (allowed) and 1 (denied) |
| 3050 / 5100 limits, `FF` in other modes, epilogue can change grant state, no rollback, `rc > 2` rejected, `rc = 1` needs the grant | Confirmed (emu) |

### protocol.md 4.3, `C4`/`C6`

Byte layouts and the `C6` check table: confirmed (emu). The discrete lists
and units are WebLink's; this pass adds that slope is used as mV per 100 ms
by the ramp (`0x19E68`) and the OCP delay as milliseconds (`0x19E68`
compares it with a millisecond counter).

### protocol.md 4.4, `E0` -> `E1`

Confirmed, with the corrections above: layout chosen by route (6 BLE short,
others long); the long layout matches WebLink's USB field list; its bytes
8..15 (payload offsets) are inferred to be the bootloader's hardware
revision and version.

### protocol.md 4.5, `chargeError`

| Bit | Verdict |
|---|---|
| 0 `OUTPUT_REVERSED` | Consistent: ADC1 channel 3 above 0.5 V (sensor meaning inferred) |
| 1 `LOW_BATTERY` | Confirmed in code |
| 2 `BATTERY_LOW_TEMP` | Confirmed: below -19 °C |
| 3 `BATTERY_OVERHEAT` | Confirmed: above 57 °C |
| 4 `SYSTEM_OVERHEAT` | Confirmed: other sensors at or above 85 °C |
| 5 `DC_OUT_OCP` | Refined: software OCP after the OCP delay with `currentOver = 1`, not a hardware trip |
| 6 `DC_OUT_OVP` | Confirmed: 33.001 V or more for 500 ms |
| 7 `DIC_INIT_ERROR` | Confirmed: power-stage start-up failure |
| 8 `DC_OUT_VOL_FAIL` | Confirmed: INA226 and ADC voltage disagree by 5 V or more in CV |
| 9..15 charger faults | Corrected: the reviewed producers set only bits 0..8 in `S+0x9E` (the `C3` field). The separate charger word contributes bits 10 and 11 to `EC`; indirect writes remain outside this absence claim |

### protocol.md 4.6

| Statement | Verdict |
|---|---|
| `18`/`19` behaviour | Confirmed |
| `A0`/`A2` behaviour | Confirmed |
| `DA` limits | Confirmed; the third word is seconds |
| PD profile is 16 bytes, a class byte and 7 or 9 groups; `E4` is index + 1 | Confirmed; the 16 bytes are the name, the class is the wattage |
| `EA` 20 payload bytes, `EC` 30, `DE` 68 | Confirmed |
| `20` is a block write replying `20`; `FE` not a bootloader entry | Confirmed for `20`; `FE AA 55` is corrected to factory reset plus reboot |


## Host-link comparison

Full source: [hostlink analysis](notes/hostlink.md).


Statements are grouped by source file. C = confirmed, X = corrected, N = new.

### protocol.md 1.1 to 2.2 (framing)

- 1.1 "USB VID 0x28E9, PID 0x028A, report ID 1 OUT / report ID 2 IN,
  63 data bytes, 62/61-byte chunking": **C** (CH58x descriptors and
  `0x3E1A` 62-byte queue; the 61-byte figure is WebLink host-side).
- 1.1 "WebLink de-stuffs `AA AA -> AA`; firmware doubles `AA` throughout
  the framed body, single leading delimiter": **C** (encoder `0x1FEDC`,
  emu round-trip).
- 2.1 "TX `[cnt] AA 12 plen cmd ... cksum`, RX addr byte, opcode index
  4/1/0": **C** for the byte order. **N**: the `12`/`31` etc are
  `(source<<4)|dest` nibbles, not a fixed device address; the MCU-side
  address is computed by nibble swap.
- 2.1 "BLE AF01 replies carry address byte 0x31": **X (clarified)**. `0x31`
  is the CH58x AF01 route marker, appended by the CH58x on AF01 writes,
  echoed by type-6 handlers, and moved to the front by the CH58x reply
  router `0x3FAC`. It is not a bus address and the main MCU never emits it
  as a frame address.
- 2.2 "checksum = sum of addr, plen, cmd+payload; `AA` doubled; single
  leading `AA`; parser splits first body byte into nibbles, does not
  compare with 0x12": **C** (emu, disasm `0x1FF38`/`0x1FEDC`).

### firmware.md "Command dispatcher"

- "`0x2F34` watches four flag bytes, first set selects a record at
  `0x1FFF9660` stride 260, byte 0 type, byte 2 length, byte 4 opcode":
  **C** (the four flags are `0x1FFE01AC..AF`; addresses given here).
- "two call shapes; `0xBB/0xBD/0xBE` no reply buffer": **C** (disasm of the
  call sites).
- "type 6 appends one byte copied from the end of the request;
  `0xF2/0xF4/0xF6/0xFC/0x20` append constant `0x31`": **C**, and **N**: the
  appended byte is the CH58x route marker (`0x31` AF01 / `0x00` AF02),
  which is why the constant `0x31` is used where the reply always targets
  AF01.
- "type byte 6 is not a transport name; `0xBD` treats 5 and 6 as
  different": **C** and explained: type = source nibble; 6 = BLE host,
  5 = accessory link, 1 = USB, 3 = CH58x internal.

### firmware.md "Frame parser"

- "Outbound stuffing `0xFFF0`, inbound `0xFF38`, `AA` counter, state table
  branch, states 1-4 as described, checksum coverage": **C** (all
  re-derived by disasm and confirmed by emu round-trip and edge cases).
- **C (offsets, corrected during recovery)**: firmware.md is correct:
  main state is at `+0x208`, the fill index at `+0x20C`, and the `AA`
  counter at `+0x213`. The earlier independent note's proposed correction
  was rejected after instruction inspection and stepped execution.
- "`0xFF38` is a file offset; absolute `0x1FF38`": **C** (function at
  `0x1FF38`; the wrapper `0x146B8` tail-calls it).

### firmware.md "0x18 bind"

- "`0x18` inline `0x3126` sets `S+0x47`, stores type at `K+6`, no reply":
  **C** (absolute `0x13126`).
- "`0x19` built at `0x2690` from `0x3836`; byte1 = 0 if `S+0x46!=0` else
  `0xFF`; len 2 or 3 (type 6 appends 0)": **C** (absolute `0x12690`,
  emu-confirmed `19 00 00` / `19 FF 00`).
- "`0x1478C` sets `S+0x46=1`,`S+0x47=0`, bit 1 of `0x1FFF9448+0x108`;
  `0x1483C` clears both, sets same bit; which button calls which is open":
  **X**. These are **file offsets**: the real functions are `0x2478C`
  (Allow, sets `S+0x46=1`) and `0x2483C` (Deny, clears `S+0x46`), both
  setting bit 1 of `0x1FFF9550`. firmware.md's "`0x1483C`" should be
  `0x2483C` (= file offset `0x1483C`). The button binding is now resolved:
  `0x2840C` builds the confirm-bind dialog and registers `0x2478C` on child
  `0x1FFE06C0` (Allow) and `0x2483C` on `0x1FFE06C4` (Deny) via `0x21A50`.
- "after `0x2690` returns `0x3836` clears bit 1": **C**.
- **N**: bind timeout auto-dismisses the dialog and yields `19 FF`; the
  main MCU never stores host IDs (remembering is CH58x-only); USB `0x18` is
  answered the same way.

### firmware.md "Stream and list ingest" / "Connection state and list ingest"

- "`0xBD` `0x4660` type 6 stores request byte 1 at `S+3`, clears `K+2` and
  u16 at `K+0x12` when 0; type 5 stores byte 1 at `S+4`, copies `len-2`
  bytes to `S+0x58`": **C** (absolute `0x14660`). **N**: `S+3` is the host
  link state (`BD 01` up / `BD 00` down) and `S+0x58` is the accessory
  name.
- "`0xBE` `0x855C` selectors 0/1/2/4, wheel `K+0x2C`": **C** (absolute
  `0x1855C`); **N**: this is Bluetooth-accessory input (wheel + buttons)
  routed into the LVGL keypad reader; also injectable by a BLE host on
  AF01.
- "`0xBB` `0x5AA0` clears `0xC4` bytes at `0x1FFF9A70`, count, stride
  `0x26`, sum, sets `S+0x3D`": **C** (absolute `0x15AA0`); **N**: it is the
  "Bluetooth Accessories" scan-result list.

### firmware.md "0x51, 0x53, 0xF1 and 0xFD"

- "`0x51`/`0x53` type 3, payload 0, store 0 at `0x1FFF9448+0x103/0x104`,
  load 1000 at `0x1FFF9440`": **C**. **N**: they are the acks of the MCU's
  own `0x50`/`0x52` companion commands.
- "`0xF1` inline `0x30D8` type 3, requires `0x1FFFA00C+2 == 1`, stores 2":
  **C**; **N**: ack of `F0 AC` update-prepare.
- "`0xFD` inline `0x32C0`, payload 3 or `0xFF`; 3 sets `0x1FFF9449`, calls
  `0xAE70(1)`, ORs `0x2000` (bit 13, request the CH58x identity with `E0`); `0xFF` clears `0x1FFF9449` and bumps
  `0x1FFF943C`": **C** (absolute `0x132C0`); **N**: `FD` carries CH58x
  update progress. Note **N**: `FD 03` also arrives during boot from node 3
  and marks the companion initialised (`0x1FFF9449 = 1`); a `FD 03` from
  node 1 (USB) is accepted too (emu).

### firmware.md "0xE1 received"

- "`0x3C40` acts only when type is 3; if byte 8 of `0x1FFF942C` is 0 sets
  `K+0=1` and copies 4 bytes from record+0x11 to bytes 8..11, else to 0..3
  and 4..7; meaning not named": **C** (absolute `0x13C40`). **X/N**: the
  4 bytes are the **CH58x version/identity field** (`01 00 00 0f` on the
  emulated reply), copied to `0x1FFF9434..37` then
  `0x1FFF942C..33`, and shown by the sys-info UI `0x57D54`. It is not a BLE
  MAC (the MAC stays inside the CH58x).

### protocol.md 1.3 (bind table)

- "device shows allow/deny prompt every connection; reply on button press":
  **C** (prompt `0x2840C`, callbacks `0x2478C`/`0x2483C`).
- "`19 00` allowed, `19 FF` denied": **C** (emu).
- "device does not remember an allowed host with WebLink's frame":
  **C** in code: the main MCU stores nothing, and the CH58x only stores a
  host ID after a `19 00` with the frame's last byte zeroed (CH58x side);
  WebLink's frame path goes through the prompt, not the remember path.
- "after deny, `0xC4`/`0xC2`/`0xE0` still answered; binding does not protect
  reading": **C** (dispatcher has no bind gate; emu `test_dispatch` answers
  reads regardless of `S+0x46`).
- "how long the device waits before giving up, and what it replies":
  **answered (code)**: the popup auto-dismisses (tens of seconds) and the
  deferred `0x12690` then replies `19 FF`.
- "whether USB shows the prompt": **answered (code)**: USB `0x18` is
  dispatched and answered identically; the prompt UI would appear, but USB
  control is gated by the remote grant (granted without a prompt), not by
  bind.

### firmware-architecture.md "Framing and bridge routing"

- "decoded slot: source nibble, dest nibble, length, unused, opcode,
  payload; addr = (source<<4)|(dest&15); wire = AA addr len opcode payload
  cksum; AA doubled incl addr/len/cksum; leading AA single; addr 0xAA
  cannot be received; zero length fails; checksum change rejected":
  **C** (all re-derived independently by disasm + emu here).
- "type-6 suffix is an internal bridge route byte, AF01=31 AF02=00,
  removed before notification; update handlers use fixed 31": **C**
  (CH58x `0x4074`/`0x3FAC`, and MCU type-6 append; emu both sides).
- encoder `0x15430`, body `0x1FEDC`, stuffing `0x1FFF0`, decoder wrapper
  `0x146B8`: **C** (all confirmed).

### hardware-buses.md "Main processor UARTs"

- "`0x4001CC00` init `0x644A4` 115200, RX `0x1EF0C` decoder ch0 parser
  `0x11900`, P3.9/P3.8 mux 0x20/0x21 -> PD companion": **C**.
- "`0x4001D400` init `0x1787C` 115200, RX `0x1EF5C` decoder ch1, P2.0/P2.1
  mux 0x20/0x21 -> BLE/USB bridge, four mailboxes stride 260 at
  `0x1FFF9660`, sources 6/1/5/3": **C** (this is the hostlink UART).
- "`0x40021000` 1000000 baud, RX `0x1F048` text-line buffer, CR terminator,
  buffer `0x1FFF8A8C` 512 bytes, status/len/cursor `0x1FFE0148/14A/14C`,
  console/factory": **C**, and **N**: full command set documented (section
  1); consumed by `0x1227C` in Time_task; not reachable from the host link.
- "source 3 opcode `0x55` handshake path and opcode `0x11` reaches
  `0x13C88`": **C** (`0x55` ack in `0x133BC`; `0x11` -> `0x13C88` time
  sync in the RX callback fast path).
- "DMA base `0x40053400` channels 0/1; selectors `0x12C/D/F` and
  `0x14C/D/F`; NVIC priority arg 15": **C**.
- **N**: RX is per-byte interrupt (RI), DMA is transmit only.

### firmware-permissions.md / firmware.md remote-control

- "bind decision `S+0x46` and remote grant `S+0x42` are separate; decline
  callback clears `S+0x46`/`S+0x47` but not `S+0x42`": **C**.
- "reads answered after denial": **C**.
- "C8 remoteCon 2 grants immediately for connection type 2, pends for type
  1/0": **C** and refined: **type 2 = USB** (grants at once, no prompt);
  **type 1 = Bluetooth host** (pends for the Allow dialog); type 0 = no
  link (dropped). emu-confirmed.
- **N (answers TBD-005/TBD-012)**: on link drop `S+3 -> 0`, the UI pass
  `0x1E284` clears the remote grant `S+0x42`; the output enable
  `0x1FFFAA2E` is not touched, so the output stays on. There is a keepalive
  (`0x55`) and a retransmit-then-give-up watchdog (about 50 tries / 5 s)
  plus an 8 s USB-silence timeout that clear `S+3`.

### New, not in docs/research

- The complete `0x1FFF9550` work-mask bit map (section 6).
- The node numbering (1/2/3/5/6) and its exact meaning per source.
- The internal MCU<->CH58x message table with `E0/FC/50/52/10/F0/55`
  outbound and `55/51/53/F1/FD/E1/11/BD/BB/BE` inbound, all emu-verified.
- The USART7 console command set and that it can switch the output on with
  no bind/grant.
- The `E1`-received 4 bytes identified as the CH58x version field.
- The transmit service `0x133BC` as the single point that serialises all
  outbound frames, with one outstanding frame gated by `K+0`.


## CH58x comparison

Full source: [ch58x analysis](notes/ch58x.md).


### protocol.md 1.1 USB HID

| Statement | Result |
|---|---|
| VID `0x28E9`, PID `0x028A`, bcdDevice 2.00, string indexes 1, 2, 3 | Confirmed [A]. New: index 3 (serial) is not served; the request stalls |
| Strings `wch.cn` and `MP305B` | Confirmed. New: the product string is RAM and is replaced by the 8-byte name from DataFlash `0x6E0E` (cut at the first space) when USB is enabled |
| WebLink filters on usagePage 1, usage 4 | The descriptor's top-level usage is 0 (`09 00`). With this image the WebLink filter would not match. Needs a USB check (TBD-013) |
| WebLink checks the product name contains MP305B/MP305A/MP3010B | Consistent; the name comes from the MCU's `FC` (MP305B on 1.6.0.51) |
| EP1 OUT/IN interrupt 64 bytes 1 ms, HID 1.11, report descriptor 35 bytes, 100 mA | Confirmed [A]. New: attributes `0xC0` (self powered) |
| Report ID 1 OUT 63 bytes, report ID 2 IN 63 bytes | Confirmed [A] |
| Outgoing chunking, stride 61, first report `[60, F[1..60]]` | Compatible, not required: the firmware accepts any count 1..62 per report and does not check the report ID |
| Frames of 63 bytes or fewer in one report | Corrected detail: at most 62 stream bytes fit in one report after the count byte |
| 5 ms delay after each report | Not needed by the CH58x (it reassembles across reports); but a new frame must not start before the previous one was forwarded (about 1.25 ms), and frames must not share a report [E] |
| Firmware doubles `0xAA` in the framed body; de-stuff in pairs | Confirmed for USB IN [E]. New: the CH58x also de-stuffs and checks the checksum of OUT frames, then re-encodes them; bad frames are dropped silently |
| Multi-report replies arrive with a leading chunk count byte | Corrected: the byte after the report ID is the number of valid stream bytes in that report (1..62), in every report |
| WebLink does not verify checksum or address | WebLink behaviour; the CH58x has already verified the checksum of every IN frame it forwards |
| A USB connection has not been observed | Still true; all USB statements here are [D]/[E] |

### protocol.md 1.2 Bluetooth LE

| Statement | Result |
|---|---|
| Local name prefix `0000MP30` | Confirmed and explained: template `0030MP305B`, index 2 patched to `'0'` every second unless RAM `0x200043B7 == 0xA5` (no writer setting it to `0xA5` was identified) |
| WebLink trims the first four characters | WebLink behaviour; the four characters are constant `0000` |
| Service UUID `AF00` in the advert | Confirmed: incomplete 16-bit UUID list `03 02 00 AF` |
| Manufacturer data company `0xABBA`, prefix `affa0135` | Confirmed. New: `AF FA` fixed; `01 35 02 00` set by the MCU's `FC`; last 14 bytes set by AF01 `10`/`C0` and persistent |
| AF01 read, write, notify: commands and telemetry | Confirmed properties `0x1A`. New: reads return 20 zero bytes; first byte of every write is discarded |
| AF02 read, write, notify: bind and hardware info | Confirmed properties. Corrected: `E0` on AF02 is forwarded to the main MCU like any other opcode; AF02 has two local opcodes: `00` (link status and BD address) and `18` with fast flag |
| `FEE0`/`FEE1` bootloader OTA service only | Consistent: not present in this application image |
| GATT table: 180A 2A23..2A2A and 2A50, AF00, DB00/DB01 | Confirmed [D]; handle spacing in the capture fits the registration order 180A, AF00, DB00 |
| DB00 purpose unknown | New: DB01 does nothing (empty hooks, never notifies) |
| 180A holds vendor placeholders | Confirmed: exact values listed above |
| Negotiated MTU 247 on macOS | Consistent: 247 is the maximum this configuration allows (BufMaxLen 251) |
| Device not seen while connected (inferred) | Confirmed in code: one host link, advertising re-enabled only on disconnect, a second central is dropped |
| Advertisements several seconds apart; scan at least 10 s | Advertising interval is 500 ms [D]; advertising is off until the MCU enables it after boot, while a host is connected, while a USB host is active, and when remote is disabled. The long gaps seen on macOS are not explained by the interval [I: scanner duty cycle] |
| Notifications must be enabled on AF01 and AF02 before commands | Confirmed in effect: a reply to a characteristic whose CCCD is off is dropped and the MCU retransmits it for about 5 s. CCCDs reset on every disconnect |
| BLE frames unpadded, un-stuffed, no length or checksum | Confirmed: the CH58x adds and removes the UART framing |
| Single writes/notifications without chunking | Confirmed: no fragmentation in either direction |
| MTU >= 126 needed for full-size frames | Not a CH58x limit; the need follows from the longest MCU reply plus 3 (plus 1 on AF01) |
| Replies on AF01 carry the address byte `0x31` | Corrected: `0x31` is the route tag the CH58x appended to the request and moves to the front; it is constant, not an address |
| Writes with response work on AF01 and AF02 | Consistent; write-without-response is not declared |
| Round trip 120 to 135 ms | The CH58x adds about 1.25 ms per direction plus UART time (a 41-byte frame takes 3.6 ms at 115200) [I]; most of the time is elsewhere |

### protocol.md 1.3 Bind handshake

| Statement | Result |
|---|---|
| WebLink writes the bind frame to AF02 after enabling notifications | Consistent |
| Field boundaries (class byte, 16-byte ID, fastBinding, status) inferred | Corrected by firmware: the CH58x takes bytes 1..16 as the ID and the last byte of the write as the fast flag; other bytes are ignored. In WebLink's frame the ID is `00 08*14 00` and the fast flag is 0 |
| Prompt at every connection; reply after a button press | Consistent: fast flag 0 always forwards to the MCU |
| `19 00` allowed, `19 FF` denied | Confirmed; the fast path produces the same two replies |
| Device does not remember an allowed host with the WebLink frame | Explained: after `19 00` the ID is stored, but with fast flag 0 the stored IDs are never consulted |
| After a deny, reads are still answered | Consistent: the CH58x forwards all writes regardless of bind state. New: an unbound link is terminated about 30 s after connecting |
| Whether fastBinding = 1 lets the device remember a host | Firmware: yes, if the same 16 bytes were allowed once before (up to 5 IDs); an unknown ID with fast flag set gets `19 FF` without a prompt |
| Whether USB shows the prompt | The CH58x has no bind logic for USB; any USB behaviour is the MCU's |
| How long the device waits for a button press | CH58x side: the link is dropped 30 s after connection unless bound; the MCU's own prompt timeout is not in this image |

### protocol.md 2 Frame encoding

| Statement | Result |
|---|---|
| HID TX `[cnt] AA 12 plen cmd payload cksum` | Confirmed (report ID 1 precedes cnt on the wire) |
| HID RX `[cnt] AA addr plen cmd payload cksum` | Confirmed; addr is `0x21` [M] |
| BLE AF01 TX `12 cmd payload` | Confirmed; the `12` is discarded, any value works |
| BLE AF01 RX `addr cmd payload` | Corrected: the first byte is the route tag `31` |
| BLE AF02 TX/RX without address | Confirmed |
| Checksum 8-bit additive; stuffing on HID only | Confirmed |
| Checksum = sum of bytes 2..N-1 | Confirmed (address + length + data) [E] |
| If the checksum equals `0xAA` another `0xAA` is appended | Confirmed [A: `0x35A8`] |
| Target address `0x12` is the device address | Corrected: `0x12` means source 1 (USB), destination 2 (MCU); the MCU replies to the source nibble |

### protocol.md 3 and 4 (related entries)

| Statement | Result |
|---|---|
| `0xBD` "RealTime_DATA": connection state and peer metadata | Confirmed and explained: `BD 00`/`BD 01` from the CH58x on channel 6 (bind state); `BD k name` on channel 5 (accessory) |
| E0 type 6: 17 bytes, final byte is the route suffix removed before notification | Confirmed [E]: `e1 ... 00` on AF02, `31 e1 ...` on AF01 |
| Which chip each `E1` version belongs to is inferred | Resolved: both host-visible versions come from the main image (application 1.6.0.x, hardware 2.0.2.0). The CH58x version is 1.0.0.15 and is only reported to the MCU |
| No release on disconnect; what happens is unknown | New: after a bound host disconnects the CH58x sends `BD 00`; the MCU sets connection type 0 (and clears state per firmware.md). An unbound host disconnecting produces no message |

### firmware.md "USB device" and firmware-architecture.md USB/GATT/binding

| Statement | Result |
|---|---|
| Report descriptor at `data.bin + 0x12F4C`, configuration `+0x12F70`, device `+0x12F9C` | Confirmed (processor `0x8F4C`, `0x8F70`, `0x8F9C`) |
| Device and configuration fields | Confirmed |
| Report descriptor content | Confirmed; exact bytes given above |
| Queue service `0x3E1A` limits chunks to 62; `0x4ECA` sends report ID 2, count, bytes | Confirmed [E] |
| Receive `0x4E86` takes the count from byte 1 and feeds from byte 2 | Confirmed [E]; the count is not bounded |
| AF/DB characteristics properties `0x1A`, handles assigned at runtime | Confirmed |
| Initialized name `0030MP305B`, prefix rewrite unresolved | Resolved (see 1.2) |
| AF02 write `0x40DC`, AF01 write `0x4224`, forwarder `0x4074` appends `31`/`00`, router `0x3FAC` | Confirmed [E]. Addition: the AF01 first byte is dropped in the callback `0x72A6`, before `0x4224` |
| Nonzero final byte selects a lookup; reply `19 00`/`19 FF` | Confirmed [E] |
| Save only when guard `0x20002F88` is zero | Confirmed; the guard is "last notification failed" |
| Five 16-byte IDs at `0x6F00`, oldest shifted out | Confirmed [E] |

### firmware.md "Companion image strings"

| Statement | Result |
|---|---|
| `CH58x_BLE_LIB_V1.8` at slice offset `0x7E68` | Confirmed (processor `0x8E68`); the image refuses to run with another library version |
| `0030MP305B` at slice offset `0x8572` | Confirmed (`.data` source of `0x20002E9A`); it is a template, rewritten at run time |
| Load address `0x1000` | Confirmed |

### firmware.md other sections that describe the CH58x's messages

| Statement | Result |
|---|---|
| `0x51`, `0x53`, `0xF1` act only for type 3 and request byte 1 = 0 | Consistent: the CH58x replies `51 00`, `53 00`, `F1 00` |
| `0xFD` with byte 3 or `0xFF` | This CH58x only ever sends `FD 03` |
| `0xE1` received (type 3) copies four bytes from offset `0x11` | Confirmed: they are the CH58x version `01 00 00 0F` |
| `0xBB` records of stride `0x26` (6 + tail) | Consistent with `BB` list: 6-byte address, length, name up to 31 |
| `0xBE`: byte 1 = 1, 2, 4; byte at length-2 = 1 or `0xFF` | Confirmed: button bits and wheel byte of an accessory report (9-byte frame, wheel at offset 7) |

### Captures

All four captures (`2026-09-29T193614`, `194219`, `194319`, `201428`)
re-decoded with the firmware model:

| Item | Decoding | Agrees |
|---|---|---|
| Name `0000MP305B  S             E!K` | `0000` + FC name `MP305B` + two FC padding spaces + `S` (remote enabled, BLE not blocked) + template spaces + BD-address suffix `E!K` (v mod 94 = 36, (v/94) mod 94 = 0, (v/8836) mod 94 = 42) | Yes. The spaces at 10..11 prove the DataFlash name override was present |
| Manufacturer data `affa0135 02 00` + 14 zero bytes (LOGBOOK) | fixed `AF FA`, MCU `FC` bytes `01 35 02 00`, empty host tail | Yes |
| GATT handles 15..31, 34, 37, 41 | 180A, AF00 (3 attributes per characteristic), DB00 | Yes |
| MTU 247 | library maximum for BufMaxLen 251 | Yes |
| AF02 TX `18 00 08*14 00 00 00` | ID `00 08*14 00`, fast flag 0: forwarded as `AA 62 14 18 ... 00 FE`, prompt | Yes |
| AF02 RX `19 00` (3.0 to 7.7 s later) | MCU reply `19 00 00`, tag stripped; ID saved to `0x6F00`; `BD 01` to MCU; MCU then detaches USB (`50 01`) | Yes |
| AF02 RX `19 ff` (194319) | deny; nothing saved; bind state stays 0, so the link would be dropped 30 s after connecting; the capture ends before that | Yes |
| AF02 TX `e0`, RX `e1 01 06 00 28 ... 02 00 02 00` (17 bytes) | forwarded with tag `00`; MCU type-6 layout; tag stripped | Yes |
| AF01 TX `12 c4`, RX `31 c5 5a 02 00 00 01 f4 01 32 00 00 00` | `12` dropped, `c4 31` forwarded; reply routed by tag `31` | Yes |
| AF01 TX `12 c2`, RX 38 bytes starting `31 c3` | same path; 37 bytes from the MCU plus the tag | Yes |
| AF01 TX `12 e0`, RX `31 e1 ...` (18 bytes) | same path | Yes |
| Reads answered after deny | CH58x forwards regardless of bind | Yes |

