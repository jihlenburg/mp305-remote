# ADR-0018: Focused hardware verification and evidence reuse

- Status: Proposed
- Date: 2026-10-04
- Decided by: pending approval of the concrete matrix; the user authorized
  preparing it on 2026-10-04
- Related: ADR-0001, ADR-0002, ADR-0008, ADR-0016, ADR-0017;
  7-system-tests.md revision 13; 8-acceptance-tests.md revision 10;
  hardware-verification-plan.md

## Context

The MP305B V51 firmware reconstruction has matched the exercised grant,
denial, timeout, revocation and telemetry paths. Hardware runs also found
test-teardown defects, a front-panel procedure that assumed settings
could be edited during a grant, and OS-specific connection and close
timing problems. Protocol confidence supports reuse of shared behavior;
it does not establish the OS transport, electrical or app behavior.

The approved matrices repeat many shared behaviors across six OS and
transport combinations. The user requested a concrete reduction of that
duplication while retaining safety and platform coverage. Existing
firmware findings, passing tests and failed attempts remain evidence with
their original scopes. No previous failure is accepted as a deviation by
this proposal.

## Decision

Proposed, not yet in force:

1. Keep all 50 ST entries and all 36 AT entries, their requirement
   mappings, the supported platforms and both transports. Each entry
   retains its required observations. Every hardware ST entry retains
   direct evidence on every applicable transport on macOS. The limited
   same-OS AT reuse is defined separately below.
2. Permit conditional analysis-based reuse for ten shared ST entries on
   Linux and Windows. The exact cells, target hardware prerequisites and
   source evidence are in the ST matrix and execution plan. Every other
   hardware cell remains a hardware obligation on its named OS.
3. Permit six AT entries to reuse a witnessed Bluetooth acceptance result
   for the USB column on the same OS and the same release artifacts,
   supported by USB system and release hardware checks. There is no
   cross-OS substitution for witnessed app behavior. The user reviews the
   equivalence analysis; it is never labeled as a witnessed USB run.
4. A reuse record must name the source result and its raw evidence, the
   target artifacts and platform, relevant code and dependency changes,
   current target UT/IT results, target hardware prerequisites, rationale,
   limits and remaining differences. A missing prerequisite leaves the
   cell open. Unexplained differences require direct execution.
5. Batch compatible work by bench setup and use a single physical event
   for multiple entries only when every entry's procedure, preconditions
   and observations are satisfied. Preserve per-ID results and each
   automated test's own ID. A shared trace is not itself a second pass.
   Bind, grant, close, crash and reconnect cases retain their required
   fresh sessions and state directories.
6. Use release artifacts for future combined ST/AT sessions. The user
   performs or witnesses AT observations. Earlier development-build ST
   runs cannot become acceptance results retrospectively.
7. Correct front-panel preparation in ST-019, ST-038, ST-049, AT-023 and
   AT-034. ST-019 explicitly releases and requests control around the
   edit. Its 2 s procedure clock starts after re-grant and a qualifying
   reading; the SR-019 100 ms settle and 1 s age limits stay intact.
   AT-037 explicitly names the current host OS and the USB cable variant
   already required by its coverage table.
8. Preserve ADR-0008 coverage targets and coding rules, ADR-0016 HIL
   opt-ins and pre-flight, the load limits, output-off and restoration
   rules, all physical fault and priority-off checks, and the existing
   completion and user-approval gates. No production change is authorized
   by this ADR. ADR-0017 remains a separate pending decision.

## Alternatives considered

- Repeat the full original matrices: simple bookkeeping, but duplicates
  shared logic and display observations even after equivalent evidence
  exists. Keep direct repetition for OS, transport and safety behavior.
- Stop HIL because the firmware is understood: rejected. It cannot
  demonstrate actual electrical measurements, OS timing, host cleanup,
  packaging or the user interface.
- Declare unrun cells passed from a mock suite or an old run: rejected.
  Every reuse cell requires a specific analysis and its prerequisites.
- Validate only macOS: rejected. Linux has already exposed differences,
  and the supported-platform requirements remain unchanged.

## Consequences

The proposed ST matrix replaces 36 of 210 direct hardware cells with
conditional reuse, leaving 174. The AT matrix replaces 18 of 177 with
same-OS reuse, leaving 159. These are entry/OS/transport obligations,
not test-process counts or a duration estimate. Analysis and inspection
cells are excluded. Some retained cells already have candidate results;
all acceptance hardware work still needs release artifacts and witnesses.

Compatible ST and AT checks can share bench setup, observations and
captures. This does not permit silently joining existing pytest tests
that require separate sessions or bypassing the load opt-ins. The present
test harness is unchanged. After approval, update the changed test
procedures and any selectors or combined drivers with per-ID reporting.

Firmware, relevant code, dependency, OS, adapter and packaging changes
invalidate the affected reuse conclusions. Reassess them before crediting
a new build. Document remaining coverage gaps as open, or obtain a
separate explicit acceptance of a named deviation. This ADR accepts none.
