# Firmware merge and verification record

The later [independent recovery record](v51/independent/README.md)
documents the completed `~/mp305b-fw-re` jobs, 657 additional asserted cases
and corrections to the research text. Results and hashes below describe
this earlier merge run; its bundle manifest is a historical snapshot.

Date: 2026-09-30. Revision: **uncommitted**. This pass merges the two
scratchpads into repository research, corrects earlier claims, adds
readable C and subsystem maps, and preserves all canonical per-function
exports. It changes research documentation, TODO.md, LOGBOOK.md and a
research spike. No production implementation or approved requirement was
changed. These checks are not a V-model gate verification run.

## Results

**2835 offline cases passed**, plus **16 merge-specific input comparisons**.
All four existing hardware captures were rechecked without modification.
No new BLE, HID, UART or physical-device I/O occurred. Original firmware
files and generated binaries remain outside the repository.

| Group | Cases | Record |
|---|---:|---|
| Original ARM settings, identity and framing | 344 | [result](v51/canonical/verification/emulation-results.json) |
| Readable C6/framer versus ARM, decoder round trips, checksum rejection | 700 | [result](v51/canonical/verification/reconstruction-comparison.json) |
| C8 control, mode and grant paths | 18 | [result](v51/canonical/verification/control-emulation.json) |
| Seven readable reply builders versus ARM | 896 | [result](v51/canonical/verification/read-reply-comparison.json) |
| Address/length/stuffing boundaries, deferred D9, E2/E8/EE fields | 592 | [result](v51/canonical/verification/extended-emulation.json) |
| Original RV32 bridge, host FIFO and USB chunking | 27 | [result](v51/canonical/verification/ble-emulation.json) |
| Deferred settings normalization | 82 | [result](v51/canonical/verification/settings-worker-emulation.json) |
| Serial storage command formatting | 16 | [result](v51/canonical/verification/storage-emulation.json) |
| Kernel heap, tasks, queues, mutex, events and scheduling primitives | 62 | [result](v51/canonical/verification/rtos-emulation.json) |
| Binding denial, dispatcher and selected permissions | 34 | [result](v51/canonical/verification/permission-emulation.json) |
| Readable D9/reference-register workers and display setup | 64 | [result](v51/canonical/verification/worker-comparison.json) |
| **Portable suite total** | **2835** | [summary and hashes](v51/canonical/verification/run-summary.json) |
| Separate source/layout comparisons | 16 | [result](v51/canonical/verification/input-verification.json) |

One case can contain multiple assertions. Counts do not measure instruction,
branch, function or hardware coverage. The 1958 earlier cases are included
in 2835, not added to it. Duplicate historical result files must not be
counted twice. [Capture reanalysis](v51/canonical/verification/capture-audit.json)
is reported separately from the emulation totals.

## Environment and exact run

- macOS 27.0, build 26A428, Apple arm64.
- Python 3.12.2, Unicorn 2.1.4, Capstone 5.0.9.
- Apple clang 21.0.0, Ghidra 12.1.3, OpenJDK 21.
- Firmware: MP305B V51 main 1.6.0.51; no transport or device selected.

From `/Users/jihlenburg/mp305b`:

```sh
python3 spikes/firmware_verify/scripts/prepare_run.py \
  --scratch /Users/jihlenburg/mp305b-firmware-scratch/2026-09-30-merge/portable-final \
  --firmware /Users/jihlenburg/mp305b-firmware-scratch/2026-09-30-merge/inputs/MP305B-V51.fwd \
  --plain /Users/jihlenburg/mp305b-firmware-scratch/2026-09-30-merge/inputs/MP305B-V51.plain.bin
MP305_PYTHON=/Users/jihlenburg/mp305b-firmware-scratch/2026-09-29/.venv/bin/python \
  sh /Users/jihlenburg/mp305b-firmware-scratch/2026-09-30-merge/portable-final/scripts/verify_offline.sh
python3 spikes/firmware_verify/scripts/audit_captures.py \
  docs/research/captures docs/research/firmware/v51/canonical/verification/capture-audit.json
```

[The final log](v51/canonical/verification/portable-final.log) and
[staged script/input hashes](v51/canonical/verification/run-inputs.json)
identify the actual run. The script independently restores the container,
executes original scatter loading, compiles the readable C with
`-std=c11 -Wall -Wextra -Werror -O2`, then runs every group above.
The [spike README](../../../spikes/firmware_verify/README.md) gives portable
commands with new scratch-directory paths.

An earlier portable run passed all instruction comparisons but failed
its optional table-export step because the external WCH SDK was absent.
The runner was corrected to keep that reference-dependent export separate,
then staged afresh and rerun successfully. The failed run and log remain
in the external merge scratchpad; it is not reported as a passing run.

## What was independently checked

- Four original input copies agree across the local firmware cache and
  both scratchpads. Original and restored hashes are recorded.
- The FWD checksum, split sizes and unchanged identity block were
  independently restored, including the exact four-byte WebLink mutation.
- Main reset and companion entry mapping were checked against bytes and
  instructions. The 8051 jump targets real startup when loaded at `0x1000`.
- The original ARM scatter loader produced initialized RAM, rather than
  treating compressed bytes as a ready-to-use data section.
- Selected readable C is compared against original instructions and full
  affected state, not only against a second handwritten implementation.
- The main decoder was exercised over all address bytes and lengths 1..255,
  with additional delimiter, zero-length and checksum cases.
- New hardware-bus conclusions were traced to register access, call
  arguments and data packing; exact component names remain inferred.
- Existing capture frame lengths and identity bytes were re-derived from
  raw RX records. Old embedded result labels were not taken as field truth.

## Decompilation and access coverage

The prior independent Ghidra rebuild reproduced function-entry sets of
2455 main, 1007 PD and 232 BLE entries. The supplementary SDK has 1047.
[Rebuild comparison](v51/canonical/verification/rebuild-comparison.json).
This proves repeatability of discovery, not correctness of every function.

| Image | Bytes classified as instructions in flash | Image bytes | Functions with warnings |
|---|---:|---:|---:|
| Main | 335078 | 476160 | 203 |
| PD | 34470 | 45056 | 102 |
| BLE | 30548 | 34432 | 53 |

Data tables, padding, compressed data and undiscovered code all affect
these ratios, so they are not “percent reverse engineered.” BLE also has
974 listed instructions in other mappings, including copied RAM code;
two functions retain bad-data diagnostics.

The new read-only memory pass produced 68,937 raw access records and
bounded decompiler address expressions across all three programs.
[The access inventory](../device/registers.md) retains unresolved pointers
and explains the limits of register attribution. All decompiler calls
completed, but the existing warnings and unresolved indirect accesses
remain material limitations.

## Scratchpad claim reconciliation

The original report and notes remain untouched externally, with
[source hashes](v51/canonical/sources.md). The following supersedes their
conflicting interpretations; it does not silently promote old guesses.

| Earlier claim | Reconciled finding |
|---|---|
| Completely recovered C for all firmware | Full discovered-function exports retained, but heuristic boundaries, warnings, missing code and unreviewed semantics remain |
| Main SRAM begins at `0x20000000` | Startup initializes `0x1FFE0000`, zeroes from `0x1FFE0B5C`, with end/SP `0x2003F618` |
| PD LJMP enters the zero gap | Wrong load-base interpretation: CODE base `0x1000`, target `0xAF88`, file offset `0x9F88` contains startup |
| BLE application begins at zero | Base `0x1000`; entry reaches `0x1C48`, then external library at `0x40000` |
| PD `P829` identifies the chip | It is a program string; exact MCU and physical power-switch roles remain unproved |
| Reply is always request plus one | Opcode `0x20` replies with `0x20`; other commands may have no immediate reply |
| C8 maximum voltage is 30500 raw | C8 accepts 3050 raw; program-record voltage limit is 30500 |
| C8 status 1 means granted | Status 1 reports absent/revoked remote control on the reviewed paths |
| C8 rejection changes nothing | Sequential stores and common remote-state epilogue can preserve or produce changes |
| Modes are charge/storage/discharge at 1/2/3 | Actual modes are 0 DC, 1 program, 2 PD, 3 charger |
| C2 field names and units inferred from offsets | Byte copies agree, but several old physical meanings conflict with hardware-confirmed protocol fields; use protocol.md and exact-byte reconstruction |
| Type-6 suffix is a client sequence byte on air | It is internal bridge routing; AF01/AF02 notification paths remove it |
| Four logical routes identify four physical links | Four mailboxes share UART `0x4001D400`; the separate channel-0 UART is the PD-link candidate |
| E0 contains a recovered eight-byte UUID | Long E0 reads a pointer from missing boot address `0x1C`, then bytes at pointer+12; exact data and meaning unresolved |
| D8 has no reply in the image | Deferred storage load and D9 builder traced; chunks contain up to ten records |
| Binding reply is absent from the main image | UI callbacks and deferred `0x12690` builder traced; BLE also supports saved-host lookup |
| Denial blocks the connection's commands | Reads remain available; selected C6 write path is also ungated, while C8 checks separate remote permission |
| C6 accepts arbitrary in-range settings permanently | Some fields are normalized by a deferred worker; early writes can persist after later validation failure |
| USB descriptor offsets identify the main MCU | Descriptors belong to the RV32 companion; VID/PID do not identify the main MCU |
| `0x40054000` is flash control | HC32 reference comparison calls it CMU; internal EFM and external serial storage are separate |
| “FreeRTOS” attribution proves version and resources | Kernel behavior, task sizes and concrete resources are traced; version remains unknown and companion schedulers are separate |

The old C8 payload labels also shifted output/protection meanings. The
current byte tables and instruction-level checks take precedence. The
old report's functions are not merged by address alone across images with
different load bases.

## Limits that remain

No whole-device execution, real interrupt delivery, electrical waveform,
flash endurance, maximum stack usage, concurrent-task stress or physical
fault response was tested. Bus tests substitute transfer/status functions;
BLE tests substitute SDK memory, storage and notification calls. E0's
missing boot identity is synthetic in the long-layout experiment.

Exact MCU packages, PD peripheral map, complete callback reachability,
unresolved load/store addresses, power-stage topology, sensor calibration,
display/touch variants and installed library/boot bytes still need work.
These gaps are retained in TODO.md and the subsystem documents. No claim
is made that every firmware instruction or physical component is verified.


## Repository integrity

The [artifact audit](v51/canonical/verification/repository-audit.json) checked
4773 canonical export hashes and 4947 local file links, parsed every Python
research script, checked shell/C syntax and found no firmware or compiled
binary in the imported research directories. All four capture hashes match
the starting snapshot. The audit reported no artifact errors.

Concurrent licensing, anonymity and quality-standard changes were observed
in AGENTS.md, ADR files and portions of README.md/LOGBOOK.md. They were
preserved. Research changes do not imply approval or verification of those
separate edits. Git status remains uncommitted.
