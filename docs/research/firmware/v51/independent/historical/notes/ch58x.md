> Historical source note. Superseded by the reviewed notes and corrections
> in the recovery README. Workflow instructions here describe the old pass.

# CH58x companion: BLE, USB HID and the bridge to the main MCU

Image: `bin/ch58x.bin` (`data.bin[0xB000:]`, firmware 1.6.0.51 update), WCH
CH58x (RV32IMAC), linked at `0x1000`. All addresses are absolute processor
addresses. RAM copies: highcode `0x1008..0x1C48` to `0x20002000`, `.data`
`0x9318..0x9628` to `0x20002C40`, BSS `0x20002F50..0x20006DF0` zeroed at
reset. GP is `0x200023B8` (set at `0x1C48`), SP `0x20007800`.

Evidence tags used below:

- **[D]** read from the Ghidra decompilation (`out/ch58x_decomp.c`, plus a
  re-export with the missed functions, see "Method").
- **[A]** checked in the disassembly (`scripts/ch58x_dis.py`).
- **[E]** confirmed by running the original code in Unicorn
  (`scripts/ch58x_emu.py`, checks in `scripts/ch58x_bridge_checks.py`). The
  BLE library, DataFlash and peripherals are simulated, so [E] proves what
  this image's code does with the inputs given, not what the library does.
- **[I]** inferred; the reason is given.
- **[M]** read from the main MCU image (`out/app_decomp.c`) to explain the
  other end of a CH58x message.

## Method

- Ghidra missed the GATT callbacks and several callback-table entries. A copy
  of the project (scratchpad, never the shared one) was processed with
  `scripts/ch58x_BridgeFix.java`: it adds functions at `0x2AB6`, `0x2B38`,
  `0x2D8C`, `0x2E28`, `0x2F58`, `0x56C0`, `0x56C2`, `0x56FE`, `0x698C`,
  `0x6C76`, `0x6CAE`, `0x7104`, labels the library jump table at
  `0x40000..0x402FF` with the names from
  `~/mp305b/docs/research/firmware-v51/wch-sdk-api.tsv`, and re-exports C.
- WCH API names and parameter IDs were taken from the official
  `CH58xBLE_ROM.h` v1.8 (copy in
  `~/mp305b-firmware-scratch/2026-09-29/reference/`), which matches the
  library version string the image checks (`0x32B6` compares `VER_LIB` with
  `CH58x_BLE_LIB_V1.8` and hangs on mismatch [D]).
- Important library convention: `tmos_memcmp` returns TRUE (non-zero) when
  the buffers are EQUAL. Several branches read backwards otherwise.
- `scripts/ch58x_emu.py` maps the image, the RAM copies, a fake library jump
  table with Python stubs (memcpy, memset, memcmp, GATT_bm_alloc,
  GATT_Notification, GATTServApp_ReadCharCfg, GAPRole_GetParameter), a
  DataFlash model behind `FLASH_EEPROM_CMD` (`0x200028D6`) and captures
  UART1 TX bytes. `scripts/ch58x_bridge_checks.py` runs every scenario quoted
  as [E] below and prints the bytes.

## Image identity and version

Vector words at flash `0x1020` and `0x1024` (RAM `0x20002018`, `0x2000201C`)
both point to an identity block at `0x8ED0` [A], the same scheme as the main
application's identity block:

| Address | Bytes | Meaning |
|---|---|---|
| `0x8ED0` | `33 CC 55 AA` | magic `0xAA55CC33` |
| `0x8ED4` | `4D 50 33 30 35 42 00 00` | "MP305B" |
| `0x8EDC` | `01 00 66 00` | second identity word; the main image has its hardware revision in this position. Meaning here not established [I] |
| `0x8EE0` | `01 00 00 0F` | CH58x firmware version **1.0.0.15** |
| `0x8EE4` | `00 10 00 00` | `0x00001000`, the image load address [I] |
| `0x8EE8` | `00 90 03 00` | `0x00039000`, end of the application area [I] (0x38000 = 224 KB above 0x1000) |

The version is confirmed by the `E0` reply the CH58x sends to the main MCU
(bytes 17..20 = `01 00 00 0F`, [E]); the main MCU copies exactly those four
bytes (`0x13C40`, request offset `0x11`) [M]. The word at flash `0x1004` is
`0x00009308` (WCH startup normally has 0 there); purpose not established.

The CH58x version is never sent to a BLE or USB host. The `E1` a host sees is
built by the main MCU (section "Comparison").

## Startup, tasks and timing

`main` = `0x7794` [D]: `SetSysClock(0x48)` (PLL 60 MHz), GPIO defaults
(all unused pins pull-down), PB7 output high, UART0 init, BLE library init
(`0x32B6`), HAL init (`0x33D0`), `GAPRole_PeripheralInit`,
`GAPRole_CentralInit`, peripheral app init (`0x72E0`), central app init
(`0x5744`), then the TMOS loop.

`bleConfig_t` built at `0x32B6` [D]:

| Field | Value |
|---|---|
| MEMAddr / MEMLen | `0x20005160` / `0x1C00` |
| SNVAddr | `0x7E00` (DataFlash offset; bond storage, used by the central role, and by the peripheral if a host ever pairs) |
| BufNumber / BufMaxLen | 5 / 251 (ATT MTU at most 247) |
| TxNumEvent | 1 |
| TxPower | `0x3D` = LL_TX_POWEER_6_DBM (+6 dBm) |
| SelRTCClock | 2 (LSI calibrated to 32768 Hz) |
| ConnectNumber | `0x0D`: 1 peripheral link, 3 central links |
| MacAddr | read from the ROM info area `0x7F018` (`FLASH_EEPROM_CMD(6, 0x7F018)`), the factory MAC |
| callbacks | srand `0x275A`, sleep `0x34A6`, temperature `0x31B8`, LSI calibration `0x3156`, flash read `0x315C`, flash write `0x3178` |

TMOS tick is 625 us (1600 ticks per second) [I, WCH convention].

| Timer / event | Period | Work |
|---|---|---|
| Peripheral task event `0x800` | 2 ticks (1.25 ms) | `0x4BB8`: runs the bridge (`0x4B9C`) when the 1 ms flag is set, the LED decoder every 10 ms, the update countdown every 100 ms |
| Peripheral event `0x100` | 16 ticks (10 ms) | writes `R8_WDOG_COUNT = 0` (watchdog feed; `0x2764(1)` enables watchdog reset) |
| Peripheral event `0x002` | 1600 ticks (1 s) | name patching, bind timeout |
| Peripheral event `0x008` | once, 6400 ticks (4 s) after a host connects | connection parameter update request |
| TMR1 | 60000 cycles = 1 ms | `0x3724`: 1/10/100/500/1000 ms flags |
| TMR2 | 6000000 cycles = 100 ms | `0x20002FBC += 100` (uptime in ms) |
| TMR0 | capture, timeout 6000 cycles | LED pulse capture (section "RGB LED") |

The bridge therefore runs about every 1.25 ms, not in interrupt context.
Frames from the MCU are parsed inside the UART1 interrupt; USB OUT reports
are parsed inside the USB interrupt.

## Pins and peripherals

| Function | Pin | Evidence |
|---|---|---|
| UART1 RX from main MCU | PA8 (input pull-up) | `0x4DDC` [D] |
| UART1 TX to main MCU | PA9 | `0x4DDC` [D] |
| UART0 TX (debug, unused) | PB7 | `0x7794`, `0x2812` [D] |
| USB D-/D+ | PB10/PB11 (pull-down when USB is off) | `0x566A` [D] |
| LED red (PWM4) | PA12 | `0x4810`, `0x4916` [D] |
| LED blue (PWM7) | PB4 | same |
| LED green (PWM10) | PB14 | same |
| LED data input (TMR0 capture, remapped) | PB23 | `0x4810` (`GPIOPinRemap(RB_PIN_TMR0)`) [D] |

UART0 and UART1: 115200 baud, 8 data bits, no parity, 1 stop bit
(`0x27E2`/`0x286E` compute the divider from the system clock, LCR = 3) [D].

## Bridge architecture

### Framing

The CH58x uses the same framing as the main MCU [D, A, E]:

```
AA  addr  len  data[len]  sum
addr = (hi << 4) | lo        sum = (addr + len + data...) & 0xFF
every AA after the leading one (addr, len, data, sum) is sent twice
```

- Encoder `0x35A8`: input struct `{u8 hi; u8 lo; u16 len; u8 data[]}`, only
  the low byte of `len` is emitted; the loop counter is 8-bit, so a length of
  256 or more never terminates [D]. Frame buffers are 256 bytes.
- Decoders: `0x3662` (one instance per slot, used for USB OUT) and `0x4BEC`
  (single instance for the UART from the MCU). Same state machine: a lone
  `AA` (odd count) starts a frame; next byte gives `hi`/`lo`; length byte 0
  is rejected; after `len` data bytes the checksum must match or the frame is
  dropped silently [D, E].

The high nibble is the source and the low nibble the destination. The CH58x
routes on the low nibble only. The main MCU replies with the nibbles swapped
(`0x12F34` copies request `lo`/`hi` into reply `hi`/`lo`) [M].

### Channel table

| Nibble | Meaning |
|---|---|
| 1 | USB HID host |
| 2 | main MCU |
| 3 | the CH58x itself (control) |
| 5 | BLE accessory (CH58x central role) |
| 6 | BLE host (CH58x peripheral role, AF01/AF02) |

Direction CH58x to main MCU (UART1 TX), all verified [E]:

| addr | Source | Content |
|---|---|---|
| `0x62` | BLE host writes, plus `BD` link state | GATT write payload + route tag (`0x31` AF01, `0x00` AF02) |
| host's own byte, normally `0x12` | USB host | the host frame, decoded and re-encoded unchanged |
| `0x52` | accessory | `BB` list, `BD` accessory state, `BE` buttons/wheel |
| `0x32` | CH58x control replies | `01`, `11`, `51`, `53`, `E1`, `F1`, `FD`, and the `55` status frame |

Direction main MCU to CH58x (UART1 RX), routed by `0x4CEE` [D, E]:

| Low nibble | Handler | What happens |
|---|---|---|
| 6 (`0x26`) | `0x3FAC` | BLE notification on AF01 or AF02 |
| 1 (`0x21`) | `0x3D8A` | re-encoded and queued for USB IN |
| 5 (`0x25`) | `0x45D4` | accessory commands `B8`, `BA`, `BC`, `BE` |
| any other (MCU uses `0x23`) | `0x388A` | CH58x control commands |

### Slots and scheduler

Four slots of `0x218` bytes at `0x20003A50` [D, A]:

| Slot | Base | Use |
|---|---|---|
| 0 | `0x20003A50` | BLE to MCU frame (`hi=6, lo=2`), pending flag `0x20003C58` |
| 1 | `0x20003C68` | USB OUT decoder and frame, ready flag `0x20003E70`; `+0x104` holds MCU frames for USB |
| 2 | `0x20003E80` | accessory to MCU frame (`hi=5, lo=2`), pending flag `0x20004088` |
| 3 | `0x20004098` | control replies; `+0x104` (`0x2000419C`) holds control frames from the MCU |

Each slot is `{frame A (0x104), frame B (0x104), u8 ready, u32 state, u8 index, u8 sum, u8 aa_count}`.
Frames from the MCU are copied into frame B of the slot chosen by the low
nibble (`0x3862(n)` = slot n + `0x104`).

Bridge loop `0x4628`, one pass per tick, in this order [D, A]:

1. Frame from MCU for BLE: route to AF01/AF02 (`0x3FAC`).
2. Frame from MCU for USB: queue for USB IN (`0x3D8A`).
3. Frame from MCU for the accessory: `0x45D4`.
4. Control frame from MCU: `0x388A`, which replies on UART1; return.
5. Otherwise, if a USB OUT report arrived (`0x20002F90`): forward the frame
   if one completed, else, if EP1 IN is idle, send the local partial-frame
   acknowledgement (`0x3C48`). If EP1 IN is busy, return without clearing
   the flag, which stalls steps 6 and 7 until the host reads IN [A].
6. Otherwise forward the pending BLE frame (slot 0), else accessory frame
   (slot 2), else slot 3.
7. Otherwise, if any frame from the MCU was handled since the last status
   (`0x20002F95`), send the status frame `55`.

Each slot is a single mailbox. A second frame to the same slot before the
loop runs overwrites the first. There is no queue except for USB IN.

### Flow control toward the MCU: the `55` status frame

Built at `0x4730` [D, E]:

```
AA 32 03 55 <q> <n> <sum>
q = 0xFF when the USB IN queue holds 4 or more frames, else 0x00
n = 0xFF when the last AF01/AF02 notification failed (0x20002F88), else 0x00
```

Main MCU side (`0x1EF5C` receive, `0x133BC` scheduler) [M]:

- After sending any frame to the CH58x the MCU marks the link busy and waits
  for a `55` from source 3. `55` clears busy.
- `q = FF`: the MCU polls with a one-byte frame `55` (`AA 23 01 55 ..`) every
  100 ms, at most 49 times, then gives up on the USB session.
- `n = FF`: the MCU retransmits its last frame every 100 ms, at most 49 times
  (about 5 s).
- No `55` within 5 s: the MCU retransmits the last frame.

The CH58x answers every frame from the MCU with exactly one `55` (after any
direct reply), including frames it ignores [E]. A `55` sent by the MCU is a
poll: it is not handled by `0x388A` but still triggers a `55` reply.

## BLE peripheral role (host link)

### Advertising

Configured in `0x72E0` [D]:

- Advertising starts disabled (`GAPROLE_ADVERT_ENABLED = 0`). It is enabled
  by the MCU command `52 53` ('S') or `50 00`, re-enabled after a host
  disconnects, and disabled by `52` with any other byte or by `50 02`.
- Interval: `TGAP_DISC_ADV_INT_MIN = TGAP_DISC_ADV_INT_MAX = 800`
  (x 0.625 ms = **500 ms**). Event type, channel map and filter policy are
  left at library defaults (connectable undirected, all channels) [I].
- Address: the factory MAC from the ROM info area (public) [I from config].
- `TGAP_ADV_SCAN_REQ_NOTIFY = 1`; the broadcaster callback struct at
  `0x20002FE0` is empty, so scan requests have no effect.
- Preferred connection interval (`GAPROLE_MIN/MAX_CONN_INTERVAL`) 6 and 40
  (7.5 ms to 50 ms).

Advertising data, `0x20002E78`, 31 bytes [D, E]:

| Offset | Bytes | Meaning |
|---|---|---|
| 0 | `02 01 06` | Flags: LE General Discoverable, BR/EDR not supported |
| 3 | `03 02 00 AF` | Incomplete list of 16-bit service UUIDs: `0xAF00` |
| 7 | `17 FF` | Manufacturer specific data, 22 bytes |
| 9 | `BA AB` | Company ID `0xABBA` (little endian) |
| 11 | `AF FA` | fixed in the image |
| 13 | 4 bytes | set by the MCU command `FC` (bytes 10..13 of the `FC` frame). Image default `01 35 02 00`; the 1.6.0.51 main image always sends `01 35 02 00` [M] |
| 17 | 14 bytes | set by a host through AF01 opcode `10` or `C0`, stored in DataFlash `0x6E00..0x6E0D` and reloaded on `FC`. Default zero |

Only RAM is changed for the 4 `FC` bytes; they are re-sent by the MCU at each
boot. The 14-byte tail is persistent.

Scan response, `0x20002E98`, 31 bytes: `1E 09` + 29-byte complete local
name. Template `"0030MP305B" 00 00` + 17 spaces [D]. Patched at run time
(name index = byte offset minus 2) [D, A, E]:

| Name index | Source | Value |
|---|---|---|
| 0..1, 3 | template | `'0'` |
| 2 | 1 s event `0x6CB0` via `0x47FE` | `'3'` if RAM `0x200043B7 == 0xA5`, else `'0'` |
| 4..11 | DataFlash `0x6E0E..0x6E15` if programmed (not all `FF`) | the 8-byte name sent by the MCU in `FC`: `"MP305B  "` (two spaces) |
| 12 | 1 s event | `'S'` when remote is enabled (`0x20002F8A`) and BLE is not blocked (`0x20002F89 != 2`), else space |
| 13..25 | template | spaces |
| 26..28 | state STARTED callback `0x7106` | three characters derived from the BD address |

Suffix formula (`0x7190`, [A, E]): with `b0..b5` the address as returned by
`GAPROLE_BD_ADDR` (WCH order, least significant byte first [I]):

```
v = (b0 ^ b1) << 24 | (b2 ^ b3) << 16 | b4 << 8 | b5
name[26] = '!' + v % 94
name[27] = '!' + (v / 94) % 94
name[28] = '!' + (v / 8836) % 94
```

`0x200043B7`: never written anywhere in this image (no direct reference, no
computed address found in a full linear disassembly, not inside the BLE
library heap `0x20005160..0x20006D60`), and it is zeroed by startup. So the
name always carries `'0'` at index 2 and the device always advertises
`0000...` once the 1 s event has run [D, A]. What `0xA5` was meant to signal
is unknown [I]; a unit advertising `0030...` would fail WebLink's
`0000MP30` name filter.

The scan response is pushed to the stack only when a patched character
changes, or when the DataFlash name is present (then every second) [D].
Before the first 1 s event the template (`0030...`, no suffix) is in use,
but advertising is normally still off then.

### GATT database

Services are registered in this order: GAP and GATT (library), Device
Information `180A` (`0x3126`, 19 attributes), `AF00` (`0x2C6A`, 7), `DB00`
(`0x2EFC`, 4) [D]. Handles are assigned by the library. The capture's
handles (180A chars 15..31, AF01 34, AF02 37, DB01 41) fit this order with
the attribute counts below.

| Service | Attribute | Properties | Permissions | Value / behaviour |
|---|---|---|---|---|
| `180A` | `2A23` System ID | read | read | 8 bytes from `0x20002F68`, never written: zeros |
| | `2A24` Model Number | read | read | "Model Number" |
| | `2A25` Serial Number | read | read | "Serial Number" |
| | `2A26` Firmware Revision | read | read | "Firmware Revision" |
| | `2A27` Hardware Revision | read | read | "Hardware Revision" |
| | `2A28` Software Revision | read | read | "Software Revision" |
| | `2A29` Manufacturer Name | read | read | "Manufacturer Name" |
| | `2A2A` IEEE 11073 cert | read | read | `FE 00` "experimental" (14 bytes) |
| | `2A50` PnP ID | read | read | `01 D7 07 00 00 10 01` (SIG source, VID `0x07D7` WCH, PID 0, version `0x0110`) |
| `AF00` | `AF01` | `0x1A` read, write, notify | read, write | see below |
| | `2902` CCCD | | read, write | `0x20003224` |
| | `AF02` | `0x1A` read, write, notify | read, write | see below |
| | `2902` CCCD | | read, write | `0x20003014` |
| `DB00` | `DB01` | `0x1A` read, write, notify | read, write | inert, see below |
| | `2902` CCCD | | read, write | `0x20003434` |

- The 180A strings are the WCH SDK placeholders [D]; the read callback
  `0x2F58` supports offsets (long reads).
- No `FEE0` or other OTA service exists in this image [A: no `E0 FE` bytes].
- AF01/AF02 reads (`0x2AB6`) always return 20 bytes of buffers that nothing
  writes (zeros). A read with an offset returns `ATT_ERR_ATTR_NOT_LONG`.
- No characteristic declares write-without-response or indicate. No
  attribute needs authentication, encryption or authorisation, so pairing
  is not required. The bond manager allows pairing if a central asks
  (wait for request, MITM on, display-only I/O, bonding on, passcode 0); no
  peripheral bond callbacks are registered (`0x20005140` is zeroed BSS).
- CCCDs: writes go through `GATTServApp_ProcessCCCWriteReq`; the app
  callback receives events 1/2 but ignores them. Both AF CCCDs (and DB01's)
  are reset when the link is removed (`0x2C02`, `0x2E9E`), so a host must
  enable notifications on every connection.
- DB00/DB01: the write hook (`0x6CAE`) and read hook (`0x7104`) are empty
  functions; the value buffer is never written; nothing ever notifies on
  DB01 [D]. A DB01 read returns whatever length the library passes in
  (probably 0) [I].

### MTU and data length

The app never starts an MTU exchange for the host link. The library accepts
up to ATT MTU 247 (BufMaxLen 251) [D]. The host decides; macOS negotiated
247 in the captures.

### Connection handling

- One host link at a time (ConnectNumber). A second link established while
  `0x20002FFC != 0xFFFE` is terminated at once with its own handle
  (`0x7106`) [A]. The 30 s timer is zeroed before that check, so a second
  connection attempt restarts the timer of the existing link [A].
- On link established: the handle, interval, latency and timeout are
  stored, the 30 s timer (`0x20002FF0`) is zeroed, and 4 s later the CH58x
  requests interval 7.5 to 50 ms, latency 0, supervision timeout 5 s
  (`GAPRole_PeripheralConnParamUpdateReq(h, 6, 40, 0, 500)`) [D].
- **Bind timeout:** every second while the role state is CONNECTED the timer
  grows by 1600; when the bind state (`0x20002FF4`) is 0 and the timer
  exceeds 47999 (30 s), the CH58x calls `GAPRole_TerminateLink` [D, A]. A
  host that has not received `19 00` within about 30 s of connecting is
  disconnected. Once bound, there is no timeout.
- On link terminated (callback in state ADVERTISING or WAITING): handle
  reset to `0xFFFE`, advertising re-enabled unless blocked (`0x20002F89 == 2`
  or remote disabled), reason stored at `0x20002FB0`, and in state
  ADVERTISING the bind state is set to 0 [D]. The CH58x does not reset the
  bind state when advertising stays off (a WAITING callback only) [D]; then
  no `BD 00` is sent [I, depends on library state reporting].
- Bind state changes are reported to the MCU by `0x42AC` as soon as slot 0
  is free: 2 gives `AA 62 03 BD 01 31 54`, 0 gives `AA 62 03 BD 00 31 53`
  [E]. Nothing is sent when a host that never bound disconnects, because the
  state stays 0.
- The MCU stores `BD` byte 1 as its connection type (`S+3` =
  `0x1FFFAACF`: 0 none, 1 BLE, 2 USB) and answers with `50 <type>` [M]. With
  type 1 the CH58x switches USB off (see "Interface arbitration").

### What a host writes: AF01

The AF service app callback `0x72A6` [A, E]:

```
event 3 (AF01 write): af01_handler(data + 1, (len - 1) & 0xFF, af01_notify)
event 4 (AF02 write): af02_handler(data,     len & 0xFF,       af02_notify)
```

The first byte of every AF01 write is discarded without being looked at.
WebLink's leading `0x12` is therefore required as a placeholder, but any
value works. The length is taken from the low byte only.

AF01 handler `0x4224` [D, E]:

| Condition | Action |
|---|---|
| `0x20002F89 == 2` (USB host active) | write dropped silently (ATT write still succeeds) |
| byte after the dropped one is `0x10` or `0xC0` | copies the next 14 bytes into manufacturer data offset 6..19, updates the advert, stores them at DataFlash `0x6E00`, replies `31 C1 00` on AF01. Not forwarded to the MCU. No length check (short writes copy stale bytes) |
| length 0 after dropping the first byte | ignored |
| anything else | forwarded as `AA 62 <len+1> <bytes> 31 <sum>` |

Example [E]: host writes `12 C4` to AF01, MCU receives `AA 62 02 C4 31 59`.

Warning: the `10`/`C0` path erases the whole DataFlash page `0x6E00` and
writes back only 14 bytes, so it also erases the 8-byte name override at
`0x6E0E` [E]. The name returns when the MCU sends `FC` again (at its next
boot). A client must never send opcode `0x10` or `0xC0` on AF01.

### What a host writes: AF02

AF02 handler `0x40DC` [D, E]:

| First byte | Action |
|---|---|
| any, when `0x20002F89 == 2` | dropped |
| `00` | local status reply on AF02, 13 bytes: `01`, gapRole state (low byte, 4 = connected), bind state (0 or 2), 30 s timer as u32 LE (1600 per second since connect), BD address (6 bytes as returned by `GAPROLE_BD_ADDR`) [E] |
| `18`, last byte of the write non-zero ("fast bind") | bytes 1..16 compared with the stored host IDs: match gives `19 00` and bind state 2; no match gives `19 FF` and bind state 0. Answered locally, not forwarded, no prompt [E] |
| `18`, last byte zero | bytes 1..16 copied to `0x20005130` (pending ID), then forwarded with tag `00` |
| anything else | forwarded as `AA 62 <len+1> <bytes> 00 <sum>` |

Examples [E]: `E0` gives `AA 62 02 E0 00 44`; the WebLink bind frame
`18 00 08*14 00 00 00` gives `AA 62 14 18 00 08*14 00 00 00 00 FE`.

Bind frame layout as the CH58x uses it: byte 0 `18`; bytes 1..16 the host
ID; the last byte of the write is the fast flag. Bytes in between are
ignored by the CH58x. With WebLink's 19-byte frame the ID is
`00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00` and the fast flag is 0.

Saving: when the MCU's reply to a forwarded bind is `19 00` (status byte
`0x20003B59` zero) and that notification was sent successfully, the pending
ID is stored (`0x7696`) and bind state becomes 2 [D, E]. Five IDs fit
(DataFlash `0x6F00`, 16 bytes each, all-`FF` = free). When all five are used
the oldest is dropped. A deny (`19 FF`) stores nothing.

### Notifications from the device

Router `0x3FAC` for frames from the MCU with destination 6 [D, E]. The MCU
appends the request's route tag as the last byte of every type-6 reply:

| Last byte | Notification |
|---|---|
| `0x31` | AF01: `31` followed by the frame bytes without the tag (same length as the MCU frame) |
| anything else | AF02: the frame bytes without the last byte |

Example [E]: MCU frame `AA 26 0D C5 5A ... 00 31 <sum>` gives AF01
`31 C5 5A 02 00 00 01 F4 01 32 00 00 00`.

- The `0x31` in front of AF01 notifications is the route tag moved to the
  front, not a device address.
- One MCU frame is one notification. There is no fragmentation. The
  notification is allocated with `GATT_bm_alloc(h, 0x1B, len)` and sent with
  `GATT_Notification`. If the CCCD for that characteristic is not enabled
  (`GATTServApp_ReadCharCfg & 1` is 0) or allocation or sending fails, the
  data is dropped and `0x20002F88 = 1` [D, E]. The next `55` then carries
  `n = FF` and the MCU retransmits for about 5 s. A reply longer than
  MTU - 3 cannot be delivered; what the library does in that case is not
  visible here [I].
- Replies to AF01 requests come back on AF01, replies to AF02 requests on
  AF02, unless an MCU handler writes a fixed `0x31` instead of echoing the
  tag (some update handlers do, firmware.md).

### Pacing on BLE

Slot 0 holds one frame. A write that arrives before the bridge forwards the
previous one (within about 1.25 ms plus UART time) replaces it [D]. Writes
with response, one outstanding request at a time, avoid this.

## USB HID

### Descriptors (flash `0x8F4C..0x8FBE`, [A])

Device descriptor `0x8F9C`: `12 01 00 02 00 00 00 40 E9 28 8A 02 00 02 01 02 03 01`
(USB 2.0, class at interface, EP0 64, VID `0x28E9`, PID `0x028A`, bcdDevice
2.00, iManufacturer 1, iProduct 2, iSerialNumber 3, one configuration).

Configuration `0x8F70` (41 bytes):
`09 02 29 00 01 01 00 C0 32` (self powered, 100 mA),
interface `09 04 00 00 02 03 00 00 00` (HID, no boot protocol),
HID `09 21 11 01 00 01 22 23 00` (HID 1.11, report descriptor 35 bytes),
`07 05 81 03 40 00 01` (EP1 IN interrupt 64, 1 ms),
`07 05 01 03 40 00 01` (EP1 OUT interrupt 64, 1 ms).

Report descriptor `0x8F4C` (35 bytes):
`05 01 09 00 A1 01 85 01 09 01 15 00 25 FF 75 08 95 3F 91 82 85 02 09 02 15 00 25 FF 75 08 95 3F 81 82 C0`
(Generic Desktop, usage 0, application collection; report 1: 63 bytes
output; report 2: 63 bytes input). The top-level usage is 0, not 4.

String descriptors (`0x4FBA` GET_DESCRIPTOR) [D]:

| Index | Content |
|---|---|
| 0 | `04 03 09 04` (US English), `0x9304` |
| 1 | "wch.cn", `0x8FB0` |
| 2 | RAM `0x20002E44`: "MP305B" by default; rebuilt by `0x54FA` each time USB is enabled from the DataFlash name override (`0x6E0E`, up to 8 characters, cut at the first `00` or space) |
| 3 | not handled: the request is stalled. There is no USB serial number although the device descriptor names index 3 |

Other control handling: standard requests only; any class or vendor request
(bmRequestType bits 5..6 set, for example SET_IDLE, GET_REPORT, SET_REPORT)
is stalled [D]. Reports must go through the interrupt endpoints. EP2..EP4
have WCH sample handlers that echo inverted data, but they are not in the
configuration descriptor.

### OUT reports (host to device)

`0x4E86` on an EP1 OUT with a valid toggle [D, E]:

```
packet: [0] report ID (not checked)  [1] n  [2 .. 2+n-1] stream bytes
```

The `n` stream bytes are fed to the slot 1 decoder (`0x3662`). `n` is not
checked against 62 or against the received length. The stream is the stuffed
frame `AA addr len data sum`, split over as many reports as needed, any `n`
from 1 to 62 per report. WebLink's 61-byte stride is one valid choice.

When a frame completes with a good checksum, the bridge re-encodes it
unchanged (same address byte, same checksum) and sends it on UART1 [E]. A
bad checksum is dropped silently [E]. The CH58x adds no route tag to USB
frames and does not look at the address nibbles. The host must use
`0x12` (source 1 = USB, destination 2 = MCU): the MCU replies to the source
nibble, so a host using `0x62` gets its reply routed to BLE [E for the
forwarding, M for the reply rule].

Hazards [E]:

- Two frames in one report: only the last one reaches the MCU.
- A frame followed by the start of the next frame in the same report, or the
  next frame's first report arriving before the bridge has forwarded the
  completed frame (within about 1.25 ms): the decoder overwrites the
  completed frame, and the CH58x forwards a corrupted frame with a freshly
  computed, valid checksum. Example: `AA 12 01 C4 D7` + `AA 12 0C C8 01 02`
  in one report forwards `AA 12 0C C8 01 02 00 00 00 00 00 00 00 00 00 E9`.
  A client must start every frame in a new report and wait for the reply
  before sending the next frame.

Local partial-frame acknowledgement (`0x3C48`) [E]: after an OUT report that
does not complete a frame, if EP1 IN is idle and the frame being assembled
has opcode `20`, the CH58x itself sends IN `AA 21 02 20 04 47`; for opcode
`F4` it sends `AA 21 07 F5 00 d2 d3 d4 d5 01 <sum>` (d2..d5 are frame bytes
2..5). Other opcodes get nothing. These belong to the firmware update
commands and are described only as behaviour.

### IN reports (device to host)

Frames from the MCU with destination 1 are decoded (checksum checked),
re-encoded with stuffing (`0x3D8A`) and put into a 4-entry ring of 256-byte
buffers at `0x20003644` (lengths at `0x20003A44`) [D]. The pump `0x3E1A`
sends the head entry whenever EP1 IN is idle [D, E]:

```
report: [0] 02 (report ID)  [1] n (1..62)  [2 .. 2+n-1] stream bytes  [rest] 00
```

`n` is the number of valid stream bytes in this report, not a chunk counter
or a count of remaining reports. Up to 62 bytes per report; a remainder of
up to 62 goes in the last report. Example [E]: a 118-byte stuffed frame
arrives as `02 3E AA 21 ...` (62) then `02 38 ...` (56). The host must
concatenate the stream bytes, then de-stuff (pairs of `AA` to one `AA`) and
check the length and checksum. The address of replies is `0x21`.

The ring accepts a frame while fewer than 5 are pending, but has only 4
slots, so a fifth pending frame overwrites the oldest unsent one [D]. The
`55` status (`q = FF` at 4 pending) is what keeps the MCU from doing that.

### Bind on USB

The CH58x has no bind logic for USB: every valid frame is forwarded, and
nothing is answered locally except the two update acknowledgements above.
Any permission check is in the main MCU.

## Interface arbitration (BLE host versus USB host)

Commands from the MCU, `0x388A` [D, E], and what drives them [M]:

| MCU sends | CH58x does | MCU sends it when |
|---|---|---|
| `52 53` ('S') | remote enabled (`0x20002F8A = 1`), USB on if off, advertising on, `0x20002F89 = 0`; reply `53 00` | remote function enabled (`0x1FFFAB1C != 0`); retried every 1 s until `53` |
| `52` other (MCU uses `20`) | remote disabled, USB off, advertising off, `0x20002F89 = 0`; reply `53 00` | remote function disabled |
| `50 00` | `0x20002F89 = 0`; USB on if off and remote enabled; advertising on; reply `51 00` | connection type became 0 (BLE unbound or lost, or 8 s without USB traffic) |
| `50 01` | `0x20002F89 = 1`; USB off (device detaches); reply `51 00` | a BLE host became bound (`BD 01`) |
| `50 02` | `0x20002F89 = 2`; advertising off; all AF01/AF02 writes dropped; name loses `'S'`; reply `51 00` | a frame arrived from USB (source 1) |

Consequences: a bound BLE host disconnects the USB device; USB traffic stops
BLE advertising and silently discards BLE writes, even on a BLE link that is
already open; after 8 s without USB frames the MCU sends `50 00` and BLE
works again [M, D].

## Main MCU to CH58x control commands (destination 3)

Handler `0x388A`. Replies go to address `0x32` (swapped nibbles). All byte
strings verified [E].

| Request | Reply | Behaviour |
|---|---|---|
| `00` | `01 00` | none |
| `10` | `11 t0 t1 t2 t3` | u32 LE uptime in ms from TMR2 (100 ms steps). The MCU compares it with its own clock (`0x13C88`, ratio x 100000) every 10 s [M] |
| `50 m` | `51 00` | see "Interface arbitration" |
| `52 c` | `53 00` | see "Interface arbitration" |
| `E0` | 31 bytes, below | none |
| `EF 2A` / `EF 2C` | none | sets or clears `0x20002FB4`, which nothing reads; the 1.6.0.51 MCU does not send `EF` [M] |
| `F0 AC` | `F1 00` | CH58x update preparation (below); `F0` with another byte: no reply |
| `FC 2A name[8] m[4]` | `FD 03` | name override and manufacturer bytes (below); `FC` with another second byte: no reply |
| anything else | none | only the `55` status |

`E1` reply (CH58x's own identity):

| Offset | Bytes | Meaning |
|---|---|---|
| 0 | `E1` | opcode |
| 1 | `4D 50 33 30 35 42 00 00` | model "MP305B" |
| 9 | `01 00 66 00` | identity word 2 (see identity block) |
| 13 | `01 00 00 00` | unknown, constant |
| 17 | `01 00 00 0F` | CH58x firmware version 1.0.0.15 |
| 21 | `4D 50 33 30 35 42 00 00 00 00` | name, 10 bytes |

Full frame: `AA 32 1F E1 4D 50 33 30 35 42 00 00 01 00 66 00 01 00 00 00 01 00 00 0F 4D 50 33 30 35 42 00 00 00 00 98`.

`FC`: bytes 2..9 are an 8-byte name, bytes 10..13 go to manufacturer data
offset 2..5 (RAM only), then the 14-byte tail is reloaded from DataFlash and
the advert updated (`0x7532`). If bytes 2..5 are not all zero, the name is
written to DataFlash `0x6E0E` when it differs from the stored one (read 22
bytes, erase page, write 22 bytes, so the 14-byte tail survives) [D, E]. The
1.6.0.51 MCU sends `FC 2A 4D 50 33 30 35 42 20 20 01 35 02 00` [M].

`F0 AC`: sets `0x20002FB8 = 1` and a 100 ms countdown. On expiry (`0x4AB8`):
USB off, all interrupts masked, DataFlash `0x7000` byte 0 set to `03`
(page read, erase, write back 4 bytes), `FLASH_EEPROM_CMD(4)`, then
`RB_SOFTWARE_RESET` [D]. The reboot lands in the WCH jump IAP below `0x1000`
(not in the update), which presumably checks that flag [I]. A second `F0 AC`
while armed replies `F1 00` again without re-arming. The MCU sends it when
its update state `0x1FFFA00E == 1` and moves to state 2 on `F1 00` [M].

Startup handshake as seen from both sides [M, E]: MCU sends `E0` until it
gets `E1` (stores bytes 17..20), then `FC` (at most 21 attempts) until
`FD 03`, which marks the link established
(`0x1FFF9449 = 1`). Then `52`, `50`, the periodic `10`, and accessory
commands follow as needed.

## Channel 6 and channel 1 messages the CH58x creates itself

| Frame | When |
|---|---|
| `AA 62 03 BD 01 31 54` | BLE bind state became 2 |
| `AA 62 03 BD 00 31 53` | bind state went back to 0 (link lost after bind, or failed fast bind) |
| AF02 local replies (`01 ...`, `19 00`, `19 FF`), AF01 `31 C1 00` | see AF01/AF02 |
| USB `AA 21 02 20 04 47`, `AA 21 07 F5 00 .. 01 ..` | partial update frames |

## Accessory role (BLE central, channel 5)

Purpose: connect to a BLE HID mouse-type remote (buttons and wheel) and pass
its input to the MCU [D, E].

- Central parameters (`0x5744`): scan duration 4800 x 0.625 ms = 3 s;
  connection interval 10 to 50 ms; supervision timeout parameter 6000
  (x 10 ms = 60 s, outside the Bluetooth range; the library's handling is
  unknown [I]). Pairing: initiate, no MITM, display only, bonding on,
  passcode callback answers a random 6-digit number. More than 2 stored
  bonds at boot erase all bonds (SNV at DataFlash `0x7E00`).
- Scanning: general discovery, active scan, no white list; restarted after
  every discovery round and after link loss.
- Advertising report parser `0x65A0`: records AD types 1, 2/3 (16-bit UUIDs,
  stops at `0x1812` HID), 8/9 (name), `0x19` (appearance) and `0xFF`
  (manufacturer data) per device (up to 16 devices, 78-byte records at
  `0x20004C50`).
- Only devices with appearance `0x03C2` (HID mouse) matter. They go into the
  accessory list (5 entries: address, name) that the MCU reads with `BA`.
- Manufacturer data starting `BA AB BE EB` marks an ISDT accessory: if bytes
  4..7 are zero and the device is the stored accessory, the stored pairing is
  forgotten (DataFlash `0x6A00` erased); if they are non-zero, the device is
  kept only if it is the stored accessory and bytes 5..10 equal this CH58x's
  own MAC.
- Connect (`0x698C`, discovery done): to the first list device with
  appearance `0x03C2`, a name, address equal to `0x20002F30`, while remote is
  enabled. An ISDT accessory sets `0x20002FCF = 1`. A connection attempt is
  cancelled after 10 s.
- After connecting: MTU request 247, service discovery once bonded, then all
  characteristics: `2A4B` report map (read, parsed by `0x5864` for button and
  wheel byte offsets), `2A4E` protocol mode, every `2A4D` report with notify
  (up to 11 CCCDs enabled with `01 00`), and `AF02` on ISDT accessories
  (write handle and notify). Link update to 10..50 ms, latency 2, 5 s after
  2 s; RSSI read every 1.5 s.
- Address persistence: after discovery the address is written to DataFlash
  `0x6A01..0x6A08` (8 bytes from `0x20002F30`) when it changed; loaded at boot
  (`0x5710`).

Messages to the MCU (`hi=5`, address `0x52`) [E]:

| Frame data | Meaning |
|---|---|
| `BB n {addr[6] len name[len]} x n` | accessory list, answer to `BA` |
| `BD k name...` | accessory connected and discovered: k = 1 ISDT accessory, 2 other HID mouse |
| `BD 00` | accessory link lost |
| `BE b 00 00 00 00 00 w 00` | input report: b = button byte (bits 1, 2, 4), w = wheel byte (`01` or `FF`); sent when the buttons change or the wheel is non-zero |

Commands from the MCU (`AA 25 ..`): `BA 00` list request; `BC a0..a5` select
the accessory address; `BE` disconnect and invalidate the address (sets it
to `01 00 00 00 00 00`); `B8 B0` makes the CH58x write `F0 B0` to the
accessory's AF02 characteristic. The accessory AF02 notification `BE FF`
clears the stored address [D].

Every 15th `BA` while no BLE host is bound clears the accessory list [D].

## DataFlash layout and flash API

`0x200028D6` is the WCH ISP ROM API `FLASH_EEPROM_CMD(cmd, addr, buf, len)`
compiled into RAM [D]: commands 1/2/3 code flash erase/write/verify, 4 flash
ROM software reset, 6 read ROM info (MAC at `0x7F018`), 9 DataFlash erase
(256-byte pages), 10 DataFlash write, 11 DataFlash read. DataFlash offsets
are added to `0x70000` and must stay below `0x8000`.

| Offset | Size | Content |
|---|---|---|
| `0x6A00` | 8 (page 256) | accessory address at `0x6A01..0x6A06` (+2 junk bytes); byte `0x6A00` unused |
| `0x6E00` | 14 | manufacturer data tail written by AF01 `10`/`C0` |
| `0x6E0E` | 8 | name override written by MCU `FC` ("MP305B  " on 1.6.0.51) |
| `0x6F00` | 80 | 5 remembered BLE host IDs, 16 bytes each, `FF` = free |
| `0x7000` | 4 | IAP flag, byte 0 = `03` written before the update reset |
| `0x7E00` | library | SNV (bonds of the central role) |

## RGB LED and debug output

RGB LED [D]: TMR0 captures pulse widths on PB23 into `0x200043C0` (up to 104
words). Every 10 ms, after a capture timeout and at least 96 captures,
`0x4964` takes the high-level pulses shorter than 100 cycles (1.67 us at
60 MHz) and reads a bit as 1 when the pulse is longer than 40 cycles
(0.67 us). 24 bits form a GRB value, WS2812 style. `0x4916` then sets
PWM10 (PB14) = G, PWM4 (PA12) = R, PWM7 (PB4) = B, with inverted polarity
[I: `PWMX_ACTOUT(..., 1, 1)` selects Low_Level in the WCH API]. So the
CH58x emulates a WS2812 LED for whoever drives PB23 (the main MCU [I]).

Debug output: the strings (`GRB:(%d,%d,%d)`, `%d,%d,%d,%d\n`,
`------------%d,%d\n`, the HID report map analysis strings, `Data-%x:`,
`TypeRspAnalysis`, `ReadcentralCharHdl:%x\n`, `16-bit UUID: 0x%04X\n`,
`16-bit ad_type: %x\n`, `Manufacturer Data Len:%d\n`) go through newlib
`printf`, whose `_write` is the stub `0x8D8E` (errno 88, return -1). Nothing
writes the UART0 transmit register. UART0 is initialised on PB7 at 115200
but never transmits, and its interrupt is not enabled [D, E]. There is no
debug output on any pin.

## What a client must do (summary)

BLE:

1. Scan for name prefix `0000MP30` or manufacturer data `BA AB AF FA`; the
   last three name characters identify the unit.
2. Connect, enable notifications on AF01 and AF02 (every connection),
   request a large MTU (247 works).
3. Send the bind on AF02 within about 30 s: `18` + 16-byte ID + last byte 0
   for the prompt, or last byte non-zero for a silent check against the 5
   remembered IDs. Only `19 00` stops the 30 s disconnect.
4. AF01 writes: one placeholder byte (use `0x12`), opcode, payload. Never
   opcode `10` or `C0`. Replies arrive on AF01 prefixed with `31`.
5. AF02 writes: opcode, payload. Replies on AF02 without prefix.
6. One request at a time, write with response.
7. BLE writes are silently dropped while a USB host is active.

USB:

1. Output report 1: `[01][n][n stuffed stream bytes]`, n at most 62, one
   frame per report sequence, each frame starting in a new report, address
   `0x12`.
2. Input report 2: `[02][n][n stream bytes]`, concatenate, de-stuff in pairs,
   check length and checksum; replies use address `0x21`.
3. No serial number string; class requests stall; no bind.
4. The USB device disappears while a BLE host is bound.

## Comparison with docs/research

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
| Local name prefix `0000MP30` | Confirmed and explained: template `0030MP305B`, index 2 patched to `'0'` every second unless RAM `0x200043B7 == 0xA5` (never true) |
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

## Open items

- Meaning of identity word 2 (`01 00 66 00`) and of `E1` bytes 13..16.
- Why `0x200043B7 == 0xA5` would select `'3'`; nothing in this image sets it.
- Library behaviour for notifications longer than MTU - 3, for DB01 read
  length, and for the 60 s central supervision timeout value.
- WebLink's USB filter (usage 4) against the descriptor (usage 0): needs a
  USB connection (TBD-013).
- The unit ran main firmware 1.6.0.40 in the captures; this note describes
  the CH58x image shipped in the 1.6.0.51 update (CH58x 1.0.0.15). Whether
  the unit's CH58x runs the same version is not known.
