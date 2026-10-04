# Focused hardware verification plan

Status: approved by the user on 2026-10-05 with ADR-0018, ST revision 13,
AT revision 10 and process revision 3 (first draft of 2026-10-04,
reworked on 2026-10-05 after an independent review and the user's
decisions on it). This document
organizes execution and evidence; the ST and AT entries remain the sole
definitions of what each test verifies.

## Scope

All 50 ST and 36 AT entries remain. All supported OS and transport
combinations remain. The matrices are in
[7-system-tests.md](7-system-tests.md#2-coverage) and
[8-acceptance-tests.md](8-acceptance-tests.md#2-coverage).

| Level | Hardware cells in the baseline | Hardware cells now | Conditional reuse cells |
|---|---:|---:|---:|
| ST | 210 | 207 | 3 |
| AT | 177 | 171 | 6 |
| Total | 387 | 378 | 9 |

A cell is one entry on one OS and transport, not an invocation, person
action or time estimate. Analysis, inspection and n/a cells are excluded.
No test or platform is declared passed by the approval of this plan.

What "hardware" means changes. The baseline's Linux and Windows cells
carried the code `VM`: the Parallels VMs on the Mac, with the supply
passed through for USB and a USB Bluetooth dongle for Bluetooth, and with
CI as the substitute for Bluetooth until a dongle was at hand. That
dongle cannot carry a connection on the Mac, with or without a VM
(LOGBOOK 2026-10-04), so the VM route gives no Bluetooth evidence.
ADR-0018 replaces `VM` and `CI` by `H`: the procedure on an actual host
with a working path to the supply. A missing host leaves the cell open.

Per platform:

| Platform | ST hardware cells | AT hardware cells | State |
|---|---:|---:|---|
| macOS | 70 | 56, and 3 reuse | the reference; Bluetooth runs under way, USB open |
| Linux | 67, and 3 reuse | 56, and 3 reuse | the native machine halobox through the USB dongle; first results of 2026-10-05 |
| Windows | 70 | 59 | open and deferred: no host with a working path to the supply |

With Windows deferred, neither level can be closed. The Windows cells
stay open until a host exists (a native Windows PC, or a Windows VM on a
machine whose USB pass-through works); they are not downgraded.

## Evidence rules

For each hardware obligation, record a direct result or review a previous
result for continued applicability. The review names the original commit,
current commit and diff, firmware, OS, architecture, adapter, dependency
changes, complete case coverage and teardown evidence. Rerun affected
cases after a relevant change. Old records are candidates, not automatic
current-build passes; failures and uncertain actions stay recorded.

For each `R` cell, record:

1. The entry, target OS/transport and artifact hashes.
2. The passing source entry and transport, record and exact frame/event
   evidence. The source result comes from the build under test, or is
   reviewed again against its commit. It must cover all required cases.
3. The current target UT/IT evidence and the specific shared code path;
   examine conditional compilation, binding, clock and dependency differences.
4. The target hardware prerequisites in the tables below, with their own
   passing results from direct runs and the actual host and adapter. A
   scan alone is insufficient, and a prerequisite that is itself a reuse
   cell does not count.
5. The equivalence argument, remaining limitations and change triggers.
   Record `verified by analysis` only after the whole argument holds;
   otherwise record `open` and run the original hardware procedure.
6. The user's sign-off. A reuse record without it leaves the cell open,
   for system cells as for acceptance cells.

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

Three Linux cells. Each retains direct macOS hardware execution on the
same transport, the current Linux UT/IT suite and the shared-code review
above. Windows has no reuse cell.

| Entry and cells | Reason for not repeating it on Linux | Source candidate and Linux hardware prerequisites |
|---|---|---|
| ST-012, Linux over Bluetooth and over USB | Model and version decoding, units and the first-reading guard are shared; every run still records the firmware and mode. Only the comparison with the supply's screens is reused; the early control call is automated and runs directly (it passed on Linux over Bluetooth on 2026-10-05). | macOS BLE screen comparison and early-call results exist from before the bounds of ADR-0017; USB open. Linux ST-006 and ST-013 on the same transport, run directly, must show the initial values and frames; compare them with the source information and the current decoder and binding tests. |
| ST-035, Linux over Bluetooth | Ramp sequencing and range checking are shared helpers. Over Bluetooth the entry needs a person for the remote-control prompt; over USB it does not, so the USB cell is a direct run. | macOS BLE passed on 2026-10-03, before the bounds of ADR-0017. Linux ST-020 over Bluetooth (applied setpoint commands), ST-034 over Bluetooth (stream timing) and ST-035 over USB, all run directly; current helper tests cover progression and limits. |

Everything else is a direct run on every OS and transport. That includes
the entries of the first draft that the review and the user moved back:
the hazard-related ST-014, ST-015, ST-021, ST-024 and ST-027 (the
physical OCP trip), the prompt entries ST-009 and ST-048, whose timing
runs through each OS's Bluetooth stack, and ST-033, which needs no
person. As before it includes the binding denial and timeout tests,
ST-022 priority output-off, ST-026 fault refusal, ST-028 loss,
ST-029/ST-030 close, ST-041 crash markers, ST-043 arbitration, ST-046
USB keepalive and ST-050 reconnection. USB framing and information layout
need direct hardware evidence.

## Acceptance evidence reuse

Three entries, on macOS and on Linux. Each runs over Bluetooth with the
release artifacts, witnessed. Only the same OS's USB cell can reuse that
result. USB AT-001, AT-004 and AT-015 must pass on the same release
artifacts, and the matching system entry must be verified over USB on the
same OS by a direct run. No AT source is available yet; existing ST
sessions are development-build evidence.

| Entry | Reason and additional USB evidence |
|---|---|
| AT-012 | Field parsing, validation and the upper-edge UI action are shared. Require ST-024 over USB plus USB AT-005 and AT-007; the witnessed Bluetooth source must include 29.99 V with nothing connected and output off. |
| AT-013 | Chart rendering is independent of the transport after readings arrive. USB AT-011 must show live updates and AT-006 the on/off transition; inspect the matching app code for transport-specific rendering. |
| AT-014 | The app's CSV writer is shared within the release. USB ST-034 and the witnessed app's Bluetooth CSV must pass ST-037's format check; USB AT-011 proves delivery of live readings. |

AT-003, AT-017 and AT-029 over USB are library scripts without a prompt
and are run directly.

## Traceability impact reviewed before editing

The generated traceability matrix was consulted before changing the test
specifications. The Verifies mappings and all requirement/design statements
are unchanged. For the reuse cells the affected parents are:

| Level | Entries with reuse cells | Existing parents |
|---|---|---|
| ST | ST-012, ST-035 | SR-012, SR-035 |
| AT | AT-012, AT-013, AT-014 | UR-012, UR-013, UR-014 |

Procedure corrections affect ST-019 (SR-019, UR-023, UR-005, H-001,
H-003; AR-025/IT-025), ST-049 (SR-054, UR-018, UR-006, H-004;
AR-025/IT-025 and AR-027/IT-027), ST-038 (SR-038 to SR-042),
AT-023 (UR-023), AT-034 (UR-034) and AT-037 (UR-037).
Session and app designs already provide explicit release/request actions
and outside-DC behavior; no new production behavior is specified. The
expected result of ST-034 (SR-034, UR-028) is reworded for a link that
cannot keep up with a rate, as SR-034 already says.

To do in the test code: update `tests/system/test_control.py` for ST-019 and
ST-049, `tests/system/test_library.py` for ST-034, and the written app
procedures for ST-038, AT-023, AT-034 and AT-037. Audit the corresponding
acceptance scripts before execution; `tests/acceptance/` currently
contains only `__init__.py`, so the named scripts in the AT specification
are still to be implemented. Do not count an absent script or this
execution plan as a passing test.

## Existing evidence and open work

Candidate sources, subject to the evidence rules above:

- [macOS BLE batches](records/2026-10-03-system-macos-ble-batch1.md):
  ST-004, ST-006, ST-012 early-call case, ST-013, ST-017 hardware log
  case, ST-018, ST-020, ST-023 normal-command case, ST-024, ST-029,
  ST-031 thread-progress case, ST-033, ST-034 hardware cases, ST-035,
  ST-039 streaming-log portion, ST-041, ST-043 same-process case and
  ST-047 available-log portions. Partial entries need their other cases.
  These runs predate the connect and close bounds of ADR-0017 (commit
  `1cbcb09`): by the evidence rules the connect- and close-sensitive
  entries among them (ST-004, ST-013, ST-029, ST-041, ST-043) are to be
  run again on the build under test, and the others reviewed against it.
- [macOS person runs](records/2026-10-04-system-macos-ble-person.md):
  ST-012 screen comparison, ST-021, ST-023 revocation, and all ST-048
  cases. ST-019 failed and awaits its corrected procedure. Teardown
  defects and inconclusive attempts remain recorded.
- [macOS discovery](records/2026-10-02-system-macos-ble-discovery.md):
  ST-002.
- Linux hardware, the native machine halobox through the USB dongle as
  its only adapter (ADR-0017: one adapter), on the build with the bounds
  of ADR-0017: [ST-013](records/2026-10-05-system-linux-ble-st013.md) and
  [the entries without a person](records/2026-10-05-system-linux-ble-noperson.md)
  (ST-002, ST-004, ST-013, ST-033 pass; ST-012, ST-017, ST-031, ST-039
  and ST-043 pass in their parts without a person; ST-034 fails at 4
  readings per second and awaits its reworded expected result). The
  machine's built-in adapter is not suited as the machine is set up
  ([record](records/2026-10-04-system-linux-ble-halobox.md)).
- [macOS automated tests](records/2026-10-02-integration-automated.md),
  [Linux automated tests](records/2026-10-02-unit-integration-linux.md)
  and [Windows automated tests](records/2026-10-02-unit-integration-windows.md)
  provide baseline mock/build evidence. Current-build and architecture
  review is still required; Windows signal-test omissions remain open.

No complete USB system run or release acceptance run is claimed here.
Windows has no test machine: the dongle cannot carry a connection on the
Mac, so its VMs are out for Bluetooth. Windows hardware work is deferred.
There is no implicit acceptance of the Linux findings or of the Windows
gap.

## Execution order

| Work package | Entries and artifacts | Bench and coordination |
|---|---|---|
| Review and implement | Implement the ST-019, ST-049 and ST-034 changes in the test code; review source diffs; build the release app/wheel and required AT scripts | No device I/O. |
| No-load reference completion | macOS BLE ST-001, ST-005, ST-007 to ST-010, ST-019, ST-031 interrupt, ST-045, ST-049; complete ST-039/ST-047 log inputs; rerun the connect- and close-sensitive entries on the current build | One instruction at a time. Bind tests with fresh host IDs last, then confirm the normal host again. Discovery-off controls must be identified before asking for a front-panel change. |
| Loss and recovery | ST-028, ST-050, and witnessed AT-024/AT-030/AT-037 where their separate preconditions are met | State the exact power, adapter or cable action and restore it. ST-028 output-off and AT-024 output-on are distinct cases. |
| USB reference | Every applicable macOS USB `H` cell, especially ST-003, ST-011, ST-040, ST-043 and ST-046 | Confirm the same unit's HID path. Transport arbitration gets a separate two-transport session. |
| Load A | ST-014, ST-015, ST-022; AT-006, AT-011, AT-013, AT-014, AT-017 and AT-028 where compatible | Named 100 ohm, 1 percent, at least 1 W load. Set up once per bench block; restore between cases. Keep the output-off timing and re-grant cases. |
| Load B | ST-026, ST-027; AT-009 | Named 22 ohm, at least 2 W load. Keep the physical OCP trip, fault observations, output-on refusal and CC restoration. Never substitute the LED. |
| Release app and library | Remaining AT `H` entries, ST-030, ST-036, ST-038; ST-037 with both CSV files; inspection entries | User-witnessed release artifacts. Combine compatible observations; retain app/library distinction and each ID's result. |
| Linux | The Linux `H` cells on halobox through the dongle, with a person and with Load A and Load B as on macOS; then the three `R` analyses and the release AT sessions | Fresh Linux build and test evidence first. The load-dependent and prompt entries are direct runs there. |
| Windows | Deferred | Needs a host with a working path to the supply first. |

The full matrices, not this scheduling table, determine completion.
Future runs use the existing test code of an entry until its changed
procedure is implemented. This document is not a new HIL
selector: the current suite still runs all selected tests. Do not skip
tests silently to obtain a green run under the matrix.

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
- ST-038's display-range observations (step 1) can be shared between
  transports on the same OS and binary after reviewing that they are
  transport-independent. Its 30-minute memory check and its prompt,
  pending-off, link-loss and mode-change observations remain
  transport-specific.
- Restore output off and original settings after each case, including
  failures. Use no-load, Load A and Load B blocks separately. Preserve
  fresh connections wherever bind, first-control or close is the subject.

## Approval boundary

The approval of 2026-10-05 accepts the matrices, the reuse rules, the
changed procedures and the amendments to AGENTS.md that ADR-0018 lists.
It does not accept a test failure, mark a level complete or relax any
HIL condition. ADR-0017 is a separate decision, accepted and
implemented on 2026-10-04.
