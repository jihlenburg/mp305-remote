# 8. Acceptance test specification (AT)

Status: draft

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

| Code | Meaning |
|---|---|
| HW | Run on the user's MP305B from this OS and transport |
| CI | No hardware for this OS (TBD-009, settled: Mac only). Covered only by CI builds and mock-transport tests, plus user reports if any arrive. That gap is accepted or rejected at G1. |
| n/a | The requirement does not apply to this transport |
| I | Inspection, independent of OS and transport |

| AT | macOS BLE | macOS USB | Linux BLE | Linux USB | Windows BLE | Windows USB |
|---|---|---|---|---|---|---|
| AT-001 | HW | HW | CI | CI | CI | CI |
| AT-002 | HW | HW | CI | CI | CI | CI |
| AT-003 | HW | HW | CI | CI | CI | CI |
| AT-004 | HW | HW | CI | CI | CI | CI |
| AT-005 | HW | HW | CI | CI | CI | CI |
| AT-006 | HW | HW | CI | CI | CI | CI |
| AT-007 | HW | HW | CI | CI | CI | CI |
| AT-008 | HW | HW (TBD-004) | CI | CI (TBD-004) | CI | CI (TBD-004) |
| AT-009 | HW | HW | CI | CI | CI | CI |
| AT-010 | HW | HW | CI | CI | CI | CI |
| AT-011 | HW | HW | CI | CI | CI | CI |
| AT-012 | HW | HW | CI | CI | CI | CI |
| AT-013 | HW | HW | CI | CI | CI | CI |
| AT-014 | HW | HW | CI | CI | CI | CI |
| AT-015 | HW | HW | CI | CI | CI | CI |
| AT-016 | HW | HW | CI | CI | CI | CI |
| AT-017 | HW | HW | CI | CI | CI | CI |
| AT-018 | HW | HW | CI | CI | CI | CI |
| AT-019 | I | I | I | I | I | I |
| AT-020 | HW | HW | CI | CI | CI | CI |
| AT-021 | I | I | I | I | I | I |
| AT-023 | HW | HW | CI | CI | CI | CI |
| AT-024 | HW | HW | CI | CI | CI | CI |
| AT-025 | I | I | I | I | I | I |
| AT-026 | HW | HW | CI | CI | CI | CI |
| AT-027 | HW | n/a | CI | n/a | CI | n/a |
| AT-028 | HW | HW | CI | CI | CI | CI |
| AT-029 | HW | HW | CI | CI | CI | CI |
| AT-030 | HW | HW | CI | CI | CI | CI |
| AT-031 | I | I | I | I | I | I |

AT-027 is Bluetooth only: a USB device cannot be held by another app in the
same way. Whether it can, and what the software then reports, is a system
test question.

## 3. Test specifications

The Method column says who runs the test and how: "manual" means the user
follows the steps with the app or a short Python session; "script" means an
automated test in `tests/acceptance/` that the user starts and watches.

| AT | Verifies | Procedure | Expected result | Method |
|---|---|---|---|---|
| AT-001 | UR-001 | 1. Start the app and connect over Bluetooth; confirm on the supply. 2. Disconnect. 3. Connect a USB cable and connect over USB. 4. Repeat steps 1 to 3 with the Python library. | Every connection succeeds and shows live readings. | manual |
| AT-002 | UR-002 | 1. Search for supplies with the app and with `mp305` while the supply is on. 2. Connect by the identifier shown. 3. If a second MP305B is available, repeat with both on. | Each supply is listed with its own identifier. The software connects only to the one chosen. With two supplies found, the library refuses to connect without an identifier. Without a second unit, step 3 is recorded as not run and ST-004 (mock transport) is cited instead. | manual |
| AT-003 | UR-003 | 1. With the library, set 5.00 V and 0.100 A. 2. Read a measurement. 3. Compare the supply's screen. | The library takes and returns floats in V and A (5.0, 0.1). The screen shows 5.00 V and 0.100 A. No raw values appear in the API. | script (`tests/acceptance/test_units.py`) |
| AT-004 | UR-004 | 1. On the front panel, set 3.00 V and 0.050 A, output off. 2. Connect the app. 3. Look before touching any control. | The app shows 3.00 V, 0.050 A, output off and no fault before any control is enabled. The supply's setpoints are unchanged. | manual |
| AT-005 | UR-005 | 1. Connect the app, output off. 2. Change the voltage to 4.00 V. 3. Start and stop a CSV recording. 4. Press "Output on". | The output stays off through steps 2 and 3 and switches on only at step 4. | manual |
| AT-006 | UR-006 | 1. Load A on the output, 5.00 V, 0.100 A, output on from the app. 2. Press "Output off"; the app's log shows the time from the press to the supply's acknowledgment. 3. Repeat with `psu.output_off()` in Python, which returns after the acknowledgment. 4. Watch the voltage on the app or a meter. | The supply acknowledges within 0.5 s in both cases, and the measured voltage falls to about 0 V right after. | manual |
| AT-007 | UR-007 | 1. Set the software limits to 4.0 V and 0.050 A in the app. 2. Enter 4.5 V. 3. Repeat in Python with `set_limits` and `set_voltage(4.5)`. | The app refuses the value and the library raises its out-of-range exception. The supply's setpoint does not change. | script (`tests/acceptance/test_limits.py`) plus manual app step |
| AT-008 | UR-008 | 1. Connect the app over Bluetooth. 2. While the prompt is on the supply's screen, check what the app shows. 3. Press deny. 4. Repeat with the library. 5. Repeat over USB. | While waiting, the app says to confirm on the supply. After a deny, the app reports it and disconnects without showing readings; the library raises its connection-denied exception. The USB result is recorded as TBD-004 settles it. | manual |
| AT-009 | UR-009 | 1. On the front panel, select OCP mode instead of CC. 2. Set 5.00 V, 0.100 A. 3. Connect Load B. 4. Switch the output on from the app, then from Python. | Current rises above 100 mA (about 230 mA) only until the trip, after the OCP delay (50 ms as read on 2026-09-29, unchecked). The expected result depends on TBD-016 and is inferred until then. The supply trips. The app names the fault (over-current) within one update. The library reports it in the next reading. The output is off afterwards. Restore CC mode. | manual |
| AT-010 | UR-010 | 1. Open the app and search. | The list shows name, identifier and signal strength for each supply found. | manual |
| AT-011 | UR-011 | 1. Load A, 5.00 V, 0.100 A, output on. 2. Watch the readout for 30 s. | Voltage, current, power, setpoints, output state and CV mode are shown and change at least twice per second. | manual |
| AT-012 | UR-012 | 1. Enter -1, 35 and 31 as voltage. 2. Enter 6 as current limit. 3. With the output off and nothing connected, enter 29.99 V and apply it. 4. Set 5.00 V again. | Out-of-range values are marked and never sent. 29.99 V is accepted and the supply's screen shows it. The upper range edge can only be checked above 5 V; the output stays off and nothing is connected throughout. The range itself is TBD-003. | manual |
| AT-013 | UR-013 | 1. Load A, output on for 20 s, then off. | The chart scrolls and shows voltage, current and power, including the step when the output goes off. | manual |
| AT-014 | UR-014 | 1. Start a recording. 2. Switch Load A on and off over 10 s. 3. Stop. 4. Open the file. | The CSV has a header with units and a row per reading with time, voltage, current, power, output state and mode. The on and off steps are visible. | manual |
| AT-015 | UR-015 | 1. Run a script that finds the supply, connects, sets 5 V and 0.1 A, switches the output on and off, and reads measurements, with plain function calls. | The script runs top to bottom without asyncio and finishes with the output off. | script (`tests/acceptance/test_python_api.py`) |
| AT-016 | UR-016 | 1. `set_voltage` above the range. 2. Connect and press deny. 3. Connect with a 10 s bind timeout and press nothing. 4. Switch off the supply while connected, then make a call. 5. Search with the supply switched off. | 1 `SetpointRangeError`, 2 `ConnectionDeniedError`, 3 `Mp305TimeoutError`, 4 `LinkLostError`, 5 `NotFoundError`. A command the supply rejects cannot be caused on demand with a real supply; ST-023 covers it with the mock transport. | script (`tests/acceptance/test_python_errors.py`) with manual steps 2 and 4 |
| AT-017 | UR-017 | 1. Load A, 5 V, 0.1 A, output on. 2. Read a measurement and inspect it. | The object has float voltage, current and power in V, A and W, the output state, the regulation mode and the list of active faults. | script (`tests/acceptance/test_python_telemetry.py`) |
| AT-018 | UR-018 | 1. Run `with` block that switches the output on and ends normally. 2. Run one that raises inside the block. | In both cases the output is off afterwards and the supply is no longer under remote control. | script (`tests/acceptance/test_context_manager.py`) |
| AT-019 | UR-019 | Inspect the Cargo workspace and the dependencies of `mp305-app` and `mp305-py`. | Both depend on `mp305-core`. Neither contains protocol encoding or decoding of its own. | inspection |
| AT-020 | UR-020 | 1. Inspect `mp305-app`'s dependencies. 2. Start the release app on each OS in the coverage table and connect. | The app uses egui and runs on each OS tested. | inspection plus manual |
| AT-021 | UR-021 | Inspect `crates/mp305-py/Cargo.toml` and the wheel. | The extension is built with PyO3 on `mp305-core`. | inspection |
| AT-023 | UR-023 | 1. Connect the app, 3.00 V, 0.050 A, output off. 2. On the front panel, change the voltage to 4.00 V. 3. In the app, change the current limit to 0.080 A. | The supply ends at 4.00 V, 0.080 A, output off. The front panel change survived. | manual |
| AT-024 | UR-024 | 1. 5.00 V, 0.100 A, no load, output on from the app. 2. Break the link: switch off Bluetooth on the host, or pull the USB cable. 3. Wait 30 s. 4. Check the supply's screen, then switch the output off on the front panel. | Within 4 s the app says that the link is lost and the output may still be on. It sends nothing and does not reconnect by itself. The record notes what the supply did with the output (input for TBD-005). | manual |
| AT-025 | UR-025 | Search the code for firmware update functions and for use of the `FEE0` service. | None found. | inspection |
| AT-026 | UR-026 | 1. Connect with the app and with the library. 2. Compare with WebLink or the supply's information screen. | Model, application version and hardware revision match. | manual |
| AT-027 | UR-027 | 1. Connect WebLink in Chrome to the supply over Bluetooth. 2. Search with the app and with the library. | The app and the library report that no supply was found and name another app holding the connection as a possible reason. | manual |
| AT-028 | UR-028 | 1. Load A, 5 V, 0.1 A, output on. 2. Stream readings at 2 per second for 60 s to a CSV file with the helper. 3. Open the file. | About 120 rows (at least 110), each with time, voltage, current and power in V, A and W. | script (`tests/acceptance/test_python_logging.py`) |
| AT-029 | UR-029 | 1. No load, 0.100 A. 2. Ramp from 1 V to 5 V in 1 V steps, 1 s each, while logging. | The logged setpoints step 1, 2, 3, 4, 5 V at about 1 s intervals. The ramp stops at 5 V. | script (`tests/acceptance/test_python_ramp.py`) |
| AT-030 | UR-030 | 1. Connect, 5.00 V, 0.100 A, nothing on the output, output on. 2. Kill the process (for example `kill -9`, or close the laptop lid until the link drops). 3. Start the software again and connect to the same supply. 4. Switch the output off. | On the restart the software warns, before any control, that the previous session may have left the output on, naming the supply. Nothing is connected throughout. | manual |
| AT-031 | UR-031 | Read the README of the app and of the library. | Both carry the unattended-run bench-safety note (front-panel current limit and OCP, safe load, prefer USB). | inspection |

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
