# ADR-0013: Coverage exclusion for vendor-library glue in the transports

- Status: Accepted
- Date: 2026-09-30
- Decided by: user, on the agent's recommendation
- Related: ADR-0008, AR-016, AR-017, DD-TRANS-010 to DD-TRANS-022, IT-016, IT-017, ST-008, ST-039, ST-040

## Context

`mp305-core` talks to the supply through `btleplug` (Bluetooth LE) and
`hidapi` (USB HID). The code that calls those libraries connects, subscribes,
writes, reads and disconnects; it can only run against a real supply or the
real OS stacks. ADR-0008 measures line coverage with `cargo llvm-cov` and
allows an exclusion for one class of code, the GUI drawing modules under
`ui/`, each exclusion carrying a comment with its reason and the test that
covers it instead. The transport design (docs/v-model/4-detailed-design/
transport.md, section 6) separates the vendor glue into two files,
`transport/ble.rs` and `transport/hid.rs`, and keeps every pure part
(route mapping, report packing, the frame decoders) in files that unit tests
reach. Without an exclusion the glue counts against the 85 % target of the
rest of `mp305-core`, and the only way to cover it in CI would be a backend
trait with a scripted implementation, which tests the script, not the glue.

## Decision

The two glue files are excluded from the coverage measurement with
`--ignore-filename-regex 'transport/(ble|hid)\.rs'`. Every function in them
carries a comment naming this ADR and the covering verification: inspection
(IT-016, IT-017) and the system tests on the real supply (ST-008, ST-039,
ST-040). Nothing but vendor-library calls and their immediate error mapping
may live in those files; any logic that can be tested without a device goes
into a sibling file that is measured. The exclusion pattern is written into
the `cargo llvm-cov` command in AGENTS.md.

## Alternatives considered

- Cover the glue through a backend trait with a scripted implementation:
  adds a layer whose only purpose is to be mocked, and the coverage it
  produces measures the script's paths, not the library's behaviour. Lost
  on value per line.
- Accept the lower measured coverage without an exclusion: makes the 85 %
  target meaningless for the rest of the crate and hides real gaps behind
  a known one. Lost on clarity.
- Run the coverage measurement on hardware: needs the supply for every CI
  run and the HIL safety rules; the system tests already exercise the glue
  on hardware. Lost on practicality.

## Consequences

Two files are verified by inspection and hardware tests instead of unit
tests; the inspection entries name what to look for. The rule that nothing
testable may live in an excluded file has to be enforced in review. A future
transport (for example a serial one) that adds glue would extend this ADR's
pattern rather than get a silent exclusion.
