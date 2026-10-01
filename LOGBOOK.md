# LOGBOOK

Chronological record of what happened: work done, decisions and who made
them, findings, gate approvals and verification runs. Planned work goes in
TODO.md, not here. New entries go at the bottom under a dated heading; a
second entry on the same day gets a new `###` heading under the existing date
heading. Old entries are never rewritten. Corrections are added as new entries
that point back to the original.

## 2026-09-29

### Research: how the MP305B can be controlled

- The MP305B has Bluetooth LE and a USB-C port that carries data. ISDT's
  official options are the Polying app (macOS, Windows, Linux, iOS, Android)
  and the WebLink browser page, https://www.isdt.co/weblink/.
- ISDT publishes no protocol, SCPI command set or API. The manual PDF has no
  text layer, so none of its content could be searched.
- WebLink's JavaScript (downloaded for analysis, not stored in the repo)
  shows:
  - USB: WebHID, `navigator.hid.requestDevice` with filters
    `{usagePage: 1, usage: 4}` and `{vendorId: 10473}` (0x28E9, the
    GigaDevice vendor ID, which suggests a GD32 microcontroller). Reports are
    sent with report ID 1, with a 5 ms delay between chunks.
  - Bluetooth LE: `navigator.bluetooth.requestDevice` with services 44800
    (0xAF00) and 65248 (0xFEE0). Characteristics are looked up under
    `0000af00-...` and `0000fee0-...`, starting at `0000af01-...`.
  - The MP305 page lists limits: program mode up to 30.5 V, 5.1 A;
    USB mode up to 28 V, 5 A, 140 W.
  - Asset files read: `index-NNOthY3Q.js`, `mp305Component-DXYvqvMA.js`,
    `headComponent-DKj48EA9.js`, `otaResp-CS2cFNEZ.js`.
- WKWebView (macOS) and WebKitGTK (Linux) do not implement Web Bluetooth or
  WebHID, which ruled out doing device I/O in a webview frontend.

### Decisions (see docs/adr/)

- There is both a Python library for scripting and a standalone app.
- Transports: both Bluetooth LE and USB HID, Bluetooth first (ADR-0004).
- App language: Rust, not Go, because both need native code for Bluetooth and
  HID and only Rust shares code cheaply with Python (ADR-0003).
- GUI: egui, after comparing Tauri, egui, Slint, Iced and Dioxus. No terminal
  UI is needed (ADR-0005).
- Python library: PyO3 bindings on the Rust core (ADR-0006).
- Proposed, not yet approved: synchronous Python API (ADR-0007).
- v1 scope: core control, live chart and CSV logging. Ramp helpers in Python
  are welcome but optional. Device program mode, USB PD, charger mode and
  protection settings wait until later.

### Draft architecture (discussed, not yet a gate)

A Cargo workspace with `mp305-core` (protocol without I/O, transport trait
with Bluetooth LE and HID implementations, async device API), `mp305-app`
(eframe/egui, device I/O on a background Tokio task, channels to the UI) and
`mp305-py` (PyO3, synchronous API, pure Python helpers for ramps and CSV).
This draft was not yet confirmed when the process changed to the V-model.
It becomes the starting point for the level 3 architecture document.

### Process

- The project follows the V-model, with design records and extensive
  documentation and unit tests. Repository initialized (branch `main`, no
  commits yet). Added AGENTS.md, README.md, TODO.md, LOGBOOK.md, the process
  document docs/v-model/README.md and ADRs 0001 to 0007.
- A background agent is extracting the frame format and command set from the
  WebLink JavaScript. Its results go into docs/research/.

### Protocol extraction, first pass

The background agent finished reading WebLink's JavaScript. Its summary (not
yet verified, kept outside the repo until the verification pass ends):

- HID and Bluetooth carry the same opcodes and payloads with different
  framing. HID frames look like `[cnt] AA 12 plen cmd payload cksum`, with an
  8-bit additive checksum and doubling of `0xAA` bytes. Bluetooth frames are
  just `12 cmd payload` on characteristic AF01.
- Each response opcode is the request opcode plus one. Live DC data is
  `C2`/`C3`. Voltage, current limit, output and mode are all set with one
  full-state command, `C8`, which first has to request remote control.
- Bluetooth needs a bind frame on AF02 before use. Firmware version is only
  readable over USB.
- Hardware questions to settle later include the HID product ID and report
  size, the reply address byte, status code meanings, the energy field's
  unit, the Bluetooth MTU, and whether a keep-alive is needed.

Because the design will depend on these details, a verification workflow
re-derives each area independently from the bundles and runs ISDT's own
frame builders in Node for byte-exact checks.

### Hardware: first Bluetooth LE observation

The user's MP305B arrived. A read-only scan from the MacBook Pro (bleak,
passive discovery, no connection, nothing sent) found it advertising:

| Field | Value |
|---|---|
| Local name | `'0000MP305B  S             E!K'` (the `0000MP30` prefix matches the WebLink filter; the rest of the name is padded with spaces) |
| Service UUIDs | `0000af00-0000-1000-8000-00805f9b34fb` |
| Manufacturer data | company ID `0xABBA`, bytes `affa013502000000000000000000000000000000` |
| RSSI | -32 dBm at close range |

Notes:
- The first scan, a few seconds earlier, did not see the device. It was
  probably switched on or started advertising in between. Not investigated.
- `0xABBA` does not look like an assigned Bluetooth SIG company ID. What the
  manufacturer bytes encode is unknown.
- No pairing in macOS System Settings is needed or possible for this kind of
  device. Apps connect to it directly.
- Spike scripts live in the session scratchpad, not in the repo.

### Hardware: the device's "Web Link" screen

The user sent a photo of the MP305B display. It has a "Web Link" screen with a
QR code and the text "Scan to access the remote control panel". The QR code
decodes to `https://www.isdt.co/weblink`, a plain URL with no device ID,
token or query parameters.

Hypothesis (inferred, not tested): the device advertises over Bluetooth LE
only while this screen is open. This would explain why the first scan missed
it and the second found it. Test: close the screen, scan, reopen it, scan
again. If true, the app and the Python library must tell the user to open
Web Link on the device when no supply is found.

### Hardware: advertising test (corrects the hypothesis above)

Read-only 15 s scans with bleak on the MacBook Pro (detection callback, no
connection):

| Time | Web Link screen | Chrome WebLink tab | MP305B seen |
|---|---|---|---|
| 19:32:20 | closed | probably still connected (the user had the Chrome device chooser open at 19:31:30) | no (17 other advertisers seen) |
| 19:32:47 | closed | closed | yes, 7 advertisements, -39 dBm, first at 0.2 s |

Result: the hypothesis is refuted. The device advertises while the Web Link
screen is closed, so the screen does not control advertising. The miss at
19:32:20 is most likely explained by the open Chrome connection, since a
Bluetooth LE peripheral normally stops advertising while a central is
connected. That explanation is inferred, not tested. The first miss earlier
in the day is still unexplained.

Consequences for the design:
- Discovery does not depend on the user opening a screen on the device.
- The "supply not found" message should mention that another app (Chrome,
  Polying) may already be connected, since that blocks discovery.
- Advertisements arrive sparsely (gaps of several seconds seen), so
  discovery needs a scan window of at least 10 s or a retry.

### Hardware: read-only Bluetooth LE spike

A read-only spike was approved. Script: `spikes/ble_readonly/spike.py`
(bleak, macOS). It can only send allowlisted frames: the bind frame and the
read requests `E0`, `C4`, `C2`. Nothing was connected to the output. Capture:
`docs/research/captures/2026-09-29T193614-ble-readonly.jsonl` (50 lines).

GATT table (confirmed on hardware):

| Service | Characteristic | Properties |
|---|---|---|
| `180A` Device Information | `2A23` to `2A2A`, `2A50` | read |
| `AF00` | `AF01` (handle 34) | notify, write, read |
| `AF00` | `AF02` (handle 37) | notify, write, read |
| `DB00` (unknown, not used by WebLink) | `DB01` (handle 41) | notify, write, read |

- No `FEE0` service while running normally. WebLink only uses it for firmware
  updates, so it probably appears only in the bootloader. Inferred.
- MTU 247 (maximum write without response 244 bytes), well above the roughly
  126 bytes the largest frames need.
- AF01 and AF02 both support write with response. The spike used it.

Exchange (times in seconds since the scan started):

| t | Dir | Char | Bytes |
|---|---|---|---|
| 4.256 | TX | AF02 | `18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00` (bind) |
| 11.985 | RX | AF02 | `19 00` (bound, after 7.7 s) |
| 12.486 | TX | AF02 | `E0` |
| 12.616 | RX | AF02 | `E1 01 06 00 28 4D 50 33 30 35 42 00 00 02 00 02 00` |
| 12.617 | TX | AF01 | `12 C4` |
| 12.750 | RX | AF01 | `31 C5 5A 02 00 00 01 F4 01 32 00 00 00` |
| 12.750 | TX | AF01 | `12 C2` |
| 12.886 | RX | AF01 | `31 C3 00 00 5A 00 00 14 05 00 00 E8 03 01 00 00 00 00 00 00 00 00 00 00 03 00 00 00 00 01 1A 00 00 01 40 06 00 00` |
| 17.309 | TX | AF01 | `12 E0` (probe, not used by WebLink over BLE) |
| 17.429 | RX | AF01 | `31 E1 01 06 00 28 4D 50 33 30 35 42 00 00 02 00 02 00` |

All 20 `C2` polls were answered with identical 38-byte `C3` frames. Round
trip from write to notification was about 120 to 135 ms. With WebLink's
100 ms pause after each reply, one poll cycle took about 225 ms (about
4.4 samples per second).

What this settles:
- The device answers on AF01 with address byte `0x31`. On AF02, module replies
  have no address byte (the command is at index 0), as the findings said.
- The bind frame from WebLink works, answered with `19 00`. It took 7.7 s.
  Whether the device showed anything on screen during that time is not yet
  known (asked the user).
- The module `E1` layout matches the findings: BLE hardware 1.6, BLE software
  0.40, 8 byte "device ID" field, hardware version 2.0.2.0. The "device ID"
  holds the model name `MP305B` padded with zeros, not a serial number.
- `E0` sent over AF01 returns the same 16 bytes as the module `E1` (with
  address byte `0x31`). The main MCU firmware version is therefore not
  readable over Bluetooth this way.
- `C5` is 13 bytes and includes the optional `usbLine` field. Decoded: charge
  limit 90 %, volume 2, screen off setting 0, auto off 0, screen direction 1,
  ramp step 500 mV per 0.1 s, OCP delay 50 ms, USB line compensation 0.
- `C3` is 38 bytes, which is the full layout including the optional error and
  chart fields (HID equivalent 41, as the findings predicted). Decoded with
  the findings' offsets: CV/CC state 0, battery 90 %, output 0.00 V, set
  13.00 V, output 0.000 A, limit 1.000 A, time 1 s, energy 0, power 0.00 W,
  current mode 0 (CC), live apply bits 3, output off, mode 0 (DC), board
  flags 0 and 1, temperature 26 °C, error bits 0, chart pause 1, chart
  interval 1600 ms.
- The decoded values are plausible (for example battery 90 % with a 90 %
  charge limit, and 26 °C). The set voltage, current limit and battery level
  still need to be confirmed against the device screen (asked the user).
- A CV/CC state of 0 while the output is off is a value the findings did not
  list.

Open after this spike:
- Whether AF01 commands work without binding (not tested, the bind succeeded).
- Meaning of the 7.7 s bind delay.
- What service `DB00` is for.

### Hardware: Device Information service

`spikes/ble_readonly/dis_read.py` read the standard Device Information
service with plain GATT reads (nothing written). Every text field holds a
placeholder string from the Bluetooth chip vendor's SDK ("Model Number",
"Serial Number", "Firmware Revision", "Hardware Revision", "Software
Revision", "Manufacturer Name"). System ID is all zeros. Regulatory data is
`FE 00` plus "experimental". PnP ID is `01 D7 07 00 00 10 01` (vendor ID
source 1, vendor 0x07D7, product 0x0000, version 0x0110). DB01 reads back
empty. AF01 and AF02 read back 20 zero bytes.

Consequence: the design must not use the Device Information service for
identity or firmware version. Over Bluetooth, identity comes from the
advertised name and the module `E1` reply.

### Hardware: screen confirmations

- The device screen showed set voltage 13.00 V and current limit 1.000 A,
  matching the decoded `C3` fields `setVoltage` (u16, 10 mV) and `setCurrent`
  (u16, mA). The answer was yes to the question that also named "output
  off" and "battery 90 %". These fields and units are now confirmed on
  hardware.
- Binding asks for confirmation on the device screen with the choices allow
  and deny. The 7.7 s delay before `19 00` was the time until the user pressed
  allow. `19 00` therefore means "allowed".

Consequences for the design:
- Connecting from a new host needs a person at the device. The app and the
  Python library must say "confirm the connection on the supply" while
  waiting, and need a bind timeout long enough for a person (WebLink's own
  timeout is still unknown).
- The deny reply and whether the device remembers an allowed host are
  unknown. Both need a test.
- The prompt is a security feature: nobody in radio range can take control
  without someone at the bench allowing it. Our software must not try to work
  around it.

### Hardware: remembered-host test

19:42:05, same spike, same fixed bind frame (WebLink's constant host ID
`00 08 08 ... 08 00`, fastBinding 0, status 0). The allow/deny prompt
appeared again and the user pressed allow. `19 00` arrived 3.0 s after the
bind frame. All other replies were byte for byte identical to the first run.

Result: with WebLink's bind frame, the device asks on every connection. It
does not remember an allowed host.

Still open, and needs the user's approval because it sends a bind frame that
WebLink never sends: whether `fastBinding = 1` or a host specific 16 byte ID
lets the device remember a host. Until then, the requirements must assume a
person confirms every connection. That rules out unattended reconnects over
Bluetooth (for example after a dropout during a long logging run) and makes
USB HID the transport for unattended use, provided HID has no prompt.

### Hardware: deny test

19:43:08, same spike. The user was asked to press deny on the prompt and
confirmed with "ok". Capture:
`docs/research/captures/2026-09-29T194319-ble-readonly.jsonl`.

| t | Dir | Char | Bytes |
|---|---|---|---|
| 4.017 | TX | AF02 | bind frame (unchanged) |
| 6.361 | RX | AF02 | `19 FF` |
| 6.362 | TX | AF01 | `12 C4` |
| 6.496 | RX | AF01 | `31 C5 ...` (same 13 bytes as before) |
| 6.497 to 11.05 | TX/RX | AF01 | 20 of 20 `C2` polls answered with the same 38-byte `C3` |
| 11.051 | TX | AF01 | `12 E0` |
| 11.175 | RX | AF01 | `31 E1 ...` (same 18 bytes as before) |

Results (confirmed on hardware):
- Deny is answered with `19 FF`. Together with the earlier runs:
  `19 00` = allowed, `19 FF` = denied.
- Binding does not protect reading. After a deny, the device still answered
  settings, live data and info requests on AF01. Anyone in Bluetooth range can
  read the supply's state without the owner's approval.

Not tested, and not to be tested without the user's explicit approval:
whether control commands (`C8`) are also accepted without a successful bind.
If they are, anyone in range could switch the output. That would be a
security problem in the device, which the user may want to report to ISDT.

Design consequences:
- Our software must treat a bind reply other than `19 00` as a failed
  connection and refuse all control commands, even though reads would work.
  Whether to offer a read-only monitoring mode after a deny is a requirements
  question for the user.
- The bind result has to be part of the connection state that the app and the
  Python API expose.

### Documentation review

An independent review pass checked AGENTS.md, README.md, TODO.md, LOGBOOK.md,
docs/v-model/README.md, docs/research/README.md and the ADRs for consistency,
process gaps, technical errors and style. Its verified findings were applied
in place, since nothing is committed yet. Where fixes conflicted, the agent
chose one version. The changes include a proposed ADR-0008 (documentation,
coverage and HIL safety standards). The user has not reviewed or approved any
of these changes; the approval items are in TODO.md.

### Corrections to earlier entries

The entries above stay as written. These corrections apply to them.

- "Research: how the MP305B can be controlled", Polying platforms: ISDT
  lists the Polying app for iOS, iPadOS, macOS (Apple Silicon) and Android
  only. Windows and Linux are covered by WebLink in a Chromium-based browser.
- "Research: how the MP305B can be controlled", Bluetooth LE bullet: service
  `0xAF00` has characteristics `0xAF01` (commands and replies) and `0xAF02`
  (bind handshake and BLE module info). WebLink also requests
  `0xFEE0`/`0xFEE1`, but only for bootloader firmware updates, and that
  service is absent in normal operation. See the GATT table under "Hardware:
  read-only Bluetooth LE spike".
- "Research: how the MP305B can be controlled", limits: the limit table is in
  `headComponent-DKj48EA9.js`. WebLink caps setpoints at 30.5 V and 5.1 A in
  program mode, and apparently also in the DC setpoint keypad
  (`mp305Component-DXYvqvMA.js`). The 28 V, 5 A, 140 W limits belong to the
  USB-C PD source profile editor, not to the USB HID link. WebLink's device
  mode values are 0 DC, 1 program, 2 USB-C PD source and 3 charger.
- "Decisions (see docs/adr/)", v1 scope: the chosen option puts the
  live chart and CSV recording in the app. The Python library gets
  measurement streaming and a CSV logging helper, and no chart.
- "Draft architecture (discussed, not yet a gate)": the draft was not
  confirmed. The process moved to the V-model before that question was
  answered. Nothing
  in the draft is approved. It is only input for
  docs/v-model/3-architecture.md, and the task and channel design is decided
  at gate G3.
- "Protocol extraction, first pass", where the report is: the first-pass
  report is still in the agent session's temporary scratchpad, not in the
  repo, and a later session cannot find it there. It will be written to
  docs/research/protocol.md after the cross-check finishes. The "verification
  pass" and "verification workflow" in that entry are the cross-check, which
  re-derives each item independently from the WebLink JavaScript. Evidence
  labels are "confirmed in code", "confirmed on hardware" (observed on the
  user's unit) and "inferred".
- "Protocol extraction, first pass", summary wording. Clearer version, still
  a first-pass result that the cross-check has not yet covered:
  - HID frames have the layout `cnt 0xAA 0x12 plen opcode payload cksum`.
    `cnt` is the number of bytes that follow in the report (counted after
    doubling), `0xAA` is the start byte, `0x12` is the host-to-device
    address, `plen` is the length of opcode plus payload (before doubling),
    and `cksum` is the 8-bit sum of the bytes from the address through the
    last payload byte. A `0xAA` from the second payload byte on is sent
    twice, and so is a checksum equal to `0xAA`.
  - Bluetooth frames are `0x12 opcode payload`, written to characteristic
    `0xAF01`, with no length, checksum or doubling.
  - Live DC readings use opcode `0xC2` (request) and `0xC3` (response).
    Voltage, current limit, output on/off and mode are all set together by
    one full-state command, `0xC8`. The host first sends `0xC8` with
    `remoteCon = 2` to request remote control, then sends each change as a
    complete `0xC8` with `remoteCon = 1`.
  - After each Bluetooth connection, the host writes a bind frame to
    characteristic `0xAF02` and waits for the reply before it sends
    commands.
- "Protocol extraction, first pass", firmware version: hardware has since
  confirmed that the main firmware version cannot be read over Bluetooth.
  `0xE0` over `0xAF01` and `0xAF02` returns only the BLE module info, and the
  Device Information service holds SDK placeholders (see "Hardware: read-only
  Bluetooth LE spike" and "Hardware: Device Information service"). Reading it
  over USB HID (`0xE0`, reply `0xE1`) is confirmed in code, not yet on
  hardware.
- "Hardware: remembered-host test": its capture is
  `docs/research/captures/2026-09-29T194219-ble-readonly.jsonl`.
- Captures of 2026-09-29: none of the three captures (19:36, 19:42, 19:43)
  records the main firmware version: firmware version not yet recorded. When
  it is read (over USB HID or from the device menu), it gets its own LOGBOOK
  entry, which applies to these captures unless the firmware was updated in
  between.
- A `### Next` section with planned work ("Write the user requirements and
  acceptance test specification (gate G1).") stood at the end of this file.
  It was removed, since nothing is committed yet and planned work belongs in
  TODO.md, which already lists that task.

### Corrections, second round

These correct entries above, including two items of "Corrections to earlier
entries". Both errors came from the agent: it gave the documentation editors
two wrong statements as fixed decisions.

- "Corrections to earlier entries", draft architecture bullet: wrong. The
  session transcript records "yes, looks right" for the draft
  architecture (design section 1) on 2026-09-29, before the move to the
  V-model. That is a chat agreement, not a gate approval. The draft is the
  agreed input for docs/v-model/3-architecture.md, and gate G3 still needs
  the user's formal approval of the architecture and integration test
  documents.
- "Corrections to earlier entries", firmware version bullet, and the
  firmware statements in "Hardware: read-only Bluetooth LE spike" and
  "Hardware: Device Information service": wrong. The device reports its
  versions over Bluetooth. In the recorded `0xE1` replies, bytes 1 to 4 after
  the opcode (`01 06 00 28`) are WebLink's "System Version" 1.6.0.40, and
  bytes 13 to 16 (`02 00 02 00`) are WebLink's "Firmware Version" 2.0.2.0.
  The spike's labels ("BLE hw 1.6, sw 0.40", "hardware version") were
  guesses. Evidence: the WebLink screenshot below, and ISDT's update manifest,
  which lists 1.6.0.51 as the MP305B main firmware and is compared against
  the System Version. All three captures (19:36, 19:42, 19:43) were taken on
  System V1.6.0.40, Firmware V2.0.2.0. Which chip each version belongs to is
  inferred.
- "Documentation review": the fixes followed a decision list the agent
  wrote, not only the reviewers' fixes. That list overrode several verified
  findings (capture location, test tagging scheme, the reviewers' wording on
  the draft architecture, and one "ask the user" step), and two of its
  entries were wrong (see the two bullets above). The decision and
  consequence text of the accepted ADR-0002, ADR-0003 and ADR-0005 changed
  in that pass, so these ADRs need the user's review (TODO).

### Hardware: WebLink screenshot and firmware update

Around 19:50 the user connected with WebLink in Chrome over Bluetooth and
sent a screenshot of the MP305B page: Equipment Model MP305B, Battery
Temperature 26 °C, Firmware Version V2.0.2.0, System Version V1.6.0.40,
V-SET 13.00 V, I-SET 1.000 A, output off, CC selected (not OCP). This
confirms on hardware the `0xC3` fields temperature and `currentOver = 0`
(CC). WebLink offered an update "V1.6.0.40->1.6.0.51, 1.Optimize known
issues. 2026/09/14", and the user started it over Bluetooth. The result was
not yet known when this entry was written.

### Research: firmware manifests, firmware file and WebLink source maps

- WebLink reads the public update manifests `/ota/newfirmware.json` and
  `/ota/newble.json` on www.isdt.co. The main manifest lists MP305B 1.6.0.51
  with a public `.fwd` firmware file. The Bluetooth manifest has no MP305
  entry.
- The `.fwd` file is obfuscated. WebLink itself restores the plain image in
  the browser before sending it to the device. Running WebLink's own routine
  gave an image that passes WebLink's checksum and identity checks (hardware
  version 2.0). It holds two parts: the main application and a second image
  that appears to be the Bluetooth chip's firmware (it contains the string
  "CH58x_BLE_LIB_V1.8"). That pass inspected printable strings.
- WebLink's source maps are public and contain the original source (54
  files, about 16,000 lines, with ISDT's own file names and comments).
- The firmware file, the plain image and the extracted sources from that
  pass were in the agent's temporary session storage.

### Documentation request

The user reported asking ISDT for documentation without getting a response
(date and channel not yet recorded).

### Research: protocol cross-check finished

The independent cross-check of the first-pass protocol report finished.
Seven areas, each re-derived from the WebLink code, with ISDT's own frame
builders run verbatim for byte-exact checks: 107 claims confirmed, 18
partly right, 1 not decidable from the code, none refuted. The corrections
and a list of safety gaps (for example full-state `0xC8` commands that can
undo a front-panel output change, and no release of remote control on
disconnect) go into docs/research/protocol.md and the hazard list for G1.

### Hardware: read-only spike after the firmware update

20:14:14, after the user reported the firmware update (offered as 1.6.0.40
to 1.6.0.51) as finished. Same unchanged `spike.py`; the user pressed allow.
Capture: `docs/research/captures/2026-09-29T201428-ble-readonly.jsonl`.
Compared with the 19:36 capture using `spikes/ble_readonly/compare.py`:

- `0x19` bind reply, both `0xE1` replies, and `0xC5`: byte for byte
  identical.
- `0xC3`: same 38-byte length and layout. Only live values differ: operating
  time 1 s to 3 s, temperature 26 °C to 27 °C, chart timer 1600 ms to
  3700 ms.

Open: `0xE1` bytes 1 to 4 still read `01 06 00 28` (1.6.0.40), not 1.6.0.51
(`01 06 00 33`). Either the update has not taken effect, or WebLink's
"System Version" does not come from these bytes. Asked the user what WebLink
shows now.

### Research: WebLink deep dive, version fields resolved

A second workflow read the WebLink code beyond the protocol claims (firmware
update and network use, UI strings, connection lifecycle, inputs and chart,
all opcodes). Its merged notes are in the agent's temporary session storage
and go into docs/research/protocol.md. Results that matter now:

- Running WebLink's own `0xE1` parser on our captured frame: bytes 1 to 4
  (`01 06 00 28`) are the main application version, shown as "System
  Version" and compared with the MP305B entry of the update manifest
  (confirmed in code). The 1.6.0.51 firmware image carries the same fields
  in its application info block, with the application version `01 06 00 33`
  (1.6.0.51) and the hardware version `02 00 02 00`.
- WebLink's English label "Firmware Version" is a mistranslation. The
  Chinese UI calls the field 硬件版本 (hardware version). V2.0.2.0 is the
  hardware revision. This corrects the "Firmware Version" wording in
  "Corrections, second round" and in the entries after it.
- Conclusion (confirmed in code, compared against the capture): at 20:14
  the unit still ran application version 1.6.0.40. The update reported as
  finished had not taken effect. The cause is unknown.
- WebLink sends no device data to ISDT and uses no browser storage. Its only
  requests are the update manifest (with a timestamp against caching), the
  firmware file after the user confirms, the manual PDF and static assets,
  plus an unused location check.
- WebLink's firmware update flow erases the application about 4 s after
  entering the bootloader and has no timeouts and no abort. An interrupted
  update can leave the unit in the bootloader.
- `voltageSlow` in `0xC8`/`0xC3` selects ramp output (1, the voltage slews
  at the "Ramp Step" rate from the settings) or step output (0). It is not a
  knob speed.
- Settings writes (`0xC6`, which also carries the self-test and factory
  reset flags) and preset writes are gated in WebLink only by "output off",
  not by remote control.
- Switching WebLink's language also switches the device's display language
  (`0xA2`).

### Research: USB HID descriptors, error bitmasks and protocol.md

- USB HID descriptor tables identified in `fw/data.bin`:
  - Device descriptor at `0x12f9c`: VID `0x28E9` (10473, GigaDevice), PID
    `0x028A` (650), USB 2.0 full-speed, EP0 max packet size 64 bytes.
  - Endpoints at `0x12f70`: EP1 OUT (`0x01`) and EP1 IN (`0x81`), interrupt
    transfer, 64-byte max packet size, 1 ms polling interval.
  - HID report descriptor at `0x12f4c` (35 bytes): asymmetric report IDs on the
    wire. Host-to-device (OUT) reports require Report ID 1 (63 data bytes).
    Device-to-host (IN) reports arrive under Report ID 2 (63 data bytes).
    Drivers using hidapi must handle Report ID 2 on input reads.
- Complete 17-bit `chargeError` hardware protection bitmask documented in
  detail, mapping bits 0 to 8 for DC power supply mode (reverse polarity,
  overheat, OVP, OCP, circuit fault) and bits 9 to 15 for battery charger mode.
- Authored the comprehensive protocol reference in `docs/research/protocol.md`,
  marking all facts as confirmed in code, confirmed on hardware, or inferred.


### Hardware: WebLink after the reported update

The user sent a WebLink screenshot taken at 19:57:45 over Bluetooth, after
the update was reported as finished. It shows System Version V1.6.0.40,
Firmware Version (hardware revision) V2.0.2.0, Equipment Model MP305B,
Battery Temperature 27 °C, V-SET 13.00 V, I-SET 1.000 A, time 000:00:01,
energy 0 Wh, power 0.00 W, output off, CC selected. No update dialog is
shown.

- ISDT's own software confirms that the unit still runs 1.6.0.40, matching
  our `0xE1` reading at 20:14. The update did not take effect.
- WebLink's displayed versions match our decoding of `0xE1` bytes 1 to 4
  and 13 to 16. This confirms the field mapping on hardware.
- The live values match our `0xC3` decoding (time, energy, power,
  temperature, setpoints, CC mode).

### Level 1: user requirements, acceptance tests and traceability

- Authored `docs/v-model/1-user-requirements.md`:
  - 8 safety hazards defined (`H-001` to `H-008`) covering unexpected output
    enable, unit misdirection, stale setpoints, connection drops, scaling
    errors, authorization denial, DUT limits, and active fault conditions.
  - 22 user requirements defined (`UR-001` to `UR-022`) across core control,
    desktop application (`mp305-app`), Python library (`mp305`), and design
    constraints (Rust core, egui, PyO3).
- Authored `docs/v-model/8-acceptance-tests.md`:
  - Coverage matrix defined across macOS, Linux, and Windows for both BLE and
    USB HID transports.
  - 22 acceptance test specifications defined (`AT-001` to `AT-022`) verifying
    every UR, including automated Python test paths, manual procedures, and
    inspection checks.
- Authored `docs/v-model/traceability.md`:
  - Hand-maintained traceability matrix connecting all hazards (`H-nnn`) to
    mitigating user requirements (`UR-nnn`) and validating acceptance tests
    (`AT-nnn`).
- Level 1 documentation is complete and ready for Gate G1 user review.


### Level 1 revision and level 2 drafts

Work continued with the Python library and the desktop app, taking the
latest protocol findings into account. The two conflicts with the records
stay as written: Rust and egui, as in ADR-0003 and ADR-0005 ("go app" meant
the app), and the V-model documents rather than code or a prototype. The
system requirements are drafted before G1.

Found in the level 1 drafts of the previous entry and fixed in revision 2:
- The hazard mitigation column named unrelated URs (for example H-001 named
  UR-013, the chart, and H-003 named UR-014, CSV recording).
- AT-001 expected a serial number, but the supply reports none over
  Bluetooth. AT-006 used a 200 ms limit that no UR states. AT-009 had no
  safe way to cause a fault. The coverage table listed mock runs in CI as
  acceptance tests.
- The Python streaming and CSV helper and the ramp helper from the agreed v1
  scope had no UR. There was no TBD list, which G1 requires.

Changes:
- `docs/research/protocol.md`: new section 1.3 on the bind handshake
  (prompt at every connection, `19 00` and `19 FF`, reads after a deny);
  the GATT table; hardware evidence for `0xC3`; `voltageSlow` is ramp or
  step output, not knob speed; `0xE1` bytes 5 to 12 are the model name and
  WebLink's "Firmware Version" is the hardware revision; USB VID, PID and
  report IDs relabeled from "confirmed on hardware" to firmware descriptor
  tables (inferred), since no USB connection has been made; section 5
  relabeled, since the device's behavior on disconnect and the `0xC9` reply
  time were stated as facts but never observed.
- `1-user-requirements.md` revision 2: H-009 (firmware update), UR-023 to
  UR-029, testable wording for several URs, TBD-001 to TBD-009. UR-006's 1 s
  limit is the agent's proposal for the user to confirm.
- `8-acceptance-tests.md` revision 2: test conditions, AT-023 to AT-029, a
  fault test using OCP mode and a 22 Ω resistor, a hardware coverage table.
- New drafts `2-system-requirements.md` (SR-001 to SR-045, TBD-010 to
  TBD-014) and `7-system-tests.md` (ST-001 to ST-040). Every UR is refined
  by at least one SR and every SR has an ST entry.
- `traceability.md` revision 2, including the draft SR to ST mapping.

### Settled questions and independent review

Four open questions were settled on 2026-09-29:
- TBD-001: after a deny, the software refuses and disconnects. There is no
  read-only mode.
- Output-off must be acknowledged within 0.5 s (UR-006), and a missing
  `0xC9` counts as a timeout after 1 s (SR-023). The agent had proposed
  1 s and 2 s.
- The residual risks of H-004 (output stays on after a crash or link loss)
  and H-006 (the supply might accept control without a bind) are not
  accepted. Further mitigations are required (TBD-015).
- TBD-009: hardware tests run only on the Mac. Linux and Windows are covered
  by CI and mock tests only, a gap to accept or reject at G1.

Protocol internals are settled from WebLink, the hardware or the firmware
image, without a further question.

An independent review agent checked the level 1 revision and the level 2
drafts against protocol.md, the LOGBOOK and the process document. It found
4 blockers for G1, 13 items to fix and 12 minor ones. All were applied:
- H-008 was only partly mitigated: UR-009 now also refuses output on during
  a fault.
- AT-009 assumed an OCP-mode trip sets `chargeError` bit 5, which nobody has
  observed. `currentOver` in `0xC3` is the OCP mode setting, not a trip
  flag. New TBD-016; protocol.md relabeled.
- AT-012 would have sent setpoints near 30 V without saying why. It now
  checks the range edge with the output off and nothing connected.
- UR-006 conflicted with the SRs that block control after a deny, after a
  lost remote control, or in non-DC modes. It now applies to allowed DC
  connections, and tells the user to use the front panel otherwise.
- Other fixes: evidence labels (H-002, SR-044, SR-045), TBD-012 cited
  wherever an SR relies on `0xC8`, SR-029 and SR-030 settled for closing,
  HIL limits kept in ST-022, ST-030 and ST-038, ST-034 consistent with
  SR-034, hazard rows list the mitigating SRs, UR parents, empty
  rationales, and the third allow run (3.6 s, capture `201428`).

Documents now at: 1-user-requirements.md revision 4, 8-acceptance-tests.md
revision 4, 2-system-requirements.md revision 3, 7-system-tests.md revision
3, traceability.md revision 3.

Correction to "Research: USB HID descriptors, error bitmasks and protocol.md":
"17-bit `chargeError`" is wrong. The field is 16 bits (protocol.md 4.5).

### TBD-015 mitigations specified and two spikes prepared

Applied the mitigations chosen on 2026-09-29 for the residual risks
of H-004 and H-006, and prepared the two spikes.

Requirements (all drafts, not yet approved):
- UR-030 (unclean-exit warning) and UR-031 (bench-safety note for unattended
  runs) added, with SR-046, SR-047, AT-030, AT-031, ST-041, ST-042 and the
  traceability rows. The H-004 and H-006 mitigation columns and TBD-015 were
  updated. TBD-015 is now the residual risk itself, to be accepted or
  rejected at G1 after the spikes run.

Spikes prepared, not run (the agent did not set MP305_HIL and executed
nothing):
- spikes/link_drop/ (TBD-005): switches the output on at 5.00 V, 0.100 A with
  nothing connected, drops the link the way a crash would, reconnects
  read-only to see whether the output stayed on and whether remote control
  survived, then switches the output off. Also the first hardware exercise of
  0xC8 and 0xC9 (TBD-012).
- spikes/control_after_deny/ (TBD-002): after the user presses deny, sends one
  0xC8 remoteCon=2 built from a fresh reading with the output field forced to
  0, and reads 0xC9 to see whether the device grants remote control to a
  denied host. It never enables the output and changes no setpoint.

Both spikes refuse to run unless MP305_HIL=1 and MP305_HIL_DEVICE name the
unit and the user types a confirmation, connect only to the named unit, and
switch the output off in a finally block. A guard on every 0xC8 enforces the
bench limit (5 V, 150 mA) whenever a command would energize the output, caps
setpoints at the device maximum otherwise (so the output-off teardown works
with the unit's real 13 V setpoint), forces DC mode, and, for the deny spike,
forces the output field to 0. The guard and frame builders were unit-tested
off-device against a 13 V snapshot: the safe commands pass and over-voltage,
over-current, non-DC and output-on commands are rejected.

### Independent audit of the spikes and TBD-015 changes

Ran a review workflow (safety, process, and protocol accuracy) over the
two spikes and the TBD-015 requirement
changes, each high-severity finding verified by a second independent agent.
Nine findings:
two safety findings (a blocker and a high) confirmed, seven medium or minor.
All were applied after the agent, or the author, checked them against the
files.

Safety (spikes/link_drop/spike.py), both confirmed:
- Blocker: the teardown was gated on a read-back confirmation, not on whether
  an energize command had been sent. If the five confirm reads timed out, and
  a timed-out read returns None without raising, the script left the output on
  and returned success, which is exactly the H-004 case the spike exists to
  study. Fixed: the spike now sets `commanded_on` right after the energize
  write and runs the teardown from a `finally` block keyed on that flag,
  independent of any read-back.
- High: the teardown helper sent nothing when its own read returned None, and
  main returned 0 even when the output-off was not confirmed. Fixed: a new
  `ensure_output_off` reconnects and retries up to three times, the off
  sequence restores the original setpoint, and the script now returns a
  non-zero code and prints a front-panel warning when it cannot confirm the
  output is off.

Other findings applied:
- The energize changed the setpoint to 5 V and did not restore it (AGENTS.md).
  The teardown now restores the reading's original setpoint.
- `chargeError` was read with an off-by-one length guard (`> 31`); corrected
  to `> 32` so a 32-byte frame cannot raise.
- The control-after-deny README described a 6 V / 150 mA cap the spike's guard
  does not enforce (its safety rests on the output field being 0). Corrected.
- H-004's mitigation column omitted SR-047; added, to match traceability.md.
- UR-030's verification method (T) now carries a note on why it differs from
  the analogous UR-024 (D).

### Repository wording

A wording pass on 2026-09-29 left the README ending at
Safety. One TODO item was dropped. One consequence left ADR-0002, and one
rejection reason left ADR-0005. In this log, the note after "Research:
firmware manifests, firmware file and WebLink source maps" is now
"Documentation request".

### Boundaries assessment withdrawn

The boundaries assessment is rejected. UR-022 and AT-022 are
withdrawn, and the firmware-image cross-check is off the TODO list. The
heading that stated that assessment is now "Documentation request" and keeps
only the note that ISDT was asked for documentation. Disconnecting
after a deny remains the decision in UR-008 (TBD-001).

### Firmware decompilation

Under Directive 2009/24/EC (2009/24/EG), decompiling the device firmware is
fully allowed in order to ensure full interoperability of the library and
the desktop app with the device. Recorded in AGENTS.md,
README.md, docs/research/README.md, docs/research/protocol.md and ADR-0010.
This corrects "Research: firmware manifests, firmware file and WebLink
source maps": the string inspection and the session-storage note in that
entry describe that pass. They do not limit decompilation.

### Firmware information

In order to ensure full interoperability, there is no limit on the
information contained in the device firmware, and the library and the
desktop app use it to its fullest. ADR-0010, ADR-0002,
AGENTS.md, README.md, docs/research/README.md and docs/research/protocol.md
record this. The USB product ID, endpoint layout and report ID 2 in
protocol.md 1.1 are read from that firmware and used in full. The earlier
label "inferred" on those three items, noted under "Level 1 revision and
level 2 drafts", no longer applies to them.

### Where firmware material is kept

The firmware image stays out of the repository, and interoperability
information reconstructed or gathered from it stays in the repository, in
whatever form it takes. Recorded in AGENTS.md, README.md,
docs/research/README.md, docs/research/protocol.md, ADR-0002 and ADR-0010.
This corrects "Research: firmware manifests, firmware file and WebLink
source maps": the session-storage note there describes where that pass left
its files. It does not keep interoperability information out of the
repository.

### Firmware is the main source of truth

The device firmware is the main source of truth, and all other findings
come on top of it. Recorded in AGENTS.md, README.md,
docs/research/README.md, docs/research/protocol.md, docs/v-model/README.md,
ADR-0002 and ADR-0010. ADR-0002's title is now "The device firmware is the
main source of truth for the protocol", and its file is
`0002-firmware-main-source-of-truth.md`. This corrects the decision sentence
in ADR-0002 that said to take the protocol from WebLink's JavaScript, the
consequence that the project follows whatever WebLink speaks, and the
matching sentences in AGENTS.md, README.md, docs/research/README.md,
docs/research/protocol.md and docs/v-model/README.md. Where the firmware and
another finding differ, the project uses the firmware. The hardware
confirmation rule in ADR-0002 still applies to sources other than the device
firmware.

### Firmware reconstruction, image 1.6.0.51

Restored the published `MP305B-V51.fwd` with WebLink's own loader. The
image files are not in the repository. They are at
`~/.local/share/mp305b/fw/`. The application is a Cortex-M Thumb image,
476160 bytes, version bytes `01 06 00 33` (1.6.0.51) and hardware
`02 00 02 00`. The companion image is 79488 bytes and holds
`CH58x_BLE_LIB_V1.8` plus the USB descriptors: VID `0x28E9`, PID `0x028A`,
HID report ID 1 out and report ID 2 in, endpoint 1 interrupt, 64 bytes,
1 ms. The command dispatcher is at application `0x2F34`. Its `0xC2`, `0xC4`
and `0xC8` handlers were walked. `0xC8` rejects a voltage above 3050 and a
current above 5100, and returns status `0xFF` when the live mode is not 0.
The record is docs/research/firmware.md. The author's unit was still
reporting 1.6.0.40 after the update attempt, so this is the published image,
not a capture of the running unit.

### Firmware reconstruction, handler walk

Decompiled the command handlers in application image 1.6.0.51 and checked
the dispatcher calls, the `0xC6` stores, the bind stores, the `0xD8` scan,
the `0xAA` parser and `0xDBE8` against a Thumb disassembly. Recorded in
docs/research/firmware.md, with the protocol reference brought into line
for the frame parser, `0xC6` and `0xE0`.

`0xE0` (`0xB634`) has two layouts. Type 6 is version `01 06 00 33`, the
name `MP305B`, and hardware `02 00 02 00`, which is the Bluetooth field
order with this image's version. The other layout starts with the model
name, then eight bytes from address `0x7AFD4`, which is outside the file.
`0xC6` accepts `perLimit` 80 to 100, volume 0 to 3, shutdown any byte 0 to
30, and slope, OCP delay and `usbLine` 0 to 1000. It checks
`screenDirection` and does not store it. The first failing check rejects
the rest. `0x18` sets a flag and does not assemble `0x19` in the dispatcher. The
`0x19` reply is built at `0x2690`: status 0 when `S+0x46` is not 0, and
`0xFF` when it is 0.
`0xD8` selects a program id and builds no reply. Program steps reject a
first word above 30500 and a second word above 5100. The frame parser at
`0xFF38` doubles `0xAA`, splits the first body byte into nibbles, and
checksums that byte, the length, and the buffered bytes. Opcode `0x20` is a
block write and replies with `0x20`. It is recorded and not sent (UR-025).
`0xFE` replies `FF AA 55` or `FF 00 00` and is not identified as a
bootloader entry.

The application touches CPACR and the literal `0x40054000` (the flash
controller base in published HC32 algorithms). The exact part is not
identified. The companion image contains a USB-PD stack and
`CH58x_BLE_LIB_V1.8`. Its instruction set is still open. No command was
sent to hardware.

### Firmware reconstruction, scratchpad comparison

Compared the handler walk with the report and decompiles in
`/private/tmp/mp305_firmware_scratchpad`. `app.bin` and `data.bin` there
match the copies at `~/.local/share/mp305b/fw/` (same SHA-256). The report's
function addresses are file offsets plus `0x10000`. That base is the link
address: reset vector `0x00010359` is the stub at file offset `0x358`.
This corrects "linked at address 0" in docs/research/firmware.md, and it
corrects the sentence "eight bytes from address `0x7AFD4`" in "Firmware
reconstruction, handler walk". The `0xE0` handler reads absolute address
`0x1C` and copies eight bytes from that pointer plus `0x0C`. Those bytes
are not in `app.bin`.

The report's `0xC2` struct offsets match the copy at `0x58BC`. Its field
names and units do not match the hardware-confirmed layout in protocol.md.
Its `0xC8` voltage maximum of 30500 is the program-step limit. The handler
accepts a voltage below `0xBEB` (3050 is accepted). Opcode `0x20` stores
reply byte `0x20`. The report's "reply is always the request plus one"
misses that. There is no `FreeRTOS` string. The task names remain
`lvgl_task`, `User_task`, `Time_task` and `Power_task`.

`data.bin` has a 1536-byte gap at `0xAA00`, almost all zero. The tail from
`0xB000` starts with a RISC-V `JAL` and holds `CH58x_BLE_LIB_V1.8`. The
head begins with 8051 `LJMP` opcodes, and that `LJMP` targets the gap.
No command was sent to hardware.

## 2026-09-30

### Project licensing

The project license is the GNU General Public License version 3.0 combined
with the Commons Clause License Condition v1.0 (GPLv3 + Commons Clause).
This permits anyone to run and use the software for personal,
research, and internal business operations (such as powering and testing DUTs
in a lab), while strictly forbidding selling the software, charging for
distribution, or offering paid commercial derivatives. Recorded in ADR-0011,
LICENSE, README.md and AGENTS.md.

### Agent anonymity and ownership

Any AI coding agent contributing to this project must never claim any
copyright, authorship, or ownership over code, documentation, or any other
artifacts produced for this repository, and must never state or disclose its
contribution, model name, agent identity, or assistant brand in code,
docstrings, comments, commit messages, pull requests, documentation, or
issues. Agents must stay absolutely and completely anonymous at all times.
Recorded in AGENTS.md and ADR-0012.


### Firmware scratchpad merge and readable reconstruction

Merged the research from `/tmp/mp305_firmware_scratchpad/` and
`/Users/jihlenburg/mp305b-firmware-scratch/2026-09-29` into repository
research. Kept original reports and binaries externally, copied canonical
per-function C and instruction/reference indexes, and recorded source hashes.
The three ISDT images have 3694 discovered function entries; the separate
WCH reference has 1047. Discovery and decompiler completion do not establish
complete semantic coverage. Added readable C with named state offsets,
reply-field tables, deferred D9 chunks and reference-register packing.

Corrected the earlier headings “Firmware reconstruction, handler walk” and
“Firmware reconstruction, scratchpad comparison”: the PD image loads at
`0x1000`, so its reset jump reaches actual startup at `0xAF88`, not padding.
The BLE image also loads at `0x1000`. Long E0 reads missing boot identity
through the pointer at absolute `0x1C`, plus 12. D8 produces deferred D9
replies; binding has a deferred main reply and a BLE saved-host path.
Clock-control, internal flash and external serial storage are separate.
The full correction ledger is in docs/research/firmware-verification.md.

Added main RTOS task, priority, stack, heap, mutex, queue and event-group
maps. The configured tick is 1 kHz, priorities span 0 through 4, and the
kernel time-slices equal-priority ready tasks. I²C completion events can
be deferred through the timer service queue. Exact kernel version and
runtime resource high-water marks remain unknown.

Mapped three main UARTs, two hardware I²C controllers, a software I²C bus,
storage/display SPI paths, DAC/ADC and timer-driven outputs. Register
layouts support inferred INA226-compatible and SC8815-compatible devices,
with the latter interface on two separate buses. Display and touch
candidates, RGB/tone waveform interpretations and their alternatives are
recorded with evidence. A new inventory preserves 68937 decoded memory
access records across the three images, including unresolved addresses.
No complete schematic or exact bill of materials is claimed.

Added manufacturer specifications and clarified the manual's MP305A/MP305B
rear USB-C distinction. Firmware USB HID code does not itself prove a data
connection on a user-accessible MP305B port.

Offline verification: 2835 portable cases and 16 separate input comparisons
passed; record: docs/research/firmware-verification.md. Rechecked the four
existing capture files without modifying them. No hardware command, commit
or push was performed. No production code or V-model approval was added.

### Why reads remain available after binding denial

Traced the question about reads after a bind denial through the original V51 UI decline callback,
BLE AF01 forwarding, main dispatcher and command handlers. The decline
callback clears binding decision/pending state and produces `19 FF`; it
does not itself revoke the separate remote-control grant. C2, C4 and E0
remain readable. A valid C6 settings write also reaches its handler and
changes synthetic state without a bind or remote grant. C8 remote-active
control returns status 1 when that separate grant is absent. These paths
passed 34 offline cases within the combined suite. The previous V1.6.0.40
deny capture independently confirms the three reads, not the C6 write.

This supports an inferred separation of visibility, binding and control;
it does not establish whether the vendor intended that policy or whether
its UI wording promises more. Recorded the distinction and remaining
permission-audit gaps in docs/research/firmware-permissions.md. The existing
UR-008/TBD-001 decision to disconnect after denial remains unchanged.

### IEC 61508 functional safety and MISRA coding standards

Because incorrect or unintended behavior of the power supply can cause
direct property damage (device-under-test destruction, fire) and indirectly
human injury (shock, burns), all software in this repository is treated as
an electrical safety-related system according to IEC 61508
(systematic fault avoidance, fail-safe defaults, full hazard-to-test
traceability). The codebase must adhere to MISRA-aligned guidelines: for Rust,
Safety-Critical Rust / Ferrocene principles including `#![forbid(unsafe_code)]`,
zero panics (`clippy::unwrap_used`, `clippy::expect_used`, `clippy::panic`),
safe indexing (`clippy::indexing_slicing`), safe arithmetic
(`clippy::arithmetic_side_effects`), and full doc coverage; for Python, strict
static typing (`mypy --strict`), flake8-bugbear and flake8-bandit static
analysis, and defensive runtime validation of all setpoint ranges at API
boundaries. Recorded in ADR-0008, AGENTS.md, docs/v-model/README.md, and
docs/v-model/1-user-requirements.md.

### Direct wording of decisions

Decision notes now state the decision itself. This covers AGENTS.md, the
ADRs, the V-model drafts, TODO.md, the read-only spike note, and the
decision sentences in this log, including the firmware, license, anonymity
and safety entries above. Sentences about the person at the bench, and
about a gate or a hardware run that still needs approval, are unchanged.

### Independent firmware reconstruction, tooling

Started an independent reconstruction of the V51 update from the restored
`app.bin` and `data.bin`, without reusing the earlier exports, to check the
research documents against a second derivation. The workspace is
`~/mp305b-fw-re`, outside the repository. The scripts that build it are in
spikes/firmware_reconstruct/ (README there). No device I/O took place.

First results, not yet merged into docs/research/:

- The main image's `SystemInit` at `0x1DB74` writes `0x10000` to VTOR
  (`0x1DB84` to `0x1DB8C`). This corrects "Startup reads VTOR and does not
  write it" in firmware.md, "Three programs".
- USART1 at `0x4001CC00` and USART3 at `0x4001D400` match HC32F448, F467,
  F472, F4A0, F4A2 and F4A8, not HC32F460. The clock routine at `0x1DAE8`
  reads an F460-style clock controller at `0x40054000` that none of those
  parts has. The exact part stays open.
- The CH58x advertising name is patched at run time. Name character 2 is
  `3` when the byte at `0x200043B7` is `0xA5`, otherwise `0`. An `S`
  marker can be set at index 14, and an 8-byte name stored in CH58x
  DataFlash at `0x6E00` can replace `MP305B`.
- The USB HID top-level collection uses usage page 1, usage 0. protocol.md
  says WebLink filters on usage 4.

The scope of this pass is the host interface. PD controller internals,
power-stage internals and firmware update procedures are outside it.


### Independent workspace recovery and reusable research archive

Completed the recoverable host-interface jobs in `~/mp305b-fw-re` on
separate copies under `recovery-2026-09-30`. The 110 original workspace
files, all four captures and the canonical per-function exports were preserved.
The user requested merging useful analysis into the repository, excluding
original manufacturer firmware, cleaning the research tree and preserving
Ghidra work for future releases.

Repaired emulator return checks, local helper selection and the CH58x global
pointer. Added explicit DataFlash modeling to the minimal bridge harness and
assertions to the framing and route comparisons. Completed 33 probe jobs,
657 distinct asserted cases and 324 observed command-table rows. The counts
separate assertions from diagnostics and do not include the earlier 2835-case
run. Repeating the suite after relocation did not add distinct cases.

Applied pending function-recovery helpers, reconciled 322 named locations with
aliases at 22 addresses, corrected three non-returning reset attributes, and
exported 2453 main, 255 CH58x and 380 PD functions. A fresh copy reproduced the
exports. Both independent and canonical entry sets remain available; these
counts do not measure complete firmware coverage.

Corrected the reviewed notes on the VTOR write, decoder state/fill offsets,
PC-relative CH58x global pointer, factory-reset path, AF01 route prefix,
conditional waveform flag and fault addresses/thresholds. Synthetic execution
also reached an output-enable request through source-6 BE accessory input
without the remote grant. The actuator was modeled, so this is not a hardware
control-after-denial result. UR-008's disconnect-after-denial policy remains.

Merged reviewed notes, historical scripts/notes/outputs, names, logs, register
source definitions and a 22-page comparison report with its LaTeX sources.
Reorganized `docs/research/` into device, firmware, versioned evidence,
references and workflow sections. The relocation map resolves old paths in
historical records; current links and maintained tooling use the new paths.

Exported seven Ghidra programs as XML with memory contents disabled and JSON
metadata for mappings, hashes, functions, variables and options. All seven
fresh restores pass the core metadata and mapped-byte comparisons. Symbol
metadata differs after import, and variable metadata differs in 64 recovered
main functions, one bridge function and three SDK functions. Original metadata
is retained and the limitations are documented. These are not lossless project
backups; the private projects remain external.

Added a reusable FWD staging/import/comparison/restore workflow. Its V51 check
verified decoding, a fresh BLE import, manual-review match suggestions and
rejection of corrupt or mismatched inputs. Added a current research manifest
and an audit command. The original manufacturer images, SDK binary and Ghidra
databases remain outside the repository. No hardware I/O, commit, production
implementation or gate approval occurred.

Verification: offline recovery, export reproduction, post-relocation replay,
Ghidra restoration and preservation/link checks are recorded in the
[recovery record](docs/research/firmware/v51/independent/README.md),
[Ghidra verification](docs/research/firmware/v51/ghidra/verification/summary.json)
and [integrity audit](docs/research/firmware/v51/independent/verification/integrity.json).

### Research corrections from the independent reconstruction

Applied the corrections listed under "Independent firmware reconstruction,
tooling" and the review of the recovered bundle to docs/research/. No
device I/O.

- firmware/v51/independent/notes/hostlink.md, section 6: the work-mask
  table for `0x1FFF9550` had bits 7 and 8 swapped and bits 10 to 14
  shifted. Re-read from the transmit service `0x133BC`: bit 7 `D9`, bit 8
  `DB`, bit 9 `DD`, bit 10 `E5`, bit 11 `EB`, bit 12 `C5`, bit 13 `E0` to
  the CH58x, bit 14 `F0 AC`. The producers were right. Sections 8 of
  hostlink.md and the `FD` rows were brought into line; report.md and the
  rebuilt report.pdf carry the same correction. This corrects the bit table
  in the "Recovered firmware analysis" bundle of 2026-09-30.
- firmware.md, "Main MCU and hardware evidence": replaced the F460 clock
  argument with the full picture. The USART bases (`0x4001CC00`,
  `0x4001D400`, `0x40021000`) and the SRAM start rule out the F460; the
  clock routine at `0x1DAE8` alone fits it. The exact part stays open.
- protocol.md 1.1, 1.2, 1.3, 2.1, 2.2, 4.1, 4.5 and 5: added the code
  findings on the HID usage (0, not 4), the missing serial string, the
  meaning of the byte after the report ID, the run-time built name and
  manufacturer data, the AF01 first-byte discard, the two AF02 opcodes the
  CH58x answers itself, the inert `DB01`, the bind frame layout as the CH58x
  reads it, code answers for the three open bind rows, `outState` 0 and 3,
  the signed temperature, `wavePause`, `waveTime`, `chargeError` bits 9 to
  15, the link-drop behaviour, and four new client rules (opcodes never to
  send, unsolicited and deferred frames, one request in flight, unchecked
  request lengths). Each item names the function it was read from.
- README.md, "Firmware version": both host-visible versions come from the
  main MCU; the Bluetooth chip's own version is not sent to a host.
- TODO.md: TBD-004, TBD-005, TBD-006, TBD-007/013 and TBD-008 now carry
  the code answer and keep their hardware confirmation open.
- Both research manifests were regenerated and the research audit passes.

Item 2 of the earlier list (VTOR) had already been corrected in firmware.md
by the bundle merge, so nothing was changed there.

### Repository published

The user chose the name `mp305-remote` and had the repository created as a
public GitHub repository at https://github.com/jihlenburg/mp305-remote, with
the initial commit `139cb10` pushed to `main`. GitHub lists the license as
"Other" because the Commons Clause addition does not match its GPL-3.0
template; README.md states the terms.

### Requirements go back to the drawing board

The user decided to make docs/research the main source for the
requirements and to redo the user and system requirements from the
firmware findings, keeping the hazards, the decisions of 2026-09-29 and the
ADRs. Reason: the drafts were written against WebLink's model of the
device, and the firmware shows a different device in identification, bind
and reconnect, remote control, link discipline and link loss. The user also
decided to prepare Linux and Windows coverage with Parallels: USB HID by
passing the supply through to a VM, Bluetooth with a USB Bluetooth dongle
assigned to the VM. This changes TBD-009 from "Mac only".

Written docs/research/device-model.md as the drawing board: the device as
a host sees it, every statement with its evidence label and the firmware
note it was read from. The BLE work continues from there with the
requirements rewrite.

### User requirements rewritten from the firmware findings

1-user-requirements.md revision 8. The hazards keep their IDs with causes
rewritten from device-model.md; H-009 now also covers the factory reset
and stored settings. Surviving requirements keep their IDs. Rewritten:
UR-002 (the three trailing name characters identify a unit), UR-004 (mode
shown before control), UR-008 (prompt only for an unrecognised host, 30 s
bound), UR-010, UR-016 (denied or lost remote control as its own case),
UR-024 (output stays, grant released), UR-026, UR-027, UR-031. Added:
UR-032 (stable host ID so the supply remembers the host), UR-033 (no
changes to stored settings, tables or the Bluetooth chip), UR-034
(unsolicited and deferred frames), UR-035 (USB keepalive), UR-036
(remote-control confirmation over Bluetooth). TBD-002 to TBD-008 and
TBD-016 carry their code answers with the hardware check still open;
TBD-009 revised for Parallels; TBD-017 (automatic reconnect, user decision
at G1) and TBD-018 (unsolicited frames never captured) added. The
decisions of 2026-09-29 are unchanged. 2-system-requirements.md carries a
note that it lags revision 8 until it is redone. traceability.md lists the
new URs without ATs yet.

### UR-032 checked against the CH58x code

The user asked for the remembered-host requirement (UR-032) to be verified
against the device firmware. Ran the original CH58x code of the 1.6.0.51
update in Unicorn across two sessions with only the DataFlash carried over
(`spikes/firmware_reconstruct/scripts/ur032_remembered_host.py`, workspace
`~/mp305b-fw-re`). Result: a first bind with the fast flag 0 is forwarded
to the main MCU; after the MCU's `19 00` the CH58x stores the 16-byte host
ID at DataFlash `0x6F00`, notifies `19 00` and reports `BD 01`. In the new
session the same ID with a non-zero flag is answered `19 00` by the CH58x
itself with `BD 01` to the MCU and nothing forwarded; another ID gets
`19 FF` and `BD 00`; the same ID with flag 0 is forwarded again. Five IDs
are kept and the oldest is dropped. The BLE library, DataFlash and
notification calls are stubbed, and the unit at the bench runs 1.6.0.40
with an unknown CH58x version, so the hardware spike for TBD-006 stays
open. device-model.md 4.1 records the check. No device I/O.

### System requirements, tests and traceability rewritten

2-system-requirements.md revision 8 and 7-system-tests.md revision 5 were
rewritten against device-model.md and UR revision 8. Surviving SRs keep
their IDs. Added SR-048 (one connection per supply), SR-049
(per-installation host ID), SR-050 (fast bind first, prompt second),
SR-051 (USB keepalive every 2 s), SR-052 (complete payloads), SR-053
(remote-control confirmation over Bluetooth, 70 s bound), SR-054 (release
only in DC mode), with ST-043 to ST-049. The bind wait is bounded at 30 s
(SR-009), the placeholder byte and route tag are named for what they are
(SR-044), and the USB report format follows the firmware (SR-045).
TBD-017 is taken conservatively, no automatic reconnection, with the
alternative noted in SR-028.

8-acceptance-tests.md revision 8 adds AT-032 to AT-036 for the new URs and
the VM coverage code for Parallels (TBD-009).

scripts/check_traceability.py now generates docs/v-model/traceability.md
from the Parent, Mitigation and Verifies columns and, once code exists,
from the spec tags in the code. It reports no defects for the current
documents. AGENTS.md names the script and its `--check` mode.

### G1 decisions

The user settled the open points put to G1:

- TBD-017: automatic reconnection is allowed as an opt-in per session. When
  enabled, the software reconnects to the same supply (over Bluetooth with
  the remembered host), reads the state again first, and never takes remote
  control or changes the output until the user acts again. New UR-037,
  SR-055, ST-050 and AT-037; UR-024 and SR-028 allow the opt-in. The
  bench-safety note recommends USB for unattended runs (UR-031, SR-047).
- TBD-009: the Mac natively; Linux and Windows as Parallels VMs with the
  supply passed through for USB. The user buys a USB Bluetooth dongle for
  the VMs; until it works, Bluetooth on Linux and Windows is CI only.
- TBD-015: the residual risks of H-004 and H-006 are accepted with the
  mitigations of revision 8. The hardware spikes TBD-005 and TBD-006 still
  confirm the code findings.

1-user-requirements.md revision 9, 2-system-requirements.md revision 9,
7-system-tests.md revision 6 and 8-acceptance-tests.md revision 9 carry the
decisions. The traceability matrix was regenerated with no defects.

### G1 approved

The user approved docs/v-model/README.md as the process baseline,
1-user-requirements.md revision 9 and 8-acceptance-tests.md revision 9
(gate G1), and accepted ADR-0007 (synchronous Python API) and ADR-0008
(quality standards). The approved documents are in commit `7715b97`, tagged
`g1-approved`. The open points that remain are hardware checks of code
findings (TBD-002 to TBD-008, TBD-011 to TBD-013, TBD-016, TBD-018) and
TBD-014 (minimum OS versions). Next: G2 (2-system-requirements.md
revision 9 and 7-system-tests.md revision 6).

### G2 approved

The user settled TBD-014 (macOS 13, Ubuntu 22.04 with manylinux_2_35,
Windows 10 22H2), confirmed the poll pacing of SR-013 and the reconnection
retry of SR-055, and approved 2-system-requirements.md revision 10 and
7-system-tests.md revision 7 (gate G2). The approved documents are in
commit `878381e`, tagged `g2-approved`. Open at this level: the hardware
checks TBD-010 to TBD-013. Next: G3, the architecture and the integration
test specification.

### Architecture drafted for G3

Drafted docs/v-model/3-architecture.md (AR-001 to AR-052) from the chat
draft of 2026-09-29 and device-model.md: one Rust core with the modules
protocol, transport (ble, hid, mock), link, session, discovery and store;
the products on top; the link, bind and remote-control state machines; the
event dispatcher for unsolicited and deferred frames; the reconnect policy;
the opcode allowlist; one error taxonomy and one constants module for the
device's timings. docs/v-model/6-integration-tests.md (IT-001 to IT-052)
gives one mock-transport test per AR item. scripts/check_traceability.py
now covers levels 3 and 6 and reports no defects. An independent review
pass is running before the gate.

### Architecture review

An independent review of 3-architecture.md revision 1 and
6-integration-tests.md revision 1 returned 58 findings. The substantive
ones: a deferred `0xC9` (the Bluetooth remote-control prompt, up to 70 s)
would have occupied the single in-flight request slot and stopped the poll
and the loss detection; the allowlist, the one-write rule and the frame
log were "enforced by the trait", which nothing enforces; HID undoubling
was assigned to both `protocol` and `transport::hid`; SR-029, SR-030,
SR-038, SR-043, SR-047 and half of SR-046 had no AR; `btleplug` cannot
request an MTU; `forbid(unsafe_code)` cannot be re-allowed in `mp305-py`;
the re-read after a failed or timed-out `0xC8` was missing; no injectable
clock for the 30 s, 70 s and 10 min bounds. Revision 2 of both documents
resolves them: a `Guarded` wrapper around every transport, pure framing
and classification functions, immediate and deferred request kinds with an
urgent queue, the poll and keepalive in `link` on the Tokio clock, a
`Ready` state, the re-read rule, the busy inference order, the marker
refresh, packaging and csv items, and two new open points for the user:
TBD-021 (SR-007's MTU wording) and TBD-022 (an editorial note in
ADR-0008). The traceability matrix regenerates with no defects.

### G3 approved

The user settled TBD-021 (SR-007 changed to verify the negotiated MTU,
approved under the change procedure as revision 11) and TBD-022 (editorial
note in ADR-0008), and approved 3-architecture.md revision 2 and
6-integration-tests.md revision 2 (gate G3). The approved documents are in
commit `ae4af88`, tagged `g3-approved`. Open at this level: TBD-019 and
TBD-020, both settled by the OS runs. Next: G4 per module, starting with
the protocol module's detailed design.

### Protocol design review

An independent review of docs/v-model/4-detailed-design/protocol.md
revision 1 returned 35 findings. The main ones: the bind payload was
specified with two zero bytes (19 bytes) following SR-007, while the
captured WebLink frame carries one zero byte between the 16-byte host ID
and the fast flag (18 bytes); `Frame::new` was public and `policy::check`
looked at the opcode only, so a short frame was constructible; the HID
decoder differed from the device's parser for a doubled `AA` outside a
frame and judged the address too early; `Command::from_reading` copied
fields without bounds and set `model` 0 from a non-DC reading, which would
request a mode change; rejected setpoints used the wrong error variant;
1.005 V did not round to 101 in binary floating point; no `Reading`
assembly, no `reply_opcode`, no route per opcode. Revision 2 resolves
them. SR-007 (revision 12), IT-011 and IT-026 (revision 3) and ST-008
(revision 9) are marked changed for the one-zero-byte bind frame, approval
pending. The traceability matrix regenerates with no defects.

### G4 protocol approved

The user approved the bind-frame change (SR-007 revision 12, IT-011 and
IT-026 revision 3, ST-008 revision 9: one zero byte between the host ID
and the fast flag, the captured WebLink length) and
docs/v-model/4-detailed-design/protocol.md revision 2 (gate G4 for the
protocol module). The approved documents are in commit `52db370`, tagged
`g4-protocol-approved`. Implementation of the protocol module may start,
written from the DD, test first, with the 95 % coverage target.

### Protocol module implemented

First production code. The Cargo workspace (`mp305-core`, `mp305-app`,
`mp305-py`, `spikes` excluded) with the lints of AR-004, and the `protocol`
module of `mp305-core` written test first from the approved DD: `frame`,
`error`, `ble`, `hid`, `ops` (bind, info, telemetry, control, settings,
events), `policy`, `units`, `timing`, plus the crate-wide `Error` variants
the module needs. Verification: fmt, clippy `-D warnings` on all targets,
docs, 47 unit tests and 3 `compile_fail` doctests pass, line coverage
97.62 % against the 95 % target, traceability without defects. The record
is docs/v-model/records/2026-09-30-unit-protocol.md (commit `899c352`). Two test-only
deviations from the DD are recorded there (the property tests live in the
crate because `Frame::new` is crate-private; `for_tests` constructors under
`cfg(test)`); the DD carries an editorial revision for the test path.
`cargo llvm-cov` uses the Homebrew LLVM tools (AGENTS.md, Commands).

### Transport design review

An independent review of docs/v-model/4-detailed-design/transport.md
revision 1 returned 47 findings. The main ones: `btleplug` 0.13 does expose
the negotiated MTU (`Peripheral::mtu`), so the design reads it and fails a
connection below 74; its notification stream never ends on a disconnect,
the adapter's `DeviceDisconnected` event does; the notification stream is a
broadcast that drops on lag and must be taken before `subscribe`;
`hidapi`'s `HidDevice` is `Send` but not `Sync`, so one thread owns it and
writes arrive as jobs; a send cancelled by a timeout could overlap the next
write unless the permit travels with a spawned task; the concrete
transports' `send` must be `pub(crate)` or the allowlist can be bypassed;
`unpack_in` must require the report ID rather than guess; the mock needed
routes, repeats, timed errors, a stop time and a factory for reconnection;
the coverage exclusion for vendor glue is a new class that ADR-0008 does
not sanction. Revision 2 resolves them. ADR-0013 (coverage exclusion for
vendor glue) is proposed. AR-017 (revision 3) and IT-017 (revision 4) are
marked changed: keeping a frame's reports together is the transport's job,
waiting for the reply is `link`'s. Both wait for the user's approval with
the transport gate.

### G4 transport approved

The user accepted ADR-0013 (coverage exclusion for the vendor glue of the
transports), approved the AR-017 (revision 3) and IT-017 (revision 4)
change, and approved docs/v-model/4-detailed-design/transport.md
revision 2 (gate G4 for the transport module). The approved documents are
in commit `cb5ea3b`, tagged `g4-transport-approved`. AGENTS.md carries the
coverage exclusion pattern. Implementation of the transport module may
start.

## 2026-10-01

### Transport module implemented

The `transport` module of `mp305-core` written test first from the
approved DD: the `Transport` trait, `Guarded` (allowlist and route check,
one write permit that travels with a spawned write task so a cancelled
send cannot overlap the next, producer-side timestamps, the frame log under
`mp305_core::frames`), `ble` and `hid` glue over `btleplug` 0.13 and
`hidapi` 2.6 with the pure parts in `ble_route` and `hid_report`, the
scripted `mock` with its factory, `AnyTransport`, and `Error::Transport`.
Verification: fmt, clippy `-D warnings`, docs, 58 in-crate tests, 4
external tests and 3 doctests pass; line coverage 96.4 % of `mp305-core`
with the vendor glue excluded under ADR-0013; the two glue files inspected
against the DD checklists; traceability without defects. The record is
docs/v-model/records/2026-10-01-unit-transport.md (commit `47f6996`), which also lists the
deviations (crate-private constructors instead of `pub(crate)` trait
methods, scheduled-time stamps in the mock). The DD carries an editorial
revision 3 for the constructor wording.

### Transport DD revision 4: the visibility rule made structural

The transport record's first deviation (DD-TRANS-012 and DD-TRANS-022 asked
for `pub(crate)` trait methods, which Rust cannot express) was put to the
user with three options: keep revision 3 as editorial, reword the DD to the
crate-private constructors the code already had, or make the rule one the
compiler enforces. The user chose the structural fix. Revision 3 is
retracted as mislabelled: the replaced sentence was a design statement with
its own rationale, so its replacement was a change, not editorial.

Revision 4, approved by the user in chat on 2026-10-01: the `ble` and
`hid` modules are crate-private, so `Ble` and `Hid` cannot be named outside
`mp305-core`; `AnyTransport` is an opaque struct around a private enum with
crate-private constructors and `From<Mock>` under the `mock` feature, so a
product cannot take the transport out of a `Guarded`. UT-TRANS-007 (three
`compile_fail` doctests pinned to E0603) is the test of the rule;
UT-TRANS-006, UT-TRANS-011 and UT-TRANS-021 were reworded. Impact: the
public API loses the `transport::ble` and `transport::hid` modules and the
variants of `AnyTransport`; no AR item changes. Verification: all gates
pass, 6 doctests; line coverage of `mp305-core` 96.09 % with the ADR-0013
exclusion, down from 96.44 % because the two new crate-private constructors
are reachable only with a device (record, run 2:
docs/v-model/records/2026-10-01-unit-transport.md).

### Link design review

An independent review of docs/v-model/4-detailed-design/link.md revision 1
returned 23 findings, two of them blockers: the urgent output-off was
chosen before the `0xC8` block was checked, so it skipped the block by
candidate order; and the 4 s loss bound did not hold, because queued
requests from `session` go before the poll and, uncounted, delay the three
poll timeouts without limit. The other main ones: the send step ran once
per loop turn and could stall after a deferred write; the timer arm could
fire on every turn while a request was in flight; a reply and its deadline
in the same instant had no defined outcome; a fast bind could take a
prompt bind's `0x19`; an expired remote-control expectation did not set
the block; a request cancelled by its caller was still written; the
handle's async `request` could not be used with `close(self)` or in a
`select!`; replies carried no arrival stamp; only the poll was paced;
closing the guard before reporting the loss could delay the report; the
task tests assumed helpers the `Stub` and the crate's test items do not
offer from `tests/`. Revision 2 resolves all of them (its revision row
lists the changes) and adopts the reviewer's recommendation on the three
open decisions: a bad frame is dropped and counted, every immediate
timeout counts toward the loss rule, and the block applies to the
output-off. The second of these changes AR-022, SR-028 and IT-022, and
the first changes DD-TRANS-004; DD-TRANS-001's sentence about `link`'s
shape changes too. All five are marked changed with the proposed wording,
approval pending at G4 link. IT-020 and the transport DD's `Stub`
description got editorial notes.

### G4 link approved

The user approved the link module design, revision 2 of
docs/v-model/4-detailed-design/link.md, on 2026-10-01 (commit `1a49fef`,
tag `g4-link-approved`), and with it the changes to AR-022, SR-028 and
IT-022 (every immediate request that times out counts toward the loss
rule), to DD-TRANS-004 (a frame that fails to decode is dropped and
counted; the link goes on) and to DD-TRANS-001 (only the link task is
generic). The user also asked on 2026-10-01 that implementation work be
delegated to Opus 5.5 agents from now on; the link module is the first.

### Link module implemented

The `link` module of `mp305-core` written test first from the approved DD
by a delegated Opus 5.5 agent, as the user asked on 2026-10-01: the `Link`
handle with synchronous enqueueing and `'static` request futures, `Pending`
for deferred requests, the pure `class` (classes, eligibility, dispatch) and
`queue`, the task loop with its biased select, the poll, the USB keepalive,
the loss rule and close, `Error::Timeout` and `Error::LinkLost`. The agent
reported four gaps in the design it had to fill (a missing wake-up for a
paced `0xC2` with polling off, the poll while a queue head waits, the
late-reply counter for an unawaited expectation, the length refusal in
`output_off`); they are recorded as revision 3 of the DD, which the user approved on 2026-10-01 together with the commit.
Verification in the main session: fmt, clippy `-D warnings`, docs, 99
in-crate tests (41 new), 4 external tests and 6 doctests pass; line
coverage 96.4 % of `mp305-core` with the ADR-0013 exclusion; `task.rs`
inspected against DD-LINK-020; traceability without defects. The record is
docs/v-model/records/2026-10-01-unit-link.md.

### Session design review

An independent review of docs/v-model/4-detailed-design/session.md
revision 1 returned 40 findings, one of them a blocker: a session that
runs control commands one at a time keeps an output-off from reaching the
link's urgent queue, and a setpoint command built before the output-off
could switch the output back on. The other main ones: the guard order was
impossible as written and could prompt the user for a call that would be
refused anyway; the deferred grant's `0xC9` did not set the freshness
marker; copying `output` 1 into a setpoint command is a reading of SR-020
and AR-025 that the user has to approve; an output-off answered status 1
left the output on; close did not cover a pending remote request, released
with a changed `output` byte and could not be called with `&self`; a loss
was handled twice; the link transition table was incomplete; commands
queued before a loss could run after a reconnection; `ready()` was not
defined on every path; the `0xC3` fixture offsets were wrong; several test
cases could not happen on the mock; every test used the same identifier on
a process-wide registry. Revision 2 resolves all of them (its revision row
lists the changes), puts the output-off and close on a priority channel
that cancels queued and unwritten commands, and lists seven decisions for
G4: two new error variants (AR-050), the test infrastructure (DD-TRANS-030
and DD-TRANS-031, a fixtures module), the `output` copy rule (SR-020,
AR-025), the close argument, the marker refresh rate (SR-046), the link
drop during the bind (SR-009), and the USB-host hint on timeouts (AR-030).
A focused second review of revision 2 was requested.

The second pass on revision 2 found five more majors (the session cannot
see whether its `0xC8` was written, so an output-off always cancels the
command in progress with a "may have been applied" reason; no fast-bind
retry, since it would trip the link's loss count; the command arm stays
enabled during the connect flow; two event channels the task never
awaits; one close test expected the wrong release byte) and six minors;
revision 3 resolves them. The final check found no blocker or major and
three minors (a closing flag, the `FaultsChanged` order, the fast-bind
bound in the SR-009 wording), applied in the same revision. The reviewer
needed no further pass. Nine decisions go to the user at G4 session; the
items they change (AR-025, AR-027, AR-030, AR-050, SR-009, SR-020, SR-029,
SR-046, IT-050, DD-TRANS-030, DD-TRANS-031) are marked changed with the
proposed wording.

### G4 session approved

The user approved the session module design, revision 3 of
docs/v-model/4-detailed-design/session.md, on 2026-10-01 (commit `40a5925`,
tag `g4-session-approved`), and with it the nine decisions of its
section 9: the error variants `AlreadyOpen` and `Cancelled` (AR-050,
IT-050), the mock's handle and reply time windows and the fixtures module
(DD-TRANS-030, DD-TRANS-031), the `output` copy rule (SR-020, AR-025),
the close argument, the marker refresh rate (SR-046), the bind link drop
and the fast-bind bound (SR-009), the USB-host hint (AR-030), the
output-off exception (AR-027) and the output-off at close only when the
output is on (SR-029). The implementation goes to an Opus 5.5 agent.

### Store, csv and discovery design reviews

Independent reviews of the three remaining core DDs, each drafted while
the session implementation ran. Store (revision 1, 13 findings): no
`sync_all` before the rename and a fixed temp name; a transient read error
would have destroyed a valid host ID; two processes starting on an empty
directory could end with two IDs; the marker file held only the time while
SR-046 asks for the identifier too; the retry path of the generator was
untestable; the parse rules were undefined. Csv (revision 1, 10 findings):
the Python helper could not reach the writer, so a second implementation
of the format would have appeared; the two time columns could differ by a
millisecond; the fixture offsets and the rounding of the electrical
columns were unstated. Discovery (revision 1, 17 findings, one blocker):
on Linux BlueZ replays its cache as "discovered" events when the event
stream is taken, so a supply that is off or busy would have been reported
as found; `connect` had no time bound and `btleplug`'s connect waits
forever; concurrent scans on one adapter would stop each other; cached or
template names gave fake unit characters; vendor calls sat in `mod.rs`
against IT-002; decidable rules sat in the excluded glue. Revision 2 of
each resolves everything (the revision rows list the changes); the store
and csv re-check found only minor items, folded in. Discovery's re-check
was requested. ADR-0014 (the coverage exclusion extended to the discovery
glue) is proposed for the G4 discovery gate, together with changes to
AR-032, IT-032, AR-014, DD-PROTO-051, DD-TRANS-002 and SR-001 and the
store's two dependencies.

### G4 store, csv and discovery approved

The user approved the store, csv and discovery module designs on
2026-10-01 (revision 2 of each; commit `a26c3fe`, tags `g4-store-approved`,
`g4-csv-approved`, `g4-discovery-approved`), with their decisions:
`getrandom` 0.4 and `tempfile` for the store; the Python CSV helper
formatting rows through the native function, the lowercase `mode`
spelling with `;` between faults, and the shared `civil` module; for
discovery ADR-0014 (accepted), `SetpointRange.min` (DD-PROTO-051), the
`Found` shape and classifier signatures (AR-032, IT-032), five timing
constants (AR-014, IT-014), the name layout rule with the veto (SR-001),
and a `Display` for `Kind` (DD-TRANS-002). The discovery re-check had
found three more majors (a deprecated `hidapi` call that can panic, a
timed-out OS connect left pending, the veto contradicting its rationale),
resolved before the gate. Every module of `mp305-core` now has an
approved design.

### Session implementation review

The session module, implemented by a delegated agent from DD revision 3
(166 tests, all gates passing in the main session, 93.7 % line coverage),
went through an adversarial review before any commit: seven reviewers with
different lenses (conformance of the connect flow, of control, of loss and
close; concurrency; safety; test quality; the mock, fixtures and errors),
and one independent skeptic per blocker or major finding, prompted to
refute it. 32 findings were confirmed and none refuted; they reduce to
about fifteen distinct issues. Blockers: an `output_off` during the
connect flow or a reconnection attempt discarded the flow, so `ready()`
never resolved; a second `output_off` did not cancel the commands queued
before it, so off, on, off ended with the output on; an output-off right
after an accepted setpoint sent the old setpoints back, so the next
output-on would have applied the old voltage (a gap in the design, SR-022).
Also: the firmware publishes a command's effect into `0xC3` on a later UI
task pass (firmware notes, commands 5.7 and 6.1), so over USB the first
reading after a `0xC9` can show the old state; a close after a cancelled
in-flight command judged the output from an older reading; the close
cleared the marker even when its output-off failed; a NaN limit switched
the limit off; several tests asserted less than their specification.
Revision 4 of the session DD holds the design changes (the settle rule of
100 ms, the output-off taking the last accepted setpoints, user limits on
copied setpoints, the close and marker rules, validated limits), with
SR-019, SR-022, SR-024, AR-014 and AR-025 changed and TBD-023 added. The
user approved revision 4 on 2026-10-01 and chose 100 ms for the settle
time. The user also gave standing permission on 2026-10-01 to commit and
push verified work without asking each time; gate approvals and design
changes still go to the user first. The same kind of review ran on the
drafts of the Python library design (71 confirmed findings) and the
desktop app design (80 confirmed, ten of them blockers around the window
close path leaving the output on); both drafts are being revised.

### Session module implemented

The `session` module of `mp305-core` implemented test first by delegated
Opus 5.5 agents from DD revision 4, with the approved changes outside the
module (`SetpointRange.min`, `Display` for `Kind`, six timing constants,
the mock's reply time windows and handle, the shared fixtures).
Verification in the main session: fmt, clippy `-D warnings`, docs, 232
tests (220 in-crate, 6 external, 6 doctests) pass; line coverage 95.3 %
of `mp305-core`, 91.1 % of `session/task.rs`; traceability without
defects. One independent reviewer read the final code and judged it fit
to commit as the implementation of revision 4; it found four further
gaps (the overlay inside the settle window, a timed-out `0xC8` applied
late, the output-off skipped after a failed decision poll in a close, a
`close(true)` on a lost link returning `Ok`), which go into revision 5.
Two unit test entries (UT-SESS-029 case 2, UT-SESS-056 part 1)
contradicted the design items they verify; the tests follow the design
items and the entries are to be restated in revision 5. The record is
docs/v-model/records/2026-10-01-unit-session.md.

Working rules agreed with the user on 2026-10-01 after three review
workflows had used about 23 million subagent tokens: designs are written
in the main session, coding goes to Opus agents, mechanical checks to
Sonnet, with one independent review per design or safety-relevant module
on Opus; one reviewer per artifact, findings deduplicated before any
verification, no multi-round fan-outs.

### Csv and civil modules implemented

The `csv` and `civil` modules of `mp305-core` implemented test first by a
delegated agent from csv DD revision 2: `header()`, `format_row()` and the
`Writer`, and the calendar conversion with the two RFC 3339 formatters
that `session::texts` now calls. Verification in the main session: all
gates pass, 241 tests; line coverage 100 % and 99.1 % of the two files,
95.8 % of `mp305-core`. Open: UT-CSV-003 is to gain the `cv` and
`held_above` cases. The record is
docs/v-model/records/2026-10-01-unit-csv.md.

### Store module implemented

The `store` module of `mp305-core` implemented test first by a delegated
agent from store DD revision 2: the host ID file with create-if-absent
through a hard link (and a `create_new` fallback), atomic writes with
per-process temp names and `sync_all`, the marker files holding the time
and the identifier, the `session::Markers` impl, and the file name mapping
with the pinned FNV-1a constants. Verification in the main session: all
gates pass, 259 tests; line coverage 94.8 % to 100 % of the three files,
95.7 % of `mp305-core`. Open: two tests go beyond their entries'
inputs, and identifiers with surrounding whitespace or a line break
cannot round-trip (the DD is to say what happens). The record is
docs/v-model/records/2026-10-01-unit-store.md.
