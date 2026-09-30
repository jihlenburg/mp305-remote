# ADR-0010: Decompile device firmware for interoperability

- Status: Accepted
- Date: 2026-09-29
- Decided by: user
- Related: ADR-0002, [AGENTS.md](../../AGENTS.md)

## Context

ISDT publishes no protocol documentation for the MP305B. The library
(`mp305`) and the desktop app (`mp305-app`) have to interoperate with the
device. Firmware decompilation is how that interoperability is reached.

## Decision

Under Directive 2009/24/EC (2009/24/EG), decompiling the device firmware is
fully allowed in order to ensure full interoperability of the library and
the desktop app with the device. There is no limit on the information
contained in that firmware. The library and the desktop app use it to its
fullest. The device firmware is the main source of truth. Findings from
WebLink, from hardware, and from anywhere else come on top of it. The
firmware image stays out of the repository. Interoperability information
reconstructed or gathered from it stays in the repository, in whatever form
it takes.

## Alternatives considered

- Leaving the permission unstated: rejected. The permission is written down,
  and no statement in the repository contradicts it.
- Treating WebLink, or a hardware capture, as the source of truth and the
  firmware as a later check: rejected on 2026-09-29. Those findings stay,
  on top of the firmware.

## Consequences

- Research, `mp305` and `mp305-app` decompile the device firmware and use
  the information in it to its fullest for that interoperability.
- The firmware image stays out of the repository. Interoperability
  information reconstructed or gathered from it is committed, in whatever
  form it takes.
- The hardware-confirmation rule in ADR-0002 applies to other sources.
  Information read from the device firmware is used to its fullest.
- Where the device firmware and another finding differ, the project uses
  the firmware. WebLink, hardware captures and other findings come on top
  of it.
