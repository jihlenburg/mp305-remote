# ADR-0006: Python library through PyO3 bindings

- Status: Accepted
- Date: 2026-09-29
- Decided by: user
- Related: ADR-0003, ADR-0007

## Context

The Python library is for scripted tests: set voltage and current, switch the
output, read measurements, log them, and run helpers such as ramps. It needs
the same protocol and transports as the app.

## Decision

Build the Python package `mp305` as PyO3 bindings to `mp305-core`, packaged
with maturin. Small pure-Python helpers, such as ramps and CSV logging, sit in
the same package on top of the native module.

## Alternatives considered

- Pure Python using `bleak` and `hid`: quicker to start and easier to
  install from source, but it means a second protocol implementation
  (see ADR-0003).

## Consequences

- Wheels have to be built per platform and Python version in CI. Users
  installing a published wheel do not need a Rust toolchain.
- The native module needs a hand-maintained `.pyi` stub so that type checkers
  and editors can see its API.
- The pure-Python helpers stay easy for users to read and change.
