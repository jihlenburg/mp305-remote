# 7. System test specification (ST)

Status: approved (revision 14, user, 2026-10-05; revision 13 with ADR-0018 and revision 14 were approved that day, the baseline before them was revision 12 of 2026-10-02).

System tests verify the system requirements in
[2-system-requirements.md](2-system-requirements.md), revision 8. Both
passed G2 on 2026-09-30.

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
to change a setting on the front panel. Over Bluetooth the first control
call of a connection opens the supply's "Allow Remote Control" prompt
(SR-018, SR-053), so over Bluetooth every entry that sends a control
command needs a person there, whatever its Method column says. The
automated tests skip such an entry unless the run opts in with
`MP305_HIL_PERSON=1` (and `pytest -s`), and an entry with a load unless
`MP305_HIL_LOAD` names that load; `tests/system/README.md` lists what each
test needs and does.

Tests over Bluetooth that need the prompt use a fresh host ID (SR-049) so
that the supply does not recognise the host; tests of the remembered-host
path say so.

## 2. Coverage

Revision 13, approved by the user on 2026-10-05 with
[ADR-0018](../adr/0018-focused-hardware-verification.md).

`H` requires the applicable hardware procedure on that OS and transport.
The record names the actual OS, architecture, adapter and firmware. A
native host or a VM whose device pass-through works is eligible; a VM
build or a scan alone does not establish a working hardware path. The
baseline's codes `VM` (the Parallels VMs on the Mac) and `CI` (no
hardware, mock tests only) are withdrawn: a missing host leaves the cell
open, it is not downgraded.

The Windows cells are hardware obligations that are open and deferred.
No Windows host with a working Bluetooth and USB path to the supply
exists: the USB Bluetooth dongle cannot carry a connection on the Mac, so
its VMs give no Bluetooth evidence (LOGBOOK 2026-10-04). No reuse is
defined for Windows. On Linux the hardware runs use a native machine, and
the record names the adapter (ADR-0017: one adapter).

`R` is permitted only for the three Linux cells marked below. It requires
a recorded equivalence analysis using a passing `H` result for the same
entry and transport on macOS from the build under test, or one reviewed
again against that commit; Linux's current unit and integration results;
and the Linux hardware prerequisites listed in
[the execution plan](hardware-verification-plan.md#system-evidence-reuse).
The user signs the reuse record off. It is not a hardware pass on Linux.
Until the prerequisites and the change-impact review pass, the cell
remains open. A failed or inconclusive source result cannot be reused.

`A` retains the existing analysis, inspection or no-supply method. Log
checks still inspect the relevant hardware logs; package inspections use
the actual release artifacts. `n/a` means the transport does not apply.
All procedures and expected results in section 3 remain required; `R`
changes where evidence is obtained, not what constitutes success.

For ST-038 only, the chart-range observations (step 1) may be shared
between transports on the same OS and app binary after a recorded
analysis confirms the same chart path and that both transports deliver
live readings. The 30 min memory check (step 2) and every other step
remain transport-specific, since the transports buffer readings
differently. Both cells remain `H`.

| ST | macOS BLE | macOS USB | Linux BLE | Linux USB | Windows BLE | Windows USB |
|---|---|---|---|---|---|---|
| ST-001 | H | n/a | H | n/a | H | n/a |
| ST-002 | H | n/a | H | n/a | H | n/a |
| ST-003 | n/a | H | n/a | H | n/a | H |
| ST-004 | H | H | H | H | H | H |
| ST-005 | H | n/a | H | n/a | H | n/a |
| ST-006 | H | H | H | H | H | H |
| ST-007 | H | n/a | H | n/a | H | n/a |
| ST-008 | H | n/a | H | n/a | H | n/a |
| ST-009 | H | n/a | H | n/a | H | n/a |
| ST-010 | H | n/a | H | n/a | H | n/a |
| ST-011 | n/a | H | n/a | H | n/a | H |
| ST-012 | H | H | R | R | H | H |
| ST-013 | H | H | H | H | H | H |
| ST-014 | H | H | H | H | H | H |
| ST-015 | H | H | H | H | H | H |
| ST-016 | A | A | A | A | A | A |
| ST-017 | A | A | A | A | A | A |
| ST-018 | H | H | H | H | H | H |
| ST-019 | H | H | H | H | H | H |
| ST-020 | H | H | H | H | H | H |
| ST-021 | H | H | H | H | H | H |
| ST-022 | H | H | H | H | H | H |
| ST-023 | H | H | H | H | H | H |
| ST-024 | H | H | H | H | H | H |
| ST-025 | A | A | A | A | A | A |
| ST-026 | H | H | H | H | H | H |
| ST-027 | H | H | H | H | H | H |
| ST-028 | H | H | H | H | H | H |
| ST-029 | H | H | H | H | H | H |
| ST-030 | H | H | H | H | H | H |
| ST-031 | H | H | H | H | H | H |
| ST-032 | A | A | A | A | A | A |
| ST-033 | H | H | H | H | H | H |
| ST-034 | H | H | H | H | H | H |
| ST-035 | H | H | R | H | H | H |
| ST-036 | H | H | H | H | H | H |
| ST-037 | A | A | A | A | A | A |
| ST-038 | H | H | H | H | H | H |
| ST-039 | H | n/a | H | n/a | H | n/a |
| ST-040 | n/a | H | n/a | H | n/a | H |
| ST-041 | H | H | H | H | H | H |
| ST-042 | A | A | A | A | A | A |
| ST-043 | H | H | H | H | H | H |
| ST-044 | A | A | A | A | A | A |
| ST-045 | H | n/a | H | n/a | H | n/a |
| ST-046 | n/a | H | n/a | H | n/a | H |
| ST-047 | A | A | A | A | A | A |
| ST-048 | H | n/a | H | n/a | H | n/a |
| ST-049 | H | H | H | H | H | H |
| ST-050 | H | H | H | H | H | H |

## 3. Test specifications

| ST | Verifies | Procedure | Expected result | Method | Status |
|---|---|---|---|---|---|
| ST-001 | SR-001 | Discover over Bluetooth with the supply on, once with remote control enabled on the supply and once disabled. | With remote enabled the supply appears with an OS identifier, the name as advertised (starting `0000MP305B`), a three-character unit identifier equal to the last three name characters, the remote flag set and an RSSI in dBm. With remote disabled it does not appear (it does not advertise). | automated, HIL, person | approved (prior baseline) |
| ST-002 | SR-002 | 1. Discover with the default scan time and time it. 2. Discover with 1 s and with 60 s. 3. Pass 0.5 s and 61 s. | Default about 10 s; 1 s and 60 s honored within 0.5 s; out-of-range values raise `ValueError`. | automated, HIL | approved (prior baseline) |
| ST-003 | SR-003 | Discover over USB with the supply plugged in. | The supply appears as a USB result with a name (the product string) containing `MP305` and its HID path as identifier; discovery lists a USB device only when its vendor is `0x28E9` and its product `0x028A` (DD-DISC-003), and a result carries neither number. No serial string is required; the library does not expose one, so TBD-013 is answered with the OS tools in the run's record. | automated, HIL | approved (prior baseline) |
| ST-004 | SR-004 | 1. Connect by the identifier from discovery. 2. With the library, connect without an identifier while a second supply, or a simulated second discovery result through the mock transport, is present. | 1 connects to that supply. 2 raises an error that lists both supplies. | automated, HIL plus mock | approved (prior baseline) |
| ST-005 | SR-005 | Connect WebLink in Chrome to the supply, then discover with the library. | `NotFoundError` whose text names the four causes. | manual, HIL (needs Chrome) | approved (prior baseline) |
| ST-006 | SR-006 | 1. Run a full session (connect, read, set 5 V and 0.1 A, output on and off, close) with the transport's frame log on. 2. The allowlist and the never-send list are not reachable through the library; they are verified by IT-012. | The log contains only `0x18`, `0xE0`, `0xC2` and `0xC8` requests. The never-send list holds `0x10`, `0xC0`, `0xBE`, `0x20`, `0xF0` to `0xFE`, each with a reason (IT-012). | automated, HIL; step 2 by IT-012 | approved (prior baseline) |
| ST-007 | SR-010 | Connect over Bluetooth with a fresh host ID; the person presses deny. Then call `set_voltage(1.0)`. | `ConnectionDeniedError` at connect; the link is closed, and the call raises because there is no connection. The frame log shows the two bind frames of SR-050 and nothing after the `19 FF`. | automated, HIL, person | approved (prior baseline) |
| ST-008 | SR-007 | Connect over Bluetooth with a fresh host ID and the frame log on; the person presses allow. | The log shows notifications enabled on both characteristics, the negotiated MTU recorded (at least 74), then the bind frame on `AF02` (`0x18`, the stored host ID, `00`, flag), and no `AF01` write before the `19 00` reply. | automated, HIL, person | approved (prior baseline) |
| ST-009 | SR-008 | Connect with a fresh host ID, a callback and a log handler; the person waits 5 s, then presses allow. | The callback ran and the WARNING record with the confirmation text and the 30 s bound was logged before the reply. | automated, HIL, person | approved (prior baseline) |
| ST-010 | SR-009 | Connect with a fresh host ID; the person does not press anything. Record the time from connection to the error and whether the OS reported a disconnect first. | `Mp305TimeoutError` naming the 30 s bound, within 31 s of the connection; the link is closed. The recorded time and any late `19 FF` settle TBD-008. | automated, HIL, person | approved (prior baseline) |
| ST-011 | SR-011 | Connect over USB with the frame log on and watch the supply's screen. | No `0x18` in the log. The connection is allowed after the `0xE1` reply. The record says whether the supply showed a prompt (TBD-004). | automated, HIL, person | approved (prior baseline) |
| ST-012 | SR-012 | Connect; compare the reported model, versions and live mode with the supply's information screen, and the setpoints with the screen. Call a control method before the first reading (via a hook that delays polling). | Values match. The early control call waits for or refuses until the first reading. | automated, HIL, person (the comparison with the screen) | approved (rev 13) |
| ST-013 | SR-013 | Stream readings for 60 s over each transport, output off. | At least 120 readings. No request followed its previous reply by less than 100 ms (frame log). | automated, HIL | approved (prior baseline) |
| ST-014 | SR-014 | 1. Set 5.00 V, 0.100 A on the front panel. 2. With Load A, output on, read 10 readings. | Setpoints read 5.0 V and 0.1 A. Measured voltage about 5.0 V, current about 0.05 A (Load A, 1 %), power about 0.25 W, each within 5 %. Working time rises by 1 per second. Timestamps rise. Result recorded for TBD-011. | automated, HIL, person (step 1 on the front panel), Load A | approved (prior baseline) |
| ST-015 | SR-015 | Read with output off; then with Load A and output on at 5 V, 0.1 A with CC (not OCP) selected on the front panel (CV expected); then with Load A at 5 V, 0.02 A (CC expected). Mock: `outState` 3 and 9. | Modes "off", CV, CC; mock gives "held above setpoint" and "unknown (9)". | automated, HIL plus mock | approved (prior baseline) |
| ST-016 | SR-016 | Mock transport: a `0xC3` two bytes short, an `AF01` notification not starting with `0x31`, a USB frame with a wrong checksum. | Each is dropped, counted and logged; no reading is produced from it. | automated, mock | approved (prior baseline) |
| ST-017 | SR-017 | 1. Frame log of ST-013. 2. Mock transport: while a `0xC2` is in flight, deliver a `0xC5`, then the `0xC3`; deliver a `0xC9` with no request in flight; deliver a `0xC9` after a `0xC8` timed out, then send a new `0xC8`. | 1 No overlapping requests. 2 The `0xC5` is reported as a settings event and the `0xC3` completes the read; the stray `0xC9` is counted as a late reply (the session's counter) and logged at WARNING; the late `0xC9` is not counted as the reply to the new `0xC8`. | automated, mock, plus log check | approved (prior baseline) |
| ST-018 | SR-018 | Over USB: connect, then set 1.00 V with the frame log on. Over Bluetooth: the same; the person presses allow on the remote-control prompt. | The first `0xC8` has `remoteCon = 2`. Over USB `0xC9` 0 follows within 1 s; over Bluetooth no reply until the person presses allow, then `0xC9` 0. The setpoint command then has `remoteCon = 1`. Result recorded for TBD-012. | automated, HIL, person | approved (prior baseline) |
| ST-019 | SR-019 | 1. Connect, set 3 V and 0.05 A, output off. 2. Explicitly release remote control with the library, then change to 4 V on the front panel and observe it in telemetry. 3. Explicitly request remote control again; over Bluetooth the person presses Allow. 4. After the grant, wait for a reading showing 4 V that meets SR-019, then call `set_current_limit(0.08)` within 2 s of observing that reading. | The active `0xC8` carries 4.00 V, 0.080 A, output 0, and every other field as in the qualifying `0xC3`, with `refresh = 0`. The source reading is at least 100 ms after the preceding `0xC9` and at most 1 s old when used. The command is accepted and telemetry confirms 4.00 V, 0.080 A, output off. The 2 s procedure bound excludes the person's grant wait; SR-019 freshness bounds are unchanged. | automated, HIL, person | approved (rev 13) |
| ST-020 | SR-020 | Change voltage, current and read state 20 times with the output off. | No `0xC8` in the log has `output = 1`. The output stays off. | automated, HIL | approved (prior baseline) |
| ST-021 | SR-021 | Put the supply in program or PD mode on the front panel, output off, then connect and call `set_voltage(1.0)`. | `ModeError`; no `0xC8` sent. Restore DC mode. | automated, HIL, person | approved (prior baseline) |
| ST-022 | SR-022 | 1. Load A, 5 V, 0.1 A, output on. 2. Queue five voltage changes (1.0, 1.5, 2.0, 2.5, 3.0 V, current limit unchanged at 0.1 A) and one `output_off()` at once. 3. Time from the call to the `0xC9` acknowledgment, and to the first reading with output 0. 4. Repeat after the supply released remote control (link loss and reconnect, ST-028), over Bluetooth with the person ready. | Output-off is sent first. Acknowledged within 0.5 s. The reading shows output 0 and voltage under 0.5 V. In step 4 the library first requests remote control, logs the confirmation text, and switches off within 0.5 s of the grant. | automated, HIL, person | approved (prior baseline) |
| ST-023 | SR-023 | 1. Normal command. 2. Take remote control away on the front panel if the supply allows it (TBD-012), then send a command. 3. Mock transport: no reply, a reply of `0xFF` to a command, and a reply of 7 (a setpoint above the range never reaches the transport: the library refuses it before encoding, ST-035). | 1 accepted. 2 `RemoteControlLostError`. 3 `Mp305TimeoutError` after 1 s, `CommandRejectedError` with an inferred reason, and `CommandRejectedError` naming 7. | automated, HIL plus mock | approved (prior baseline) |
| ST-024 | SR-024 | Call `set_voltage` with NaN, infinity, -0.01, 30.01 and a value above a user limit; then 1.004 and 1.006. | The first five raise `SetpointRangeError` and send nothing. The last two send 1.00 V and 1.01 V. | automated, HIL (sending part at 5 V or less) | approved (prior baseline) |
| ST-025 | SR-025 | Read the range the library reports; call `set_current_limit(5.001)`. | 0 to 30.00 V, 0 to 5.000 A; the call raises `SetpointRangeError`. | automated, no supply needed | approved (prior baseline) |
| ST-026 | SR-026 | Trip OCP as in AT-009, then call `output_on()`. | `FaultActiveError`; no `0xC8` with `output = 1` sent. Restore CC mode. | automated, HIL, person | approved (prior baseline) |
| ST-027 | SR-027 | 1. Trip OCP as in AT-009 while streaming. 2. Mock: a `0xC3` with bit 11 set. | 1 The first reading after the trip lists the over-current fault; the fault set change is reported once. 2 The reading lists "unknown fault bit 11". | automated, HIL, person, plus mock | approved (prior baseline) |
| ST-028 | SR-028 | 1. Streaming, output off. 2. Switch the supply off. 3. Repeat by switching off Bluetooth on the host, and by pulling the USB cable. | `LinkLostError` within 4 s of the last reply, whose text says the output is still in its last state and remote control was released. No frames sent afterwards and no reconnect. | automated, HIL, person | approved (prior baseline) |
| ST-029 | SR-029 | 1. `with` block that switches the output on with no load, then raises. 2. Same with a normal end. | Frame log ends with `0xC8` `output = 0`, then `0xC8` `remoteCon = 0`. The original exception reaches the caller in case 1. | automated, HIL | approved (prior baseline) |
| ST-030 | SR-030 | Close the app window with the output on (no load), once choosing "switch off" and once "leave on". After the "leave on" run, switch the output off on the front panel. On macOS, also quit with Cmd+Q with the output on and with the Dock's Quit. | The app asks. The output follows the choice. Cmd+Q asks; the Dock's Quit does not ask, and the next connection shows the unclean-exit warning. | manual, HIL | approved (prior baseline) |
| ST-031 | SR-031 | 1. Start a connect and press Ctrl-C during the bind wait. 2. Run a Python thread that counts while a library call blocks. | 1 `KeyboardInterrupt` within 0.5 s. 2 The counter advances during the call. | automated, HIL, person (step 1 in a subprocess) | approved (prior baseline) |
| ST-032 | SR-032 | Inspect the exception classes. | All listed classes exist with the stated bases. The HIL tests raise most of them; `CommandRejectedError` is raised through the mock in ST-023, `RemoteControlDeniedError` in ST-048, and `RemoteControlLostError` only if TBD-012 finds a way to cause it. | analysis plus inspection | approved (prior baseline) |
| ST-033 | SR-033 | Read a reading and inspect it; try to change a field. | Types and units as listed, including `live_mode` and `working_time`; assigning raises an error. | automated, HIL | approved (prior baseline) |
| ST-034 | SR-034 | 1. Stream at 0.1, 2 and 4 per second for 30 s each. 2. Write 30 s to CSV. 3. Ask for 4.1 per second. 4. With the mock transport slowed to 1 reply per second, ask for 4 per second. | Step 1: each count is within 10 % of the rate, or, where the link cannot keep up with the rate, it is what the link delivers: below the rate, not below 90 % of the 2 per second of SR-013 or of the rate if that is lower, with exactly one warning logged for that stream. A stream that keeps up logs no warning. The CSV follows SR-037. Step 3 raises `ValueError`. Step 4 yields about 1 reading per second and one warning. | automated, HIL | approved (rev 13) |
| ST-035 | SR-035 | 1. Ramp 1 to 5 V, step 1 V, 1 s dwell, no load. 2. Ramp with an end value above the user limit. | 1 setpoints 1, 2, 3, 4, 5 V, about 1 s apart. 2 `SetpointRangeError` before anything is sent. | automated, HIL | approved (rev 13) |
| ST-036 | SR-036, SR-043 | Install the wheel on each OS in the coverage table and import `mp305`; start the app there. Inspect the macOS bundle's Info.plist. | Import works; stub present; app starts; Info.plist has the key. | inspection plus manual | approved (prior baseline) |
| ST-037 | SR-037 | Analysis plus check: parse a file from ST-034 and one from the app. | Both have the same header and format. | automated (`tests/system/test_csv_format.py`), with files from HIL runs | approved (prior baseline) |
| ST-038 | SR-038, SR-039, SR-040, SR-041, SR-042 | Manual app session: 1. Chart range 10 s and 10 min. 2. Watch memory for 30 min at 60 s range. 3. During the bind wait and during a remote-control prompt, move and resize the window, with the app's frame-time log on. 4. Set a user voltage limit of 5 V, then type "4.5" slowly into the voltage field without Enter. 5. Output-off while a command is pending. 6. Break the link. 7. With output off, release remote control if held, then change the ramp step on the front panel while connected. 8. With output off, disable the active grant on the front panel if needed and select PD mode while connected; restore DC afterwards. | 1 Ranges honored. 2 Memory stays flat within 10 %. 3 No frame over 100 ms in the log, and readings appear within 100 ms of arriving (log timestamps). 4 Nothing sent until Enter; then 4.5 V is sent once (frame log). 5 Output-off works. 6 Banner with the "still in its last state" text, controls off, reconnect button. 7 The new value appears without a request from the app (TBD-018). 8 The app tells the user to switch the output off on the supply; Output OFF stays enabled. | manual, HIL, person | approved (rev 13) |
| ST-039 | SR-044 | Frame log of ST-008 and ST-013. | Requests and replies have the stated shape on each characteristic; one write in flight; every notification was handled as one frame. | automated, HIL | approved (prior baseline) |
| ST-040 | SR-045 | Frame log of a USB session that includes a reply containing `0xAA` (for example a setpoint of 1.70 V, raw 170 = `0xAA`) and a request that needs more than one report (a `0xC8`, 13 stream bytes, fits one report; use the mock to check a 70-byte frame). | Every frame starts in a new report; no request is sent before the previous reply; the byte after the report ID equals the number of stream bytes in that report; the doubled byte decodes correctly; replies carry address `0x21`. Result recorded for TBD-013. | automated, HIL plus mock | approved (prior baseline) |
| ST-041 | SR-046 | 1. Connect, 5.00 V, 0.100 A, nothing connected, output on. 2. End the process without an orderly close (send SIGKILL to the test subprocess). 3. Reconnect to the same supply and read the marker state the library exposes. | The library reports that a previous session may have left the output on, before any control call. After an orderly close in a control run, no marker remains. | automated, HIL | approved (prior baseline) |
| ST-042 | SR-047 | Inspect the installed README of the app and the library. | Both carry the UR-031 note; the app links to it from its connection screen. | inspection | approved (prior baseline) |
| ST-043 | SR-048 | 1. With a Bluetooth session open and streaming, connect over USB from a second process and read once. 2. Try to open a second connection to the same supply from the first process. | 1 The Bluetooth session reports that a USB host is active (its reads go silent) and recovers within 30 s after the USB process closes. 2 The second connection raises an error naming the open one. | automated, HIL | approved (rev 14) |
| ST-044 | SR-049 | 1. Delete the state directory, start the library, read the host ID it will present, restart and read it again. 2. Compare with a second state directory. | The ID is 16 bytes, not all zero, not WebLink's constant, the same across restarts, and different between the two directories. | automated, no supply needed | approved (prior baseline) |
| ST-045 | SR-050 | 1. Fresh host ID; connect; the person presses allow; disconnect. 2. Connect again with the same ID; the person watches the screen. 3. Delete the ID, connect again. | 1 The log shows a fast bind answered `19 FF`, then the prompt bind and `19 00`. 2 The fast bind is answered `19 00`, no prompt appears, and the library reports the supply recognised the host. 3 The prompt appears again. Result settles TBD-006. | automated, HIL, person | approved (prior baseline) |
| ST-046 | SR-051 | Over USB: connect, take remote control, stream readings for 20 s, then send `set_voltage(1.0)`. The clause of SR-051 for paused polling is verified on the mock by IT-021 and UT-LINK-020. | The frame log shows at least one frame every 2 s; the setpoint command is accepted with `0xC9` 0 (the grant survived). | automated, HIL | approved (prior baseline) |
| ST-047 | SR-052 | Check every request in the frame logs of ST-006, ST-008 and ST-018 against the payload lengths of protocol.md 3 and 4. | Every request carries its full payload. | automated, log check | approved (prior baseline) |
| ST-048 | SR-053 | Over Bluetooth: connect, then call `set_voltage(1.0)`. Run 1: the person presses deny. Run 2: nobody presses anything. Run 3: the person presses allow after 10 s while the test queues a second control call. | Run 1 `RemoteControlDeniedError` after the `0xC9` 1. Run 2 `RemoteControlDeniedError` within 70 s. Run 3 the frame log shows no control command between the request and the `0xC9` 0; the queued call is sent after it. The confirmation text was logged in all runs. | automated, HIL, person | approved (prior baseline) |
| ST-049 | SR-054 | Connect, take remote control, output off. On the front panel confirm disabling the active remote-control grant, then select PD mode while leaving the library connection open. Observe PD telemetry, then close the library connection. Restore DC mode. | The frame log shows no `0xC8` with `remoteCon = 0` after the mode change; a warning is logged. Restore DC mode. | automated, HIL, person | approved (rev 13) |
| ST-050 | SR-055 | 1. Enable automatic reconnection, connect over Bluetooth to a supply that remembers the host, stream readings, then switch off Bluetooth on the host for 20 s and switch it on again. 2. Repeat over USB by pulling and re-plugging the cable. 3. Repeat step 1 with the remembered host ID deleted. 4. With reconnection disabled, repeat step 1. | 1 and 2: the library reports the loss and, within 30 s of the link being available again, the reconnection; readings resume; no `0xC8` in the frame log until a control call. 3: the fast bind gets `19 FF`, the retry stops and is reported. 4: `LinkLostError`, no retry. | automated, HIL, person | approved (rev 14) |


## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | First draft, written ahead of G1 | not yet approved |
| 2 | 2026-09-29 | Matched SR revision 2: ST-007, ST-022, ST-023; CI instead of HW? in the coverage table. | not yet approved |
| 3 | 2026-09-29 | Independent review findings: Load B defined, HIL limits kept in ST-022, ST-030, ST-038; ST-034 matches SR-034; ST-038 measures frame times; coverage codes match methods. | not yet approved |
| 4 | 2026-09-29 | TBD-015 mitigations: ST-041 (unclean-exit marker) and ST-042 (bench note) added. | not yet approved |
| 5 | 2026-09-30 | Matched SR revision 8: ST-001, ST-003, ST-005 to ST-012, ST-014 to ST-018, ST-022, ST-023, ST-027, ST-028, ST-032, ST-033, ST-038 to ST-040 rewritten; ST-043 to ST-049 added for SR-048 to SR-054; coverage table with the Parallels VM code (TBD-009); every HIL test records the supply's versions. | not yet approved |
| 6 | 2026-09-30 | ST-050 for SR-055 (automatic reconnection). | not yet approved |
| 7 | 2026-09-30 | G2: status approved. No test procedure changed. | user, 2026-09-30 (G2) |
| 8 | 2026-09-30 | ST-008 matches the changed SR-007 (negotiated MTU recorded instead of a request). | user, 2026-09-30 (with G3) |
| 9 | 2026-09-30 | ST-008 changed with SR-007: bind frame with one zero byte. | user, 2026-09-30 (with G4 protocol) |
| 10 | 2026-10-01 | ST-046 restated from the py DD (py.md section 8, decision 7): the library has no way to pause polling, so the test streams readings for 20 s; the paused-polling clause of SR-051 stays verified on the mock. Approved with G4 py. | user, 2026-10-01 (G4 py) |
| 11 | 2026-10-01 | ST-030 (Cmd+Q and the Dock's Quit on macOS) and ST-038 (step 8, the notice outside DC mode) changed with SR-030 and SR-041 from the app DD (app.md section 8, decisions 7 and 13). Approved with G4 app. | user, 2026-10-01 (G4 app) |
| 12 | 2026-10-02 | From writing the automated system tests: section 1 states that over Bluetooth every entry with a control command needs a person for the remote-control prompt, and names the opt-ins of the tests; ST-003 (a result carries no vendor or product number and no serial), ST-006 (step 2 is IT-012), ST-012 and ST-014 (a person), ST-017 (a stray `0xC9` is a counted late reply, not an event), ST-023 (step 3). Still open until a run on hardware: ST-043 step 1, ST-050 step 3, and the HID path after a re-plug. | user, 2026-10-02 |
| 13 | 2026-10-05 | Coverage: the codes `VM` and `CI` give way to `H`, hardware on an actual host, with a missing host leaving the cell open; the Windows cells are open and deferred. Conditional reuse (`R`) only for ST-012 on Linux and ST-035 on Linux over Bluetooth, with the user's sign-off; every hazard-related entry and every entry without a person stays hardware (the user's decisions of 2026-10-05 on the review of the first draft of 2026-10-04). ST-034: a link that cannot keep up delivers what it has with one warning, as SR-034 says (Linux delivers 2.5 to 3.3 readings per second, record `2026-10-05-system-linux-ble-noperson.md`). Correct grant handling in ST-019, ST-038 and ST-049; the ST-019 2 s procedure clock starts after re-grant and a qualifying reading, with SR-019 freshness unchanged. ST-038 step 1 may be shared between transports on the same OS and binary after analysis; its memory check stays per transport. ADR-0018 and the execution plan define the reuse prerequisites and batching. | user, 2026-10-05 |
| 14 | 2026-10-05 | ST-043 and ST-050: the recovery is expected within 30 s instead of 10 s. Reconnection attempts come every 5 s, and an attempt that is under way when the link returns must end first (its scan takes up to 10 s, a stalled connect up to 35 s in all, DD-DISC-011 revision 7), so the design never guaranteed 10 s. 30 s covers an attempt under way plus a normal one; a stalled connect still fails the entry. | user, 2026-10-05 |
