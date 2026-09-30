# Main command map

All addresses below are processor addresses, equal to `app.bin` offset plus `0x10000`. The dispatcher is `0x12f34`. Evidence: confirmed in the supplied V51 code. Names such as PD and program also use the earlier WebLink interpretation; numeric operations below come from the firmware.

Most ordinary handlers receive an opcode-first buffer, its length, a reply buffer, and a route type. Some handlers use a different optimized register order. In particular, E0 takes request in r0, reply in r1, type in r2, length in r3. Do not impose one C prototype on every call site.

Lengths below include the reply opcode, but exclude internal framing and the extra route byte used by type 6. The BLE bridge strips that byte. Empty return length means no immediate common reply.

| Request | Handler or inline address | Reply and behavior |
|---|---|---|
| 00 | `0x1dffc` | `01 91 67 01`, four bytes. Type 6 appends request tail. |
| 18 | `0x13126` | Sets bind pending and records incoming route. Decision and `19` reply are deferred to UI/transmit service. |
| 20 | `0x116a8` | Update transfer subcommands 05/06. Reply opcode remains **20**, not request + 1. Subcommand 05 can erase/write storage at `0x100000`; data blocks are 128 bytes. |
| 51, 53 | `0x1312e`, `0x1313c` | Companion acknowledgments. Test route **type 3**, not payload length 3. No common reply. |
| A0 | `0x1307e` | A1 plus current language byte; two bytes. |
| A2 | `0x18368` | Coerces values above 1 to zero. On language change, disables output/charging and refreshes UI. A3 status, two bytes. |
| BB | `0x15aa0` | Parses a counted list containing six-byte addresses and length-prefixed names into scan-result storage. No common reply. Bound checks require further review. |
| BD | `0x14660` | Updates connection state. Type 6 updates the main connection byte; type 5 also copies remote metadata. No common reply. Earlier waveform-trigger interpretation is insufficient. |
| BE | `0x1855c` | Companion connection/selection state, selectors 0/1/2/4 and completion flags. No common reply. |
| C2 | `0x158bc` | C3 DC telemetry, 37 bytes. |
| C4 | `0x15ef8` | C5 settings, 12 bytes. |
| C6 | `0x1caa4` | C7 status, two bytes. Sequential partial writes, no remote-grant check in this handler. See [firmware.md](../firmware.md). |
| C8 | `0x1b7f4` | C9 status, usually two bytes; remote request can remain pending with no reply. DC active-mode guard. |
| D0 | `0x15bec` | D1, profile selector, 16-byte name, metadata byte, entry-count byte, then 7 or 9 four-byte entries. Returns 48 or 56 bytes before route suffix. Index is `(request[1]-1) & 255`; no local range guard. |
| D2 | `0x1c628` | D3 status. Profile indexes 1 to 10; copies name, metadata, and up to nine four-byte entries. Dispatcher disables output and marks transfer state, including when the handler rejects. |
| D4 | `0x15e48` | D5 and count, then 16-byte names and one-byte step counts in display order. Variable length. |
| D6 | `0x1c8b8` | D7 status. Program IDs 1 to 10, header fields, deletion/reindexing, save flags. Dispatcher disables output. |
| D8 | `0x131f0` | Starts deferred lookup of program ID among ten slots. Records route tail; worker 0x1d380 and service 0x133bc produce D9 through builder 0x15ca0. |
| DA | `0x1c73c` | DB status or deferred completion. Accepts program ID 1 to **9**, unlike D6 which accepts 10. Up to ten records per call, each three u32 values. First <=30500. Second <=5100 unless third is zero. Third <=99990 when second <=5100. Completion sets a flag and returns zero. |
| DC | `0x1565c` | DD plus selected program ID and step count, three bytes. |
| DE | `0x15694` | DF combined program/PD telemetry, 69 bytes. |
| E0 | `0x1b634` | E1, compact 18-byte internal reply for type 6; otherwise 31 bytes. Ordinary reply reads bootloader identity through address `0x1c`. |
| E1 | `0x13c40` | Consumes device-info response from another component. No common reply. |
| E2 | `0x1b4d0` | E3 program-control status. Requires active mode 1 for normal control. Uses the shared remote-request/grant state. |
| E4 | `0x15630` | E5 plus active PD profile index + 1, two bytes. |
| E8 | `0x1d520` | E9 PD-control status. Requires active mode 2 for normal control. |
| EA | `0x154ac` | EB charger settings, 21 bytes. |
| EC | `0x1555c` | ED charger telemetry, 31 bytes. |
| EE | `0x13d44` | EF charger-control status. Requires active mode 3. Battery-type index <=5, table-based voltage check, current <=5000, type-dependent cell-count checks. |
| F0 | `0x1b7c4` | F1 status only when request byte 1 is AC. Sets update-state flag. |
| F1 | Inline in `0x12f34` | Companion acknowledgment for route 3, payload zero; update handshake state. |
| F2 | `0x15118` | F3 initialization/validation status. Three bytes, fourth fixed 31 for route 6. |
| F4 | `0x1f508` | F5, status/data acknowledgment including four request bytes, seven bytes; fixed 31 suffix for route 6. |
| F6 | `0x1f250` | F7 final verification status, three bytes; failure path erases storage at `0xF0000`. |
| FC | `0x12400` | FD status when request byte 1 is CA; commits update metadata and storage flags. |
| FD | Inline in `0x12f34` | Consumes update progress/acknowledgment, including status 03 and FF. No common reply. |
| FE | `0x1db94` | FF plus AA 55 if input contains AA 55; sets flags, calls a defaults initializer, and delays 200 ticks. No reset or bootloader entry is established. Other input returns FF 00 00. |

The default case and unused response opcodes take the no-reply path. This table describes code paths, not permission to send update or output-changing commands to hardware.
