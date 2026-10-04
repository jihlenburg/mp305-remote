# Focused hardware verification plan

Status: proposed, 2026-10-04, pending approval of ADR-0018, ST revision 13,
AT revision 10 and process revision 3. The user authorized preparation.
This document organizes execution and evidence; the ST and AT entries
remain the sole definitions of what each test verifies.

## Scope and reduction

All 50 ST and 36 AT entries remain. All supported OS and transport
combinations remain. The proposed matrices are in
[7-system-tests.md](7-system-tests.md#2-coverage) and
[8-acceptance-tests.md](8-acceptance-tests.md#2-coverage).

| Level | Original hardware cells | Proposed hardware cells | Conditional reuse cells |
|---|---:|---:|---:|
| ST | 210 | 174 | 36 |
| AT | 177 | 159 | 18 |
| Total | 387 | 333 | 54 |

A cell is one entry on one OS and transport, not an invocation, person
action or time estimate. Existing analysis, inspection and n/a cells are
excluded. Batching adds savings without changing cell counts. No test or
platform is declared passed by approving this plan.

## Evidence rules

For each retained hardware obligation, record a direct result or review a
previous result for continued applicability. The review names the original
commit, current commit and diff, firmware, OS, architecture, adapter,
dependency changes, complete case coverage and teardown evidence. Rerun
affected cases after a relevant change. Old records are candidates, not
automatic current-build passes; failures and uncertain actions stay recorded.

For each `R` cell, record:

1. The entry, target OS/transport and artifact hashes.
2. The passing source entry and transport, record and exact frame/event
   evidence. Source results must cover all required cases.
3. The current target UT/IT evidence and the specific shared code path;
   examine conditional compilation, binding, clock and dependency differences.
4. The target hardware prerequisites in the tables below, with their own
   passing results and actual host/adapter. A scan alone is insufficient.
5. The equivalence argument, remaining limitations and change triggers.
   Record `verified by analysis` only after the whole argument holds;
   otherwise record `open` and run the original hardware procedure.

Reuse applies to the recorded unit and firmware versions. A firmware
change requires a new impact review and affected baseline hardware runs.
Transport, discovery, scheduling or shutdown changes require the relevant
platform checks again. Pure documentation edits do not by themselves
require physical retesting. A trace only earns another result when that
entry's prescribed setup, actions and expected observations are all met.

Acceptance additionally requires a witnessed release-build source on the
same OS and the user's review of the reuse conclusion. A development
extension built with `maturin develop` is not a release wheel acceptance
result. No AT pass is recorded without the user's observation or review.

## System evidence reuse

Every row below retains direct macOS hardware execution on each applicable
transport. Reuse is only for Linux and Windows, always from the same
transport. Every row also requires the current target UT/IT suite and
the shared-code review above. The target prerequisites remain hardware
obligations in the ST matrix. Sources listed as open cannot yet be reused.

| Entry | Reason for reducing OS repetition | Source candidate and target hardware prerequisites |
|---|---|---|
| ST-009 | Bind callback and warning dispatch are shared session/Python logic. | Baseline open. Target ST-008 proves real bind ordering and ST-010 exercises pending-bind timeout; review callback delivery in the target binding tests. |
| ST-012 | Model/version decoding, units and first-reading guard are shared; every run still records firmware and mode. | macOS BLE screen and early-call results exist; USB open. Target ST-006 and ST-013 must show the initial values and frames; compare them with source information and current decoder/binding tests. |
| ST-014 | Loaded voltage/current/power scaling and working time originate in the same device and decoder. | Both baseline transports open with Load A. Target ST-006 and ST-013 establish applied setpoints and live telemetry; inspect their decoded values against raw frames. |
| ST-015 | Off/CV/CC decoding is a shared enum mapping; regulation is device behavior. | Both baseline transports open with Load A. Target ST-006 and ST-026 establish real output/fault telemetry; baseline must demonstrate both CV and CC, not just no-load CV. |
| ST-021 | The mode guard runs in the shared session before encoding a command. | macOS BLE PD case passed; USB open. Target ST-049 must deliver a real PD mode transition; current mock tests establish refusal before I/O. |
| ST-024 | Validation, clamping and rounding are shared API/protocol paths. | macOS BLE passed; USB open. Target ST-020 proves actual setpoint commands; current binding/core tests cover invalid inputs and copied limits. |
| ST-027 | Fault bit decoding and change-event de-duplication are shared logic. | Both baseline transports open with Load B. Target ST-026 must physically trip OCP and prove output-on refusal; analyze its raw fault readings and current event tests. |
| ST-033 | Reading types, units and immutability are shared binding behavior. | macOS BLE passed; USB open. Target ST-013 supplies actual telemetry; inspect binding/type tests for the actual Python and architecture. |
| ST-035 | Ramp sequencing and range checking are shared helpers. | macOS BLE passed; USB open. Target ST-020 verifies applied commands and ST-034 verifies target timing/stream behavior; current helper tests cover progression and limits. |
| ST-048 | Grant/deny/idle-timeout semantics originate in the same firmware; pending-state and queue logic are shared. | macOS BLE all three cases passed with explicit user observations. Target ST-018, ST-023 and ST-022 must pass real grant, revocation and queued priority-off paths; current remote-state tests cover pending denial, timeout and queuing. |

This does not reduce direct binding denial/timeout tests, ST-022 priority
output-off, ST-026 fault refusal, ST-028 loss, ST-029/ST-030 close,
ST-041 crash markers, ST-043 arbitration, ST-046 USB keepalive or
ST-050 reconnection. Those remain on every applicable OS/transport.
USB framing and information layout still need direct hardware evidence.

## Acceptance evidence reuse

These entries run on Bluetooth on every OS using the release artifacts.
Only the same OS's USB cell can reuse that witnessed result. In addition
to the entry-specific prerequisites below, USB AT-001, AT-004 and AT-015
must pass on the same release artifacts, and the matching system entry
must be verified for USB by its approved `H` or `R` method. No AT source
is available yet; existing ST sessions are development-build evidence.

| Entry | Reason and additional USB evidence |
|---|---|
| AT-003 | Float units and public API conversion are shared. ST-014 must cover physical scaling; inspect USB readings from AT-015 against raw telemetry and expected setpoints. |
| AT-012 | Field parsing, validation and the upper-edge UI action are shared. Require ST-024 plus USB AT-005 and AT-007; the witnessed Bluetooth source must include 29.99 V with nothing connected and output off. |
| AT-013 | Chart rendering is independent of the transport after readings arrive. USB AT-011 must show live updates and AT-006 the on/off transition; inspect the matching app code for transport-specific rendering. |
| AT-014 | The app's CSV writer is shared within the release. USB ST-034 and the witnessed app's Bluetooth CSV must pass ST-037's format check; USB AT-011 proves delivery of live readings. |
| AT-017 | Reading object types and units are shared. USB ST-014 and ST-033 must be verified, and USB AT-009 must show a real fault through the release library. |
| AT-029 | The installed helper's sequencing is shared. Require USB ST-035 and the actual USB release API session; the witnessed Bluetooth source must cover every step and dwell. |

## Traceability impact reviewed before editing

The generated traceability matrix was consulted before changing the test
specifications. The Verifies mappings and all requirement/design statements
are unchanged. For coverage reductions the affected parents are:

| Level | Changed coverage entries | Existing parents |
|---|---|---|
| ST | ST-009, ST-012, ST-014, ST-015, ST-021, ST-024, ST-027, ST-033, ST-035, ST-048 | SR-008, SR-012, SR-014, SR-015, SR-021, SR-024, SR-027, SR-033, SR-035, SR-053 |
| AT | AT-003, AT-012, AT-013, AT-014, AT-017, AT-029 | UR-003, UR-012, UR-013, UR-014, UR-017, UR-029 |

Procedure corrections affect ST-019 (SR-019, UR-023, UR-005, H-001,
H-003; AR-025/IT-025), ST-049 (SR-054, UR-018, UR-006, H-004;
AR-025/IT-025 and AR-027/IT-027), ST-038 (SR-038 to SR-042),
AT-023 (UR-023), AT-034 (UR-034) and AT-037 (UR-037).
Session and app designs already provide explicit release/request actions
and outside-DC behavior; no new production behavior is specified.

After approval, update `tests/system/test_control.py` for ST-019 and
ST-049, and the written app procedures for ST-038, AT-023, AT-034 and
AT-037. Audit the corresponding acceptance scripts before execution;
`tests/acceptance/` currently contains only `__init__.py`, so the named
scripts in the AT specification are still to be implemented. Do not
count an absent script or this execution plan as a passing test.

## Existing evidence and open work

Candidate sources, subject to the evidence rules above:

- [macOS BLE batches](records/2026-10-03-system-macos-ble-batch1.md):
  ST-004, ST-006, ST-012 early-call case, ST-013, ST-017 hardware log
  case, ST-018, ST-020, ST-023 normal-command case, ST-024, ST-029,
  ST-031 thread-progress case, ST-033, ST-034 hardware cases, ST-035,
  ST-039 streaming-log portion, ST-041, ST-043 same-process case and
  ST-047 available-log portions. Partial entries need their other cases.
- [macOS person runs](records/2026-10-04-system-macos-ble-person.md):
  ST-012 screen comparison, ST-021, ST-023 revocation, and all ST-048
  cases. ST-019 failed and awaits its corrected procedure. Teardown
  defects and inconclusive attempts remain recorded.
- [macOS discovery](records/2026-10-02-system-macos-ble-discovery.md):
  ST-002. Linux and Windows scans are in the separate discovery/VM
  records; they do not establish full connection coverage.
- [Linux hardware](records/2026-10-04-system-linux-ble-halobox.md):
  ST-002 passed; ST-013 remains unverified because close fails.
  ADR-0017 is proposed, not implemented or approved by this plan.
- [macOS automated tests](records/2026-10-02-integration-automated.md),
  [Linux automated tests](records/2026-10-02-unit-integration-linux.md)
  and [Windows automated tests](records/2026-10-02-unit-integration-windows.md)
  provide baseline mock/build evidence. Current-build and architecture
  review is still required; Windows signal-test omissions remain open.

No complete USB system run or release acceptance run is claimed here.
The Windows hardware host still needs a working USB path independent of
the Mac's observed dongle problem. There is no implicit acceptance of
the Linux timeout, intermittent discovery or Windows hardware gaps.

## Execution order after approval

| Work package | Entries and artifacts | Bench and coordination |
|---|---|---|
| Review and implement | Approve the draft; implement ST-019/ST-049 corrections; review source diffs; build the release app/wheel and required AT scripts | No device I/O. Keep ADR-0017 a separate decision. |
| No-load reference completion | macOS BLE ST-001, ST-005, ST-007 to ST-010, ST-019, ST-031 interrupt, ST-045, ST-049; complete ST-039/ST-047 log inputs | One instruction at a time. Bind tests with fresh host IDs last, then confirm the normal host again. Discovery-off controls must be identified before asking for a front-panel change. |
| Loss and recovery | ST-028, ST-050, and witnessed AT-024/AT-030/AT-037 where their separate preconditions are met | State the exact power, adapter or cable action and restore it. ST-028 output-off and AT-024 output-on are distinct cases. |
| USB reference | Every applicable macOS USB `H` cell, especially ST-003, ST-011, ST-040, ST-043 and ST-046 | Confirm the same unit's HID path. Transport arbitration gets a separate two-transport session. |
| Load A | ST-014, ST-015, ST-022; AT-006, AT-011, AT-013, AT-014, AT-017 and AT-028 where compatible | Named 100 ohm, 1 percent, at least 1 W load. Set up once per bench block; restore between cases. Keep the output-off timing and re-grant cases. |
| Load B | ST-026, ST-027; AT-009 | Named 22 ohm, at least 2 W load. Keep the physical OCP trip, fault observations, output-on refusal and CC restoration. Never substitute the LED. |
| Release app and library | Remaining AT `H` entries, ST-030, ST-036, ST-038; ST-037 with both CSV files; inspection entries | User-witnessed release artifacts. Combine compatible observations; retain app/library distinction and each ID's result. |
| Other hosts | Linux and Windows retained `H` cells, then justified `R` analyses and release AT sessions | Working hardware and fresh target build/test evidence first. Load-dependent safety cells still require their loads on each host. |

The full matrices, not this scheduling table, determine completion.
Future runs use the exact existing entry procedures until their changed
versions are approved and implemented. This document is not a new HIL
selector: the current suite still runs all selected tests. Do not skip
tests silently to obtain a green run under the proposed matrix.

## Combining executions without losing observations

- A release Python connect/control/close session can provide parts of
  ST-006 and AT-015 plus the ST-047/AT-033 frame inspection, only if
  every required command, value and observation is present.
- Load A recording can serve chart, readout and CSV observations when
  the individual durations, rates and on/off steps are all satisfied.
  ST-034 and AT-028 have different durations/rates; neither is credited
  from a shorter capture.
- An OCP event can supply fault data to multiple entries only when the
  streaming, event count, subsequent refused output-on and witnessed app
  observations are all captured. The existing separate pytest functions
  still run separately unless an approved driver preserves every step.
- ST-038's 30-minute memory and display-range observations can be shared
  between transports on the same OS and binary after reviewing that they
  are transport-independent. Its prompt, pending-off, link-loss and
  mode-change observations remain transport-specific.
- Restore output off and original settings after each case, including
  failures. Use no-load, Load A and Load B blocks separately. Preserve
  fresh connections wherever bind, first-control or close is the subject.

## Approval boundary

This draft changes verification methods and selected procedures. Approval
is needed before implementing or re-verifying the changed items, under
AGENTS.md process rule 5. Approving it accepts the reduced matrix and
these procedures; it does not approve ADR-0017, accept a test failure,
mark a level complete, authorize a commit or relax any HIL condition.
