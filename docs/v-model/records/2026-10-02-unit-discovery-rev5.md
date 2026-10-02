# Verification record: discovery DD revision 5 (properties read before the scan stops)

Date: 2026-10-02. Level: unit (UT-DISC-010, by inspection) with a scan on
hardware. Scope: `crates/mp305-core/src/discovery/ble.rs` after discovery
DD revision 5, approved by the user on 2026-10-02: `watch` hands the
running scan back to its caller, `scan` reads `properties()` of each
counted id before it stops the scan, and `find` stops the scan at once as
before.

Commit: uncommitted. Diff summary: `discovery/ble.rs` (`watch`, `scan`,
`find`); discovery.md (revision 5 approved); `traceability.md`; this
record; TODO.md; LOGBOOK.md. Written and checked in the main session.

OS: macOS 27.0.1, Apple arm64. Rust 1.98.1 (Homebrew), clippy 0.1.98.
Transport for the scan: Bluetooth LE, advertising only, the Mac's own
adapter; nothing above the link layer was sent and no connection was
made. Firmware: not read (LOGBOOK 2026-09-29).

## Results

| Check | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| `cargo clippy --workspace --all-targets -- -D warnings` | pass |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | pass |
| `cargo test --workspace` | pass: 522 tests |
| `cargo doc` with `-D warnings` | pass |
| UT-DISC-010, the changed point: `properties()` per counted id in `seen()` order, read before `stop_scan` | present: `scan` reads into a list, then calls `ScanStop::finish`, then classifies |
| UT-DISC-010, the drop guard: a failed read returns early and the dropped guard issues `stop_scan` and releases the lock after it | present (the guard is held by `scan` until `finish`) |
| UT-DISC-010, `find` stops the scan before returning | present |
| One 5 s scan through the library on macOS | the supply is found with name, unit `E!K`, remote flag and RSSI -82 dBm, as before the change |

## Open

The purpose of the change, a signal strength on Linux (BlueZ), is not
verified: the USB Bluetooth dongle was not plugged in when the change was
made. It is to be checked with one scan in the Ubuntu VM, and ST-001 on
Linux is to follow (TODO.md).
