# Architecture decision records

One file per decision, numbered in order. An ADR is never deleted. When a
decision changes, write a new ADR that supersedes the old one and set the old
one's status to `Superseded by ADR-nnnn`.

Write an ADR for a decision that affects more than one module or product,
picks between real alternatives the user might question, reverses an earlier
decision, or changes a process rule. This includes such decisions made in
chat. Choices local to one module are recorded, with their rationale, in that
module's DD file.

Status values: `Proposed` (waiting for the user's approval), `Accepted`,
`Rejected`, `Superseded by ADR-nnnn`.

## Index

| ADR | Title | Status |
|---|---|---|
| [0001](0001-v-model-docs-as-code.md) | V-model process with design documents in the repository | Accepted |
| [0002](0002-firmware-main-source-of-truth.md) | The device firmware is the main source of truth for the protocol | Accepted |
| [0003](0003-rust-core-crate.md) | One Rust core crate shared by the app and the Python library | Accepted |
| [0004](0004-transports-ble-and-hid.md) | Support Bluetooth LE and USB HID, Bluetooth first | Accepted |
| [0005](0005-egui-desktop-app.md) | egui for the desktop app | Accepted |
| [0006](0006-python-via-pyo3.md) | Python library through PyO3 bindings | Accepted |
| [0007](0007-synchronous-python-api.md) | Synchronous Python API | Accepted |
| [0008](0008-quality-standards.md) | Quality standards, IEC 61508 functional safety and MISRA-aligned guidelines | Accepted |
| [0010](0010-decompile-firmware-for-interoperability.md) | Decompile device firmware for interoperability | Accepted |
| [0011](0011-licensing-gplv3-with-commons-clause.md) | License under GNU GPLv3 with Commons Clause | Accepted |
| [0012](0012-agent-anonymity-and-ownership.md) | Agent anonymity and ownership | Accepted |
| [0013](0013-coverage-exclusion-vendor-glue.md) | Coverage exclusion for vendor-library glue in the transports | Accepted |

## Template

```markdown
# ADR-nnnn: Title

- Status: Proposed
- Date: YYYY-MM-DD
- Decided by: (user; user, on the agent's recommendation; or pending while
  Proposed)
- Related: (UR/SR/AR/DD IDs, other ADRs)

## Context

What problem needs a decision, and which forces matter.

## Decision

What we will do, stated plainly.

## Alternatives considered

Each option with the reason it lost.

## Consequences

What becomes easier, what becomes harder, and what follow-up work this
creates.
```
