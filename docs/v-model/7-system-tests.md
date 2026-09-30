# 7. System test specification (ST)

Status: draft

System tests verify the system requirements in
[2-system-requirements.md](2-system-requirements.md), revision 8. Like that
document, this draft was written ahead of G1 and is not put up for G2 until
G1 has passed.

Automated system tests are pytest tests in `tests/system/`. They drive the
system through the installed Python library, carry `@pytest.mark.spec("ST-nnn")`
and, when they use a supply, `@pytest.mark.hil`. They run only when the user
sets `MP305_HIL=1` and `MP305_HIL_DEVICE` in the current session (AGENTS.md,
"Hardware-in-the-loop tests"). App behavior is tested by manual procedures.

Every test that uses a supply records the supply's application version and
hardware revision from `0xE1`. The device facts behind the expected results
come from the 1.6.0.51 update; a run on another version records any
difference as a finding, not as a failure of the software.

## 1. Test conditions

The HIL safety rules of AGENTS.md apply: nothing on the output unless the
test names a load, 5 V and 100 mA or less, output off and settings restored
in teardown, also on failure. "Load A" is the 100 Ω resistor of
8-acceptance-tests.md, with 1 % tolerance. "Load B" is its 22 Ω resistor. It is
used only in ST-026 and ST-027, where about 230 mA must flow briefly to make
the supply trip at a 100 mA limit.

Tests marked "person" need someone at the supply to press allow or deny, or
to change a setting on the front panel.

Tests over Bluetooth that need the prompt use a fresh host ID (SR-049) so
that the supply does not recognise the host; tests of the remembered-host
path say so.

## 2. Coverage

Codes: HW (the user's MP305B from the Mac itself), VM (the user's MP305B
from a Parallels VM on the Mac: USB by passing the supply through to the VM,
Bluetooth with a USB Bluetooth dongle assigned to the VM, TBD-009), CI (no
hardware for this OS and transport), n/a, and A (analysis, inspection or a
test without a supply, OS and transport independent). "BLE" and "USB" stand
for the transports. Until a Bluetooth dongle is at hand, "VM" in a BLE
column means CI.

| ST | macOS BLE | macOS USB | Linux BLE | Linux USB | Windows BLE | Windows USB |
|---|---|---|---|---|---|---|
| ST-001, ST-002, ST-005, ST-007 to ST-010, ST-039, ST-045, ST-048 | HW | n/a | VM | n/a | VM | n/a |
| ST-003, ST-011, ST-040, ST-046 | n/a | HW | n/a | VM | n/a | VM |
| ST-004, ST-006, ST-012 to ST-015, ST-018 to ST-024, ST-026 to ST-031, ST-033 to ST-036, ST-038, ST-041, ST-043, ST-049 | HW | HW | VM | VM | VM | VM |
| ST-016, ST-017, ST-025, ST-032, ST-037, ST-042, ST-044, ST-047 | A | A | A | A | A | A |

## 3. Test specifications

| ST | Verifies | Procedure | Expected result | Method |
|---|---|---|---|---|
| ST-001 | SR-001 | Discover over Bluetooth with the supply on, once with remote control enabled on the supply and once disabled. | With remote enabled the supply appears with an OS identifier, the name as advertised (starting `0000MP305B`), a three-character unit identifier equal to the last three name characters, the remote flag set and an RSSI in dBm. With remote disabled it does not appear (it does not advertise). | automated, HIL, person |
| ST-002 | SR-002 | 1. Discover with the default scan time and time it. 2. Discover with 1 s and with 60 s. 3. Pass 0.5 s and 61 s. | Default about 10 s; 1 s and 60 s honored within 0.5 s; out-of-range values raise `ValueError`. | automated, HIL |
| ST-003 | SR-003 | Discover over USB with the supply plugged in. | The supply appears with vendor `0x28E9`, product `0x028A`, a product string containing `MP305` and its HID path. No serial string is required; whether the OS reports one is recorded for TBD-013. | automated, HIL |
| ST-004 | SR-004 | 1. Connect by the identifier from discovery. 2. With the library, connect without an identifier while a second supply, or a simulated second discovery result through the mock transport, is present. | 1 connects to that supply. 2 raises an error that lists both supplies. | automated, HIL plus mock |
| ST-005 | SR-005 | Connect WebLink in Chrome to the supply, then discover with the library. | `NotFoundError` whose text names the four causes. | manual, HIL (needs Chrome) |
| ST-006 | SR-006 | 1. Run a full session (connect, read, set 5 V and 0.1 A, output on and off, close) with the transport's frame log on. 2. Inspect the transport's allowlist and never-send list. | The log contains only `0x18`, `0xE0`, `0xC2` and `0xC8` requests. The never-send list holds `0x10`, `0xC0`, `0xBE`, `0x20`, `0xF0` to `0xFE`, each with a reason. | automated, HIL, plus inspection |
| ST-007 | SR-010 | Connect over Bluetooth with a fresh host ID; the person presses deny. Then call `set_voltage(1.0)`. | `ConnectionDeniedError` at connect; the link is closed, and the call raises because there is no connection. The frame log shows the two bind frames of SR-050 and nothing after the `19 FF`. | automated, HIL, person |
| ST-008 | SR-007 | Connect over Bluetooth with a fresh host ID and the frame log on; the person presses allow. | The log shows notifications enabled on both characteristics, an MTU request of 247, then the bind frame on `AF02` (`0x18`, the stored host ID, `00 00`, flag), and no `AF01` write before the `19 00` reply. | automated, HIL, person |
| ST-009 | SR-008 | Connect with a fresh host ID, a callback and a log handler; the person waits 5 s, then presses allow. | The callback ran and the WARNING record with the confirmation text and the 30 s bound was logged before the reply. | automated, HIL, person |
| ST-010 | SR-009 | Connect with a fresh host ID; the person does not press anything. Record the time from connection to the error and whether the OS reported a disconnect first. | `Mp305TimeoutError` naming the 30 s bound, within 31 s of the connection; the link is closed. The recorded time and any late `19 FF` settle TBD-008. | automated, HIL, person |
| ST-011 | SR-011 | Connect over USB with the frame log on and watch the supply's screen. | No `0x18` in the log. The connection is allowed after the `0xE1` reply. The record says whether the supply showed a prompt (TBD-004). | automated, HIL, person |
| ST-012 | SR-012 | Connect; compare the reported model, versions and live mode with the supply's information screen, and the setpoints with the screen. Call a control method before the first reading (via a hook that delays polling). | Values match. The early control call waits for or refuses until the first reading. | automated, HIL |
| ST-013 | SR-013 | Stream readings for 60 s over each transport, output off. | At least 120 readings. No request followed its previous reply by less than 100 ms (frame log). | automated, HIL |
| ST-014 | SR-014 | 1. Set 5.00 V, 0.100 A on the front panel. 2. With Load A, output on, read 10 readings. | Setpoints read 5.0 V and 0.1 A. Measured voltage about 5.0 V, current about 0.05 A (Load A, 1 %), power about 0.25 W, each within 5 %. Working time rises by 1 per second. Timestamps rise. Result recorded for TBD-011. | automated, HIL |
| ST-015 | SR-015 | Read with output off; then with Load A and output on at 5 V, 0.1 A with CC (not OCP) selected on the front panel (CV expected); then with Load A at 5 V, 0.02 A (CC expected). Mock: `outState` 3 and 9. | Modes "off", CV, CC; mock gives "held above setpoint" and "unknown (9)". | automated, HIL plus mock |
| ST-016 | SR-016 | Mock transport: a `0xC3` two bytes short, an `AF01` notification not starting with `0x31`, a USB frame with a wrong checksum. | Each is dropped, counted and logged; no reading is produced from it. | automated, mock |
| ST-017 | SR-017 | 1. Frame log of ST-013. 2. Mock transport: while a `0xC2` is in flight, deliver a `0xC5`, then the `0xC3`; deliver a `0xC9` with no request in flight; deliver a `0xC9` after a `0xC8` timed out, then send a new `0xC8`. | 1 No overlapping requests. 2 The `0xC5` is reported as a settings event and the `0xC3` completes the read; the stray `0xC9` is reported as an event; the late `0xC9` is not counted as the reply to the new `0xC8`. | automated, mock, plus log check |
| ST-018 | SR-018 | Over USB: connect, then set 1.00 V with the frame log on. Over Bluetooth: the same; the person presses allow on the remote-control prompt. | The first `0xC8` has `remoteCon = 2`. Over USB `0xC9` 0 follows within 1 s; over Bluetooth no reply until the person presses allow, then `0xC9` 0. The setpoint command then has `remoteCon = 1`. Result recorded for TBD-012. | automated, HIL, person |
| ST-019 | SR-019 | 1. Connect, 3 V, 0.05 A, output off. 2. On the front panel change to 4 V. 3. Within 2 s, set 0.08 A from the library. | The `0xC8` carries 4.00 V, 0.080 A, output 0, and every other field as in the last `0xC3`. | automated, HIL, person |
| ST-020 | SR-020 | Change voltage, current and read state 20 times with the output off. | No `0xC8` in the log has `output = 1`. The output stays off. | automated, HIL |
| ST-021 | SR-021 | Put the supply in program or PD mode on the front panel, output off, then connect and call `set_voltage(1.0)`. | `ModeError`; no `0xC8` sent. Restore DC mode. | automated, HIL, person |
| ST-022 | SR-022 | 1. Load A, 5 V, 0.1 A, output on. 2. Queue five voltage changes (1.0, 1.5, 2.0, 2.5, 3.0 V, current limit unchanged at 0.1 A) and one `output_off()` at once. 3. Time from the call to the `0xC9` acknowledgment, and to the first reading with output 0. 4. Repeat after the supply released remote control (link loss and reconnect, ST-028), over Bluetooth with the person ready. | Output-off is sent first. Acknowledged within 0.5 s. The reading shows output 0 and voltage under 0.5 V. In step 4 the library first requests remote control, logs the confirmation text, and switches off within 0.5 s of the grant. | automated, HIL, person |
| ST-023 | SR-023 | 1. Normal command. 2. Take remote control away on the front panel if the supply allows it (TBD-012), then send a command. 3. Mock transport: no reply, a reply of `0xFF` after a setpoint above the range was blocked at the transport, and a reply of 7. | 1 accepted. 2 `RemoteControlLostError`. 3 `Mp305TimeoutError` after 1 s, `CommandRejectedError` with an inferred reason, and `CommandRejectedError` naming 7. | automated, HIL plus mock |
| ST-024 | SR-024 | Call `set_voltage` with NaN, infinity, -0.01, 30.01 and a value above a user limit; then 1.004 and 1.006. | The first five raise `SetpointRangeError` and send nothing. The last two send 1.00 V and 1.01 V. | automated, HIL (sending part at 5 V or less) |
| ST-025 | SR-025 | Read the range the library reports; call `set_current_limit(5.001)`. | 0 to 30.00 V, 0 to 5.000 A; the call raises `SetpointRangeError`. | automated, no supply needed |
| ST-026 | SR-026 | Trip OCP as in AT-009, then call `output_on()`. | `FaultActiveError`; no `0xC8` with `output = 1` sent. Restore CC mode. | automated, HIL, person |
| ST-027 | SR-027 | 1. Trip OCP as in AT-009 while streaming. 2. Mock: a `0xC3` with bit 11 set. | 1 The first reading after the trip lists the over-current fault; the fault set change is reported once. 2 The reading lists "unknown fault bit 11". | automated, HIL, person, plus mock |
| ST-028 | SR-028 | 1. Streaming, output off. 2. Switch the supply off. 3. Repeat by switching off Bluetooth on the host, and by pulling the USB cable. | `LinkLostError` within 4 s of the last reply, whose text says the output is still in its last state and remote control was released. No frames sent afterwards and no reconnect. | automated, HIL, person |
| ST-029 | SR-029 | 1. `with` block that switches the output on with no load, then raises. 2. Same with a normal end. | Frame log ends with `0xC8` `output = 0`, then `0xC8` `remoteCon = 0`. The original exception reaches the caller in case 1. | automated, HIL |
| ST-030 | SR-030 | Close the app window with the output on (no load), once choosing "switch off" and once "leave on". After the "leave on" run, switch the output off on the front panel. | The app asks. The output follows the choice. | manual, HIL |
| ST-031 | SR-031 | 1. Start a connect and press Ctrl-C during the bind wait. 2. Run a Python thread that counts while a library call blocks. | 1 `KeyboardInterrupt` within 0.5 s. 2 The counter advances during the call. | automated, HIL, person (step 1 in a subprocess) |
| ST-032 | SR-032 | Inspect the exception classes. | All listed classes exist with the stated bases. The HIL tests raise most of them; `CommandRejectedError` is raised through the mock in ST-023, `RemoteControlDeniedError` in ST-048, and `RemoteControlLostError` only if TBD-012 finds a way to cause it. | analysis plus inspection |
| ST-033 | SR-033 | Read a reading and inspect it; try to change a field. | Types and units as listed, including `live_mode` and `working_time`; assigning raises an error. | automated, HIL |
| ST-034 | SR-034 | 1. Stream at 0.1, 2 and 4 per second for 30 s each. 2. Write 30 s to CSV. 3. Ask for 4.1 per second. 4. With the mock transport slowed to 1 reply per second, ask for 4 per second. | Counts within 10 % of the rate. The CSV follows SR-037. Step 3 raises `ValueError`. Step 4 yields about 1 reading per second and one warning. | automated, HIL |
| ST-035 | SR-035 | 1. Ramp 1 to 5 V, step 1 V, 1 s dwell, no load. 2. Ramp with an end value above the user limit. | 1 setpoints 1, 2, 3, 4, 5 V, about 1 s apart. 2 `SetpointRangeError` before anything is sent. | automated, HIL |
| ST-036 | SR-036, SR-043 | Install the wheel on each OS in the coverage table and import `mp305`; start the app there. Inspect the macOS bundle's Info.plist. | Import works; stub present; app starts; Info.plist has the key. | inspection plus manual |
| ST-037 | SR-037 | Analysis plus check: parse a file from ST-034 and one from the app. | Both have the same header and format. | automated (`tests/system/test_csv_format.py`), with files from HIL runs |
| ST-038 | SR-038, SR-039, SR-040, SR-041, SR-042 | Manual app session: 1. Chart range 10 s and 10 min. 2. Watch memory for 30 min at 60 s range. 3. During the bind wait and during a remote-control prompt, move and resize the window, with the app's frame-time log on. 4. Set a user voltage limit of 5 V, then type "4.5" slowly into the voltage field without Enter. 5. Output-off while a command is pending. 6. Break the link. 7. Change the ramp step on the front panel while connected. | 1 Ranges honored. 2 Memory stays flat within 10 %. 3 No frame over 100 ms in the log, and readings appear within 100 ms of arriving (log timestamps). 4 Nothing sent until Enter; then 4.5 V is sent once (frame log). 5 Output-off works. 6 Banner with the "still in its last state" text, controls off, reconnect button. 7 The new value appears without a request from the app (TBD-018). | manual, HIL, person |
| ST-039 | SR-044 | Frame log of ST-008 and ST-013. | Requests and replies have the stated shape on each characteristic; one write in flight; every notification was handled as one frame. | automated, HIL |
| ST-040 | SR-045 | Frame log of a USB session that includes a reply containing `0xAA` (for example a setpoint of 1.70 V, raw 170 = `0xAA`) and a request that needs more than one report (a `0xC8`, 13 stream bytes, fits one report; use the mock to check a 70-byte frame). | Every frame starts in a new report; no request is sent before the previous reply; the byte after the report ID equals the number of stream bytes in that report; the doubled byte decodes correctly; replies carry address `0x21`. Result recorded for TBD-013. | automated, HIL plus mock |
| ST-041 | SR-046 | 1. Connect, 5.00 V, 0.100 A, nothing connected, output on. 2. End the process without an orderly close (send SIGKILL to the test subprocess). 3. Reconnect to the same supply and read the marker state the library exposes. | The library reports that a previous session may have left the output on, before any control call. After an orderly close in a control run, no marker remains. | automated, HIL |
| ST-042 | SR-047 | Inspect the installed README of the app and the library. | Both carry the UR-031 note; the app links to it from its connection screen. | inspection |
| ST-043 | SR-048 | 1. With a Bluetooth session open and streaming, connect over USB from a second process and read once. 2. Try to open a second connection to the same supply from the first process. | 1 The Bluetooth session reports that a USB host is active (its reads go silent) and recovers within 10 s after the USB process closes. 2 The second connection raises an error naming the open one. | automated, HIL |
| ST-044 | SR-049 | 1. Delete the state directory, start the library, read the host ID it will present, restart and read it again. 2. Compare with a second state directory. | The ID is 16 bytes, not all zero, not WebLink's constant, the same across restarts, and different between the two directories. | automated, no supply needed |
| ST-045 | SR-050 | 1. Fresh host ID; connect; the person presses allow; disconnect. 2. Connect again with the same ID; the person watches the screen. 3. Delete the ID, connect again. | 1 The log shows a fast bind answered `19 FF`, then the prompt bind and `19 00`. 2 The fast bind is answered `19 00`, no prompt appears, and the library reports the supply recognised the host. 3 The prompt appears again. Result settles TBD-006. | automated, HIL, person |
| ST-046 | SR-051 | Over USB: connect, take remote control, pause polling for 20 s, then send `set_voltage(1.0)`. | The frame log shows at least one frame every 2 s during the pause; the setpoint command is accepted with `0xC9` 0 (the grant survived). | automated, HIL |
| ST-047 | SR-052 | Check every request in the frame logs of ST-006, ST-008 and ST-018 against the payload lengths of protocol.md 3 and 4. | Every request carries its full payload. | automated, log check |
| ST-048 | SR-053 | Over Bluetooth: connect, then call `set_voltage(1.0)`. Run 1: the person presses deny. Run 2: nobody presses anything. Run 3: the person presses allow after 10 s while the test queues a second control call. | Run 1 `RemoteControlDeniedError` after the `0xC9` 1. Run 2 `RemoteControlDeniedError` within 70 s. Run 3 the frame log shows no control command between the request and the `0xC9` 0; the queued call is sent after it. The confirmation text was logged in all runs. | automated, HIL, person |
| ST-049 | SR-054 | Connect, take remote control, put the supply in PD mode on the front panel, then close the library connection. | The frame log shows no `0xC8` with `remoteCon = 0` after the mode change; a warning is logged. Restore DC mode. | automated, HIL, person |

## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | First draft, written ahead of G1 | not yet approved |
| 2 | 2026-09-29 | Matched SR revision 2: ST-007, ST-022, ST-023; CI instead of HW? in the coverage table. | not yet approved |
| 3 | 2026-09-29 | Independent review findings: Load B defined, HIL limits kept in ST-022, ST-030, ST-038; ST-034 matches SR-034; ST-038 measures frame times; coverage codes match methods. | not yet approved |
| 4 | 2026-09-29 | TBD-015 mitigations: ST-041 (unclean-exit marker) and ST-042 (bench note) added. | not yet approved |
| 5 | 2026-09-30 | Matched SR revision 8: ST-001, ST-003, ST-005 to ST-012, ST-014 to ST-018, ST-022, ST-023, ST-027, ST-028, ST-032, ST-033, ST-038 to ST-040 rewritten; ST-043 to ST-049 added for SR-048 to SR-054; coverage table with the Parallels VM code (TBD-009); every HIL test records the supply's versions. | not yet approved |
