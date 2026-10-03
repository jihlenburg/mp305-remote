# Research

Evidence the design depends on. The device firmware is the main source of
truth. Findings from WebLink, from hardware, and from anywhere else come on
top of it (LOGBOOK 2026-09-29, "Firmware is the main source of truth").
Where the firmware and another finding differ, the project uses the firmware.

Each file says where its information came from and when it was gathered, and
gives each fact one of three evidence labels:

- confirmed in code: read from the decompiled device firmware, or from the
  JavaScript of ISDT's WebLink page. A WebLink reading is a finding on top
  of the firmware.
- confirmed on hardware: observed on the author's MP305B. A hardware
  observation is a finding on top of the firmware.
- inferred: concluded from other facts.

An item is "cross-checked" when it was derived a second time, independently,
from the WebLink JavaScript. A cross-check is a finding on top of the
firmware. It is not a hardware confirmation.

For sources other than the device firmware, production code relies only on
items marked confirmed on hardware, or on items that the relevant detailed
design (DD) file explicitly accepts as inferred, with a TBD entry.

Decompiling the device firmware is fully allowed under Directive 2009/24/EC
(2009/24/EG), in order to ensure full interoperability of `mp305` and
`mp305-app` with the device. There is no limit on the information contained
in that firmware. It is used to its fullest (AGENTS.md, ADR-0010, LOGBOOK
2026-09-29, "Firmware information").

The firmware image stays out of this repository. Interoperability
information reconstructed or gathered from it stays in this repository, in
whatever form it takes (LOGBOOK 2026-09-29, "Where firmware material is
kept").

Downloaded copies of ISDT's original WebLink asset files are not stored in
this repository. Interoperability information gathered from those files is.

## Start here

| Area | Contents |
|---|---|
| [Device](device/README.md) | Identity, board hypotheses, buses, registers, UI and analog paths |
| [Device model](device-model.md) | The device as a host sees it: identification, transports, bind, remote control, link loss, reply discipline, modes, telemetry units and timings. The starting point for the requirements rewrite |
| [Protocol](protocol.md) | Framing, commands, payloads, units and recorded transport behavior |
| [Firmware](firmware/README.md) | Architecture, RTOS, command map, permissions, readable reconstructions and verification |
| [Firmware source narrative](firmware.md) | V51 image restoration and instruction-level evidence for the host protocol |
| [V51 evidence](firmware/v51/README.md) | Canonical and independently recovered exports, logs and comparison report |
| [Ghidra snapshots](firmware/v51/ghidra/README.md) | Seven programs exported without firmware memory contents, with restore checks |
| [Repeat the analysis](workflow/README.md) | Restore existing work or begin a future firmware release |
| [Reference definitions](reference/README.md) | Preserved register descriptions, provenance and licensing notices |
| [Captures](#captures) | Immutable observations from the real unit |

Reviewed topic documents summarize the evidence. Versioned directories retain
raw analysis exports, run records and historical notes. Counts of discovered
functions or accesses describe the analysis output, not proof of complete
coverage. Outstanding questions remain in [TODO.md](../../TODO.md).

The 2026-09-30 cleanup moved existing evidence without discarding it.
[structure-map.json](structure-map.json) resolves old paths in historical
logs and manifests. Current links use the new layout. Firmware images and
Ghidra databases containing them remain outside the repository.

## Captures

Raw hardware captures are stored once, in `captures/`, exactly as the spike
that recorded them wrote them: JSONL with a meta line first, then one line
per sent or received frame, then a results line. A capture is never edited
after recording. A correction is a new capture or a note.

Each capture is described in a LOGBOOK entry giving the date, the transport,
what was sent, and the device firmware version or a pointer to where it is
recorded.

Rust and Python fixture tests do not read these files and do not keep copies
of them. A test embeds the exact frames it needs inline and cites the capture
file name and the event timestamp (`t`) in a comment, for example
`// 2026-09-29T193614-ble-readonly.jsonl, t = 12.7497`.

| Capture | Transport | Bind reply | LOGBOOK entry (2026-09-29) | Firmware version |
|---|---|---|---|---|
| `2026-09-29T193614-ble-readonly.jsonl` | Bluetooth LE | allowed (`19 00`) | Hardware: read-only Bluetooth LE spike | System V1.6.0.40, Firmware V2.0.2.0 |
| `2026-09-29T194219-ble-readonly.jsonl` | Bluetooth LE | allowed (`19 00`) | Hardware: remembered-host test | System V1.6.0.40, Firmware V2.0.2.0 |
| `2026-09-29T194319-ble-readonly.jsonl` | Bluetooth LE | denied (`19 FF`) | Hardware: deny test | System V1.6.0.40, Firmware V2.0.2.0 |
| `2026-09-29T201428-ble-readonly.jsonl` | Bluetooth LE | allowed (`19 00`) | Hardware: read-only spike after the firmware update | `0xE1` still reports 1.6.0.40 / 2.0.2.0; update status open |

These four were recorded by [spikes/ble_readonly/](../../spikes/ble_readonly/),
which lists what it sends.

| Capture | Transport | What was sent | LOGBOOK entry (2026-10-02) | Firmware version |
|---|---|---|---|---|
| `2026-10-02T103456-vm-dongle-scan-linux.jsonl` | Bluetooth LE, advertising only (Linux VM, USB dongle) | nothing above the link layer (active scan) | USB Bluetooth dongle in the VMs | not read |
| `2026-10-02T104520-vm-dongle-scan-windows.jsonl` | Bluetooth LE, advertising only (Windows VM, USB dongle) | nothing above the link layer (active scan) | USB Bluetooth dongle in the VMs | not read |

These two come from [spikes/vm_dongle_scan/](../../spikes/vm_dongle_scan/).
They are transcribed from the scripts' console output, hold only the
supply's advertisements, and mask the last three octets of its address.

| Capture | Transport | What was sent | LOGBOOK entry (2026-10-04) | Firmware version |
|---|---|---|---|---|
| `2026-10-03T224341-dongle-acl-supply.jsonl` | Bluetooth LE, raw HCI through the USB dongle on the Mac, no VM | a connection, link-layer feature and version queries, ATT Exchange MTU Request, ATT Read By Group Type Request; no frame of the protocol | The dongle delivers no received data, also without a VM | not read |
| `2026-10-03T224614-dongle-acl-mac.jsonl` | the same, with the Mac's built-in Bluetooth as the peer instead of the supply | nothing to the supply | The dongle delivers no received data, also without a VM | does not apply |
| `2026-10-03T225259-dongle-acl-mac.jsonl` | the same, after the dongle was unplugged and plugged in again (no firmware loaded) | nothing to the supply | The dongle after a power cycle | does not apply |

These three come from [spikes/dongle_acl_path/](../../spikes/dongle_acl_path/).
Their file names carry the UTC time, so they are dated 2026-10-03 for runs
made shortly after midnight local time on 2026-10-04. They hold the HCI
packets of the dongle (`hci` says which kind, `hex` is the packet without
the transport's type byte), mask the last three octets of the peer's
address, and leave out the advertisements of other devices. The
advertising reports carry the time the scan ended, not the time they
arrived.

## Firmware version

The device reports its versions in the `0xE1` reply to `0xE0`, over
Bluetooth as well as USB (confirmed on hardware, LOGBOOK 2026-09-29,
"Corrections, second round"):

| `0xE1` bytes after the opcode | WebLink label | Value on 2026-09-29 before the update |
|---|---|---|
| 1 to 4 | System Version (main firmware, the version ISDT's update manifest compares) | 1.6.0.40 |
| 13 to 16 | Firmware Version (a mistranslation: the Chinese UI says hardware version, so this is the hardware revision) | 2.0.2.0 |

Both values come from the main MCU: the `0xE1` reply is built by the main
application from constants in its own identity block, and the Bluetooth
chip only relays it (confirmed in code, image 1.6.0.51). The Bluetooth chip
has its own version (1.0.0.15 in the 1.6.0.51 update), which it reports to
the main MCU and never to a host. Whether the user's unit runs that
Bluetooth chip version is not known. The Device Information service holds
only placeholder strings from the Bluetooth chip vendor's SDK and is not
used.

Procedure:

1. Read both versions from `0xE1` (the read-only spike records the reply).
2. Record them in LOGBOOK.md with the date.
3. Captures and hardware runs cite that LOGBOOK entry.
4. After any firmware update, record the new versions and compare a new
   read-only capture with the previous one.
