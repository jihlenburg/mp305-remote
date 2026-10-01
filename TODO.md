# TODO

Open and finished work, grouped by V-model phase. The process is described in
[docs/v-model/README.md](docs/v-model/README.md). Planned work lives here;
[LOGBOOK.md](LOGBOOK.md) records only what happened.

## Phase status

| Gate | Level | Status |
|---|---|---|
| G1 | User requirements + acceptance test spec | approved 2026-09-30 (UR rev 9, AT rev 9, tag g1-approved) |
| G2 | System requirements + system test spec | approved 2026-09-30 (SR rev 10, ST rev 7, tag g2-approved) |
| G3 | Architecture + integration test spec | approved 2026-09-30 (AR rev 2, IT rev 2, tag g3-approved) |
| G4 | Detailed design + unit test spec, per module | protocol and transport approved 2026-09-30 (tags g4-protocol-approved, g4-transport-approved); other modules not started |

## Project setup

- [x] Initialize git repository
- [x] AGENTS.md, README.md, TODO.md, LOGBOOK.md
- [x] Draft the V-model process document (docs/v-model/README.md)
- [x] User review and approval of docs/v-model/README.md (process baseline, 2026-09-30)
- [x] ADRs 0001 to 0006 for decisions made so far
- [x] Select project license: GNU GPLv3 with Commons Clause (ADR-0011, LICENSE)
- [x] Agent anonymity and ownership rule (ADR-0012, AGENTS.md)
- [x] User approval of ADR-0007 (synchronous Python API, 2026-09-30)
- [x] User approval of ADR-0008 (IEC 61508 functional safety, MISRA-aligned
      guidelines, coverage and HIL safety standards)
- [ ] User review of the changed decision and consequence text in the
      accepted ADR-0002, ADR-0003 and ADR-0005 (LOGBOOK 2026-09-29,
      "Corrections, second round")
- [ ] Record when and how ISDT was asked for documentation
- [ ] Initial commit (waiting for user permission)

## Requirements rewrite from the firmware findings

- [x] Write docs/research/device-model.md, the device as a host sees it,
      from the firmware findings (2026-09-30)
- [x] Rewrite 1-user-requirements.md against the device model, keeping
      the hazards and the 2026-09-29 decisions (revision 8, 2026-09-30):
      UR-032 to UR-036 added, TBD-017 and TBD-018 added, TBD-009 revised
      for Parallels
- [x] TBD-017 settled 2026-09-30: opt-in automatic reconnection per
      session (UR-037), USB recommended for unattended runs
- [ ] Buy a USB Bluetooth dongle for the Parallels VMs and check that
      Linux and Windows see the supply over it (TBD-009)
- [ ] TBD-018: read-only Bluetooth spike that records the unsolicited
      `0xC5` when a setting is changed on the front panel
- [x] Rewrite 2-system-requirements.md (revision 8) and 7-system-tests.md
      (revision 5) against the device model (2026-09-30): SR-048 to SR-054
      and ST-043 to ST-049 added, TBD-017 taken conservatively
- [x] 8-acceptance-tests.md revision 8: AT-032 to AT-036, coverage table
      with the Parallels VM code (2026-09-30)
- [x] Traceability generator scripts/check_traceability.py; the matrix is
      generated from now on (2026-09-30)
- [x] G1 and G2 with the user (2026-09-30, tags g1-approved and g2-approved)
- [x] G3 approved 2026-09-30 (AR rev 2, IT rev 2); TBD-021 and TBD-022
      settled
- [x] G4 protocol approved 2026-09-30 (docs/v-model/4-detailed-design/protocol.md rev 2)
- [x] Implement the protocol module from its DD, test first (2026-09-30):
      47 unit tests, 3 doctests, 97.6 % line coverage, verification record
      docs/v-model/records/2026-09-30-unit-protocol.md; workspace skeleton
      with the lints of AR-004
- [x] G4 transport approved 2026-09-30 (DD rev 2); ADR-0013 accepted
- [x] Implement the transport module from its DD, test first (2026-10-01):
      65 tests, 96.4 % line coverage with the ADR-0013 exclusion, record
      docs/v-model/records/2026-10-01-unit-transport.md
- [x] Transport DD rev 4 (2026-10-01): `ble` and `hid` crate-private,
      `AnyTransport` opaque, UT-TRANS-007 compile_fail doctests; 96.1 %
      line coverage, record run 2 in the file above
- [x] G4 link approved 2026-10-01 (DD rev 2, 20 items, 29 UT entries,
      tag g4-link-approved); AR-022, SR-028, IT-022, DD-TRANS-001 and
      DD-TRANS-004 changed and approved with it
- [x] Implement the link module from its DD, test first, by an Opus 5.5
      agent (2026-10-01): 41 tests, 96.4 % line coverage, record
      docs/v-model/records/2026-10-01-unit-link.md
- [x] Link DD rev 3 (four implementation gaps) approved 2026-10-01
- [ ] IT-020, IT-021, IT-022 (link integration tests in
      crates/mp305-core/tests/it_link_*.rs) once the mock's sends can be
      observed from tests (frame log or a shared record)
- [x] G4 session approved 2026-10-01 (DD rev 3, 27 items, 33 UT entries,
      tag g4-session-approved); AR-025, AR-027, AR-030, AR-050, SR-009,
      SR-020, SR-029, SR-046, IT-050, DD-TRANS-030 and DD-TRANS-031 changed
      and approved with it
- [ ] Implement the session module from its DD, test first, by an Opus 5.5
      agent (started 2026-10-01), with the mock, fixtures and error
      additions of its decisions 1 and 2; then the unit verification record
- [x] G4 store, G4 csv and G4 discovery approved 2026-10-01 (store rev 2,
      csv rev 2, discovery rev 2; tags g4-store-approved, g4-csv-approved,
      g4-discovery-approved); ADR-0014 accepted; AR-014, AR-032, SR-001,
      IT-014, IT-032, DD-PROTO-051 and DD-TRANS-002 changed and approved
- [ ] Implement the approved changes outside the new modules:
      `SetpointRange.min` (DD-PROTO-051), `Display` for `Kind`
      (DD-TRANS-002), the five timing constants (AR-014)
- [ ] Implement store, csv (with `civil`) and discovery from their DDs,
      test first, by Opus 5.5 agents; then the unit verification records
- [ ] G4 py: DD draft rev 1 written 2026-10-01
      (docs/v-model/4-detailed-design/py.md, 27 items, 20 UT entries,
      6 decisions); multi-lens review started 2026-10-01
- [ ] G4 app: DD draft rev 1 written 2026-10-01
      (docs/v-model/4-detailed-design/app.md, 16 items, 15 UT entries,
      5 decisions); multi-lens review started 2026-10-01
- [x] Session implementation reviewed adversarially 2026-10-01 (32
      confirmed findings); session DD rev 4 approved 2026-10-01 (settle
      100 ms; SR-019, SR-022, SR-024, AR-014, AR-025 changed; TBD-023)
- [ ] Session: fix the confirmed defects and implement DD rev 4 (Opus 5.5
      agent, started 2026-10-01); then gates, record, commit
- [ ] TBD-023: measure on hardware how long after a 0xC9 the 0xC3 shows
      the new setpoints and output state (bench session, user)
- [ ] From 2026-10-01 implementation work is delegated to Opus 5.5 agents
      (user's instruction); the session keeps DD, review, gates, records

## Research

- [x] Refactor docs/research by topic, index the versioned evidence and retain
      historical source material (started and completed 2026-09-30). Verify
      relocated tooling, links, captures and preserved exports. See
      docs/research/README.md and structure-map.json. Original firmware and
      Ghidra databases remain outside the repository.
- [x] Preserve seven Ghidra programs as XML without memory contents and JSON
      metadata, with hashes and restore/re-export comparisons (2026-09-30).
      All core comparisons pass; symbol and variable-storage import differences
      are recorded in docs/research/firmware/v51/ghidra/README.md.
- [x] Add a reusable workflow for staging, importing, comparing and publishing
      a future firmware release (2026-09-30). Tested on V51 with a fresh BLE
      import and rejected corrupt/mismatched inputs. See
      docs/research/workflow/README.md and spikes/firmware_workflow/.
- [x] Merge both firmware scratchpads with `docs/research/firmware.md`,
      reconcile conflicting claims and run the first combined verification
      pass (started and completed 2026-09-30). Preserved 3694 discovered
      function exports from the three images, plus the separate WCH reference.
      The portable suite passes 2835 cases; 16 separate input comparisons
      also pass. See docs/research/firmware/verification.md. Firmware binaries
      remain outside the repository.
- [x] Salvage the independent V51 jobs in ~/mp305b-fw-re (started and
      completed 2026-09-30). Preserve the original 110-file snapshot, complete
      33 probe jobs with checked termination and 657 distinct asserted cases,
      regenerate 324 observed command rows, reconcile 322 named locations and
      recover 3088 function exports. Reproduce the exports and rerun probes
      after relocation. See docs/research/firmware/v51/independent/README.md.
- [x] Complete the independent host-interface comparison and its Markdown,
      LaTeX and 22-page PDF report (2026-09-30). Earlier research statements
      are reviewed within the stated transport/command/bind/identity scope.
      The canonical PD and power-stage evidence remains available; complete
      PD internals, physical hardware mapping and update procedures stay open.
- [x] Reconstruct main scheduling and concrete RTOS resources, hardware
      bus paths, selected readable C and post-denial permission behavior
      (2026-09-30). See firmware/rtos.md, device/buses.md,
      firmware/readable.md and firmware/permissions.md under docs/research/.
- [~] Trace all remaining register accesses and hardware roles (started
      2026-09-30). The three-image inventory preserves 68937 decoded access
      records. Resolve parameter-dependent addresses and indirect callers;
      identify the PD SFR/XDATA map and exact main/companion MCU variants.
- [ ] Complete physical hardware mapping: assign power-controller selectors
      to power paths; trace fan, backlight, buttons, encoder, temperature and
      battery protection; determine storage ID, display/touch IDs, package
      pins, board topology and calibration. Keep inferred alternatives and
      confidence explicit until markings or measurements distinguish them.
- [ ] Complete RTOS caller/resource audit, event-bit-2 producer, heap lifetime
      accounting, allocation/stack hooks and timing measurements. Current
      offline checks do not measure stack high-water marks or CPU load.
- [ ] Extend readable reconstruction and original-instruction comparisons
      to the remaining handlers, PD state machines and update paths. Review
      decompiler warnings and unresolved paths before claiming coverage.
- [ ] Extend permission analysis to remaining indirect callers and physical
      device behavior. Shared C8/E2/E8/EE gates and the BE accessory path
      were verified offline on 2026-09-30. Hardware control-after-denial remains TBD-002;
      the existing project policy to disconnect after denial is unchanged.

- [x] Protocol extraction from ISDT WebLink JavaScript, first pass (report
      not yet in the repo; see LOGBOOK 2026-09-29, corrections)
- [x] Cross-check each first-pass protocol item against the WebLink bundles
      (finished 2026-09-29)
- [x] Write the cross-checked findings to docs/research/protocol.md, marking
      each item confirmed in code, confirmed on hardware, or inferred, and
      listing the WebLink asset file names that were read (docs/research/protocol.md)
- [x] Hardware: does the device advertise without the Web Link screen open?
      Yes (LOGBOOK 2026-09-29, advertising test)
- [ ] Optional: record a WebLink session with Apple PacketLogger (bind,
      `0xE0`/`0xE1`, `0xC4`/`0xC5`, `0xC2`/`0xC3`, request remote control).
      The capture is a finding on top of the device firmware.
- [x] Spike: connect over Bluetooth LE, read device info and one
      measurement, record a capture (spikes/ble_readonly/, capture in
      docs/research/captures/)
- [x] Confirm decoded `0xC3` setpoints against the device screen (13.00 V,
      1.000 A confirmed against the device screen)
- [ ] Confirm `0xC5` settings against the device's settings menu (charge
      limit 90 %, volume 2, OCP delay 50 ms, ramp 0.5 V per 0.1 s)
- [x] Find out whether the device shows anything during the 7.7 s bind: it
      asks the user to allow or deny
- [x] Spike: reconnect and check whether an allowed host is asked again:
      yes, the prompt appears on every connection
- [ ] TBD-006. Spike (needs user approval, non-WebLink bind frame): does
      fastBinding = 1 or a host-specific ID make the device remember a host?
      Code answer (2026-09-30, protocol.md 1.3): the Bluetooth chip stores
      up to five host IDs after a `19 00` and answers a repeat `0x18` with a
      non-zero last byte itself. The spike would confirm it on hardware.
- [ ] TBD-004. Spike: does USB HID need a confirmation on the device?
      Code answer (2026-09-30, protocol.md 1.3): bind is answered through
      the prompt on USB too, but remote control over USB is granted without
      a prompt. Hardware confirmation open.
- [ ] TBD-007, TBD-010, TBD-013. Spike over USB (read-only): product ID,
      report IDs, `0xE1` layout, serial number string, `0xAA` doubling.
      Added 2026-09-30: the HID top-level usage is 0, not the usage 4 that
      WebLink filters on, and the serial string request stalls
      (protocol.md 1.1). The spike should record what the OS enumerates.
- [ ] TBD-008. Spike over Bluetooth (read-only): how long the device waits
      for allow or deny, and what it replies when nobody presses a button.
      Code answer (2026-09-30, protocol.md 1.3): the Bluetooth chip drops an
      unbound link about 30 s after connecting; the prompt closes on its own
      and the reply is then `19 FF`. Hardware confirmation open.
- [ ] TBD-003. The 1.6.0.51 parser rejects a `0xC8` above 30.50 V and
      5.100 A (docs/research/firmware.md). Still open: what the output does
      at that top, against the 30.0 V and 5.0 A rating. Spike with the
      user's approval
- [~] TBD-005. Spike prepared: spikes/link_drop/ (needs user approval and
      MP305_HIL at the bench, nothing on the output). Answers what the device
      does with the output and remote control when the link drops, and gives
      the first hardware evidence for TBD-012. Ready to run. Code answer
      (2026-09-30, protocol.md 5.2): the remote grant is cleared, the output
      is left as it was. The spike confirms it on hardware.
- [ ] TBD-011. HIL capture with the output on (5 V, 100 mA, 100 Ω load,
      needs user approval): confirm measured voltage, current and power
      scaling
- [x] Spike: press deny and record the reply: `0x19 0xFF`
- [x] Spike: does `0xAF01` answer read requests without a successful bind?
      Yes, after a deny all reads still work
- [~] TBD-002. Spike prepared: spikes/control_after_deny/ (needs user approval
      and MP305_HIL at the bench, output never enabled). Tests whether the
      device grants remote control after a deny. Possible device security
      issue; if confirmed, consider reporting to ISDT. Ready to run
- [x] TBD-001. Requirements question (user): offer a read-only monitoring mode when
      the bind is denied, or refuse the connection entirely? Refuse and
      disconnect (user, 2026-09-29)
- [x] TBD-009. Question (user): which Linux and Windows machines are
      available for acceptance runs on hardware? Only the Mac (user,
      2026-09-29); the Linux and Windows gap goes to G1 for acceptance
- [x] TBD-015. Mitigations chosen and specified (2026-09-29): H-004 gets
      UR-030 (unclean-exit warning), UR-031 (bench-safety note) and the
      TBD-005 spike; H-006 gets the TBD-002 spike. Remaining under this TBD:
      run the two spikes, then the
      user accepts or rejects the residual risk at G1
- [ ] Implement UR-030 and UR-031 (unclean-exit marker and warning, bench
      note in both READMEs) when the modules are built (post-G4)
- [ ] TBD-016. Find out how an over-current trip shows in `0xC3` (bit 5,
      output off, or both) and check the 50 ms OCP delay in the settings
      menu (HIL with the user's approval)
- [x] TBD-014 settled 2026-09-30: macOS 13, Ubuntu 22.04, Windows 10 22H2
- [ ] TBD-012. Spike (needs explicit user approval, changes device state): request
      remote control with `0xC8` and observe `0xC9` (result codes, reply
      time), with nothing on the output
- [ ] Spike: the same over USB HID
- [x] Record the versions of the user's unit: System Version (main
      firmware) V1.6.0.40, Firmware Version V2.0.2.0, read over Bluetooth
      from `0xE1` and shown by WebLink (LOGBOOK 2026-09-29)
- [x] Re-run the read-only spike after the update and compare with the
      19:36 capture: layout unchanged, but the unit still reports
      application version 1.6.0.40 (LOGBOOK 2026-09-29)
- [ ] Find out why the update did not take effect: ask what WebLink and
      the device's own info screen show, power-cycle, re-read `0xE1`
      (read-only)
- [x] Write docs/research/protocol.md from the cross-check results and the
      deep-dive notes
- [x] Record that the device firmware is the main source of truth, with
      other findings on top of it (LOGBOOK 2026-09-29, "Firmware is the main
      source of truth")
- [x] Restore published image 1.6.0.51 and reconstruct the dispatcher,
      `0xC2`/`0xC3`, `0xC4`/`0xC5`, `0xC8`/`0xC9` and the USB descriptors
      (docs/research/firmware.md, 2026-09-29). Image files are outside the
      repository, at `~/.local/share/mp305b/fw/`
- [x] Walk the 1.6.0.51 handlers, the `0xAA` framer at `0xFF38`/`0xFFF0`,
      and record them (docs/research/firmware.md, 2026-09-29). `0xC6` checks
      `screenDirection` and does not store it. `0xE0` has two layouts. `0x20`
      is a block write and is not sent (UR-025)
- [ ] Obtain the missing main boot identity read by long E0 through address
      `0x1C`, the actual installed WCH library and per-unit calibration.
      Confirm physical UI action mapping and untested output behavior.
      The prior PD zero-gap interpretation and E2/E8 field offsets were
      corrected on 2026-09-30; exact MCU identification remains open.
      Existing hardware captures concern 1.6.0.40, not analyzed V51.

## Level 1: user requirements (G1)

- [x] Write docs/v-model/1-user-requirements.md from the agreed v1 scope,
      including constraint URs that cite ADR-0003 to ADR-0006
- [x] Hazard list in 1-user-requirements.md before G1 (`H-nnn`: hazard,
      cause, severity, mitigation)
- [x] Write docs/v-model/8-acceptance-tests.md alongside it, with the
      coverage table (test x OS x transport)
- [x] Start docs/v-model/traceability.md (kept by hand until the check
      script exists)
- [x] Revise the level 1 drafts (started and finished 2026-09-29): fix the hazard
      mitigation columns, add the latest protocol findings (bind prompt on
      every connection, reads after a deny, `0xE1` versions, discovery
      blocked by another connected app), add the missing Python streaming
      and CSV helper, add the TBD list, and bring protocol.md in line with
      the LOGBOOK
- [x] Independent review pass of the level 1 and draft level 2 documents
      (2026-09-29; 4 blockers, 13 should-fix, 12 minor, all applied)
- [ ] User review and approval (gate G1), including explicit acceptance of
      the open TBD list and of any unmitigated hazard

Agreed v1 scope (from the conversation on 2026-09-29):
- Core control: connect over Bluetooth LE or USB, set voltage and current
  limit, switch the output on and off, and read live voltage, current, power
  and regulation mode (constant voltage or constant current, CV/CC).
- Live chart (scrolling V/I/P plot) and CSV recording in the app. The Python
  library gets a measurement streaming and CSV logging helper, and no chart.
- Nice to have: ramps and similar sequence helpers in the Python library,
  driven from the host.
- Platforms: macOS, Linux, Windows.

## Level 2: system requirements (G2)

- [ ] docs/v-model/2-system-requirements.md (draft started 2026-09-29 on
      the unapproved level 1 revision, ahead of G1; not for
      approval before G1)
- [ ] docs/v-model/7-system-tests.md, with the coverage table (test x OS x
      transport) (draft started 2026-09-29 together with the SR draft)
- [ ] Rework the SR and ST drafts after G1, then an independent review pass
      before G2

## Level 3: architecture (G3)

- [ ] docs/v-model/3-architecture.md, using the unconfirmed draft in LOGBOOK
      2026-09-29 as input only. Open points to decide there:
  - task and channel design between device I/O and the egui UI (ADR-0005
    only requires I/O off the UI thread and a repaint request after new
    data)
  - who owns the Tokio runtime in the app (ADR-0007 covers the Python side)
  - whether protocol types derive serde traits
- [ ] docs/v-model/6-integration-tests.md

## Level 4: detailed design (G4, per module)

Entry criterion: the traceability check script exists before the first
module is implemented.

- [ ] Traceability check script: generates docs/v-model/traceability.md from
      the Parent columns, the test spec entries and the code tags, and
      reports every defect the process document lists
- [ ] DD + UT spec: protocol module (frames, checksum, commands)
- [ ] DD + UT spec: transport trait and mock transport. Constraint to record
      in this DD: the mock is public API of mp305-core behind a `mock` cargo
      feature (not `#[cfg(test)]`), so doctests, tests/ and the other crates
      can use it
- [ ] DD + UT spec: Bluetooth LE transport
- [ ] DD + UT spec: USB HID transport
- [ ] DD + UT spec: device API
- [ ] DD + UT spec: app state and logic
- [ ] DD + UT spec: Python bindings and helpers

## Tooling

- [ ] CI matrix (macOS, Linux, Windows): fmt, clippy, tests, coverage, wheels

## Later (not v1)

- Device program mode (sequences run by the device itself)
- USB-C PD source mode (custom PDO profiles, up to 28 V / 5 A / 140 W)
- Battery charger mode
- OVP and OCP settings, presets
- Async Python API
