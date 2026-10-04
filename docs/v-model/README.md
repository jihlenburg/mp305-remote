# Development process: V-model

Status: changed (revision 3, approval pending). Approved baseline: revision 2, user, 2026-09-30. The evidence-reuse and combined-execution rules in "Verification and validation" are proposed under ADR-0018.

The project follows the V-model
([ADR-0001](../adr/0001-v-model-docs-as-code.md)). The process baseline is
approved; the revision 3 changes wait for review and approval, which
[TODO.md](../../TODO.md) tracks.

Each design level on the left side of the V has a matching verification level
on the right side. The test specification for a level is written at the same
time as the design for that level, not after the code exists.

```
 1 User requirements (UR) ─────────────────────────── 8 Acceptance tests (AT)
    2 System requirements (SR) ───────────────── 7 System tests (ST)
       3 Architecture (AR) ─────────────── 6 Integration tests (IT)
          4 Detailed design (DD) ──── 5 Unit tests (UT)
                          Implementation
```

## Documents

| Level | Design document | ID prefix | Verified by | Test specification | Test ID prefix |
|---|---|---|---|---|---|
| 1 | [1-user-requirements.md](1-user-requirements.md) | `UR-`, hazards `H-` | Acceptance tests | [8-acceptance-tests.md](8-acceptance-tests.md) | `AT-` |
| 2 | [2-system-requirements.md](2-system-requirements.md) | `SR-` | System tests | [7-system-tests.md](7-system-tests.md) | `ST-` |
| 3 | [3-architecture.md](3-architecture.md) | `AR-` | Integration tests | [6-integration-tests.md](6-integration-tests.md) | `IT-` |
| 4 | [4-detailed-design/](4-detailed-design/)`<module>.md`, one file per module | `DD-<MODULE>-` | Unit tests | "Unit test specification" section at the end of the same DD file | `UT-<MODULE>-` |

IDs have three digits, for example `UR-001`, `DD-PROTO-004` or `UT-PROTO-007`.
Open points are written as `TBD-nnn`. A design item is an AR- or DD- entry.

Level 5 of the V has no file of its own. Each DD file ends with a section
"Unit test specification", a table with the columns UT ID, verifies DD ID,
input, expected result and test path.

A document that does not exist yet has not been started. The current state of
each level lives in TODO.md.

### Document header and revision table

Every V-model document starts with a status line: `Status: draft`,
`Status: in review`, `Status: approved` or `Status: changed`. `changed` means
that an approved document has changes waiting for the user's approval. Once
the document is approved, a second line follows:
`Approved at gate Gn on YYYY-MM-DD, commit <hash>`.

Every V-model document ends with a revision table:

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | YYYY-MM-DD | First approved version | user, gate G1 |

### Cross-cutting records

- [docs/adr/](../adr/) holds architecture decision records (ADRs), one file
  per decision. Write an ADR for a decision that affects more than one module
  or product, picks between real alternatives the user might question,
  reverses an earlier decision, or changes a process rule, including such
  decisions made in chat. A choice local to one module is recorded with its
  rationale in that module's DD file.
- [docs/research/](../research/) holds the evidence the design relies on.
  The device firmware is the main source of truth. Findings from WebLink and
  captures from real hardware come on top of it. Each fact carries one of
  three evidence labels: confirmed in code, confirmed on hardware, or
  inferred. Information read from the device firmware is used to its fullest
  (ADR-0010). For other sources, production code relies only on facts marked
  confirmed on hardware, or on inferred facts that the relevant DD accepts
  explicitly with a TBD (ADR-0002).
- [traceability.md](traceability.md) maps every requirement down to design
  items and tests, and back up. See "Tracing code and tests to the design".
- `records/` holds verification records. See "Verification and validation".

## Phase gates

Work moves down the left side one gate at a time. A gate passes only when the
user approves it.

| Gate | Passes when | Unlocks |
|---|---|---|
| G1 | UR document (including the hazard list) and AT specification approved | System requirements |
| G2 | SR document and ST specification approved | Architecture |
| G3 | AR document and IT specification approved | Detailed design |
| G4 | The DD file of one module approved, design and unit test specification together | Implementation of that module |

G4 is per module, so the protocol module can be implemented while the GUI
design is still under review. No production code is written for a module
before its G4.

After the user approves a gate, the approved documents are committed once the
user permits the commit. The approval goes into
[LOGBOOK.md](../../LOGBOOK.md) with the date and the hash of that commit, and
the commit gets the git tag `gN-approved` (module gates:
`g4-<module>-approved`), for example `g1-approved` or `g4-protocol-approved`.

### Before asking for a gate

- Every item has all its attributes.
- Every item traces to a parent or source and to at least one test spec
  entry.
- Every open point is written as `TBD-nnn` and has a TODO item. The user
  accepts the list of open TBDs explicitly at the gate.
- Every item that relies on a protocol fact cites the docs/research entry and
  its evidence label.
- For G1, every hazard is mitigated, or the user has accepted it explicitly.
- An independent review pass has run, and its findings are resolved or
  logged.

A module implementation is done when its unit tests pass, its coverage target
([ADR-0008](../adr/0008-quality-standards.md)) is met, its docs and its `Implements:` and `Test:` tags are
complete, traceability.md is regenerated, and a verification record exists.

### Spikes

A throwaway spike may answer a question before G4, for example "does the
device answer this frame?".

- Spikes live under `spikes/`, one folder per spike, with a README that states
  the question.
- Spikes are excluded from the Cargo workspace (`exclude = ["spikes"]`) and
  from the Python package. The documentation, lint and coverage rules do not
  apply to them.
- Production code never imports or copies spike code. It is written from the
  approved DD.
- A spike that talks to a device follows the HIL safety rules
  ([AGENTS.md](../../AGENTS.md), [ADR-0008](../adr/0008-quality-standards.md)):
  5 V and 100 mA defaults, nothing on the output
  unless the spike says so, output off at the end. It needs the user's
  go-ahead before any command that changes device state.
- The answer goes into docs/research/, with a LOGBOOK entry.

## Writing requirements

Requirement documents use this table:

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| UR-001 | The app shall ... | user, conversation 2026-09-29 | must | D | draft | ... |
| UR-002 | The ... shall ... | ADR-0003 | must | I | draft | Settled constraint. |
| SR-001 | The library shall ... | UR-001 | must | T | draft | ... |
| SR-002 | The library shall ... | derived | must | T | draft | Protocol constraint: ... |

- One requirement per ID, always written with "shall". Importance is carried
  only by the Priority column: must, should or could.
- Each requirement is verifiable. If nobody can say how to check it, rewrite
  it. Verification methods are T (test), D (demonstration), I (inspection)
  and A (analysis).
- Status is draft, approved, changed or withdrawn.
- A UR names its source: a conversation date, a user statement or an ADR. An
  SR names the UR it refines.
- A derived SR has no UR parent, for example a safety or protocol constraint.
  It writes `derived` in the Parent column and explains why in its rationale.
- Settled design constraints (ADR-0003 to ADR-0006) become
  constraint URs that cite the ADR.
- IDs are never reused or renumbered. A dropped requirement stays in the
  document with status `withdrawn` and the reason.
- Every requirement has at least one test spec entry at the matching level,
  or a reason, recorded in the test specification, why demonstration,
  inspection or analysis suffices.

### Hazards and functional safety (IEC 61508)

Because unintended or incorrect behavior of the power supply can cause direct
property damage (DUT destruction, electrical fire) and indirectly human injury,
this software is treated as an electrical safety-related system under
**IEC 61508** (ADR-0008). The V-model serves as the systematic fault avoidance
lifecycle (IEC 61508-3).

Before G1, 1-user-requirements.md contains a hazard list:

| ID | Hazard | Cause | Severity | Mitigation |
|---|---|---|---|---|
| H-001 | ... | ... | ... | UR and SR IDs |

Every hazard is mitigated by at least one UR or derived SR and verified by an
AT or ST. G1 cannot pass with an unmitigated hazard unless the user accepts it
explicitly.

## Tracing code and tests to the design

- Each test spec entry has its own ID, lists the UR, SR or design item IDs it
  verifies, and gives either the path of the automated test that implements
  it or a written manual procedure. The spec entry is the only place that
  records what a test verifies.
- Each module starts with a doc comment naming the DD items it implements,
  for example `//! Implements: DD-PROTO-001, DD-PROTO-002`.
- Each automated test names only its own spec ID. Rust: `/// Test: UT-PROTO-007`
  in the test's doc comment. Python: `@pytest.mark.spec("ST-014")`.
  pyproject.toml registers the `spec` and `hil` markers and pytest runs with
  `--strict-markers`, so a mistyped marker is an error.
- A test's level comes from the spec ID it names, not from its directory.
  AGENTS.md describes where each kind of test lives.

It is a defect in the documents when a UR, SR, AR or DD item has no test spec
entry (and no recorded reason why demonstration, inspection or analysis
suffices), when a spec entry has neither an implementing automated test nor a
written manual procedure, or when an automated test names no spec ID.

traceability.md is generated by a check script from the Parent columns, the
test spec entries and the code tags. The output is committed and never edited
by hand. Until the script exists, traceability.md is kept by hand. The script
must exist before the first module is implemented.

## Verification and validation

The right side of the V runs bottom up: unit tests, then integration tests,
then system tests, then acceptance tests.

A level is verified when every test spec entry of that level has a recorded
passing result, or a failure the user has explicitly accepted as a known
deviation (logged, with a TODO item). A result comes from an automated test
(including HIL tests), a manual procedure, an inspection, a demonstration or
an analysis.

Each verification run gets a record in
`docs/v-model/records/YYYY-MM-DD-<level>-<scope>.md`, for example
`YYYY-MM-DD-unit-protocol.md`, with:

- the commit hash, or `uncommitted` plus a summary of the diff
- the OS and the transport
- for hardware runs, the device firmware version or a pointer to the LOGBOOK
  entry that records it
- the exact command or procedure
- pass or fail for each test ID, with notes

LOGBOOK.md gets one line per verification run that points to its record.
Routine development test runs are not logged.

Acceptance tests are validation: they check the product against the user
requirements. They run against a release build (the app binary and the
installed Python wheel) and a real MP305B, and the user performs or witnesses
them. An agent may prepare and assist, but never records an AT as passed on
its own.

System tests run on real hardware over each transport the SRs name.
7-system-tests.md and 8-acceptance-tests.md each contain a coverage table of
test by OS by transport. A hardware cell requires the applicable procedure
on the named OS and transport. A native host and a VM whose device
pass-through works are eligible; missing hardware leaves that cell open.
No cell falls back to CI without a device.

Proposed revision 3 under [ADR-0018](../adr/0018-focused-hardware-verification.md):
only cells explicitly marked for reuse in an approved coverage table may
use an equivalence analysis instead of a repeated hardware execution. The
analysis identifies the passing source result, artifacts, relevant changes,
current target unit/integration results and target hardware prerequisites.
It explains the shared behavior and any platform or transport differences.
The prerequisites and limits are in
[hardware-verification-plan.md](hardware-verification-plan.md). Missing or
contradictory evidence leaves the cell open. A reuse result is recorded as
verified by analysis, never as a hardware run on the target combination.
The source result is from the build under test or reviewed again against
its commit, a prerequisite counts only when it was run directly, and the
user signs every reuse record off. Acceptance reuse also requires a
witnessed source on the same OS and release artifacts.

Compatible executions may share setup, traces and observations when each
entry's complete procedure and expected results are satisfied. Each ID
keeps its own result and evidence references; automated tests keep only
their own spec ID. Combined ST/AT work uses release artifacts and preserves
the user's acceptance observations. Development-build results cannot be
relabeled as acceptance results. Required fresh sessions, loads, HIL
opt-ins, output-off teardown and settings restoration remain mandatory.
Neither reuse nor batching changes the level-completion rule above.

## Changing an approved document

This applies to every approved document: UR, SR, AR, DD and every test
specification.

1. Before editing, use traceability.md to find the lower-level items and
   tests that depend on the item you want to change.
2. Edit the item, set its Status to `changed`, note that it is pending
   approval, and add a row to the revision table.
3. Ask the user to approve the change. Until they do, the changed item is not
   implemented or re-verified.
4. After approval, set the item's Status to `approved`, update the dependent
   items found in step 1 under the same rules, and run their tests again.
5. Write an ADR if the change falls under the ADR rule in "Cross-cutting
   records".
6. Log the change, its impact and the approval in LOGBOOK.md.

A failing test is never fixed by changing its specification without the
user's approval. Editorial changes that alter no requirement, design
statement, expected result or ID need no approval. They are logged as
editorial in the revision table.

## Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | First draft, revised the same day after an independent review | not yet approved |
| 2 | 2026-09-30 | Editorial: the V-model is stated as the project process. No process rule changed. | user, 2026-09-30 (process baseline) |
| 3 | 2026-10-04 | Define conditional evidence reuse only where approved ST/AT matrices permit it, actual-host hardware obligations, and combined execution with per-ID results and witnessed release acceptance. Correct the stale introductory claim that the approved process still awaited approval. Reworked on 2026-10-05 after the review of ADR-0018: no cell falls back to CI, the source of a reuse is from the build under test, prerequisites count only as direct runs, and the user signs every reuse record off. ADR-0018. | pending user approval |
