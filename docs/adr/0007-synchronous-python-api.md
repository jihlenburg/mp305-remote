# ADR-0007: Synchronous Python API

- Status: Accepted
- Date: 2026-09-30 (proposed 2026-09-29)
- Decided by: user
- Related: ADR-0003, ADR-0006

## Context

`btleplug` is async, and the draft architecture gives `mp305-core` an async
device API. Python users write test scripts and Jupyter notebooks, where
blocking calls read most naturally:

```python
psu = Mp305.connect()
psu.set_voltage(5.0)
print(psu.measure())
```

Exposing Rust futures as Python awaitables through PyO3 works, but it adds a
bridge between event loops and makes errors and cancellation harder to get
right.

A blocking Rust call that has released the GIL does not see Ctrl-C: Python
only sets a flag on SIGINT and acts on it when control returns to the
interpreter. Connecting can take well over 10 s: discovery needs a scan
window of at least 10 s, and the bind waits for a person to confirm on the
device (LOGBOOK 2026-09-29).

## Decision

The Python API is synchronous in v1.

- One shared multi-threaded Tokio runtime per Python process, created lazily
  on first use, serves all connections.
- Every call blocks on that runtime and releases the GIL while it waits, so
  other Python threads keep running.
- Blocking waits run in short slices of about 100 ms and call
  `Python::check_signals` between slices. Ctrl-C and Jupyter interrupts then
  raise `KeyboardInterrupt` and cancel the pending request.
- All calls have timeouts.
- Measurement streaming is offered as a blocking iterator.

## Alternatives considered

- Async Python API only: suits asyncio users, awkward for plain scripts.
- Both APIs from the start: twice the surface to document and test before
  anyone has asked for async.
- One Tokio runtime per connection object: keeps connections apart, but every
  open supply adds its own worker threads.

## Consequences

- Scripts and notebooks stay simple, and Ctrl-C works during a blocking call.
- A lost Bluetooth link ends in a timeout error instead of hanging a script.
- The runtime's worker threads live until the Python process exits.
- An async API can be added later without breaking the synchronous one.
