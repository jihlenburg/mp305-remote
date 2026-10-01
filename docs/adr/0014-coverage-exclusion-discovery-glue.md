# ADR-0014: Coverage exclusion extended to the discovery glue

- Status: Accepted
- Date: 2026-10-01
- Decided by: user, on the agent's recommendation (G4 discovery, 2026-10-01)
- Related: ADR-0008, ADR-0013, AR-032, DD-DISC-006, DD-DISC-010 to
  DD-DISC-013, IT-002, IT-032, ST-001 to ST-003, UT-DISC-010, UT-DISC-011

## Context

ADR-0013 excludes the two transport glue files from the coverage
measurement because they only call `btleplug` and `hidapi` and can run only
against the real OS stacks, and it says that a future addition of glue
"would extend this ADR's pattern rather than get a silent exclusion". The
discovery module (docs/v-model/4-detailed-design/discovery.md) adds two
such files, `discovery/ble.rs` (the scan loop over `Central::events`,
`start_scan`, `stop_scan` and `properties`) and `discovery/hid.rs`
(`HidApi::new` and `device_list`). Its design moves every decidable rule
into `discovery/classify.rs`: the two classifiers, the sighting accumulator
that decides which events count as "advertising now", the choice of the
advertised name, the identifier shape test and the connect plan, all unit
tested. ADR-0008 says a coverage standard changes only through an ADR, and
ADR-0013's scope is the transports, so the extension needs its own record.

## Decision

`discovery/ble.rs` and `discovery/hid.rs` are excluded from the coverage
measurement under the same rule as ADR-0013: nothing but vendor-library
calls, their immediate error mapping and the hand-over to the pure part may
live in them; every function carries a comment naming this ADR and the
covering verification (inspection UT-DISC-010 and UT-DISC-011, the
integration test IT-032 for the classification they feed, and the system
tests ST-001 to ST-003 on the real supply). The pattern in the
`cargo llvm-cov` command of AGENTS.md becomes
`(transport|discovery)/(ble|hid)\.rs`.

## Alternatives considered

- Measure the two files and accept the lower number: the module's 85 %
  target would be unreachable without a device, which hides real gaps
  behind a known one. Lost on clarity, as in ADR-0013.
- Cover the glue through a backend trait with a scripted implementation:
  the scripted paths are the script's, not `btleplug`'s or `hidapi`'s.
  Lost on value per line, as in ADR-0013.
- Widen ADR-0013 by editing it: an accepted ADR is not edited; a new one
  that extends it keeps the history readable.

## Consequences

Four files in `mp305-core` are now verified by inspection and hardware
tests instead of unit tests. The review rule that nothing testable may live
in an excluded file applies to the discovery glue, and the discovery DD's
section 4 lists what the inspection looks for. Any further glue (a serial
transport, another discovery backend) needs a further ADR.
