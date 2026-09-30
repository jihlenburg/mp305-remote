# 2. System requirements (SR)

Status: draft

This draft refines revision 2 of
[1-user-requirements.md](1-user-requirements.md), which has not passed G1.
Revision 8 of that document (2026-09-30) rewrote the requirements from the
device firmware findings; this draft has not been redone yet and is
superseded where it conflicts with
[docs/research/device-model.md](../research/device-model.md) (TODO.md,
"Requirements rewrite from the firmware findings").
It was written ahead of G1 (LOGBOOK 2026-09-29). It is
not put up for G2 until G1 has passed, and any change to the URs at G1 flows
into it first.

The system is `mp305-core` together with the two products built on it, the
app `mp305-app` and the Python library `mp305`. A requirement that names
neither product applies to both. Protocol facts cite sections of
[docs/research/protocol.md](../research/protocol.md) with their evidence
label. An SR that depends on a fact not yet confirmed on hardware names the
TBD that settles it.

## 1. Discovery and connection

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-001 | Bluetooth discovery shall report every peripheral whose advertised local name starts with `0000MP30`, with the identifier the OS assigns, the name without the leading `0000` (the rest kept as advertised, for example `MP305B  S             E!K`), and the signal strength in dBm. | UR-001, UR-002, UR-010 | must | T | draft | Name prefix and trimming: protocol.md 1.2, confirmed in code and on hardware. |
| SR-002 | Bluetooth discovery shall scan for 10 s by default. The scan time shall be settable from 1 s to 60 s. | UR-001, UR-027 | must | T | draft | Advertisements arrive several seconds apart (protocol.md 1.2, confirmed on hardware). |
| SR-003 | USB discovery shall report every HID device with vendor ID `0x28E9` whose product string contains `MP305B`, with its HID path and serial number string if it has one. | UR-001, UR-002, UR-010 | must | T | draft | WebLink's filter (protocol.md 1.1, confirmed in code). Product ID and serial are inferred (TBD-007, TBD-013). |
| SR-004 | The system shall connect only to the supply the caller names by identifier. The library may connect without an identifier only when discovery found exactly one supply, and shall raise an error naming the supplies found otherwise. The app shall never connect without a user selection. | UR-002, UR-010, H-002 | must | T | draft | All supplies look the same by name. |
| SR-005 | When discovery finds no supply, the app message and the library exception text shall name three possible causes: the supply is off, it is out of range or unplugged, or another app (WebLink in a browser, ISDT's Polying app) is connected to it. | UR-027 | should | T | draft | A connected peripheral stops advertising (protocol.md 1.2, inferred). |
| SR-006 | The system shall send nothing to a supply other than these requests: `0x18` (bind, Bluetooth only), `0xE0`, `0xC2` and `0xC8`. | UR-025, H-009 | must | T | draft | Settings writes (`0xC6`), language (`0xA2`), program, PD, charger and bootloader commands stay out of v1 (protocol.md 3, 4.3, 5.5). A transport-level allowlist makes this checkable. |

## 2. Authorization over Bluetooth

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-007 | After a Bluetooth connection is made, the system shall enable notifications on `AF01` and `AF02`, wait 1000 ms, write WebLink's bind frame `18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00` to `AF02`, and send nothing on `AF01` until the bind reply arrives. | UR-008 | must | T | draft | protocol.md 1.2 and 1.3: sequence confirmed in code, frame and replies confirmed on hardware. Only WebLink's frame is sent (TBD-006 stays a spike). |
| SR-008 | While waiting for the bind reply, the app shall show "Confirm the connection on the supply's screen", and the library shall log the same text through Python's `logging` module at level WARNING and call an optional callback the caller passes. | UR-008 | must | T | draft | A person must press allow on the supply (protocol.md 1.3, confirmed on hardware). A script's user needs to see why it waits. |
| SR-009 | The system shall wait for the bind reply for 60 s by default, settable from 10 s to 300 s. On timeout it shall disconnect and report a timeout. | UR-008, UR-016 | must | T | draft | Replies took 3.0 s, 3.6 s and 7.7 s with a person ready. What the supply does when nobody answers is TBD-008. |
| SR-010 | The system shall treat the connection as allowed only when the bind reply is exactly `19 00`. On any other reply it shall report "denied", send nothing more, disconnect, and not reconnect by itself. | UR-008, UR-016, H-006 | must | T | draft | `19 FF` is the deny reply (protocol.md 1.3, confirmed on hardware). There is no read-only mode after a deny (TBD-001, settled). |
| SR-011 | Over USB HID, the system shall authorize the connection as TBD-004 establishes. Until then, a USB connection counts as allowed without a bind. | UR-008 | must | T | draft | WebLink sends no bind over HID (protocol.md 1.3 lists this as not tested on hardware). |

## 3. State and readings

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-012 | After an allowed connection, the system shall read `0xE1` and one `0xC3`, and report model, application version, hardware revision, setpoints, output state, regulation mode and faults before it accepts any control request. | UR-004, UR-026 | must | T | draft | Versions and model: protocol.md 4.4, Bluetooth layout confirmed on hardware, USB layout TBD-010. |
| SR-013 | While connected, the system shall request `0xC2` continuously, sending the next request no earlier than 100 ms after the previous reply, and shall deliver at least 2 readings per second over each transport. | UR-011, UR-028 | must | T | draft | WebLink paces with 100 ms after each reply. One cycle took about 225 ms over Bluetooth (LOGBOOK 2026-09-29, confirmed on hardware). |
| SR-014 | Each reading shall carry a host timestamp taken when the reply arrived, and values converted as follows: voltages raw / 100 in V, currents raw / 1000 in A, power raw / 100 in W, energy raw / 10 in Wh, temperature in °C unchanged. | UR-003, UR-017, H-005 | must | T | draft | protocol.md 4.1. Setpoint scaling confirmed on hardware; measured voltage, current and power scaling are TBD-011. |
| SR-015 | The system shall report the regulation mode as CV for `outState` 1, CC for 2, "none" for 0, and "unknown" with the raw value for anything else. | UR-011, UR-017 | must | T | draft | 1 and 2: confirmed in code. 0 seen with output off (protocol.md 4.1, inferred meaning). |
| SR-016 | The system shall drop any reply whose length is shorter than its layout needs or whose opcode is not the reply to the request in flight, count it, and log it. It shall never turn part of a frame into a reading. | UR-017, H-005 | must | T | draft | A half-decoded frame would show wrong values. |
| SR-017 | Each connection shall have at most one request in flight. A reply is matched to its request by opcode (request + 1). | derived | must | T | draft | Protocol constraint: replies carry no sequence number, only the opcode (protocol.md 3, confirmed in code and, for `0xE0`, `0xC2`, `0xC4`, on hardware). |

## 4. Control

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-018 | Before its first control command on a connection, the system shall send `0xC8` with `remoteCon = 2` built from the latest reading and proceed only if `0xC9` returns 0. Later commands shall use `remoteCon = 1`. | UR-008, UR-023 | must | T | draft | protocol.md 4.2, confirmed in code only. Behavior on hardware is TBD-012. |
| SR-019 | The system shall build every `0xC8` from a reading that arrived after the previous `0xC9` and is at most 1 s old, reading `0xC3` first if it has none. It shall copy every field from that reading and change only the field the request names; `refresh` shall be 0. | UR-023, UR-005, H-001, H-003 | must | T | draft | `0xC8` carries the whole state (protocol.md 5.1, confirmed in code; never sent to hardware, TBD-012). SR-022 is the one exception. |
| SR-020 | The system shall set `output = 1` only in a command that carries an explicit output-on request. | UR-005, H-001 | must | T | draft | Together with SR-019 this keeps the output off unless the user asks. Depends on the `0xC8` layout, TBD-012. |
| SR-021 | The system shall reject control requests with a mode error while the latest reading reports `model` other than 0 (DC), and shall always send `model = 0`. | UR-023, H-001 | must | T | draft | Sending mode 0 while the supply runs a program or PD profile would switch modes (protocol.md 4.1, 4.2, confirmed in code; TBD-012). |
| SR-022 | An output-off request on an allowed connection in DC mode shall be sent ahead of any queued request, built from the latest reading whatever its age with only `output` set to 0 (preceded by `remoteCon = 2` if remote control was lost or never taken), and the supply's `0xC9` acknowledgment shall arrive within 0.5 s of the request. The system shall then read `0xC3` and report any setpoint that differs from what the user last saw. | UR-006, H-004 | must | T | draft | Speed beats freshness here: with the output off, a stale setpoint is harmless until the next output-on, and the report makes it visible. In other modes `0xC8` would change the mode, so the user is told to use the front panel (UR-006). Depends on TBD-012. |
| SR-023 | The system shall handle `0xC9` as follows: 0 accepted; 1 remote control not granted or lost, reported as such and all control disabled until the user requests control again; any other value rejected, reported with the value. No reply within 1 s shall be reported as a timeout, with the device state unknown until the next reading. | UR-016, H-001; user, conversation 2026-09-29 (1 s) | must | T | draft | Result codes: protocol.md 4.2, confirmed in code. The timeout is 1 s. Read replies took up to 135 ms on hardware; the `0xC8` reply time is TBD-012. |
| SR-024 | The system shall reject, before encoding, any setpoint that is not a finite number, is negative, exceeds the supply's range, or exceeds the user limit of UR-007. It shall round accepted values to the nearest 10 mV or 1 mA. | UR-007, UR-012, H-005, H-007 | must | T | draft | NaN or a negative value would otherwise wrap into a large raw `u16`. 10 mV and 1 mA are the protocol's steps (protocol.md 4.2). |
| SR-025 | The supply's setpoint range shall be 0 to 30.00 V and 0 to 5.000 A until TBD-003 settles it. | UR-012 | must | T | draft | The rated values are the safer of the two candidates. |
| SR-026 | The system shall reject an output-on request while the latest reading reports any fault. | UR-009, H-008 | must | T | draft | Refines the refusal in UR-009. Depends on `0xC8`, TBD-012. |

## 5. Faults and link loss

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-027 | The system shall decode `chargeError` bits 0 to 8 into named faults (reversed output, low battery, battery too cold, battery overheat, system overheat, over-current, over-voltage, digital IC init error, output voltage failure) and report bits 9 to 15 as "charger fault bit n". Every change in the set of active faults shall be reported with the reading that shows it. | UR-009, H-008 | must | T | draft | protocol.md 4.5, confirmed in code; only 0 seen on hardware. |
| SR-028 | The system shall declare the link lost on an OS disconnect event, a transport error, or three polls in a row without a reply within 1 s each, and shall report it within 4 s of the last reply. After that it shall send nothing and not reconnect until the user asks. | UR-024, H-004 | must | T | draft | Behavior of the supply on link loss is TBD-005. |
| SR-029 | When a library connection closes (`close()` or the end of a `with` block) on an allowed connection in DC mode, the library shall switch the output off as in SR-022, send `0xC8` with `output = 0` and `remoteCon = 0`, and then disconnect, whether or not the script ever took remote control. An error during this shall be logged and shall not hide an exception already in flight. | UR-018, UR-006, H-004 | must | T | draft | WebLink sends nothing on disconnect (protocol.md 5.2). The app's behavior is SR-030. Depends on `0xC8`, TBD-012. |
| SR-030 | When the user disconnects in the app or closes its window while the output is on, the app shall ask whether to switch the output off. Either way it shall then send `0xC8` with `remoteCon = 0` (and `output = 0` if chosen) before disconnecting. | H-004, UR-006 | should | D | draft | Some users want a DUT to stay powered after the app closes; nobody should lose that choice by accident. |

## 6. Python library

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-031 | Every library call shall block until done or timed out, release the GIL while waiting, and raise `KeyboardInterrupt` within 0.5 s of Ctrl-C. | UR-015 | must | T | draft | ADR-0007 (proposed). |
| SR-032 | The library shall raise these exceptions, all derived from `mp305.Mp305Error`: `NotFoundError`, `ConnectionDeniedError`, `SetpointRangeError` (also a `ValueError`), `CommandRejectedError`, `RemoteControlLostError`, `ModeError`, `FaultActiveError`, `Mp305TimeoutError` (also a `TimeoutError`) and `LinkLostError` (also a `ConnectionError`). | UR-016 | must | T | draft | One type per case of UR-016 plus the cases SR-021, SR-023 and SR-026 add. |
| SR-033 | A reading shall be an immutable typed object with: timestamp (float, seconds since the epoch), voltage, current, power (float, V, A, W), set_voltage, set_current (float, V, A), output_on (bool), mode (enum CV, CC, NONE, UNKNOWN), faults (frozenset of a fault enum), temperature (int, °C) and energy (float, Wh). | UR-017 | must | T | draft | Immutable readings can be shared between threads and stored in lists without copying. |
| SR-034 | The library shall offer a blocking iterator of readings at a requested rate from 0.1 to 4 per second, and a helper that writes the stream to CSV for a given duration or until interrupted. If the transport cannot keep up, the iterator shall deliver what it gets and log one warning. | UR-028 | must | T | draft | 4 per second is about what Bluetooth delivers (SR-013). A silent shortfall would corrupt a timed log. |
| SR-035 | The ramp helper shall take the quantity (voltage or current limit), start, stop, step and dwell time, check every point against SR-024 before sending the first, and stop at the first error or `KeyboardInterrupt`, leaving the output as it is. | UR-029 | could | T | draft | Checking all points first means a bad end value fails before the DUT sees any step. |
| SR-036 | The library shall ship as wheels for CPython 3.10 and later on macOS (arm64, x86_64), Linux manylinux (x86_64, aarch64) and Windows (x86_64), with a `.pyi` stub for the native module. | UR-015, UR-021 | must | I | draft | Minimum OS versions are TBD-014. |

## 7. Desktop app

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-037 | The app and the library shall write CSV files in one format: UTF-8, comma separated, `.` as decimal point, a header row with the columns `time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults`, one row per reading, flushed at least once per second. | UR-014, UR-028 | must | T | draft | One format means one parser for the user. Flushing limits a crash to losing 1 s. |
| SR-038 | The chart shall show voltage, current and power over the last 60 s by default, settable from 10 s to 10 min, and shall keep memory bounded however long the app runs. | UR-013 | must | T | draft | Logging runs can last hours; the chart must not grow without limit. |
| SR-039 | The app window shall stay responsive, with no frame taking more than 100 ms, while connecting, while waiting for the bind and while commands are pending. A new reading shall appear on screen within 100 ms of arriving. | UR-011, ADR-0005 | must | T | draft | I/O stays off the UI thread (ADR-0005). |
| SR-040 | The voltage and current fields shall send a value only when the user presses Enter or an apply button, never while typing, and shall show the supply's range and the user limits. | UR-012, UR-005, H-007 | must | D | draft | Typing "12" would otherwise send 1 V, then 12 V. |
| SR-041 | The app shall show an output-off button that is enabled whenever a supply is connected, including while other commands are pending. Output on shall be a separate button. | UR-006, UR-005 | must | D | draft | A single toggle can be pressed twice by accident. |
| SR-042 | After a link loss the app shall show a banner saying the output may still be on, disable all controls, and offer a reconnect button. | UR-024 | must | D | draft | Makes UR-024 visible in the app. |
| SR-043 | The app shall run on macOS, Linux and Windows. The macOS bundle shall declare `NSBluetoothAlwaysUsageDescription`. | UR-020 | must | I | draft | ADR-0004, ADR-0005. Minimum OS versions are TBD-014. |

## 8. Transport framing (derived)

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-044 | Over Bluetooth, the system shall write `0x12, opcode, payload` to `AF01` and `opcode, payload` to `AF02` with write-with-response, and shall accept replies as `0x31, opcode, payload` on `AF01` and `opcode, payload` on `AF02`. | derived | must | T | draft | Protocol constraint: protocol.md 1.2 and 2.1. Confirmed on hardware for requests without payload; writes with a payload (`0xC8`) are confirmed in code only (TBD-012). |
| SR-045 | Over USB HID, the system shall frame, checksum, split and reassemble reports as protocol.md 1.1 and 2.2 describe: report ID 1 out and 2 in, `0xAA` doubled and undoubled strictly in pairs, 5 ms between reports. | derived | must | T | draft | Protocol constraint. Framing and doubling are confirmed in code. Product ID and report ID 2 are read from the device firmware and used in full (protocol.md 1.1, ADR-0010). A USB connection has not been observed yet (TBD-013). WebLink's own de-doubling has a bug that must not be copied (protocol.md 1.1). |

## 8a. Unclean exit and bench safety

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| SR-046 | While a connection holds remote control and the latest reading reports the output on, the system shall keep a persistent marker in the user's state directory holding the supply identifier and a timestamp, refresh it with each reading that still shows the output on, and remove it during an orderly close (SR-029, SR-030) or when the output is switched off. On connecting to a supply whose marker is still present, the system shall warn the user, before any control action, that a previous session may have left the output on. | UR-030, H-004 | should | T | draft | The marker survives a crash because it is on disk. It is advisory, so a stale marker (for example after a power cycle of the supply) only produces a warning, never an action. |
| SR-047 | The README of the app and the library shall carry the bench-safety note of UR-031, and the app shall link to it from its connection screen. | UR-031, H-004 | should | I | draft | The note only helps if the user meets it near where they run unattended sessions. |

## 9. Open points added at this level

These continue the list in 1-user-requirements.md.

| ID | Open point | Affects | How it gets settled |
|---|---|---|---|
| TBD-010 | Layout of `0xE1` over USB HID, which WebLink parses differently from the Bluetooth reply. | SR-012 | Spike over USB |
| TBD-011 | Scaling of measured voltage, current and power, seen so far only as 0 with the output off. | SR-014 | HIL capture with the output on at 5 V, 100 mA into Load A, with the user's approval |
| TBD-012 | `0xC8` and `0xC9` on hardware: remote control request, result codes, reply time. | SR-018, SR-023 | Spike with the user's explicit approval, nothing on the output |
| TBD-013 | USB HID on hardware: product ID, report IDs, doubling, reassembly, serial number string. | SR-003, SR-045 | Spike over USB |
| TBD-014 | Minimum OS versions to support. | SR-036, SR-043 | Choose the minimum versions |

## 10. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | First draft, written ahead of G1 | not yet approved |
| 2 | 2026-09-29 | Matched UR revision 3: SR-010 disconnects after a deny, SR-022 acknowledgment within 0.5 s, SR-023 timeout 1 s. | not yet approved |
| 3 | 2026-09-29 | Independent review findings: SR-017 derived; SR-022, SR-029 and SR-030 settle output-off and closing; TBD-012 cited where `0xC8` is used; SR-044 and SR-045 evidence relabeled; rationales filled in. | not yet approved |
| 4 | 2026-09-29 | TBD-015 mitigations: SR-046 (unclean-exit marker and warning) and SR-047 (bench-safety note in the docs) added in a new section 8a. | not yet approved |
| 5 | 2026-09-29 | UR-022 dropped from the parents of SR-006, SR-007 and SR-010. | not yet approved |
| 6 | 2026-09-29 | SR-045 rationale: the product ID and report ID 2 read from the device firmware are used in full. | not yet approved |
| 7 | 2026-09-30 | Editorial: rationales state the deny rule and the 1 s timeout directly. No requirement text changed. | not yet approved |
