# Firmware reconstruction, image 1.6.0.51

Reconstructed from the published MP305B firmware image dated in ISDT's
update manifest as 1.6.0.51. The image files are not in this repository.
They are kept at `~/.local/share/mp305b/fw/` (`MP305B-V51.fwd`,
`MP305B-V51.plain.bin`, `app.bin`, `data.bin`). This note is the
interoperability information read out of them. The author's unit was still
reporting application version 1.6.0.40 after the update attempt (LOGBOOK
2026-09-29, "Hardware: read-only spike after the firmware update"), so these
facts are about image 1.6.0.51.

Evidence label for everything in this file: confirmed in code, read from
that image, unless a sentence says otherwise. Offline execution checks
selected functions in synthetic memory; it is not hardware confirmation.

Merged and corrected on 2026-09-30 using both scratchpads. See the
[verification and correction ledger](firmware/verification.md),
[architecture and bridge details](firmware/architecture.md),
[hardware reconstruction](device/hardware.md),
[RTOS scheduling and resources](firmware/rtos.md),
[binding and command permissions](firmware/permissions.md), and
[complete research export index](firmware/v51/canonical/README.md).

**Address convention:** handler addresses in this document are `app.bin`
file offsets unless explicitly called processor addresses. Add `0x10000`
to find the corresponding main function in the exports. RAM addresses are
absolute. The architecture document and generated function indexes use
processor addresses. Payload offset zero follows the opcode; request and
reply offset zero include the opcode.

## Image container

The published file is `MP305B-V51.fwd`, 555680 bytes. WebLink's loader reads
a 32-byte header of little-endian words:

| Word | Value in this file | Meaning |
|---|---|---|
| 0 | `0x15F7E6F5` | Running key |
| 1 | `0x7689FFE3` | Checksum of the restored body |
| 2 | `0x00010000` | Application storage offset |
| 3 | `0x00000000` | Data storage offset |
| 4 | 476160 | Application size |
| 5 | 79488 | Data size |
| 6 | 115200 | Original baud rate |
| 7 | 115200 | Rapid baud rate |

The body is a sequence of little-endian words. Each word is XORed with a
running value that starts as the checksum word. After each word that running
value is replaced by `(running + key) XOR key`. The sum of the restored
words equals the checksum word. The restored body is 555648 bytes:
`app.bin` (476160) followed by `data.bin` (79488).

Inside the application, four candidate words at offset 28, 32, 36 and 40
are turned into an address by subtracting the application storage offset.
The one that lands inside the application and holds `0xAA55CC33` is the
identity block. In this image that block is at application offset
`0x6AFC8`:

| Offset | Bytes | Meaning |
|---|---|---|
| `0x6AFC8` | `0xAA55CC33` | Identity magic. The plain image stored beside the `.fwd` has these four bytes set to `0xFF`, which is what WebLink writes after it has accepted the file |
| `0x6AFCC` | `MP305B` and two zero bytes | Device id, 8 bytes |
| `0x6AFD4` | `02 00 02 00` | Hardware revision 2.0.2.0 |
| `0x6AFD8` | `01 06 00 33` | Application version 1.6.0.51 |

## Three programs

`app.bin` is a Cortex-M Thumb image linked at `0x10000`, the container's
application storage offset. The reset vector word is `0x00010359`. Clearing
the Thumb bit and subtracting `0x10000` lands at file offset `0x358`, which
is the reset stub: it writes `0x1FF` to `0x40050810`, branches through
`0x0001DB75`, then enters the startup at `0x00010281`. With that base, the
vector words at file offsets `0x08` through `0x18` are branches to self.
Read as file offsets from a base of 0, those same words land in the middle
of a floating-point routine. `SystemInit` at absolute `0x1DB74` writes
`0x10000` to `VTOR` (`0xE000ED08`) at `0x1DB8C`, confirmed by instructions
and offline execution. The 64 KB below `0x10000` is not in this file.

| Item | Value |
|---|---|
| Initial stack pointer | `0x2003F618` |
| Link address | `0x10000` |
| Reset vector | `0x00010359` (Thumb), file offset `0x358` |
| Live power-supply state | `0x1FFFAACC` |

Task names in the image include `lvgl_task`, `User_task`, `Time_task` and
`Power_task`. The command dispatcher below is in this image.

`data.bin` contains two distinct programs. Both are linked at processor
address `0x1000` in separate processors:

| Slice in `data.bin` | Architecture | Role | Entry |
|---|---|---|---|
| `0` through `0xA9FF`, padded through `0xAFFF` | 8051 | PD and power companion, role inferred from code and messages | `LJMP 0xAF88`, file offset `0x9F88` |
| `0xB000` through `0x1367F` | RV32 with compressed instructions | BLE and USB companion | `0x1000` jumps to `0x1C48` |

The 8051 jump does not target the padding. Its absolute code address must
be converted using the `0x1000` load address. The BLE image references a
WCH library at `0x40000`, absent from this update. See the architecture
note for startup, initialized RAM, tasks, GATT tables and library provenance.

## USB device, in the companion image

The report descriptor is at `data.bin + 0x12F4C`, the configuration at
`+0x12F70`, and the device descriptor at `+0x12F9C`.

Device descriptor:

| Field | Value |
|---|---|
| bcdUSB | 2.00 |
| Class | 0 (defined at the interface) |
| Max packet size 0 | 64 |
| Vendor ID | `0x28E9` |
| Product ID | `0x028A` |
| bcdDevice | 2.00 |
| Strings | indexes 1, 2 and 3. The image contains `wch.cn` and `MP305B` |
| Configurations | 1 |

Configuration descriptor, total length 41 bytes, one interface, attributes
`0xC0`, max power 100 mA. Interface 0 is HID (class 3), two endpoints,
bcdHID 1.11, one report descriptor of 35 bytes.

| Endpoint | Direction | Type | Packet | Interval |
|---|---|---|---|---|
| `0x01` | OUT | Interrupt | 64 | 1 ms |
| `0x81` | IN | Interrupt | 64 | 1 ms |

The 35-byte report descriptor is:

- Usage page Generic Desktop, usage 0, application collection.
- Report ID 1, 63 bytes, output (host to device).
- Report ID 2, 63 bytes, input (device to host).

String descriptors in the same image: `wch.cn` and `MP305B`.

A USB connection has not been observed on the author's unit (TBD-013). The
descriptor bytes themselves are what this image contains.

## Command dispatcher

Function at `app.bin` `0x2F34`. It watches four flag bytes. The first one
that is set selects a channel record in a table at `0x1FFF9660`, stride 260
bytes. Byte 0 of that record is the type byte. Byte 2 is the length the
handlers index with. Byte 4 is the opcode. A request the switch does not
recognise falls through without a reply.

Most handlers that build a reply write `opcode + 1` as the first reply byte,
either by adding 1 or by storing a constant that equals that sum. Opcode
`0x20` stores `0x20` instead. When the type byte is 6, those handlers append
one extra byte and return a length one greater. The builders copy that byte
from the end of the request. The `0xF2`, `0xF4`, `0xF6`, `0xFC` and `0x20`
handlers append the constant `0x31`. Type 6 is not, by itself, a transport
name: `0xBD` treats type 5 and type 6 as different requests.

Two call shapes, from the instructions in front of each `bl`:

- `mov r3, r2` / `mov r2, r1` / `mov r1, ip`: the handler sees (request,
  length, reply, type). Used for `0xA2`, `0xC2`, `0xC4`, `0xC6`, `0xC8`,
  `0xD0`, `0xD2`, `0xD4`, `0xD6`, `0xDA`, `0xDC`, `0xDE`, `0xE1`, `0xE2`,
  `0xE4`, `0xE8`, `0xEA`, `0xEC` and `0xEE`.
- `mov r3, ip` and no shuffle: the handler sees (request, reply, type,
  length). Used for `0x00`, `0x20`, `0xE0`, `0xF0`, `0xF2`, `0xF4`, `0xF6`,
  `0xFC` and `0xFE`.

`0xBB`, `0xBD` and `0xBE` are called with the length in `r1` and no reply
buffer. The request pointer they all share has the opcode at byte 0, so
payload byte N is request byte N+1.

The bodies below were decompiled from this image. The dispatcher calls, the
`0xC6` stores, the bind stores, the `0x51`/`0x53` store of 1000, the `0xD8`
scan start, the `0xAA` parser and `0xDBE8` were checked against a Thumb
disassembly of the same bytes. `0xE2` and `0xE8` each have a block the
decompiler dropped, and their output branches are that reading.

### Opcodes with their own compare

| Opcode | Handler | What the handler does |
|---|---|---|
| `0x00` | `0xDFFC` | Fixed reply `01 91 67 01` |
| `0x18` | inline `0x3126` | Sets `S+0x47` and stores the type byte. No reply in this function |
| `0x20` | `0x16A8` | Block write. Reply opcode is `0x20` |
| `0x51` | inline `0x312E` | Type 3 and payload 0: clear a flag, store 1000. No reply |
| `0x53` | inline `0x313C` | Same shape as `0x51`, the other flag |
| `0xA0` | inline `0x307E` | Language read, reply built in the frame |
| `0xA2` | `0x8368` | Language write |
| `0xBB` | `0x5AA0` | List ingest, no reply |
| `0xBD` | `0x4660` | Connection state and peer metadata, no reply |
| `0xBE` | `0x855C` | Connection/selection flags, no reply |
| `0xC2` | `0x58BC` | DC telemetry, below |
| `0xC4` | `0x5EF8` | Settings read, below |
| `0xC6` | `0xCAA4` | Settings write, below |
| `0xC8` | `0xB7F4` | DC control, below |
| `0xD0` | `0x5BEC` | PD profile read |
| `0xD2` | `0xC628` | PD profile write |
| `0xD4` | `0x5E48` | Program list read |
| `0xD6` | `0xC8B8` | Program header write or delete |
| `0xD8` | inline `0x31F0` | Select a program id; deferred `D9` chunks, described below |
| `0xDA` | `0xC73C` | Program step write |

### Opcodes `0xDC` to `0xFE`

A table branch at `0x304E` covers `0xDC` through `0xFE`. Response opcodes
in that range (`0xDD`, `0xDF`, `0xE3`, `0xE5`, `0xE7`, `0xE9`, `0xEB`,
`0xED`, `0xEF`, `0xF3`, `0xF5`, `0xF7`, `0xF9`, `0xFB`) go to the no-reply
path. The ones that call a handler:

| Opcode | Next call |
|---|---|
| `0xDC` | `0x565C` | Selected program, two payload bytes |
| `0xDE` | `0x5694` | Prog/PD live telemetry, 69 bytes |
| `0xE0` | `0xB634` | Device info, two layouts, below |
| `0xE1` | `0x3C40` | Acts only when the type byte is 3. No reply |
| `0xE2` | `0xB4D0` | Program run control |
| `0xE4` | `0x5630` | Active PD index, one byte |
| `0xE8` | `0xD520` | PD connect |
| `0xEA` | `0x54AC` | Charge settings, 21 bytes |
| `0xEC` | `0x555C` | Charge telemetry, 31 bytes |
| `0xEE` | `0x3D44` | Charge control |
| `0xF0` | `0xB7C4` | Replies `F1 00` only when payload byte 0 is `0xAC` |
| `0xF1` | inline `0x30D8` | Type 3 and payload 0. No reply |
| `0xF2` | `0x5118` | Reply `F3 00` plus a status byte |
| `0xF4` | `0xF508` | Reply `F5 00`, four echoed bytes, a status |
| `0xF6` | `0xF250` | Reply `F7 00` plus a status byte |
| `0xFC` | `0x2400` | Log slot, only when payload byte 0 is `0xCA` |
| `0xFD` | inline `0x32C0` | Payload byte 0 must be 3 or `0xFF`. No reply |
| `0xFE` | `0xDB94` | Reply `FF AA 55` or `FF 00 00` |

`0xE6` and every response opcode in this range (`0xDD`, `0xDF`, `0xE3`,
`0xE5`, `0xE7`, `0xE9`, `0xEB`, `0xED`, `0xEF`, `0xF3`, `0xF5`, `0xF7`,
`0xF8` to `0xFB`, `0xFF`) take the no-reply path. WebLink's opcode matrix
does not name `0x00`, `0x20`, `0x51`, `0x53`, `0xA0`, `0xBB`, `0xBE`, or the
`0xF0` to `0xFE` commands. They are in this image.

## `0xC2` reply, handler `0x58BC`

The reply buffer starts with the response opcode. Payload offsets below
match protocol.md 4.1. The handler always writes every byte through payload
offset 35, and returns 37 (opcode plus 36 payload bytes). Over Bluetooth
that is the 38-byte frame that includes the address byte.

State base `S` is `0x1FFFAACC`.

| Payload offset | Width | Copied from |
|---|---|---|
| 0 | u8 | `S+2` |
| 1 | u8 | `S+14` |
| 2 | u8 | `S+58` |
| 3 | u16 | `S+172` |
| 5 | u16 | `S+168` |
| 7 | u16 | `S+174` |
| 9 | u16 | `S+170` |
| 11 | u32 | `S+208` |
| 15 | u32 | `S+212` |
| 19 | u16 | `S+176` |
| 21 | u8 | `S+18` |
| 22 | u8 | `S+24` |
| 23 | u8 | `S+16` |
| 24 | u8 | `S+5` |
| 25 | u8 | `S+48` |
| 26 | u8 | `S+55` |
| 27 | u8 | `S+56` |
| 28 | u8 | `S+57` |
| 29 | u16 | `S+158` |
| 31 | u8 | 1 if a global word is 0, otherwise `S+17` |
| 32 | u32 | offset 76 of a second global |

Multi-byte fields are stored little-endian. The scale of each field (10 mV,
1 mA, and the rest) is not in this copy loop. The `0xC8` limits below are
what tie the voltage and current units to 10 mV and 1 mA.

## `0xC4` reply, handler `0x5EF8`

Returns 12: the response opcode plus 11 payload bytes, which is the
13-byte Bluetooth frame including the address byte. `usbLine` is always
present.

| Payload offset | Width | Copied from | protocol.md 4.3 name |
|---|---|---|---|
| 0 | u8 | `S+45` | `perLimit` |
| 1 | u8 | `S+50` | `volume` |
| 2 | u8 | `S+46` | `screenOff` |
| 3 | u8 | `S+51` | `shutdown` |
| 4 | u8 | `S+47` | `screenDirection` |
| 5 | u16 | `S+150` | `slopeSteps` |
| 7 | u16 | `S+152` | `currentOver` (OCP delay) |
| 9 | u16 | `S+164` | `usbLine` |

## `0xC8` command, handler `0xB7F4`

`r5[0]` is the opcode, so payload byte N is `r5[N+1]`. The reply is the
response opcode, then one status byte. Status `0` is the path that applied
or accepted the command, status `1` is "remote not granted", status `0xFF`
is a rejected value. Return length 2, or 3 when the type byte is 6.

When the live mode byte at `S+48` is not 0, normal DC control is rejected
with status `0xFF`. The common epilogue still runs: for example, an existing
remote-request value of zero clears the grant. Rejection does not guarantee
that all state is unchanged.

Payload byte 0 is `remoteCon`:

- Above 2: status `0xFF`; the common epilogue still runs.
- 1, while `S+66` is not 1: status `1`, nothing applied.
- 1, while `S+66` is 1: the rest of the payload is checked and applied.
- 0: `S+66` is cleared.
- 2: if `S+3` is 2, both `S+66` and `S+69` are set to 1. Otherwise the
  handler returns length 0 and writes no status byte.

Applied fields on the `remoteCon = 1` path while mode is 0, remote
is already granted, and the requested mode equals the current mode.
A different requested mode takes a separate branch: with output off,
transfer state not 1, and target mode below 4, it stores `S+0x31` and
skips the other field checks. Writes are sequential. A valid voltage can
be stored before a later invalid current produces `0xFF`.

| Payload | Check | Stored at |
|---|---|---|
| 1, u16 voltage | Reject above 3050 (`0x0BEA`) | passed to `0xAF64` |
| 3, u16 current | Reject above 5100 (`0x13EC`) | passed to `0xAEA4` |
| 5, `realChange` | Reject above 3 | `S+24`, the byte `0xC3` payload offset 22 is copied from |
| 6, `voltageSlow` | Reject above 1 | `S+16`, the byte `0xC3` payload offset 23 is copied from |
| 7, `currentOver` | Reject above 1 | `S+18`, the byte `0xC3` payload offset 21 is copied from |
| 8, `output` | Reject above 1 | passed to `0xA128`, `0xA134`, `0xAEBC`, `0xCB8C` |
| 9, `model` | Reject above 3. A value different from the live mode calls `0xA128` | live mode is `S+48` |
| 10, `refresh` | Reject above 1. The value 1 calls `0xA5FC` | |

3050 steps of 10 mV is 30.50 V. 5100 steps of 1 mA is 5.100 A. The parser
in this image rejects a `0xC8` above those two numbers. What the output
hardware does at 30.50 V or 5.100 A is still TBD-003.

Bit 2 of the word at global `+264`, tested with `lsls #29` and `bmi`, makes
this handler skip the setpoint update and still build a reply.

## State blocks

Offsets below are hexadecimal. The `0xC2`, `0xC4` and `0xC8` tables earlier
in this file use decimal offsets of `S`: decimal 48 is `0x30`, decimal 66
is `0x42`, decimal 69 is `0x45`.

| Address | Used as |
|---|---|
| `0x1FFFAACC` | `S`, the live supply state. The dispatcher's `fp` |
| `0x1FFFA354` | Program table. Ten slots |
| `0x1FFFA138` | PD profile table |
| `0x1FFFA340` | PD class byte for each profile index |
| `0x1FFFA8C4` | Program working bytes |
| `0x1FFF8F7C` | Program step records, stride 12 |
| `0x1FFE0184` | Slot structure `K`. Pool `0x1FFE01AC` minus `0x28` |
| `0x1FFF9660` | Four channel records, stride 260 |
| `0x1FFFA0B8` | Language byte at `+0x16` |
| `0x1FFF9448` | Remote-control gate word at `+0x108` |
| `0x1FFE07E0` | Charge limit table, stride `0x16` |
| `0x1FFFA00C` | Flag and checksum block used by `0x20`, `0xF0` and `0xFC` |

## `0xE0` reply, handler `0xB634`

Reply byte 0 is the constant `0xE1`. The type byte selects one of two
layouts. Nothing in this function says which transport a type belongs to.

Type 6 returns 18 bytes:

| Reply offset | Bytes |
|---|---|
| 1 to 4 | `01 06 00 33`, application version 1.6.0.51 |
| 5 to 12 | `MP305B` and two zero bytes |
| 13 to 16 | `02 00 02 00`, hardware revision 2.0.2.0 |
| 17 | The last byte of the request |

Any other type returns 31 bytes:

| Reply offset | Bytes |
|---|---|
| 1 to 8 | `MP305B` and two zero bytes. This is the model name, not a serial number |
| 9 to 16 | Eight bytes from the pointer at absolute address `0x1C`, plus `0x0C` |
| 17 to 20 | `01 06 00 33` again |
| 21 to 28 | `MP305B` and two zero bytes again |
| 29 to 30 | Two zero bytes |

The handler loads the word at absolute address `0x1C` (`movs r0, #28`, then
`ldr r3, [r0]`) and copies eight bytes from that pointer plus `0x0C`.
Address `0x1C` is below this image. The application's own vector word at
file offset `0x1C` is `0x0007AFC8`, and adding `0x0C` gives `0x7AFD4`, which
at this link address is file offset `0x6AFD4` (hardware revision, then
version). The instruction does not read that vector word. The eight bytes
are not in `app.bin`.

WebLink's USB field names (serial, hardware, bootloader, application, name)
do not line up with either layout. The Bluetooth captures match the type 6
field order, with the running unit reporting `01 06 00 28` (1.6.0.40)
instead of this image's `01 06 00 33`.

## `0xC6` command, handler `0xCAA4`

Checked against the Thumb listing, not only the decompiler. Reply is the
response opcode plus one status byte: `0` if every check passed, `0xFF`
otherwise. Length 2, or 3 when the type byte is 6. The first failing check
sets `0xFF` and skips every later store. The handler does not read the
output byte.

| Payload | Check | Store |
|---|---|---|
| 0 `perLimit` | 80 to 100 inclusive | `S+0x2D` |
| 1 `volume` | 0 to 3 | `S+0x32` |
| 2 `screenOff` | 0 or 1 | `S+0x2E` |
| 3 `shutdown` | 0 to 30 inclusive | `S+0x33` |
| 4 `screenDirection` | 0 or 1, or the command is rejected | No store. `0xC4` still reads `S+0x2F` |
| 5, u16 `slopeSteps` | 0 to 1000 inclusive | `S+0x96` |
| 7, u16 OCP delay | 0 to 1000 inclusive | `S+0x98` |
| 9 | 0 or 1 | `S+0x35` |
| 10 | 0 or 1 | `S+0x36` |
| 11, u16 `usbLine` | 0 to 1000 inclusive | `S+0xA4`, and `S+0x48` is set to 1 |

Payload bytes 9 and 10 are not in the `0xC4` reply. The `usbLine` u16 that
`0xC4` returns at payload offset 9 is the u16 this write takes at payload
offset 11. WebLink describes the write as the `0xC4` fields followed by
`systemCheck` and `recover`, and it lists shutdown as 0, 5, 10, 15, 20 or
30, slope as 100 to 1000, and the OCP delay as 50 to 1000. Those are
findings on top of this image. This image accepts any byte in the ranges
above and stores payload bytes 9 and 10 as flags. Later tasks consume the
flags, so this handler alone cannot establish their full effects.

The settings worker at processor `0x128A4` consumes `S+0x48`. Unless
`S+0x36` is set, it rounds each of the following fields up to the first
table value greater than or equal to the stored value:

| Field | Supported values after normalization |
|---|---|
| Charge limit | 80, 85, 90, 95, 100 |
| Shutdown | 0, 5, 10, 15, 20, 30 |
| Slope | 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 |
| OCP delay | 50, 100, 200, 300, 500, 1000 |
| USB line | 0 through 1000 in steps of 100 |

These tables are in initialized RAM `0x1FFE0778` through `0x1FFE07B9`.
For example, limit 81 becomes 85, shutdown 1 becomes 5, and slope 0
becomes 100. A partial rejected write does not set the dirty flag, so it
is not equivalent to this successful deferred path. With `S+0x36` set,
the worker sets `S+0x51`; with `S+0x35` set, it sends UI event 7 to the
object at `0x1FFE0744`. Callback `0x5E6E0` then requests power state 5
when the prior state permits it. A complete self-test sequence and reset
effects remain open. Normalization has 82 original-instruction checks
with UI callees explicitly replaced by no-op returns.

## `0x18` bind, inline at `0x3126`

`S+0x47` is set to 1 (`fp` is `S`, and `r9` is the constant 1). The type
byte is stored at `K+6`. The function then takes the no-reply path. It does
not assemble a `0x19`.

The `0x19` reply is built at `0x2690`, which is called from `0x3836`. Reply
byte 0 is `0x19`. Reply byte 1 is 0 when `S+0x46` is not 0, and `0xFF` when
`S+0x46` is 0. Length 2. When the caller's `r1` is 6, a zero byte is
appended and the length is 3. The deny capture `0x19 0xFF` (LOGBOOK
2026-09-29) is the path where `S+0x46` is 0.

`0x1478C` sets `S+0x46` to 1 and `S+0x47` to 0, and sets bit 1 of the word
at `0x1FFF9448+0x108`. `0x1483C` sets both `S+0x46` and `S+0x47` to 0, and
sets that same bit. Which front-panel action calls which of those two is
still open. After `0x2690` returns, `0x3836` clears bit 1 of that word.

## Language, `0xA0` and `0xA2`

`0xA0` is inline at `0x307E`. It writes the reply into the frame at the
opcode position: response byte `0xA1`, then the byte at `0x1FFFA0B8+0x16`.
Length 2, or 3 when the type byte is 6, in which case the extra byte is
copied from the end of the request. WebLink does not name `0xA0`.

`0xA2`, handler `0x8368`, forces payload byte 0 to 0 when it is above 1.
The status byte is always 0. Length 2, or 3 when the type byte is 6. If the
byte differs from `0x1FFFA0B8+0x16`, it is stored there. When `S+0x30` is 3
the handler calls `0xD858`, otherwise `0xAEBC(0)`, then calls `0xD958`
and sets the first byte of `S` to 1.

## `0x00`, handler `0xDFFC`

The reply is the four bytes `01 91 67 01`. Length 4, or 5 when the type
byte is 6, copying the last request byte. `0x01` is `0x00 + 1`.

## Remote-control tail

`0xC8`, `0xE2`, `0xE8` and `0xEE` share one skeleton. Bit 2 of the byte at
`0x1FFF9448+0x108`, tested by shifting that byte left 29, skips the body and
still builds a reply. Payload byte 0 is `remoteCon` and must be below 3.
The live mode at `S+0x30` must be 0 for `0xC8`, 1 for `0xE2`, 2 for `0xE8`
and 3 for `0xEE`, or the status is `0xFF`.

- `remoteCon` 2 stores the value at `S+0x45`. If `S+3` is 2, both `S+0x45`
  and `S+0x42` are set to 1. If `S+3` is not 2, the handler returns length 0
  and writes no status.
- `remoteCon` 0 clears `S+0x42`.
- `remoteCon` 1 requires `S+0x42` already 1, or the status is 1 and nothing
  else is applied.

The `0xC8` field table above is the granted path for mode 0. The granted
paths for the other three are in their sections. `0xE2` and `0xE8` are the
two functions where the decompiler dropped a block.

## Program table

Ten slots. Ids are the bytes at program table `+0xAA`. A per-slot flag is
at `+0xA0`. The count is the byte at `+0xB5`. The selected index is the
byte at `+0xB4`. Each slot's 16-byte record sits at index times 16.

`0xD4`, handler `0x5E48`, reads the list. Reply byte 1 is the count. For
each id from 1 through that count it finds the slot whose id byte matches,
copies that slot's 16 bytes, then the flag byte. Variable length. A type
byte of 6 appends the last request byte.

`0xDC`, handler `0x565C`, reads the selected slot: payload byte 0 is the id
at the selected index, payload byte 1 is that slot's flag. Length 3, or 4
when the type byte is 6.

`0xD8`, inline at `0x31F0`, does not build a reply. `r3` is set to 0 at
`0x2FB0` and the path to this opcode does not write `r3` again, so the scan
starts at slot 0. It compares request byte 1 with the ten id bytes. On a
match it stores the slot index at `K+4` and sets `0x1FFFA8C4+6` to 1.
Otherwise it sets that byte to 0. It always copies the last request byte to
`K+5`.

The deferred reply is present in this image. Worker at processor `0x1D380`
reads `0x4B0` bytes from serial-storage offset `0x162000 + slot*0x1000`
into `0x1FFF8F7C`, then sets transmit bit 7 at `0x1FFF9550`. Service
`0x133BC` calls builder `0x15CA0`. It emits `D9`, the program ID, and up
to ten 12-byte records, using cursor `0x1FFE0187`. It advances that cursor
and appends the route suffix for type 6. Full chunks contain 122 bytes
before the route suffix. The service clears bit 7 when the cursor reaches
the slot's step count. Offline checks cover empty, partial, full and
multiple chunks, including a 100-record program. This corrects the earlier
claim that the image has no `D9` reply.

`0xD6`, handler `0xC8B8`, takes a slot id in payload byte 0 and requires 1
to 10. It finds that id or allocates a free slot, and increments the count
when it allocates. It copies 16 bytes into the slot and stores one flag
byte. Two further request bytes follow. When the second of those is 1 and
the count is not 0, the handler deletes: it decrements the count, clears
that slot's flag and id, and renumbers higher ids down by 1. Status `0` or
`0xFF`, length 2 or 3. After the call the dispatcher clears
`0x1FFFA8C4+8` and calls `0xAEBC(0)`.

`0xDA`, handler `0xC73C`, writes steps. Payload byte 0 is a slot id and must
be 1 to 9. The id is looked up in the ten id bytes. The handler then reads
up to ten steps of three little-endian words. The first word is rejected
above 30500 (`0x7724`). The second word must be at most 5100 (`0x13EC`),
except that a second word outside that range is accepted when the third
word is 0. When the second word is in range, the third word must be at
most 99990 (`0x18696`, the literal at `0xC8AC`). 5100 matches the 5.100 A ceiling
of `0xC8` in 1 mA steps. 30500 is ten times the 3050 ceiling, which is
30.500 V if a step is 1 mV and the DC field is 10 mV. That is a scale
reading of these two constants, not a hardware measurement. 99990 is the
duration limit in seconds: the program runner compares calibrated elapsed
seconds with that word. See the recovered [program-mode analysis](firmware/v51/independent/notes/commands.md#63-program-mode).
Accepted steps are stored at `0x1FFF8F7C` with stride 12.
Filling the step count returns length 0. A rejected value sets status
`0xFF` and writes 2 at `S+0x4B`. The dispatcher then writes 1 at `S+0x4B`
after the call returns, so the value left there is 1. Reply length 2, or 3
when the type byte is 6, on the paths that do return a status.

`0xDE`, handler `0x5694`, always writes reply bytes through index `0x44`
and returns `0x45`, or `0x46` when the type byte is 6. Payload offsets:

| Payload | Width | Source |
|---|---|---|
| 0 | u8 | `S+0x02` |
| 1 | u8 | `S+0x0E` |
| 2 | u8 | `S+0x3A` |
| 3 | u16 | `S+0xAC` |
| 5 | u16 | `S+0xAE` |
| 7 | u32 | If `S+0x30` is 1, the u16 at `S+0xC8` with the high half zero. Otherwise the u32 at `S+0xD0` |
| 11 | u32 | `S+0xD4` |
| 15 | u16 | `S+0xB0` |
| 17 | u8 | The signed short at `S+0x7C`: 1 when negative, otherwise the value plus 1 |
| 18 | u8 | `S+0x05` |
| 19 | u8 | `S+0x30` |
| 20 | u8 | `S+0x39` |
| 21 | u8 | `S+0x20` |
| 22 | u32 | The signed word at `S+0xB8`, or four zero bytes when it is negative |
| 26 | u8 | `S+0x1F` |
| 27 | u8 | `S+0x1E0` |
| 28 | u8 | `S+0x1E2` |
| 29 | u16 | `S+0x1E4` |
| 31 | u8 | `S+0x1E8` |
| 32 | u8 | `S+0x1E6` |
| 33 | u8 | `S+0x1EA` |
| 34 | u8 | `S+0x1EC` |
| 35 | u8 | `S+0x1F0` |
| 36 | u8 | `S+0x1EE` |
| 37 | u8 | byte `+0x5A` of `0x1FFF9B34` |
| 38 | u32 | `+0x08` of that block |
| 42 | u32 | `+0x0C` |
| 46 | u32 | `+0x10` |
| 50 | u32 | `+0x14` |
| 54 | u32 | `+0x18` |
| 58 | u32 | `+0x1C` |
| 62 | u16 | `S+0x9E` |
| 64 | u32 | `+0x4C` of `0x1FFFA934` |

`0xE2`, handler `0xB4D0`, controls programs in live mode 1. Payload
layout: offset 0 remote selector, 1 action (0 to 3), 2 output (0 or 1),
3 requested mode. The earlier offsets were one byte too high. A mode
change uses the output-off/transfer guard and skips action/output stores.
With the same mode, action is stored at `S+0x4C`. Enabling requires a
nonzero selected step count and no output faults; when output is off it
clears `S+0x4C`, sets `S+6` to 1 and calls `0xCB8C(1)`. Disabling can call
`0xAEBC(0)`. Success sets `S+0x49`. Status is 0, 1 or `0xFF`, with the
shared pending and route behavior. The original instructions confirm the
payload offsets; output branch semantics also required disassembly because
Ghidra dropped a block. Physical sequencing remains untested.

## PD profiles

`0xD0`, handler `0x5BEC`, reads one profile. Reply byte 1 echoes payload
byte 0. The index used is that byte minus 1. If the class byte at
`0x1FFFA340` plus the index is below `0x65`, the group count is 7, otherwise
9. The reply then copies 16 bytes from the PD table at index times 16, the
class byte, the count, and that many groups of 4 bytes from index times
`0x24` plus `0xA0` in the same table. Variable length.

`0xD2`, handler `0xC628`, writes one profile. The index is payload byte 0
minus 1 and must be below 10, or the status is `0xFF`. It writes 16 bytes
into the PD table, one class byte at `0x1FFFA340` plus the index, a count,
a save flag, and up to 9 groups of 4 bytes. The request layout is
`D2, id, name[16], class, count, save, groups` before any route suffix.
Groups past the count have a 16-bit word
masked with `0xFFF8`. Status 0 or `0xFF`, length 2 or 3. As with `0xDA`,
the dispatcher writes 1 at `S+0x4B` after the call.

`0xE4`, handler `0x5630`, returns one payload byte: the byte at
`0x1FFFA138+0x212`, plus 1. Length 2, or 3 when the type byte is 6. WebLink
calls this the active PDO index. The formula in this image is that stored
byte plus one.

`0xE8`, handler `0xD520`, controls PD in live mode 2. Payload layout:
offset 0 remote selector, 1 u16 to `S+0x9C`, 3 selector to `0x1FFF9BB9`,
4 output, 5 requested mode. The earlier offsets were one byte too high.
A mode change takes the separate guarded path. Enable requires no faults;
when output is off and the selector is zero, it sets the selector to 1,
`S+0x2A` to 1 and `S+0x2C` to zero. Disable can call `0xAEBC(0)`. The
same-mode branch sets the control-dirty flag. The original instructions
confirm the field stores; physical sequencing remains untested.

## Charge

`0xEA`, handler `0x54AC`, copies a fixed block and returns `0x15`, or
`0x16` when the type byte is 6. These are the same offsets `0xEE` writes.
No field names are assigned here.

| Payload | Width | Source |
|---|---|---|
| 0 | u8 | `S+0x1CA` |
| 1 | u16 | `S+0x1C8` |
| 3 | u8 | `S+0x1C4` |
| 4 | u16 | `S+0x1C6` |
| 6 | u8 | `S+0x1CC` |
| 7 | u8 | `S+0x1CD` |
| 8 | u32 | `S+0x1D0` |
| 12 | u32 | `S+0x1D4` |
| 16 | u32 | `S+0x1D8` |

`0xEC`, handler `0x555C`, returns `0x1F`, or `0x20` when the type byte is 6.

| Payload | Width | Source |
|---|---|---|
| 0 | u8 | `S+0x0E` |
| 1 | u8 | `S+0x3A` |
| 2 | u16 | `S+0xB4` |
| 4 | u32 | `S+0xD8` |
| 8 | u8 | `S+0x7A` |
| 9 | u8 | `S+0x79` |
| 10 | u16 | `S+0xB2` |
| 12 | u32 | `S+0xDC` |
| 16 | u32 | `S+0xE0` |
| 20 | u16 | `S+0xB6` |
| 22 | u8 | `S+0x78` |
| 23 | u8 | `S+0x05` |
| 24 | u8 | `S+0x30` |
| 25 | u8 | `S+0x39` |
| 26 | u16 | Low half of the u32 at `S+0x1DC`, ORed with the u16 at `S+0x9E` |
| 28 | u16 | High half of the u32 at `S+0x1DC` only |

`0xEE`, handler `0x3D44`, is charge control. The remote-control tail
applies, with live mode 3. On the granted path, payload byte 8 is the mode
byte. Payload byte 1 below 6 is stored at `S+0x1CA`. The u16 at payload
bytes 2 and 3 must lie between the low limit at offset 0 and the high limit
at offset `0x14` of the charge table entry for that type (base
`0x1FFE07E0`, stride `0x16`), and is stored at `S+0x1C8`. Payload byte 4
must be below 7 when the type is 0, 1 or 2, below 9 when the type is 3, and
below `0x0D` when the type is 4. When the type is 5 the byte is accepted
and not stored. Otherwise it is stored at `S+0x1C4`. The u16 at
payload bytes 5 and 6 must be below 5001 (`0x1389`) and is stored at
`S+0x1C6`. Payload byte 7 below 2, and `S+0x4B` not 1, is the output bit.
Output 1 calls `0xA134` and, when `S+0x7B` is 0 and the short at `S+0x9E`
is 0, calls `0xD6FC`. Output 0 calls `0xD858` when `S+0x7B` is not 0. Both
call `0xCB8C(1)`.

The earlier payload offsets in this paragraph were one byte too high.
Original-instruction checks now verify type, voltage, current and table
boundaries while keeping the output off. The six voltage-limit rows are
exported in [charger-limits.json](firmware/v51/canonical/charger-limits.json); mapping
each numeric type to a chemistry still needs a UI/enum trace.

## Connection state and list ingest

`0xBD`, handler `0x4660`, returns no reply. Type 6 stores request byte 1 at
`S+3`, and when that byte is 0 clears `K+2` and the u16 at `K+0x12`. Type 5
stores request byte 1 at `S+4` and copies `length - 2` bytes from request+2
to `S+0x58`, with a zero terminator. When `S+4` is 0 it sets `K+0x0D` to 2,
clears the word at `K+0x2C` and the bytes at `K+0x0E`, `K+0x0F`, `S+0x1D`
and `S+0x1E`.

`0xBE`, handler `0x855C`, returns no reply. Request byte 1 equal to 0
clears `K+0x0D`, `K+0x0E` and `K+0x0F`. The byte at request `length - 2`
must then be 1 or `0xFF`, which increments or decrements the word at
`K+0x2C`. Request byte 1 equal to 1, 2 or 4 sets one of those three flag
bytes, or forces all three to 2 when the chosen one is already 2.

`0xBB`, handler `0x5AA0`, returns no reply. It clears `0xC4` bytes at
`0x1FFF9A70`, takes request byte 1 as a count, and for each item copies 6
bytes plus a length-prefixed tail into records of stride `0x26`. It adds
the 6 bytes into a sum and sets `S+0x3D` to 1.

## `0x51`, `0x53`, `0xF1` and `0xFD`

`0x51` and `0x53` act only when the type byte is 3 and request byte 1 is 0.
They store 0 at `0x1FFF9448+0x103` or `+0x104`. The path that reaches them
loads the constant 1000 into `r3` at `0x2FDE` and stores that word at
`0x1FFF9440`. Neither builds a reply.

`0xF1`, inline at `0x30D8`, continues only when the type byte is 3 and
request byte 1 is 0. It then requires the byte at `0x1FFFA00C+2` to be 1,
and stores 2 there. No reply.

`0xFD`, inline at `0x32C0`, continues only when request byte 1 is 3 or
`0xFF`. The value `0xFF` clears `0x1FFF9448+1` and three slot bytes, sets
`K+0` to 1, and increments the word at `0x1FFF943C`. The value 3 clears
`K+9`, sets `0x1FFF9448+1` to 1, calls `0xAE70(1)`, and ORs `0x2000` into
the word at `0x1FFF9448+0x108`. That is bit 13 of the same word whose bit 2
the remote-control tail tests. No reply.

## `0xE1` received, handler `0x3C40`

Called for request opcode `0xE1`. It acts only when the type byte is 3. If
byte 8 of the block at `0x1FFF942C` is 0, it sets `K+0` to 1 and copies four
bytes from request offset `0x11` into bytes 8 to 11 of that block. Otherwise
it copies those four bytes into bytes 0 to 3 and again into bytes 4 to 7.
The companion's reply builder identifies these as its application version,
`1.0.0.15` in this CH58x image. They are not the host-visible hardware
revision. See [the companion message trace](firmware/v51/independent/notes/commands.md#517-e1-from-the-companion-0x13c40-shape-a-no-reply).

## Block write and the `0xF0` to `0xFE` commands

These commands are in the image. `mp305` and `mp305-app` do not send them
(UR-025). The notes record the frames. They are not a procedure for writing
the device.

`0x20`, handler `0x16A8`, switches on request byte 1.

- Subcommand 5 carries a little-endian offset at request bytes 5 to 8, a
  length word at request bytes 9 to 12, and data at request byte `0x1D`.
  An offset of 0 calls `0xBDC6` with `0x100000`, `0x110000`, `0x120000` and
  `0x130000`, and clears the checksum at `0x1FFFA00C+0x94`. The length word
  must be `0x80` and `offset + 0x1000` must be below `0x44000`, or the
  status is `0xFF`. The accepted path adds `0x80` to the counter at
  `+0x0C`, writes `0x80` bytes to `offset + 0x100000`, reads them back, and
  adds each byte into that checksum. The reply is opcode `0x20`, the
  subcommand, the offset, and the status. Length 7.
- Subcommand 6 compares a little-endian word at request bytes `0x0D` to
  `0x10` with the checksum. A match echoes subcommand 6. A mismatch replies
  `0x86` and clears the counter. Reply bytes 2 to 5 are the checksum and
  byte 6 is 0. Length 7.

A type byte of 6 appends the constant `0x31` on both subcommands. `0xBDC6`
sends command byte `0xD8` to `0xBF9C` together with the address it was
given, between calls to `0xF420` (arguments 6 and 4) and `0xF3CC`. The
sequence is not named further here.

`0xF0`, handler `0xB7C4`: request byte 1 must be `0xAC`. It sets
`0x1FFFA00C` to 1 and replies `F1 00`. Length 2, or 3 copying the last
request byte when the type byte is 6. Any other request byte returns
length 0.

`0xF2`, handler `0x5118`: clears `0x98` bytes at `0x1FFFA00C`, sets the
first byte to 1, and calls `0xFC24` with the request. A zero return sets
the status to `0xFF`. Reply `F3 00` plus the status. Length 3, or 4 with
the constant `0x31`.

`0xF4`, handler `0xF508`: calls `0xFC94`. A zero return sets the status to
`0xFF`. Reply `F5 00`, then request bytes 2, 3, 4 and 5, then the status.
Length 7, or 8 with `0x31`.

`0xF6`, handler `0xF250`: calls `0xFE0C`. A zero return sets the status to
`0xFF` and calls `0xBDC6` with `0xF0000`. Reply `F7 00` plus the status.
Length 3, or 4 with `0x31`.

`0xFC`, handler `0x2400`: request byte 1 must be `0xCA`, or the return is
0. It walks flash at `0x1F0000` in blocks of `0x100`, up to 16 blocks,
looking for a byte that is neither 0 nor `0xFF`, and writes a status byte
1, 3 or 7 from the counter at `0x1FFFA00C+0x0C` (0, below `0xB001`, or not).
It also writes four short records through `0xBF3A`. Reply `FD 00`. Length
2, or 3 with `0x31`.

`0xFE`, handler `0xDB94`: reply opcode `0xFF`. When request bytes 1 and 2
are `0xAA` and `0x55`, the next two reply bytes are `AA 55` and the handler
calls `0xDBE8` then `0xCA60(200)`. Otherwise the two reply bytes are `00 00`.
Length 3, or 4 when the type byte is 6. `0xDBE8` sets byte 1 of
`0x1FFE01CC` to 1, calls `0xD868`, then sets byte 0 of that same address to
1. `0xD868` writes a fixed set of bytes and halfwords into one structure,
including 1000, 330, 1500 and 5000. The scheduled countdown reaches absolute
`0x1B71C`, then `0x1FC86`, which writes `0x1234` at `0x2005F000` and calls
the non-returning reset routine `0x1FEB8`. The latter writes AIRCR with
`0x05FA0004` plus the retained priority-group bits. Thus this is a factory
reset followed by reboot. The missing bootloader's interpretation of the
mailbox value remains unknown. The [recovery assertions](firmware/v51/independent/verification/assertions.json)
trace both writes in synthetic memory.

## Frame parser

Outbound stuffing is `0xFFF0`. It stores the byte, and stores it a second
time when the byte is `0xAA`.

Inbound parsing is `0xFF38`. A counter lives at struct `+0x213` and the
state at `+0x208`. A `0xAA` increments the counter. When the count becomes
odd the function returns 0 and the byte is not parsed. When the count
becomes even the `0xAA` falls into the state machine as a data byte. A
non-`0xAA` that arrives while the count is odd sets the state to 1 and
clears the count: the `0xAA` started a frame, and this byte is the first
body byte. A non-`0xAA` while the count is even is parsed in the current
state.

The state switch is a table branch at `0xFF5C`. Halfword offsets from
`0xFF60` are `3F 0A 15 1F 34`.

| State | Address | What it does |
|---|---|---|
| 0 | `0xFFDE` | Returns 0 |
| 1 | `0xFF74` | Splits the byte into a high nibble at struct `+0` and a low nibble at struct `+1`. The checksum at `+0x210` is set to the whole byte. State becomes 2 |
| 2 | `0xFF8A` | Stores the byte at struct `+2`, adds it to the checksum, clears the fill index at `+0x20C`. State becomes 3 |
| 3 | `0xFF9E` | Stores the byte at struct `+4`, indexed by the fill count, and adds it to the checksum. When the count reaches the byte stored in state 2, state becomes 4 |
| 4 | `0xFFC8` | Compares the byte with the checksum. Equal: returns the struct pointer and clears the state. Not equal: state becomes 0 and the function returns 0 |

State 5 and above reset the state to 0. The function does not compare the
first body byte with `0x12`. It does keep that byte whole in the checksum.
The checksum is the sum of the first body byte, the length byte, and the
buffered bytes, which is the coverage in protocol.md 2.2. The doubling rule
matches that section as well.

## Main MCU and hardware evidence

The main application uses Thumb-2, an FPU and BASEPRI critical sections.
Its startup initializes RAM from `0x1FFE0000` through `0x2003F617`.
An HDSC HC32 family attribution is inferred from register layouts. The
exact part is unresolved, and the evidence points two ways (confirmed in
code, compared with the vendor SVD files for HC32F448, F460, F467, F472,
F4A0, F4A2 and F4A8 on 2026-09-30):

- The framed UARTs are at `0x4001CC00` and `0x4001D400`. Those are USART1
  and USART3 on the F448, F467, F472, F4A0, F4A2 and F4A8. On the F460 they
  are not USART bases (its USART1 is `0x4001D000`). The console UART at
  `0x40021000` is USART7 on the F4A0-class parts and USART3 on the F460.
- RAM starts at `0x1FFE0000`. The F460's high SRAM starts at `0x1FFF8000`,
  so the initialized data and the stack do not fit an F460.
- Of 130 distinct literal addresses in the `0x4000xxxx` range, 26 match
  peripheral bases and 55 match register addresses in the F4A0 file, against
  16 and 38 for the F460. EFM at `0x40010400`, SRAMC at `0x40050800`, INTC,
  DMA1 and DMA2, GPIO, PWC, TMRA and I2C1 and I2C2 all match the F4A0 map.
- The clock routine at `0x1DAE8` (called from `SystemInit`) reads
  `0x40054026` and `0x40054100`. In the F460 header `0x40054000` is the
  clock-management base (CKSWR at `+0x26`, PLL configuration at `+0x100`).
  No F4A0-class file has a peripheral at `0x40054000`.

So the USART, SRAM and most peripheral addresses fit an F4A0-class part,
while one clock routine fits the F460. A vendor clock routine written for
the F460 and carried into an F4A0-class build would explain it (inferred).
The scoring script is `svd_score.py` in spikes/firmware_reconstruct/.

The `0x100000` and `0x1F0000` storage offsets are sent through a serial
storage driver. They do not prove 2 MB of on-chip program flash. See
[hardware.md](device/hardware.md) for the bus, command bytes, chip-select
registers, storage map and power-control signals. USB VID `0x28E9` does
not identify the main processor.

## Companion image strings

The [8051 string inventory](firmware/v51/canonical/pd-8051.bin.strings.tsv) includes
PD source/sink transitions, Safe5V/Safe0V, EPR, PPS, AVS and
`P829 v%d.%d Bat=%d-%d`. That string is at `data.bin + 0xA3BA`, processor
`0xB3BA`; it is not a verified chip model. The padding at `0xAA00` through
`0xAFFF` contains 1530 zero bytes and six nonzero bytes. The 8051 entry
is processor `0xAF88`, file offset `0x9F88`, before that padding.

The [BLE string inventory](firmware/v51/canonical/ble-riscv.bin.strings.tsv) contains
`CH58x_BLE_LIB_V1.8` at slice offset `0x7E68` and `0030MP305B` at
`0x8572`. Its load address is `0x1000`, not zero. Startup and data
pointers independently establish that mapping.

## Remaining limits

- The update omits the main bootloader, installed WCH library, per-unit
  calibration and saved runtime data.
- Discovered functions are not all semantically reviewed. Decompiler
  warnings and heuristic entries remain in the exports.
- Exact MCU models, analog circuitry, connector pinout, calibration and
  protection behavior require further evidence. No board has been inspected.
- Deferred UI, charge, PD and update state machines are only partly traced.
  Complete UI/font/graphics extraction and a buildable replacement firmware
  remain unfinished.
- The user's captured unit still reported 1.6.0.40. These V51 findings do
  not establish its behavior without a version-matched hardware check.

See [the verification ledger](firmware/verification.md) and
[TODO.md](../../TODO.md) for concrete unresolved work.
