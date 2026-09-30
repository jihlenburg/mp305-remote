# ISDT MP305B protocol reference

Protocol notes. The device firmware is the main source of truth. Findings
from the JavaScript of ISDT's WebLink page, from captures of the author's
unit, and from anywhere else come on top of that firmware. Each item carries
an evidence label. Information read from the device firmware is used to its
fullest, with no limit on what it covers (ADR-0010). Where the firmware and
another finding differ, the project uses the firmware. For other sources,
only items marked confirmed on hardware may be relied on without a TBD
(ADR-0002).

Date gathered: 2026-09-29.

Sources, with the firmware first:
- Device firmware, the main source of truth. USB descriptor tables in the
  plain 1.6.0.51 image (product ID, endpoint layout, report ID 2), produced
  by WebLink's own restore routine (LOGBOOK 2026-09-29, "Research: firmware
  manifests, firmware file and WebLink source maps"). Decompiling the device
  firmware is fully allowed under Directive 2009/24/EC (2009/24/EG) so that
  `mp305` and `mp305-app` interoperate with the device. There is no limit on
  the information in that image, and it is used to its fullest. The image
  itself stays out of the repository. The interoperability information
  gathered from it is recorded here, in whatever form it takes (AGENTS.md,
  ADR-0010).
- ISDT WebLink production assets (`index-NNOthY3Q.js`,
  `mp305Component-DXYvqvMA.js`, `headComponent-DKj48EA9.js`,
  `otaResp-CS2cFNEZ.js`, `updateOta-BdJVsDR4.js`). Findings from these files
  come on top of the firmware.
- Hardware captures: `docs/research/captures/2026-09-29T193614-ble-readonly.jsonl`,
  `2026-09-29T194219-ble-readonly.jsonl`, `2026-09-29T194319-ble-readonly.jsonl`,
  and `2026-09-29T201428-ble-readonly.jsonl`. Findings from these captures
  come on top of the firmware.

Evidence labels used in this document:
- **confirmed in code**: directly read and verified from the decompiled
  device firmware, or from WebLink JavaScript. A WebLink reading is a
  finding on top of the firmware.
- **confirmed on hardware**: verified against physical device captures. A
  hardware observation is a finding on top of the firmware.
- **inferred**: deduced from arithmetic, context or structure; not read from
  the firmware and not verified by hardware capture.

---

## 1. Transports

### 1.1 USB HID

- **Device identification:** Vendor ID `0x28E9` (10473, GigaDevice Semiconductor),
  Product ID `0x028A`, bcdDevice 2.00. The same image contains the USB
  strings `wch.cn` and `MP305B`, and the device descriptor names string
  indexes 1, 2 and 3 (firmware.md). A USB connection has not been observed
  yet (TBD-013). WebLink filters on
  `{ usagePage: 1, usage: 4, vendorId: 10473 }` and checks that the reported
  product name contains `"MP305B"`, `"MP305A"` or `"MP3010B"` (confirmed in
  code, WebLink). The report descriptor's top-level collection is usage
  page 1, usage 0 (confirmed in code, firmware.md). A WebHID filter on usage
  4 does not describe this descriptor, so whether WebLink enumerates the
  device over USB is part of TBD-013. String index 3 (the serial number) is
  not served: the CH58x stalls that request (confirmed in code, CH58x
  `0x4FBA`). The product string comes from the 8-byte name the main MCU
  stores in the CH58x (`MP305B` in 1.6.0.51).
- **Endpoint configuration** (companion image, firmware 1.6.0.51, firmware.md):
  - Endpoint 1 OUT (`0x01`): Interrupt, 64-byte max packet size, 1 ms interval.
  - Endpoint 1 IN (`0x81`): Interrupt, 64-byte max packet size, 1 ms interval.
  - One HID interface, bcdHID 1.11, report descriptor 35 bytes, configuration
    max power 100 mA.
- **Report IDs** (the 35-byte report descriptor in that companion image):
  - Host to Device (OUT): **Report ID 1**, 63 data bytes.
  - Device to Host (IN): **Report ID 2**, 63 data bytes.
    A USB connection has not been observed yet (TBD-013).
- **Outgoing chunking:**
  Frames longer than 63 bytes are divided into chunks with a stride of 61
  bytes:
  - Report 1: `[60, F[1..=60]]` (byte 0 is overwritten with the chunk count).
  - Subsequent reports: `[n, next <=61 bytes]`.
  - A 5 ms delay follows each transmitted report (confirmed in code).
  Frames of 63 bytes or fewer are transmitted as a single report without
  splitting.
  The 61-byte stride and the 5 ms delay are WebLink's choices. The CH58x
  reads the byte after the report ID as the number of stream bytes in that
  report, accepts any value from 1 to 62, and reassembles across reports
  (confirmed in code, CH58x `0x4E86`). It holds one frame per direction:
  a frame must not share a report with another frame, and a new frame must
  not start before the reply to the previous one has arrived (confirmed in
  code, CH58x `0x3662` and `0x4628`).
- **Incoming de-stuffing and reassembly:**
  The firmware doubles `0xAA` throughout the framed body, including
  address, length, opcode/data and checksum; the leading delimiter is single. WebLink de-stuffs reports
  before frame reassembly:
  - *Quirk in WebLink:* The web app loop does not reset its skip flag, causing
    runs of four `0xAA` bytes to collapse into a single byte. Implementations
    must de-stuff strictly in pairs (`0xAA 0xAA` -> `0xAA`).
  - *Reassembly:* Multi-report replies (used for `0xD5`, `0xD9`, `0xDF`) arrive
    in several reports. In every report the byte after the report ID is the
    number of valid stream bytes in that report, from 1 to 62, not a chunk
    count (confirmed in code, CH58x `0x4ECA` and `0x3E1A`). The complete
    frame is formed when the accumulated payload length matches the length
    declared in the frame header. Replies carry address `0x21`.
  - WebLink does not verify the checksum or address byte on incoming frames
    (confirmed in code).

### 1.2 Bluetooth LE

- **Advertisement:**
  - Local name prefix: `0000MP30` (confirmed in code and confirmed on
    hardware). WebLink trims the first four characters (`0000`) before
    displaying the model name.
  - Service UUID: `0000af00-0000-1000-8000-00805f9b34fb`.
  - Manufacturer data: Company ID `0xABBA`, payload prefix `affa0135`
    (confirmed on hardware).
  - The CH58x builds the name and the manufacturer data at run time
    (confirmed in code, CH58x `0x6CB0`, `0x7106`, `0x7532`; firmware.md).
    The name is `0000`, then the 8-byte name the main MCU sends to the CH58x
    (`MP305B` and two spaces in 1.6.0.51), then `S` while remote control is
    enabled and no USB host is active, then spaces, then three characters
    derived from the Bluetooth address. The captured name
    `0000MP305B  S             E!K` decodes that way. In the manufacturer
    data `AF FA` is fixed, `01 35 02 00` comes from the main MCU, and the
    last 14 bytes are a host-writable tail that is zero unless a host wrote
    it. The advertising interval is 500 ms; advertising is off while a host
    is connected, while a USB host is active, and while remote control is
    disabled on the device.
- **GATT services and characteristics:**
  - Service `0xAF00`:
    - Characteristic `0000af01-0000-1000-8000-00805f9b34fb` (**AF01**):
      Application commands and replies. Read, write, notify. The CH58x
      discards the first byte of every AF01 write without looking at it, so
      the leading `0x12` is a placeholder (confirmed in code, CH58x
      `0x72A6`). Opcodes `0x10` and `0xC0` on AF01 are handled inside the
      CH58x and rewrite its advertising data; a client must never send them
      (confirmed in code, CH58x `0x4224`). Reads return 20 zero bytes.
    - Characteristic `0000af02-0000-1000-8000-00805f9b34fb` (**AF02**):
      Bind request/response (`0x18`/`0x19`). Any other opcode written here,
      including `0xE0`, is forwarded to the main MCU like an AF01 write and
      answered on AF02 without the `0x31` prefix. Two opcodes are answered
      by the CH58x itself: `0x00` (13 bytes: `01`, link state, bind state,
      a 32-bit connection timer, the 6-byte Bluetooth address) and `0x18`
      with a non-zero last byte (see 1.3) (confirmed in code, CH58x
      `0x40DC`). Read, write, notify.
  - Service `0xFEE0`, Characteristic `0xFEE1`: Bootloader OTA service only
    (confirmed in code, WebLink). It is not in the 1.6.0.51 CH58x
    application image (confirmed in code).
- **GATT table** (confirmed on hardware, capture `2026-09-29T193614`):

  | Service | Characteristic | Properties |
  |---|---|---|
  | `180A` Device Information | `2A23` to `2A2A`, `2A50` | read |
  | `AF00` | `AF01` | notify, write, read |
  | `AF00` | `AF02` | notify, write, read |
  | `DB00` (not used by WebLink) | `DB01` | notify, write, read |

  `DB01` is inert in 1.6.0.51: its read and write hooks are empty and
  nothing ever notifies on it (confirmed in code, CH58x `0x6CAE`, `0x7104`).

  The `FEE0` service is absent in normal operation. The Device Information
  service holds placeholder strings from the Bluetooth chip vendor's SDK and
  must not be used for identity or versions (confirmed on hardware). The
  negotiated MTU on macOS was 247 (confirmed on hardware).
- **Advertising while connected:** the device was not seen while WebLink in
  Chrome was probably still connected, and was seen after the tab closed.
  A peripheral normally stops advertising while a central is connected
  (inferred). Advertisements arrive several seconds apart, so discovery needs
  a scan window of at least 10 s (confirmed on hardware).
- **Connection rule:**
  Notifications must be enabled on both `AF01` and `AF02` before transmitting
  commands (confirmed in code). The CH58x drops a reply whose characteristic
  has notifications off, and the main MCU then retransmits it for about 5 s;
  both CCCDs are reset on every disconnect (confirmed in code, CH58x
  `0x6F6C`, `0x6FF6`, `0x2C02`). The CH58x does not start an MTU exchange;
  it accepts up to 247. It holds one frame per direction, so a client keeps
  one request in flight and writes with response.
- **Framing on BLE:**
  BLE uses unpadded, un-stuffed frames without outer length or checksum bytes
  because the BLE Link Layer provides framing and CRC. Packets are transmitted
  in single writes/notifications without chunking. An ATT MTU >= 126 is
  required for full-size frames (confirmed in code). Device replies on AF01
  carry prefix byte `0x31` (confirmed on hardware). The CH58x code identifies
  it as the AF01 route marker, appended internally and moved to the reply's
  front, rather than a UART address. Writes with response
  work on AF01 and AF02 (confirmed on hardware). Round trip from a read request
  to its notification was 120 to 135 ms (confirmed on hardware).

### 1.3 Bluetooth bind handshake

After enabling notifications, WebLink waits 1000 ms and writes a bind frame
to AF02 (confirmed in code). The frame WebLink sends, and the only one tested,
is:

```
18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00
```

WebLink names the fields a class byte, a 16-byte host ID (a constant, the
same for every browser), `fastBinding` (0) and a status byte (confirmed in
code, WebLink). The CH58x reads bytes 1 to 16 of the write as the host ID
and the last byte of the write as the fast flag, and ignores the bytes in
between (confirmed in code, CH58x `0x40DC`). In WebLink's frame the ID is
therefore `00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00` and the fast
flag is 0.

| Observation | Evidence |
|---|---|
| The device shows an allow or deny prompt on its screen at every connection. The reply comes when a person presses a button: 7.7 s, 3.0 s and 3.6 s in the three allow runs. | confirmed on hardware (captures `193614`, `194219`, `201428`) |
| `19 00` means allowed, `19 FF` means denied. | confirmed on hardware (captures `193614`, `194319`) |
| The device does not remember an allowed host when the WebLink bind frame is used. | confirmed on hardware (capture `194219`) |
| After a deny, `0xC4`, `0xC2` and `0xE0` on AF01 are still answered. Binding does not protect reading. | confirmed on hardware (capture `194319`) |
| Whether `0xC8` is accepted without a successful bind on hardware. | not tested on hardware; V51 separately checks remote-control grant, see firmware-permissions.md |
| Whether `fastBinding = 1` or a host-specific ID lets the device remember a host. | not tested on hardware. In code: after a `19 00` the CH58x stores the host ID (up to five, oldest dropped). A later `0x18` with the same ID and a non-zero last byte is answered `19 00` by the CH58x without a prompt; an unknown ID gets `19 FF`. A stable, host-specific ID is what makes this work (confirmed in code, CH58x `0x773C`, `0x7696`) |
| Whether USB HID shows the same prompt. | not tested on hardware. In code: the CH58x has no bind logic for USB; the main MCU answers a USB `0x18` the same way as a Bluetooth one, through the prompt. Remote control over USB (`0xC8` with `remoteCon = 2`) is granted at once without a prompt (confirmed in code, `0x1B7F4`) |
| How long the device waits for a button press before giving up, and what it then replies. | not tested on hardware. In code: the CH58x terminates a link that has not been bound about 30 s after it connected (confirmed in code, CH58x `0x6CB0`). The main MCU's prompt closes on its own after tens of seconds and the deferred reply is then `19 FF` (inferred from the shared popup timer code) |

The V51 code keeps binding and remote-control permission separate. It
also accepts C6 settings writes on the traced path without either grant.
See [the command-specific permission analysis](firmware/permissions.md)
for original-instruction checks and the limits of this conclusion.

---

## 2. Frame encoding

### 2.1 Comparison: HID vs BLE

| Parameter | USB HID | BLE (AF01) | BLE (AF02) |
|---|---|---|---|
| TX structure | `[cnt] AA 12 plen cmd payload... cksum` | `12 cmd payload...` | `cmd payload...` |
| RX structure | `[cnt] AA addr plen cmd payload... cksum` | `addr cmd payload...` | `cmd payload...` |
| Opcode index (RX) | Index 4 | Index 1 | Index 0 |
| Payload index (RX) | Index 5 | Index 2 | Index 1 |
| Checksum | 8-bit additive sum | None | None |
| Byte stuffing | `0xAA` doubled throughout framed body (firmware) | None | None |

The address byte is `(source << 4) | destination`. `0x12` means source 1
(the USB host) and destination 2 (the main MCU). The main MCU replies with
the nibbles swapped, so USB replies carry `0x21` (confirmed in code,
`0x1FEDC`). On AF01 the leading `0x12` is discarded by the CH58x and the
`addr` in front of replies is the constant route tag `0x31` (section 1.2).

### 2.2 HID frame structure

```
Byte 0:      Count of remaining bytes in this report (1 byte)
Byte 1:      Start of frame magic: 0xAA
Byte 2:      Address: 0x12 (source 1 = USB host, destination 2 = main MCU)
Byte 3:      Payload length: plen (count of bytes from cmd through payload)
Byte 4:      Command opcode (1 byte)
Byte 5..N-1: Payload data (bytes with value 0xAA are doubled to 0xAA 0xAA)
Byte N:      Checksum: 8-bit sum of bytes 2 through N-1 (modulo 256)
```

If the calculated checksum byte equals `0xAA`, an additional `0xAA` is
appended, and the leading count byte is incremented by 1 (confirmed in code,
WebLink).

Image 1.6.0.51 implements this in the application. Outbound doubling is
`0xFFF0`: a byte equal to `0xAA` is stored twice. Inbound parsing is
`0xFF38`. A single `0xAA` is not passed into the body. A second `0xAA` is
parsed as a data byte `0xAA`. A non-`0xAA` that arrives while a `0xAA` is
outstanding starts the frame, and that non-`0xAA` is the first body byte.
The parser splits that byte into a high nibble and a low nibble and does
not compare it with `0x12`. The whole byte initialises the checksum. The
next byte is a length. That many following bytes are buffered and added to
the checksum, and the byte after them is compared with the sum. The sum
covers the first body byte, the length, and the buffered bytes, which is
the coverage in the diagram above (firmware.md).

---

## 3. Opcode matrix

Request and response opcodes are paired: **Response = Request + 1**. Image
1.6.0.51 follows that for every handler that builds a reply, except `0x20`,
which replies with `0x20`. `0xD8` and `0x18` schedule deferred replies,
`0xD9` and `0x19`, through workers outside the immediate dispatcher.

| Request | Response | Name in code | Mode | Description |
|---|---|---|---|---|
| `0xE0` | `0xE1` | `INFO_DATA` | All | Device version and model name. Two layouts (4.4) |
| `0x18` | `0x19` | `bind` | BLE (AF02) | Deferred UI decision or BLE saved-host lookup; see firmware-permissions.md |
| `0xC2` | `0xC3` | `INFO_DATA` | 0 (DC) | Live power supply telemetry |
| `0xC4` | `0xC5` | `SEARCH_DATA` | All | Read system configuration |
| `0xC6` | `0xC7` | `systemSetCmd` | All | Write system configuration |
| `0xC8` | `0xC9` | `connectCmd` | 0 (DC) | Write voltage, current, output, mode |
| `0xBD` | none | `RealTime_DATA` | All | Firmware updates connection state and peer metadata; WebLink name is not a proven waveform trigger |
| `0xD0` | `0xD1` | `pdoSearchCmd` | 2 (PD) | Read USB-PD profile |
| `0xD2` | `0xD3` | `pdoWriteCmd` | 2 (PD) | Write USB-PD profile |
| `0xD4` | `0xD5` | `Programmable_DATA` | 1 (Prog) | Read program sequence list |
| `0xD6` | `0xD7` | `ProgrammableChangeCmd` | 1 (Prog) | Modify program header / delete |
| `0xD8` | `0xD9` deferred | `ProgrammableREADCmd` | 1 (Prog) | Selects a program ID, loads storage, then returns chunks of up to ten 12-byte records |
| `0xDA` | `0xDB` | `ProgrammableWriteCmd` | 1 (Prog) | Write program step details |
| `0xDC` | `0xDD` | `ProgrammableMain_DATA` | 1 (Prog) | Read currently selected program |
| `0xDE` | `0xDF` | `ProgrammableInfo_DATA` | 1, 2 | Live telemetry for Prog and PD modes |
| `0xE2` | `0xE3` | `ProgrammableConnectCmd` | 1 (Prog) | Program run/pause/step control |
| `0xE4` | `0xE5` | `PDOMain_DATA` | 2 (PD) | Read active USB-PD PDO index |
| `0xE8` | `0xE9` | `pdoConnectCmd` | 2 (PD) | USB-PD source enable and selection |
| `0xEA` | `0xEB` | `ChargeSearch_DATA` | 3 (Charge) | Read battery charger settings |
| `0xEC` | `0xED` | `ChargeInfo_DATA` | 3 (Charge) | Live battery charger telemetry |
| `0xEE` | `0xEF` | `chargeConnectCmd` | 3 (Charge) | Battery charger control |
| `0xA2` | `0xA3` | `setLanguage` | All | Language selection (0 English, 1 Chinese) |

Image 1.6.0.51 dispatches these from the application at `0x2F34`
(firmware.md). Handlers that build a reply use request + 1 as the response
opcode, except `0x20`, which replies with `0x20`. `0x18` sets a flag and
does not assemble `0x19` in the dispatcher. The deferred builder at
processor address `0x12690` emits it after a UI decision. This reply has
also been seen on hardware. The same switch also accepts `0x00`, `0x20`, `0x51`, `0x53`,
`0xA0`, `0xBB`, `0xBE` and commands from `0xF0` to `0xFE`. Those have no
WebLink name. A request the switch does not recognise gets no reply. The
byte maps for the program, PD, charge and maintenance commands are in
firmware.md. v1 still sends only `0x18`, `0xE0`, `0xC2` and `0xC8` (SR-006).

---

## 4. Payload layouts

All multi-byte numeric fields are little-endian. Offsets are relative to the
start of payload (Index 5 on HID, Index 2 on BLE AF01).

### 4.1 DC live telemetry: `0xC2` -> `0xC3` (confirmed in code)

The 1.6.0.51 handler at `app.bin` `0x58BC` always writes this whole table,
through `waveTime`, and returns 37 bytes including the response opcode
(firmware.md). The field order below matches that copy.

| Offset | Type | Field | Unit / Scaling |
|---|---|---|---|
| 0 | `u8` | `outState` | 0 = output off (confirmed in code), 1 = Constant Voltage (CV), 2 = Constant Current (CC), 3 = measured voltage held more than 100 mV above the setpoint at low current (inferred) |
| 1 | `u8` | `batteryState` | Internal battery status enum |
| 2 | `u8` | `percentage` | Internal battery state of charge (0 to 100 %) |
| 3 | `u16` | `voltage` | Measured terminal voltage in **10 mV** (`/100` -> V) |
| 5 | `u16` | `setVoltage` | Active voltage setpoint in **10 mV** |
| 7 | `u16` | `current` | Measured current in **1 mA** (`/1000` -> A) |
| 9 | `u16` | `setCurrent` | Active current limit in **1 mA** |
| 11 | `u32` | `workingTime` | Output active time in **seconds** |
| 15 | `u32` | `energy` | Accumulated energy in **0.1 Wh** |
| 19 | `u16` | `power` | Output power in **10 mW** (`/100` -> W) |
| 21 | `u8` | `currentOver` | Current limit behavior set on the supply: 0 = limit (CC), 1 = switch off (OCP mode). A setting, not a trip indicator |
| 22 | `u8` | `realChange` | Bit 0: live voltage updates; Bit 1: live current updates |
| 23 | `u8` | `voltageSlow` | 0 = step output, 1 = ramp output at the settings' ramp step rate |
| 24 | `u8` | `output` | 0 = Output OFF, 1 = Output ON |
| 25 | `u8` | `model` | Active mode: 0 DC, 1 Prog, 2 PD, 3 Charger |
| 26 | `u8` | `voltageBoard` | UI keypad input flag |
| 27 | `u8` | `currentBoard` | UI keypad input flag |
| 28 | `u8` | `temperature` | Signed 8-bit temperature in **°C**, the sensor the firmware uses for the battery protections (confirmed in code) |
| 29 | `u16` | `chargeError` | Fault/protection bitmask (optional, see Section 4.5) |
| 31 | `u8` | `wavePause` | 1 whenever the device's own waveform page timer is not running, which is every state found; not a host streaming flag (confirmed in code) |
| 32 | `u32` | `waveTime` | Raw output-on time in milliseconds, the uncalibrated counter behind `workingTime`; reset by `refresh` and by a mode change (confirmed in code) |

Hardware evidence for `0xC3` (captures `193614`, `201428`, and the WebLink
screenshots in LOGBOOK 2026-09-29):
- Over Bluetooth the frame is 38 bytes including the address byte, which is
  the full layout with the optional fields (confirmed on hardware).
- Confirmed on hardware: `setVoltage` (1300 = 13.00 V) and `setCurrent`
  (1000 = 1.000 A) against the device screen, `output` = 0 with the output
  off, `percentage` = 90, `temperature` (26 and 27 °C, matching WebLink),
  `currentOver` = 0 shown by WebLink as CC, and `workingTime`, `energy` and
  `power` matching WebLink's display.
- `outState` read 0 with the output off. The firmware writes 0 at switch-off
  and 1 at switch-on (confirmed in code, commands.md 7.1).
- Measured `voltage`, `current`, `outState` 1 and 2, and every
  `chargeError` bit other than all zeros have not been seen on hardware yet,
  because the output has never been switched on.

### 4.2 DC control: `0xC8` -> `0xC9` (confirmed in code, never sent to hardware)

WebLink first sends `0xC8` with `remoteCon = 2` to request remote control,
then sends every change as a complete `0xC8` with `remoteCon = 1`
(confirmed in code).

Payload length: 11 bytes. The command transmits complete state:

| Offset | Type | Field | Meaning |
|---|---|---|---|
| 0 | `u8` | `remoteCon` | 0 = Release remote, 1 = Remote active, 2 = Request remote |
| 1 | `u16` | `setVoltage` | Target voltage in **10 mV** (e.g. 1200 = 12.00 V) |
| 3 | `u16` | `setCurrent` | Target current in **1 mA** (e.g. 1000 = 1.000 A) |
| 5 | `u8` | `realChange` | Bit 0: V live, Bit 1: I live |
| 6 | `u8` | `voltageSlow` | 0 = step output, 1 = ramp output |
| 7 | `u8` | `currentOver` | 0 = CC mode, 1 = OCP mode |
| 8 | `u8` | `output` | 0 = Output OFF, 1 = Output ON |
| 9 | `u8` | `model` | Target mode (0 = DC) |
| 10 | `u8` | `refresh` | 1 = Reset cumulative counters, 0 = normal |

Response `0xC9`:
- `payload[0] == 0`: Command accepted.
- `payload[0] == 1`: Remote control revoked or not granted.
- `payload[0] == 0xFF`: the 1.6.0.51 handler's explicit reject (firmware.md).
  WebLink treats any other value as rejected.

In image 1.6.0.51 the handler at `0xB7F4` rejects a voltage above 3050
(30.50 V in 10 mV steps) and a current above 5100 (5.100 A in 1 mA steps).
It returns `0xFF` when the live mode byte is not 0, but the common
remote-control epilogue can still change grant/request state. A later
invalid field can preserve earlier valid stores; failure is not rollback.
`remoteCon` above 2 is rejected. `remoteCon` 1 is applied only when remote
control is already granted. What the output hardware does at 30.50 V or
5.100 A is still TBD-003.

### 4.3 System settings: `0xC4` -> `0xC5` (read), `0xC6` -> `0xC7` (write)

`0xC5` response payload (confirmed in code). The 1.6.0.51 handler at
`0x5EF8` always writes the 11 payload bytes below, including `usbLine`, and
returns 12 including the response opcode (firmware.md). Over Bluetooth the
reply is 13 bytes including the address byte (confirmed on hardware). The
OCP delay of 50 ms decoded from the user's unit is unchecked, TBD-016. The
decoded values still need a check against the device's settings menu:
- Offset 0 (`u8`): `perLimit` (battery charge limit %: 80, 85, 90, 95, 100).
- Offset 1 (`u8`): `volume` (0 muted, 1 low, 2 medium, 3 high).
- Offset 2 (`u8`): `screenOff` (0 off, 1 30 s).
- Offset 3 (`u8`): `shutdown` (auto-off in minutes: 0 off, 5, 10, 15, 20, 30).
- Offset 4 (`u8`): `screenDirection` (display orientation).
- Offset 5 (`u16`): `slopeSteps` (ramp step in **mV per 0.1 s**, 100 to 1000).
- Offset 7 (`u16`): `currentOver` (OCP delay in **ms**, 50 to 1000).
- Offset 9 (`u16`): `usbLine` (optional, USB cable compensation in mV at 5 A).

The discrete lists and the units in those bullets are WebLink's. The `0xC5`
handler copies the bytes and does not contain the units. The ranges the
image accepts on a write are the table below.

`0xC6` in image 1.6.0.51, handler `0xCAA4`, checks the fields in this order
and stops at the first failure. Status `0` accepts, status `0xFF` rejects.
The handler does not read the output byte.

| Payload | Firmware check | Stored at |
|---|---|---|
| 0 | 80 to 100 | the `perLimit` byte |
| 1 | 0 to 3 | `volume` |
| 2 | 0 or 1 | `screenOff` |
| 3 | 0 to 30, any byte | `shutdown` |
| 4 | 0 or 1, or the command is rejected | not stored. `0xC5` still returns `S+0x2F` |
| 5, u16 | 0 to 1000 | `slopeSteps` |
| 7, u16 | 0 to 1000 | the OCP delay |
| 9 | 0 or 1 | `S+0x35`, not in the `0xC5` reply |
| 10 | 0 or 1 | `S+0x36`, not in the `0xC5` reply |
| 11, u16 | 0 to 1000 | `usbLine`, and a flag byte is set |

The `usbLine` u16 that `0xC5` returns at offset 9 is the u16 this write
takes at offset 11. WebLink describes the write as the read fields followed
by `systemCheck` and `recover`, lists shutdown as 0, 5, 10, 15, 20 or 30,
slope as 100 to 1000, and the OCP delay as 50 to 1000, and it allows a
settings write whenever the output is off. Those are findings on top of
this image. The project uses the table. The deferred firmware worker at processor
address `0x128A4` rounds selected accepted values upward to entries in
discrete tables; see firmware.md. v1 does not write settings.

### 4.4 Device info: `0xE0` -> `0xE1`

Image 1.6.0.51, handler `0xB634`, has two layouts. The channel record's type
byte selects them. The function does not name a transport (firmware.md).

Type 6 builds 17 bytes after the opcode internally. The final byte is a
bridge route suffix, removed before a BLE notification, leaving 16
payload bytes on AF02 (and an address prefix on AF01):

| Offset | Bytes |
|---|---|
| 0 | `01 06 00 33`, application version 1.6.0.51 |
| 4 | `MP305B` and two zero bytes |
| 12 | `02 00 02 00`, hardware revision 2.0.2.0 |
| 16 | One trailing request byte, present because the type is 6 |

Any other type returns 30 payload bytes:

| Offset | Bytes |
|---|---|
| 0 | `MP305B` and two zero bytes. The model name, not a serial number |
| 8 | Eight bytes through the pointer at absolute `0x1C`, plus `0x0C`; the pointed-to boot identity is missing from this update |
| 16 | `01 06 00 33` |
| 20 | `MP305B` and two zero bytes |
| 28 | Two zero bytes |

WebLink's USB field list (8-byte serial, hardware, bootloader, application,
10-byte name) is a finding on top of these two layouts. It has not been seen
on a USB connection (TBD-010).

Bluetooth, on AF02 without an address byte and on AF01 with address byte
`0x31`, matches the type 6 field order (confirmed on hardware, captures
`193614` to `201428`, and matched against WebLink's display on 2026-09-29).
The running unit reported application version `01 06 00 28` (1.6.0.40).
WebLink labels that field "System Version". The eight name bytes are
`MP305B` padded with zeros, not a serial number. The last four bytes are the
hardware revision `02 00 02 00`. WebLink's English label "Firmware Version"
is a mistranslation of 硬件版本 (hardware version, confirmed in code).

### 4.5 Fault protection bitmask: `chargeError` (confirmed in code)

When non-zero, this 16-bit word indicates an active protection fault. Only
the value 0 has been seen on hardware:
- Bit 0: `OUTPUT_REVERSED` (Output polarity reversed).
- Bit 1: `LOW_BATTERY` (Internal battery low).
- Bit 2: `BATTERY_LOW_TEMP` (Battery temperature too low).
- Bit 3: `BATTERY_OVERHEAT` (Battery overheat).
- Bit 4: `SYSTEM_OVERHEAT` (Power stage overheat).
- Bit 5: `DC_OUT_OCP` (Software over-current protection after the configured delay).
- Bit 6: `DC_OUT_OVP` (Software over-voltage protection, measured voltage at least 33001 mV with a timing guard).
- Bit 7: `DIC_INIT_ERROR` (Digital IC initialization failure).
- Bit 8: `DC_OUT_VOL_FAIL` (Output voltage sensor failure).
- Bits 9 to 15: never set in the `0xC3` word (confirmed in code: every
  producer of `S+0x9E` was traced). Charger bits 10 and 11 exist only in
  the charger word that `0xEC` merges into its payload offset 26.

The recovered [fault-producer table](firmware/v51/independent/notes/commands.md#72-fault-source-0x1fffaa1e-published-to-s0x9e-0x1fffab6a-producer-0x1978c-0x19e68-0x1ab34)
records thresholds, hysteresis and evidence. Physical sensor roles remain
inferred where the circuit has not been identified.

### 4.6 Other commands in image 1.6.0.51

The byte maps are in firmware.md. The points that change how a client reads
the matrix above:

- `0x18` sets `S+0x47` to 1 and stores the type byte. The `0x19` reply is
  built later, at `0x2690`: status 0 when `S+0x46` is not 0, status `0xFF`
  when it is 0. The deny capture is that second case.
- `0xA0` reads the language byte that `0xA2` writes. `0xA2` accepts 0 or 1
  and clamps anything else to 0. Status is always 0.
- Program steps (`0xDA`) reject a first word above 30500 and a second word
  above 5100, unless the third word is 0. The third word must be at most
  99990 when the second is in range. 5100 is the same 5.100 A ceiling as
  `0xC8`. The runner uses millivolts for the first word and seconds for the
  third; duration-zero records also encode Off and Jump operations.
- A PD profile (`0xD0`, `0xD2`) is 16 bytes, a class byte, and 7 or 9 groups
  of 4 bytes. The D2 write includes count and save bytes before its groups;
  the complete request layout is in firmware.md. `0xE4` returns the stored
  index plus 1.
- Charge settings (`0xEA`) are 20 payload bytes. Charge telemetry (`0xEC`)
  is 30. Prog/PD telemetry (`0xDE`) is 68 payload bytes.
- `0x20` is a block write. Its reply opcode is `0x20`, not `0x21`. v1 does
  not send it (UR-025). `FE AA 55` replies `FF AA 55` and schedules a factory
  reset and reboot. Other payloads reply `FF 00 00`. The missing bootloader's
  later behavior is unknown. v1 does not send it either.

---

## 5. Safety considerations for client design

1. **Full-state command (confirmed in code).** `0xC8` carries voltage,
   current limit, output state, mode and ramp flag together. A client that
   sends it from stale or default values can switch the output on or off, or
   undo a change made on the front panel. A client must read `0xC3` right
   before building each `0xC8` and change only the field the user asked for.
2. **No release on disconnect (confirmed in code).** WebLink sends nothing
   when the link closes. In image 1.6.0.51 a link drop clears the
   remote-control grant on the next UI pass and does not touch the output
   enable: the output stays as it was (confirmed in code, `0x1E284`; every
   writer of `0x1FFFAA2E` was traced and none runs on a link drop; not yet
   confirmed on hardware, see the `link_drop` spike). The device treats the
   link as down after `BD 00` from the CH58x, after about 8 s without a USB
   frame, or after about 50 unacknowledged retransmissions. A client must
   send `0xC8` with `output = 0` and `remoteCon = 0` in its orderly shutdown
   path, and over USB it must send a frame at least every 8 s to keep the
   remote grant.
3. **Acknowledgment timing (inferred).** Read requests are answered within
   about 135 ms (confirmed on hardware). The `0xC9` reply time has not been
   measured. A client must treat a missing `0xC9` after a timeout as an
   unknown device state and read `0xC3` again before doing anything else.
4. **Reading is not protected (confirmed on hardware).** The device answers
   reads after the user denies the bind. A client must decide on the bind
   result, not on whether reads work.
5. **Firmware updates (confirmed in code).** WebLink's update flow erases the
   application about 4 s after entering the bootloader and has no timeout or
   abort. An interrupted update can leave the unit in the bootloader. Image
   1.6.0.51 also contains a block-write command, opcode `0x20` (firmware.md).
   v1 does not update firmware and does not send `0x20` (UR-025).
6. **Opcodes a client must never send (confirmed in code).** `0x10` and
   `0xC0` on AF01 rewrite the CH58x's advertising data. `0xBE` is the
   Bluetooth accessory input message; the main MCU does not reject it when
   it arrives from the host route, and it reaches the front-panel input
   path. `0x20` and `0xF0` to `0xFE` are maintenance commands; `FE AA 55` is
   a factory reset followed by a reboot. The remaining values are ignored
   without a reply (commands.md 2.1).
7. **Unsolicited and deferred frames (confirmed in code).** The device sends
   `0xC5`, `0xDD`, `0xE5`, `0xEB` and `0xDB` on its own when the matching
   state changes, and answers some requests later: `0x19` after the bind
   prompt, `0xC9`/`0xE3`/`0xE9`/`0xEF` after the remote-control prompt over
   Bluetooth (no immediate reply at all while it is pending), `0xD9` chunks
   after `0xD8`, and `0xDB 00` after the last `0xDA` chunk. A client must
   match replies by opcode, not by order.
8. **One request in flight (confirmed in code).** The CH58x holds one frame
   per direction and the main MCU one outstanding reply. A second request
   before the previous reply can overwrite it, and over USB a frame that
   shares a report with another can be forwarded corrupted with a valid
   checksum. Write with response, wait for the reply, then send the next.
9. **Request lengths are not checked (confirmed in code).** Handlers read
   their fixed offsets; a short request is completed with stale bytes from
   an earlier request. Always send complete payloads.
