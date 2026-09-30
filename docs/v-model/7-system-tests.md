# 7. System test specification (ST)

Status: draft

System tests verify the system requirements in
[2-system-requirements.md](2-system-requirements.md). Like that document,
this draft was written ahead of G1 and is not put up for G2 until G1 has
passed.

Automated system tests are pytest tests in `tests/system/`. They drive the
system through the installed Python library, carry `@pytest.mark.spec("ST-nnn")`
and, when they use a supply, `@pytest.mark.hil`. They run only when the user
sets `MP305_HIL=1` and `MP305_HIL_DEVICE` in the current session (AGENTS.md,
"Hardware-in-the-loop tests"). App behavior is tested by manual procedures.

## 1. Test conditions

The HIL safety rules of AGENTS.md apply: nothing on the output unless the
test names a load, 5 V and 100 mA or less, output off and settings restored
in teardown, also on failure. "Load A" is the 100 Ω resistor of
8-acceptance-tests.md, with 1 % tolerance. "Load B" is its 22 Ω resistor. It is
used only in ST-026 and ST-027, where about 230 mA must flow briefly to make
the supply trip at a 100 mA limit.

Tests marked "person" need someone at the supply to press allow or deny.

## 2. Coverage

Codes as in 8-acceptance-tests.md: HW (the user's MP305B on this OS and
transport), CI (no hardware for this OS, TBD-009), n/a, and A (analysis, inspection or a test without a
supply, OS and transport independent). "BLE" and "USB" stand for the transports.

| ST | macOS BLE | macOS USB | Linux BLE | Linux USB | Windows BLE | Windows USB |
|---|---|---|---|---|---|---|
| ST-001, ST-002, ST-005, ST-007 to ST-010, ST-039 | HW | n/a | CI | n/a | CI | n/a |
| ST-003, ST-011, ST-040 | n/a | HW | n/a | CI | n/a | CI |
| ST-004, ST-006, ST-012 to ST-015, ST-018 to ST-024, ST-026 to ST-031, ST-033 to ST-036, ST-038, ST-041 | HW | HW | CI | CI | CI | CI |
| ST-016, ST-017, ST-025, ST-032, ST-037, ST-042 | A | A | A | A | A | A |

## 3. Test specifications

| ST | Verifies | Procedure | Expected result | Method |
|---|---|---|---|---|
| ST-001 | SR-001 | Discover over Bluetooth with the supply on. | The supply appears with an OS identifier, a name that starts with `MP305B` (the `0000` prefix removed, the rest as advertised) and an RSSI in dBm. | automated, HIL (`tests/system/test_discovery.py`) |
| ST-002 | SR-002 | 1. Discover with the default scan time and time it. 2. Discover with 1 s and with 60 s. 3. Pass 0.5 s and 61 s. | Default about 10 s; 1 s and 60 s honored within 0.5 s; out-of-range values raise `ValueError`. | automated, HIL |
| ST-003 | SR-003 | Discover over USB with the supply plugged in. | The supply appears with its HID path and, if present, its serial string. The result is recorded for TBD-007 and TBD-013. | automated, HIL |
| ST-004 | SR-004 | 1. Connect by the identifier from discovery. 2. With the library, connect without an identifier while a second supply, or a simulated second discovery result through the mock transport, is present. | 1 connects to that supply. 2 raises an error that lists both supplies. | automated, HIL plus mock |
| ST-005 | SR-005 | Connect WebLink in Chrome to the supply, then discover with the library. | `NotFoundError` whose text names the three causes. | manual, HIL (needs Chrome) |
| ST-006 | SR-006 | Run a full session (connect, read, set 5 V and 0.1 A, output on and off, close) with the transport's frame log on. | The log contains only `0x18`, `0xE0`, `0xC2` and `0xC8` requests. | automated, HIL |
| ST-007 | SR-010 | Connect over Bluetooth; the person presses deny. Then call `set_voltage(1.0)`. | `ConnectionDeniedError` at connect; the link is closed, and the call raises because there is no connection. The frame log shows one bind frame and nothing after the `19 FF`. | automated, HIL, person |
| ST-008 | SR-007 | Connect over Bluetooth with the frame log on; the person presses allow. | The log shows notifications enabled on both characteristics, then about 1000 ms, then the exact bind frame on `AF02`, and no `AF01` write before the `19 00` reply. | automated, HIL, person |
| ST-009 | SR-008 | Connect with a callback and a log handler; the person waits 5 s, then presses allow. | The callback ran and the WARNING record with the confirmation text was logged before the reply. | automated, HIL, person |
| ST-010 | SR-009 | Connect with a 10 s bind timeout; the person does not press anything. | `Mp305TimeoutError` after 10 s (within 1 s); the link is closed. (TBD-008 needs a separate spike, since the link is closed before any late reply.) | automated, HIL, person |
| ST-011 | SR-011 | Connect over USB and watch the supply's screen. | The result follows TBD-004. Until it settles: the connection is allowed without a bind, and the record says whether the supply showed a prompt. | automated, HIL, person |
| ST-012 | SR-012 | Connect; compare the reported model and versions with WebLink or the supply's information screen, and the setpoints with the screen. Call a control method before the first reading (via a hook that delays polling). | Values match. The early control call waits for or refuses until the first reading. | automated, HIL |
| ST-013 | SR-013 | Stream readings for 60 s over each transport, output off. | At least 120 readings. No request followed its previous reply by less than 100 ms (frame log). | automated, HIL |
| ST-014 | SR-014 | 1. Set 5.00 V, 0.100 A on the front panel. 2. With Load A, output on, read 10 readings. | Setpoints read 5.0 V and 0.1 A. Measured voltage about 5.0 V, current about 0.05 A (Load A, 1 %), power about 0.25 W, each within 5 %. Timestamps rise. Result recorded for TBD-011. | automated, HIL |
| ST-015 | SR-015 | Read with output off; then with Load A and output on at 5 V, 0.1 A with CC (not OCP) selected on the front panel (CV expected); then with Load A at 5 V, 0.02 A (CC expected). | Modes "none", CV, CC. | automated, HIL |
| ST-016 | SR-016 | Analysis: frames too short or with a wrong opcode cannot be produced by a real supply on demand. | Covered by unit and integration tests named at G3 and G4. This entry records the reason. | analysis |
| ST-017 | SR-017 | Analysis: in-flight limits and reply matching are internal. | Covered by integration tests named at G3. The frame log of ST-013 shows no overlapping requests. | analysis plus log check |
| ST-018 | SR-018 | Connect, then set 1.00 V with the frame log on. | The first `0xC8` has `remoteCon = 2` and `0xC9` 0, then the setpoint command has `remoteCon = 1`. Result recorded for TBD-012. | automated, HIL |
| ST-019 | SR-019 | 1. Connect, 3 V, 0.05 A, output off. 2. On the front panel change to 4 V. 3. Within 2 s, set 0.08 A from the library. | The `0xC8` carries 4.00 V, 0.080 A, output 0, and every other field as in the last `0xC3`. | automated, HIL, person |
| ST-020 | SR-020 | Change voltage, current and read state 20 times with the output off. | No `0xC8` in the log has `output = 1`. The output stays off. | automated, HIL |
| ST-021 | SR-021 | Put the supply in program or PD mode on the front panel, output off, then connect and call `set_voltage(1.0)`. | `ModeError`; no `0xC8` sent. Restore DC mode. | automated, HIL, person |
| ST-022 | SR-022 | 1. Load A, 5 V, 0.1 A, output on. 2. Queue five voltage changes (1.0, 1.5, 2.0, 2.5, 3.0 V, current limit unchanged at 0.1 A) and one `output_off()` at once. 3. Time from the call to the `0xC9` acknowledgment, and to the first reading with output 0. | Output-off is sent first. Acknowledged within 0.5 s. The reading shows output 0 and voltage under 0.5 V. | automated, HIL |
| ST-023 | SR-023 | 1. Normal command. 2. Take remote control away on the front panel if the supply allows it (TBD-012), then send a command. 3. Mock transport: no reply, and a reply of 7. | 1 accepted. 2 `RemoteControlLostError`. 3 `Mp305TimeoutError` after 1 s and `CommandRejectedError` naming 7. | automated, HIL plus mock |
| ST-024 | SR-024 | Call `set_voltage` with NaN, infinity, -0.01, 30.01 and a value above a user limit; then 1.004 and 1.006. | The first five raise `SetpointRangeError` and send nothing. The last two send 1.00 V and 1.01 V. | automated, HIL (sending part at 5 V or less) |
| ST-025 | SR-025 | Read the range the library reports; call `set_current_limit(5.001)`. | 0 to 30.00 V, 0 to 5.000 A; the call raises `SetpointRangeError`. | automated, no supply needed |
| ST-026 | SR-026 | Trip OCP as in AT-009, then call `output_on()`. | `FaultActiveError`; no `0xC8` with `output = 1` sent. Restore CC mode. | automated, HIL, person |
| ST-027 | SR-027 | Trip OCP as in AT-009 while streaming. | The first reading after the trip lists the over-current fault; the fault set change is reported once. | automated, HIL, person |
| ST-028 | SR-028 | 1. Streaming, output off. 2. Switch the supply off. 3. Repeat by switching off Bluetooth on the host, and by pulling the USB cable. | `LinkLostError` within 4 s of the last reply. No frames sent afterwards and no reconnect. | automated, HIL, person |
| ST-029 | SR-029 | 1. `with` block that switches the output on with no load, then raises. 2. Same with a normal end. | Frame log ends with `0xC8` `output = 0`, `remoteCon = 0`. The original exception reaches the caller in case 1. | automated, HIL |
| ST-030 | SR-030 | Close the app window with the output on (no load), once choosing "switch off" and once "leave on". After the "leave on" run, switch the output off on the front panel. | The app asks. The output follows the choice. | manual, HIL |
| ST-031 | SR-031 | 1. Start a connect and press Ctrl-C during the bind wait. 2. Run a Python thread that counts while a library call blocks. | 1 `KeyboardInterrupt` within 0.5 s. 2 The counter advances during the call. | automated, HIL, person (step 1 in a subprocess) |
| ST-032 | SR-032 | Inspect the exception classes. | All listed classes exist with the stated bases. The HIL tests raise most of them; `CommandRejectedError` is raised only through the mock in ST-023, and `RemoteControlLostError` only if TBD-012 finds a way to cause it. | analysis plus inspection |
| ST-033 | SR-033 | Read a reading and inspect it; try to change a field. | Types and units as listed; assigning raises an error. | automated, HIL |
| ST-034 | SR-034 | 1. Stream at 0.1, 2 and 4 per second for 30 s each. 2. Write 30 s to CSV. 3. Ask for 4.1 per second. 4. With the mock transport slowed to 1 reply per second, ask for 4 per second. | Counts within 10 % of the rate. The CSV follows SR-037. Step 3 raises `ValueError`. Step 4 yields about 1 reading per second and one warning. | automated, HIL |
| ST-035 | SR-035 | 1. Ramp 1 to 5 V, step 1 V, 1 s dwell, no load. 2. Ramp with an end value above the user limit. | 1 setpoints 1, 2, 3, 4, 5 V, about 1 s apart. 2 `SetpointRangeError` before anything is sent. | automated, HIL |
| ST-036 | SR-036, SR-043 | Install the wheel on each OS in the coverage table and import `mp305`; start the app there. Inspect the macOS bundle's Info.plist. | Import works; stub present; app starts; Info.plist has the key. | inspection plus manual |
| ST-037 | SR-037 | Analysis plus check: parse a file from ST-034 and one from the app. | Both have the same header and format. | automated (`tests/system/test_csv_format.py`), with files from HIL runs |
| ST-038 | SR-038, SR-039, SR-040, SR-041, SR-042 | Manual app session: 1. Chart range 10 s and 10 min. 2. Watch memory for 30 min at 60 s range. 3. During the bind wait, move and resize the window, with the app's frame-time log on. 4. Set a user voltage limit of 5 V, then type "4.5" slowly into the voltage field without Enter. 5. Output-off while a command is pending. 6. Break the link. | 1 Ranges honored. 2 Memory stays flat within 10 %. 3 No frame over 100 ms in the log, and readings appear within 100 ms of arriving (log timestamps). 4 Nothing sent until Enter; then 4.5 V is sent once (frame log). 5 Output-off works. 6 Banner, controls off, reconnect button. | manual, HIL |
| ST-039 | SR-044 | Frame log of ST-008 and ST-013. | Requests and replies have the stated shape on each characteristic. | automated, HIL |
| ST-040 | SR-045 | Frame log of a USB session with a reply containing `0xAA` (for example a setpoint of 1.70 V, raw 170 = `0xAA`). | Frames match protocol.md 1.1 and 2.2; the doubled byte decodes correctly. Result recorded for TBD-013. | automated, HIL |
| ST-041 | SR-046 | 1. Connect, 5.00 V, 0.100 A, nothing connected, output on. 2. End the process without an orderly close (send SIGKILL to the test subprocess). 3. Reconnect to the same supply and read the marker state the library exposes. | The library reports that a previous session may have left the output on, before any control call. After an orderly close in a control run, no marker remains. | automated, HIL |
| ST-042 | SR-047 | Inspect the installed README of the app and the library. | Both carry the UR-031 note; the app links to it from its connection screen. | inspection |

## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | First draft, written ahead of G1 | not yet approved |
| 2 | 2026-09-29 | Matched SR revision 2: ST-007, ST-022, ST-023; CI instead of HW? in the coverage table. | not yet approved |
| 3 | 2026-09-29 | Independent review findings: Load B defined, HIL limits kept in ST-022, ST-030, ST-038; ST-034 matches SR-034; ST-038 measures frame times; coverage codes match methods. | not yet approved |
| 4 | 2026-09-29 | TBD-015 mitigations: ST-041 (unclean-exit marker) and ST-042 (bench note) added. | not yet approved |
