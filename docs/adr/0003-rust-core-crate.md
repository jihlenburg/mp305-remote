# ADR-0003: One Rust core crate shared by the app and the Python library

- Status: Accepted
- Date: 2026-09-29
- Decided by: user, on the agent's recommendation
- Related: ADR-0005, ADR-0006, ADR-0007

## Context

There are two products: a Python library for scripted tests and a
standalone desktop app for macOS, Linux and Windows. The app language was
a choice between Go and Rust.

Both products need the same undocumented protocol, over Bluetooth LE and USB
HID. The protocol is the riskiest part of the project, so a second
implementation of it doubles the places where a decoding bug can hide.

Both languages need native code on some platforms:

| Need | Rust | Go |
|---|---|---|
| Bluetooth LE | `btleplug` (CoreBluetooth, WinRT, BlueZ) | `tinygo.org/x/bluetooth`, cgo on macOS |
| USB HID | `hidapi` crate, bundles the C library (still needs system libudev on Linux, see ADR-0004) | `go-hid` or `karalabe/hid`, cgo |
| Python bindings | PyO3 and maturin | C shared library plus ctypes |

## Decision

Write the protocol, the transports and the device API once, in a Rust crate
called `mp305-core`. The desktop app and the Python bindings are thin layers
on top of it.

## Alternatives considered

- Go for the app: Go's main advantage, cross-compiling a static binary from
  one machine, disappears once Bluetooth on macOS and HID require cgo. Sharing
  code with Python would need a C ABI layer, so in practice the protocol would
  be written twice.
- Pure Python library plus a separate app: quickest start, but two protocol
  implementations to keep in step.

## Consequences

- Each platform needs its own build (a CI matrix), for the app binaries and
  for the Python wheels.
- `btleplug` is async, so the app and the Python bindings each have to drive
  an async runtime. ADR-0007 proposes the runtime for the Python side.
- Open points for docs/v-model/3-architecture.md (gate G3): the runtime and
  task design, and whether protocol types derive `serde` traits.
