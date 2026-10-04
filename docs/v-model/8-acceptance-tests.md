# 8. Acceptance test specification (AT)

Status: changed (revision 10, approval pending). Approved baseline: revision 9, user, 2026-09-30 (G1). Section 2 and the rows marked changed are proposed under ADR-0018; no acceptance result is approved by this draft.

Acceptance tests validate the software against the user requirements in
[1-user-requirements.md](1-user-requirements.md). They run against a release
build (the app binary and the installed Python wheel) and a real MP305B. The
user performs or witnesses each test. An agent may prepare and assist, but
never records an AT as passed on its own.

## 1. Test conditions

These apply to every AT that uses the supply, unless the test says otherwise:

- Nothing is connected to the output. Where a test needs a load, it names the
  resistor.
- Setpoints stay at 5 V or less and 100 mA or less.
- At the end of the test, including after a failure, the output is off and
  any changed device setting is restored.
- The record names the supply's application version and hardware revision,
  or points to the LOGBOOK entry that records them.

"Load A" is a 100 Ω resistor rated at least 1 W (50 mA at 5 V). "Load B" is a
22 Ω resistor rated at least 2 W; at 5 V it would draw about 230 mA, so a
100 mA limit makes the supply limit or trip.

## 2. Coverage

Status: changed, revision 10, approval pending under
[ADR-0018](../adr/0018-focused-hardware-verification.md).

`H` requires the applicable procedure on the named OS and transport, on
real hardware with the release app and installed release wheel as
applicable. The user performs or witnesses it. The actual host, adapter,
firmware, artifact hashes and observations are recorded. Native hosts or
working device pass-through are eligible. Missing hardware remains open.

`R` is permitted only for the six USB cells per OS listed below. It
requires the user-witnessed Bluetooth acceptance result for that entry
on the same OS and release artifacts, the corresponding same-transport
system evidence, and the USB hardware prerequisites listed in
[the execution plan](hardware-verification-plan.md#acceptance-evidence-reuse).
The user reviews the equivalence conclusion. Record it as acceptance by
analysis, not as a witnessed USB execution. No development-build ST run
is substituted for a release-build acceptance observation.

`I` retains the existing inspection. Inspect each relevant installed
artifact where packaging can differ. `n/a` means the transport does not
apply. A Bluetooth-specific step remains Bluetooth-specific inside an
otherwise shared entry; `H` in a USB column requires its applicable USB
steps, not a Bluetooth bind on USB.

| AT | macOS BLE | macOS USB | Linux BLE | Linux USB | Windows BLE | Windows USB |
|---|---|---|---|---|---|---|
| AT-001 | H | H | H | H | H | H |
| AT-002 | H | H | H | H | H | H |
| AT-003 | H | R | H | R | H | R |
| AT-004 | H | H | H | H | H | H |
| AT-005 | H | H | H | H | H | H |
| AT-006 | H | H | H | H | H | H |
| AT-007 | H | H | H | H | H | H |
| AT-008 | H | H | H | H | H | H |
| AT-009 | H | H | H | H | H | H |
| AT-010 | H | H | H | H | H | H |
| AT-011 | H | H | H | H | H | H |
| AT-012 | H | R | H | R | H | R |
| AT-013 | H | R | H | R | H | R |
| AT-014 | H | R | H | R | H | R |
| AT-015 | H | H | H | H | H | H |
| AT-016 | H | H | H | H | H | H |
| AT-017 | H | R | H | R | H | R |
| AT-018 | H | H | H | H | H | H |
| AT-019 | I | I | I | I | I | I |
| AT-020 | H | H | H | H | H | H |
| AT-021 | I | I | I | I | I | I |
| AT-023 | H | H | H | H | H | H |
| AT-024 | H | H | H | H | H | H |
| AT-025 | I | I | I | I | I | I |
| AT-026 | H | H | H | H | H | H |
| AT-027 | H | n/a | H | n/a | H | n/a |
| AT-028 | H | H | H | H | H | H |
| AT-029 | H | R | H | R | H | R |
| AT-030 | H | H | H | H | H | H |
| AT-031 | I | I | I | I | I | I |
| AT-032 | H | n/a | H | n/a | H | n/a |
| AT-033 | I | I | I | I | I | I |
| AT-034 | H | H | H | H | H | H |
| AT-035 | n/a | H | n/a | H | n/a | H |
| AT-036 | H | H | H | H | H | H |
| AT-037 | H | H | H | H | H | H |

AT-027 remains Bluetooth-only. USB ownership and interference are covered
by the system tests, including ST-043.

## 3. Test specifications

The Method column says who runs the test and how: "manual" means the user
follows the steps with the app or a short Python session; "script" means an
automated test in `tests/acceptance/` that the user starts and watches.

| AT | Verifies | Procedure | Expected result | Method | Status |
|---|---|---|---|---|---|
| AT-001 | UR-001 | 1. Start the app and connect over Bluetooth; confirm on the supply. 2. Disconnect. 3. Connect a USB cable and connect over USB. 4. Repeat steps 1 to 3 with the Python library. | Every connection succeeds and shows live readings. | manual | approved (prior baseline) |
| AT-002 | UR-002 | 1. Search for supplies with the app and with `mp305` while the supply is on. 2. Compare the unit identifier shown with the last three characters of the name on the supply's Web Link screen or in a Bluetooth scanner. 3. Connect by the identifier shown. 4. If a second MP305B is available, repeat with both on. | Each supply is listed with its own identifier, and over Bluetooth it is the three trailing name characters. The software connects only to the one chosen. With two supplies found, the library refuses to connect without an identifier. Without a second unit, step 4 is recorded as not run and ST-004 (mock transport) is cited instead. | manual | approved (prior baseline) |
| AT-003 | UR-003 | 1. With the library, set 5.00 V and 0.100 A. 2. Read a measurement. 3. Compare the supply's screen. | The library takes and returns floats in V and A (5.0, 0.1). The screen shows 5.00 V and 0.100 A. No raw values appear in the API. | script (`tests/acceptance/test_units.py`) | changed (rev 10, approval pending) |
| AT-004 | UR-004 | 1. On the front panel, set 3.00 V and 0.050 A, output off. 2. Connect the app. 3. Look before touching any control. | The app shows 3.00 V, 0.050 A, output off, DC mode, no fault and the supply's versions before any control is enabled. The supply's setpoints are unchanged. | manual | approved (prior baseline) |
| AT-005 | UR-005 | 1. Connect the app, output off. 2. Change the voltage to 4.00 V. 3. Start and stop a CSV recording. 4. Press "Output on". | The output stays off through steps 2 and 3 and switches on only at step 4. | manual | approved (prior baseline) |
| AT-006 | UR-006 | 1. Load A on the output, 5.00 V, 0.100 A, output on from the app. 2. Press "Output off"; the app's log shows the time from the press to the supply's acknowledgment. 3. Repeat with `psu.output_off()` in Python, which returns after the acknowledgment. 4. Watch the voltage on the app or a meter. | The supply acknowledges within 0.5 s in both cases, and the measured voltage falls to about 0 V right after. | manual | approved (prior baseline) |
| AT-007 | UR-007 | 1. Set the software limits to 4.0 V and 0.050 A in the app. 2. Enter 4.5 V. 3. Repeat in Python with `set_limits` and `set_voltage(4.5)`. | The app refuses the value and the library raises its out-of-range exception. The supply's setpoint does not change. | script (`tests/acceptance/test_limits.py`) plus manual app step | approved (prior baseline) |
| AT-008 | UR-008 | 1. Clear the software's remembered host ID (fresh installation state) and connect the app over Bluetooth. 2. While the prompt is on the supply's screen, check what the app shows. 3. Press deny. 4. Repeat with the library. 5. Connect once more and press nothing for 35 s. | While waiting, the app says to confirm on the supply within 30 seconds. After a deny, the app reports it and disconnects without showing readings; the library raises its connection-denied exception. In step 5 the software reports a timeout naming the 30 s bound and the record notes whether the supply dropped the link first (TBD-008). | manual | approved (prior baseline) |
| AT-009 | UR-009 | 1. On the front panel, select OCP mode instead of CC. 2. Set 5.00 V, 0.100 A. 3. Connect Load B. 4. Switch the output on from the app, then from Python. | Current rises above 100 mA (about 230 mA) only until the trip, after the OCP delay (50 ms as read on 2026-09-29, unchecked). The expected result depends on TBD-016 and is inferred until then. The supply trips. The app names the fault (over-current) within one update. The library reports it in the next reading. The output is off afterwards. Restore CC mode. | manual | approved (prior baseline) |
| AT-010 | UR-010 | 1. Open the app and search over Bluetooth, then with the USB cable connected. | The list shows name, unit identifier, transport and signal strength for each supply found; the Bluetooth entry's unit identifier is the three trailing name characters, the USB entry's is the device path. | manual | approved (prior baseline) |
| AT-011 | UR-011 | 1. Load A, 5.00 V, 0.100 A, output on. 2. Watch the readout for 30 s. | Voltage, current, power, setpoints, output state and CV mode are shown and change at least twice per second. | manual | approved (prior baseline) |
| AT-012 | UR-012 | 1. Enter -1, 35 and 31 as voltage. 2. Enter 6 as current limit. 3. With the output off and nothing connected, enter 29.99 V and apply it. 4. Set 5.00 V again. | Out-of-range values are marked and never sent. 29.99 V is accepted and the supply's screen shows it. The upper range edge can only be checked above 5 V; the output stays off and nothing is connected throughout. The range itself is TBD-003. | manual | changed (rev 10, approval pending) |
| AT-013 | UR-013 | 1. Load A, output on for 20 s, then off. | The chart scrolls and shows voltage, current and power, including the step when the output goes off. | manual | changed (rev 10, approval pending) |
| AT-014 | UR-014 | 1. Start a recording. 2. Switch Load A on and off over 10 s. 3. Stop. 4. Open the file. | The CSV has a header with units and a row per reading with time, voltage, current, power, output state and mode. The on and off steps are visible. | manual | changed (rev 10, approval pending) |
| AT-015 | UR-015 | 1. Run a script that finds the supply, connects, sets 5 V and 0.1 A, switches the output on and off, and reads measurements, with plain function calls. | The script runs top to bottom without asyncio and finishes with the output off. | script (`tests/acceptance/test_python_api.py`) | approved (prior baseline) |
| AT-016 | UR-016 | 1. `set_voltage` above the range. 2. Connect with a fresh host ID and press deny. 3. Connect with a fresh host ID and press nothing. 4. Over Bluetooth, call `set_voltage(1.0)` and press deny on the remote-control prompt. 5. Switch off the supply while connected, then make a call. 6. Search with the supply switched off. | 1 `SetpointRangeError`, 2 `ConnectionDeniedError`, 3 `Mp305TimeoutError`, 4 `RemoteControlDeniedError`, 5 `LinkLostError`, 6 `NotFoundError`. A command the supply rejects cannot be caused on demand with a real supply; ST-023 covers it with the mock transport. | script (`tests/acceptance/test_python_errors.py`) with manual steps 2 to 5 | approved (prior baseline) |
| AT-017 | UR-017 | 1. Load A, 5 V, 0.1 A, output on. 2. Read a measurement and inspect it. | The object has float voltage, current and power in V, A and W, the output state, the regulation mode and the list of active faults. | script (`tests/acceptance/test_python_telemetry.py`) | changed (rev 10, approval pending) |
| AT-018 | UR-018 | 1. Run `with` block that switches the output on and ends normally. 2. Run one that raises inside the block. | In both cases the output is off afterwards and the supply is no longer under remote control. | script (`tests/acceptance/test_context_manager.py`) | approved (prior baseline) |
| AT-019 | UR-019 | Inspect the Cargo workspace and the dependencies of `mp305-app` and `mp305-py`. | Both depend on `mp305-core`. Neither contains protocol encoding or decoding of its own. | inspection | approved (prior baseline) |
| AT-020 | UR-020 | 1. Inspect `mp305-app`'s dependencies. 2. Start the release app on each OS in the coverage table and connect. | The app uses egui and runs on each OS tested. | inspection plus manual | approved (prior baseline) |
| AT-021 | UR-021 | Inspect `crates/mp305-py/Cargo.toml` and the wheel. | The extension is built with PyO3 on `mp305-core`. | inspection | approved (prior baseline) |
| AT-023 | UR-023 | 1. Connect the app, 3.00 V, 0.050 A, output off. 2. Release remote control in the app if held. 3. On the front panel, change the voltage to 4.00 V and observe it in the app. 4. Request control again in the app; over Bluetooth allow the prompt. 5. Change the current limit in the app to 0.080 A. | The supply ends at 4.00 V, 0.080 A, output off. The front panel change survived. | manual | changed (rev 10, approval pending) |
| AT-024 | UR-024 | 0. Automatic reconnection off. 1. 5.00 V, 0.100 A, no load, output on from the app. 2. Break the link: switch off Bluetooth on the host, or pull the USB cable. 3. Wait 30 s. 4. Check the supply's screen for the output state and the remote-control marker, then switch the output off on the front panel. | Within 4 s the app says that the link is lost, that the output is still in its last state and that the supply has released remote control. It sends nothing and does not reconnect by itself. The record notes what the supply's screen showed (TBD-005: the firmware keeps the output on and drops the remote marker). | manual | approved (prior baseline) |
| AT-025 | UR-025 | Search the code for firmware update functions and for use of the `FEE0` service. | None found. | inspection | approved (prior baseline) |
| AT-026 | UR-026 | 1. Connect with the app and with the library, over Bluetooth and over USB. 2. Compare with the supply's information screen. | Model, application version and hardware revision match on both transports. The USB layout is recorded for TBD-010. | manual | approved (prior baseline) |
| AT-027 | UR-027 | 1. Connect WebLink in Chrome to the supply over Bluetooth. 2. Search with the app and with the library. 3. Disconnect WebLink, disable remote control on the supply's screen, search again. | In both cases the app and the library report that no supply was found and list the possible reasons: off or out of range, another app connected, a USB host active, remote control disabled on the supply. Restore remote control. | manual | approved (prior baseline) |
| AT-028 | UR-028 | 1. Load A, 5 V, 0.1 A, output on. 2. Stream readings at 2 per second for 60 s to a CSV file with the helper. 3. Open the file. | About 120 rows (at least 110), each with time, voltage, current and power in V, A and W. | script (`tests/acceptance/test_python_logging.py`) | approved (prior baseline) |
| AT-029 | UR-029 | 1. No load, 0.100 A. 2. Ramp from 1 V to 5 V in 1 V steps, 1 s each, while logging. | The logged setpoints step 1, 2, 3, 4, 5 V at about 1 s intervals. The ramp stops at 5 V. | script (`tests/acceptance/test_python_ramp.py`) | changed (rev 10, approval pending) |
| AT-030 | UR-030 | 1. Connect, 5.00 V, 0.100 A, nothing on the output, output on. 2. Kill the process (for example `kill -9`, or close the laptop lid until the link drops). 3. Start the software again and connect to the same supply. 4. Switch the output off. | On the restart the software warns, before any control, that the previous session may have left the output on, naming the supply. Nothing is connected throughout. | manual | approved (prior baseline) |
| AT-031 | UR-031 | Read the README of the app and of the library. | Both carry the unattended-run bench-safety note (front-panel current limit and OCP, safe load, the output stays on when the link drops, prefer USB for unattended runs). | inspection | approved (prior baseline) |
| AT-032 | UR-032 | 1. Clear the remembered host ID, connect over Bluetooth with the app, press allow, disconnect. 2. Connect again and watch the supply's screen. 3. Repeat steps 1 and 2 with the library. | On the second connection no prompt appears, the software connects within 5 s and tells the user the supply recognised it. The record settles TBD-006. | manual | approved (prior baseline) |
| AT-033 | UR-033 | 1. Inspect the transport's allowlist and never-send list in the code. 2. Read the frame log of AT-015. | Only `0x18`, `0xE0`, `0xC2` and `0xC8` can be sent; the never-send list names `0x10`, `0xC0`, `0xBE`, `0x20`, `0xF0` to `0xFE` with reasons; the log contains only allowed requests. | inspection | approved (prior baseline) |
| AT-034 | UR-034 | 1. Connect the app, output off. 2. Release remote control in the app if held, then change the ramp step setting on the front panel. 3. In the app, check the settings display. 4. Run the library's mock-transport test that injects a `0xC5` and a late `0xC9`. | The app shows the new ramp step without any action in the app (TBD-018). The mock test passes: the injected frames are reported as events and never taken as the reply to another request. | manual plus script (`tests/acceptance/test_unsolicited.py`) | changed (rev 10, approval pending) |
| AT-035 | UR-035 | 1. Connect over USB with the library, take remote control by setting 1.00 V. 2. Wait 20 s without any call. 3. Set 1.50 V. | Step 3 is accepted at once; the supply did not release remote control, and its screen kept the remote marker throughout. | script (`tests/acceptance/test_usb_keepalive.py`) with the user watching the screen | approved (prior baseline) |
| AT-036 | UR-036 | 1. Connect the app over Bluetooth, then change the voltage. 2. While the supply shows "Allow Remote Control", check what the app shows. 3. Press allow. 4. Repeat and press deny. 5. Repeat over USB. | Over Bluetooth the app says to allow remote control on the supply; after allow the change is applied, after deny the app reports the refusal and keeps the controls disabled until the user asks again. Over USB no prompt appears and the change is applied at once (TBD-004, TBD-012). | manual | approved (prior baseline) |
| AT-037 | UR-037 | 1. In the app, enable automatic reconnection for the session, connect to the supply (with a remembered host over Bluetooth), 5.00 V, 0.100 A, nothing on the output, output on. 2. On the tested OS, switch Bluetooth off for 20 s and on again, or unplug and re-plug USB for the USB run. 3. Watch the app and supply. 4. Change the voltage in the app. 5. Repeat with reconnection disabled. | 1 to 4: the app reports the loss, reconnects by itself without a bind prompt, shows fresh readings, and the output state is unchanged; the remote marker returns only at step 4 when control is requested again (a remote-control prompt over Bluetooth, no prompt over USB). 5: the app stays disconnected and offers the reconnect button. | manual | changed (rev 10, approval pending) |


## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | Initial draft of acceptance test specification for G1 | not yet approved |
| 2 | 2026-09-29 | Matched UR revision 2: added test conditions (5 V, 100 mA, named loads), a safe fault procedure for AT-009 using OCP mode and a resistor, AT-023 to AT-029, and a coverage table that shows real hardware per OS and transport instead of mock runs. Removed claims the protocol does not support (serial number in AT-001, 200 ms in AT-006). | not yet approved |
| 3 | 2026-09-29 | Matched UR revision 3: AT-006 at 0.5 s to acknowledgment, AT-008 disconnect after a deny, coverage table with CI instead of HW? for Linux and Windows. | not yet approved |
| 4 | 2026-09-29 | Independent review findings: AT-012 edge check with output off, AT-016 maps each exception, AT-009 depends on TBD-016, AT-024 timing matches SR-028, AT-002 substitute named. | not yet approved |
| 5 | 2026-09-29 | TBD-015 mitigations: AT-030 (unclean-exit warning) and AT-031 (bench note in the docs) added. | not yet approved |
| 6 | 2026-09-29 | AT-022 withdrawn with UR-022. | not yet approved |
| 7 | 2026-09-30 | Editorial: the CI coverage note states the Linux and Windows gap directly. No test procedure changed. | not yet approved |
| 8 | 2026-09-30 | Matched UR revision 8: AT-002, AT-004, AT-008, AT-010, AT-016, AT-024, AT-026, AT-027, AT-031 rewritten; AT-032 to AT-036 added for UR-032 to UR-036; coverage table with the VM code for Parallels (TBD-009). | not yet approved |
| 9 | 2026-09-30 | AT-037 for UR-037 (automatic reconnection); AT-024 and AT-031 match the TBD-017 decision. | user, 2026-09-30 (G1) |
| 10 | 2026-10-04 | Conditional same-OS release evidence reuse for USB AT-003, AT-012, AT-013, AT-014, AT-017 and AT-029. Correct front-panel preparation in AT-023 and AT-034; make AT-037 explicit for the tested OS and USB. Keep witnessed release hardware results for every other applicable cell. ADR-0018 and the execution plan define reuse and combined ST/AT evidence. | pending user approval |
