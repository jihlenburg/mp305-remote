# 3. Architecture (AR)

Status: approved (G3, user, 2026-09-30; AR-017 change approved 2026-09-30, revision 3)

The architecture of the v1 remote control: one Rust core, two products on
top of it, and the pieces of the core that the device's behavior demands.
It refines [2-system-requirements.md](2-system-requirements.md) revision 10
(approved at G2) and rests on the decisions in ADR-0003 (one Rust core),
ADR-0004 (Bluetooth LE with `btleplug`, USB HID with `hidapi`), ADR-0005
(egui desktop app), ADR-0006 (Python through PyO3), ADR-0007 (synchronous
Python API on one shared Tokio runtime) and ADR-0008 (quality standards).
Device facts cite [docs/research/device-model.md](../research/device-model.md)
by section. The draft agreed in chat on 2026-09-29 (LOGBOOK, "Draft
architecture") is the starting point; the device model adds the host ID
store, the link and remote-control state machines, the event dispatcher, the
reconnect policy and the allowlist. Revision 2 resolves the independent
review of revision 1 (LOGBOOK, "Architecture review").

Design items carry no priority: every AR item is needed for the SRs it
refines. Each item names the module that implements it. A module's detailed
design (level 4) refines its AR items and may not contradict them.

## 1. Products and crates

```
 mp305-app (egui)                     mp305 (Python package)
   ui/ (drawing only)                   helpers: stream, to_csv, ramp
   model (chart buffer, settings)       mp305._native (PyO3, crate mp305-py)
   worker task  <-channels->  |                 |
        \                     v                 v
         `--------->  mp305-core (library, no device I/O of its own)
     discovery | session | link | protocol | transport | store | csv
                              |               |
                              |      Guarded<T> (allowlist, one in
                              |      flight, frame log, timestamps)
                              |               |
                        transport::ble  transport::hid   transport::mock
                          (btleplug)      (hidapi)         (tests only)
```

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-001 | The Cargo workspace holds three crates: `mp305-core` (library), `mp305-app` (binary with its logic in `src/lib.rs` and a thin `src/main.rs`) and `mp305-py` (`cdylib` and `rlib`). `spikes/` is excluded from the workspace. The Python package `mp305` under `python/mp305/` wraps the native module `mp305._native` and adds pure Python helpers. Python integration tests live in `tests/integration/`. | UR-019, UR-020, UR-021 | IT-001 | approved | ADR-0003, ADR-0005, ADR-0006. The `rlib` target and the `lib.rs` split let doctests and integration tests reach the code (AGENTS.md, Testing standards). |
| AR-002 | `mp305-core` performs no device I/O of its own: every byte to or from a supply goes through the `Transport` trait behind the `Guarded` wrapper (AR-015). The only file I/O in the core is `store` (AR-033); the CSV writer takes `impl std::io::Write` (AR-042). Every function that talks to a device is testable against `transport::mock`. | SR-016, SR-017, ADR-0008 | IT-002 | approved | Unit and integration tests run without hardware; HIL tests are the exception and are marked. |
| AR-003 | `mp305-core` is async on Tokio, and `link` and `session` take all time from Tokio's clock (`tokio::time`), so tests run with a paused clock and advance it. `mp305-app` runs the device on a worker task and talks to the UI through channels. `mp305-py` owns one shared multi-threaded Tokio runtime per process; a blocking call releases the GIL and waits in slices of at most 100 ms, calling `Python::check_signals` between slices, so Ctrl-C raises `KeyboardInterrupt` within 0.5 s and cancels the pending request. | UR-015, SR-031, SR-039 | IT-003 | approved | `btleplug` is async; ADR-0007 fixes the Python side. The Tokio clock is what lets the 30 s, 70 s and 10 min bounds be tested in seconds. |
| AR-004 | `mp305-core` and `mp305-app` set `#![forbid(unsafe_code)]`; `mp305-py` sets `#![deny(unsafe_code)]` and allows it only in its `ffi` module. Every crate sets `#![deny(missing_docs)]`, `#![warn(clippy::missing_docs_in_private_items)]` and the clippy lints of ADR-0008 (`unwrap_used`, `expect_used`, `panic`, `indexing_slicing`, `arithmetic_side_effects`). | UR-019, UR-020, UR-021, ADR-0008 | IT-004 | approved | The lints make the safety rules checkable by `cargo clippy -D warnings`. `forbid` cannot be re-allowed inside a crate, so the PyO3 crate uses `deny`. |

## 2. Core modules

Each module of `mp305-core` is one Rust module tree and gets one DD file at
level 4: `protocol` (with its `hid` and `ble` framing submodules and the
timing constants), `transport` (trait, `Guarded`, `ble`, `hid`, `mock`),
`link`, `session`, `discovery`, `store` and `csv`.

### 2.1 protocol: frames, payloads and constants, no I/O

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-010 | `protocol` defines one `Frame { opcode, payload }` type and two pure framing submodules. `protocol::ble` maps a `Frame` to and from the AF01 form (`0x12 opcode payload` out, `0x31 opcode payload` in) and the AF02 form (`opcode payload` both ways). `protocol::hid` has a stream `Decoder` (resynchronises on `AA`, reads the address and the length, undoubles `AA` in pairs, checks the checksum, yields `Frame`s with address `0x21`) and an `encode` that produces the `AA 12 len opcode payload sum` stream with `AA` doubled and splits it into report payloads of at most 62 bytes, each frame starting a new report. Neither submodule depends on `btleplug` or `hidapi`. | SR-044, SR-045, SR-016 | IT-010 | approved | device-model.md 2.1 and 2.2. One `Frame` type keeps the layers above transport-independent; one decoder means one place for the doubling rule (WebLink's own de-doubling bug shows what a second implementation risks, protocol.md 1.1). |
| AR-011 | `protocol` defines typed request builders and reply parsers for exactly the v1 opcodes: `0x18` bind (host ID, fast flag), `0xE0`/`0xE1` info (both layouts), `0xC2`/`0xC3` telemetry, `0xC8`/`0xC9` control, the unsolicited `0xC5` settings, and the event frames `0xDD`, `0xE5`, `0xEB`, `0xDB` as opaque events. Every parser checks the length before reading a field and returns `Error::Protocol` with the reason (short, bad prefix, bad checksum) and never a partial value. Builders produce the exact payload lengths of protocol.md 3 and 4. | SR-012, SR-014, SR-015, SR-016, SR-027, SR-052 | IT-011 | approved | device-model.md 1, 6, 8, 9. Typed builders make a short frame impossible to construct (SR-052). |
| AR-012 | `protocol::policy` holds the opcode policy: an allowlist of the four request opcodes the system may send (`0x18`, `0xE0`, `0xC2`, `0xC8`) and a never-send list with a reason per opcode (`0x10`, `0xC0`, `0xBE`, `0x20`, `0xF0` to `0xFE`). The `Guarded` wrapper (AR-015) refuses any frame whose opcode is not on the allowlist. | SR-006, UR-033 | IT-012 | approved | device-model.md 11. The policy lives next to the opcode tables so both are reviewed together. |
| AR-013 | `protocol::units` converts between raw and SI units in one place: voltage 10 mV, current 1 mA, power 10 mW, energy 0.1 Wh, working time seconds, temperature signed 8-bit °C. It validates setpoints (finite, not negative, within the supply range of SR-025 and the user limits) before encoding and rounds to the nearest raw step, halves away from zero. | SR-014, SR-024, SR-025, H-005 | IT-013 | approved | One conversion site is one place to test against the hardware-confirmed scaling. |
| AR-014 | `protocol::timing` defines every bound as a named constant with its source in a comment: bind 30 s, remote prompt 70 s, reply 1 s, output-off acknowledgment 0.5 s, poll pause 100 ms, USB keepalive 2 s, link-loss report 4 s, reconnect retry 5 s for 10 min. No other module carries these numbers. | SR-009, SR-013, SR-022, SR-023, SR-028, SR-051, SR-053, SR-055 | IT-014 | approved | device-model.md 12. |

### 2.2 transport: the two links, the guard and the mock

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-015 | The `Transport` trait is minimal: `send(Frame, Route)` (route: AF01, AF02 or the HID path), a stream of incoming `Frame`s tagged with their route, `close()`, and a description (kind, identifier). `Guarded<T: Transport>` wraps every transport, real or mock: it refuses opcodes outside the allowlist (AR-012), allows one write in flight, stamps each incoming frame with its arrival time, and writes the frame log (AR-018). `link` constructs `Guarded` itself, so no path to a device bypasses it. `transport::mock` is scripted (replies per request, injected frames at Tokio-clock times, delays, errors) and records every frame it was given; tests only. | SR-006, SR-017, SR-044, SR-045 | IT-015 | approved | device-model.md 2.1 and 6: the bridge holds one frame per direction. Putting the rules in one wrapper means the mock-tested path is the shipped path. |
| AR-016 | `transport::ble` (`btleplug`) connects, enables notifications on AF01 and AF02 on every connection, treats each notification as one frame tagged with its characteristic, writes with response, and reports an OS disconnect as a transport error. It does not request an MTU: it reads the negotiated value where the OS exposes it and fails the connection with `Error::Transport` when a notification arrives truncated. It holds no bind or policy logic. | SR-007, SR-028, SR-044 | IT-016 | approved | device-model.md 2.1. The bridge accepts up to 247 and starts no exchange; `btleplug` exposes no MTU request, and macOS, Windows and BlueZ negotiate on their own (TBD-019). SR-007's "request an ATT MTU of 247" is met by the OS negotiation; see TBD-021. |
| AR-017 | `transport::hid` (`hidapi`) opens the HID path, writes every report payload of one frame from `protocol::hid::encode` as consecutive output reports 1 (`01 n bytes`) that no other frame interleaves with, reads input report 2 and hands the `n` stream bytes of each report to `protocol::hid::Decoder`, and reports device errors as transport errors. Waiting for the reply before the next frame is `link`'s rule (AR-020). The report ID byte handling per OS is TBD-020. | SR-045, SR-028 | IT-017 | approved | device-model.md 2.2. The transport only moves report payloads; all framing is in `protocol::hid`, which is testable without `hidapi`. |
| AR-018 | `Guarded` writes a frame log through the `log` crate at level TRACE: direction, timestamp, route, hex bytes. The app and the library can enable it; the system tests read it. | SR-006 | IT-018 | approved | Most system tests (ST-006, ST-039, ST-040) check the log rather than the device. |

### 2.3 link: requests, events, poll, keepalive and loss

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-020 | `link` owns one `Guarded` transport and serialises requests: at most one immediate request in flight, taken from a two-level queue (urgent, normal); the output-off request is the only urgent one and is sent before any queued normal request. A request has a kind: immediate (expects its reply within the reply timeout) or deferred (`0x18` with the fast flag clear, and `0xC8` with `remoteCon = 2` over Bluetooth). A deferred request frees the link as soon as it is written and registers an expectation (opcode plus its bound: 30 s, 70 s) that `session` state matches. Incoming frames are dispatched: the expected reply completes the immediate request; a `0x19` or `0xC9` matching an open expectation completes it; `0xC5`, `0xDD`, `0xE5`, `0xEB`, `0xDB` become `DeviceEvent`s; a `0x19` or `0xC9` matching nothing becomes `DeviceEvent::LateReply`; anything else is counted and logged. After a `0xC8` timeout or a `LateReply`, `link` sends no `0xC8` until one `0xC2`/`0xC3` cycle has completed, so a late `0xC9` can only arrive during a poll. | SR-017, SR-016, SR-022, SR-053, UR-034 | IT-020 | approved | device-model.md 6: replies are matched by opcode and state; the bind and the Bluetooth remote request are answered seconds later while polling must go on (SR-013) and loss detection must keep working (SR-028). Two `0xC9`s cannot be told apart by their bytes, so the rule after a timeout is what makes attribution safe. |
| AR-021 | `link` runs the poll timer: it sends `0xC2` no earlier than 100 ms after the previous `0xC3` and delivers each reading with its arrival timestamp to `session`. It runs the keepalive: over USB it guarantees a frame at least every 2 s, using the poll when it runs and an `0xE0` when the poll is paused; over Bluetooth it sends nothing on its own. | SR-013, SR-051, UR-035 | IT-021 | approved | device-model.md 4.4: 8 s of USB silence drops the link and the grant. The poll lives in `link` so that keepalive and loss detection see the same clock. |
| AR-022 | `link` declares the link lost on a transport error, an OS disconnect, or three consecutive timeouts of immediate requests (the `0xC2` poll or any other request that expects a reply within 1 s; deferred requests never count), and reports it within 4 s of the last reply as `DeviceEvent::LinkLost(reason)`. It then empties both queues, fails every pending request and expectation with `Error::LinkLost`, and sends nothing more. | SR-028 | IT-022 | approved (rev 4) | device-model.md 4.4. A command issued before the loss is reported as lost, never replayed (AR-029). |

### 2.4 session: the device as the products see it

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-025 | `session` holds the device API: `connect(identifier)` (an identifier is always required here; the exactly-one rule of SR-004 is the products' concern, AR-040 and AR-041), `info`, `readings` (stream), `set_voltage`, `set_current_limit`, `output_on`, `output_off`, `request_remote_control`, `release_remote_control`, `close`. It keeps the latest reading and builds every `0xC8` from a reading that arrived after the previous `0xC9` and is at most 1 s old, polling first otherwise, copying every field and changing only the named one, `refresh` 0, `model` 0. Guards, in this order: `ModeError` unless the reading says DC mode; `FaultActive` for output-on while any fault bit is set; `output = 1` only from `output_on` or copied from a reading at most 1 s old that arrived after the previous `0xC9` (the software never turns the output on by itself). After any `0xC9` other than 0, and after a `0xC8` timeout, the setpoints are marked unknown, a `0xC3` is read before the next control call, and a `SetpointsChanged` event reports any value that differs from what the user last set. `output_off` uses the urgent queue and the 0.5 s bound, then reads `0xC3` and reports differences the same way. A `0xC9` of `0xFF` is reported as `CommandRejected` with the inferred reason, in this order: mode, range, fault, else busy. The unclean-exit marker (AR-033) is written while remote control is held and the reading shows the output on, refreshed with each such reading, and removed on `output_off`, on a reading with the output off, and on `close`. | SR-012, SR-013, SR-018 to SR-026, SR-046, SR-053, SR-054 | IT-025 | approved (rev 5) | device-model.md 5, 7, 8, 9: a `0xC8` applies fields until the first bad one, the busy flag is not readable, and front-panel edits apply live, so a re-read after any failure is what keeps a stale value from being re-sent (H-003). |
| AR-026 | `session` implements the link state machine: `Connected`, `Binding` (Bluetooth: fast bind, then on `19 FF` a prompt bind with a `Prompt` event; USB: no bind, no `0x18` ever sent), `Allowed`, `Ready` (info and first reading done; control calls before `Ready` are refused with `Error::NotReady`), `Denied` (transport closed), `Lost`. The bind wait is bounded at 30 s from the connection; a link drop during it is reported as `LinkLost`. Between `Connected` and `Allowed` nothing but the bind frames is sent. | SR-007, SR-009, SR-010, SR-011, SR-012, SR-050 | IT-026 | approved | device-model.md 4.1, 4.2. |
| AR-027 | `session` implements the remote-control state machine: `None`, `Requested` (Bluetooth: a deferred request with the 70 s bound and a `Prompt` event, no other control command sent; USB: immediate), `Granted`, `Denied`, `Lost` (from `0xC9` status 1 or a link loss). A control call in `None` requests control as part of that call (the user issued the command); a control call in `Denied` or `Lost` raises `RemoteControlDenied` or `RemoteControlLost` and sends nothing until `request_remote_control()` is called again, except `output_off`, which requests control first (SR-022). `release_remote_control` is sent only while the reading says DC mode, else `ModeError`. | SR-018, SR-023, SR-053, SR-054 | IT-027 | approved (rev 5) | device-model.md 5. |
| AR-028 | `session` emits a `SessionEvent` stream to the products: `Reading`, `FaultsChanged`, `SettingsChanged` (from `0xC5`), `BindResult { recognised }`, `RemoteControl(state)`, `Prompt { kind: ConfirmConnection or AllowRemoteControl, bound_s }`, `SetpointsChanged`, `UncleanExitWarning`, `LinkLost(text)`, `Reconnected`, `ReconnectGaveUp`. The texts of SR-008, SR-028 and SR-053 are constants in `session`; products render or log them and do not derive them. | SR-008, SR-027, SR-028, SR-042, SR-046, SR-050, SR-053 | IT-028 | approved | One wording for the app and the library. |
| AR-029 | `session` implements the reconnect policy of SR-055: off by default, enabled per session, retry every 5 s for up to 10 min, fast bind only (a `19 FF` ends the retries), repeat info and the first reading, never re-take remote control. On link loss the request queue was already emptied (AR-022); nothing issued before the loss is replayed, and the unclean-exit marker is left in place until a reading shows the output off. | SR-055, UR-037 | IT-029 | approved | device-model.md 4.1, 4.4. |
| AR-030 | `session` keeps a process-wide registry of open connections by identifier and refuses a second `connect` to an identifier that is open. The same supply reached over Bluetooth and over USB has two unrelated identifiers, so the "one transport" part of SR-048 rests on the device (a bound Bluetooth host detaches USB). Bluetooth silence caused by an active USB host is not distinguishable from any other silence; the `LinkLost` text names an active USB host as a possible cause, and every Bluetooth timeout is logged with the same hint. | SR-048 | IT-030 | approved (rev 5) | device-model.md 4.3: writes are dropped silently and no frame tells the Bluetooth host why. |

### 2.5 discovery, store and csv

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-032 | `discovery` has two pure classifiers, `classify_advertisement(name, manufacturer_data)` (name prefix `0000MP30`, or company `0xABBA` with data starting `AF FA`) and `classify_hid(vid, pid, product)` (`0x28E9:0x028A`, product containing `MP305`), and two thin backends (`btleplug` scan of 10 s by default, 1 s to 60 s; `hidapi` enumeration) that feed them. It returns `Found { transport, os_id, unit_id, name, rssi, remote_flag }`, where `unit_id` is the last three name characters over Bluetooth and the HID path over USB. | SR-001, SR-002, SR-003 | IT-032 | approved | device-model.md 1. The classifiers are what the integration tests feed. |
| AR-033 | `store` keeps the per-installation state in a directory given at construction (`Store::new(path)`, the products pass the user's state directory from the `directories` crate): the 16-byte host ID (generated once from the OS random source, never all zero, never WebLink's constant) and one unclean-exit marker per supply identifier with a timestamp. A missing or corrupt file is regenerated (host ID) or ignored (marker) and logged. | SR-046, SR-049 | IT-033 | approved | device-model.md 3, 4.1. |
| AR-034 | `csv` writes readings in the format of SR-037 to any `impl std::io::Write`, flushing after each row, and is the one CSV implementation for both products. | SR-037, UR-014, UR-028 | IT-034 | approved | One format, one implementation; the sink is injected so the core opens no files here. |

## 3. Products

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-040 | `mp305-py` exposes the session synchronously: `discover()`, `Mp305.connect(identifier=None)` (without an identifier only when discovery found exactly one supply, else `NotFoundError` naming the supplies found), a context manager whose `__exit__` runs the SR-029 sequence (output off as SR-022, then `0xC8` with `remoteCon = 0`, then disconnect) also when an exception is in flight, logging any error instead of masking that exception, and `close()` doing the same. Every setpoint entry point validates the value in Python (finite, 0 to 30 V, 0 to 5 A, user limits) before any native call. `Prompt` events become `logging` WARNING records with the SR-008 and SR-053 texts and one call of the optional callback; the other events are exposed as a queue and through `readings()`. Exceptions map one to one from `Error` (AR-050). Readings are immutable objects with the fields of SR-033. A test-only constructor `Mp305._from_mock(script)` exposes the mock transport. The pure Python package adds `stream()`, `to_csv()` and `ramp()`. | UR-015 to UR-018, UR-028, UR-029, SR-004, SR-005, SR-008, SR-029, SR-031 to SR-035, SR-053 | IT-040 | approved | ADR-0006, ADR-0007, ADR-0008 (Python-side validation). Helpers in Python stay easy to read and change. |
| AR-041 | `mp305-app` keeps device I/O on a Tokio worker task that owns the `session` and forwards `SessionEvent`s over a channel; the UI thread sends commands (`Connect(identifier)`, setpoints, `OutputOn`, `OutputOff`, `RequestRemoteControl`, `Disconnect { output_off: bool }`) over another channel and never blocks. `Connect` is sent only after a user selection. A disconnect or window close with the output on first asks whether to switch the output off, then sends `Disconnect` with the answer; the worker runs the SR-022 path if asked and always releases remote control before closing. The `model` module holds the non-drawing state: the chart ring buffer sized for 10 min at 4 readings per second, the window setting (60 s default, 10 s to 10 min), the user limits, and the last events. Drawing code lives in `ui/` and holds no logic beyond layout. | SR-004, SR-030, SR-038, SR-039, SR-040, SR-041, SR-042 | IT-041 | approved | ADR-0005. The `ui/` split is what the coverage exclusion of ADR-0008 relies on. |
| AR-042 | Packaging: the macOS bundle declares `NSBluetoothAlwaysUsageDescription`; wheels are built for CPython 3.10 and later on macOS 13 (arm64, x86_64), manylinux_2_35 (x86_64, aarch64) and Windows 10 22H2 (x86_64) with a `.pyi` stub; the README of each product carries the bench-safety note of UR-031 and the app links to it from its connection screen. | SR-036, SR-043, SR-047 | IT-042 | approved | The OS minima of TBD-014. |

## 4. Cross-cutting

| ID | Architecture item | Parent or source | Verification | Status | Rationale |
|---|---|---|---|---|---|
| AR-050 | `mp305-core` has one `Error` enum: `NotFound { causes }` (the four causes of SR-005 as text), `ConnectionDenied`, `RemoteControlDenied`, `RemoteControlLost`, `SetpointRange`, `CommandRejected { status, reason }`, `Mode`, `FaultActive`, `NotReady`, `Timeout`, `LinkLost { text }`, `Transport`, `Store`, `Protocol`, `AlreadyOpen { identifier }` (a second session to an open identifier, AR-030), `Cancelled { reason }` (a command dropped by an output-off or a close). The Python mapping is total: the first eleven map to the exceptions of SR-032 one to one (`NotReady` to `Mp305Error`), `Transport` to `LinkLostError`, `Store`, `Protocol`, `AlreadyOpen` and `Cancelled` to `Mp305Error`. The app's messages map from the same enum. | SR-005, SR-023, SR-032, UR-016 | IT-050 | approved (rev 5) | One error taxonomy keeps the two products consistent. |
| AR-052 | Every module starts with a `//! Implements: AR-nnn, DD-...` comment and every automated test names its specification ID; `scripts/check_traceability.py` reads both. | ADR-0008, AGENTS.md | IT-052 | approved | Makes the matrix generation work for code. |

## 5. Key flows

Connect over Bluetooth (AR-016, AR-026, AR-033):

```
discovery -> transport::ble.connect(os_id); Guarded around it
          -> enable notifications AF01, AF02 (every connection)
          -> session: bind(host_id, fast=1) on AF02      [deferred, 30 s]
             19 00 -> Allowed, event BindResult{recognised: true}
             19 FF -> event Prompt(ConfirmConnection, 30 s); bind(host_id, fast=0)
                      19 00 -> Allowed, BindResult{recognised: false}
                      19 FF -> Denied, transport closed
                      link drop or 30 s since connect -> Timeout, closed
          -> info (0xE0), first reading (0xC2) -> Ready; poll runs in link
```

First control command over Bluetooth (AR-020, AR-027):

```
set_voltage (remote None) -> 0xC8 rc=2 from the latest reading  [deferred, 70 s]
   link frees the slot; 0xC2 polls continue; no other control command sent
   event Prompt(AllowRemoteControl, 70 s)
   0xC9 status 0 -> Granted; 0xC8 rc=1 with the new voltage [immediate, 1 s]
   0xC9 status 1, or 70 s -> Denied (error to the caller, nothing sent)
```

Link loss with reconnection enabled (AR-022, AR-029):

```
link: LinkLost(reason); queues emptied, pending requests fail
session: remote -> Lost; event LinkLost("output still in its last state ...")
  reconnect enabled -> every 5 s: connect, fast bind, info, reading
     success -> Ready, event Reconnected; polling resumes; no 0xC8
     19 FF, or 10 min -> event ReconnectGaveUp
```

## 6. Open points at this level

| ID | Open point | Affects | How it gets settled |
|---|---|---|---|
| TBD-019 | Whether `btleplug` on macOS, Linux (BlueZ) and Windows delivers the notification ordering the design assumes and exposes the negotiated MTU. | AR-016 | The runs of ST-008 and ST-039 on each OS (TBD-009). |
| TBD-020 | Whether `hidapi` report writes need the leading report ID byte in the buffer on each OS (they do on Windows and Linux hidraw). | AR-017 | Checked in the USB spike (TBD-013) on each OS. |
| TBD-021 | SR-007 said the system requests an ATT MTU of 247; `btleplug` has no MTU request and the OS negotiates. | AR-016, SR-007 | Settled 2026-09-30: SR-007 changed to verify the negotiated MTU (revision 11 of 2-system-requirements.md). |
| TBD-022 | ADR-0008 section 1 mentioned an output-off on disconnection that the device does not allow. | AR-022, ADR-0008 | Settled 2026-09-30: editorial note added to ADR-0008. |

## 7. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-30 | First draft for G3, from the chat draft of 2026-09-29 and device-model.md | not yet approved |
| 2 | 2026-09-30 | Independent review resolved: `Guarded` wrapper enforces allowlist, one write in flight and frame log for every transport; HID framing and discovery classification are pure functions in `protocol` and `discovery`; `link` distinguishes immediate and deferred requests, has an urgent queue for output-off, runs the poll, the keepalive and the loss detection on the Tokio clock; `session` gains `Ready`, the re-read after a failed or timed-out `0xC8`, the busy inference order, the marker refresh and removal, the explicit re-request after `Denied` or `Lost`, and the connection registry; AR-016 verifies the negotiated MTU; AR-040 gains Python-side validation, the `close()` sequence, prompt logging and the mock constructor; AR-041 gains the disconnect question and the chart model; AR-034 (csv), AR-042 (packaging) and AR-014 (timing constants) added; AR-002, AR-004, AR-018, AR-030, AR-032, AR-050 corrected; TBD-021 and TBD-022 added. | user, 2026-09-30 (G3) |
| 3 | 2026-09-30 | AR-017 changed under the change procedure (transport DD review): the transport keeps a frame's reports together; waiting for the reply is `link`'s rule, since ignored opcodes get no reply and only `link` has the timeout. | user, 2026-09-30 (with G4 transport) |
| 4 | 2026-10-01 | AR-022 marked changed (link DD review, decision 2 of link.md section 7): every immediate request that times out counts toward the three that end the link, not only the poll. Approved with G4 link. | user, 2026-10-01 (G4 link) |
| 5 | 2026-10-01 | AR-050, AR-025, AR-027 and AR-030 marked changed from the session DD review (session.md section 9, decisions 1, 3, 8 and 7): two error variants, the `output` copy rule, the output-off exception, the USB-host hint on timeouts in the log. Approved with G4 session. | user, 2026-10-01 (G4 session) |
