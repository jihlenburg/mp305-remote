# Hostlink: the main MCU side of the host communication path

> Recovery review, 2026-09-30: imported from `~/mp305b-fw-re/notes/`.
> Instruction/decompiler labels below mean **confirmed in code**. Emulation
> uses original instructions with modeled external calls and synthetic RAM.
> **Inferred** meanings retain that status. Earlier-document verdicts describe
> the source snapshot, before the corrections in this recovery.
> See [the recovery record](../README.md) for corrections, run results and limits.

Firmware 1.6.0.51, `bin/app.bin` (HC32-family Cortex-M4, linked at
`0x10000`). All addresses are absolute processor addresses. `S` is the live
state block `0x1FFFAACC`. `K` is the link bookkeeping block `0x1FFE0184`.
`T` is the transmit block `0x1FFF9448`. CH58x addresses are CH58x processor
addresses (image loaded at `0x1000`, RAM copies as in the README).

Evidence labels used below:

- **disasm**: read from the Thumb (or RV32) instruction listing.
- **decomp**: read from the Ghidra C in `out/app_decomp.c` or `out/ch58x_decomp.c`.
- **emu**: executed on original instructions in Unicorn with synthetic RAM
  (`scripts/hostlink_emu_tests.py` for the main MCU,
  `scripts/hostlink_ch58x_route_tests.py` for the CH58x). Not hardware.
- **inferred**: an interpretation, with the reason given.

Scripts written for this area: `scripts/hostlink_emu_tests.py`,
`scripts/hostlink_emu_ch58x.py` (RV32 Unicorn harness with a stubbed WCH
library table), `scripts/hostlink_ch58x_route_tests.py`,
`scripts/hostlink_xref.py` (Thumb BL/B.W and literal cross references, finds
callers Ghidra missed), `scripts/hostlink_rvdis.py` (RV32 listing).

## Summary of the most important findings

1. All host traffic (USB HID and Bluetooth) reaches the main MCU over one
   UART, USART3 at `0x4001D400`, 115200 baud, pins PC0/PC1, receive by
   byte interrupt, transmit by DMA2 channel 1. The CH58x is the only thing
   on that UART.
2. The first body byte of every UART frame is `(source << 4) | destination`.
   Node numbers: 1 USB host, 2 main MCU, 3 CH58x itself, 5 Bluetooth
   accessory link (CH58x central role), 6 Bluetooth host app (CH58x
   peripheral role, AF01 and AF02). The "type byte" of a channel record is
   the source nibble, written by the MCU frame decoder. Replies swap the
   nibbles: a USB request `0x12` gets `0x21`, a BLE request `0x62` gets
   `0x26`.
3. The `0x31` that precedes AF01 notifications is not an address. It is the
   AF01 route marker that the CH58x appends to every AF01 write (`0x00` for
   AF02), that type-6 handlers echo as the last reply byte, and that the
   CH58x moves to the front when it notifies on AF01. The first byte a host
   writes on AF01 is discarded by the CH58x, whatever its value.
4. Link state `S+3`: 0 none, 1 Bluetooth host bound (set by `BD 01` from the
   CH58x after a successful bind), 2 USB host active (set by any USB
   request). When `S+3` becomes 0 the remote-control grant `S+0x42` and the
   request state `S+0x45` are cleared within one lvgl_task pass. The output
   is not switched off by a link drop (answers TBD-005 in code).
5. Link-drop triggers: Bluetooth disconnect (`BD 00` from the CH58x when it
   starts advertising again), USB silence for 8000 User_task iterations
   (about 8 s), a VBUS collapse reported by the PD companion, 50 failed
   retransmissions toward the CH58x (about 5 s), and power-off.
6. Remote control over USB is granted at once on `C8` with `remoteCon = 2`
   (reply `C9 00`), with no prompt. Over Bluetooth the same request gives no
   immediate reply. The device shows "Allow Remote Control" and sends a
   deferred `C9 00` (Allow) or `C9 01` (Deny, or a menu open, or no key
   press for about 60 s). While pending, every `C8` gets no reply. Without a
   bind (`S+3 = 0`) the deferred reply is dropped and the grant is cleared.
7. Bind (`0x18`): the main MCU sets a pending flag and records the source
   nibble, then shows the "Confirm Bluetooth Binding" prompt. Allow builds
   `19 00`, Deny builds `19 FF`, both deferred through the transmit service.
   Whether the device remembers a host is decided in the CH58x, not the main
   MCU; the main MCU does not store host IDs. USB `0x18` is answered too and
   is not gated by the prompt in the traced path.
8. The main MCU drives the CH58x with internal frames on node 3: `E0` at
   boot (get BLE info), `FC *` (push the advertised name into CH58x
   DataFlash), `50 xx` (advertising/role mode 0/1/2), `52 53`/`52 20`
   (enable/disable the radio and USB), `10` (time?), `F0 AC` (update
   prepare). It consumes `55`, `51`, `53`, `F1`, `FD`, `BD`, `BB`, `BE`,
   `11` and `E1` coming the other way. Full table below.

## 1. Physical links

**One UART carries all host traffic.** `main` at `0x533C0` calls
`0x27D24` (console UART) then `0x1787C`, which sets up two framed UARTs
through the shared init helper `0x644A4`:

| UART | Base | Init | Baud | GPIO (port.bit, mux) | DMA | RX path | Endpoint |
|---|---|---|---|---|---|---|---|
| USART1 | `0x4001CC00` | `0x644A4` | 115200 | P3.9 mux `0x20` (TX), P3.8 mux `0x21` (RX) | DMA2 ch0, TRGSEL0 = `0x12E` | RI IRQ `0x1EF0C` -> decoder ch 0 -> PD parser `0x11900` | 8051 PD companion |
| USART3 | `0x4001D400` | `0x1787C` via `0x644A4` shape | 115200 | P2.0 mux `0x20` (TX), P2.1 mux `0x21` (RX) | DMA2 ch1, TRGSEL1 = `0x14E` | RI IRQ `0x1EF5C` -> decoder ch 1 -> `0x12F34` dispatch | CH58x (BLE + USB HID) |
| USART7 | `0x40021000` | `0x27D24` | 1000000 | P0.9 mux `0x26` (TX), P0.10 mux `0x27` (RX) | none (polled) | RI IRQ `0x145EC` -> line buffer `0x1FFF8A8C` | text/debug console |

Evidence: disasm of `0x644A4`, `0x1787C`, `0x27D24`. `0x1F0E4` writes USART
`CR1/CR2` with `0x600` ORed in (word length, 1 stop, no parity) and the
`0x1C200` = 115200 divisor; `0x27D24` uses `0x1C200` = ... actually the
console uses divisor arg `1000000` passed to `0x27D24` (disasm). GPIO mux
codes come from `0x153B4(port, bitmask, mux)` calls (decomp). Interrupt
sources on the HC32F4A0 map are USART3_RI = 333, USART3_EI = 332,
USART3_TCI = 335 (selectors `0x14C/0x14D/0x14F` registered at
`0x1787C`); USART1 uses `0x12C/0x12D/0x12F` (RI = 301). NVIC priority
argument 15 (`0x20138(vec, 0x0F)`). Confirmed against `svd/hc32f4a0.h`.
The exact package pins need the MCU part, still unresolved (inferred).

**RX is per-byte, not DMA.** DMA2 is set up for each UART but the RI
interrupt callback runs the byte decoder. USART3 RX callback `0x1EF5C`:
reads `USART3_RDR` (`0x1F026` returns the halfword at base+6), calls the
decoder `0x146B8(1, byte)`, and on a completed frame (nonzero return)
copies the 260-byte record to one of four mailboxes by source nibble and
sets that mailbox's "ready" flag (decomp; see section 2). USART1 RX
callback `0x1EF0C` calls `0x146B8(0, byte)` and, on a completed frame,
`0x11900(0)` (the PD-link parser). DMA is used only for transmit
(`0x1E24C` programs DMA2 source/count and starts it, then enables the
UART TX interrupt bit).

**Transmit ring.** The transmit service `0x133BC` (User_task) builds a
frame into the mailbox-1 record via encoder `0x15430(1, record, out)`,
copies the result to the DMA source buffer `0x1FFF944A`, saves its length
at `0x1FFF954A`, and calls `0x1E24C(0x4001D400, 1, &0x1FFF944A, len)` which
starts DMA2 ch1. There is one outstanding frame; the next is not sent until
`K+0` (`0x1FFE0184`, "CH58x acknowledged") is set again by an incoming
frame (decomp, and emu: a second request while unacked overwrites the
mailbox, so pipelined requests can lose the earlier reply, see
`test_pipelining`).

**Console/debug UART (USART7, `0x40021000`, 1 Mbaud).** RX callback
`0x145EC` treats CR (`0x0D`) as end of line and ignores LF (`0x0A`); it
buffers into `0x1FFF8A8C` (512 bytes) with length at `0x1FFE014A`,
cursor/flag at `0x1FFE0148/0x1FFE014C`. The line is consumed by
`0x1227C`, called once per Time_task loop (`0x1E054`, disasm). It matches
these commands with `strncmp`/`sscanf`-style helpers (`0x1051E`, `0x10550`)
against literals at `0x12380`:

| Command written to USART7 | Parsed as | Effect (decomp `0x1227C`) |
|---|---|---|
| `VSET=%d,ISET=%d,DCOUT_EN=%d` | prefix `VSET=` | reject if V > 30500 or I > 5100; else `0x1AF64((V+5)/10)` set voltage, `0x1AEA4(I)` set current, `0x1AEBC(en)` set output |
| `TSET=%d,%d` | prefix `TSET=` | store two bytes at `S` region `0x1FFFAA26/27` (temperature setpoints; feed the fan curve `0x19FE0`) |
| `FanCompareValue=%d` | prefix `FanCompareValue=` | store `0x1FFFAA06` (fan PWM compare) |
| `language=%d` | prefix `language=` | store `0x1FFFA0CE` (language byte, same as `0xA2`), then `0x1D958` + `0x1CA60(200)` (reload settings, reset) |

Output on the console is one-way printf (`0x58970` -> `0x58A6C` polls
`USART7` TX-empty then writes `USART7_TDR`); the "Data-%x" style dumps and
`%dmV/%dmA` debug strings on the BLE side are separate. The console command
set is small and fixed: it is a factory/bring-up test hook. It listens only
on USART7, which is a separate physical UART from the CH58x/PD links. It is
not reachable from the Bluetooth or USB host: those arrive on USART3 and
never reach `0x1227C`. Whether the USART7 pins are on an accessible header
is a hardware question (inferred). `VSET`/`TSET`/`DCOUT_EN` let this console
switch the output on with no bind and no remote grant, so it is a genuine
control surface if physically reachable.

## 2. The four channel records at 0x1FFF9660 (stride 260)

The decoder writes decoded frames into per-channel work areas at
`0x1FFF9BE4 + ch*0x214` (ch 0 = USART1/PD, ch 1 = USART3/host). On a
completed USART3 frame, `0x1EF5C` looks at the source nibble stored at
offset 0 of the ch-1 work area and copies the whole 260-byte record to one
of four mailboxes, then sets a ready byte (decomp `0x1EF5C`):

| Source nibble | Mailbox base | Ready flag | Meaning |
|---|---|---|---|
| 6 | `0x1FFF9660` | `0x1FFE01AC` | Bluetooth host app (CH58x peripheral, AF01/AF02) |
| 1 | `0x1FFF9764` | `0x1FFE01AD` | USB HID host |
| 5 | `0x1FFF9868` | `0x1FFE01AE` | Bluetooth accessory link (CH58x central) |
| 3 | `0x1FFF996C` | `0x1FFE01AF` | CH58x internal messages |

(`0x1046A` copies `0x104` = 260 bytes. Source 3 has a fast path: if the
opcode there is `0x11` it calls `0x13C88` directly (time sync) and clears
the ready flag.)

**Record layout** (offsets into a 260-byte record, decomp of decoder
`0x146B8`, dispatcher `0x12F34`, and `0x15FA4` which returns
`ch*0x214 + 0x1FFF9CE8` for the transmit staging copy):

| Offset | Field | Set by |
|---|---|---|
| 0 | source nibble (the dispatcher's "type byte") | decoder state 1: `byte >> 4` |
| 1 | destination nibble | decoder state 1: `byte & 0x0F` |
| 2 | body length (opcode + payload) | decoder state 2 |
| 3 | unused (0) | - |
| 4 | opcode | decoder state 3, index 0 |
| 5.. | payload bytes | decoder state 3 |

**Who writes the type byte and where it comes from.** The type byte is
record byte 0, the high nibble of the first UART body byte, written by the
decoder in state 1 (`(&DAT_1fff9be5)[..] = b & 0xf; (&DAT_1fff9be4)[..] =
b >> 4;`, decomp `0x146B8`). The full first body byte is
`(source << 4) | destination`. On the wire from the CH58x to the MCU the
source is the origin node and the destination is 2 (the MCU). So:

- `0x62` host->device on AF01/AF02 gives type byte 6.
- `0x12` USB host->device gives type byte 1.
- `0x52` accessory link gives type byte 5.
- `0x32` CH58x internal gives type byte 3.

When the MCU replies, the encoder `0x1FEDC` swaps the nibbles:
`addr = (record[1] & 0xf) << 4 | (record[0] & 0xf)`, i.e. source becomes
the old destination (2, the MCU) and destination becomes the old source.
So a BLE request `0x62` produces a reply `0x26` (dest 6, "to the host"),
and a USB request `0x12` produces `0x21`. The `0x31` address WebLink sees
on AF01 replies is a separate CH58x route marker (section 3), not this
byte. Emulated in `test_dispatch`: reply addr = `0x26/0x21/0x25/0x23` for
sources 6/1/5/3.

Type 6 vs the other types is a route, not a transport: `0xBD` treats its
own record differently for type 5 and type 6 (accessory link vs host link),
and every reply handler appends the trailing route byte only when the type
is 6 (section 4). Types 3 and 5 are internal (CH58x, accessory); type 1 is
USB; type 6 is the Bluetooth host app.

## 3. Frame parser and builder (UART between CH58x and MCU)

**Wire format (both directions), confirmed by emu round-trip on the
original encoder `0x1FEDC` and decoder `0x1FF38` over 300 random frames,
0 mismatches, plus edge cases** (`scripts/hostlink_emu_tests.py`):

```
AA  ADDR  LEN  OPCODE payload...  CKSUM
```

- `AA` (single) starts the frame and is never doubled.
- `ADDR` = `(source << 4) | destination`.
- `LEN` = count of bytes from OPCODE through the last payload byte.
- `CKSUM` = 8-bit sum of ADDR, LEN and the OPCODE+payload bytes.
- Every byte after the leading `AA` that equals `AA` is written twice; the
  reader consumes `AA AA` as one `AA`. This covers ADDR, LEN, payload and
  CKSUM.

**Decoder `0x1FF38` state machine** (disasm + decomp `0x146B8`). Per channel
there is a stuffing counter at record `+0x213`, a state byte at `+0x208`,
and a 32-bit fill index at `+0x20C`. The original recovery note confused
the fill index with the state. Instructions and stepped execution agree
with the existing firmware.md offsets:

| State | Action |
|---|---|
| any | If byte == `AA`: increment the stuffing counter; if it is now odd, return 0 (swallow, wait for the pair). If a non-`AA` arrives while the counter is odd, force state 1 and clear the counter (the `AA` opened a frame). |
| 0 | idle, returns 0 |
| 1 | first body byte: high nibble -> record[0], low nibble -> record[1], checksum := whole byte, state := 2 |
| 2 | length -> record[2], add to checksum, fill index := 0, state := 3 |
| 3 | payload byte -> record[4 + i], add to checksum; when i+1 reaches the length, state := 4 |
| 4 | compare byte with checksum: equal -> return record pointer and clear state; not equal -> state := 0, return 0 |

Edge cases confirmed by emu:

- A frame whose ADDR would be `AA` cannot be received from a fresh state:
  the `AA` after the marker is treated as stuffing, so `AA` as the marker
  plus `AA` as ADDR collapses. Address `0xAA` (source 0xA, dest 0xA) does
  not decode (emu returns 0). No real node uses nibble `0xA`.
- Zero length (`AA ADDR 00 CKSUM`) does not form an accepted frame (state 3
  never satisfies the fill loop; emu returns all 0). Confirms the earlier
  note.
- A checksum error sets state back to 0 and drops the frame (emu: state 0,
  no record).
- Leading garbage before `AA`, and a truncated frame followed by a fresh
  `AA`-started frame, both resync correctly (emu: the good frame decodes).
- A single (un-doubled) `AA` inside the body restarts the parser with the
  following byte as a new ADDR, so a malformed stuffing is not silently
  accepted as data (emu: state stuck mid-frame, no record).
- LEN or a payload byte equal to `0xAA` round-trips because the sender
  doubles it (emu: `len 0xAA` frame decodes, body matches).

The parser does not compare the first body byte with `0x12`; it keeps the
whole byte in the checksum (matches protocol.md 2.2). No timeout is applied
inside the byte parser itself: a stalled frame just leaves the state
non-zero until the next `AA` resyncs it. Frame-level timeouts live in the
transmit service (section 6), not the parser.

**Builder `0x1FEDC`** (via wrapper `0x15430(channel, record, out)`):
writes `AA`, then `addr = (record[1] & 0xf) << 4 | (record[0] & 0xf)`
through the stuffing helper `0x1FFF0` (which writes the byte and writes it
again if it is `AA`), then LEN, then each payload byte, then the running
checksum, doubling `AA` throughout. Returns the encoded length. There is no
outer chunking on this UART: a whole frame (up to 260 body bytes) goes in
one DMA burst. Chunking to 62-byte USB reports is done in the CH58x, not
here (section 8, CH58x side).

**Reply address `0x31`.** The main MCU never emits `0x31` as a frame
address. It appends `0x31` as a payload byte only on type-6 replies, and
only because the CH58x asked it to: the CH58x AF01 write handler appends
`0x31` to the forwarded command and AF02 appends `0x00` (CH58x side,
confirmed in `out/ch58x_decomp.c` `FUN_ram_00004074` and by emu). The
type-6 reply handlers copy that last request byte to the end of the reply
(`param_3[2] = param_1[param_2-1]`, e.g. `0x1B7F4` C8, `0x12690` bind).
The CH58x reply router `0x3FAC` then: if the reply's last byte is `0x31`,
notify on AF01 with `0x31` moved to the front (this is the address WebLink
sees); otherwise notify on AF02 without the trailing byte. Emu
(`hostlink_ch58x_route_tests.py`): a `C5+31` frame notifies AF01 as
`31 C5 00...`; a `19 00 00` frame notifies AF02 as `19 00`.

## 4. Dispatcher 0x12F34 (User_task)

Runs once per User_task loop (`0x1F224`, disasm `0x1F208`). Flow (decomp +
disasm):

1. Watches the four ready flags `0x1FFE01AC..0x1FFE01AF` (mailboxes 6, 1,
   5, 3 in that priority). The first one set selects mailbox index 0..3;
   that flag is cleared. Only one mailbox is serviced per call (emu
   `test_pipelining`: with both BLE and USB pending, the first call handles
   BLE, the next handles USB).
2. `iVar4 * 0x104` selects the 260-byte record. `type = record[0]` (source
   nibble), `len = record[2]`, `opcode = record[4]`, payload pointer =
   record+5.
3. If the type is 1 (USB) it sets `S+3 = 2` (`DAT_1fffaacf = 2`) and, when
   `S+3` was not already 2, snapshots a PD field; it also clears the USB
   idle timer `0x1FFE01A8`. So any USB frame marks the USB link active.
4. A big switch on the opcode calls the handler with one of two register
   shapes (disasm of the call sites confirms firmware.md's two shapes:
   `mov r3,r2 / mov r2,r1 / mov r1,ip` = (record, len, reply, type) for the
   `0xA2/0xC2.../0xEE` group; `mov r3,ip` = (record, reply, type, len) for
   `0x00/0x20/0xE0/0xF0/0xF2/0xF4/0xF6/0xFC/0xFE`). `0xBB/0xBD/0xBE` take
   (record, len, type) with no reply buffer.
5. If a handler returns a nonzero length, the dispatcher builds the reply
   into the transmit staging area: `reply[2] = len`, `reply[1] = type`
   (source nibble), `reply[0] = record[1]` (destination nibble = 2),
   encodes with `0x15430`, saves the length at `0x1FFF954A`, and sets
   `T = 0x1FFF9448 = 1` to tell the transmit service a frame is queued.
   Emu confirms reply address = swapped nibbles.

**Per-type trailing byte (type 6 appends one byte).** Every reply handler,
on the granted return paths, does `if (type == 6) { reply[n] =
record[len-1]; length++; }`. `record[len-1]` is the CH58x route marker
(`0x31` for AF01, `0x00` for AF02). Handlers `0xF2/0xF4/0xF6/0xFC/0x20`
instead store the constant `0x31` directly for type 6 (disasm of
`0x1F250`, `0x1F508`, `0x1F27A`). Reason: the CH58x needs the route marker
back so `0x3FAC` can pick AF01 vs AF02; for the update-family handlers the
firmware hard-codes AF01 (`0x31`) because those replies always go to the
host app. `0xE0` type-6 layout also ends with that byte (emu: type-6 E1
reply ends `...02 00 00`, then route `0x31` appended by the dispatcher path
for a real AF01 request).

Inline (no separate handler) cases in the dispatcher body: `0x18` (bind
pending, `S+0x47=1`, `K+6=type`), `0x51`/`0x53` (type 3, payload 0: clear
`0x1FFF954B`/`0x1FFF954C`, load `1000` into `0x1FFF9440`), `0xA0` (language
read), `0xD8` (program select), `0xF1` (type 3), `0xFD` (type 3 or `0xFF`),
`0xE1` (`0x13C40`). See sections 5, 7, 8.

## 5. Bind flow end to end (0x18 / 0x19)

**Strings** (`out/app_strings.tsv`): `Confirm Bluetooth\nBinding`
(`0x8379C`, string index `0x26`), `Allow Remote\nControl` (`0x83868`,
index `0x25`), `Remote Control\nActive` (`0x83784`), `Bluetooth
Accessories` (`0x839DC`), `Scan to access the remote control panel`
(`0x83840`).

**`0x18` receipt** (inline `0x13126`, disasm): sets `S+0x47 = 1`
(`0x1FFFAB13`, bind pending) and stores the type byte at `K+6`
(`0x1FFE018A`). No reply is built here.

**The prompt** is the "Confirm Bluetooth Binding" dialog built by
`0x2840C` (uses string index `0x26`), reachable from the UI popup builder
`0x2E158`. Its two buttons register callbacks through `0x21A50` (disasm at
`0x21D94`/`0x21DA6`): the object at `0x1FFE06C0` gets callback `0x2478D`
(Allow) and `0x1FFE06C4` gets `0x2483D` (Deny). Both are odd (Thumb)
pointers, so the functions are at `0x2478C` and `0x2483C`. These are
processor addresses, i.e. firmware.md's "`0x1478C`" and "`0x14840`" are
those file offsets plus `0x10000` (and `0x14840` is really `0x2483C`);
corrected. The physical button binding is: `0x1FFE06C0` and `0x1FFE06C4`
are the two child widgets of the confirm-bind dialog (`0x2840C` builds
them), and `0x14B14` (the input event handler) routes a click on the
active dialog to their callbacks.

- **Allow `0x2478C`** (decomp): `S+0x46 = 1` (`0x1FFFAB12`, bind decision),
  `S+0x47 = 0` (clear pending), and sets bit 1 of the word at
  `0x1FFF9550`. It does not touch the remote grant `S+0x42`.
- **Deny `0x2483C`** (decomp): `S+0x46 = 0`, `S+0x47 = 0`, sets the same
  bit 1 of `0x1FFF9550`.

Bit 1 of `0x1FFF9550` is the "build the bind reply" request the transmit
service watches.

**`0x19` builder `0x12690`** (called from `0x133BC` at `0x13836`, disasm):
`reply[0] = 0x19`; `reply[1] = 0` if `S+0x46 != 0`, else `0xFF`; length 2,
or 3 with a trailing `0` when the caller's type is 6. After it returns the
transmit service clears bit 1 of `0x1FFF9550` and clears `S+0x46` and
`S+0x47`. Emu (`test_bind`): allow -> reply addr `0x26` body `19 00 00`;
deny -> `19 FF 00`; USB (type 1) allow -> addr `0x21` body `19 00`.

**Timeout if nobody presses a button.** The UI service `0x1E7B4`
(lvgl_task) times popups: `0x1E284` and the popup timers (`S+0x243`,
`S+0x2B4` accumulators) auto-dismiss the confirm dialog. When the dialog
closes without Allow, `S+0x46` stays 0, so the deferred `0x12690` yields
`19 FF`. The dominant timer is the 60 s idle in the general UI path; the
hardware captures (protocol.md 1.3) show Allow after 3-7.7 s (a key press)
and the design's "no key press -> deny" matches `19 FF`. Exact timer
identity for this specific dialog is inferred from the shared popup timing
code; the value is on the order of tens of seconds.

**Does the device remember hosts?** The main MCU does not: it stores no
host ID and `0x18` only records the type byte. Remembering is entirely a
CH58x function (host-ID store, `fastBinding`), and only for Bluetooth. The
"deferred `0x2690`" and the whole prompt are bypassed by the CH58x for a
frame whose last byte is nonzero (fast-bind lookup) - that never reaches
the main MCU.

**Does USB need the prompt?** A USB `0x18` (type 1) is dispatched the same
way and its `0x19` is built the same way (emu, addr `0x21`), so the prompt
UI would appear for USB too. In practice WebLink over USB has not been
observed. The remote-control gate (below), not bind, is what actually
controls output for USB, and that is granted without a prompt for USB
(section 6).

## 6. Remote-control gate and link-drop behaviour

State bytes in `S = 0x1FFFAACC` (offsets decimal->hex): `S+0x42`
(`0x1FFFAB0E`) remote granted; `S+0x45` (`0x1FFFAB11`) remote request
state; `S+0x46` (`0x1FFFAB12`) bind decision; `S+0x47` (`0x1FFFAB13`) bind
pending; `S+3` (`0x1FFFAACF`) link/stream state. (Note: firmware.md's
"S+0x42/0x45/0x46/0x47" map to these `0x1FFFAB0E/11/12/13` bytes, which are
in a *mirror* block copied from `S` each UI pass by `0x1E284`; the handlers
read/write both. The `C8` handler `0x1B7F4` uses `0x1FFFAB0E`/`0x1FFFAB11`
directly, confirmed by disasm and emu.)

**The word at `0x1FFF9448+0x108` = `0x1FFF9550`.** It is a bitmask of
"work to do", read by the transmit service `0x133BC` and the `0xC8`/remote
tail. Every bit and its writer (disasm/decomp, exhaustive from
`out/app_refs.tsv` and grep):

| Bit (mask) | Set by | Meaning / transmit-service action |
|---|---|---|
| 0 (`0x1`) | `0x1920C`, `0x1AB34`, `0x1ECC4`, `0x12F34` (via `0x51`/`0x53` path effect) | request `0x52` companion charge/PD sync frame |
| 1 (`0x2`) | `0x2478C`, `0x2483C`, `0x54688`, `0x13836` clears it | build the `0x19` bind reply |
| 2 (`0x4`) | `0x5553C`, `0x5AF88`, `0x5B034` | build the deferred `0xC9` remote-request reply |
| 7 (`0x80`) | `0x1D380` | send a `0xD9` program-read chunk (builder `0x15CA0`) |
| 8 (`0x100`) | `0x1D380` | send the deferred `0xDB 00` after the program steps were saved |
| 9 (`0x200`) | `0x56E3C` | send `0xDD` selected-program update (builder `0x1565C`) |
| 10 (`0x400`) | `0x5735C`, `0x5FAE4`, `0x5FF04` | send `0xE5` active PD profile update (builder `0x15630`) |
| 11 (`0x800`) | `0x26594`, `0x380EC` | send `0xEB` charge settings update (builder `0x154AC`) |
| 12 (`0x1000`) | `0x5E7C0` | send `0xC5` settings update (builder `0x15EF8`) |
| 13 (`0x2000`) | `0x12F34` (`0xFD` value 3), `0x27C58` | send `0xE0` to the CH58x (node 3) to read its identity |
| 14 (`0x4000`) | `0x1CA60` | send `0xF0 AC` to the CH58x before a main-MCU reset |
| bit 5/6 etc (`0x20/0x40/0x10`) | `0x2176C`, `0x2299E`, `0x24E9E` | UI-driven `0xB8`/`0xBE`/other one-shot sends |

The transmit service walks these bits in priority order; each satisfied
bit is cleared with an `& ~mask`. (Correction, 2026-09-30: the meanings of
bits 7 to 14 were re-read from the transmit service `0x133BC`, whose
`DAT_1fff9550 << n` tests select bit `31 - n`: `<< 0x18` bit 7 `D9`,
`<< 0x17` bit 8 `DB`, `<< 0x16` bit 9 `DD`, `<< 0x15` bit 10 `E5`,
`<< 0x14` bit 11 `EB`, `<< 0x13` bit 12 `C5`, `<< 0x12` bit 13 `E0`,
`<< 0x11` bit 14 `F0 AC`. An earlier version of this table had bits 7 and 8
swapped and bits 10 to 14 shifted. The producers were correct. Section 8 of
commands.md has the same map.) So `0x1FFF9550` is a set-by-producer,
clear-by-sender work mask, not a permission gate. firmware.md's "bit 2
skips the setpoint" is a different test: `0x1B7F4` tests
`(byte)DAT_1fff9550 << 0x1d`, i.e. bit 2 of the low byte, which is the
remote-reply-pending bit; when set, `0xC8` returns status 1
(remote not granted yet) rather than applying (emu-consistent).

**Remote grant flow** (decomp `0x1B7F4`, emu `test_c8_sequences`,
`test_remote`):

- `remoteCon = 2` requests control. `S+0x45` (`0x1FFFAB11`) := 2. If
  `S+3 == 2` (USB) it grants immediately: `S+0x45 := 1`, `S+0x42 := 1`,
  reply `C9 00`. If `S+3 != 2` (Bluetooth or none) the handler returns
  length 0 (no reply) and leaves `S+0x45 = 2` pending, and sets bit 2 of
  `0x1FFF9550` via the Allow-dialog callback path.
- The Bluetooth grant is completed by the "Allow Remote Control" dialog:
  `0x5AF88` (Allow) sets `S+0x42 = 1`, `S+0x45 = 1` and bit 2 (deferred
  `C9 00`); `0x5B034` (Deny) leaves `S+0x42 = 0` (deferred `C9 01`). Emu:
  allow dialog -> deferred `C9 00 31` on AF01, deny -> `C9 01 31`.
- `remoteCon = 1` needs `S+0x42 == 1` already, else `C9 01` and nothing
  applied. `remoteCon = 0` clears `S+0x42`. `remoteCon > 2` -> `C9 FF`.
- While a request is pending (bit 2 low-byte set) every `C8` returns no
  reply (emu: rc2 then rc1 both "no reply" until the dialog resolves).

**Link drop / disconnect.** The UI snapshot `0x1E284` runs every lvgl_task
pass and copies `S`-mirror bytes. It contains
(decomp, emu `test_link_drop_snapshot`):

```
if (S+3 == 0)      S+0x42 = 0;           // remote released
else if (S+3 == 2) S+0x4F(aa4f) = 1;     // USB "remote active" marker
```

So when the link state `S+3` goes to 0, the remote grant `S+0x42` is
cleared on the next UI pass. **The output is not switched off.** No path in
`0x1E284`, `0x14660` (BD handler) or the transmit service writes the output
enable `0x1FFFAA2E` on a link drop (emu: output stays 1 through
`S+3 -> 0`). This directly answers **TBD-005**: on link loss the device
releases remote control but leaves the output in its current state, and
answers **TBD-012** in code: remote control is a real, revocable grant that
is dropped on disconnect (so a `RemoteControlLostError`-style condition is
reachable by dropping the link).

**What sets `S+3` to 0:**

- Bluetooth: `0xBD` type 6 with payload byte 0 == 0 (`0x14660`:
  `S+3 = 0`, clears the retry counters `K+2`/`0x1FFE0196`). The CH58x sends
  `BD 00` when the peripheral link drops and it resumes advertising (CH58x
  side). Emu: `BD 00` src 6 -> `S+3 = 0`.
- USB: the transmit service `0x133BC` runs a USB idle timer
  `0x1FFE01A2`; after `0x1388` (5000) accumulated ms with no USB frame it
  sends a `0x55` poll to the CH58x, and the dispatcher's own timer
  `0x1FFE01A8` clears `S+3` from 2 after `0x1F40` (8000) ms of USB silence
  (decomp, emu `test_timeouts (b)`: `S+3` cleared after ~8000 iterations).
- The retransmit watchdog: if the CH58x never acknowledges (no incoming
  frame sets `K+0`), the transmit service resends every ~5000 loop
  iterations and, after `0x31` (49, i.e. the 50th) unacknowledged tries on
  the USB path (`K+2 > 0x31`) or the BLE path, clears `S+3`, `K+2` and the
  stream state (decomp, emu `test_timeouts (c)/(d)`: 50 resends then `S+3`
  cleared).

There is a **keepalive/watchdog on host traffic**: the `0x55` heartbeat to
the CH58x and the incoming `0x55` acks form the link liveness check, and
the notify-failure code `55 00 FF` / queue-full `55 FF 00` from the CH58x
drives the retransmit-then-give-up logic above.

## 7. Real-time stream 0xBD/0xBE and list ingest 0xBB

**`0xBD` handler `0x14660`** (decomp, emu `test_internal_inbound`):

- Type 6 (Bluetooth host link): `S+3 = record[1]`. If that byte is 0
  it clears `K+2` (`0x1FFE0186`) and `0x1FFE0196` (the retry counters). So
  `BD 01` = host bound (link up, `S+3 = 1`), `BD 00` = link down. This is
  the CH58x telling the MCU the BLE host connection state, not a waveform
  trigger. Confirms the CH58x-side claim; `0xBD type 6` = link state.
- Type 5 (accessory link): `S+4 = record[1]`; copies `len-2` bytes from
  record+2 to `S+0x58` (`0x1FFFAB24`) with a zero terminator - this is the
  accessory's name string. The string copied to `S+0x58` is the connected
  Bluetooth accessory's advertised name (used by the "Bluetooth
  Accessories" UI, string `0x839DC`). When `S+4 == 0` it resets the
  accessory input state (`K+0x0D..0F`, wheel counter `K+0x2C`, `S+0x1D`,
  `S+0x1E`). Emu: `BD 05 01 "ISDT-RC"` -> `S+4=1`, `S+0x58 = "ISDT-RC\0"`.

**`0xBE` handler `0x855C`** (decomp, emu): accessory input events (a remote
control wheel/buttons). `record[1] == 0` reads a wheel/step at
`record[len-2]` (1 = +1, `0xFF` = -1) into `K+0x2C` and latches the two
button-armed flags into `S+0x1D`/`S+0x1E` (`0x1FFFAAE9`/`0x1FFFAAEA`).
`record[1]` 1/2/4 arm three input flags `K+0x0D/0x0E/0x0F`
(`0x1FFE0191/92/93`); when the chosen one is already 2 all three are forced
to 2. The wheel and buttons then feed the encoder-read callbacks
`0x15B54` (wheel), `0x1868C`/`0x1919C` (buttons) and the LVGL keypad reader
`0x3B05C`, i.e. a Bluetooth accessory acts as a remote knob/keypad. Emu:
`BE 04` arms the push, `BE ...01` gives wheel +1 (`0x15B54` returns 101),
`BE 00` releases.

These accessory events also arrive from a Bluetooth *host* on AF01
(type 6 with a `0x31` suffix): emu `test_be_from_host` shows a host-sent
`BE 01`/`BE 00` (src 6) arming `S+0x1D` and the output-key worker `0x18728`
then toggling the output. So the phone app can drive the same input path as
a physical accessory.

**`0xBB` handler `0x15AA0`** (decomp, emu): clears `0xC4` bytes at
`0x1FFF9A70`, takes `record[1]` as a count, and for each item copies 6
bytes (a MAC) plus a length-prefixed name into records of stride `0x26` at
`0x1FFF9A76+`; sums the 6 MAC bytes into `0x1FFF9A70` and sets `S+0x3D`
(`0x1FFFAB09`) = 1 so the UI list `0x54390` rebuilds. This is the
**"Bluetooth Accessories" scan-result list** (the accessories the device,
as a BLE central, can connect to). Confirms the CH58x-side claim
(`0xBB` = accessory scan list, 6-byte MAC + len + name).

**Stream type 5 vs 6 in 0xBD.** Type 6 is the host-link state byte
(`S+3`); type 5 is the accessory-link state byte plus the accessory name
(`S+4`, `S+0x58`). There is no free-running telemetry "stream" opcode after
`0xBD`: the device does not push `0xC3`/`0xDE` frames on its own. Instead
the UI producers set bits in `0x1FFF9550` (section 6) and the transmit
service emits one `0xC5`/`0xDE`/`0xE0`/... update per set bit when the host
link is up. That is the closest thing to a stream, and it is stopped by the
link going down (`S+3 = 0` stops the producers gating on it).

## 8. Internal MCU<->CH58x messages (node 3, and node 5 for accessories)

Direction MCU->CH58x is handled in the CH58x by `FUN_ram_0000388a`
(node 3 commands) and `FUN_ram_000045d4` (node 2 accessory commands),
confirmed by emu (`scripts/hostlink_ch58x_route_tests.py`). Direction
CH58x->MCU are the node-3 and node-5 frames the MCU consumes in `0x12F34`,
`0x13C40`, `0x13C88`, `0x14660`, `0x855C`, `0x15AA0`.

**MCU -> CH58x (node 3, MCU sends these):**

| Opcode | Sent by (main MCU) | When | CH58x reply | Effect on CH58x |
|---|---|---|---|---|
| `E0` | transmit svc `0x133BC` (`0xE0` path) | at boot, before `FD 03` | `E1` 31 bytes (`e1 MP305B.. 01 00 66 00 ...`) | returns BLE/CH58x device info |
| `FC * <8 name bytes>` | transmit svc when `0x1FFF9434` set | after first `E1` | `FD 03` | stores advertised name in DataFlash `0x6E00` |
| `50 00/01/02` | transmit svc | role change | `51 00` | 00 = advertise + USB on; 01 = radio/USB off; 02 = radio on, not advertising |
| `52 53` / `52 20` | transmit svc | enable/disable | `53 00` | `52 'S'` enables radio+USB, `52 ' '` disables both |
| `10` | transmit svc (`0xE0`-adjacent path) | periodic | `11 <4 bytes>` | time/uptime query (bytes at CH58x `0x20002FBC`) |
| `F0 AC` | transmit svc when bit 14 set, or `0x1FFFA00E == 1` | before a main-MCU reset, or update prepare | `F1 00` | enter CH58x update-prepare state |
| `55` | transmit svc | USB idle poll / keepalive | none | liveness probe |

Emu confirms every reply above byte-for-byte. `50` mapping verified by
hooking the CH58x advertising-enable and USB on/off calls: `50 00` ->
USB on + advertise; `50 01` -> USB off; `50 02` -> advertise off.

Who sends what on the MCU side and when: the transmit service `0x133BC`
sends `E0` and `FC` during the boot handshake (emu `test_boot_sequence`:
`E0` at ~0.5 s, `FC 2A ...name` twice, then `50 01`, `52 53`, then `10`
repeating). `50`/`52` are sent when the UI changes the radio/USB state
(the `DAT_1fffab1c`/charge paths set bit 0). `F0 AC` is sent while
bit 14 is set (`0x1CA60`, reset pending) or the update state `0x1FFFA00E` is 1. Bit 13 makes it send `E0` to the CH58x. `55` is the USB idle keepalive.

**CH58x -> MCU (node 3 unless noted; MCU consumes these):**

| Opcode | MCU handler | Meaning |
|---|---|---|
| `55 <a> <b>` | `0x133BC` reads it as the ack | link ack; `55 00 FF` = notify failed (retransmit), `55 FF 00` = queue full (poll+give up) |
| `51` | inline `0x1312E` (type 3, payload 0) | ack of `50`; clears `0x1FFF954B`, arms `1000` ms timer |
| `53` | inline `0x1313C` (type 3, payload 0) | ack of `52`; clears `0x1FFF954C` |
| `F1` | inline `0x30D8` (type 3) | ack of `F0`; `0x1FFFA00C+2`: 1 -> 2 |
| `FD` | inline `0x32C0` (payload 3 or `0xFF`) | companion status: 3 (ready) sets `0x1FFF9449=1`, calls `0xAE70(1)`, sets bit 13 (ask the CH58x for its identity with `E0`); `0xFF` (link down) clears `0x1FFF9449` and bumps `0x1FFF943C` |
| `E1` | `0x13C40` (type 3) | CH58x info reply; first time copies 4 bytes from record+0x11 to `0x1FFF9434..37`, later to `0x1FFF942C..2F` (twice) |
| `11` | `0x13C88` (fast path in RX cb) | time sync: 4-byte value at record+1, feeds the mAh integrator (`0x1FFE0160`) |
| `BD` type 6 | `0x14660` | Bluetooth host link state (`BD 01`/`BD 00`) |
| `BD` type 5 | `0x14660` | accessory link state + name |
| `BB` type 5 | `0x15AA0` | accessory scan list |
| `BE` type 5 | `0x855C` | accessory input event (wheel/keys) |

**The 4 bytes in the `E1` reply at record offset 0x11** (`0x13C40`,
decomp): the emulated CH58x `E1` reply is
`e1 4d 50 33 30 35 42 00 00 01 00 66 00 01 00 00 00 01 00 00 0f ...`
(model `MP305B` then version fields). `param_1` points at the opcode, so
`param_1+0x11` is payload byte 16; on
the emulated CH58x `E1` reply that is the 4 bytes `01 00 00 0f` (emu:
`0x1FFF9434..37 = 01 00 00 0f`). So `0x13C40` copies a CH58x
**firmware/version identifier** into `0x1FFF9434..37` (first) and
`0x1FFF942C..2F` (later). It is shown by the UI `0x57D54` via the format
`"%d.%d/%d.%d/%d.%d/%d.%d"`. It is a version/identity block from the CH58x,
not a BLE MAC. (The BLE MAC is handled entirely inside the CH58x, in its
adv-data path.) Corrected: firmware.md called this "four bytes ... not
named"; it is the CH58x version field.

**MCU -> CH58x accessory commands (node 2, `FUN_ram_000045d4`):** the MCU
builds `0xB8` (`0x18680`, request accessory list), `0xBA` (implicit),
`0xBC` (`0x185EC`, connect to a 6-byte accessory MAC), `0xBE` (disconnect).
These are sent by the transmit service on `0x1FFF9550` bits (the `0x2176C`
etc one-shot sends) when the "Bluetooth Accessories" UI asks to
scan/connect/disconnect. The CH58x answers `0xBB` (scan list) which comes
back as node 5.

**USB path (CH58x side).** The CH58x
USB interrupt `FUN_ram_00004fba` handles the HID endpoints; OUT reports
(report ID 1) are de-framed by `0x4E86` from byte 2 onward and fed to the
CH58x frame decoder `0x4BEC`, then routed by source nibble exactly like BLE
(emu `usb_out`: a `0x12` frame is forwarded verbatim on the UART to the MCU,
a `0x62` frame keeps its `0x31`). MCU replies destined for the USB host
(destination nibble 1, i.e. address `0x21`) are chunked by the CH58x queue
`0x3E1A` into 62-byte pieces and sent as report ID 2 `[02, count, <=62
bytes]` (emu `mcu_frame`: a 125-byte `D9` frame becomes three IN reports).
**The main MCU uses destination nibble 1 for USB replies** (it just swaps
the request's source nibble 1 into the destination), so from the MCU's side
USB and BLE are identical except for the nibble; all USB-specific framing
(report IDs, 62-byte chunking, `AA` handling) is in the CH58x.

## Comparison with docs/research

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
