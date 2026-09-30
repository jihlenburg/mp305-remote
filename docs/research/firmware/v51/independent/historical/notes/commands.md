> Historical source note. Superseded by the reviewed notes and corrections
> in the recovery README. Workflow instructions here describe the old pass.

# Commands: dispatcher 0x12F34 and every opcode handler (app.bin, V1.6.0.51)

Area: "commands". All addresses are absolute processor addresses (app.bin is
linked at `0x10000`). `S` = `0x1FFFAACC` (live state), `K` = `0x1FFE0184`
(link/transmit control block), `GATE` = `0x1FFF9448` (transmit record; the
word at `GATE+0x108` = `0x1FFF9550` is the event/transmit flag word, called
`FLAGS` below), `P` = `0x1FFFA354` (program table), `PDT` = `0x1FFFA138`
(PD profile table), `PWR` = `0x1FFFA934` (power-stage block).

Evidence labels used here:

- **disasm**: read from the Thumb disassembly (`scripts/tdis.py`).
- **emu**: the original handler (and, unless noted, the real dispatcher
  `0x12F34` around it) executed in Unicorn on crafted input; the result is in
  the test-vector appendix. Emulation uses the flash image plus the RW init
  image with ZI zeroed and peripherals as plain RAM, and a Python model of
  the SPI NOR flash (hooks on `0x1BEF8` read, `0x1BF3A` program, `0x1BDC6`
  64 KB erase, `0x1BDF6` 4 KB erase).
- **decomp**: Ghidra output, cross-checked where it matters.
- **inferred**: meaning deduced from how a value is used; the reason is given.

Scripts (all in `~/mp305b-fw-re/scripts/`):

- `commands_emu.py`: helper around `emu_app.App`. `H.dispatch(req, typ)`
  places a request in channel record 0 exactly as the frame decoder does and
  runs the real dispatcher; `H.handler(addr, req, typ, shape)` calls a
  handler directly; `HT` adds call tracing and diffs over the state regions.
- `commands_vectors.py`: generates every test vector in the appendix
  (`.venv/bin/python scripts/commands_vectors.py [group ...]`, groups `c8 c6
  reads misc e2 e8 ee prog pd chreads maint deferred`).

## 1. Routes: what the "type" byte is

The main MCU talks to the WCH CH58x bridge over UART `0x4001D400`. The frame
decoder (main `0x15430`/`0x1FEDC` encode, `0x146B8` decode; CH58x
`ram:0x3662`) splits the frame's address byte into a high nibble (stored at
record `+0`) and a low nibble (record `+1`). The dispatcher calls the high
nibble the **type**. The reply is encoded with address `(record[1] << 4) |
record[0]`, so a request addressed `0x12` is answered from `0x21`, and a
request `0x62` from `0x26` (emu, wire bytes `AA 21 ...`, `AA 26 ...`).

| Type (high nibble) | Who sends it | Evidence |
|---|---|---|
| 1 | USB HID host. The CH58x decodes the HID reports (channel 1) and re-encodes the host's own frame unchanged onto the UART (`ram:0x4628` -> `ram:0x3DD2(1)`); main replies to destination nibble 1, which the CH58x routes back to USB (`ram:0x4628` -> `ram:0x3D8A(1)` -> USB IN queue `ram:0x3D0C`). WebLink's `0x12` gives type 1. | disasm/decomp of both images |
| 3 | The CH58x itself (system channel): heartbeat `55`, `E1` identity reply, acks `51`/`53`/`F1`, status `FD`. Main sends it `10`, `50`, `52`, `E0`, `F0 AC`, `FC 2A ...`. | decomp `0x133BC`, CH58x `ram:0x4628` |
| 5 | The CH58x BLE-central side (scan list `BB`, peer state and name `BD`, selection `BE`). Main sends it `B8 B0`, `BE` and the frames from `0x185EC`/`0x18680`. Replies to type 5 go to CH58x destination 5, whose handler `ram:0x45D4` only knows `B8`/`BA`/`BC`/`BE`, so ordinary replies to type 5 are dropped there. | decomp |
| 6 | Bluetooth LE host. `ram:0x4074` queues every AF01/AF02 write with address bytes `06 02` and appends a route byte: `31` for AF01, `00` for AF02. `ram:0x3FAC` strips it again. | decomp CH58x |

The type is not validated. A USB host that used another high nibble would be
treated as that route (for example `0x62` would be answered like BLE and the
reply would be sent to the BLE side).

**Host link byte `S+0x03`.** 0 = no host, 1 = a BLE host is bound, 2 = USB
host active (disasm/emu):

- Every type-1 request sets `S+3 = 2` and clears the USB idle counter
  `K+0x24` (`0x12FB6..0x12FCC`). This happens before the opcode switch, so
  even an ignored opcode keeps the link alive. On the first type-1 frame
  after another state it also stores the PD-chip VBUS word `0x1FFF9B54` in
  `K+0x20`.
- The dispatcher's tail (`0x1330A`), which runs on every call even without a
  frame, adds its `r0` argument (always 1, see section 2) to `K+0x24`.
  Above 8000 it sets `S+3 = 0` and clears `K+0x24`, `K+1`, `K+0x14`. It
  also drops the link when `0x1FFF9B9A == 0`, `0x1FFF9B54 < 3000` and
  `0x1FFF9B54 + 500 < K+0x20`. 8000 iterations take at least 8 s, so **a USB
  host that sends a frame at least every 8 s never loses the link** (emu:
  4000 + 4000 counted units keep `S+3 = 2`, one more clears it).
- The CH58x sends `BD 01` (type 6) when its bind state `0x20002FF4` becomes
  2 (a saved-host match, or a `19 00` from main passing through) and `BD 00`
  when it becomes 0 (`ram:0x42AC`; state 1 sends nothing). `0x14660`
  stores that byte in `S+3` (emu).
- `0x1E284` clears the remote-control grant `S+0x42` whenever `S+3 == 0`.

`S+3` also selects where **deferred and unsolicited** frames go: the transmit
service `0x133BC` addresses them to type 6 when `S+3 == 1` and to type 1 when
`S+3 == 2`, and drops them (clearing the flag bit) when `S+3 == 0` (emu,
section 11).

## 2. The dispatcher `0x12F34`

Called once per iteration of the `User_task` loop at `0x1F210` with `r0 =
1`, right after `vTaskDelay(1)` (`0x658D4(1)`, 1 kHz tick); the same loop
then runs the transmit service `0x133BC(1)`, the storage worker `0x1D380`
and the reboot countdown `0x12850`. All "millisecond" counters in this area
therefore count loop iterations of at least 1 ms. Four mailbox flags at
`0x1FFE01AC..0x1FFE01AF` (set by the UART receive path) select the channel
record `0x1FFF9660 + n*0x104`, first set flag wins, flag cleared.

Record layout: `+0` type (high nibble of the address byte), `+1` low nibble
of the address byte, `+2` length (u8, number of bytes from the opcode on,
including the type-6 route byte), `+4..` request, opcode first.

Registers at the switch (disasm `0x12F66..0x12FB0`): `r0` = request
(`record+4`), `r1` = reply buffer (`0x15FA4(1)+4` = `0x1FFF9F00`), `r2` =
type, `ip` = length, `lr` = opcode, `r3 = 0`, `r3 = 1000` on the path that
reaches `0x51`/`0x53` (`0x12FDE`).

### 2.1 Opcode map (all 256 values)

Compare chain (disasm `0x12FCE..0x1304C`) plus a `TBB` table at `0x1304E`
(35 byte entries at `0x13052`, index `opcode - 0xDC`, target
`0x13052 + 2*entry`):

| Opcode | Target | Call shape | Handler |
|---|---|---|---|
| `00` | `0x13076` -> `bl 0x1DFFC` | B | identity bytes |
| `18` | inline `0x13126` | none | bind request |
| `20` | `0x1311E` -> `bl 0x116A8` | B | block write |
| `51` | inline `0x1312E` | none | companion ack |
| `53` | inline `0x1313C` | none | companion ack |
| `A0` | inline `0x1307E` | none (builds reply) | language read |
| `A2` | `0x1309C` -> `bl 0x18368` | A | language write |
| `BB` | `0x132A8` -> `bl 0x15AA0` | C `(req, len)` | scan list |
| `BD` | `0x132B0` -> `bl 0x14660` | C `(req, len, type)` | link/peer state |
| `BE` | `0x132B8` -> `bl 0x1855C` | C `(req, len)` | peer selection |
| `C2` | `0x13150` -> `bl 0x158BC` | A | DC telemetry |
| `C4` | `0x1315C` -> `bl 0x15EF8` | A | settings read |
| `C6` | `0x13168` -> `bl 0x1CAA4` | A | settings write |
| `C8` | `0x13174` -> `bl 0x1B7F4` | A | DC control |
| `D0` | `0x13180` -> `bl 0x15BEC` | A | PD profile read |
| `D2` | `0x1318C` -> `bl 0x1C628`, then `S+0x4B = 1`, `0x1AEBC(0)` | A | PD profile write |
| `D4` | `0x1319A` -> `bl 0x15E48` | A | program list |
| `D6` | `0x131A6` -> `bl 0x1C8B8`, then `0x1FFFA8CC = 0`, `0x1AEBC(0)` | A | program header |
| `D8` | inline `0x131F0` | none | program read request |
| `DA` | `0x13236` -> `bl 0x1C73C`, then `S+0x4B = 1`, `0x1AEBC(0)` | A | program steps |
| `DC` | TBB -> `0x13248` -> `bl 0x1565C` | A | selected program |
| `DE` | TBB -> `0x13254` -> `bl 0x15694` | A | prog/PD telemetry |
| `E0` | TBB -> `0x130B2` -> `bl 0x1B634` | B | device info |
| `E1` | TBB -> `0x130CC` -> `bl 0x13C40` | A, no reply | companion identity |
| `E2` | TBB -> `0x13260` -> `bl 0x1B4D0` | A | program control |
| `E4` | TBB -> `0x1326C` -> `bl 0x15630` | A | active PD profile |
| `E8` | TBB -> `0x13278` -> `bl 0x1D520` | A | PD control |
| `EA` | TBB -> `0x13284` -> `bl 0x154AC` | A | charge settings |
| `EC` | TBB -> `0x13290` -> `bl 0x1555C` | A | charge telemetry |
| `EE` | TBB -> `0x1329C` -> `bl 0x13D44` | A | charge control |
| `F0` | TBB -> `0x130C4` -> `bl 0x1B7C4` | B | update mode |
| `F1` | TBB -> inline `0x130D8` | none | companion ack |
| `F2` | TBB -> `0x130F8` -> `bl 0x15118` | B (uses r0..r2) | update erase |
| `F4` | TBB -> `0x13100` -> `bl 0x1F508` | B (uses r0..r2) | update write |
| `F6` | TBB -> `0x13108` -> `bl 0x1F250` | B (uses r0..r2) | update verify |
| `FC` | TBB -> `0x13116` -> `bl 0x12400` | B | update commit |
| `FD` | TBB -> inline `0x13224` -> `0x132C0` | none | companion status |
| `FE` | TBB -> `0x130AA` -> `bl 0x1DB94` | B | factory reset |

Shape A: `mov r3, r2; mov r2, r1; mov r1, ip` -> `(request, length, reply,
type)`. Shape B: `mov r3, ip` -> `(request, reply, type, length)`. Shape C:
`mov r1, ip` only. Verified at every call site listed (disasm).

**Silently ignored** (no reply, no state change; emu for a sample of 28
opcodes): every other value, that is `01..17`, `19..1F`, `21..50`, `52`,
`54..9F`, `A1`, `A3..BA`, `BC`, `BF..C1`, `C3`, `C5`, `C7`, `C9..CF`, `D1`,
`D3`, `D5`, `D7`, `D9`, `DB`, and via the `TBB` table `DD`, `DF`, `E3`, `E5`,
`E6`, `E7`, `E9`, `EB`, `ED`, `EF`, `F3`, `F5`, `F7`, `F8`, `F9`, `FA`, `FB`,
`FF` (all to `0x131E4`, the no-reply tail). `0x1304A` (default) also goes
there.

No handler checks the request length. Handlers read their fixed offsets from
the channel record, so a short request is completed with bytes left over
from an earlier, longer request on that channel. The type-6 suffix is always
taken from `request[length-1]`.

### 2.2 Common reply path `0x131BC`

When the handler returns a nonzero length `n`: tx record `+2 = n`, `+1 =
type`, `+0 = record[1]`, `0x15430(1, rec, 0x1FFF944A)` encodes the frame into
`GATE+2`, its length goes to `GATE+0x102`, and `GATE+0 = 1` marks it
pending. The transmit service `0x133BC` sends it later. Length 0 means no
reply.

### 2.3 Tail processing on every call

- USB idle timeout and link drop (section 1).
- Retry timers for main-to-companion messages: `GATE+0x103` (set when main
  sent `50 xx`) and `GATE+0x104` (set after `52 xx`) count down the word
  `0x1FFF9440` (1000 iterations). On expiry `+0x103` clears `K+8` (resend `50`) and
  `+0x104` sets `FLAGS` bit 0 (resend `52`). `51 00` and `53 00` from type 3
  cancel them (they store 0 in `+0x103`/`+0x104` and 1000 in `0x1FFF9440`).
- If `K+9 > 20` (CH58x identity requests without answer) or `K+0xA > 20`
  (PD companion polls without answer, counted in `0x11EAC`), `S+0x56 = 1`
  (shown by the UI through `0x54818`).

## 3. Remote control (shared by `C8`, `E2`, `E8`, `EE`)

State: `S+0x42` grant (0/1), `S+0x45` request (0 release, 1 active, 2
requested), `S+0x03` host link, `FLAGS` bit 2 (deferred-reply mode). Each of
the four handlers has the same prologue and epilogue (disasm `0x1B804..0x1B84C`
and `0x1B932..0x1B988` for `C8`; `0x1B4E2..`/`0x1B5C2..` `E2`;
`0x1D532..`/`0x1D612..` `E8`; `EE` at `0x13D44`). With `rc` = payload byte 0
and `mode` the handler's own mode (0 `C8`, 1 `E2`, 2 `E8`, 3 `EE`):

1. `status = 0`. If `FLAGS` bit 2 is set, skip to the epilogue (this is the
   deferred-reply call, see below).
2. If `rc > 2` or `S+0x30 != mode`: `status = FF`, `S+0x45` is not written.
3. Else if `rc == 1` and `S+0x42 != 1`: `status = 1`, go to the epilogue.
4. Else `S+0x45 = rc`. For `rc` 0 and 2 go to "success" (`S+0x49 = 1`, or
   `S+0x4D = 1` for `EE`). For `rc == 1` apply the body (sections 5.x).
5. Epilogue, on the **stored** `S+0x45` (which may be a value left by an
   earlier command):
   - `S+0x45 == 2`: if `S+3 == 2` (USB) then `S+0x45 = 1`, `S+0x42 = 1`,
     reply `status`; otherwise **return length 0** (no reply).
   - `S+0x45 == 0`: `S+0x42 = 0`; reply 1 if `FLAGS` bit 2 is set, else
     `status`.
   - otherwise: reply `status` if `S+0x42 != 0`; if the grant is 0, reply 1
     when bit 2 is set, else `status`.
6. Reply `opcode+1, byte`, plus the route byte for type 6. Length 2 or 3.

What happens around it (decomp of the UI and transmit code, emu for the
transmit side):

- Over USB, `rc = 2` is granted immediately (`C9 00`), because the dispatcher
  has already set `S+3 = 2` (emu C8 #3).
- Over BLE, `rc = 2` leaves `S+0x45 = 2` and sends nothing. The UI sync
  worker `0x1E7B4` calls `0x5553C(S+0x45)`, which opens the remote-control
  prompt `0x5F434` (buttons `0x1FFE06AC` -> `0x5AF88` allow, `0x1FFE06B0`
  -> `0x5B034` deny, wired in `0x21A50`). Allow sets `S+0x42 = 1`, `S+0x45 =
  1`, `FLAGS |= 4`. Deny (when `0x1FFFAB10 == 0`, or `0x1FFFAB0F == 0` and
  `0x1FFFAB10 == 1`) sets `S+0x42 = 0`, `S+0x45 = 0`, `FLAGS |= 4`. If the
  prompt cannot be shown because another screen is active, `0x5553C` denies
  at once (`FLAGS |= 4`, grant and request 0).
- The transmit service then calls the handler for the **current mode**
  (`S+0x30` 0..3 -> `C8`/`E2`/`E8`/`EE`) with the two-byte request
  `opcode, 31` and type 6 (or 1 for USB), producing `C9 00 31` (allowed) or
  `C9 01 31` (denied), or `E3`/`E9`/`EF` in the other modes (emu, section
  11). Bit 2 is then cleared.
- While a BLE request is pending (`S+0x45 == 2`, `S+3 != 2`) **every**
  `C8`/`E2`/`E8`/`EE` returns no reply, whatever its payload (emu C8 #32).
- Releasing with `rc = 0` works only through the command of the current mode:
  `C8 00 ...` while in PD mode returns `C9 FF` and leaves the grant set (emu
  C8 #27). `rc = 0` without a grant returns status 0 (emu C8 #31).
- The grant is also cleared by `0x1E284` when `S+3 == 0`, by `0x1920C` when
  its hold counter reaches 100 in power states above 3 (inferred: power key
  held to switch off; it also sets `S+3 = 0`), by `0x36BB0` (boot) and by the
  deny callback.

## 4. Status codes

| Byte | Meaning |
|---|---|
| `00` | Accepted (or, for `rc` 0/2, request stored). Also the deferred "allowed" reply |
| `01` | Remote control not granted (`rc = 1` without grant), or the deferred "denied" reply |
| `FF` | Rejected: bad `rc`, wrong live mode, a field out of range, a fault, or the transfer-busy flag `S+0x4B == 1` |

Partial application: every handler validates and stores field by field.
Fields before the first bad one are stored, fields after it are not. Some
handlers also call setters before the later checks (section 5).

## 5. Handlers

Payload offset `n` = request byte `n+1` (the opcode is byte 0). "Suffix" is
the type-6 route byte copied from the last request byte.

### 5.1 `00`, `0x1DFFC` (shape B)

Reply `01 91 67 01`, length 4, plus suffix for type 6 (length 5). Constants,
no state read (disasm, emu). The meaning of `91 67 01` is not found in this
image.

### 5.2 `18` bind, inline `0x13126`; `19` built later by `0x12690`

`S+0x47 = 1` (bind pending), `K+6 = type`. No reply now (emu). The UI prompt
callbacks `0x2478C` (allow: `S+0x46 = 1`, `S+0x47 = 0`, `FLAGS |= 2`) and
`0x2483C` (deny: both 0, `FLAGS |= 2`) trigger the transmit service, which
calls `0x12690(buf, K+6)`: `19 00` if `S+0x46 != 0` else `19 FF`, and for type
6 a constant `00` suffix (route AF02). It then clears `S+0x46` and `S+0x47`
(emu: `19 00 00`, `19 FF 00` at address `26`). Payload bytes of `18` are not
read by main; the CH58x handles the saved-host lookup.

### 5.3 Language: `A0` inline `0x1307E`, `A2` `0x18368`

`A0`: reply `A1, [0x1FFFA0CE]` (+suffix). `0x1FFFA0CE` is the language byte
of the persistent configuration block `0x1FFFA0B8` (`+0x16`).

`A2`: payload 0 above 1 is forced to 0 (written back into the request).
Reply `A3 00` always. Only when the value differs from `0x1FFFA0CE`: store
it, then `0x1D858()` (charger stop) if `S+0x30 == 3` else `0x1AEBC(0)`
(output request off), then `0x1D958()` (save configuration, see 6.1) and
`S+0 = 1` (UI rebuild request, consumed by `0x1E284`). 0 English, 1 Chinese
(protocol.md; the image only knows 0/1). Emu: `A2 01` from language 0 turns
the output request off and saves; `A2 01` when already 1 changes nothing.

### 5.4 `C2` DC telemetry, `0x158BC`

Reply 37 bytes (38 with suffix). Every byte is copied, no conditions except
payload 31. Units come from the producers in section 7.

| Payload | Width | Source | Name | Unit and meaning |
|---|---|---|---|---|
| 0 | u8 | `S+0x02` | outState | 0 output off, 1 CV, 2 CC, 3 output voltage above setpoint (see 7.1) |
| 1 | u8 | `S+0x0E` | batteryState | 0 on battery, 1 external input charging the battery, 2 charging held (see 7.1) |
| 2 | u8 | `S+0x3A` | percentage | internal battery state of charge, % |
| 3 | u16 | `S+0xAC` | voltage | measured output voltage, 10 mV |
| 5 | u16 | `S+0xA8` | setVoltage | DC setpoint, 10 mV |
| 7 | u16 | `S+0xAE` | current | measured output current, 1 mA |
| 9 | u16 | `S+0xAA` | setCurrent | DC current limit, 1 mA |
| 11 | u32 | `S+0xD0` | workingTime | output-on time, s |
| 15 | u32 | `S+0xD4` | energy | output energy, 0.1 Wh |
| 19 | u16 | `S+0xB0` | power | output power, 10 mW |
| 21 | u8 | `S+0x12` | currentOver | 0 constant-current limit, 1 trip (OCP) after the OCP delay |
| 22 | u8 | `S+0x18` | realChange | bit 0 voltage, bit 1 current: front-panel knob edits apply live |
| 23 | u8 | `S+0x10` | voltageSlow | 0 step, 1 ramp at `slopeSteps` mV per 100 ms |
| 24 | u8 | `S+0x05` | output | 1 when the power stage output is on (actual, not requested) |
| 25 | u8 | `S+0x30` | model | live mode 0 DC, 1 program, 2 PD, 3 charge |
| 26 | u8 | `S+0x37` | voltageBoard | persisted UI entry-mode flag for the voltage field (default 1) |
| 27 | u8 | `S+0x38` | currentBoard | same for the current field (default 1) |
| 28 | u8 | `S+0x39` | temperature | signed int8 °C, the temperature the firmware protects the battery with |
| 29 | u16 | `S+0x9E` | chargeError | fault word, bits 0..8 (7.2) |
| 31 | u8 | `S+0x11`, or 1 when the word `0x1FFE02A0` is 0 | wavePause | 1 unless the device's own waveform page timer is running |
| 32 | u32 | `0x1FFFA980` | waveTime | output-on time in raw ms (uncalibrated counter behind workingTime) |

### 5.5 `C4` settings read, `0x15EF8`; also sent unsolicited (`FLAGS` bit 12)

Reply 12 (13 with suffix): `C5, S+0x2D perLimit, S+0x32 volume, S+0x2E
screenOff, S+0x33 shutdown, S+0x2F screenDirection, u16 S+0x96 slopeSteps,
u16 S+0x98 OCP delay, u16 S+0xA4 usbLine` (emu).

### 5.6 `C6` settings write, `0x1CAA4`

Order and bounds (disasm, emu at every bound):

| Payload | Check | Store |
|---|---|---|
| 0 perLimit | 80..100 | `S+0x2D` |
| 1 volume | 0..3 | `S+0x32` |
| 2 screenOff | 0..1 | `S+0x2E` |
| 3 shutdown | 0..30 | `S+0x33` |
| 4 screenDirection | 0..1 | **not stored** |
| 5 u16 slopeSteps | 0..1000 | `S+0x96` |
| 7 u16 OCP delay | 0..1000 | `S+0x98` |
| 9 systemCheck | 0..1 | `S+0x35` |
| 10 recover | 0..1 | `S+0x36` |
| 11 u16 usbLine | 0..1000 | `S+0xA4`, then `S+0x48 = 1` |

Reply `C7 00` or `C7 FF` (+suffix). No grant, mode or output check. The
deferred worker `0x128A4` normalises and applies the values when `S+0x48` is
set (covered by the settings analysis; not repeated here).

### 5.7 `C8` DC control, `0x1B7F4`

Request: `C8, rc, u16 voltage, u16 current, realChange, voltageSlow,
currentOver, output, model, refresh` (+suffix). Remote-control skeleton of
section 3 with mode 0. Body for `rc == 1` with grant (disasm
`0x1B84E..0x1B92E`):

1. If `model != S+0x30` (that is, not 0): `FF` if `model > 3`, if `S+0x4B ==
   1`, or if the output request `0x1FFFAA2E` is set; otherwise `S+0x31 =
   model` and success. No other field is read or stored (emu: `FFFF` setpoints
   ignored). `S+0x31` is the requested mode; the UI worker `0x54474` switches
   modes, see 6.2.
2. Same mode, in this order, stopping at the first failure:
   - voltage `<= 3050` -> `0x1AF64(voltage)` (target voltage `0x1FFFA940`,
     10 mV)
   - current `<= 5100` -> `0x1AEA4(current)` (current limit `0x1FFFA944`,
     1 mA)
   - realChange `<= 3` -> `S+0x18`
   - voltageSlow `<= 1` -> `S+0x10`
   - currentOver `<= 1` -> `S+0x12`
   - output `<= 1` and `S+0x4B != 1`: output 1: `FF` if the fault word
     `0x1FFFAA1E` is nonzero; if the output request was 0, `0x1CB8C(1)`
     (beep); then `0x1AEBC(1)`. Output 0: if the request was 1, beep; then
     `0x1AEBC(0)`.
   - refresh `<= 1`; 1 calls `0x1A5FC()` (reset energy and time counters).
   - success: `S+0x49 = 1`.

A `FF` after step "voltage" leaves the new voltage applied (emu C8 #8).
`setV`/`setI` only write the power-stage targets; `S+0xA8`/`S+0xAA` (the
values `C3` reports) follow within one UI tick (`0x1E284` calls `0x58268`
and `0x569B8` when they differ, only while the DC screen exists). The
`voltageSlow` and `currentOver` bytes reach the power stage through the UI
setters `0x558B0` and `0x56D80`, which also only act while the DC screen
object `0x1FFE034C` exists.

### 5.8 `D0` PD profile read, `0x15BEC`

`idx = (payload0 - 1) & 0xFF`, no range check (`D0 00` reads index 255, far
outside the table; emu returns zeros there). `n = 7` if the class byte
`0x1FFFA340[idx] < 0x65` else 9. Reply: `D1, payload0, 16-byte name
PDT[idx*16], class byte, n, n x 4 bytes from PDT+0xA0+idx*0x24` (+suffix).
Length 48 or 56 (49/57). The count `n` is derived from the class, not stored.

### 5.9 `D2` PD profile write, `0x1C628`

Request: `D2, id, name[16], class, count, save, count x 4 bytes` (+suffix).
`0x1FFFA8C5 = id - 1` always. If `id - 1 < 10`: name -> `PDT[idx*16]`, class
-> `0x1FFFA340[idx]`, then for group `g = 0..8`: `g < count` copies 4 bytes
to `PDT+0xA0+idx*0x24+g*4`; otherwise the low 3 bits (type code) of that
group's first u16 are cleared (group disabled). `count` above 9 is treated as
9. If `idx` equals the active profile `0x1FFFA34A`, `S+0x27 = 1` (re-apply).
If `save != 0`, `0x1FFFA8C4 = 1` (worker writes `PDT` to SPI `0x160000`).
Else `D3 FF` and `S+0x4B = 2`.

After the call the dispatcher always sets `S+0x4B = 1` and calls
`0x1AEBC(0)`: **every `D2`, accepted or not, requests the output off and
marks a transfer busy**. Only a completed flash save clears `S+0x4B` (worker
`0x1D380`). A `D2` with `save == 0` or a rejected `D2` therefore leaves
`S+0x4B = 1` until a later save, and while it is 1 the output and
mode-change parts of `C8`/`E2`/`E8`/`EE` return `FF` (emu: "D2 without save
flag leaves S+0x4B = 1").

### 5.10 `D4` program list, `0x15E48`

Reply `D5, count(P+0xB5)`, then for each id `k = 1..count`: the slot whose id
byte `P+0xAA+slot == k`: 16-byte name `P+slot*16` and step count
`P+0xA0+slot` (+suffix). Ids that are not contiguous from 1 are left out
(emu: a lone program with id 10 gives `D5 01` and no record).

### 5.11 `D6` program header, `0x1C8B8`

Request: `D6, id, name[16], steps, save, op` (+suffix). `id` must be 1..10,
else `D7 FF`. Finds the slot with that id, or takes the first free slot (id
byte 0), stores the id and increments the count. Copies the name and the
step count. `0x1FFFA8C7 = op`, `0x1FFFA8CB = slot`.

- `op == 1` and count not 0: delete. Count decremented, that slot's id and
  step count cleared, ids above it renumbered down by 1. If the deleted slot
  was selected, the program now having id 1 is selected (reload request).
- `save != 0`: `op == 2` sets `0x1FFFA8C6 = 1` (header saved now, busy flag
  kept until the steps are saved); any other op sets `0x1FFFA8C6 = 2` (header
  saved, busy flag cleared).
- `op == 0`, slot is the selected one and its step count is 0: reload
  request for that slot.

Reply `D7 00`. After the call the dispatcher clears the `DA` cursor
`0x1FFFA8CC` and calls `0x1AEBC(0)` (output request off).

### 5.12 `D8` program read, inline `0x131F0`; `D9` built later

`K+3 = 0` (chunk cursor). Scans the 10 id bytes for payload 0: found ->
`K+4 = slot`, `0x1FFFA8CA = 1`; not found -> `0x1FFFA8CA = 0` (and **no
reply ever**, emu). Always `K+5 = last request byte`. No immediate reply.
Worker `0x1D380` reads `0x4B0` bytes from SPI `0x162000 + slot*0x1000` into
`0x1FFF8F7C` and sets `FLAGS` bit 7. The transmit service calls `0x15CA0`
once per service cycle: `D9, id, up to 10 x 12-byte records` from cursor
`K+3`, advancing it; suffix `31` only on route type 6 (the request is
rebuilt as `D8, slot, K+5`, so the suffix is the saved route byte). Bit 7 is
cleared when the cursor reaches the step count. A program with 0 steps gives
one `D9 id`. The destination is the host link `S+3`, not the route the `D8`
came from (emu).

### 5.13 `DA` program steps, `0x1C73C`

Request: `DA, id, 10 x (u32 voltage, u32 current, u32 duration)` (+suffix).
`id` must be 1..**9** (`bVar1 < 10`), and a slot with that id must exist,
else `DB FF`. With `c = 0x1FFFA8CC` (cursor, cleared by every `D6`) and
`N` = the slot's step count:

- If `c >= N`: reply `DB 00`, nothing stored.
- Else read records 0..9 **regardless of the request length**. For each:
  voltage `<= 30500`; if current `<= 5100` then duration `<= 99990`, else
  duration must be 0 (a jump record, 6.3). A bad record: `DB FF`, `S+0x4B =
  2`. A good one is stored at `0x1FFF8F7C + c*12`, `c++`. When `c` reaches
  `N`: `0x1FFFA8C8 = 1` and **return 0 (no reply)**; the worker then writes
  the steps to SPI `0x162000+slot*0x1000`, sets `FLAGS` bit 8 and the
  transmit service sends the deferred `DB 00`.
- After 10 records without reaching `N`: `DB 00`.

The dispatcher then sets `S+0x4B = 1` and calls `0x1AEBC(0)`. So a
non-final chunk must contain exactly 10 records, and the final one is
answered later (emu: 3-step and 12-step uploads).

### 5.14 `DC` selected program, `0x1565C`; also unsolicited (`FLAGS` bit 9)

Reply `DD, id of selected slot, its step count` (+suffix), selected slot =
`P+0xB4`.

### 5.15 `DE` program/PD telemetry, `0x15694`

Reply 69 bytes (70 with suffix):

| Payload | Width | Source | Meaning |
|---|---|---|---|
| 0 | u8 | `S+0x02` | outState |
| 1 | u8 | `S+0x0E` | batteryState |
| 2 | u8 | `S+0x3A` | battery % |
| 3 | u16 | `S+0xAC` | measured voltage, 10 mV |
| 5 | u16 | `S+0xAE` | measured current, 1 mA |
| 7 | u32 | mode 1: u16 `S+0xC8` + two zero bytes; else u32 `S+0xD0` | mode 1: seconds elapsed in the current step; else output-on time s |
| 11 | u32 | `S+0xD4` | energy, 0.1 Wh |
| 15 | u16 | `S+0xB0` | power, 10 mW |
| 17 | u8 | `S+0x7C` (s16): 1 if negative else value + 1 | current program step, 1-based |
| 18 | u8 | `S+0x05` | output on |
| 19 | u8 | `S+0x30` | mode |
| 20 | u8 | `S+0x39` | temperature, signed °C |
| 21 | u8 | `S+0x20` | program paused or stopped (1), running (0) |
| 22 | u32 | `S+0xB8` (s32), 0 if negative | remaining jump repetitions |
| 26 | u8 | `S+0x1F` | PD: cable e-marker report present (inferred, 6.4) |
| 27 | u8 | `S+0x1E0` | PD e-marker field (raw `0x1FFF9B8F`) |
| 28 | u8 | `S+0x1E2` | PD e-marker field (low byte of `0x1FFF9B80`) |
| 29 | u16 | `S+0x1E4` | PD e-marker field (`0x1FFF9B82`) |
| 31 | u8 | `S+0x1E8` | cable voltage rating, V: 20, 30, 40 or 50 |
| 32 | u8 | `S+0x1E6` | cable current rating, A: 3 or 5 |
| 33 | u8 | `S+0x1EA` | cable power, W (20/28/36/48 V class x current) |
| 34 | u8 | `S+0x1EC` | raw `0x1FFF9B8A` |
| 35 | u8 | `S+0x1F0` | raw low byte of `0x1FFF9B38` |
| 36 | u8 | `S+0x1EE` | raw `0x1FFF9B8C` |
| 37 | u8 | `0x1FFF9B8E` | raw count byte of the e-marker report |
| 38..61 | 6 x u32 | `0x1FFF9B3C..0x1FFF9B50` | six raw 32-bit words from the PD companion's `E5` report (inferred VDOs) |
| 62 | u16 | `S+0x9E` | fault word |
| 64 | u32 | `0x1FFFA980` | output-on time, raw ms |

### 5.16 `E0` device info, `0x1B634` (shape B)

Layout selected by the route type only: **type 6 (BLE) -> short**, anything
else (USB type 1, companion types 3 and 5) -> long (disasm `0x1B65A`, emu for
types 1, 3, 5, 6). All constants are immediates in the code.

Short, 18 bytes: `E1, 01 06 00 33 (application 1.6.0.51), "MP305B" 00 00,
02 00 02 00 (hardware 2.0.2.0), suffix`.

Long, 31 bytes, no suffix: `E1, "MP305B" 00 00, 8 bytes at [word@0x1C] +
0x0C .. +0x13, 01 06 00 33, "MP305B" 00 00 00 00`.

The word at absolute `0x1C` is vector 7 of the missing main bootloader. The
application's own vector 7 (`0x1001C` = `0x0007AFC8`) points to its identity
block (`AA55CC33`, 8-byte id, hardware revision at `+0x0C`, version at
`+0x10`), and the update verifier `0x1FE0C` uses that same vector-7 pointer
to locate the magic in a staged image (5.26). So the long reply's bytes 9..16
are, **inferred**, the bootloader identity block's hardware revision (4) and
bootloader version (4). That gives exactly WebLink's USB field list: serial
8 (here the model string), hardware 4, bootloader 4, application 4, name 10.

### 5.17 `E1` from the companion, `0x13C40` (shape A, no reply)

Only type 3. The CH58x answers main's `E0` with the long layout, so request
bytes `0x11..0x14` are its application version. First reply (while
`0x1FFF9434 == 0`): stored at `0x1FFF9434..37`, `K+0 = 1`. Later replies:
`0x1FFF942C..2F` and a copy at `0x1FFF9430..33`. The UI (`0x57D54`) shows
them. Once `0x1FFF9434 != 0` the transmit service sends the CH58x `FC 2A "MP305B" 20 20
01 35 02 00` instead of `E0` (up to 20 times, counter `K+9`).

### 5.18 `E2` program control, `0x1B4D0`

Request: `E2, rc, action, output, model` (+suffix). Skeleton with mode 1.
Body (disasm `0x1B532..0x1B5BE`; this is the block Ghidra dropped):

1. `model != 1`: as in `C8` (`FF` if `> 3`, busy, or output requested; else
   `S+0x31 = model`).
2. `action <= 3` -> `S+0x4C`, else `FF`. The UI sync worker `0x127FC` turns
   it into a button press on the program screen and clears it: 1 previous
   step (`0x59638`), 2 pause/resume (`0x597C0`, toggles `S+0x20` and the
   step timer), 3 next step (`0x5934C`). 0 none.
3. `output`: `> 1` or `S+0x4B == 1` -> `FF`.
   - 1: `FF` if the selected program has 0 steps (`P+0xA0+[P+0xB4]`) or the
     fault word is set. If the output request is already on: success, nothing
     else. Otherwise `S+0x4C = 0`, `S+0x06 = 1` (start request), beep 1.
     `0x1E284` then calls `0x58BA4(1)`, the program runner start (6.3).
   - 0: if the output request is on: `S+0x4C = 0`, `0x1AEBC(0)`, beep 1. The
     runner is stopped by `0x1E284` when the output goes off (`0x58BA4(0)`).
4. Success: `S+0x49 = 1`.

Note that `E2` with `output = 1` never calls `0x1AEBC(1)` itself.

### 5.19 `E4` active PD profile, `0x15630`; also unsolicited (`FLAGS` bit 10)

Reply `E5, [0x1FFFA34A] + 1` (+suffix). `0x1FFFA34A` is `PDT+0x212`, the
active profile index; boot default 6 after a table reset (`0x188E0`).

### 5.20 `E8` PD control, `0x1D520`

Request: `E8, rc, u16 mask, sendPdos, output, model` (+suffix). Skeleton with
mode 2. Body (disasm `0x1D582..0x1D60E`, the second dropped block):

1. `model != 2`: as `C8`.
2. **Without any check**: `S+0x9C = mask` and `0x1FFF9BB9 = sendPdos`.
3. `output > 1` or `S+0x4B == 1` -> `FF` (the two stores above stay).
4. output 1: `FF` on fault. If the output request is on: success. Else if
   `0x1FFF9BB9 != 0` (that is, `sendPdos` was nonzero): success, nothing
   else. Else `0x1FFF9BB9 = 1`, `S+0x2A = 1`, `S+0x2C = 0`, beep 1.
5. output 0: if the output request is on, `0x1AEBC(0)` and beep 1.
6. Success: `S+0x49 = 1`.

Meaning (decomp of the consumers): `S+0x9C` is a 9-bit enable mask for the
PDO groups of the active profile. `0x12ADC` (UI tick) applies it when it
differs from the currently enabled set `S+0x9A` and is not 0: a set bit gives
group `g` its type code (1 for g 0..4, 2 for 5, 5 for 6, 3 for 7, 4 for 8), a
clear bit clears the type code; then `0x5735C` re-renders and `S+0x9C = 0`.
`0x1FFF9BB9 = 1` makes the PD link task `0x11EAC` send the companion `BC`
plus the nine groups (`0x11E3C`). `S+0x2A = 1` waits for the companion's
`BD` acknowledgement (`0x11900`), which sets `0x1FFF9BA3`; `0x11C18` then
calls `0x1AEBC(1)` and `0x1A5FC()`: **the PD output is switched on only after
the companion confirms**.

### 5.21 `EA` charge settings, `0x154AC`; also unsolicited (`FLAGS` bit 11)

Reply 21 bytes (22):

| Payload | Width | Source | Meaning |
|---|---|---|---|
| 0 | u8 | `S+0x1CA` | battery type (6.5) |
| 1 | u16 | `S+0x1C8` | charge voltage per cell, mV; for NiMH/Cd the -dV termination threshold, mV |
| 3 | u8 | `S+0x1C4` | cells |
| 4 | u16 | `S+0x1C6` | charge current, mA |
| 6 | u8 | `S+0x1CC` | last completed charge: type |
| 7 | u8 | `S+0x1CD` | last completed charge: cells |
| 8 | u32 | `S+0x1D0` | last charge: capacity, mAh |
| 12 | u32 | `S+0x1D4` | last charge: energy, mWh |
| 16 | u32 | `S+0x1D8` | last charge: duration, s |

The "last charge" fields are copied by `0x56244` when a charge ends, which
also sets `FLAGS` bit 11 (push `EB`) if a host is linked.

### 5.22 `EC` charge telemetry, `0x1555C`

Reply 31 bytes (32):

| Payload | Width | Source | Meaning |
|---|---|---|---|
| 0 | u8 | `S+0x0E` | batteryState |
| 1 | u8 | `S+0x3A` | battery % |
| 2 | u16 | `S+0xB4` | charge current, mA |
| 4 | u32 | `S+0xD8` | charged capacity, mAh |
| 8 | u8 | `S+0x7A` | running charge: type |
| 9 | u8 | `S+0x79` | running charge: cells (NiMH: the NiMH cell field `0x1FFFAA61`) |
| 10 | u16 | `S+0xB2` | battery voltage, 10 mV |
| 12 | u32 | `S+0xDC` | charged energy, mWh |
| 16 | u32 | `S+0xE0` | charge time, s |
| 20 | u16 | `S+0xB6` | charge power, 10 mW |
| 22 | u8 | `S+0x78` | charge complete (1 after the charger state passes 4) |
| 23 | u8 | `S+0x05` | output on |
| 24 | u8 | `S+0x30` | mode |
| 25 | u8 | `S+0x39` | temperature, signed °C |
| 26 | u16 | low half of `S+0x1DC` OR `S+0x9E` | charger error word merged with the fault word (7.2) |
| 28 | u16 | high half of `S+0x1DC` | always 0 in this image (the word is built from 16-bit values) |

### 5.23 `EE` charge control, `0x13D44`

Request: `EE, rc, type, u16 voltage, cells, u16 current, output, model`
(+suffix). Skeleton with mode 3; success flag `S+0x4D` instead of `S+0x49`.
Body:

1. `model != 3`: as `C8`.
2. `type <= 5` -> `S+0x1CA`, else `FF`.
3. `table[type].min <= voltage <= table[type].max` (table 6.5) -> `S+0x1C8`.
4. cells: `FF` if (`type <= 2` and `cells > 6`), (`type == 3` and `cells >
   8`) or (`type == 4` and `cells > 12`). 0 is accepted. Stored at `S+0x1C4`
   unless `type == 5` (NiMH/Cd cells are not stored).
5. `current <= 5000` -> `S+0x1C6` (0 accepted).
6. `output > 1` or `S+0x4B == 1` -> `FF`. Output 1: `FF` on fault; if the
   charger is idle (`S+0x7B == 0`) and `S+0x9E == 0`: `0x1D6FC(u32 S+0x1C4,
   u32 S+0x1C8)` (charger start), `S+0x78 = 0`, beep 1; otherwise nothing
   (still status 0). Output 0: if `S+0x7B != 0`, `0x1D858()` (charger stop)
   and beep 1.
7. Success: `S+0x4D = 1`.

### 5.24 `BB`, `BD`, `BE` from the CH58x (no reply)

- `BB` `0x15AA0` (type 5 in practice, type not checked): clears `0xC4` bytes
  at `0x1FFF9A70`, count = payload 0 at `0x1FFF9A74`, then per item 6 bytes
  (BLE address) plus a length-prefixed name into records of `0x26` bytes at
  `0x1FFF9A76`; the 6 bytes are summed into `0x1FFF9A70`; `S+0x3D = 1`. No
  bound checks on count or name length.
- `BD` `0x14660`: type 6 stores payload 0 in `S+3` (host link, section 1); 0
  also clears `K+2` and `K+0x12`. Type 5 stores payload 0 in `S+4` (peer link)
  and copies `length - 2` bytes from payload 1 to `S+0x58` with a zero
  terminator. Then if `S+4 == 0`: `K+0xD = 2`, word `K+0x2C = 0`, `K+0xE`,
  `K+0xF`, `S+0x1D`, `S+0x1E` cleared.
- `BE` `0x1855C`: selector 0 moves pending `K+0xE`/`K+0xF` into `S+0x1D`/`S+0x1E`, clears the three
  flags and adds +1 or -1 (last payload byte 1 or `FF`) to the word `K+0x2C`, setting
  `0x1FFE016F = 1`; selectors 1, 2, 4 set one of `K+0xE`, `K+0xF`, `K+0xD`
  to 1, or all three to 2 if the chosen one already is 2.

### 5.25 `51`, `53`, `F1`, `FD` from the CH58x (no reply)

- `51 00`, `53 00` (type 3 only): acknowledgements of main's `50 <S+3>` (link
  state) and `52 53|20` (power state) messages (2.3).
- `F1 00` (type 3 only): if `0x1FFFA00E == 1` set it to 2. This is the CH58x
  confirming main's `F0 AC` "prepare for update"; `0x12850` then reboots
  (5.26).
- `FD` (any type): payload 3 = companion ready: `K+9 = 0`, `0x1FFF9449 = 1`
  (companion link up), `0x1AE70(1)` (`0x1FFFAA4E = 1`), `0x1FFF9438 = 1`,
  `FLAGS |= 0x2000` (ask the companion's identity with `E0`). Payload `FF`:
  link down: `0x1FFF9449 = 0`, `K+0..2` = 1, 0, 0, `0x1FFF9438 = 0`,
  `0x1FFF943C++`.

### 5.26 Maintenance: `20`, `F0`, `F2`, `F4`, `F6`, `FC`, `FE`

These implement an in-application firmware update through the external SPI
NOR flash, plus a factory reset. The flash is driven with the standard
commands `06`/`04` write enable/disable, `05` status poll, `03` read, `02`
page program, `20` 4 KB erase and `D8` 64 KB erase with 24-bit addresses
(same result as `hardware.md`). No JEDEC ID read exists, so the part is not
identified; `0x1BF3A` refuses `addr + len > 0x800000` (an 8 MB software
limit), and the offsets in use reach `0x1F0FFF`, so the chip holds at least
2 MB. They are recorded here; the client never
sends them. The replies of `20`, `F2`, `F4`, `F6`, `FC` append a constant
`31` for type 6.

| Command | Request | Effect | Reply |
|---|---|---|---|
| `F0 AC` | | `0x1FFFA00C = 1` (update mode: the transmit service stops its normal traffic) | `F1 00` (+suffix); other payload: no reply |
| `F2 00 addr len` | u32 addr at 2, u32 len at 6 | Clears `0x98` bytes at `0x1FFFA00C`, sets it to 1. If `addr + len <= 0x800000`: erases 64 KB block 0, then blocks from `addr` while `len` counts down in 0x10000 steps, then one more if a remainder is left | `F3 00 st`, `st = FF` if byte 1 is not 0 or the range is too large |
| `F4 00 addr data[128]` | u32 addr at 2, 32 LE words at 6 | Programs 128 bytes at `addr`, reads them back, adds the 32 read-back words to the running sum `0x1FFFA01C` | `F5 00 addr[4] st`, `st = 00` if the first byte read back equals the first byte sent |
| `F6 35 x addr len sum` | u32 at 3, 7, 11 | Requires `0x10000 <= addr < 0xFC001`, `addr % 4 == 0`, `len < 0xEC001`, `addr + len < 0xFC001` and `sum == 0x1FFFA01C`. Then reads the staged image's vector 7 at SPI `0x1001C` and programs `AA55CC33` at the address it points to (the identity-block magic), saves `len` at `0x1FFFA010` and `sum` at `0x1FFFA014`, clears the running sum | `F7 00 00`; on any failure `F7 00 FF` and SPI block `0xF0000` is erased |
| `20 05 x x x off len pad[16] data[128]` | u32 off at 5, u32 len at 9, data at `0x1D` | `off == 0`: clears the byte sum `0x1FFFA0A0` and erases 64 KB blocks `0x100000`, `0x110000`, `0x120000`, `0x130000`. Requires `len == 0x80` and `off + 0x1000 < 0x44000` (offsets up to `0x42F80` are accepted, although only `0x100000..0x13FFFF` was erased); then counter `0x1FFFA018 += 0x80`, programs `0x100000 + off`, reads back and adds every byte to `0x1FFFA0A0` | `20 05 off[4] st` |
| `20 06 ... sum` | u32 at `0x0D` | Compares with `0x1FFFA0A0`; mismatch clears the counter `0x1FFFA018` | `20 06|86 sum[4] 00` |
| `20` other | | none | length 0, or the single byte `31` for type 6 (emu) |
| `FC CA` | | If `0x1FFFA010 != 0`: writes the header at SPI 0: `len`, `sum`, companion byte count `0x1FFFA018`, `AA55CC33`. Then scans SPI `0x1F0000` (16 x 256 bytes) for the first byte that is not `00`: a stale code (not `FF`) is overwritten with `00` and the new code goes in the next byte, an erased byte takes the code directly. Code 1 if the companion count is 0, 3 if it is at most `0xB000`, 7 above. Always `0x1FFFA00D = 1`, `0x1FFFA00C = 0` | `FD 00`; other payload: no reply |
| `FE AA 55` | | `0x1DBE8`: factory defaults (`0x1D868`, keeps `0x1FFFA0D0`, resets the language to 0), then the worker rebuilds the PD table (defaults, active index 6) and the program table (one default program), erases all ten step areas `0x162000..0x16B000` and saves everything (emu); `0x1CA60(200)`: power stage shutdown request, `S+0x50 = 0`, `FLAGS |= 0x4008` (`F0 AC` to the CH58x, `B8 B0` to the BLE side), reboot countdown 200 | `FF AA 55` (+suffix); other payload `FF 00 00` |

The codes 1/3/7 read as a bitmask of images to install (bit 0 main
application, bit 1 PD 8051 image, bit 2 CH58x image): `data.bin` holds the
8051 image in its first `0xB000` bytes and the CH58x image after it
(inferred from the `0xB000` split). After `FC`, `S+0x3F` (copy of
`0x1FFFA00D`) makes the UI (`0x55854` -> `0x5F8E0`) ask the user; its
confirm callback `0x54128` switches the output off, saves the configuration,
requests power-stage shutdown and sets `0x1FFFA00E = 1`. The transmit service
then sends `F0 AC` to the CH58x; its `F1 00` sets `0x1FFFA00E = 2`, and
`0x12850` counts down and calls `0x1B71C`, which writes `0x1234` twice at
`0x2005F000` (pointer `0x1FFE01C8`) and resets through `AIRCR = 0x05FA0004`
(`0x1FEB8`). The bootloader presumably applies the staged images (inferred;
the bootloader is not in the update).

Defects found (disasm, emu):

- `F2` with `len < 0x10000` (including 0) loops 65536 times: `len - 0x10000`
  wraps and `cmp r5, #0x10000; bhs` keeps looping (`0x1FC6C..0x1FC76`). Every
  iteration erases the next 64 KB block with a 24-bit address, so every
  block of the chip is erased many times over (emu: 65538 erase calls for
  `len = 0x100`), which also wipes the PD and program tables.
- `F4` with byte 1 not 0 programs 128 bytes of stale reply-buffer content at
  SPI address 0 (the source pointer is left at the reply buffer,
  `0x1FC94..0x1FCBA`).

**SPI flash map** (from the handlers and worker `0x1D380`):

| SPI address | Content |
|---|---|
| `0x000000` | update header: length, word sum, companion byte count, `AA55CC33` |
| `0x010000..0x0FC000` | staged main application, stored at its processor addresses; `0xF0000` block erased on a failed verify |
| `0x100000..0x142FFF` | staged companion image (`20 05`), `data.bin` (8051 part first, CH58x part after `0xB000`); only `0x100000..0x13FFFF` is erased by offset 0 |
| `0x160000` | PD profile table `PDT`, `0x21C` bytes |
| `0x161000` | program table `P`, `0xC0` bytes |
| `0x162000 + slot*0x1000` | program steps, `0x4B0` bytes (100 x 12) per slot, slots 0..9 |
| `0x1F0000..0x1F0FFF` | update request log, one code byte per request |

The persistent configuration `0x1FFFA0B8` (128 bytes) is not in SPI flash; it
is written to internal flash at `0xFE000 + n*0x80` (64 records, sector erased
when full) by `0x1C364`.

## 6. Side effects of the callees

### 6.1 Output-control callees

| Callee | Does | Evidence |
|---|---|---|
| `0x1A128` | returns the output request flag `0x1FFFAA2E` | disasm |
| `0x1A134` | returns the u16 fault word `0x1FFFAA1E` | disasm |
| `0x1AEBC(v)` | `0x1FFFAA2E = v` inside a BASEPRI critical section. Nothing else | disasm |
| `0x1AF64(v)` | target voltage `0x1FFFA940 = v` (10 mV) | disasm |
| `0x1AEA4(v)` | current limit `0x1FFFA944 = v` (1 mA) | disasm |
| `0x1CB8C(n)` | buzzer: if the buzzer level `S+0x54` is not 0, loads tone pattern `n` (tables at `0x7AFE4..0x7B11C`) into the player at `0x1FFFA0A5` and restarts timer A2. Pattern 1 is the short key beep | decomp |
| `0x1A5FC()` | clears the energy remainder `0x1FFE01E4`, energy `0x1FFFA978` (mWh) and output time `0x1FFFA980` (ms): **refresh resets energy and time** | disasm |
| `0x1D6FC(a, b)` | charger start: `a` = cells (byte 0) and current (bits 16..31), `b` = voltage (bits 0..15) and type (bits 16..23) into `0x1FFFAA60`, `0x1FFFAA6E`, `0x1FFFAA70`, `0x1FFFAAAD`; runs the pre-checks `0x1FA20`, `0x1FAE4` (battery voltage too high sets charger error bit 11); if no error, resets the charge accumulators, sets up NiMH -dV parameters for type 5, sets charger state `0x1FFFAAAC = 1` and `0x1FFFAA5C = 1` | decomp, emu |
| `0x1D858()` | charger stop: `0x1FFFAAAC = 0`, `0x1FFFAA5C = 0` | disasm |
| `0x1D958()` | copies the settings, mode, DC setpoints and flags into the configuration block `0x1FFFA0B8` and, if its checksum changed, increments the record counter and writes it to internal flash (`0x1C364`); sets `0x1FFFA8CD = 1` so the worker also re-saves the PD and program tables if their checksums changed | decomp |
| `0x1AE70(v)` | `0x1FFFAA4E = v` (companion ready flag for the power code) | disasm |

What the power stage does with them (decomp of `0x1AB34`, `0x19F18`,
`0x19E68`, `0x19A50`):

- The power state machine `0x1FFFAA54` (copied to `S+0x19`) runs DC and
  program in state 7, PD in state 8, charge in state 9. Any nonzero fault word
  forces `0x1FFFAA2E = 0` every cycle. A change of the request flag resets
  only the ampere-hour accumulators (`0x1FFE01E8`, `0x1FFFA97C`), not energy
  or time.
- Output on (`0x19F18`): `0x1FFFAA2F = 1` (reported as `S+5`), outState
  starts at 1. The applied voltage `0x1FFFA950` is 0 while the output is off.
  In state 7 `0x19E68` moves it to the target: immediately when voltageSlow
  (`0x1FFFAA35`) is 0, otherwise by `slopeSteps / 10` 10-mV units every 100
  ms. **With voltageSlow = 1 the output ramps from 0 V at switch-on**, and
  every setpoint change ramps too.
- The same routine counts time while the output is on and the measured
  current is at or above the limit; with currentOver (`0x1FFFAA36`) = 1 and
  the count reaching the OCP delay (`0x1FFFAA1C`, ms) it sets fault bit 5.
- Executed (emu, `0x19E68` called every 50 ms, target 1200, slope 500):
  voltageSlow 0 gives 1200 at once; voltageSlow 1 gives 50, 50, 100, 100,
  150, ... (0.5 V per 100 ms). With limit 1000 mA, measured 1000 mA and OCP
  delay 50 ms, fault bit 5 appears on the third 20 ms call with currentOver 1
  and never with currentOver 0.
- Energy and time accumulate in states 7 and 8 while the output is on
  (`0x19A50`): time in ms (clamp 3599999000), energy in mWh (clamp 999900).

### 6.2 Mode change

`C8`/`E2`/`E8`/`EE` only store the requested mode `S+0x31`. The UI worker
`0x1E7B4` calls `0x54474(S+0x31)`: if it differs from `S+0x30` it rebuilds
the screen for the new mode, sets `S+0x30`, calls `0x1A5FC()` (resets energy
and time), `0x1AF48(mode)` (power-stage mode `0x1FFFAA37`) and, for DC,
re-applies the stored DC setpoints `S+0xA8`/`S+0xAA`. The handlers only allow
this while the output request is off, so a mode change never switches the
output off by itself; it is refused instead.

### 6.3 Program mode

Tables (RAM, persisted to SPI by the worker):

| Address | Content |
|---|---|
| `P+0x00..0x9F` | 10 x 16-byte program names (the "header" record) |
| `P+0xA0..0xA9` | step count per slot |
| `P+0xAA..0xB3` | program id per slot, 0 = free |
| `P+0xB4` | selected slot |
| `P+0xB5` | number of programs |
| `P+0xB8` | magic `AA55CC33` |
| `P+0xBC` | checksum |
| `0x1FFF8F7C` | transfer buffer, 100 x 12 bytes |
| `0x1FFFA414` | steps of the selected program, 100 x 12 bytes (runner) |

Step record, 12 bytes: `u32 voltage_mV, u32 current_mA, u32 duration_s`.
Checks in `DA`: voltage `<= 30500` (30.500 V), current `<= 5100`, duration `<=
99990` s. The runner applies `voltage / 10` (10 mV) and the current as is
(`0x58BA4`, `0x58D50`); the step table shows `"%02d.%02d"` V, `"%01d.%03d"`
A and `"%d"` for the duration, and the step timer compares elapsed whole
seconds with that number (500 ms tick, calibrated with the word
`0x1FFE0160`).

Special records (duration 0):

- voltage 0: shown as `Off`; the program ends there.
- voltage not 0: shown as `Jump`. `current` = `target_step << 24 |
  repeat_count` (target 1-based). Count 0 = jump forever; count `n` = jump `n`
  times, then end (counter `S+0xB8`, loaded from the last jump record at
  start). This is why `DA` accepts a current above 5100 only when the
  duration is 0.

Factory default program (on `FE AA 55` or an invalid table, `0x14318`):
id 1 `Test1`, 6 steps: (5000, 3000, 100), (9000, 3000, 100), (15000, 3000,
100), (20000, 3000, 100), (30000, 3000, 100), (0, 0, 0): 5, 9, 15, 20 and
30 V at 3 A for 100 s each, then `Off`.

Runner (`0x58BA4` start/stop, `0x58D50` 500 ms timer): start resets energy
and time, applies step 0, sets the output request. Each tick adds elapsed
time in `S+0xC8`; at the step duration it advances, follows jumps, or at
the end stops (output request 0, step index 0). State: `S+0x7C` step index,
`S+0x20` paused/stopped (1) or running (0), `S+0xB8` repetitions left.

### 6.4 PD mode

`PDT` layout (`0x21C` bytes): names 10 x 16 at `+0`, PDO groups 10 x 9 x 4 at
`+0xA0` (profile stride `0x24`), class (profile power, W) 10 bytes at
`+0x208`, active index at `+0x212`, magic `AA55CC33` at `+0x214`, checksum
at `+0x218`. The class byte is the profile's wattage: the UI prints `"SRC
Test - %dW"` with it, and `< 101` gives 7 groups, otherwise 9 (EPR).

Group `g` is 4 bytes: `lo` = u16 at bytes 0-1, `hi` = u16 at bytes 2-3.
`lo & 7` is the type code (0 disabled). Decoding from the UI formatter
`0x5735C` (disasm `0x574C8..0x57650`):

| Group | Type code | Kind | Fields |
|---|---|---|---|
| 0..4 | 1 | fixed | voltage `(lo >> 6) x 50 mV`, current `(hi >> 6) x 10 mA` |
| 5 | 2 | PPS | minimum voltage `byte3 x 100 mV`, maximum `byte2 x 100 mV`, current `(lo >> 9) x 50 mA` |
| 6 | 5 | SPR AVS | current for 9..15 V `(lo >> 6) x 10 mA`, for 15..20 V `(hi >> 6) x 10 mA` |
| 7 | 3 | EPR fixed | as fixed |
| 8 | 4 | EPR AVS | minimum voltage `byte2 x 100 mV`, maximum `(lo >> 7) x 100 mV`, power `byte3` W |

The kind names are inferred from the type codes and the printed ranges;
the factory defaults below confirm the scaling.

Factory default profiles (built by `0x18BFC` when the table is invalid or on
`FE AA 55`; emu of `FE AA 55` followed by the worker; active index 6, that is id 7 `60W`):

| Id | Name, class | Groups (type: decoded) |
|---|---|---|
| 1 | `12W`, 12 | fixed 5.00 V 2.40 A; others disabled |
| 2 | `18W`, 18 | 5.00 V 3.00 A, 9.00 V 2.00 A |
| 3 | `20W`, 20 | 5 V 3.00 A, 9 V 2.22 A, 12 V 1.66 A |
| 4 | `30W`, 30 | 5 V 3 A, 9 V 3 A, 12 V 2.50 A |
| 5 | `36W`, 36 | 5 V, 9 V, 12 V at 3 A |
| 6 | `45W`, 45 | 5, 9, 12, 15 V at 3 A, 20 V 2.25 A, PPS 3.3..21.0 V 2.10 A |
| 7 | `60W`, 60 | 5..20 V at 3 A, PPS 3.3..21.0 V 2.85 A |
| 8 | `65W`, 65 | 5..15 V at 3 A, 20 V 3.25 A, PPS 3.3..21.0 V 3.00 A |
| 9 | `100W`, 100 | 5..15 V at 3 A, 20 V 5 A, PPS 3.3..21.0 V 4.75 A |
| 10 | `140W`, 140 | as 100 W with PPS 5.00 A, SPR AVS 3.00 A / 5.00 A, EPR fixed 28.00 V 5.00 A, EPR AVS 15.0..28.0 V 140 W |

Raw words of the 140 W profile, groups 0..8: `0x4B001901 0x4B002D01
0x4B003C01 0x4B004B01 0x7D006401 0x21D2C802 0x7D004B05 0x7D008C03
0x8C968C04`. Disabled groups keep their values with type code 0. The
PD mode is a USB-PD source tester ("SRC Test"). `0x1FFF9B34..` holds what
the 8051 PD companion reports (`0x11900`): `B1` status (three temperatures,
VBUS and other words), `B7` a list of voltage/current pairs, `B5` per-port
words, `BD` an acknowledgement, `E5` cable e-marker data (copied to
`S+0x1E0..` by `0x11C18` and shown in `DE`). Their exact meaning belongs to
the PD companion analysis.

### 6.5 Charge mode

Battery types (pointer table `0x1FFE07BC`, strings in flash, used by the
charge screen `0x2B350` and `0x56608`):

| Type | Name | `u16` range (`0x1FFE07E0 + type*0x16`, first and eleventh entry) | Cells |
|---|---|---|---|
| 0 | `LiHv` | 4250..4450 mV per cell | 0..6 |
| 1 | `LiPo` | 4150..4250 | 0..6 |
| 2 | `Lilon` (sic) | 4050..4150 | 0..6 |
| 3 | `LiFe` | 3600..3700 | 0..8 |
| 4 | `Pb` | 2350..2450 | 0..12 |
| 5 | `NiMH/Cd` | 3..13, the -dV threshold in mV | not stored |

Each row has 11 entries (the UI steps through them). For NiMH the value goes
to `0x1FFFAABC`; `0x1F7C4` ends the charge when the battery voltage falls that
many mV below its peak three times in a row (confirmed in code), or above 1.5
V per cell, or above 2499 mAh. Charge current limit 5000 mA. Charger state
`S+0x7B` (`0x1FFFAAAC`): 0 idle, 1 started, 4 set by `0x1F7C4` for the
non-NiMH types when `0x1FFFAA68` reaches `0x1FFFAA72` (inferred: constant
voltage phase), 6 NiMH termination (reason in `0x1FFFAAB4`: 1 -dV, 2 above
1.5 V per cell, 3 capacity). The UI treats values above 4 as finished
(`S+0x78 = 1`, beep 8), and when the state returns to 0 it stores the
summary and stops the charger (`0x56244`).

## 7. State field semantics

### 7.1 Producers and units (decomp of `0x1E284` publisher, `0x19F4C`, `0x19A50`, `0x1A660`, `0x1978C`)

| Field | Producer | Unit / meaning |
|---|---|---|
| `S+0xAC` voltage | `(0x1FFFA964 + 5) / 10`; `0x1FFFA964` = INA226 (I2C `0x40`) bus register x 1.25 mV, +1 % in PD mode | 10 mV. With the output off it reads 0 below 0.501 V |
| `S+0xAE` current | `(0x1FFFA968 + 500) / 1000`, `0x1FFFA968` in µA from the INA226 shunt register minus a voltage-proportional leakage term, scaled by the calibration word `0x1FFFA938` | 1 mA; 0 while the output is off; in CC (outState 2) a reading within 1 mA of the limit is reported as the limit |
| `S+0xB0` power | `(0x1FFFA974 + 5000) / 10000`, `0x1FFFA974 = mA x mV` | 10 mW; 0 when current or voltage is 0 |
| `S+0xD0` workingTime | `0x1FFFA980 x cal / 100000 / 1000`, cal = `0x1FFE0160` (100000 in the image) | s, output-on time |
| `S+0xD4` energy | `(0x1FFFA978 + 50) / 100` | 0.1 Wh; max 9999 |
| `S+0x02` outState | on switch-off 0, on switch-on 1, then `0x1FFFAA40` on change | 1 CV and 2 CC from the CV/CC detector `0x154A0` (10-cycle hysteresis); 3 when the measured voltage exceeds the applied setpoint by more than 100 mV while the current is below 100 mA for 10 cycles (inferred: an external source holding the output above the setpoint) |
| `S+0x0E` batteryState | `0x1FFFAA41`, or 2 | 1 when the charger input channel reports an active input (`0x18EE0(0)` and `0x1BC68(0)`), 0 otherwise; 2 when `0x1FFFAA42` is set (battery temperature outside the charge window, `0x1978C`), no USB host and power state 3 |
| `S+0x3A` percentage | `0x1FFFAA23` from `0x193C0` | % |
| `S+0x39` temperature | `0x1FFFAA26` = PD companion byte `0x1FFF9B9C` (signed), forced to 5 when it reads below -15 while the hotter of the other two sensors is above 20 | °C; used for the battery temperature protections |
| `S+0x3B`, `S+0x3C` | companion bytes `0x1FFF9B9D`, `0x1FFF9B9E` | the two other temperatures, not in any reply |
| `S+0x05` output | `0x1FFFAA2F` | actual output state |
| `S+0x10`, `S+0x12`, `S+0x18` | handlers and front panel | see `C8` |
| `S+0x37`, `S+0x38` | front panel (`0x14B14`), persisted (`0x1FFFA0C1/C2`, default 1) | UI entry-mode flags (inferred; WebLink calls them keypad flags) |
| `S+0x11` wavePause | `0x53438` sets 1 when it starts the waveform-page timer and 0 when it deletes it | the `C3` byte is 1 whenever the timer does not exist, so it is 1 in every state found (inferred from all writers found) |
| `S+0x4B` | `D2`/`DA` dispatcher tail 1, handlers 2, worker 0 | transfer busy: 1 blocks output and mode changes |

### 7.2 Fault word `S+0x9E` = `0x1FFFAA1E` (producer `0x1978C`, `0x19E68`, `0x1AB34`)

| Bit | Set when | Cleared when | WebLink name |
|---|---|---|---|
| 0 | ADC1 channel 3 (`0x1FFFA9C8`, mV) at or above 501 | below 100 mV for more than 1000 ms | `OUTPUT_REVERSED` |
| 1 | battery % (`0x1FFFAA23`) is 0 and the battery current word `0x1FFFA998` is not negative | the fine charge estimate `0x1FFFA9D8` (persisted as `0x1FFFA0D0`, 0.1 % units, inferred) exceeds 9, or `0x1FFFA998` turns negative | `LOW_BATTERY` |
| 2 | temperature `S+0x39` below -19 °C | above -15 °C | `BATTERY_LOW_TEMP` |
| 3 | temperature above 57 °C | below 54 °C | `BATTERY_OVERHEAT` |
| 4 | the hotter of the two other sensors at or above 85 °C | below 75 °C | `SYSTEM_OVERHEAT` |
| 5 | current at the limit for the OCP delay with currentOver = 1 (`0x19E68`) | `0x1974C` (UI) | `DC_OUT_OCP` |
| 6 | measured voltage at or above 33001 mV for 500 ms | automatically when it falls below; also `0x1976C` | `DC_OUT_OVP` |
| 7 | power-up of the power stage (state 4) failed for 1100 ms (`0x1AB34`) | on a later successful power-up | `DIC_INIT_ERROR` |
| 8 | in CV, INA226 voltage and ADC channel 6 x 10 differ by 5 V or more for 500 ms | `0x1972C` (UI) | `DC_OUT_VOL_FAIL` |

Thresholds executed with `0x1978C` in 100 ms steps (emu): bit 6 sets on
the sixth call at 33001 mV and never at 33000 mV; bit 3 at 58 °C but not
57; bit 2 at -20 °C but not -19; bit 4 at 85 °C but not 84; bit 0 at 501
but not 500; bit 1 with 0 % and `0x1FFFA9D8 = 5` but not 10; bit 8 on the
sixth call with 12.000 V measured against 5.000 V from the ADC in CV.

Bits 9..15 are never set in `S+0x9E`. The charger error word `S+0x1DC`
(`0x1FFFAAB0`) holds the fault word ORed with bit 10 (charge current below
11 mA for more than 5 checks while the battery voltage is at or near the
target or below 0.5 V: no battery or battery disconnected, inferred) and bit
11 (battery voltage above cells x target + 50 mV at start, or above 30.05 V
for NiMH: wrong cell count, inferred). `EC` payload 26 merges both.

## 8. Transmit service `0x133BC`: deferred and unsolicited frames

Runs when the previous transmission is done (`K+0 != 0`). Priority order
(decomp; emu for the rows marked in the appendix table): a resend (`K+2`),
the pending dispatcher reply (`GATE+0`), `50 <S+3>` link state to the CH58x
when `S+3` changed, `F0 AC` (update, bit 14 or `0x1FFFA00E == 1`), then,
while the CH58x link flag `0x1FFF9449` is 0, `E0` (or `FC 2A "MP305B" 20 20
01 35 02 00` once its version is known) every 500 iterations for up to 20 tries,
then the flag bits of `FLAGS` in this order: bit 0 (only with the link up),
13, 7, 9, 8, 10, 11, 1, 2, 3, 6, 5, 4, 12, and finally the heartbeat:

| Bit | Frame | Destination |
|---|---|---|
| 0 | `52 53` or `52 20` (device-on flag `S+0x50`, set when the power key switches the device on, `0x1920C`) | CH58x (3) |
| 1 | `19 00`/`19 FF` + `00` for type 6 | route saved in `K+6` |
| 2 | deferred `C9`/`E3`/`E9`/`EF` for the current mode | host (`S+3`) |
| 3 | `B8 B0` | BLE side (5) |
| 4, 5 | frames from `0x18680`, `0x185EC` | BLE side (5) |
| 6 | `BE` | BLE side (5) |
| 7 | `D9` chunks | host |
| 8 | `DB 00` (program steps saved) | host |
| 9 | `DD` (selected program) | host |
| 10 | `E5` (active PD profile) | host |
| 11 | `EB` (charge settings, after a charge ended) | host |
| 12 | `C5` (settings) | host |
| 13 | `E0` | CH58x (3) |
| none | `10` heartbeat every 10000 iterations (at least 10 s) | CH58x (3) |

Host frames use route 6 with suffix `31` when `S+3 == 1`, route 1 without
suffix when `S+3 == 2`, and are dropped when `S+3 == 0`. **A client must
therefore expect unsolicited `C5`, `DD`, `E5`, `EB`, `DB` and deferred
`C9`/`E3`/`E9`/`EF`/`D9`/`19` frames at any time.**

## 9. Points for the client library

1. Always send complete payloads; lengths are not checked (2.1).
2. Over USB keep a frame going at least every 8 s, or the host link drops and
   the remote grant is cleared (section 1).
3. `rc = 2` over BLE produces no immediate reply; wait for a deferred `C9`
   (00 allowed, 01 denied). Over USB it is granted at once.
4. Release remote control with the command of the current mode.
5. `D2`, `D6` and `DA` switch the output request off. `D2` without the save
   flag, or a rejected `D2`/`DA`, leaves the device "busy" (`S+0x4B`), which
   blocks output and mode changes until a later successful save.
6. `DA` needs exactly 10 records in every non-final chunk; the final chunk is
   answered by a deferred `DB 00`.
7. `D8` for an unknown id produces nothing.
8. Refresh (`C8` byte 10 = 1) and every mode change reset energy and time.

## 10. Names

See `names/app_commands.tsv`.

## 11. Test vectors (generated by execution)

Produced by `scripts/commands_vectors.py` from the original code (the
introduction of this file describes the emulation). "Request" and "Reply" are opcode-first
bytes as the dispatcher sees them: for type 6 the last request byte is the
BLE route byte and replies carry it back; for type 1 (USB) there is no route
byte and the wire frame is `AA 21 len reply... sum`. "State changes" lists
every byte that changed in the watched regions (`S`, `PWR` = `0x1FFFA934`,
`GATE+0x108..` = event flags, `K`, `PROG` = `P`, `PD` = `PDT`, `XFER` =
`0x1FFFA8C4`, `UPD` = `0x1FFFA00C`, `CFG` = `0x1FFFA0B8`, `PDC` =
`0x1FFF9B34`, `CAP` = `0x1FFF942C`) as `old>new`. "Calls" lists traced
callees with their first argument. Setup values not listed are 0 (ZI) or the
RW-init image. `P` in a setup column means the group's standard granted
setup: live mode matching the command, `S+0x42 = 1`, `S+0x45 = 1`, `S+3 = 1`.


#### 0xC8 DC control

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | reset state | 6 | `C8 02 B0 04 E8 03 03 00 00 00 00 00 31` | `none` | S+0x45:00>02, S+0x49:00>01 | - |
| 2 | S+0x3=1 | 6 | `C8 02 B0 04 E8 03 03 00 00 00 00 00 31` | `none` | S+0x45:00>02, S+0x49:00>01 | - |
| 3 | reset state | 1 | `C8 02 B0 04 E8 03 03 00 00 00 00 00` | `C9 00` | S+0x3:00>02, S+0x42:00>01, S+0x45:00>01, S+0x49:00>01 | - |
| 4 | S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 01 31` | - | - |
| 5 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 00 31` | S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000), outReq(0) |
| 6 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 EA 0B EC 13 03 00 00 00 00 00 31` | `C9 00 31` | S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>EA, PWR+0xD:00>0B, PWR+0x10:00>EC, PWR+0x11:00>13 | setV(3050), setI(5100), outReq(0) |
| 7 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 EB 0B E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 8 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 EA 0B ED 13 03 00 00 00 00 00 31` | `C9 FF 31` | PWR+0xC:00>EA, PWR+0xD:00>0B | setV(3050) |
| 9 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 04 00 00 00 00 00 31` | `C9 FF 31` | PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000) |
| 10 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 02 00 00 00 00 31` | `C9 FF 31` | S+0x18:00>03, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000) |
| 11 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 02 00 00 00 31` | `C9 FF 31` | S+0x18:00>03, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000) |
| 12 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 01 00 00 31` | `C9 00 31` | S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03, PWR+0xFA:00>01 | setV(1200), setI(1000), beep(1), outReq(1) |
| 13 | S+0x42=1, S+0x45=1, S+0x3=1, 0x1fffaa1e=32 | 6 | `C8 01 B0 04 E8 03 03 00 00 01 00 00 31` | `C9 FF 31` | S+0x18:00>03, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000) |
| 14 | S+0x42=1, S+0x45=1, S+0x3=1, S+0x4b=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 01 00 00 31` | `C9 FF 31` | S+0x18:00>03, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000) |
| 15 | S+0x42=1, S+0x45=1, S+0x3=1, 0x1fffaa2e=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 00 31` | S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03, PWR+0xFA:01>00 | setV(1200), setI(1000), beep(1), outReq(0) |
| 16 | S+0x42=1, S+0x45=1, S+0x3=1, 0x1fffaa2e=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 01 00 00 31` | `C9 00 31` | S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000), outReq(1) |
| 17 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 02 00 00 31` | `C9 FF 31` | S+0x18:00>03, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000) |
| 18 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 01 31` | `C9 00 31` | S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000), outReq(0), resetCounters |
| 19 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 02 31` | `C9 FF 31` | S+0x18:00>03, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000), outReq(0) |
| 20 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 FF FF FF FF 03 00 00 00 01 00 31` | `C9 00 31` | S+0x31:00>01, S+0x49:00>01 | - |
| 21 | S+0x42=1, S+0x45=1, S+0x3=1, 0x1fffaa2e=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 01 00 31` | `C9 FF 31` | - | - |
| 22 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 04 00 31` | `C9 FF 31` | - | - |
| 23 | S+0x42=1, S+0x45=1, S+0x3=1, S+0x4b=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 01 00 31` | `C9 FF 31` | - | - |
| 24 | S+0x42=1, S+0x45=1, S+0x3=1, S+0x30=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 25 | S+0x42=1, S+0x45=1, S+0x3=1, S+0x30=2 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 26 | S+0x42=1, S+0x45=1, S+0x3=1, S+0x30=3 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 27 | S+0x42=1, S+0x45=1, S+0x3=1, S+0x30=2 | 6 | `C8 00 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 28 | S+0x3=1, S+0x30=3 | 6 | `C8 02 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 29 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 03 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 FF 31` | - | - |
| 30 | S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `C8 00 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 00 31` | S+0x42:01>00, S+0x45:01>00, S+0x49:00>01 | - |
| 31 | S+0x3=1 | 6 | `C8 00 B0 04 E8 03 03 00 00 00 00 00 31` | `C9 00 31` | S+0x49:00>01 | - |
| 32 | S+0x3=1, S+0x45=2, S+0x30=1 | 6 | `C8 01 B0 04 E8 03 03 00 00 00 00 00 31` | `none` | - | - |
| 33 | S+0x42=1, S+0x45=1 | 1 | `C8 01 B0 04 E8 03 03 00 00 00 00 00` | `C9 00` | S+0x3:00>02, S+0x18:00>03, S+0x49:00>01, PWR+0xC:00>B0, PWR+0xD:00>04, PWR+0x10:00>E8, PWR+0x11:00>03 | setV(1200), setI(1000), outReq(0) |
| 34 | S+0x3=1, S+0x42=1, S+0x45=1, 0x1fff9550=4 | 6 | `C8 31` | `C9 00 31` | - | - |
| 35 | S+0x3=1, S+0x42=0, S+0x45=0, 0x1fff9550=4 | 6 | `C8 31` | `C9 01 31` | - | - |

#### 0xC6 settings write

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | reset state | 6 | `C6 5A 03 00 1E 01 F4 01 32 00 00 00 00 00 31` | `C7 00 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E, S+0x48:00>01, S+0x96:00>F4, S+0x97:00>01, S+0x98:00>32 | - |
| 2 | reset state | 6 | `C6 50 00 00 00 00 00 00 00 00 00 00 00 00 31` | `C7 00 31` | S+0x2D:00>50, S+0x48:00>01 | - |
| 3 | reset state | 6 | `C6 64 03 01 1E 01 E8 03 E8 03 01 01 E8 03 31` | `C7 00 31` | S+0x2D:00>64, S+0x2E:00>01, S+0x32:00>03, S+0x33:00>1E, S+0x35:00>01, S+0x36:00>01, S+0x48:00>01, S+0x96:00>E8, S+0x97:00>03, S+0x98:00>E8, S+0x99:00>03, S+0xA4:00>E8, S+0xA5:00>03 | - |
| 4 | reset state | 6 | `C6 4F 03 00 1E 01 F4 01 32 00 00 00 00 00 31` | `C7 FF 31` | - | - |
| 5 | reset state | 6 | `C6 65 03 00 1E 01 F4 01 32 00 00 00 00 00 31` | `C7 FF 31` | - | - |
| 6 | reset state | 6 | `C6 5A 04 00 1E 01 F4 01 32 00 00 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A | - |
| 7 | reset state | 6 | `C6 5A 03 02 1E 01 F4 01 32 00 00 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03 | - |
| 8 | reset state | 6 | `C6 5A 03 00 1F 01 F4 01 32 00 00 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03 | - |
| 9 | reset state | 6 | `C6 5A 03 00 1E 02 F4 01 32 00 00 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E | - |
| 10 | reset state | 6 | `C6 5A 03 00 1E 01 E9 03 32 00 00 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E | - |
| 11 | reset state | 6 | `C6 5A 03 00 1E 01 F4 01 E9 03 00 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E, S+0x96:00>F4, S+0x97:00>01 | - |
| 12 | reset state | 6 | `C6 5A 03 00 1E 01 F4 01 32 00 02 00 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E, S+0x96:00>F4, S+0x97:00>01, S+0x98:00>32 | - |
| 13 | reset state | 6 | `C6 5A 03 00 1E 01 F4 01 32 00 00 02 00 00 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E, S+0x96:00>F4, S+0x97:00>01, S+0x98:00>32 | - |
| 14 | reset state | 6 | `C6 5A 03 00 1E 01 F4 01 32 00 00 00 E9 03 31` | `C7 FF 31` | S+0x2D:00>5A, S+0x32:00>03, S+0x33:00>1E, S+0x96:00>F4, S+0x97:00>01, S+0x98:00>32 | - |
| 15 | reset state | 1 | `C6 51 03 00 01 01 00 00 01 00 00 00 96 00` | `C7 00` | S+0x3:00>02, S+0x2D:00>51, S+0x32:00>03, S+0x33:00>01, S+0x48:00>01, S+0x98:00>01, S+0xA4:00>96 | - |

#### Read commands (C2, C4, E0, 00, A0)

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | S+0x2=1, S+0xe=0, S+0x3a=90, S+0xac:u16=1199, S+0xa8:u16=1200, S+0xae:u16=523, S+0xaa:u16=1000, S+0xd0:u32=3725, S+0xd4:u32=12, S+0xb0:u16=627, S+0x12=0, S+0x18=3, S+0x10=0, S+0x5=1, S+0x30=0, S+0x37=1, S+0x38=1, S+0x39=27, S+0x9e:u16=0, S+0x11=0, 0x1fffa980=3725123 | 6 | `C2 31` | `C3 01 00 5A AF 04 B0 04 0B 02 E8 03 8D 0E 00 00 0C 00 00 00 73 02 00 03 00 01 00 01 01 1B 00 00 01 43 D7 38 00 31` | - | - |
| 2 | S+0x2=1, S+0xe=0, S+0x3a=90, S+0xac:u16=1199, S+0xa8:u16=1200, S+0xae:u16=523, S+0xaa:u16=1000, S+0xd0:u32=3725, S+0xd4:u32=12, S+0xb0:u16=627, S+0x12=0, S+0x18=3, S+0x10=0, S+0x5=1, S+0x30=0, S+0x37=1, S+0x38=1, S+0x39=27, S+0x9e:u16=0, S+0x11=0, 0x1fffa980=3725123, 0x1ffe02a0=536875008 | 1 | `C2` | `C3 01 00 5A AF 04 B0 04 0B 02 E8 03 8D 0E 00 00 0C 00 00 00 73 02 00 03 00 01 00 01 01 1B 00 00 00 43 D7 38 00` | S+0x3:00>02 | - |
| 3 | S+0x9e:u16=288, S+0x2=2, S+0x39=251 | 6 | `C2 31` | `C3 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FB 20 01 01 00 00 00 00 31` | - | - |
| 4 | S+0x2d=90, S+0x32=3, S+0x2e=0, S+0x33=30, S+0x2f=1, S+0x96:u16=500, S+0x98:u16=50, S+0xa4:u16=0 | 6 | `C4 31` | `C5 5A 03 00 1E 01 F4 01 32 00 00 00 31` | - | - |
| 5 | S+0x2d=90, S+0x32=3, S+0x2e=0, S+0x33=30, S+0x2f=1, S+0x96:u16=500, S+0x98:u16=50, S+0xa4:u16=0 | 1 | `C4` | `C5 5A 03 00 1E 01 F4 01 32 00 00 00` | S+0x3:00>02 | - |
| 6 | reset state | 6 | `E0 31` | `E1 01 06 00 33 4D 50 33 30 35 42 00 00 02 00 02 00 31` | - | - |
| 7 | reset state | 6 | `E0 00` | `E1 01 06 00 33 4D 50 33 30 35 42 00 00 02 00 02 00 00` | - | - |
| 8 | reset state | 1 | `E0` | `E1 4D 50 33 30 35 42 00 00 00 00 00 00 00 00 00 00 01 06 00 33 4D 50 33 30 35 42 00 00 00 00` | S+0x3:00>02 | - |
| 9 | reset state | 5 | `E0 31` | `E1 4D 50 33 30 35 42 00 00 00 00 00 00 00 00 00 00 01 06 00 33 4D 50 33 30 35 42 00 00 00 00` | - | - |
| 10 | reset state | 6 | `00 31` | `01 91 67 01 31` | - | - |
| 11 | reset state | 1 | `00` | `01 91 67 01` | S+0x3:00>02 | - |
| 12 | 0x1fffa0ce=1 | 6 | `A0 31` | `A1 01 31` | - | - |
| 13 | reset state | 1 | `A0` | `A1 00` | S+0x3:00>02 | - |

#### Language, bind, ignored opcodes and companion messages

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | reset state | 6 | `A2 01 31` | `A3 00 31` | S+0x0:00>01, XFER+0x9:00>01, CFG+0x0:00>01, CFG+0x16:00>01, CFG+0x7C:00>02 | outReq(0), saveCfg |
| 2 | 0x1fffa0ce=1 | 6 | `A2 00 31` | `A3 00 31` | S+0x0:00>01, XFER+0x9:00>01, CFG+0x16:01>00 | outReq(0), saveCfg |
| 3 | 0x1fffa0ce=1 | 6 | `A2 05 31` | `A3 00 31` | S+0x0:00>01, XFER+0x9:00>01, CFG+0x16:01>00 | outReq(0), saveCfg |
| 4 | 0x1fffa0ce=1 | 6 | `A2 01 31` | `A3 00 31` | - | - |
| 5 | S+0x30=3 | 6 | `A2 01 31` | `A3 00 31` | S+0x0:00>01, XFER+0x9:00>01, CFG+0x0:00>01, CFG+0x7:00>03, CFG+0x16:00>01, CFG+0x7C:00>05 | chargeStop, saveCfg |
| 6 | reset state | 6 | `18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00` | `none` | S+0x47:00>01, K+0x6:00>06 | - |
| 7 | reset state | 6 | `01 00 31` | `none` | - | - |
| 8 | reset state | 6 | `19 00 31` | `none` | - | - |
| 9 | reset state | 6 | `C3 00 31` | `none` | - | - |
| 10 | reset state | 6 | `C9 00 31` | `none` | - | - |
| 11 | reset state | 6 | `DD 00 31` | `none` | - | - |
| 12 | reset state | 6 | `DF 00 31` | `none` | - | - |
| 13 | reset state | 6 | `E3 00 31` | `none` | - | - |
| 14 | reset state | 6 | `E5 00 31` | `none` | - | - |
| 15 | reset state | 6 | `E6 00 31` | `none` | - | - |
| 16 | reset state | 6 | `E7 00 31` | `none` | - | - |
| 17 | reset state | 6 | `E9 00 31` | `none` | - | - |
| 18 | reset state | 6 | `EB 00 31` | `none` | - | - |
| 19 | reset state | 6 | `ED 00 31` | `none` | - | - |
| 20 | reset state | 6 | `EF 00 31` | `none` | - | - |
| 21 | reset state | 6 | `F3 00 31` | `none` | - | - |
| 22 | reset state | 6 | `F5 00 31` | `none` | - | - |
| 23 | reset state | 6 | `F7 00 31` | `none` | - | - |
| 24 | reset state | 6 | `F8 00 31` | `none` | - | - |
| 25 | reset state | 6 | `F9 00 31` | `none` | - | - |
| 26 | reset state | 6 | `FA 00 31` | `none` | - | - |
| 27 | reset state | 6 | `FB 00 31` | `none` | - | - |
| 28 | reset state | 6 | `FF 00 31` | `none` | - | - |
| 29 | reset state | 6 | `50 00 31` | `none` | - | - |
| 30 | reset state | 6 | `52 00 31` | `none` | - | - |
| 31 | reset state | 6 | `55 00 31` | `none` | - | - |
| 32 | reset state | 6 | `AA 00 31` | `none` | - | - |
| 33 | reset state | 6 | `10 00 31` | `none` | - | - |
| 34 | reset state | 6 | `11 00 31` | `none` | - | - |
| 35 | 0x1fff954b=1 | 3 | `51 00` | `none` | CAP+0x14:00>E8, CAP+0x15:00>03 | - |
| 36 | 0x1fff954b=1 | 3 | `51 01` | `none` | - | - |
| 37 | 0x1fff954b=1 | 6 | `51 00 31` | `none` | - | - |
| 38 | 0x1fff954c=1 | 3 | `53 00` | `none` | CAP+0x14:00>E8, CAP+0x15:00>03 | - |
| 39 | 0x1fffa00e=1 | 3 | `F1 00` | `none` | UPD+0x2:01>02 | - |
| 40 | reset state | 3 | `F1 00` | `none` | - | - |
| 41 | reset state | 3 | `FD 03` | `none` | PWR+0x11A:00>01, GATE+0x109:00>20, CAP+0xC:00>01 | set_aa4e |
| 42 | reset state | 3 | `FD FF` | `none` | CAP+0x10:00>01 | - |
| 43 | reset state | 6 | `FD 03 31` | `none` | PWR+0x11A:00>01, GATE+0x109:00>20, CAP+0xC:00>01 | set_aa4e |
| 44 | reset state | 6 | `BD 01 31` | `none` | S+0x3:00>01, K+0xD:00>02 | - |
| 45 | S+0x3=1 | 6 | `BD 00 31` | `none` | S+0x3:01>00, K+0xD:00>02 | - |
| 46 | reset state | 5 | `BD 01 41 42 43` | `none` | S+0x4:00>01, S+0x58:00>41, S+0x59:00>42, S+0x5A:00>43 | - |
| 47 | S+0x4=1 | 5 | `BD 00` | `none` | S+0x4:01>00, K+0xD:00>02 | - |
| 48 | reset state | 5 | `BE 01 31` | `none` | K+0xE:00>01 | - |
| 49 | 0x1ffe0192=1 | 5 | `BE 00 01 31` | `none` | S+0x1D:00>01, K+0xE:01>00, K+0x2C:00>01 | - |
| 50 | reset state | 5 | `BB 01 01 02 03 04 05 06 03 41 42 43 31` | `none` | S+0x3D:00>01 | - |
| 51 | reset state | 3 | `E1 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 0A 0B 0C 0D` | `none` | CAP+0x8:00>0A, CAP+0x9:00>0B, CAP+0xA:00>0C, CAP+0xB:00>0D | - |
| 52 | 0x1fff9434=1 | 3 | `E1 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 0A 0B 0C 0D` | `none` | CAP+0x0:00>0A, CAP+0x1:00>0B, CAP+0x2:00>0C, CAP+0x3:00>0D, CAP+0x4:00>0A, CAP+0x5:00>0B, CAP+0x6:00>0C, CAP+0x7:00>0D | - |
| 53 | reset state | 6 | `E1 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 0A 0B 0C 0D 31` | `none` | - | - |

#### 0xE2 program run control

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 00 00 01 31` | `E3 00 31` | S+0x49:00>01 | - |
| 2 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 01 00 01 31` | `E3 00 31` | S+0x49:00>01, S+0x4C:00>01 | - |
| 3 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 02 00 01 31` | `E3 00 31` | S+0x49:00>01, S+0x4C:00>02 | - |
| 4 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 03 00 01 31` | `E3 00 31` | S+0x49:00>01, S+0x4C:00>03 | - |
| 5 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 04 00 01 31` | `E3 FF 31` | - | - |
| 6 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 00 01 01 31` | `E3 00 31` | S+0x6:00>01, S+0x49:00>01 | beep(1) |
| 7 | S+0x30=1, S+0x42=1, S+0x45=1, S+0x3=1, 0x1fffa408=0, 0x1fffa3f4=0 | 6 | `E2 01 00 01 01 31` | `E3 FF 31` | - | - |
| 8 | P (mode 1, selected slot 0 with 5 steps), 0x1fffaa1e=1 | 6 | `E2 01 00 01 01 31` | `E3 FF 31` | - | - |
| 9 | P (mode 1, selected slot 0 with 5 steps), 0x1fffaa2e=1 | 6 | `E2 01 00 01 01 31` | `E3 00 31` | S+0x49:00>01 | - |
| 10 | P (mode 1, selected slot 0 with 5 steps), 0x1fffaa2e=1 | 6 | `E2 01 00 00 01 31` | `E3 00 31` | S+0x49:00>01, PWR+0xFA:01>00 | outReq(0), beep(1) |
| 11 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 00 02 01 31` | `E3 FF 31` | - | - |
| 12 | P (mode 1, selected slot 0 with 5 steps), S+0x4b=1 | 6 | `E2 01 00 01 01 31` | `E3 FF 31` | - | - |
| 13 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 04 01 01 31` | `E3 FF 31` | - | - |
| 14 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 00 00 00 31` | `E3 00 31` | S+0x49:00>01 | - |
| 15 | P (mode 1, selected slot 0 with 5 steps), 0x1fffaa2e=1 | 6 | `E2 01 00 00 00 31` | `E3 FF 31` | - | - |
| 16 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 01 00 00 04 31` | `E3 FF 31` | - | - |
| 17 | S+0x30=1, S+0x42=0, S+0x45=1, S+0x3=1, 0x1fffa408=0, 0x1fffa3f4=5 | 6 | `E2 01 00 00 01 31` | `E3 01 31` | - | - |
| 18 | S+0x30=1, S+0x3=1 | 6 | `E2 02 00 00 01 31` | `none` | S+0x45:00>02, S+0x49:00>01 | - |
| 19 | S+0x30=1 | 1 | `E2 02 00 00 01` | `E3 00` | S+0x3:00>02, S+0x42:00>01, S+0x45:00>01, S+0x49:00>01 | - |
| 20 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 00 00 00 01 31` | `E3 00 31` | S+0x42:01>00, S+0x45:01>00, S+0x49:00>01 | - |
| 21 | S+0x30=0, S+0x42=1, S+0x45=1, S+0x3=1, 0x1fffa408=0, 0x1fffa3f4=5 | 6 | `E2 01 00 00 01 31` | `E3 FF 31` | - | - |
| 22 | P (mode 1, selected slot 0 with 5 steps) | 6 | `E2 03 00 00 01 31` | `E3 FF 31` | - | - |

#### 0xE8 PD control

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | P | 6 | `E8 01 00 00 00 00 02 31` | `E9 00 31` | S+0x49:00>01 | - |
| 2 | P | 6 | `E8 01 FF 01 01 00 02 31` | `E9 00 31` | S+0x49:00>01, S+0x9C:00>FF, S+0x9D:00>01, PDC+0x85:00>01 | - |
| 3 | P | 6 | `E8 01 00 00 00 01 02 31` | `E9 00 31` | S+0x2A:00>01, S+0x49:00>01, PDC+0x85:00>01 | beep(1) |
| 4 | P | 6 | `E8 01 00 00 01 01 02 31` | `E9 00 31` | S+0x49:00>01, PDC+0x85:00>01 | - |
| 5 | P, 0x1fffaa1e=1 | 6 | `E8 01 00 00 00 01 02 31` | `E9 FF 31` | - | - |
| 6 | P, 0x1fffaa2e=1 | 6 | `E8 01 00 00 00 01 02 31` | `E9 00 31` | S+0x49:00>01 | - |
| 7 | P, 0x1fffaa2e=1 | 6 | `E8 01 00 00 00 00 02 31` | `E9 00 31` | S+0x49:00>01, PWR+0xFA:01>00 | outReq(0), beep(1) |
| 8 | P | 6 | `E8 01 34 12 07 02 02 31` | `E9 FF 31` | S+0x9C:00>34, S+0x9D:00>12, PDC+0x85:00>07 | - |
| 9 | P, S+0x4b=1 | 6 | `E8 01 00 00 00 01 02 31` | `E9 FF 31` | - | - |
| 10 | P | 6 | `E8 01 00 00 00 00 00 31` | `E9 00 31` | S+0x49:00>01 | - |
| 11 | P, 0x1fffaa2e=1 | 6 | `E8 01 00 00 00 00 03 31` | `E9 FF 31` | - | - |
| 12 | S+0x30=0, S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `E8 01 00 00 00 00 02 31` | `E9 FF 31` | - | - |
| 13 | S+0x30=2, S+0x42=0, S+0x45=1, S+0x3=1 | 6 | `E8 01 00 00 00 00 02 31` | `E9 01 31` | - | - |
| 14 | S+0x30=2, S+0x3=1 | 6 | `E8 02 00 00 00 00 02 31` | `none` | S+0x45:00>02, S+0x49:00>01 | - |

#### 0xEE charge control

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | P | 6 | `EE 01 01 68 10 03 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 2 | P | 6 | `EE 01 00 9A 10 06 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>06, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>9A, S+0x1C9:00>10 | - |
| 3 | P | 6 | `EE 01 00 62 11 00 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>62, S+0x1C9:00>11 | - |
| 4 | P | 6 | `EE 01 00 99 10 03 E8 03 00 03 31` | `EF FF 31` | - | - |
| 5 | P | 6 | `EE 01 00 63 11 03 E8 03 00 03 31` | `EF FF 31` | - | - |
| 6 | P | 6 | `EE 01 00 9A 10 07 E8 03 00 03 31` | `EF FF 31` | S+0x1C8:00>9A, S+0x1C9:00>10 | - |
| 7 | P | 6 | `EE 01 01 36 10 06 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>06, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>36, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 8 | P | 6 | `EE 01 01 9A 10 00 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>9A, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 9 | P | 6 | `EE 01 01 35 10 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>01 | - |
| 10 | P | 6 | `EE 01 01 9B 10 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>01 | - |
| 11 | P | 6 | `EE 01 01 36 10 07 E8 03 00 03 31` | `EF FF 31` | S+0x1C8:00>36, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 12 | P | 6 | `EE 01 02 D2 0F 06 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>06, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>D2, S+0x1C9:00>0F, S+0x1CA:00>02 | - |
| 13 | P | 6 | `EE 01 02 36 10 00 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>36, S+0x1C9:00>10, S+0x1CA:00>02 | - |
| 14 | P | 6 | `EE 01 02 D1 0F 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>02 | - |
| 15 | P | 6 | `EE 01 02 37 10 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>02 | - |
| 16 | P | 6 | `EE 01 02 D2 0F 07 E8 03 00 03 31` | `EF FF 31` | S+0x1C8:00>D2, S+0x1C9:00>0F, S+0x1CA:00>02 | - |
| 17 | P | 6 | `EE 01 03 10 0E 08 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>08, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>10, S+0x1C9:00>0E, S+0x1CA:00>03 | - |
| 18 | P | 6 | `EE 01 03 74 0E 00 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>74, S+0x1C9:00>0E, S+0x1CA:00>03 | - |
| 19 | P | 6 | `EE 01 03 0F 0E 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>03 | - |
| 20 | P | 6 | `EE 01 03 75 0E 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>03 | - |
| 21 | P | 6 | `EE 01 03 10 0E 09 E8 03 00 03 31` | `EF FF 31` | S+0x1C8:00>10, S+0x1C9:00>0E, S+0x1CA:00>03 | - |
| 22 | P | 6 | `EE 01 04 2E 09 0C E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>0C, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>2E, S+0x1C9:00>09, S+0x1CA:00>04 | - |
| 23 | P | 6 | `EE 01 04 92 09 00 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>92, S+0x1C9:00>09, S+0x1CA:00>04 | - |
| 24 | P | 6 | `EE 01 04 2D 09 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>04 | - |
| 25 | P | 6 | `EE 01 04 93 09 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>04 | - |
| 26 | P | 6 | `EE 01 04 2E 09 0D E8 03 00 03 31` | `EF FF 31` | S+0x1C8:00>2E, S+0x1C9:00>09, S+0x1CA:00>04 | - |
| 27 | P | 6 | `EE 01 05 03 00 FF E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>03, S+0x1CA:00>05 | - |
| 28 | P | 6 | `EE 01 05 0D 00 00 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>0D, S+0x1CA:00>05 | - |
| 29 | P | 6 | `EE 01 05 02 00 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>05 | - |
| 30 | P | 6 | `EE 01 05 0E 00 03 E8 03 00 03 31` | `EF FF 31` | S+0x1CA:00>05 | - |
| 31 | P | 6 | `EE 01 06 68 10 03 E8 03 00 03 31` | `EF FF 31` | - | - |
| 32 | P | 6 | `EE 01 01 68 10 03 88 13 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C6:00>88, S+0x1C7:00>13, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 33 | P | 6 | `EE 01 01 68 10 03 89 13 00 03 31` | `EF FF 31` | S+0x1C4:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 34 | P | 6 | `EE 01 01 68 10 03 00 00 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 35 | P | 6 | `EE 01 01 68 10 03 E8 03 01 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01, PWR+0x128:00>01, PWR+0x12C:00>03, PWR+0x13A:00>E8, PWR+0x13B:00>03, PWR+0x13C:00>68, PWR+0x13D:00>10, PWR+0x13E:00>68, PWR+0x13F:00>10, PWR+0x140:00>B8, PWR+0x141:00>0B, PWR+0x142:00>B8, PWR+0x143:00>0B, PWR+0x144:00>64, PWR+0x146:00>9C, PWR+0x147:00>31, PWR+0x148:00>64, PWR+0x14A:00>64, PWR+0x178:00>01, PWR+0x179:00>01 | chargeStart(65536003), beep(1) |
| 36 | P, S+0x7b=1 | 6 | `EE 01 01 68 10 03 E8 03 01 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 37 | P, S+0x9e:u16=4 | 6 | `EE 01 01 68 10 03 E8 03 01 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 38 | P, 0x1fffaa1e=4 | 6 | `EE 01 01 68 10 03 E8 03 01 03 31` | `EF FF 31` | S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 39 | P, S+0x7b=1 | 6 | `EE 01 01 68 10 03 E8 03 00 03 31` | `EF 00 31` | S+0x4D:00>01, S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | chargeStop, beep(1) |
| 40 | P | 6 | `EE 01 01 68 10 03 E8 03 02 03 31` | `EF FF 31` | S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 41 | P, S+0x4b=1 | 6 | `EE 01 01 68 10 03 E8 03 01 03 31` | `EF FF 31` | S+0x1C4:00>03, S+0x1C6:00>E8, S+0x1C7:00>03, S+0x1C8:00>68, S+0x1C9:00>10, S+0x1CA:00>01 | - |
| 42 | P | 6 | `EE 01 01 68 10 03 E8 03 00 00 31` | `EF 00 31` | S+0x4D:00>01 | - |
| 43 | P, 0x1fffaa2e=1 | 6 | `EE 01 01 68 10 03 E8 03 00 00 31` | `EF FF 31` | - | - |
| 44 | S+0x30=0, S+0x42=1, S+0x45=1, S+0x3=1 | 6 | `EE 01 01 68 10 03 E8 03 00 03 31` | `EF FF 31` | - | - |
| 45 | S+0x30=3, S+0x3=1 | 6 | `EE 02 01 68 10 03 E8 03 00 03 31` | `none` | S+0x45:00>02, S+0x4D:00>01 | - |

#### Program upload, read back and delete (BLE host, S+3 = 1)

| Step | Input | Output |
|---|---|---|
| 1 | `D4 31` | `D5 00 31` |
| 2 | `D6 01 54 45 53 54 00 00 00 00 00 00 00 00 00 00 00 00 03 01 02 31` | `D7 00 31` |
| 3 | `D4 31` | `D5 01 54 45 53 54 00 00 00 00 00 00 00 00 00 00 00 00 03 31` |
| 4 | `DA 01 88 13 00 00 E8 03 00 00 0A 00 00 00 E0 2E 00 00 D0 07 00 00 14 00 00 00 E4 0C 00 00 F4 01 00 00 96 86 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `none` |
| 5 | worker 0x1D380 | flash ops: erase4k 0x161000, write 0x161000 len 0xC0, erase4k 0x162000, write 0x162000 len 0x4B0, read 0x162000 len 0x4B0 |
| 6 | tx service 0x133BC | addr 26 `DB 00 31` |
| 7 | `DC 31` | `DD 01 03 31` |
| 8 | `D8 01 31` | `none` |
| 9 | worker 0x1D380 | flash ops: read 0x162000 len 0x4B0 |
| 10 | tx service 0x133BC | addr 26 `D9 01 88 13 00 00 E8 03 00 00 0A 00 00 00 E0 2E 00 00 D0 07 00 00 14 00 00 00 E4 0C 00 00 F4 01 00 00 96 86 01 00 31` |
| 11 | tx service 0x133BC | addr 23 `10` |
| 12 | `D8 05 31` | `none` |
| 13 | worker 0x1D380 | flash ops: none |
| 14 | tx service 0x133BC | nothing sent |
| 15 | `D6 01 54 45 53 54 00 00 00 00 00 00 00 00 00 00 00 00 03 01 01 31` | `D7 00 31` |
| 16 | worker 0x1D380 | flash ops: erase4k 0x161000, write 0x161000 len 0xC0, read 0x162000 len 0x4B0 |
| 17 | `D4 31` | `D5 00 31` |

Flash 0x161000 after sequence: 544553540000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000040010000
Flash 0x162000: 88130000e80300000a000000e02e0000d007000014000000e40c0000f401000096860100000000000000000000000000
S+0x4B = 0

#### Program with 12 steps: two DA chunks

| Step | Input | Output |
|---|---|---|
| 1 | `D6 02 54 57 45 4C 56 45 00 00 00 00 00 00 00 00 00 00 0C 01 02 31` | `D7 00 31` |
| 2 | `DA 02 E8 03 00 00 00 00 00 00 01 00 00 00 4C 04 00 00 64 00 00 00 02 00 00 00 B0 04 00 00 C8 00 00 00 03 00 00 00 14 05 00 00 2C 01 00 00 04 00 00 00 78 05 00 00 90 01 00 00 05 00 00 00 DC 05 00 00 F4 01 00 00 06 00 00 00 40 06 00 00 58 02 00 00 07 00 00 00 A4 06 00 00 BC 02 00 00 08 00 00 00 08 07 00 00 20 03 00 00 09 00 00 00 6C 07 00 00 84 03 00 00 0A 00 00 00 31` | `DB 00 31` |
| 3 | `DA 02 D0 07 00 00 E8 03 00 00 0B 00 00 00 34 08 00 00 4C 04 00 00 0C 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `none` |
| 4 | worker 0x1D380 | flash ops: erase4k 0x161000, write 0x161000 len 0xC0, erase4k 0x162000, write 0x162000 len 0x4B0, read 0x162000 len 0x4B0 |
| 5 | tx service 0x133BC | addr 26 `DB 00 31` |
| 6 | `D8 02 31` | `none` |
| 7 | worker 0x1D380 | flash ops: read 0x162000 len 0x4B0 |
| 8 | tx service 0x133BC | addr 26 `D9 02 E8 03 00 00 00 00 00 00 01 00 00 00 4C 04 00 00 64 00 00 00 02 00 00 00 B0 04 00 00 C8 00 00 00 03 00 00 00 14 05 00 00 2C 01 00 00 04 00 00 00 78 05 00 00 90 01 00 00 05 00 00 00 DC 05 00 00 F4 01 00 00 06 00 00 00 40 06 00 00 58 02 00 00 07 00 00 00 A4 06 00 00 BC 02 00 00 08 00 00 00 08 07 00 00 20 03 00 00 09 00 00 00 6C 07 00 00 84 03 00 00 0A 00 00 00 31` |
| 9 | tx service 0x133BC | addr 26 `D9 02 D0 07 00 00 E8 03 00 00 0B 00 00 00 34 08 00 00 4C 04 00 00 0C 00 00 00 31` |
| 10 | tx service 0x133BC | addr 23 `10` |

#### DA validation

| Step | Input | Output |
|---|---|---|
| 1 | `D6 03 56 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 01 02 31` | `D7 00 31` |
| 2 | `DA 03 25 77 00 00 E8 03 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `DB FF 31` |
| 3 | `D6 03 56 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 01 02 31` | `D7 00 31` |
| 4 | `DA 03 24 77 00 00 ED 13 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `DB FF 31` |
| 5 | `D6 03 56 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 01 02 31` | `D7 00 31` |
| 6 | `DA 03 24 77 00 00 EC 13 00 00 97 86 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `DB FF 31` |
| 7 | `D6 03 56 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 01 02 31` | `D7 00 31` |
| 8 | `DA 03 24 77 00 00 03 00 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `none` |
| 9 | `DA 0A 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 31` | `DB FF 31` |
| 10 | `DA 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 31` | `DB FF 31` |
| 11 | `DA 04 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00 31` | `DB FF 31` |

#### D6 edge cases

| Step | Input | Output |
|---|---|---|
| 1 | `D6 00 5A 45 52 4F 00 00 00 00 00 00 00 00 00 00 00 00 01 01 00 31` | `D7 FF 31` |
| 2 | `D6 0B 45 4C 45 56 45 4E 00 00 00 00 00 00 00 00 00 00 01 01 00 31` | `D7 FF 31` |
| 3 | `D6 0A 54 45 4E 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | `D7 00 31` |
| 4 | `D4 31` | `D5 01 31` |
| 5 | `D6 0A 54 45 4E 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 31` | `D7 00 31` |
| 6 | `D4 31` | `D5 00 31` |
| 7 | `D6 01 55 53 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00` | `D7 00` |

#### Deferred replies go to the host link in S+3 (USB, S+3 = 2)

| Step | Input | Output |
|---|---|---|
| 1 | `D6 01 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 01 02` | `D7 00` |
| 2 | `DA 01 64 00 00 00 64 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00` | `none` |
| 3 | worker 0x1D380 | flash ops: erase4k 0x161000, write 0x161000 len 0xC0, erase4k 0x162000, write 0x162000 len 0x4B0, read 0x162000 len 0x4B0 |
| 4 | tx service 0x133BC | addr 21 `DB 00` |
| 5 | `D8 01` | `none` |
| 6 | worker 0x1D380 | flash ops: read 0x162000 len 0x4B0 |
| 7 | tx service 0x133BC | addr 21 `D9 01 64 00 00 00 64 00 00 00 01 00 00 00` |

#### PD profile commands (D0, D2, E4)

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | S+0x3=1 | 6 | `D2 01 50 44 36 35 00 00 00 00 00 00 00 00 00 00 00 00 41 03 01 2C 91 01 0A 2C 91 01 0A 2C 91 01 0A 31` | `D3 00 31` | S+0x27:00>01, S+0x4B:00>01, PD+0x0:00>50, PD+0x1:00>44, PD+0x2:00>36, PD+0x3:00>35, PD+0xA0:00>2C, PD+0xA1:00>91, PD+0xA2:00>01, PD+0xA3:00>0A, PD+0xA4:00>2C, PD+0xA5:00>91, PD+0xA6:00>01, PD+0xA7:00>0A, PD+0xA8:00>2C, PD+0xA9:00>91, PD+0xAA:00>01, PD+0xAB:00>0A, PD+0x208:00>41, XFER+0x0:00>01 | outReq(0) |
| 2 | S+0x3=1 | 6 | `D2 00 58 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 41 00 01 31` | `D3 FF 31` | S+0x4B:00>01, XFER+0x1:00>FF | outReq(0) |
| 3 | S+0x3=1 | 6 | `D2 0B 58 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 41 00 01 31` | `D3 FF 31` | S+0x4B:00>01, XFER+0x1:00>0A | outReq(0) |
| 4 | reset state | 6 | `D2 0A 58 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 8C 09 00 11 22 33 44 11 22 33 44 11 22 33 44 11 22 33 44 11 22 33 44 11 22 33 44 11 22 33 44 11 22 33 44 11 22 33 44 31` | `D3 00 31` | S+0x4B:00>01, PD+0x90:00>58, PD+0x1E4:00>11, PD+0x1E5:00>22, PD+0x1E6:00>33, PD+0x1E7:00>44, PD+0x1E8:00>11, PD+0x1E9:00>22, PD+0x1EA:00>33, PD+0x1EB:00>44, PD+0x1EC:00>11, PD+0x1ED:00>22, PD+0x1EE:00>33, PD+0x1EF:00>44, PD+0x1F0:00>11, PD+0x1F1:00>22, PD+0x1F2:00>33, PD+0x1F3:00>44, PD+0x1F4:00>11, PD+0x1F5:00>22, PD+0x1F6:00>33, PD+0x1F7:00>44, PD+0x1F8:00>11, PD+0x1F9:00>22, PD+0x1FA:00>33, PD+0x1FB:00>44, PD+0x1FC:00>11, PD+0x1FD:00>22, PD+0x1FE:00>33, PD+0x1FF:00>44, PD+0x200:00>11, PD+0x201:00>22, PD+0x202:00>33, PD+0x203:00>44, PD+0x204:00>11, PD+0x205:00>22, PD+0x206:00>33, PD+0x207:00>44, PD+0x211:00>8C, XFER+0x1:00>09 | outReq(0) |
| 5 | 0x1fffa138=50524f46494c45310000000000000000, 0x1fffa340=100, 0x1fffa1d8=167874860, 0x1fffa1dc=167956781 | 6 | `D0 01 31` | `D1 01 50 52 4F 46 49 4C 45 31 00 00 00 00 00 00 00 00 64 07 2C 91 01 0A 2D D1 02 0A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | - | - |
| 6 | 0x1fffa138=50524f46494c45310000000000000000, 0x1fffa340=101, 0x1fffa1d8=167874860, 0x1fffa1dc=167956781 | 6 | `D0 01 31` | `D1 01 50 52 4F 46 49 4C 45 31 00 00 00 00 00 00 00 00 65 09 2C 91 01 0A 2D D1 02 0A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | - | - |
| 7 | 0x1fffa138=50524f46494c45310000000000000000, 0x1fffa340=100, 0x1fffa1d8=167874860, 0x1fffa1dc=167956781 | 1 | `D0 01` | `D1 01 50 52 4F 46 49 4C 45 31 00 00 00 00 00 00 00 00 64 07 2C 91 01 0A 2D D1 02 0A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00` | S+0x3:00>02 | - |
| 8 | 0x1fffa34a=2 | 6 | `E4 31` | `E5 03 31` | - | - |
| 9 | reset state | 1 | `E4` | `E5 01` | S+0x3:00>02 | - |

#### D2 without save flag leaves S+0x4B = 1

| Step | Input | Output |
|---|---|---|
| 1 | `D2 01 41 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 41 00 00 31` | `D3 00 31` |
| 2 | worker 0x1D380 | flash ops: none |
S+0x4B after: 1

#### D2 with save flag: worker clears S+0x4B

| Step | Input | Output |
|---|---|---|
| 1 | `D2 01 41 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 41 00 01 31` | `D3 00 31` |
| 2 | worker 0x1D380 | flash ops: erase4k 0x160000, write 0x160000 len 0x21C |
S+0x4B after: 0

#### Charge and program/PD telemetry reads (EA, EC, DE)

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | S+0x1ca=1, S+0x1c8:u16=4200, S+0x1c4=3, S+0x1c6:u16=1000, S+0x1cc=1, S+0x1cd=3, S+0x1d0:u32=1234, S+0x1d4:u32=15230, S+0x1d8:u32=3600 | 6 | `EA 31` | `EB 01 68 10 03 E8 03 01 03 D2 04 00 00 7E 3B 00 00 10 0E 00 00 31` | - | - |
| 2 | S+0x1ca=1, S+0x1c8:u16=4200, S+0x1c4=3, S+0x1c6:u16=1000, S+0x1cc=1, S+0x1cd=3, S+0x1d0:u32=1234, S+0x1d4:u32=15230, S+0x1d8:u32=3600 | 1 | `EA` | `EB 01 68 10 03 E8 03 01 03 D2 04 00 00 7E 3B 00 00 10 0E 00 00` | S+0x3:00>02 | - |
| 3 | S+0xe=1, S+0x3a=80, S+0xb4:u16=1000, S+0xd8:u32=250, S+0x7a=1, S+0x79=3, S+0xb2:u16=1180, S+0xdc:u32=2950, S+0xe0:u32=900, S+0xb6:u16=1180, S+0x78=0, S+0x5=1, S+0x30=3, S+0x39=30, S+0x1dc:u32=131073, S+0x9e:u16=16 | 6 | `EC 31` | `ED 01 50 E8 03 FA 00 00 00 01 03 9C 04 86 0B 00 00 84 03 00 00 9C 04 00 01 03 1E 11 00 02 00 31` | - | - |
| 4 | S+0x2=1, S+0xe=0, S+0x3a=77, S+0xac:u16=500, S+0xae:u16=1000, S+0xc8:u32=74565, S+0xd0:u32=3725, S+0xd4:u32=12, S+0xb0:u16=500, S+0x7c:u16=2, S+0x5=1, S+0x30=1, S+0x39=28, S+0x20=0, S+0xb8:u32=4, S+0x1f=0, S+0x9e:u16=0, 0x1fffa980=5000 | 6 | `DE 31` | `DF 01 00 4D F4 01 E8 03 45 23 00 00 0C 00 00 00 F4 01 03 01 01 1C 00 04 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 88 13 00 00 31` | - | - |
| 5 | S+0x2=1, S+0xe=0, S+0x3a=77, S+0xac:u16=500, S+0xae:u16=1000, S+0xc8:u32=74565, S+0xd0:u32=3725, S+0xd4:u32=12, S+0xb0:u16=500, S+0x7c:u16=65535, S+0x5=1, S+0x30=2, S+0x39=28, S+0x20=0, S+0xb8:u32=4294967295, S+0x1f=0, S+0x9e:u16=0, 0x1fffa980=5000 | 6 | `DE 31` | `DF 01 00 4D F4 01 E8 03 8D 0E 00 00 0C 00 00 00 F4 01 01 01 02 1C 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 88 13 00 00 31` | - | - |
| 6 | 0x1fffacac=160, 0x1fffacad=161, 0x1fffacae=162, 0x1fffacaf=163, 0x1fffacb0=164, 0x1fffacb1=165, 0x1fffacb2=166, 0x1fffacb3=167, 0x1fffacb4=168, 0x1fffacb5=169, 0x1fffacb6=170, 0x1fffacb7=171, 0x1fffacb8=172, 0x1fffacb9=173, 0x1fffacba=174, 0x1fffacbb=175, 0x1fffacbc=176, 0x1fffacbd=177, 0x1fff9b3c=16, 0x1fff9b3d=17, 0x1fff9b3e=18, 0x1fff9b3f=19, 0x1fff9b40=20, 0x1fff9b41=21, 0x1fff9b42=22, 0x1fff9b43=23, 0x1fff9b44=24, 0x1fff9b45=25, 0x1fff9b46=26, 0x1fff9b47=27, 0x1fff9b48=28, 0x1fff9b49=29, 0x1fff9b4a=30, 0x1fff9b4b=31, 0x1fff9b4c=32, 0x1fff9b4d=33, 0x1fff9b4e=34, 0x1fff9b4f=35, 0x1fff9b50=36, 0x1fff9b51=37, 0x1fff9b52=38, 0x1fff9b53=39, 0x1fff9b8e=90, S+0x1f=1 | 1 | `DE` | `DF 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 01 A0 A2 A4 A5 A8 A6 AA AC B0 AE 5A 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20 21 22 23 24 25 26 27 00 00 00 00 00 00` | S+0x3:00>02 | - |

#### Maintenance commands, single frames

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | reset state | 6 | `F0 AC 31` | `F1 00 31` | UPD+0x0:00>01 | - |
| 2 | reset state | 1 | `F0 AC` | `F1 00` | S+0x3:00>02, UPD+0x0:00>01 | - |
| 3 | reset state | 6 | `F0 00 31` | `none` | - | - |
| 4 | reset state | 6 | `FE AA 55 31` | `FF AA 55 31` | PWR+0x11D:00>01, GATE+0x108:00>08, GATE+0x109:00>40, K+0x40:00>01, CFG+0x1:00>05, CFG+0x2:00>5A, CFG+0x3:00>01, CFG+0x4:00>03, CFG+0x6:00>1E, CFG+0x9:00>01, CFG+0xA:00>01, CFG+0xB:00>03, CFG+0xF:00>05, CFG+0x10:00>01, CFG+0x11:00>01, CFG+0x12:00>01, CFG+0x13:00>01, CFG+0x14:00>01, CFG+0x15:00>01, CFG+0x1C:00>4A, CFG+0x1D:00>01, CFG+0x1E:00>E8, CFG+0x1F:00>03, CFG+0x20:00>F4, CFG+0x21:00>01, CFG+0x22:00>32, CFG+0x24:00>FE, CFG+0x25:00>10, CFG+0x26:00>68, CFG+0x27:00>10, CFG+0x28:00>04, CFG+0x29:00>10, CFG+0x2A:00>42, CFG+0x2B:00>0E, CFG+0x2C:00>60, CFG+0x2D:00>09, CFG+0x2E:00>08, CFG+0x30:00>E8, CFG+0x31:00>03, CFG+0x32:00>E8, CFG+0x33:00>03, CFG+0x34:00>E8, CFG+0x35:00>03, CFG+0x36:00>E8, CFG+0x37:00>03, CFG+0x38:00>E8, CFG+0x39:00>03, CFG+0x3A:00>E8, CFG+0x3B:00>03, CFG+0x40:00>4A, CFG+0x41:00>01, CFG+0x42:00>E8, CFG+0x43:00>03, CFG+0x44:00>F4, CFG+0x45:00>01, CFG+0x46:00>E8, CFG+0x47:00>03, CFG+0x48:00>E8, CFG+0x49:00>03, CFG+0x4A:00>D0, CFG+0x4B:00>07, CFG+0x4C:00>DC, CFG+0x4D:00>05, CFG+0x4E:00>B8, CFG+0x4F:00>0B, CFG+0x50:00>D0, CFG+0x51:00>07, CFG+0x52:00>88, CFG+0x53:00>13, CFG+0x54:00>B8, CFG+0x55:00>0B, CFG+0x56:00>88, CFG+0x57:00>13, CFG+0x78:00>40, CFG+0x79:00>42, CFG+0x7A:00>0F, CFG+0x7C:00>A8, CFG+0x7D:00>14 | factoryDefaults, defaultsInit, rebootReq(200) |
| 5 | reset state | 6 | `FE 00 00 31` | `FF 00 00 31` | - | - |
| 6 | reset state | 1 | `FE AA 55` | `FF AA 55` | S+0x3:00>02, PWR+0x11D:00>01, GATE+0x108:00>08, GATE+0x109:00>40, K+0x40:00>01, CFG+0x1:00>05, CFG+0x2:00>5A, CFG+0x3:00>01, CFG+0x4:00>03, CFG+0x6:00>1E, CFG+0x9:00>01, CFG+0xA:00>01, CFG+0xB:00>03, CFG+0xF:00>05, CFG+0x10:00>01, CFG+0x11:00>01, CFG+0x12:00>01, CFG+0x13:00>01, CFG+0x14:00>01, CFG+0x15:00>01, CFG+0x1C:00>4A, CFG+0x1D:00>01, CFG+0x1E:00>E8, CFG+0x1F:00>03, CFG+0x20:00>F4, CFG+0x21:00>01, CFG+0x22:00>32, CFG+0x24:00>FE, CFG+0x25:00>10, CFG+0x26:00>68, CFG+0x27:00>10, CFG+0x28:00>04, CFG+0x29:00>10, CFG+0x2A:00>42, CFG+0x2B:00>0E, CFG+0x2C:00>60, CFG+0x2D:00>09, CFG+0x2E:00>08, CFG+0x30:00>E8, CFG+0x31:00>03, CFG+0x32:00>E8, CFG+0x33:00>03, CFG+0x34:00>E8, CFG+0x35:00>03, CFG+0x36:00>E8, CFG+0x37:00>03, CFG+0x38:00>E8, CFG+0x39:00>03, CFG+0x3A:00>E8, CFG+0x3B:00>03, CFG+0x40:00>4A, CFG+0x41:00>01, CFG+0x42:00>E8, CFG+0x43:00>03, CFG+0x44:00>F4, CFG+0x45:00>01, CFG+0x46:00>E8, CFG+0x47:00>03, CFG+0x48:00>E8, CFG+0x49:00>03, CFG+0x4A:00>D0, CFG+0x4B:00>07, CFG+0x4C:00>DC, CFG+0x4D:00>05, CFG+0x4E:00>B8, CFG+0x4F:00>0B, CFG+0x50:00>D0, CFG+0x51:00>07, CFG+0x52:00>88, CFG+0x53:00>13, CFG+0x54:00>B8, CFG+0x55:00>0B, CFG+0x56:00>88, CFG+0x57:00>13, CFG+0x78:00>40, CFG+0x79:00>42, CFG+0x7A:00>0F, CFG+0x7C:00>A8, CFG+0x7D:00>14 | factoryDefaults, defaultsInit, rebootReq(200) |
| 7 | reset state | 6 | `FC 00 31` | `none` | - | - |
| 8 | reset state | 6 | `FC CA 31` | `FD 00 31` | UPD+0x1:00>01 | - |
| 9 | reset state | 6 | `F6 00 31` | `F7 00 FF 31` | - | - |
| 10 | reset state | 6 | `F2 01 31` | `F3 00 FF 31` | UPD+0x0:00>01 | - |
F2 len 0x100: reply F3 00 00 31, 65538 erase64k calls, first ['0x0', '0x10000', '0x20000'], last 0x10000
F2 len 0xFFFF: reply F3 00 00 31, 65538 erase64k calls, first ['0x0', '0x10000', '0x20000'], last 0x10000
F2 len 0x10000: reply F3 00 00 31, 2 erase64k calls, first ['0x0', '0x10000'], last 0x10000
F2 len 0x18000: reply F3 00 00 31, 3 erase64k calls, first ['0x0', '0x10000', '0x20000'], last 0x20000
F2 len 0x20000: reply F3 00 00 31, 3 erase64k calls, first ['0x0', '0x10000', '0x20000'], last 0x20000

#### In-application update sequence (flash modelled)

Data frames are abbreviated; the script builds them in full.

| Step | Input | Output |
|---|---|---|
| 1 | `F0 AC 31` | `F1 00 31` |
| 2 | `F2 00 00 00 01 00 00 01 00 00 31` | `F3 00 00 31` |
| 3 | `F4 00 00 00 01 00` + 128 data bytes (image 0x10000..0x1007F, word 7 = 0x00010040, `FF FF FF FF MP305B` at 0x40) + `31` | `F5 00 00 00 01 00 00 31` |
| 4 | `F4 00 80 00 01 00` + 128 zero bytes + `31` | `F5 00 80 00 01 00 00 31` |
| 5 | `F6 35 00 00 00 01 00 00 01 00 00 C0 92 34 30 31` | `F7 00 FF 31` |
| 6 | `F6 35 00 00 00 01 00 00 01 00 00 C1 92 34 30 31` | `F7 00 00 31` |
| 7 | `20 05 00 00 00 00 00 00 00 80 00 00 00` + 16 zero bytes + data `00 01 .. 7F` + `31` | `20 05 00 00 00 00 00 31` |
| 8 | `20 05 00 00 00 80 00 00 00 80 00 00 00` + 16 zero bytes + data `80 .. FF` + `31` | `20 05 80 00 00 00 00 31` |
| 9 | `20 06 00 00 00 00 00 00 00 00 00 00 00 80 7F 00 00 31` | `20 06 80 7F 00 00 00 31` |
| 10 | `20 06 00 00 00 00 00 00 00 00 00 00 00 81 7F 00 00 31` | `20 86 80 7F 00 00 00 31` |
| 11 | `20 05` offset `0x43000`, length `0x80` | `20 05 00 30 04 00 FF 31` |
| 12 | `20 05` offset `0x100`, length `0x40` | `20 05 00 01 00 00 FF 31` |
| 13 | `20 06 00 00 00 00 00 00 00 00 00 00 00 80 7F 00 00 31` | `20 06 80 7F 00 00 00 31` |
| 14 | as step 7 | `20 05 00 00 00 00 00 31` |
| 15 | as step 8 | `20 05 80 00 00 00 00 31` |
| 16 | `20 06 00 00 00 00 00 00 00 00 00 00 00 80 7F 00 00 31` | `20 06 80 7F 00 00 00 31` |
| 17 | `FC CA 31` | `FD 00 31` |
| 18 | `FC CA 31` | `FD 00 31` |

Flash log (erase runs collapsed):
    erase64k 0x0  x65538
    write 0x10000 0x80 
    read 0x10000 0x80 
    write 0x10080 0x80 
    read 0x10080 0x80 
    erase64k 0xf0000  
    read 0x1001c 0x4 
    write 0x10040 0x4 
    erase64k 0x100000  x4
    write 0x100000 0x80 
    read 0x100000 0x80 
    write 0x100080 0x80 
    read 0x100080 0x80 
    erase64k 0x100000  x4
    write 0x100000 0x80 
    read 0x100000 0x80 
    write 0x100080 0x80 
    read 0x100080 0x80 
    write 0x0 0x4 
    write 0x4 0x4 
    write 0x8 0x4 
    write 0xc 0x4 
    read 0x1f0000 0x100 
    write 0x1f0000 0x1 
    write 0x0 0x4 
    write 0x4 0x4 
    write 0x8 0x4 
    write 0xc 0x4 
    read 0x1f0000 0x100 
    write 0x1f0000 0x1 
    write 0x1f0001 0x1 
SPI 0x0..0x10: 00010000c19234300001000033cc55aa
SPI 0x10040..: 33cc55aa4d5033303542000000000000
SPI 0x1F0000..: 0003ffffffffffff
SPI 0x100000..: 000102030405060708090a0b0c0d0e0f
UPD block: 0001000000010000c192343000010000 sum 0x0 A0A0 0x7f80
S+0x3F (update-ready) 0  A00D 1
total word sum used: 0x303492c1

#### Deferred and unsolicited frames built by the transmit service 0x133BC

| Case | Flag bits (0x1FFF9550) | State | Frames sent |
|---|---|---|---|
| remote grant allowed, DC | 0x0004 | S+0x3=1, S+0x42=1, S+0x45=1, S+0x30=0 | addr 26 `C9 00 31` |
| remote grant denied, DC | 0x0004 | S+0x3=1, S+0x42=0, S+0x45=0, S+0x30=0 | addr 26 `C9 01 31` |
| remote grant allowed, Prog | 0x0004 | S+0x3=1, S+0x42=1, S+0x45=1, S+0x30=1 | addr 26 `E3 00 31` |
| remote grant allowed, PD | 0x0004 | S+0x3=1, S+0x42=1, S+0x45=1, S+0x30=2 | addr 26 `E9 00 31` |
| remote grant denied, Charge | 0x0004 | S+0x3=1, S+0x42=0, S+0x45=0, S+0x30=3 | addr 26 `EF 01 31` |
| remote grant, USB link | 0x0004 | S+0x3=2, S+0x42=1, S+0x45=1, S+0x30=0 | addr 21 `C9 00` |
| remote grant, no link | 0x0004 | S+0x3=0, S+0x42=1, S+0x45=1, S+0x30=0 | nothing |
| bind allowed, BLE | 0x0002 | S+0x3=1, S+0x46=1, 0x1ffe018a=6 | addr 26 `19 00 00` |
| bind denied, BLE | 0x0002 | S+0x3=0, S+0x46=0, 0x1ffe018a=6 | addr 26 `19 FF 00` |
| settings push | 0x1000 | S+0x3=1, S+0x2d=90, S+0x32=3 | addr 26 `C5 5A 03 00 00 00 00 00 00 00 00 00 31` |
| active PD profile push | 0x0400 | S+0x3=1, 0x1fffa34a=1 | addr 26 `E5 02 31` |
| charge settings push | 0x0800 | S+0x3=1, S+0x1ca=2 | addr 26 `EB 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` |
| selected program push | 0x0200 | S+0x3=1, 0x1fffa3fe=1, 0x1fffa3f4=4 | addr 26 `DD 01 04 31` |
| program saved | 0x0100 | S+0x3=1 | addr 26 `DB 00 31` |
| program saved, USB | 0x0100 | S+0x3=2 | addr 21 `DB 00` |
| ask companion identity | 0x2000 | S+0x3=1 | addr 23 `E0` |
| companion update prepare | 0x4000 | S+0x3=1 | addr 23 `F0 AC` |
| bit 3 | 0x0008 | S+0x3=1 | addr 25 `B8 B0` |
| bit 6 | 0x0040 | S+0x3=1 | addr 25 `BE` |
| bit 0, ab1c=1 | 0x0001 | S+0x3=1, 0x1ffe018c=1, 0x1fffab1c=1 | addr 23 `52 53` |
| bit 0, ab1c=0 | 0x0001 | S+0x3=1, 0x1ffe018c=1, 0x1fffab1c=0 | addr 23 `52 20` |
| link state change notice | 0x0000 | S+0x3=1, 0x1ffe018c=0, 0x1fffab1c=1 | addr 23 `50 01` |
| idle heartbeat | 0x0000 | S+0x3=1 | addr 23 `10` |

#### Further edge cases

| # | Setup | Type | Request | Reply | State changes | Calls |
|---|---|---|---|---|---|---|
| 1 | reset state | 6 | `20 07 31` | `31` | - | - |
| 2 | reset state | 1 | `20 07` | `none` | S+0x3:00>02 | - |
| 3 | reset state | 6 | `D0 00 31` | `D1 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 07 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 31` | - | - |
| 4 | reset state | 3 | `E0` | `E1 4D 50 33 30 35 42 00 00 00 00 00 00 00 00 00 00 01 06 00 33 4D 50 33 30 35 42 00 00 00 00` | - | - |

## 12. Comparison with docs/research

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
| `wavePause` waveform streaming active flag | Corrected (inferred from all writers): 1 whenever the device's own waveform page timer is not running, which is every state found; it does not reflect host streaming |
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
| 9..15 charger faults | Corrected: never set in `S+0x9E` (the `C3` field). Charger bits 10 and 11 exist only in the charger word merged into `EC` |

### protocol.md 4.6

| Statement | Verdict |
|---|---|
| `18`/`19` behaviour | Confirmed |
| `A0`/`A2` behaviour | Confirmed |
| `DA` limits | Confirmed; the third word is seconds |
| PD profile is 16 bytes, a class byte and 7 or 9 groups; `E4` is index + 1 | Confirmed; the 16 bytes are the name, the class is the wattage |
| `EA` 20 payload bytes, `EC` 30, `DE` 68 | Confirmed |
| `20` is a block write replying `20`; `FE` not a bootloader entry | Confirmed for `20`; `FE AA 55` is corrected to factory reset plus reboot |
