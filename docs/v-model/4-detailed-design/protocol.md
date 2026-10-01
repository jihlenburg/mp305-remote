# DD: protocol module of `mp305-core`

Status: approved (G4 protocol, user, 2026-09-30)

Refines AR-010, AR-011, AR-012, AR-013 and AR-014 of
[3-architecture.md](../3-architecture.md) (approved at G3). Device facts
cite [docs/research/device-model.md](../../research/device-model.md) and
[docs/research/protocol.md](../../research/protocol.md); the byte layouts
below are the ones those documents record, with their evidence labels. The
module is pure: no I/O, no time, no allocation beyond `Vec` and `String`
for frames and messages. Coverage target 95 % (ADR-0008). Revision 2
resolves the independent review of revision 1 (LOGBOOK, "Protocol design
review").

Rust module tree: `mp305_core::protocol` with the submodules `frame`,
`ble`, `hid`, `ops` (one file per opcode pair), `policy`, `units`,
`timing` and `error`, plus `fixtures` under `cfg(any(test, feature = "mock"))`
(the capture frames `C3_CAPTURE`, `E1_BLE`, `E1_USB`, `C5_SETTINGS` with
their citations, `c3_with(..)` for variants, and `reply_route(..)` and
`on_air(..)` for the route and the on-air bytes of a frame from the
supply, shared by the tests of the other modules and by the mock bridge of
`mp305-py`; added with the session DD and the py DD, test support only).
`fixtures::reply_route(kind: Kind, opcode: u8) -> Route` gives AF02 for
`0x19`, AF01 for every other Bluetooth reply and `Route::Hid` over USB;
`fixtures::on_air(kind: Kind, opcode: u8, payload: &[u8]) -> Vec<u8>`
gives `31 op payload` on AF01, `op payload` on AF02, and over USB
`AA 21 len op payload sum` with every later `AA` doubled and `sum` from
`hid::checksum`. Every source
file starts with `//! Implements: DD-PROTO-nnn, ...`. The Refines column names only the AR
items of this module; requirements and other modules' items appear in the
rationale.

## 1. Types and invariants

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-001 | `Frame { opcode: u8, payload: Vec<u8> }` is the one type the layers above see. Its fields are private; `Frame::new(opcode, payload)` is `pub(crate)` and rejects a payload longer than 254 bytes with `Reason::TooLong`. Public code obtains frames only from the builders of section 3. `opcode()` and `payload()` are public accessors. `Frame` derives `Clone`, `PartialEq`, `Eq`; `Debug` prints hex. | AR-010 | approved | The framed length is one byte (device-model.md 2.2). A crate-private constructor is what makes a short frame unbuildable outside the module (SR-052). |
| DD-PROTO-002 | `BleRoute { Af01, Af02 }` names the two characteristics; `Route { Ble(BleRoute), Hid }` is the transport-level route that `transport` reuses. `ble::encode(frame, BleRoute) -> Vec<u8>` and `ble::decode(bytes, BleRoute) -> Result<Frame>` map between `Frame` and the AF01 form (`0x12, opcode, payload` out; `0x31, opcode, payload` in) and the AF02 form (`opcode, payload` both ways). An AF01 notification that does not start with `0x31`, or an empty notification on either route, gives `Reason::BadPrefix` or `Reason::Short`. Each opcode has a fixed route: `ops::bind::ROUTE` is `Af02`, every other v1 request goes on `Af01` (`ops::route(opcode) -> BleRoute`). | AR-010 | approved | device-model.md 2.1 (code, hardware): the `0x12` is a placeholder the bridge discards, the `0x31` is a constant route tag. The captures used AF02 for `0x18` and AF01 for `0xE0`, `0xC2` and `0xC4`, so v1 keeps that pattern. |
| DD-PROTO-003 | `protocol::error` defines `Reason { Short { needed: usize, got: usize }, BadLength { expected: usize, got: usize }, TooLong, BadPrefix, BadChecksum { expected: u8, got: u8 }, BadAddress(u8), Restarted, Skipped(u64), NotAllowed(u8), WrongOpcode { expected: u8, got: u8 }, Value { field: &'static str, value: i64 } }` with `Display`. It is carried by the crate-wide `Error::Protocol(Reason)` of AR-050. A parser given fewer bytes than its layout returns `Short`; given more, `BadLength`. Parsers never return a partial value: every field is read only after the length check against the whole layout. | AR-011 | approved | SR-016. |

## 2. HID framing (`hid`)

Stream form of one frame, device-model.md 2.2 (code), protocol.md 2.2:

| Position | Byte | Meaning |
|---|---|---|
| 0 | `AA` | start of frame, never doubled |
| 1 | address | `0x12` host to device (source 1, destination 2); `0x21` in replies |
| 2 | length | number of bytes from the opcode through the last payload byte |
| 3 | opcode | |
| 4 .. 3 + length | payload | |
| last | checksum | 8-bit sum of address, length, opcode and payload |

After position 0 every byte equal to `AA` is written twice; the reader
takes `AA AA` as one `AA`. The checksum is computed over the unstuffed
bytes.

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-010 | `hid::encode(frame) -> Vec<Vec<u8>>` builds the stream with address `0x12`, computes the checksum with `hid::checksum`, doubles every `AA` after the first byte (address, length, body and checksum included), and splits the stream into report payloads of at most 62 bytes, each returned `Vec` being the `n` stream bytes of one output report. The caller prepends `01, n`. A frame always starts a new report. | AR-010 | approved | device-model.md 2.2: the byte after the report ID is the number of stream bytes, at most 62; two frames must not share a report (AR-017 moves the payloads, this item builds them). |
| DD-PROTO-011 | `hid::Decoder` is a resynchronising stream parser with the states `Idle`, `Address`, `Length`, `Body`, `Checksum` and one `aa_pending` flag that applies in every state, `Idle` included. `push(&mut self, bytes) -> Vec<Result<Frame, Reason>>` consumes the `n` stream bytes of any number of input reports. Rules, the device's own (protocol.md 2.2, firmware.md "Frame parser"): an `AA` toggles `aa_pending`; a non-`AA` byte with `aa_pending` set starts a frame with that byte as the address, in every state (a frame in progress is dropped with `Reason::Restarted`); a non-`AA` byte with `aa_pending` clear is consumed in the current state (skipped in `Idle`); an `AA` with `aa_pending` set is the data byte `AA` in the current state (skipped in `Idle`, so `AA AA 21 ...` starts nothing). The address is stored and not judged until the frame completes; length 0 gives `Reason::BadLength` at once. At the checksum: a mismatch gives `Reason::BadChecksum`; an address other than `0x21` gives `Reason::BadAddress(addr)`; otherwise `Ok(Frame)`. Every outcome returns to `Idle` with `aa_pending` clear. Bytes skipped in `Idle` are counted; the count is reported as `Err(Reason::Skipped(n))` immediately before the next result, and `skipped_total()` exposes the running sum. | AR-010 | approved | device-model.md 2.2 (code): the bridge forwards replies with address `0x21`. Following the device's parser to the letter means the host and the device agree on every stuffing edge case, and judging the address at the end keeps resynchronisation clean. |
| DD-PROTO-012 | `hid::checksum(address, length, body) -> u8` is the wrapping sum; it is the only checksum implementation, used by `encode`, by `Decoder`, and by tests that build reply streams. | AR-010 | approved | One implementation of the rule. |

## 3. Opcodes (`ops`)

Every opcode pair has a request builder returning a `Frame` and, where the
device replies, a reply parser taking a `&Frame`, checking the opcode
(`Reason::WrongOpcode` otherwise) and the exact length. Payload offset 0 is
the byte after the opcode. `ops::reply_opcode(request: u8) -> u8` is
`request + 1` for every v1 opcode (the `0x20` exception is recorded in a
comment and not needed in v1).

### 3.1 Bind `0x18` / `0x19`

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-020 | `ops::bind::request(host_id: &HostId, fast: bool) -> Frame` builds opcode `0x18` with the 18-byte payload: `host_id` (16 bytes), one `00`, then `01` if `fast` else `00`. `HostId([u8; 16])` has `new`, `as_bytes` and `from_bytes`; `new` and `from_bytes` reject the all-zero ID and WebLink's constant `00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00` with `Reason::Value { field: "host_id" }`. | AR-011 | approved | device-model.md 3, 4.1 (code): bytes 1 to 16 are the ID, the last byte of the write is the fast flag, the bytes between are ignored. The captured WebLink write is 19 bytes (`18`, 16-byte ID, `00`, flag), so with a 16-byte ID there is exactly one byte between; this payload is the hardware-confirmed one (protocol.md 1.3). SR-007, IT-011, IT-026 and ST-008 were changed to one zero byte and approved on 2026-09-30 (LOGBOOK, "Protocol design review"). The `HostId` rule is SR-049. |
| DD-PROTO-021 | `ops::bind::parse(&Frame) -> Result<BindReply>` requires opcode `0x19` and payload length 1: `00` gives `BindReply::Allowed`, `FF` gives `BindReply::Denied`, any other byte `Reason::Value { field: "bind" }`. | AR-011 | approved | device-model.md 4.1 (hardware for both values). |

### 3.2 Info `0xE0` / `0xE1`

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-022 | `ops::info::request() -> Frame` is opcode `0xE0` with an empty payload. `Version([u8; 4])` displays as `a.b.c.d`. | AR-011 | approved | protocol.md 4.4. |
| DD-PROTO-023 | `ops::info::parse(&Frame) -> Result<Info>` accepts two payload lengths. 16 bytes (Bluetooth): version at 0 (4 bytes), model at 4 (8 bytes), hardware at 12 (4 bytes). 30 bytes (USB): model at 0 (8), bootloader block at 8 (8 bytes, kept raw), version at 16 (4), name at 20 (10). Any other length gives `Short` or `BadLength` against the nearer layout. `Info { model: String, version: Version, hardware: Option<Version>, bootloader_raw: Option<[u8; 8]>, name: Option<String> }`. Model and name are ASCII up to the first NUL; a byte above `0x7E` or below `0x20` before the NUL gives `Reason::Value { field: "model" }` or `"name"`. | AR-011 | approved | device-model.md 1 (code; Bluetooth layout hardware). The USB layout has never been captured (TBD-010), so its bootloader bytes are kept raw and not interpreted. SR-012 lists what the products show. |

### 3.3 Telemetry `0xC2` / `0xC3`

Payload layout of `0xC3`, 36 bytes (protocol.md 4.1; code, with the
setpoints, output, percentage, temperature, time, energy and power
confirmed on hardware with the output off):

| Offset | Type | Field | Raw unit |
|---|---|---|---|
| 0 | u8 | outState | 0 off, 1 CV, 2 CC, 3 held above setpoint, else unknown |
| 1 | u8 | batteryState | 0 on battery, 1 external input, 2 charge held |
| 2 | u8 | percentage | % |
| 3 | u16 | voltage | 10 mV |
| 5 | u16 | setVoltage | 10 mV |
| 7 | u16 | current | 1 mA |
| 9 | u16 | setCurrent | 1 mA |
| 11 | u32 | workingTime | s |
| 15 | u32 | energy | 0.1 Wh |
| 19 | u16 | power | 10 mW |
| 21 | u8 | currentOver | 0 limit, 1 trip |
| 22 | u8 | realChange | bit 0 voltage, bit 1 current |
| 23 | u8 | voltageSlow | 0 step, 1 ramp |
| 24 | u8 | output | 0 off, 1 on |
| 25 | u8 | model | 0 DC, 1 program, 2 PD, 3 charge |
| 26 | u8 | voltageBoard | UI flag, kept raw |
| 27 | u8 | currentBoard | UI flag, kept raw |
| 28 | i8 | temperature | °C |
| 29 | u16 | chargeError | fault bits |
| 31 | u8 | wavePause | kept raw |
| 32 | u32 | waveTime | ms, kept raw |

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-024 | `ops::telemetry::request() -> Frame` is opcode `0xC2` with an empty payload. | AR-011 | approved | |
| DD-PROTO-025 | `ops::telemetry::parse(&Frame) -> Result<RawReading>` requires opcode `0xC3` and payload length 36 and reads the table above into `RawReading` with every field as its raw integer; multi-byte fields are little-endian; temperature is the byte reinterpreted as `i8`. `RawReading` keeps the raw `[u8; 36]` too. `telemetry::parse_payload(payload: &[u8]) -> Result<RawReading, Reason>` performs the length check and the field decode of `parse` without the opcode check; `parse` checks the opcode and delegates to it. | AR-011 | approved (rev 6) | SR-019: the control command copies every field of the latest reading (AR-025). |
| DD-PROTO-026 | `RegulationMode::from_raw(u8)` maps 0 `Off`, 1 `Cv`, 2 `Cc`, 3 `HeldAboveSetpoint`, other `Unknown(u8)`. `LiveMode::from_raw(u8)` maps 0 `Dc`, 1 `Program`, 2 `Pd`, 3 `Charge`, other `Unknown(u8)`. Both implement `Display`. | AR-011 | approved | device-model.md 8; SR-015. |
| DD-PROTO-027 | `Faults(u16)` decodes bits 0 to 8 to `Fault::{ReversedOutput, LowBattery, BatteryTooCold, BatteryOverheat, SystemOverheat, OverCurrent, OverVoltage, PowerStageStart, OutputVoltageSensor}` and bits 9 to 15 to `Fault::Unknown(n)`. `Faults::iter()` yields the active faults in bit order; `Faults::is_empty()`. `Fault` displays as the lower-case name with spaces, `Unknown(n)` as `unknown fault bit n`. | AR-011 | approved | device-model.md 8 (code): the bit names follow the firmware's producers; protocol.md 4.5 gives WebLink's names for the same bits (`DIC_INIT_ERROR` for bit 7). Bits 9 to 15 are never set in `0xC3`. SR-027. |
| DD-PROTO-053 | `Reading::from_raw(&RawReading) -> Reading` assembles the SI view without a timestamp (`link` adds it): `volts`, `set_volts`, `amps`, `set_amps`, `watts`, `watt_hours`, `working_time_s`, `regulation: RegulationMode`, `live_mode: LiveMode`, `output_on: bool`, `faults: Faults`, `temperature_c: i8`, `battery_percent: u8`, plus the `RawReading` it came from. | AR-013 | approved | AR-013 puts every conversion in this module so `session` does no field mapping; SR-033 lists the fields the library exposes. |

### 3.4 Control `0xC8` / `0xC9`

Payload layout of `0xC8`, 11 bytes (protocol.md 4.2, device-model.md 9;
code):

| Offset | Type | Field |
|---|---|---|
| 0 | u8 | remoteCon: 0 release, 1 active, 2 request |
| 1 | u16 | setVoltage, 10 mV |
| 3 | u16 | setCurrent, 1 mA |
| 5 | u8 | realChange |
| 6 | u8 | voltageSlow |
| 7 | u8 | currentOver |
| 8 | u8 | output |
| 9 | u8 | model |
| 10 | u8 | refresh |

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-028 | `ops::control::Command` has private fields, no `Default` and no constructor from loose values. `Command::from_reading(&RawReading) -> Result<Command>` returns `Err(Error::Mode)` unless `model` is 0, and `Err(Error::Protocol(Reason::Value))` unless `setVoltage <= 3050`, `setCurrent <= 5100`, `realChange <= 3` and `voltageSlow`, `currentOver`, `output <= 1`; otherwise it copies those six fields and sets `remoteCon = 1`, `model = 0`, `refresh = 0`. The setters `remote_con(RemoteCon)`, `set_voltage(RawVoltage)`, `set_current(RawCurrent)` and `output(bool)` change one field each. There is no setter for `model` or `refresh`. `RemoteCon { Release = 0, Active = 1, Request = 2 }`. | AR-011 | approved | H-001, H-003, SR-019, SR-020, SR-021 (AR-025): a `0xC8` carries the whole state and the device applies fields in order until the first bad one; the type makes a command from stale or default values, a mode change, or a flag outside the device's bounds unbuildable. The 3050 and 5100 bounds are the device's own (device-model.md 9), so a value the device reported is always accepted for copying. |
| DD-PROTO-029 | `Command::encode(&self) -> Frame` is opcode `0xC8` with the 11-byte payload above, little-endian. The setters take `RawVoltage` and `RawCurrent`, which only `units` constructs within the supply range and the user limits; the copied fields are bounded by `from_reading`. | AR-011, AR-013 | approved | SR-024, SR-025. |
| DD-PROTO-030 | `ops::control::parse(&Frame) -> Result<ControlReply>` requires opcode `0xC9` and payload length 1: 0 `Accepted`, 1 `NotGranted`, `0xFF` `Rejected`, other `Other(u8)`. | AR-011 | approved | device-model.md 9 (code); SR-023. |

### 3.5 Settings `0xC5` and event frames

Payload layout of `0xC5`, 11 bytes (protocol.md 4.3; code, layout hardware):

| Offset | Type | Field |
|---|---|---|
| 0 | u8 | chargeLimit, % |
| 1 | u8 | volume |
| 2 | u8 | screenOff |
| 3 | u8 | shutdown, min |
| 4 | u8 | screenDirection |
| 5 | u16 | rampStep, mV per 100 ms |
| 7 | u16 | ocpDelay, ms |
| 9 | u16 | usbLineDrop |

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-031 | `ops::settings::parse(&Frame) -> Result<Settings>` requires opcode `0xC5` and payload length 11 and reads the table above. There is no builder for `0xC4` or `0xC6` in v1. | AR-011 | approved | device-model.md 10: the device sends `0xC5` on its own when a setting changes on the front panel (UR-034). |
| DD-PROTO-032 | `ops::events::classify(&Frame) -> Result<Option<DeviceFrame>>` maps `0xC5` to `Settings(Settings)` (propagating the parse error), `0xDD` to `SelectedProgram(payload)`, `0xE5` to `ActivePdProfile(payload)`, `0xEB` to `ChargeSettings(payload)`, `0xDB` to `ProgramStepsSaved(payload)`, and every other opcode to `Ok(None)`. The payloads of the four opaque events are kept as bytes. | AR-011 | approved | device-model.md 6: these arrive unsolicited; v1 reports them without interpreting them (AR-020). A malformed `0xC5` is an error the caller counts and logs (SR-016), not a silent `None`. |

## 4. Policy (`policy`)

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-040 | `policy::check(&Frame) -> Result<()>` accepts exactly opcode `0x18` with payload length 18, `0xE0` with 0, `0xC2` with 0 and `0xC8` with 11, and returns `Reason::NotAllowed(opcode)` for any other opcode and `Reason::BadLength` for a wrong length. `policy::ALLOWED` lists the four opcodes with their lengths. | AR-012 | approved | SR-006, SR-052: `Guarded` (AR-015) calls this on every frame, so neither a foreign opcode nor a short or long frame can reach a transport. |
| DD-PROTO-041 | `policy::NEVER: &[(u8, &str)]` lists every opcode from `0xF0` to `0xFE` (even values "maintenance and update", odd values "maintenance reply opcode", `0xFE` "factory reset with reboot"), `0x20` "block write", `0x10` and `0xC0` "rewrite the Bluetooth chip's advertising data", and `0xBE` "accessory input, reaches the front-panel input path". `policy::never_reason(opcode) -> Option<&str>`. The list is documentation the tests check; `check` refuses these opcodes like any other. | AR-012 | approved | device-model.md 11 (code); UR-033. |

## 5. Units (`units`)

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-050 | Conversions, one function each, on the raw integer types: `volts(raw: u16) -> f64 = raw / 100`, `amps(raw: u16) -> f64 = raw / 1000`, `watts(raw: u16) -> f64 = raw / 100`, `watt_hours(raw: u32) -> f64 = raw / 10`, `seconds(raw: u32) -> u32`, `celsius(raw: i8) -> i8`. | AR-013 | approved | protocol.md 4.1 (setpoints hardware; measured values code, TBD-011); SR-014. |
| DD-PROTO-051 | `RawVoltage::from_volts(v: f64, limits: &Limits) -> Result<RawVoltage>` and `RawCurrent::from_amps(a: f64, limits: &Limits)`: reject a value that is not finite or is negative with `Error::SetpointRange { field, value, min, max }` (`min` 0 here; displayed as `<field> <value> is outside <min> to <max>`); scale by 100 (volts) or 1000 (amps), round the scaled value to six decimals first and then to the nearest integer, halves away from zero (`((x * 1e6).round() / 1e6).round()`); reject a raw value above `SUPPLY_MAX_RAW_VOLTAGE` or `SUPPLY_MAX_RAW_CURRENT`, or above the user limit in `Limits { max_volts: Option<f64>, max_amps: Option<f64> }` converted through the same path, with `Error::SetpointRange`. | AR-013 | approved (rev 5) | H-005, H-007, SR-024, SR-025, UR-007. The pre-rounding removes binary-float artefacts such as `1.005 * 100 = 100.49999999999999`, so 1.005 V rounds to raw 101 as the requirements expect. |
| DD-PROTO-052 | `pub const SUPPLY_MAX_RAW_VOLTAGE: u16 = 3000` and `SUPPLY_MAX_RAW_CURRENT: u16 = 5000` (0 to 30.00 V, 0 to 5.000 A); the firmware's own ceiling (3050, 5100) is recorded in a comment and not used until TBD-003 settles. `Limits::none()` has no user limits. | AR-013 | approved | device-model.md 9; SR-025. |

## 6. Timing (`timing`)

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-060 | `timing` defines `pub const` `Duration`s with a source comment each: `BIND: 30 s`, `REMOTE_PROMPT: 70 s`, `REPLY: 1 s`, `OUTPUT_OFF_ACK: 500 ms`, `POLL_PAUSE: 100 ms`, `USB_KEEPALIVE: 2 s`, `LINK_LOSS_REPORT: 4 s`, `RECONNECT_RETRY: 5 s`, `RECONNECT_GIVE_UP: 10 min`, `SETTLE: 100 ms`, `SCAN_DEFAULT: 10 s`, `SCAN_MIN: 1 s`, `SCAN_MAX: 60 s`, `FIND: 4 s`, `CONNECT: 10 s`, `WAIT_SLICE: 100 ms` (source comment "AR-003, the Python wait slice"). No other module in `mp305-core` or `mp305-py` writes these numbers (checked by IT-014). | AR-014 | approved (rev 6) | device-model.md 12. |

## 7. Documentation

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-PROTO-070 | Every public item has rustdoc with units. The byte tables of sections 2 and 3 appear in the rustdoc of `hid::Decoder`, `ops::telemetry::RawReading`, `ops::control::Command`, `ops::info::Info` and `ops::settings::Settings`, each with a link to protocol.md. Doctests use a `Frame` built in the example and no transport; `Command` has a `compile_fail` doctest showing that its fields cannot be written. | AR-010, AR-011 | approved | AGENTS.md, documentation standards. |

## 8. Unit test specification

Tests live in `crates/mp305-core/src/protocol/**` under `#[cfg(test)]` and
in `crates/mp305-core/tests/ut_protocol_*.rs`. Each test names its UT ID
(`/// Test: UT-PROTO-nnn`). Fixture frames are inline bytes with the capture
file name and event timestamp in a comment; there is no copy of the
captures under `crates/`. Property tests use `proptest` with a fixed seed
in CI. Reply streams for the HID decoder are built in the test from the
capture payload with `hid::checksum` and address `0x21`, since no HID
capture exists yet (TBD-013). The capture reading used below is the first
`0xC3` of `2026-09-29T193614-ble-readonly.jsonl`: outState 0, batteryState
0, percentage 90, voltage 0, setVoltage 1300, current 0, setCurrent 1000,
workingTime 1, energy 0, power 0, currentOver 0, realChange 3, voltageSlow
0, output 0, model 0, voltageBoard 0, currentBoard 1, temperature 26,
chargeError 0, wavePause 1, waveTime 1600.

| UT | Verifies | Input | Expected result | Test |
|---|---|---|---|---|
| UT-PROTO-001 | DD-PROTO-001 | `Frame::new` with payloads of 0, 254 and 255 bytes; `Debug` of `Frame(0xC4, [])`. | 0 and 254 accepted; 255 gives `Reason::TooLong`; `Debug` prints `c4`. | `crates/mp305-core/src/protocol/frame.rs` |
| UT-PROTO-002 | DD-PROTO-002 | `ble::encode` of `Frame(0xC4, [])` on `Af01` and of `Frame(0xE0, [])` on `Af02`; `ble::decode` of `31 c5 5a 02 00 00 01 f4 01 32 00 00 00` on `Af01` (capture `193614`) and of `19 00` on `Af02` (capture `193614`); decode of `c5 ...` without the `0x31` on `Af01`, and of an empty slice on both routes; `ops::route` for `0x18`, `0xE0`, `0xC2`, `0xC8`. | `12 c4`, `e0`; `Frame(0xC5, 11 bytes)`, `Frame(0x19, [00])`; `BadPrefix`; `Short` twice; `Af02`, `Af01`, `Af01`, `Af01`. | `crates/mp305-core/src/protocol/ble.rs` |
| UT-PROTO-003 | DD-PROTO-002 | Property: any `Frame` round-trips through `ble::encode` then `ble::decode` on both routes (with the `0x12` replaced by `0x31` for `Af01` as the bridge does). | Identity. | `crates/mp305-core/src/protocol/props.rs` |
| UT-PROTO-004 | DD-PROTO-003 | Every parser of section 3 given a payload one byte shorter and one byte longer than its layout; `Display` of each `Reason` variant. | Shorter gives `Short { needed, got }` with the layout's length; longer gives `BadLength { expected, got }`; no partial value is observable (the functions return `Result`). Each `Display` names the variant and its fields. | `crates/mp305-core/src/protocol/error.rs` |
| UT-PROTO-010 | DD-PROTO-010, DD-PROTO-012 | `hid::encode` of `Frame(0xC4, [])`; of the `0xC8` command built from the capture reading with `set_voltage(RawVoltage(170))`; of `Frame(0x97, [])`. | `[AA 12 01 C4 D7]`; `[AA 12 0C C8 01 AA AA 00 E8 03 03 00 00 00 00 00 7F]` (checksum `7F` over the unstuffed bytes); `[AA 12 01 97 AA AA]` (a checksum of `AA` is doubled). | `crates/mp305-core/src/protocol/hid.rs` |
| UT-PROTO-011 | DD-PROTO-010 | `hid::encode` of a frame whose stream is 63 bytes and one whose stream is 124 bytes. | Report payloads of 62 and 1 bytes; 62 and 62 bytes. Each payload at most 62. | `crates/mp305-core/src/protocol/hid.rs` |
| UT-PROTO-012 | DD-PROTO-011 | `Decoder::push` with the stream `AA 21 25 C3 <36 capture bytes> <checksum>` built with `hid::checksum`, split at every boundary from 1 to 41 bytes per push. | Exactly one `Ok(Frame(0xC3, payload))` in total, identical for every split, and no error. | `crates/mp305-core/src/protocol/hid.rs` |
| UT-PROTO-013 | DD-PROTO-011 | Streams: the UT-012 stream with its checksum byte changed to `00`; `AA 21 00 21`; the UT-012 stream with address `12` (checksum recomputed); `AA 21 25 C3 <10 bytes> AA 21 01 C4 E6` (a lone `AA` restarts); `01 02 03 04 05 06 07` then the UT-012 stream; `AA AA 21 ...` (doubled `AA` outside a frame); a frame whose last payload byte is `AA` and one whose checksum is `AA`, both doubled. | `BadChecksum { expected: <sum>, got: 0 }`; `BadLength`; `BadAddress(0x12)` and no frame; `Restarted` then `Ok(Frame(0xC4, []))`; `Skipped(7)` then `Ok`; nothing (skipped) until a lone `AA` follows; both decode to one `AA`. | `crates/mp305-core/src/protocol/hid.rs` |
| UT-PROTO-014 | DD-PROTO-010, DD-PROTO-011, DD-PROTO-012 | Property: any `Frame` encoded with `hid::encode`, its stream rebuilt with address `0x21` and `hid::checksum`, pushed in random splits. | Decodes to the same `Frame` once with no error. | `crates/mp305-core/src/protocol/props.rs` |
| UT-PROTO-020 | DD-PROTO-020 | `bind::request` with `HostId::new([0xA0..=0xAF])` and `fast` true and false; `HostId::new` with all zero and with WebLink's constant; `from_bytes(as_bytes())`. | Opcode `0x18`, payload 18 bytes: `A0 .. AF 00 01` and `A0 .. AF 00 00`; the two IDs are rejected with `Reason::Value { field: "host_id" }`; round trip identity. | `crates/mp305-core/src/protocol/ops/bind.rs` |
| UT-PROTO-021 | DD-PROTO-021 | `bind::parse` of `19 00` (capture `193614`), `19 ff` (capture `194319`), `19 01`, `18 00`. | `Allowed`, `Denied`, `Value { field: "bind" }`, `WrongOpcode { expected: 0x19, got: 0x18 }`. | `crates/mp305-core/src/protocol/ops/bind.rs` |
| UT-PROTO-022 | DD-PROTO-022, DD-PROTO-023 | `info::request`; `info::parse` of the capture `e1 01 06 00 28 4d 50 33 30 35 42 00 00 02 00 02 00` (`193614`), of a constructed 30-byte USB layout with model `MP305B`, bootloader bytes `01..08`, version `01 06 00 33`, name `MP305B` padded; of 15, 17 and 29-byte payloads; of a 16-byte payload with `0xFF` in the model. `Version([1,6,0,40])` display. | `Frame(0xE0, [])`; version 1.6.0.40, model `MP305B`, hardware 2.0.2.0, no bootloader bytes, no name; USB: model, version 1.6.0.51, the 8 raw bytes, name `MP305B`, no hardware; `Short { 16, 15 }`, `BadLength { 16, 17 }`, `Short { 30, 29 }`; `Value { field: "model" }`; `1.6.0.40`. | `crates/mp305-core/src/protocol/ops/info.rs` |
| UT-PROTO-024 | DD-PROTO-024, DD-PROTO-025 | `telemetry::request`; `telemetry::parse` of the capture `0xC3` payload, of the same with `FA` at offset 28, of 35 and 37-byte payloads; `telemetry::parse_payload` of the 36 capture payload bytes, of 35 and of 37 bytes. | `Frame(0xC2, [])`; every field equal to the capture values listed above, raw bytes kept; temperature -6 for the `FA` case; `Short { 36, 35 }`, `BadLength { 36, 37 }`; the same `RawReading` as `parse` gives, `Short { 36, 35 }`, `BadLength { 36, 37 }`. | `crates/mp305-core/src/protocol/ops/telemetry.rs` |
| UT-PROTO-025 | DD-PROTO-026 | `RegulationMode::from_raw` for 0 to 4 and `Display` of each; `LiveMode::from_raw` for 0 to 4 and `Display`. | Off, Cv, Cc, HeldAboveSetpoint, Unknown(4); Dc, Program, Pd, Charge, Unknown(4); each displays its name, `Unknown(4)` as `unknown (4)`. | `crates/mp305-core/src/protocol/ops/telemetry.rs` |
| UT-PROTO-026 | DD-PROTO-027 | `Faults(0)`, `Faults(0b1_0010_0001)`, `Faults(0xFE00)`; `Display` of `OverCurrent` and `Unknown(11)`. | empty; ReversedOutput, OverCurrent, OutputVoltageSensor in that order; Unknown(9) to Unknown(15); `over current`, `unknown fault bit 11`. | `crates/mp305-core/src/protocol/ops/telemetry.rs` |
| UT-PROTO-027 | DD-PROTO-028, DD-PROTO-029 | `Command::from_reading` of the capture reading, then `set_voltage(RawVoltage(170))`, `encode`; `from_reading` then `output(true)`; `from_reading` then `set_current(RawCurrent(5000))`; `from_reading` then `remote_con(Request)`; `from_reading` alone; `from_reading` of the capture reading with `model` 2; with `realChange` 4; with `setVoltage` 3051. | Payloads `01 AA 00 E8 03 03 00 00 00 00 00`; `01 14 05 E8 03 03 00 00 01 00 00`; `01 14 05 88 13 03 00 00 00 00 00`; `02 14 05 E8 03 03 00 00 00 00 00`; `01 14 05 E8 03 03 00 00 00 00 00`; `Error::Mode`; `Reason::Value { field: "realChange" }`; `Reason::Value { field: "setVoltage" }`. | `crates/mp305-core/src/protocol/ops/control.rs` |
| UT-PROTO-028 | DD-PROTO-030 | `control::parse` of `c9 00`, `c9 01`, `c9 ff`, `c9 07`, `c9`. | Accepted, NotGranted, Rejected, Other(7), `Short { 1, 0 }`. | `crates/mp305-core/src/protocol/ops/control.rs` |
| UT-PROTO-029 | DD-PROTO-028 | `compile_fail` doctests: `Command { .. }` literal; `cmd.model = 1`; `Command::default()`. | None of the three compiles. | `crates/mp305-core/src/protocol/ops/control.rs` (doctests) |
| UT-PROTO-030 | DD-PROTO-031 | `settings::parse` of `c5 5a 02 00 00 01 f4 01 32 00 00 00` (capture `193614`) and of a 10-byte payload. | chargeLimit 90, volume 2, screenOff 0, shutdown 0, screenDirection 1, rampStep 500, ocpDelay 50, usbLineDrop 0; `Short { 11, 10 }`. | `crates/mp305-core/src/protocol/ops/settings.rs` |
| UT-PROTO-031 | DD-PROTO-032 | `events::classify` of frames with opcodes `0xC5` (capture payload), `0xC5` with 10 bytes, `0xDD`, `0xE5`, `0xEB`, `0xDB`, `0xC3`, `0x00`. | `Ok(Some(Settings(..)))`, `Err(Short)`, the four opaque variants with their payloads, `Ok(None)`, `Ok(None)`. | `crates/mp305-core/src/protocol/ops/events.rs` |
| UT-PROTO-032 | DD-PROTO-053 | `Reading::from_raw` of the capture reading. | volts 0.0, set_volts 13.0, amps 0.0, set_amps 1.0, watts 0.0, watt_hours 0.0, working_time_s 1, Off, Dc, output_on false, no faults, 26 °C, 90 %. | `crates/mp305-core/src/protocol/ops/telemetry.rs` |
| UT-PROTO-033 | DD-PROTO-002 | `reply_opcode` for `0x18`, `0xE0`, `0xC2`, `0xC8`. | `0x19`, `0xE1`, `0xC3`, `0xC9`. | `crates/mp305-core/src/protocol/ops/mod.rs` |
| UT-PROTO-040 | DD-PROTO-040, DD-PROTO-041 | `policy::check` for `Frame::new(op, [])` with every opcode 0 to 255; for `0x18` with 17, 18 and 19 bytes; for `0xC8` with 10, 11 and 12 bytes; `never_reason` for each listed opcode and for `0xC2`. | Only `0xE0` and `0xC2` pass the empty-payload sweep; `0x18` passes only with 18, `0xC8` only with 11, the others `BadLength`; every other opcode `NotAllowed`; each listed opcode has a non-empty reason, `0xC2` has none. | `crates/mp305-core/src/protocol/policy.rs` |
| UT-PROTO-050 | DD-PROTO-050 | `volts(1300)`, `amps(1000)`, `watts(25)`, `watt_hours(123)`, `seconds(3600)`, `celsius(-6)`. | 13.0, 1.0, 0.25, 12.3, 3600, -6. | `crates/mp305-core/src/protocol/units.rs` |
| UT-PROTO-051 | DD-PROTO-051, DD-PROTO-052 | `RawVoltage::from_volts` with NaN, infinity, -0.01, 30.004, 30.005, 1.004, 1.005, 1.006, and 4.5 with `max_volts` 4.0; `RawCurrent::from_amps` with 1.0004, 1.0005, 5.0004, 5.0005, and 0.06 with `max_amps` 0.05; the two constants. | `SetpointRange` for NaN, infinity, -0.01; 3000; `SetpointRange`; 100, 101, 101; `SetpointRange` with `max` 4.0; 1000, 1001, 5000, `SetpointRange`, `SetpointRange`; 3000 and 5000. | `crates/mp305-core/src/protocol/units.rs` |
| UT-PROTO-060 | DD-PROTO-060 | Read every constant. | The nine values of DD-PROTO-060. | `crates/mp305-core/src/protocol/timing.rs` |
| UT-PROTO-070 | DD-PROTO-070 | `cargo doc -p mp305-core` under `deny(missing_docs)`; inspect the rustdoc of the five types for the byte tables and links; run the doctests. | Builds without warnings; tables and links present; doctests pass, including the `compile_fail` ones. | inspection plus `cargo test --doc -p mp305-core`, record `unit-protocol` |

## 9. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-30 | First draft for G4 of the protocol module | not yet approved |
| 2 | 2026-09-30 | Independent review resolved: bind payload 18 bytes as captured (SR-007, IT-011, IT-026 and ST-008 changed); `NEVER` covers `0xF0` to `0xFE`; the HID decoder follows the device's parser in every state and judges the address at the end; `policy::check` takes the frame and checks the length; `Frame::new` is crate-private; `from_reading` bounds the copied fields and refuses a non-DC reading; `SetpointRange` for rejected setpoints with the pre-rounding rule; `Reading::from_raw`, `reply_opcode`, `route`, `HostId` bytes, `Version`, the supply constants and `Skipped` added; `classify` returns a `Result`; Refines restricted to this module's AR items; Status column; documentation as DD-PROTO-070; UT table with concrete bytes and paths. | user, 2026-09-30 (G4 protocol) |
| 3 | 2026-09-30 | Editorial: the property tests (UT-PROTO-003, UT-PROTO-014) live in `crates/mp305-core/src/protocol/props.rs`, not under `tests/`, because `Frame::new` is crate-private by design. Test paths only; no design statement, expected result or ID changed. | editorial, no approval needed |
| 4 | 2026-10-01 | Editorial: the `fixtures` module (test support under the `mock` feature) named in the module tree, from the session DD (session.md section 9, decision 2). No design statement, expected result or ID changed. | editorial, no approval needed |
| 5 | 2026-10-01 | DD-PROTO-051 marked changed from the discovery DD review (discovery.md section 5, decision 2): `Error::SetpointRange` gains `min`, the existing callers pass 0 and their texts do not change; UT-PROTO-004's literal gains the field. Approved with G4 discovery. | user, 2026-10-01 (G4 discovery) |
| 6 | 2026-10-01 | From the py DD (py.md section 8, decisions 8, 9 and 10): `fixtures::reply_route` and `fixtures::on_air` (test support) in the module tree; `telemetry::parse_payload` (DD-PROTO-025, UT-PROTO-024); `WAIT_SLICE` and `mp305-py` in DD-PROTO-060, whose list now also names the six constants that AR-014 revisions 6 and 7 added and the code already defines. Approved with G4 py. | user, 2026-10-01 (G4 py) |
