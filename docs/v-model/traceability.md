# Traceability matrix

Status: draft

Kept by hand until the check script exists (TODO.md, level 4). The script
must exist before the first module is implemented, and from then on it
generates this file.

## 1. Hazards

| Hazard | Summary | Mitigating URs | Mitigating SRs (draft) | Verifying ATs |
|---|---|---|---|---|
| H-001 | Output switches on unasked | UR-004, UR-005, UR-023 | SR-019, SR-020, SR-021 | AT-004, AT-005, AT-023 |
| H-002 | Commands reach the wrong supply | UR-002, UR-010 | SR-001, SR-004 | AT-002, AT-010 |
| H-003 | Setpoints change to values the user did not choose | UR-004, UR-023, UR-024 | SR-019, SR-028 | AT-004, AT-023, AT-024 |
| H-004 | Output stays on after exit, crash or link loss (residual risk not accepted, TBD-015) | UR-006, UR-018, UR-024, UR-030, UR-031 | SR-022, SR-028, SR-029, SR-030, SR-046, SR-047 | AT-006, AT-018, AT-024, AT-030, AT-031 |
| H-005 | Wrong unit or scale | UR-003, UR-012, UR-017 | SR-014, SR-024 | AT-003, AT-012, AT-017 |
| H-006 | Someone else controls or watches the supply (residual risk not accepted, TBD-015) | UR-008, UR-016 | SR-006, SR-010 | AT-008, AT-016 |
| H-007 | Setpoint exceeds what the DUT can take | UR-007, UR-012 | SR-024, SR-040 | AT-007, AT-012 |
| H-008 | Output runs during a reported fault | UR-009 | SR-026, SR-027 | AT-009 |
| H-009 | Supply left in its bootloader | UR-025 | SR-006 | AT-025 |

## 2. User requirements

| UR | Summary | Parent or source | Verified by | Status |
|---|---|---|---|---|
| UR-001 | Connect over Bluetooth LE and USB HID | user, ADR-0004 | AT-001 | draft |
| UR-002 | Explicit choice of the target supply | user, H-002 | AT-002 | draft |
| UR-003 | Volts, amperes and watts | user, H-005 | AT-003 | draft |
| UR-004 | Read and show state before control | H-001, H-003 | AT-004 | draft |
| UR-005 | Output on only on explicit request | H-001 | AT-005 | draft |
| UR-006 | Output off acknowledged within 0.5 s | H-004 | AT-006 | draft |
| UR-007 | User limits for voltage and current | H-007 | AT-007 | draft |
| UR-008 | Confirm on the supply; disconnect unless "allowed" | H-006 | AT-008 | draft |
| UR-009 | Report every fault; no output on during a fault | H-008 | AT-009 | draft |
| UR-010 | App: list of supplies found | user, H-002 | AT-010 | draft |
| UR-011 | App: live readout at 2 Hz or more | user | AT-011 | draft |
| UR-012 | App: validated inputs | user, H-005, H-007 | AT-012 | draft |
| UR-013 | App: scrolling V, I, P chart | user | AT-013 | draft |
| UR-014 | App: CSV recording | user | AT-014 | draft |
| UR-015 | Library: synchronous API | ADR-0006, ADR-0007 | AT-015 | draft |
| UR-016 | Library: distinct exceptions | ADR-0007, H-006 | AT-016 | draft |
| UR-017 | Library: typed readings in SI units | user, H-005, H-008 | AT-017 | draft |
| UR-018 | Library: context manager leaves output off | H-004 | AT-018 | draft |
| UR-019 | One Rust core crate | ADR-0003 | AT-019 | draft |
| UR-020 | App in Rust and egui on three OSes | ADR-0005 | AT-020 | draft |
| UR-021 | Library on the core via PyO3 | ADR-0006 | AT-021 | draft |
| UR-023 | Change one setting, keep the others | H-001, H-003 | AT-023 | draft |
| UR-024 | Link loss: warn, no automatic reconnect | H-003, H-004 | AT-024 | draft |
| UR-025 | No firmware updates | H-009 | AT-025 | draft |
| UR-026 | Show model and versions | user, AGENTS.md | AT-026 | draft |
| UR-027 | "Not found" names another app as possible cause | user, LOGBOOK | AT-027 | draft |
| UR-028 | Library: streaming and CSV helper | user | AT-028 | draft |
| UR-029 | Library: host-driven ramp helper | user | AT-029 | draft |
| UR-030 | Unclean-exit warning | H-004, user | AT-030 | draft |
| UR-031 | Bench-safety note in the docs | H-004, user | AT-031 | draft |
| UR-032 | Remembered host: stable host ID at bind | H-006, user | AT to be written | draft |
| UR-033 | No changes to stored settings, tables or chip configuration | H-009, user | AT to be written | draft |
| UR-034 | Unsolicited and deferred frames handled | H-001, H-003, H-005 | AT to be written | draft |
| UR-035 | USB keepalive | H-004 | AT to be written | draft |
| UR-036 | Remote-control confirmation over Bluetooth | H-006 | AT to be written | draft |

## 3. System requirements

| SR | Parent or source | Verified by | Status |
|---|---|---|---|
| SR-001 | UR-001, UR-002, UR-010 | ST-001 | draft |
| SR-002 | UR-001, UR-027 | ST-002 | draft |
| SR-003 | UR-001, UR-002, UR-010 | ST-003 | draft |
| SR-004 | UR-002, UR-010, H-002 | ST-004 | draft |
| SR-005 | UR-027 | ST-005 | draft |
| SR-006 | UR-025, H-009 | ST-006 | draft |
| SR-007 | UR-008 | ST-008 | draft |
| SR-008 | UR-008 | ST-009 | draft |
| SR-009 | UR-008, UR-016 | ST-010 | draft |
| SR-010 | UR-008, UR-016, H-006 | ST-007 | draft |
| SR-011 | UR-008 | ST-011 | draft |
| SR-012 | UR-004, UR-026 | ST-012 | draft |
| SR-013 | UR-011, UR-028 | ST-013 | draft |
| SR-014 | UR-003, UR-017, H-005 | ST-014 | draft |
| SR-015 | UR-011, UR-017 | ST-015 | draft |
| SR-016 | UR-017, H-005 | ST-016 | draft |
| SR-017 | derived | ST-017 | draft |
| SR-018 | UR-008, UR-023 | ST-018 | draft |
| SR-019 | UR-023, UR-005, H-001, H-003 | ST-019 | draft |
| SR-020 | UR-005, H-001 | ST-020 | draft |
| SR-021 | UR-023, H-001 | ST-021 | draft |
| SR-022 | UR-006, H-004 | ST-022 | draft |
| SR-023 | UR-016, H-001 | ST-023 | draft |
| SR-024 | UR-007, UR-012, H-005, H-007 | ST-024 | draft |
| SR-025 | UR-012 | ST-025 | draft |
| SR-026 | UR-009, H-008 | ST-026 | draft |
| SR-027 | UR-009, H-008 | ST-027 | draft |
| SR-028 | UR-024, H-004 | ST-028 | draft |
| SR-029 | UR-018, UR-006, H-004 | ST-029 | draft |
| SR-030 | H-004, UR-006 | ST-030 | draft |
| SR-031 | UR-015 | ST-031 | draft |
| SR-032 | UR-016 | ST-032 | draft |
| SR-033 | UR-017 | ST-033 | draft |
| SR-034 | UR-028 | ST-034 | draft |
| SR-035 | UR-029 | ST-035 | draft |
| SR-036 | UR-015, UR-021 | ST-036 | draft |
| SR-037 | UR-014, UR-028 | ST-037 | draft |
| SR-038 | UR-013 | ST-038 | draft |
| SR-039 | UR-011, ADR-0005 | ST-038 | draft |
| SR-040 | UR-012, UR-005, H-007 | ST-038 | draft |
| SR-041 | UR-006, UR-005 | ST-038 | draft |
| SR-042 | UR-024 | ST-038 | draft |
| SR-043 | UR-020 | ST-036 | draft |
| SR-044 | derived | ST-039 | draft |
| SR-045 | derived | ST-040 | draft |
| SR-046 | UR-030, H-004 | ST-041 | draft |
| SR-047 | UR-031, H-004 | ST-042 | draft |

The SR rows cover the level 2 draft, which is not up for approval before G1.

## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | Initial traceability matrix for Level 1 (UR and AT) | not yet approved |
| 2 | 2026-09-29 | Matched UR and AT revision 2; added the draft SR to ST mapping | not yet approved |
| 3 | 2026-09-29 | Matched UR revision 4, SR revision 3; hazard rows list the draft SRs | not yet approved |
| 4 | 2026-09-29 | TBD-015 mitigations: UR-030, UR-031, SR-046, SR-047 and their tests; H-004 row updated. | not yet approved |
| 5 | 2026-09-29 | UR-022 and AT-022 withdrawn. H-006, SR-006, SR-007 and SR-010 parents updated. | not yet approved |
| 6 | 2026-09-30 | UR revision 8: UR-032 to UR-036 added; their ATs and the SR columns wait for the rewrite of 2-system-requirements.md and 8-acceptance-tests.md. | not yet approved |
