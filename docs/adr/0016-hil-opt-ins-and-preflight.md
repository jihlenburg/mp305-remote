# ADR-0016: Further opt-ins and a pre-flight check for hardware-in-the-loop tests

- Status: Accepted
- Date: 2026-10-02
- Decided by: user, on the agent's recommendation (2026-10-02, after the system tests were written)
- Related: ADR-0008, AGENTS.md ("Working with the real device",
  "Hardware-in-the-loop tests"), 7-system-tests.md section 1,
  `tests/system/conftest.py`, `tests/system/README.md`

## Context

AGENTS.md gates every hardware-in-the-loop test behind `MP305_HIL=1` and
`MP305_HIL_DEVICE`, and ADR-0008 says its HIL safety standards change
only through an ADR. Writing the system tests showed three things the
gate does not cover:

1. Some entries need a load on the output and all others need the output
   free. One variable for "hardware allowed" cannot tell the two apart, so
   a run with a load connected would also run the tests that assume
   nothing is connected, and the reverse.
2. Some entries need a person at the supply (to allow or deny a prompt,
   to change a setting on the front panel, to pull a cable). Over
   Bluetooth this includes every entry with a control command, since the
   first control call of a connection opens the remote-control prompt.
   Without a person such a test would sit in a prompt or fail half way.
3. A run that starts with the output on has something unexpected on the
   bench.

## Decision

The HIL rules of AGENTS.md gain, in addition to the two variables:

- `MP305_HIL_LOAD=A` or `B`: the named load of 8-acceptance-tests.md is
  on the output. Only the entries that name that load run; every other
  HIL test skips. Without the variable the entries with a load skip.
- `MP305_HIL_PERSON=1`, with `pytest -s`: a person is at the supply. The
  entries that need one skip without it, and tell the person on the
  terminal what to do and when.
- `MP305_HIL_DEVICE_HID=<path>`: the HID path of the same unit, for the
  one entry that uses both transports at once (ST-043).
- `MP305_HIL_RECORD=<file>`: the run writes its record (OS, transport,
  the supply's versions, the result per test ID) there.
- A pre-flight: before the first test that connects, the run connects
  once and stops when the output is on (its close switches the output
  off). Tests that only discover make no connection.
- Every connection of a HIL test is opened with user limits of 5 V and
  0.1 A unless the entry documents more, and a fixture switches the
  output off, restores the setpoints the supply had and has the person
  undo front-panel changes in teardown, also after a failure.

An agent sets none of these unless the user asks for it in the current
session, as for `MP305_HIL`.

## Alternatives considered

- Separate pytest markers for loads and persons: `pyproject.toml`
  registers only `hil` and `spec` with strict markers (DD-PY-060), and a
  marker selects tests but does not state what is on the bench.
  Environment variables state the bench, and the tests check them.
- No pre-flight: a run on a bench with the output on would start its
  first test with a live output that no test asked for.

## Consequences

A hardware run is described by its variables, which the run's record
keeps. The person tests are run by the user in a terminal, since they
read answers from standard input. AGENTS.md's HIL section lists the
variables.
