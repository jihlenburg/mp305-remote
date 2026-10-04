# Verification record: person-assisted system tests on macOS over Bluetooth

Date: 2026-10-04 local time. Level: system. Scope: remaining
person-assisted entries over Bluetooth, with the user at the supply.
These entries require nothing connected to the output. A later load
disclosure was clarified by the user: the LED was connected after the
tests. The bench clarification and subsequent disconnection confirmations
are recorded below.

Commit: uncommitted, based on `6f985e03714a334d9776183a4822110063eaf5d0`.
The Rust core and Python library were rebuilt from that commit's production
code with `env -u CONDA_PREFIX uv run maturin develop -m
crates/mp305-py/Cargo.toml`. Existing uncommitted changes comprise the
proposed ADR-0017 and the related architecture, design, integration test
specification and traceability edits, plus a system-test pre-flight change
that waits for background closure after an unanswered connection prompt.
That exception path has not been exercised by the runs below. This session
also adds task tracking and verification records. The proposed design
changes are not implemented or re-verified here.

OS: macOS 27.0.1, Darwin 27.0.0, arm64. CPython 3.10.19, pytest 9.1.1.
Transport: Bluetooth LE through the Mac's built-in adapter. Unit:
`72de66a3-7c9b-58a3-a45b-cf098194d568`.

The user confirmed DC mode, CC selected, output off, nothing connected to
the output, remote control enabled and no other app connected. Every run
uses the HIL safety fixtures and default user limits of 5 V and 0.1 A.
The original setpoints may be higher; the fixtures restore them only with
the output confirmed off.

## Commands

For each run below, `<record>` is its JSON filename and `<test>` is its
pytest node ID:

```sh
env -u MP305_HIL_LOAD -u MP305_HIL_DEVICE_HID \
  MP305_HIL=1 \
  MP305_HIL_DEVICE=72de66a3-7c9b-58a3-a45b-cf098194d568 \
  MP305_HIL_PERSON=1 MP305_HIL_RECORD=<record> \
  uv run --no-sync pytest <test> -m hil -s -rs -v
```

## ST-012: reported values against the supply's screens

Node ID:
`tests/system/test_readings.py::test_st012_reported_values_match_the_supply_screens`.

First attempt, 02:27:03 to 02:27:23: setup failed. The discovery fixture
found the supply, but the pre-flight connection's scan did not see it
within 10 s and raised `NotFoundError`. No connection completed and the
screen comparison did not run. JSON:
`2026-10-04T022703-system-macos-ble-st012.json`.

The retry, 02:27:47 to 02:29:16, passed. The pre-flight read the output
off, System Version 1.6.0.51, hardware revision 2.0.2.0, model MP305B, DC
mode and setpoints 12.00 V and 0.500 A. The user confirmed that all the
reported values matched the supply's screens, and that answer was passed
to the test. Setup, call and teardown passed. JSON:
`2026-10-04T022747-system-macos-ble-st012.json`.

The earlier pre-flight failure remains recorded and is not a passing
connection result. ST-012's early-control-call case passed in the
2026-10-03 batch record; this run completes the screen-comparison case
over macOS Bluetooth.

## ST-019: front-panel voltage change followed by a current command

Node ID:
`tests/system/test_control.py::test_st019_a_command_copies_the_front_panel_change`.
Run: 02:29:38 to 02:31:15. Result: failed in the test call and error in
teardown. JSON: `2026-10-04T022938-system-macos-ble-st019.json`.

The pre-flight confirmed the original 12.00 V and 0.500 A setpoints,
output off and the same versions as ST-012. The remote-control request
was allowed at 02:30:00.341. The test set 3.00 V and 0.050 A and sent
output-off; every command received `C9 00`. It then asked the user to
change the voltage to 4.00 V on the front panel.

The user reported that the front panel would not let settings be changed
while remote control was active and asked whether to disable remote
control. The kept frame log shows:

| Local time | Observation |
|---|---|
| 02:31:01.135 and 02:31:01.181 | Unsolicited `C9 01`, both logged as late replies and ignored by the session |
| 02:31:05.867 | `C3` reports 4.00 V, 0.050 A and output off |
| 02:31:05.872 | `C8 01 90 01 50 00 01 00 00 00 00 00`: active command, 4.00 V, 0.080 A, output off |
| 02:31:05.998 | `C9 01`; the session changes from granted to lost and returns `RemoteControlLostError` |

The outgoing command preserved the front-panel voltage, but the supply
did not apply it because the grant was gone. All 308 stored readings show
output off; the final stored reading is 4.00 V and 0.050 A. This does not
make ST-019 pass: its call raised instead of completing the approved
procedure.

At teardown the first restoration attempt failed with
`RemoteControlLostError`. The guard attempted a recovery connection and
printed an Allow prompt, but retained the restoration error and the test
ended with a teardown failure. The frame-log fixture ended before the
guard's teardown, so the stored frame log cannot establish the final
restored setpoints. The user was asked to keep the output off and restore
12.00 V and 0.500 A. Before the next run the user confirmed the output
off and then the original setpoints restored.

The JSON report retains the teardown exception in its single `reason`
field, replacing the call exception; the call's rejected command is
preserved in its frame log. Both failures are recorded here.

At the user's request the firmware UI path was reviewed. It blocks
ordinary front-panel actions during a remote grant, allows the user to
disable the grant, and rejects subsequent active commands with `C9 01`.
The detailed evidence is in
[the UI research](../../research/device/ui-and-analog.md#front-panel-controls-while-remote-control-is-granted).
The approved ST-019 procedure needs review; no specification or production
code was changed to turn this failure into a pass. ST-023 step 2 is the
existing test of front-panel revocation and remains to be run separately.

## Test-log lifetime correction after ST-019

The `supply` fixture now explicitly depends on `frame_log`, so the guard
finishes output-off, restoration and close before the log is stopped.
This changes evidence retention, not the expected result or device
commands. `ruff check tests/system/conftest.py` passes; pytest
`--setup-plan` for the ST-019 node confirms `TEARDOWN F supply` before
`TEARDOWN F frame_log`. The subsequent ST-023 run below verifies the
retained restoration and release exchanges on hardware.

## Preparation for ST-023 step 2

The user confirmed output off and the original 12.00 V and 0.500 A
setpoints restored. Before ST-023 the teardown helper was changed to
call `request_remote_control()` explicitly when restoration finds the
session in `lost` or `denied` remote state. After the grant it reads again
and refuses restoration unless the output is still off and the mode DC.
This implements the existing HIL restoration rule with the approved API;
the ST-023 procedure and its expected exception are unchanged.

A mock exercise produced the command selectors `2, 1, 2, 1, 1`: initial
grant, rejected command, new grant, restored voltage and restored current.
Every command kept output zero. The existing three non-HIL ST-023 cases
passed with `uv run --no-sync pytest tests/system/test_control.py -k st023 -q`.
Lint passed. The JSON recorder now also keeps each phase under `phases`,
so a teardown failure cannot erase the call failure's reason; a synthetic
report check retained both reasons and counted the failed test once.

The hardware command for ST-023 adds `--show-capture=no --tb=short` to
the command template above. These options shorten terminal errors; the
JSON file retains the captured frame log.

## ST-023 step 2: remote control revoked on the front panel

Node ID:
`tests/system/test_control.py::test_st023_step2_remote_control_taken_away_on_the_front_panel`.
Run: 02:42:16 to 02:44:08. Result: pass, including setup and teardown.
JSON: `2026-10-04T024216-system-macos-ble-st023.json`.

The pre-flight confirmed 12.00 V, 0.500 A, output off and the same
versions as ST-012. After the user allowed remote control, the test set
1.00 V. The user then confirmed disabling remote control on the front
panel. The supply sent two unsolicited `C9 01` replies at 02:43:37.718
and 02:43:37.808. The test's next request, 1.50 V, received `C9 01` at
02:44:01.207 and raised the required `RemoteControlLostError`.

Teardown explicitly requested control again. The user allowed it; the
guard restored 12.00 V and closed with the release acknowledged. The
last reading, at 02:44:08.137, confirms 12.00 V, 0.500 A and output off.
Every retained reading shows output off. This confirms on hardware that
the front panel can revoke control (TBD-012) and that the teardown fix
recovers from the resulting lost grant. ST-023 step 1 and its mock cases
are recorded separately; this run covers step 2.

The non-HIL system suite also passed after the fixture changes:
`uv run --no-sync pytest tests/system -q`, 19 passed, one skipped and
52 HIL cases deselected. This is a regression check, not an additional
hardware verification run.

## ST-048: denial and an interrupted timeout case

Command: the template above with `tests/system/test_control.py -k st048`
as the selection and `-x --show-capture=no --tb=short` added. Run:
02:45:25 to 02:46:07. JSON:
`2026-10-04T024524-system-macos-ble-st048.json`.

| Automated case | Result | Interpretation |
|---|---|---|
| `test_st048_run1_a_denied_remote_control_request` | pass, including teardown | The request was denied, with `C9 01`, and raised `RemoteControlDeniedError` |
| `test_st048_run2_no_answer_is_a_denial_within_70_s` | fail; teardown reported pass | The user reported pressing the wrong button. `C9 00` arrived, so the test cannot verify the unanswered-prompt timeout |
| `test_st048_run3_nothing_is_sent_while_the_request_is_pending` | not run | `-x` stopped the run after case 2 |

All kept readings show output off. In case 2 the accepted request led to
the 1.00 V command, and the last reading, at 02:46:07.252, still shows
1.00 V and 0.500 A. The guard incorrectly reported successful teardown:
its cached reading could still show the original setpoints immediately
after an acknowledged command, so it skipped restoration. The user then
confirmed manually restoring 12.00 V and 0.500 A with output off.

The guard now always checks an open DC connection using settled readings
after its output-off step, and verifies output off, DC mode and both
setpoints after sending restoration commands. A mock exercise reproduced
the stale-value case and verified restoration; another confirmed that
an acknowledged but unapplied restoration is reported as a failure.
The non-HIL system suite passed again (19 passed, one skipped, 52
deselected), and lint passed. Expected ST results are unchanged.

## Bench clarification before the timeout retry

After the run above the user reported a 12 V, 1 W LED connected to the
output. Hardware tests were held while the cleanup changes were checked
on mocks. The user then confirmed the LED disconnected and output off
before the next run. The user was also asked whether the LED had been
connected during earlier runs, to qualify their recorded bench setup.
In a later reply to that question, the user confirmed connecting it
after the latest test. This resolves the uncertainty about a load during
the earlier ST-012, ST-019, ST-023 and ST-048 runs: the LED was connected
afterwards. The explicit disconnection confirmations above cover the
subsequent repetitions. No test outcome changes because of this
clarification.

## ST-048 timeout retry: acceptance without a reported button press

Node ID:
`tests/system/test_control.py::test_st048_run2_no_answer_is_a_denial_within_70_s`.
Command: the template above with that node and
`--show-capture=no --tb=short`. Run: 02:53:14 to 02:53:52. Result: fail;
setup and teardown passed. JSON:
`2026-10-04T025314-system-macos-ble-st048-timeout.json`.

The user had confirmed the LED disconnected and output off. Pre-flight
read DC mode, 1.00 V and 0.500 A, differing from the earlier manual
restoration confirmation. The remote request was sent at 02:53:40.810;
`C9 00` arrived at 02:53:50.347, after 9.537 s. The library then sent
the active 1.00 V command, which also received `C9 00`. The expected
`RemoteControlDeniedError` was not raised. The user initially reported
pressing nothing, but later said that the earlier button action was
uncertain (see the clarification below). This attempt remains a raw
test failure and is inconclusive for unanswered-prompt behavior.

The final reading, 02:53:51.878, is 1.00 V, 0.500 A, output off. Every
kept reading shows output off, and the release was acknowledged. The
guard preserved this run's initial values; this run does not exercise
the restoration fix with changed setpoints. The user confirmed the
screen showed 1.00 V, then manually restored 12.00 V and 0.500 A with
the LED disconnected and output off before the next retry.

The firmware paths were checked again: the pending dialog sets
`DAT_1fffab10 = 0` in `0x5F434`; generic idle dismissal calls `0x1BA58`,
which targets the Deny button; `0x5B034` clears the pending grant and
queues the denied reply in this state. The Allow callback `0x5AF88`
sets the grant. These paths do not establish the cause of this early
acceptance, and the uncertain button action prevents a firmware
conclusion. No expected result or production code was changed.

## ST-048 retry stopped before the remote request

Same timeout node and command as above. Run: 03:00:46 to 03:01:20.
JSON: `2026-10-04T030046-system-macos-ble-st048-timeout.json`.
Pre-flight confirmed DC mode, 12.00 V, 0.500 A and output off. The
test's next connection failed with `NotFoundError` after its 10 s scan.
No control frames were sent by the test and no prompt was requested.
Setup and teardown passed; the call failed before exercising ST-048.

## ST-048 repeat: prompt confirmed, restoration verified

Same timeout node and command as above. Run: 03:01:42 to 03:02:16.
JSON: `2026-10-04T030142-system-macos-ble-st048-timeout.json`.
The test failed because it received acceptance instead of denial. The
user then reported confirming the prompt. This attempt therefore does
not verify the unanswered-prompt case. Whether that clarification also
applies to the 02:53 attempt was put to the user.

Pre-flight and the first test reading confirmed 12.00 V, 0.500 A and
output off. The request at 03:02:02.527 received `C9 00` at
03:02:12.681 (10.154 s). The subsequent active command set 1.00 V.
Teardown sent the restoration to 12.00 V at 03:02:14.257 and received
`C9 00`. The final reading at 03:02:15.426 confirms 12.00 V, 0.500 A
and output off, followed by an acknowledged release. Every kept reading
shows output off. This verifies the changed-setpoint restoration fix
on hardware, despite the invalid timeout procedure.

## Clarification and coordinated ST-048 repetition

The user subsequently said that they were unsure about pressing a button
in the 02:53 attempt and requested repetition with clear instructions.
That attempt is therefore inconclusive for unanswered-prompt behavior;
the initial report of no button press is not maintained as confirmed
evidence. The raw failed result and frames are retained unchanged.
The 03:01 attempt was confirmed by the user and also cannot verify the
timeout. Neither attempt establishes acceptance without a button press.

The three cases are repeated as separate pytest invocations: press
Deny for case 1, touch nothing until completion for case 2, and wait
for an explicit Allow instruction after the test's countdown for case 3.
No test specification or expected result changes.

### Case 1: explicit denial

Node:
`tests/system/test_control.py::test_st048_run1_a_denied_remote_control_request`.
Command: the common template with that node and
`--show-capture=no --tb=short`.

The first invocation, 03:06:18 to 03:06:44, failed in the test's
connection scan after pre-flight succeeded. Pre-flight read 12.00 V,
0.500 A, DC mode and output off; no test prompt was requested. JSON:
`2026-10-04T030618-system-macos-ble-st048-deny-coordinated.json`.

The retry, 03:06:58 to 03:07:25, passed in all phases. The user was
instructed to press Deny for this case only, received another instruction
when the prompt became active, and confirmed pressing Deny. The request
at 03:07:18.697 received `C9 01` at 03:07:22.685 and another `C9 01`
at 03:07:22.774. The expected `RemoteControlDeniedError` was raised.
Final telemetry at 03:07:24.307 confirmed 12.00 V, 0.500 A, output off;
release was acknowledged. Every kept reading shows output off. JSON:
`2026-10-04T030658-system-macos-ble-st048-deny-coordinated.json`.

### Case 2: unanswered prompt

Node:
`tests/system/test_control.py::test_st048_run2_no_answer_is_a_denial_within_70_s`.
Command: the common template with that node and
`--show-capture=no --tb=short`. Run: 03:08:23 to 03:09:58. All phases
passed. JSON:
`2026-10-04T030823-system-macos-ble-st048-timeout-coordinated.json`.

The user was told before starting and again when the prompt became
active to touch nothing until completion. The request at 03:08:53.766
received `C9 01` at 03:09:55.593, after 61.827 s. The library raised
`RemoteControlDeniedError`. This was a device reply, not the library's
70 s fallback. The user reported that the prompt had disappeared and
explicitly confirmed touching nothing throughout the prompt.

Pre-flight and final telemetry confirmed DC mode, 12.00 V, 0.500 A
and output off. Every kept reading shows output off, and release was
acknowledged. The observed timing is consistent with the identified
firmware idle-dismissal path.

### Case 3: queued command during delayed permission

Node:
`tests/system/test_control.py::test_st048_run3_nothing_is_sent_while_the_request_is_pending`.
Command: the common template with that node and
`--show-capture=no --tb=short`. Run: 03:11:36 to 03:12:19. All phases
passed. JSON:
`2026-10-04T031136-system-macos-ble-st048-queued-coordinated.json`.

The user was instructed to wait until the test's 10 s countdown ended,
then explicitly told to press Allow. They confirmed pressing Allow
after that instruction. The request at 03:11:57.906 received `C9 00`
at 03:12:14.598 (16.692 s). There was no control command between that
request and the grant. The 1.00 V command followed the grant at
03:12:15.006, and the queued 0.050 A command at 03:12:15.500. Both
were acknowledged.

Teardown restored 12.00 V and 0.500 A in acknowledged commands. Final
telemetry at 03:12:19.055 confirmed those values and output off;
release was acknowledged. Every kept reading shows output off.

### Result of the coordinated repetition

ST-048 passes on macOS Bluetooth: all three approved cases have passing
results with the user's actions established, and all teardowns passed.
The earlier uncertain or interrupted timeout attempts and the scan
failures remain in the record; they are not rewritten as passes. This
does not verify ST-048 on Linux or Windows or complete the system level.

## ST-021: refuse a DC command in PD mode

Node ID:
`tests/system/test_control.py::test_st021_no_command_outside_dc_mode`.
Command: the common template with that node and
`--show-capture=no --tb=short`.

The user selected PD mode and explicitly confirmed the output off and
the LED disconnected before the run. The first invocation, 03:22:48
to 03:22:58, failed in initial discovery with no connection or command
sent. JSON: `2026-10-04T032248-system-macos-ble-st021.json`.

The retry, 03:23:24 to 03:24:12, passed in all phases. Pre-flight
confirmed PD mode, 12.00 V, 0.500 A, output off and the same versions
as ST-012. The test's front-panel preparation prompt was acknowledged
using the user's existing confirmation. Its first reading at
03:23:51.992 reported mode 2 (PD); `set_voltage(1.0)` raised
`ModeError` at 03:23:51.993. No `C8` frame was sent for that command.

On the teardown instruction the user switched back to DC and confirmed
output off. Telemetry first reported DC at 03:24:10.274. The only
`C8` in the test log was the release after restoration to DC, at
03:24:11.849, acknowledged with `C9 00`. Final telemetry at
03:24:11.848 confirmed DC mode, 12.00 V, 0.500 A and output off.
All 90 retained readings show output off. JSON:
`2026-10-04T032324-system-macos-ble-st021.json`.

ST-021 is verified on macOS Bluetooth using its PD-mode option. No
production code, fixture or approved specification changed for this run.
