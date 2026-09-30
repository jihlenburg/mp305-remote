# ADR-0001: V-model process with design documents in the repository

- Status: Accepted
- Date: 2026-09-29
- Decided by: user (adopt the V-model); process details on the agent's
  recommendation, pending the user's review
- Related: [docs/v-model/README.md](../v-model/README.md), ADR-0008

## Context

The project talks to a device whose protocol is undocumented and has to be
reverse engineered. Mistakes can switch a power supply output on at the wrong
voltage. Every requirement is traceable to a design and a test, and the
code is documented as thoroughly as the design.

## Decision

Development follows the V-model: user requirements, system requirements,
architecture and detailed design on the way down, each with a matching test
level (acceptance, system, integration, unit) that is specified at the same
time. Each step down passes a gate that the user approves.

All design records live in the repository as Markdown under `docs/`, next to
the code, and change through the same review as the code. Requirements, design
elements and tests carry stable IDs and are linked in a traceability matrix.

## Alternatives considered

- Informal design notes plus tests: faster at the start, but nothing shows
  which requirement a test covers, or which requirements have no test.
- A single spec document: fine for a small change, but it mixes levels and
  makes it hard to see what was approved at which gate.
- An external tool (wiki, requirements tool): separates documents from the
  code they describe and from version control.

## Consequences

- More writing before any code exists. The protocol risk justifies it, and
  throwaway spikes (see the process document) keep hardware questions from
  blocking on paperwork.
- Every test has a reason to exist, and gaps show up in the traceability
  matrix.
- Hazards, such as an output switched on at the wrong voltage, are listed in
  the user requirements before G1. Each one is traced to a requirement that
  mitigates it and a test that verifies it.
- A script that generates the traceability matrix from the documents and the
  code tags must exist before the first module is implemented (tracked in
  TODO.md).
