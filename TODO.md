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
- [x] USB Bluetooth dongle for the Parallels VMs at hand 2026-10-02
      (ASUS, `0b05:1d70`); Linux and Windows see the supply's advertising
      over it (spikes/vm_dongle_scan, TBD-009)
- [ ] Connect to the supply from Linux and from Windows (read-only
      first), then the Bluetooth system tests there; needs the user's
      go-ahead. The dongle at hand delivers no received data on this
      Mac (spikes/dongle_acl_path, 2026-10-04). Linux: the user's machine
      "halobox" (native, own Bluetooth) is set up and sees the supply
      since 2026-10-04. Windows: needs a machine that is not a VM on
      this Mac
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
- [ ] IT-020, IT-021, IT-022 (link integration tests): part of the
      integration level started 2026-10-02 (see below)
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
- [x] csv and civil implemented 2026-10-01 (7 tests, record
      docs/v-model/records/2026-10-01-unit-csv.md)
- [x] store implemented 2026-10-01 (17 tests, record
      docs/v-model/records/2026-10-01-unit-store.md)
- [x] discovery implemented 2026-10-01 (11 tests and 3 doctests, two
      inspections, record
      docs/v-model/records/2026-10-01-unit-discovery.md); UT-DISC-009
      added with the user's approval (discovery DD rev 3)
- [x] Discovery DD rev 4 approved 2026-10-02 (DD-DISC-012 wording; a scan
      without a backend for its enabled transports fails, DD-DISC-010)
- [x] Discovery DD rev 4 implemented 2026-10-02 (record
      docs/v-model/records/2026-10-02-unit-core-amendments.md)
- [x] Store DD rev 3 and csv DD rev 3 approved 2026-10-01: UT-STORE-005
      and 010 amended, identifiers that cannot be stored are refused
      (DD-STORE-004, UT-STORE-011), UT-CSV-003 gains `cv` and `held_above`
- [x] Store DD rev 3, the two csv cases and the core additions of the py
      DD implemented 2026-10-01 (277 tests, record
      docs/v-model/records/2026-10-01-unit-core-additions.md)
- [x] Store DD rev 4 approved 2026-10-02 (UT-STORE-011 with the
      planted-marker step; no code change)
- [x] G4 py approved 2026-10-01 (py DD rev 2, 35 items, 28 UT entries,
      18 decisions, tag g4-py-approved); ADR-0015 accepted; AR-003, AR-014,
      AR-015, SR-036, ST-046, IT-003, IT-014, DD-PROTO-025, DD-PROTO-060
      and UT-PROTO-024 changed and approved with it
- [x] `mp305-py` and the `mp305` package implemented 2026-10-02 from py
      DD rev 2 and rev 3 (34 Rust and 128 Python tests, 96.2 % and 91.5 %
      line coverage, record docs/v-model/records/2026-10-02-unit-py.md);
      the intermittent failure was UT-PY-009 (a) reading its log records
      too early and is fixed
- [x] Py DD rev 4 approved 2026-10-02 (`__exit__` and other exceptions,
      the log thread's exit hook, UT-PY-024 (d) and (l), UT-PY-015 (g);
      no code change)
- [ ] Run `.github/workflows/wheels.yml` once by manual dispatch (the
      user's decision); Linux and Windows wheels are unverified
- [x] Integration level verified 2026-10-02 on the mock: 70 Rust and 54
      Python integration tests and eight inspection entries (records
      docs/v-model/records/2026-10-02-integration-*.md); the lint
      attributes and the timing literals found by the inspections fixed
- [x] Architecture rev 11, integration tests rev 10 and py DD rev 5
      approved 2026-10-02 (AR-002, AR-004, AR-016, AR-017 and twelve IT
      entries worded as the approved designs and the code have it;
      `_native.WAIT_SLICE_S`)
- [x] System tests written 2026-10-02 (`tests/system/`, 72 tests: 52 need
      the supply and are skipped without `MP305_HIL`, 20 run without one);
      no test has run on the supply yet
- [x] System tests rev 12 approved and ADR-0016 accepted 2026-10-02 (the
      person needed over Bluetooth, the tests' opt-ins and pre-flight as
      HIL rules in AGENTS.md, ST-003, 006, 012, 014, 017, 023 corrected)
- [ ] Still open in the system tests until a hardware run: ST-043 step 1,
      ST-050 step 3, the HID path after a re-plug (SR-055)
- [x] Linux build and mock test suites in the Ubuntu VM 2026-10-02: all
      gates pass on Ubuntu 24.04.5 aarch64 with Rust 1.99 (record
      docs/v-model/records/2026-10-02-unit-integration-linux.md); two
      findings of Rust 1.99's clippy fixed
- [x] Windows build and mock test suites in the Windows VM 2026-10-02
      (x86_64 toolchain under emulation, Rust 1.99): all gates pass
      (record docs/v-model/records/2026-10-02-unit-integration-windows.md);
      two test errors fixed (100 ns clock steps, a path separator)
- [x] Py DD rev 6 approved 2026-10-02: UT-PY-022 (e) allows 100 ms (test
      changed), UT-PY-024 names its POSIX-only cases
- [ ] Windows: the wait at exit after an uncaught Ctrl-C (DD-PY-008) has
      no test there (the three cases are POSIX only); decide whether a
      Windows variant with CTRL_C_EVENT is wanted
- [x] First hardware run 2026-10-02: ST-002 on macOS over Bluetooth
      passes (three scans, no connection; record
      docs/v-model/records/2026-10-02-system-macos-ble-discovery.md)
- [x] ST-002 on Linux over the dongle 2026-10-02: passes (record
      docs/v-model/records/2026-10-02-system-linux-ble-discovery.md); the
      Ubuntu VM was rebooted onto kernel 7.0.0-38 before
- [x] Discovery DD rev 5 approved and implemented 2026-10-02 (read
      `properties()` before `stop_scan`; record
      docs/v-model/records/2026-10-02-unit-discovery-rev5.md)
- [x] Signal strength on Linux verified 2026-10-03 (RSSI -29 dBm through
      the library on BlueZ; discovery DD rev 5)
- [x] ST-002 on Windows 2026-10-03: passes with the dongle present
      (record docs/v-model/records/2026-10-03-system-vm-ble.md)
- [x] Why connecting from the VMs fails, found 2026-10-04: the dongle
      (ASUS USB-BT600, `0b05:1d70`, RTL8761CU) hands no received data
      packet to its USB host, with its firmware loaded and also on the
      Mac without a VM (spikes/dongle_acl_path). The guests, the supply
      and the library are cleared. In the Linux PC halobox the same
      dongle works, so the loss is on this Mac's USB host side, which
      Parallels and libusb share
- [x] ST-002 on Linux, native (halobox), 2026-10-04: passes (record
      docs/v-model/records/2026-10-04-system-linux-ble-halobox.md); the
      user gave the go-ahead for that machine
- [x] ST-013 from Linux 2026-10-05: passes from halobox through the
      ASUS dongle with the bounds of ADR-0017 (record
      docs/v-model/records/2026-10-05-system-linux-ble-st013.md)
- [x] System tests on Linux without a person 2026-10-05 (halobox, the
      dongle): ST-002, ST-004, ST-013, ST-033 pass, and the parts
      without a person of ST-012, ST-017, ST-031, ST-039 and ST-043
      (record docs/v-model/records/2026-10-05-system-linux-ble-noperson.md)
- [x] ST-034 decided by the user 2026-10-05: a link that cannot keep
      up delivers what it has, with one warning per stream (SR-034)
- [ ] ST-034: word the expected result in the reworked revision 13 of
      the system tests, change the test after the approval, rerun on
      Linux
- [ ] The system tests on Linux that need a person, Load A or B, or USB
      (halobox, the dongle); needs the user at the supply
- [x] Decided by the user 2026-10-04 (ADR-0017): close bound 5 s,
      connect bound 20 s, an abandoned connect is cancelled before the
      error returns, one Bluetooth adapter is the supported setup
- [x] ADR-0017 and its revision approved by the user 2026-10-04: AR-014
      (rev 13), IT-014 (rev 11), protocol DD rev 8, link DD rev 4,
      discovery DD rev 7
- [x] ADR-0017 implemented 2026-10-04 and verified at unit and
      integration level on the Mac (record
      docs/v-model/records/2026-10-04-unit-integration-adr0017.md); the
      READMEs carry the one-adapter note
- [x] ADR-0017 on hardware 2026-10-05: with the dongle in halobox the
      connect takes 2.4 s and the close 1.9 s, and ST-013 passes. Through
      halobox's built-in adapter no connect came up on 2026-10-04 (plain
      connects there take 1 s to more than 40 s; its MT7925 module also
      runs the Wi-Fi on 2.4 GHz); the awaited cancel worked
- [x] System tests: the run record masks Bluetooth addresses and
      leaves out the dependencies' lines and discovery's lines about
      other devices (`44b2463`, 2026-10-05)
- [x] py DD revision 7 (DD-PY-006) approved by the user 2026-10-05:
      the log bridge passes records of dependencies only at DEBUG and
      above
- [ ] Implement py DD revision 7 (started 2026-10-05), verify on the
      Mac and on halobox (no dropped records in a connect on Linux)
- [ ] Check on Linux whether a Bluetooth link outlives its process
      (BlueZ owns the connection): the app's dropped close at exit and a
      killed Python process rely on "the link drops, the supply clears
      the grant" (DD-APP-023, py DD). From the review of ADR-0017
- [ ] ST-043 and ST-050 expect a recovery within 10 s; the design gives
      reconnection attempts every 5 to 35 s (5 to 20 s before ADR-0017).
      Settle the tolerance with the system tests' revision 13
- [ ] Find bound on Linux: a discovery of 10 s scans for Bluetooth LE
      for about 5.3 s, and halobox's built-in adapter missed the supply
      in one of eight scans. Measure before proposing a change
- [ ] System tests: when the pre-flight needs a person and none is there,
      the next test fails with "a session ... is already open" instead of
      skipping, because the pre-flight's background close still runs
      (seen on halobox 2026-10-04). Changed 2026-10-04: the pre-flight
      waits for that close. To verify on hardware with a host the supply
      does not know
- [ ] Put to the user: a machine for the Windows runs whose USB is not
      this Mac's (a native Windows PC, or a Windows VM on halobox with
      the dongle passed through); then ST-013 from Windows
- [x] Assess the attached NINA-B506 as an alternative Bluetooth controller
      (2026-10-04): USB enumeration identifies its FTDI UART and J-Link.
      NXP's MCX W71 HCI Black Box example provides a plausible UART-to-BlueZ
      path for Ubuntu, requiring EVK adaptation and hardware validation.
      Current board firmware is unknown; no flashing or implementation
      was performed. Findings and sources are in
      `docs/research/asus-usb-bt600-macos.md`.
- [ ] Diagnose the ASUS USB-BT600 receive path on the Mac (started
      2026-10-04, requested by the user after reconnecting the dongle):
      expose USB errors, compare local loopback transfer parameters and
      initialization, and distinguish a probe defect from a host/device
      compatibility problem. No power-supply commands are needed.
      Ubuntu 26.04 VM comparison completed 2026-10-04: both stock btusb
      and direct libusb reproduce zero received ACL bytes, with valid
      USB traces of successful writes and pending reads cancelled at
      timeout or cleanup. Bluetooth and the driver were restored. Record:
      `docs/research/asus-usb-bt600-macos.md`. The exact host/device defect
      remains open; another physical controller path and the modern
      IOUSBHost API have not yet been compared.
- [x] UT-PY-020 on halobox 2026-10-04: clippy installed there at the
      user's request, and the one finding of clippy 1.93 fixed
      (`615d949`, DD-PROTO-023). The test still fails on a machine with
      cargo and without clippy, since it skips only without cargo
- [x] ST-013 on macOS over Bluetooth 2026-10-03: the first connection of
      the library to the supply passes (record
      docs/v-model/records/2026-10-03-system-macos-ble-st013.md); the
      find bound became 10 s first (AR-014 rev 12)
- [x] System tests: tear the `frame_log` fixture down after the `supply`
      guard, so that the kept log covers the close and its release reply
      (2026-10-04; fixture dependency added, lint and setup order checked)
- [x] System tests on macOS over Bluetooth, batches A and B, 2026-10-03:
      18 entries pass in whole or in their automated part (record
      docs/v-model/records/2026-10-03-system-macos-ble-batch1.md)
- [ ] Put to the user: a connect right after a disconnect missed the
      supply once within the 10 s find bound ("no supply found"); a
      second scan window inside `connect`, or a documentation note
- [ ] Update docs/research (TBD-012): remote control seen on hardware
      2026-10-03 (prompt, `0xC9` 00 after ALLOW, commands applied, release
      answered)
- [ ] Remaining system tests on macOS over Bluetooth: batch C (the person
      entries, run by the user with `pytest -s`) and batch D (Load A and
      Load B); then USB, then the VMs
- [x] Prepare a reduced hardware verification matrix (2026-10-04,
      requested by the user): ADR-0018 and
      docs/v-model/hardware-verification-plan.md retain all 50 ST and
      36 AT entries, replace 54 repeated hardware cells with conditional
      evidence reuse, retain safety/platform checks, and define compatible
      release ST/AT sessions. Coverage and traceability checks pass.
- [ ] User approval of ADR-0018, ST revision 13, AT revision 10 and process
      revision 3 (drafted 2026-10-04). The approved baselines remain in
      force until approval. ADR-0017 is a separate pending decision.
- [x] ADR-0018 reworked 2026-10-05 along the review and the user's
      decisions (LOGBOOK, "ADR-0018 reworked after its review"): 3 system
      and 6 acceptance reuse cells left, Windows deferred, the hazard
      and no-person entries direct runs, four reuse rules
- [ ] After approval, implement the ST-019/ST-049 procedure corrections,
      prepare the missing acceptance scripts and release artifacts, then
      execute the reduced matrices and record each reuse analysis. No
      unrun entry is passed by the proposal.
- [ ] Continue macOS Bluetooth system tests with the user at the supply and
      nothing connected to the output (started 2026-10-04): remaining
      person-assisted entries. ST-012 screen comparison passed; ST-019
      failed after front-panel revocation, with a teardown error. Record:
      docs/v-model/records/2026-10-04-system-macos-ble-person.md.
- [x] Confirm output off and restoration to 12.00 V and 0.500 A after
      ST-019 of 2026-10-04 before another hardware run (user confirmed both
      2026-10-04).
- [x] Review ST-019 against the firmware's front-panel remote-control
      lock (2026-10-04): the library must explicitly release before the
      front-panel edit and request control afterwards. Front-panel
      revocation alone leaves the local grant stale until a command fails.
      Corrected procedures for ST-019, ST-038, ST-049, AT-023 and AT-034
      are drafted under ADR-0018; approval and implementation remain open.
- [x] System-test teardown: request control explicitly after a lost or
      denied grant before restoring settings (2026-10-04); mock check and
      ST-023 hardware teardown pass, final reading 12.00 V, 0.500 A, off.
      JSON records retain each phase's result and failure reason.
- [x] ST-023 step 2 on macOS Bluetooth (2026-10-04): the user disabled
      remote control on the front panel; the next command raised
      `RemoteControlLostError`, and restoration passed. Record:
      docs/v-model/records/2026-10-04-system-macos-ble-person.md.
- [x] Complete ST-048 on macOS Bluetooth (2026-10-04): all three cases
      passed in coordinated repetitions with confirmed user actions.
      Unanswered-prompt denial arrived after 61.827 s. No control
      command was sent while permission was pending in the delayed-Allow
      case. Final setpoints 12.00 V and 0.500 A, output off. Earlier
      timeout attempts were allowed or their button actions are uncertain.
      Record: the macOS person-test record of 2026-10-04.
- [x] Fix the stale-reading restoration check exposed by ST-048
      (2026-10-04): always read settled values on an open connection and
      verify the restored setpoints and output off. Mock checks and the
      non-HIL system suite pass. Hardware restoration from 1.00 V to
      12.00 V was confirmed in the 03:01 ST-048 attempt, output off.
- [x] Clarify the LED connection timing for the 2026-10-04 hardware runs:
      the user confirmed connecting it after the tests, resolving the
      no-load setup of ST-012, ST-019, ST-023 and ST-048. Disconnection
      and output off were confirmed before the later ST-048 repetitions.
- [x] ST-021 on macOS Bluetooth (2026-10-04): `set_voltage(1.0)` in PD
      mode raised `ModeError` without a control frame. The user restored
      DC mode; final telemetry confirmed 12.00 V, 0.500 A and output off.
      One initial discovery failed; the retry passed. Record:
      docs/v-model/records/2026-10-04-system-macos-ble-person.md.
- [ ] Next hardware runs of the system tests (the user's go-ahead per
      session): the first connection on macOS over Bluetooth with a person
      to press ALLOW (ST-013 and the entries without a load), then USB,
      then the VMs
- [ ] System level (ST): the hardware runs on macOS, and on Linux and
      Windows in the VMs with the dongle; needs the user's go-ahead per
      session, the supply, and a Rust toolchain in the guests
- [x] G4 app approved 2026-10-01 (app DD rev 2, 25 items, 25 UT entries,
      13 decisions, tag g4-app-approved); AR-033, AR-041, SR-030, SR-041,
      ST-030 and ST-038 changed and approved with it
- [x] `mp305-app` implemented 2026-10-02 from app DD rev 2 and rev 3
      (129 tests, 96.2 % line coverage of the non-drawing code, record
      docs/v-model/records/2026-10-02-unit-app.md with the UT-APP-020 and
      021 inspections)
- [x] App DD rev 4 approved 2026-10-02 (three test entries corrected,
      three statements added; no code change)
- [ ] UT-APP-011 and UT-APP-015 do not pin the first poll of DD-APP-003
      (they pass with it removed); strengthen them or add a case
- [ ] UT-APP-021 demonstration (build and sign the macOS bundle) and
      UT-APP-024 (manual, with the supply): user's bench session
- [x] Session implementation reviewed adversarially 2026-10-01 (32
      confirmed findings); session DD rev 4 approved 2026-10-01 (settle
      100 ms; SR-019, SR-022, SR-024, AR-014, AR-025 changed; TBD-023)
- [x] Session implemented from DD rev 4 (2026-10-01): 232 tests, 95.3 %
      line coverage, record docs/v-model/records/2026-10-01-unit-session.md
- [x] Session DD rev 5 approved 2026-10-01 (the four gaps of the final
      review, two test entries restated, UT-SESS-061 to 065 added, the
      session changes the product designs need)
- [x] Session DD rev 5 implemented 2026-10-01 (289 tests, record
      docs/v-model/records/2026-10-01-unit-session-rev5.md); the session
      tests use `fixtures::reply_route` and `on_air`
- [x] Session DD rev 6 approved 2026-10-02 (UT-SESS-044 (5), DD-SESS-053
      (b), DD-SESS-035; no code change, the code already behaves so)
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
