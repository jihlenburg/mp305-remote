# ADR-0022: A close that leaves the output on, on request

- Status: Accepted
- Date: 2026-10-06
- Decided by: user, 2026-10-06 ("there should be a way to exit without
  cutting power"; "yes please" to the proposal)
- Related: SR-029, SR-030, UR-018, H-004, DD-PY-043, DD-SESS-053, ADR-0019

## Context

SR-029 makes every close of a library connection switch the output off:
the end of a `with` block, `close()`, an interrupt, the exit hook. That is
the safe default for a script that ends, and it is what the hands-on
checks rely on. It also means that a script which only watches the supply
cannot end without cutting the power to whatever the supply feeds; on
2026-10-06 a read-only check from this project switched off the user's
load that way, twice. The app has had the choice since its design: on
Disconnect it asks whether to switch the output off (SR-030), and the
core's `close(output_off)` carries the answer. Only the Python library
had no way to pass `false`.

## Decision

1. `Mp305.close(output_off: bool = True)`. With `False` the library
   releases remote control with the output as the fresh reading shows it
   and disconnects; the output stays as it is, and one WARN record says so
   (`close of <identifier> leaves the output as it is`). A value that is
   not a `bool` is a `TypeError`, checked before anything else.
2. The default stays `True`, and every implicit close keeps it: the end
   of a `with` block, an interrupt, an exception in flight, the exit hook.
   To leave the output on, a script calls `close(output_off=False)` as the
   last statement inside the block; the block's own close then finds the
   object closed and does nothing.
3. No new parameter on `connect`: nothing changes for existing scripts,
   and the safe path stays the one a script gets without thinking.
4. SR-029 and DD-PY-043 are revised accordingly; the README says in one
   sentence that the supply then keeps the output on with no host attached.

## Alternatives considered

- A parameter on `connect` that changes what the `with` block does at
  its end: convenient, but it moves the unsafe choice far away from the
  place where the output is left on, and an exception in flight would
  then also leave the output on.
- Keeping the library as it is and pointing to the app: the library is
  the tool for unattended scripts, which is where a monitor that must not
  cut the power lives.

## Consequences

- A script can end and leave the supply running. The supply then holds
  the output with no host attached, which the bench-safety note already
  describes; the WARN line makes it visible in the script's log.
- One unit test entry (UT-PY-030) and a 0.1.1 release of the library.
