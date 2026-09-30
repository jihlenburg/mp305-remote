# Device behaviour model for a host

Status: draft, 2026-09-30. The starting point for the rewrite of the user
and system requirements.

This document describes the MP305B as a host sees it: what it advertises,
what it accepts, what it answers, when it answers later, and which state a
host must track. Every statement comes from the 1.6.0.51 firmware update
unless it says otherwise, and names where it was read. The detailed evidence
is in [protocol.md](protocol.md), [firmware.md](firmware.md) and the notes
of the independent reconstruction:
[hostlink.md](firmware/v51/independent/notes/hostlink.md),
[commands.md](firmware/v51/independent/notes/commands.md) and
[ch58x.md](firmware/v51/independent/notes/ch58x.md). Cited as `hostlink 6`,
`commands 5.7`, `ch58x "Advertising"`.

Evidence labels: **code** means confirmed in code (disassembly, or the
original instructions executed in an emulator with synthetic inputs);
**hardware** means confirmed on the user's unit; **inferred** means a
reading of the code that is not itself in the code. The user's unit ran
application 1.6.0.40 when the captures were taken, so every code statement
still needs a version-matched hardware check before it is relied on for the
unit at the bench.

The device is three processors. The main MCU runs the supply, the user
interface and every command handler. A WCH CH58x carries Bluetooth and USB
and bridges both to the main MCU over one UART. An 8051 controller runs the
USB-PD port. A host only ever talks to the CH58x, and the CH58x answers a
few things itself (section 3). Everything else is the main MCU's answer.

## 1. Identification

| Fact | Evidence |
|---|---|
| The advertised name is 29 characters: `0000`, an 8-character name the main MCU stores in the CH58x (`MP305B` and two spaces in 1.6.0.51), `S` while remote control is enabled on the device and no USB host is active, spaces, and three characters derived from the unit's Bluetooth address. | code, ch58x "Advertising"; hardware for `0000MP305B  S             E!K` |
| The three trailing characters identify a unit: `'!' + v % 94`, `'!' + (v / 94) % 94`, `'!' + (v / 8836) % 94` with `v = (b0 ^ b1) << 24 \| (b2 ^ b3) << 16 \| b4 << 8 \| b5` over the address bytes. Two units differ unless their addresses collide in `v`. | code, ch58x "Advertising"; the formula, not its uniqueness, is confirmed |
| The manufacturer data is company `0xABBA`, then `AF FA`, then `01 35 02 00` from the main MCU, then 14 bytes a host can write (zero unless written). | code, ch58x "Advertising"; hardware for the first 10 bytes |
| The advertising interval is 500 ms. Advertising is off while a host is connected, while a USB host is active, and while remote control is disabled on the device. | code, ch58x "Advertising" |
| Over USB the device is VID `0x28E9`, PID `0x028A`, product string from the same 8-character name, manufacturer `wch.cn`. The serial number string request stalls; there is no serial. The HID collection is Generic Desktop, usage 0. | code, ch58x "USB HID"; not observed on hardware (TBD-013) |
| `0xE0` returns the main MCU's application version and hardware revision. Over Bluetooth the reply is `E1`, version (4), `MP305B` (8), hardware (4). Over USB it is `E1`, `MP305B` (8), 8 bytes from the bootloader's identity block (inferred: hardware revision and bootloader version), version (4), name (10). The CH58x's own version never reaches a host. | code, commands 5.16; hardware for the Bluetooth layout with 1.6.0.40 |

## 2. Transports as the host sees them

### 2.1 Bluetooth LE

| Fact | Evidence |
|---|---|
| Service `AF00` with characteristics `AF01` and `AF02`, both read, write, notify. `DB00`/`DB01` is inert. `180A` holds vendor placeholders. No OTA service in the application image. | code, ch58x "GATT database"; hardware for the table |
| A write to `AF01` is `placeholder, opcode, payload`. The CH58x discards the first byte unread. The reply arrives as a notification on `AF01`: `0x31, opcode, payload`. The `0x31` is a constant route tag, not an address. | code, ch58x "What a host writes: AF01", hostlink 3; hardware |
| A write to `AF02` is `opcode, payload`. The reply is a notification on `AF02` without prefix. | code, ch58x "What a host writes: AF02"; hardware |
| Any opcode can be written on either characteristic; the main MCU does not see which one. `0x18` on `AF01` and `0xE0` on `AF02` both work. | code, hostlink 2 and 4 |
| Opcodes `0x10` and `0xC0` on `AF01` are handled by the CH58x and rewrite its advertising data. A host must never send them. `0x00` on `AF02` is answered by the CH58x with 13 bytes including the Bluetooth address. | code, ch58x "AF01", "AF02" |
| One frame is one notification; no fragmentation. The CH58x accepts an ATT MTU up to 247 and does not start the exchange. The longest reply is 70 bytes (`DF`) plus the tag. | code, ch58x "Notifications", "MTU"; hardware for MTU 247 |
| Notifications must be enabled on both characteristics on every connection; the CH58x resets them on disconnect and drops a reply whose characteristic has them off (the main MCU then retransmits for about 5 s). | code, ch58x "Connection handling", "Notifications" |
| The CH58x holds one frame per direction. A second write before the first was forwarded (about 1.25 ms) replaces it. | code, ch58x "Pacing on BLE" |
| Bluetooth writes are dropped silently while a USB host is active (section 4.3). | code, ch58x "Interface arbitration" |

### 2.2 USB HID

| Fact | Evidence |
|---|---|
| Output report ID 1: `01, n, n stream bytes`, `n` from 1 to 62. The stream is the framed request `AA 12 len opcode payload sum` with every `AA` after the first doubled; it may span reports. | code, ch58x "OUT reports"; protocol.md 1.1, 2.2 |
| Input report ID 2: `02, n, n stream bytes, zero padding`, `n` from 1 to 62 in every report. The host concatenates, un-doubles `AA` pairs, and checks length and checksum. Replies carry address `0x21`. | code, ch58x "IN reports" |
| Address byte `0x12` means source 1 (USB host), destination 2 (main MCU). The main MCU replies to the source nibble. | code, hostlink 2 |
| A frame must not share a report with another frame, and a new frame must not start before the reply to the previous one arrived: the bridge can otherwise forward a corrupted frame with a valid checksum. | code, ch58x "OUT reports" (emulated) |
| Class requests (`SET_IDLE`, `GET_REPORT`, `SET_REPORT`) stall. Only the interrupt endpoints carry data. | code, ch58x "Descriptors" |
| There is no bind on USB (section 4.2). The USB device detaches while a Bluetooth host is bound. | code, ch58x "Bind on USB", "Interface arbitration" |

## 3. What the CH58x answers itself

| Request | Reply | Evidence |
|---|---|---|
| `AF02`: `00` | `01`, link state, bind state, 32-bit connection timer, 6-byte Bluetooth address | code, ch58x "AF02" |
| `AF02`: `18`, 16-byte host ID, filler, last byte non-zero | `19 00` if the ID is one of the up to five remembered IDs, else `19 FF`; no prompt on the device | code, ch58x "AF02" |
| `AF01`: `10` or `C0` | `31 C1 00`; must not be sent | code, ch58x "AF01" |

Everything else is forwarded to the main MCU.

## 4. Link state

The main MCU keeps one host link state: none, Bluetooth host bound, or USB
host active (`S+3`; hostlink 6, commands 1). A host must model it as below.

### 4.1 Bluetooth: connect and bind

1. Connect, enable notifications on `AF01` and `AF02`.
2. Write `18`, then 16 bytes of host ID, then filler, then the fast flag as
   the last byte of the write. WebLink's frame is
   `18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00`: ID
   `00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00`, flag 0 (code, ch58x
   "AF02"; hardware for the frame and the replies).
3. Flag 0: the request goes to the main MCU, which shows "Confirm Bluetooth
   Binding". Allow gives `19 00`, deny gives `19 FF`, both deferred until a
   button is pressed (code, hostlink 5; hardware: 3.0 s, 3.6 s, 7.7 s).
   After a `19 00` the CH58x stores the ID (oldest of five dropped) and
   reports the link as bound to the main MCU (code, ch58x "AF02").
4. Flag non-zero: the CH58x answers from its stored IDs without a prompt
   (section 3). A host that was allowed once, using a stable host-specific
   ID, reconnects without a person at the supply (code; not yet tested on
   hardware, TBD-006).
5. A link that is not bound is terminated by the CH58x about 30 s after
   connecting (code, ch58x "Connection handling"; TBD-008). The main MCU's
   prompt also closes on its own after tens of seconds and then replies
   `19 FF` (inferred, hostlink 5).
6. Reads are answered before and after the bind, and after a deny (code,
   hostlink 4; hardware). The project still refuses and disconnects after a
   deny (user decision, TBD-001).

### 4.2 USB: no bind

Any frame from USB marks the USB link active. A `18` over USB is answered
through the same prompt, but nothing requires it: remote control is the
gate (section 5) and it is granted at once over USB (code, hostlink 5 and
6; not observed on hardware, TBD-004).

### 4.3 One host at a time

| Fact | Evidence |
|---|---|
| A bound Bluetooth host makes the main MCU switch the USB device off. | code, ch58x "Interface arbitration" |
| A frame from USB makes the main MCU stop Bluetooth advertising and drop all Bluetooth writes silently, even on an open link. After 8 s without a USB frame Bluetooth works again. | code, ch58x "Interface arbitration", hostlink 6 |
| A second Bluetooth central is disconnected at once. | code, ch58x "Connection handling" |

### 4.4 Link loss

| Fact | Evidence |
|---|---|
| The main MCU treats the link as down when the CH58x reports the Bluetooth link lost, after about 8 s without a USB frame, or after about 50 unacknowledged retransmissions toward the CH58x (about 5 s). | code, hostlink 6, commands 1 |
| On link down the remote-control grant is cleared on the next UI pass. The output enable is not touched: the output stays as it was. | code, hostlink 6; every writer of the output enable traced; hardware check pending (TBD-005, `link_drop` spike) |
| Over USB a host must send a frame at least every 8 s to keep the link and the grant. Over Bluetooth the CH58x reports the loss; nothing is required from the host. | code, commands 1 |
| A Bluetooth host that disconnects without ever binding produces no message to the main MCU. | code, ch58x "Connection handling" |

## 5. Remote control

Control commands (`C8` DC, `E2` program, `E8` PD, `EE` charge) share one
gate (code, commands 3). `rc` is payload byte 0.

| Rule | Evidence |
|---|---|
| `rc = 2` requests control. Over USB it is granted at once, reply status 0. Over Bluetooth there is no reply; the device shows "Allow Remote Control" and later sends the reply of the current mode's command (`C9`, `E3`, `E9` or `EF`) with status 0 (allowed) or 1 (denied, or no key press for about 60 s, or another screen open). | code, commands 3, hostlink 6; not observed on hardware (TBD-012) |
| While a request is pending, every control command gets no reply at all. | code, commands 3 |
| `rc = 1` applies the command only while the grant is held; without it the reply is status 1 and nothing is applied. | code, commands 3 |
| `rc = 0` releases the grant, but only when sent with the command of the current mode; in another mode the reply is `FF` and the grant stays. | code, commands 3 |
| The grant is cleared on link loss, on device power-off and at boot. The device does not switch the output off when it clears the grant. | code, hostlink 6 |
| Reads, settings writes (`C6`) and the program, profile and charge writes are not gated by the grant or the bind. | code, commands 2, 5.6; permissions.md |

## 6. Request and reply discipline

| Rule | Evidence |
|---|---|
| One request in flight. The main MCU holds one outstanding reply and the CH58x one frame per direction; a second request can overwrite the first or lose its reply. | code, hostlink 1 and 4, ch58x "Pacing" |
| The reply opcode is request + 1, except `20` which replies `20`. | code, commands 2.1 |
| Deferred replies: `19` after the bind prompt, `C9`/`E3`/`E9`/`EF` after the remote prompt, `D9` chunks after `D8`, `DB 00` after the last `DA` chunk. They can arrive seconds later. | code, commands 8, hostlink 5 |
| Unsolicited frames: `C5` (settings changed on the device), `DD` (selected program), `E5` (active PD profile), `EB` (a charge ended), `DB`. They arrive whenever the device's own state changes. | code, commands 8 |
| Replies must therefore be matched by opcode and state, not by order. | derived |
| Request lengths are not checked. A short request is completed with stale bytes from an earlier request on the same channel. Always send the full payload. | code, commands 2.1 |
| Opcodes the device ignores get no reply at all: every value not in the command table, plus `D8` with an unknown program id. | code, commands 2.1, 5.12 |
| The observed Bluetooth round trip for a read was 120 to 135 ms. | hardware |

## 7. Modes and the transfer-busy flag

| Rule | Evidence |
|---|---|
| Live mode (`model`): 0 DC, 1 program, 2 PD, 3 charge. Each control command works only in its own mode; in another mode the reply is `FF`. | code, commands 3 |
| A control command with a different `model` requests a mode change and reads no other field. It is refused (`FF`) while the output is on. A mode change resets energy and time. | code, commands 5.7, 6.2 |
| `D2`, `D6` and `DA` (profile and program writes) switch the output request off. A `D2` without its save byte, or a rejected `D2` or `DA`, leaves the device "busy": output-on and mode changes return `FF` until a later successful save. | code, commands 5.9, 5.13 |
| `A2` (language) switches the output request off when the value changes. | code, commands 5.3 |

## 8. Telemetry (`C2` to `C3`)

37 reply bytes plus the tag; every byte is always written (code, commands
5.4). Units from the producers (code, commands 7.1):

| Payload | Field | Unit and meaning |
|---|---|---|
| 0 | outState | 0 output off, 1 CV, 2 CC, 3 measured voltage held above the setpoint at low current (inferred) |
| 1 | batteryState | 0 on battery, 1 external input charging, 2 charging held |
| 2 | percentage | internal battery, percent |
| 3, 5 | voltage, setVoltage | 10 mV; measured reads 0 with the output off |
| 7, 9 | current, setCurrent | 1 mA; measured reads 0 with the output off |
| 11 | workingTime | seconds of output-on time |
| 15 | energy | 0.1 Wh, at most 9999 |
| 19 | power | 10 mW |
| 21 | currentOver | 0 constant-current limit, 1 trip after the OCP delay |
| 22 | realChange | bit 0 voltage, bit 1 current: front-panel knob edits apply live |
| 23 | voltageSlow | 0 step, 1 ramp at `slopeSteps` mV per 100 ms, also from 0 V at switch-on |
| 24 | output | actual power-stage state |
| 25 | model | live mode |
| 26, 27 | voltageBoard, currentBoard | UI entry-mode flags (inferred) |
| 28 | temperature | signed 8-bit, °C |
| 29 | chargeError | fault bits 0 to 8 (below); bits 9 to 15 never set here |
| 31 | wavePause | 1 in every state found; not a host flag |
| 32 | waveTime | raw output-on time in ms; reset by refresh and mode change |

Hardware confirmed with the output off: setpoints, output, percentage,
temperature, currentOver, workingTime, energy, power (protocol.md 4.1).
Measured voltage, current and outState 1 and 2 are not yet seen on hardware
(TBD-011).

Fault bits (code, commands 7.2): 0 reversed output, 1 low battery, 2
battery too cold, 3 battery overheat, 4 system overheat, 5 over-current
(software, after the OCP delay with `currentOver = 1`), 6 over-voltage,
7 power-stage start failure, 8 output voltage sensor disagreement. Any
active fault forces the output off every cycle and makes output-on requests
fail with `FF`.

## 9. DC control (`C8`)

Payload: `rc, u16 voltage (10 mV), u16 current (1 mA), realChange,
voltageSlow, currentOver, output, model, refresh` (code, commands 5.7;
protocol.md 4.2).

| Rule | Evidence |
|---|---|
| Validation and application are sequential; a field before the first bad one is applied and the reply is still `FF`. A `FF` after the voltage leaves the new voltage applied. | code, commands 5.7 |
| Bounds: voltage at most 3050 (30.50 V), current at most 5100 (5.100 A), realChange at most 3, voltageSlow, currentOver, output at most 1, model at most 3, refresh at most 1. The rated values are 30.0 V and 5.0 A; what the output does above them is open (TBD-003). | code, commands 5.7 |
| Output on: `FF` while any fault is active or the device is busy (section 7). With `voltageSlow = 1` the output ramps from 0 V. | code, commands 5.7, 6.1 |
| `refresh = 1` resets energy and time. | code, commands 6.1 |
| The reply is `C9` and one status byte: 0 accepted, 1 remote control not granted, `FF` rejected. | code, commands 4; not observed on hardware (TBD-012) |

## 10. Settings (`C4`, `C6`)

`C5` is 11 payload bytes: charge limit, volume, screen off, auto shutdown,
screen direction, u16 ramp step, u16 OCP delay, u16 USB line drop (code,
commands 5.5; hardware for the layout). `C6` writes them field by field with
these bounds and stops at the first failure, leaving earlier fields written:
80 to 100, 0 to 3, 0 to 1, 0 to 30, 0 to 1 (checked, not stored), 0 to 1000,
0 to 1000, two flags 0 to 1, 0 to 1000 (code, commands 5.6). A deferred
worker rounds some values up to the menu steps (firmware.md). `C5` is also
sent unsolicited when a setting changes on the device (code, commands 8).

## 11. Opcodes

| Group | Opcodes | Host use |
|---|---|---|
| Read | `00`, `A0`, `C2`, `C4`, `D0`, `D4`, `DC`, `DE`, `E0`, `E4`, `EA`, `EC` | allowed |
| Bind | `18` | Bluetooth only |
| Control | `C8`, `E2`, `E8`, `EE` | with the grant, in the matching mode |
| Write | `A2`, `C6`, `D2`, `D6`, `D8`, `DA` | change device settings or stored tables; out of v1 scope |
| Never | `10`, `C0` (CH58x advertising data), `BE` (accessory input), `20`, `F0`, `F2`, `F4`, `F6`, `FC`, `FE` (maintenance; `FE AA 55` is a factory reset with reboot) | never |
| Ignored | everything else | no reply |

Evidence: code, commands 2.1, ch58x "AF01"; protocol.md 5.

## 12. Timings a host must respect

| Value | Meaning | Evidence |
|---|---|---|
| 30 s | Bluetooth link dropped by the CH58x if not bound | code (TBD-008) |
| about 60 s | remote-control prompt closes as denied | code, hostlink 6 |
| 8 s | USB link and grant lost without a frame | code, commands 1 |
| about 5 s | main MCU gives up retransmitting a reply the CH58x could not deliver | code, hostlink 6 |
| 1.25 ms | bridge tick: a second frame within it overwrites the first | code, ch58x "Startup" |
| 100 ms | WebLink's pause after each reply; the Bluetooth cycle took about 225 ms | hardware |
| 120 to 135 ms | Bluetooth round trip for a read | hardware |

## 13. Still open on hardware

Every code statement above is for the 1.6.0.51 update, while the unit at the
bench reported 1.6.0.40. These points have code answers and no hardware
confirmation yet: TBD-003 (setpoint top), TBD-004 (USB and the prompt),
TBD-005 (link drop), TBD-006 (remembered host), TBD-007 and TBD-013 (USB
enumeration and serial), TBD-008 (bind timeout), TBD-011 (measured
scaling), TBD-012 (`C9` on hardware), and the deferred and unsolicited
frames of section 6, which no capture has shown yet.
