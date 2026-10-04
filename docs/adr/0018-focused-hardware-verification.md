# ADR-0018: Focused hardware verification and evidence reuse

- Status: Proposed
- Date: 2026-10-04, reworked 2026-10-05
- Decided by: pending approval of the reworked matrices; the user
  authorized preparing the proposal on 2026-10-04 and decided the points
  of an independent review on 2026-10-05 (LOGBOOK, "Independent review of
  ADR-0018" and "Decisions of the user on the log bridge, ST-034 and
  ADR-0018")
- Related: ADR-0001, ADR-0002, ADR-0008, ADR-0016, ADR-0017 (accepted);
  7-system-tests.md revision 13; 8-acceptance-tests.md revision 10;
  hardware-verification-plan.md; AGENTS.md

## Context

The MP305B V51 firmware reconstruction has matched the exercised grant,
denial, timeout, revocation and telemetry paths. Hardware runs also found
test-teardown defects, a front-panel procedure that assumed settings
could be edited during a grant, and OS-specific connection and close
timing problems. Protocol confidence supports reuse of shared behavior;
it does not establish the OS transport, electrical or app behavior.

The approved matrices repeat many shared behaviors across six OS and
transport combinations. The user asked for a concrete reduction of that
duplication while retaining safety and platform coverage.

The baseline matrices give Linux and Windows the code `VM`: the Parallels
VMs on the Mac, with CI as the substitute for Bluetooth until a USB
Bluetooth dongle was at hand. The dongle came, and it cannot carry a
connection on the Mac, with or without a VM (LOGBOOK 2026-10-04). Linux
hardware runs therefore use a native machine, where the first system
tests passed on 2026-10-05 and showed platform differences (close and
connect timing, a slower reading rate, an unsuitable built-in adapter).
Windows has no host with a working path to the supply.

A first draft of this ADR turned 36 system cells and 18 acceptance cells
into reuse cells. An independent review found that it took hardware
evidence from hazard-related entries, the physical OCP trip among them,
that several reuse cells saved nothing, and that the change of the `VM`
and `CI` codes was not stated as a decision. The user decided each point;
this text is the result.

Existing firmware findings, passing tests and failed attempts remain
evidence with their original scopes. No previous failure is accepted as
a deviation by this proposal.

## Decision

Proposed, not yet in force:

1. Keep all 50 ST entries and all 36 AT entries, their requirement
   mappings, the supported platforms and both transports. Each entry
   retains its required observations.
2. A hardware cell (`H`) means the procedure on an actual host with a
   working path to the supply: a native machine, or a VM whose device
   pass-through works. The baseline's codes `VM` and `CI` are withdrawn.
   A missing host leaves the cell open; nothing is downgraded to mock
   tests.
3. Windows is deferred. Its cells are hardware obligations and stay open
   until a host exists. No reuse is defined for Windows, and the README
   says that Windows is not verified on hardware. Neither test level can
   be closed while they are open.
4. Conditional analysis-based reuse (`R`) is permitted for exactly these
   cells: ST-012 on Linux over both transports (the comparison with the
   supply's screens), ST-035 on Linux over Bluetooth, and the USB cells
   of AT-012, AT-013 and AT-014 on macOS and on Linux, which reuse the
   witnessed Bluetooth acceptance result of the same OS and release
   artifacts. Every other hardware cell is a direct run.
5. Hazard-related entries are never reuse cells: ST-014, ST-015, ST-021,
   ST-024, ST-027 and every other entry that the first draft already
   kept. Entries that need no person over a transport are not reuse
   cells there either (ST-033, ST-035 over USB, AT-003, AT-017 and AT-029
   over USB), nor are ST-009 and ST-048, whose timing runs through each
   OS's Bluetooth stack.
6. A reuse record names the source result and its raw evidence, the
   target artifacts and platform, relevant code and dependency changes,
   current target UT/IT results, target hardware prerequisites,
   rationale, limits and remaining differences. Four rules bind it:
   the user signs every reuse record off, for system cells as for
   acceptance cells; the source result comes from the build under test
   or is reviewed again against its commit; a prerequisite or a matching
   system entry counts only when it was run directly, never when it is
   itself a reuse cell; and the 30 min memory check of ST-038 is made per
   transport. A missing prerequisite leaves the cell open. Unexplained
   differences require direct execution.
7. Batch compatible work by bench setup and use a single physical event
   for multiple entries only when every entry's procedure, preconditions
   and observations are satisfied. Preserve per-ID results and each
   automated test's own ID. A shared trace is not itself a second pass.
   Bind, grant, close, crash and reconnect cases retain their required
   fresh sessions and state directories. The display-range step of
   ST-038 may be shared between transports on the same OS and binary
   after analysis.
8. Use release artifacts for future combined ST/AT sessions. The user
   performs or witnesses AT observations. Earlier development-build ST
   runs cannot become acceptance results retrospectively.
9. Correct front-panel preparation in ST-019, ST-038, ST-049, AT-023 and
   AT-034. ST-019 explicitly releases and requests control around the
   edit. Its 2 s procedure clock starts after re-grant and a qualifying
   reading; the SR-019 100 ms settle and 1 s age limits stay intact.
   AT-037 explicitly names the current host OS and the USB cable variant
   already required by its coverage table. ST-034 states its expected
   result for a link that cannot keep up with a rate, as SR-034 already
   requires: the link's own count, not below the 2 per second of SR-013,
   with exactly one warning for the stream.
10. Preserve ADR-0008 coverage targets and coding rules, ADR-0016 HIL
    opt-ins and pre-flight, the load limits, output-off and restoration
    rules, all physical fault and priority-off checks, and the existing
    completion and user-approval gates. No production change is
    authorized by this ADR.
11. On approval AGENTS.md is amended in three places, so that the
    standing rules and this ADR agree: "Verification records" names the
    reuse record and its fields and says that a cell marked `R` in an
    approved coverage table is verified by that record instead of a run;
    the sentences on system and acceptance tests on real hardware say
    "except the cells an approved coverage table marks for reuse
    (ADR-0018)"; and "Functional safety and coding standards" lists
    ADR-0018 with the other ADRs that add to ADR-0008.

## Alternatives considered

- Repeat the full original matrices: simple bookkeeping, but duplicates
  shared logic and display observations even after equivalent evidence
  exists. Direct repetition is kept for OS, transport and safety
  behavior.
- The first draft's wider reuse (36 system and 18 acceptance cells):
  rejected after the review, for the reasons in Context.
- No reuse at all, only the procedure corrections: simpler, but the few
  cells left need a person for a comparison or a prompt whose logic is
  shared, which is what reuse is for.
- Keep the CI substitute for Windows, so that a level can be closed
  without Windows hardware: rejected by the user; the gap is stated
  instead.
- Stop HIL because the firmware is understood: rejected. It cannot
  demonstrate actual electrical measurements, OS timing, host cleanup,
  packaging or the user interface.
- Declare unrun cells passed from a mock suite or an old run: rejected.
  Every reuse cell requires a specific analysis and its prerequisites.
- Validate only macOS: rejected. Linux has already exposed differences,
  and the supported-platform requirements remain unchanged.

## Consequences

The ST matrix has 207 hardware cells and 3 reuse cells, the AT matrix 171
and 6. Against the baseline's 210 and 177 cells that named a host (`HW`
or `VM`), the reduction is 9 cells. The larger change is in what the
cells demand: an actual host instead of a VM that could fall back to CI.
These are entry/OS/transport obligations, not test-process counts or a
duration estimate.

Of the hardware cells, 70 system and 59 acceptance cells are Windows
cells and open until a host exists. The system and acceptance levels
cannot be reported as verified before that, and a release before then
names Windows as unverified on hardware.

Compatible ST and AT checks can share bench setup, observations and
captures. This does not permit silently joining existing pytest tests
that require separate sessions or bypassing the load opt-ins. After
approval, update the changed test procedures (ST-019, ST-034, ST-049 in
the test code) and any selectors or combined drivers with per-ID
reporting.

The macOS results of 2026-10-03 predate the connect and close bounds of
ADR-0017. The entries that depend on connecting and closing are run again
on the current build; the others are reviewed against it.

Firmware, relevant code, dependency, OS, adapter and packaging changes
invalidate the affected reuse conclusions. Reassess them before crediting
a new build. Document remaining coverage gaps as open, or obtain a
separate explicit acceptance of a named deviation. This ADR accepts none.
