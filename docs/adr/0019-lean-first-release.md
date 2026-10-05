# ADR-0019: A lean path to the first release

- Status: Accepted
- Date: 2026-10-05
- Decided by: user, 2026-10-05 ("find a way to finish the software without
  all of this overcomplicated setup. we're a remote control library not
  the space shuttle program. we can always calibrate later with a
  precision load", and "We trust the readings of the mp305b")
- Related: ADR-0001, ADR-0008, ADR-0016, ADR-0018, TODO.md ("Release 0.1"),
  `scripts/hardware_check.py`

## Context

The system and acceptance test matrices ask for 378 hardware results
over three operating systems and two transports, with two precision
loads and a person at the supply for most of them (ADR-0018). The bench
has one lamp as a load and no multimeter, Windows has no test machine,
and the work to complete the matrices is out of proportion for a remote
control library and its app. The software itself is implemented and
passes its unit and integration tests on macOS, Linux and Windows.

## Decision

1. The first release, 0.1.0, is gated by a short hands-on checklist and
   by the automated gates, not by the system and acceptance matrices:
   - `scripts/hardware_check.py` passes on a real supply from macOS over
     Bluetooth and over USB, and from Linux over Bluetooth. The script
     finds the supply, connects, reads, sets a voltage and a current
     limit, switches the output on and off, restores the setpoints and
     closes.
   - The app does the same by hand on macOS: connect, set, switch on and
     off, show the chart, record a CSV file.
   - The unit and integration tests and the lint gates pass where they
     run today.
   - The release artifacts build.
2. The supply's own readings are the reference. There is no independent
   measurement of voltage, current or power, and any load at hand may be
   used. Calibration against a precision load is later work.
3. The system and acceptance test specifications, their matrices and the
   plan of ADR-0018 stay in the repository as a backlog and as a
   description of what could be verified. They do not gate a release, and
   no test level is reported as verified. Results recorded so far stand
   as they are.
4. The README says what was checked on hardware and what was not:
   Windows, the accuracy of the readings, the fault trips, and whatever
   else the checklist does not cover.
5. The coding standards of ADR-0008 stay; they are in the code and its
   gates. The project claims no verified safety integrity level. Bench
   safety is the user's: the README's notes on a hardware current limit
   and a safe load remain.
6. The rules for the automated hardware tests (ADR-0016: `MP305_HIL` and
   the opt-ins) stay for those tests. The hands-on check is run by the
   user, or at the user's request with the voltage and current the user
   names.

## Alternatives considered

- Complete the matrices of ADR-0018 first: not possible with the bench
  at hand, and not wanted.
- Adapt every load test to the lamp and keep the matrices as the gate:
  still most of the effort, for results whose reference is the supply
  itself.
- Release without any hardware check: rejected. USB and the app had
  never met the real supply; a short check finds what a mock cannot.

## Consequences

- The release can follow three short sessions at the bench instead of
  hundreds of recorded results.
- Known gaps are stated instead of closed: no hardware evidence for
  Windows, no check of the readings against a reference, no over-current
  trip or load regulation test beyond what the hands-on check shows, no
  acceptance test witnessed entry by entry.
- A defect that only the full matrices would have found can reach a
  user. The first release is therefore numbered 0.1.0 and described as
  such.
- The backlog can be picked up entry by entry when a precision load, a
  Windows machine or a reason exists.
