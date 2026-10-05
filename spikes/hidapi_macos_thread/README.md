# Spike: hidapi on macOS and the thread that first used it

## Question

Does `hidapi` on macOS survive an enumeration from one thread after the
thread that used the library first has ended? The app crashed on
2026-10-05 inside `hid_enumerate`, on a thread of Tokio's blocking pool,
after a click on a supply (LOGBOOK 2026-10-05, "The app crashes in the USB
enumeration").

## What it does

`src/main.rs` lists the HID devices six times in one of four ways:

| Mode | Who calls `hidapi` |
|---|---|
| `fresh` | every round a new thread that ends afterwards |
| `owner` | one thread that lives for the whole run, asked by new threads |
| `alive` | new threads, while the first thread stays alive |
| `library` | a USB scan through `mp305-core`, every round on a new thread with its own Tokio runtime |

No frame is sent to any device. The `library` mode enumerates and
classifies; it opens nothing.

A use of freed memory only crashes when the allocator has reused the
memory, so a plain run usually passes. Guard Malloc unmaps freed memory
and makes the fault certain:

```sh
cargo build --release
DYLD_INSERT_LIBRARIES=/usr/lib/libgmalloc.dylib target/release/hidapi_macos_thread fresh
```

Guard Malloc is slow: a run takes up to a minute.

## Answer (2026-10-05, macOS 27.0.1 on arm64, hidapi 2.6.7)

No. `hidapi` keeps one `IOHIDManager` for the process and schedules it on
the run loop of the thread that initialises the library (`mac/hid.c`,
`init_hid_manager`). The Rust crate never calls `hid_exit`. When that
thread ends, its run loop is freed, and the next enumeration schedules
the devices on the freed run loop.

| Mode | Under Guard Malloc |
|---|---|
| `fresh` | segmentation fault in the second round |
| `owner` | six rounds pass |
| `alive` | six rounds pass |
| `library`, `mp305-core` at commit `2528dab` | segmentation fault in the second round |
| `library`, `mp305-core` with the owner thread (discovery DD revision 8) | six rounds pass, the supply found over USB each time |

The library therefore makes every `hidapi` context call on one thread
that never ends (DD-DISC-013, `crates/mp305-core/src/discovery/hid_owner.rs`).
The `library` mode of this spike builds against the working tree, so it
shows the current behaviour; the row for commit `2528dab` came from the
same source built against that commit.
