# Recovered firmware analysis

Date: 2026-09-30. Revision: **uncommitted**. This completes the recoverable
host-interface jobs left in `~/mp305b-fw-re`. The original workspace is
preserved. Working copies, Ghidra databases and firmware images remain in
`~/mp305b-fw-re/recovery-2026-09-30`.

## Results

- **33 offline probe jobs completed** with checked emulator returns.
- **657 asserted cases passed**: 305 encoder comparisons, 300 decoder
  comparisons, eight bridge-route scenarios and 44 recovery assertions.
- **324 command-table rows** were regenerated, including state changes and
  calls. These are recorded observations, separate from the asserted cases.
- **322 named locations** were reconciled, retaining aliases at 22 locations.
- **3088 function exports** were recovered: 2453 main, 255 CH58x and 380 PD.
  Every requested function decompiled, with zero reported failures. Function
  boundaries, types and decompiler warnings still require interpretation.
- The existing 3694-function canonical bundle remains intact. The two
  analyses use different entry sets; their counts must not be added.

No physical device, BLE link, USB port or UART was accessed. These results
do not pass a V-model gate. The earlier 2835-case suite is a separate run;
its results remain in [the earlier verification record](../../verification.md).

## Read the findings

| File | Contents |
|---|---|
| [Command analysis](notes/commands.md) | All opcode branches, handlers, remote control, deferred replies, program/PD/charge structures, units, fault producers, update staging and regenerated vectors |
| [Host-link analysis](notes/hostlink.md) | UARTs, framing, mailboxes, bind flow, remote prompts, retransmission, link loss, console and accessory input |
| [CH58x analysis](notes/ch58x.md) | GATT database, advertising, saved host IDs, USB descriptors and queues, BLE/USB arbitration, accessory central role, DataFlash, timers and pins |
| [Comparison report](report.md) | Reviewed conclusions and the recovered statement-by-statement comparisons |
| [Printable report](report.pdf) | The comparison report as a rendered LaTeX document |
| [Named locations and aliases](verification/names.json) | Original source, primary name and every alternative name |
| [Function comparison](verification/function-comparison.json) | Original, recovered and canonical entry-set differences |
| [Job ledger](verification/jobs.json) | Exact commands, completion status, durations and output hashes |
| [Recovery assertions](verification/assertions.json) | Expected and actual values for each additional asserted case |

The notes' **disasm**, **decomp**, **[A]**, **[D]** and **[M]** labels mean
**confirmed in code**. **emu** and **[E]** also mean confirmed in code,
for the stated synthetic inputs and modeled external calls. **[I]** means
**inferred**. Earlier-document verdicts refer to the source snapshot. Some
earlier documents already contained overlapping findings from another pass.
No recovered note is a new hardware confirmation. A comparison between two
firmware reconstructions is not a WebLink cross-check.

## Reuse this work

The [workflow](../../../workflow/README.md) covers future releases.
[Ghidra snapshots](../ghidra/README.md) preserve both program interpretations,
including types, symbols, context, comments, mappings and function metadata,
with documented import limitations. [Historical sources](historical/README.md)
retain the original scripts, notes, names and outputs. The maintained recovery
runners are the entry point for rerunning V51 jobs.

All 33 jobs and the 44-case assertion runner were rerun after relocation.
Their [job ledger](verification/relocation-jobs.json) and
[assertion results](verification/relocation-assertions.json) confirm the new paths.
This repeats the same cases and does not increase the distinct case count.

## What needed repair

| Problem | Resolution and evidence |
|---|---|
| Emulator instruction budgets could expire without a failure | ARM and both RV32 helpers now require the return trap. Separate one-instruction cases prove that exhaustion raises an error |
| Absolute imports could select older helpers | Recovered probes import their own script directory. The assertion runner requires `MP305_RE_SCRIPTS` explicitly |
| CH58x global pointer was wrong in one helper and its notes | Original startup instructions yield `0x20002000`: `AUIPC` uses its own PC. The mistaken value was `0x200023B8` |
| AF02 bind-success routing entered a physical flash wait loop | Added an explicit successful DataFlash-call model in the minimal routing harness. The larger bridge harness separately models saved-ID storage. The failed strict-return log is retained |
| Encoder/decoder mismatches were printed without failing the job | Both comparisons now assert zero mismatches |
| Name application order depended on directory enumeration | Sorted source order, one primary name per address, all aliases preserved in the ledger and comments |
| Reset helpers appeared to fall through into unrelated storage code | Instruction inspection and a write trace establish a non-returning reset path. Three Ghidra function attributes now reflect it |
| Report contained only a preamble | Completed the Markdown comparison, LaTeX source and rendered PDF |

See [the harness patch](verification/harness-repairs.patch) and the
[spike](../../../../../spikes/firmware_reconstruct/README.md). Failed preliminary
attempts are kept in the scratchpad. The final logs and assertions establish
the reported result; a process exit alone is not a passing semantic test.

## Corrections established during recovery

1. **Confirmed in code:** `SystemInit` writes `0x10000` to VTOR at
   `0x1DB8C`. The older firmware.md statement that startup only reads VTOR
   was incorrect.
2. **Confirmed in code:** the main decoder state is at record `+0x208`,
   the 32-bit fill index at `+0x20C`, and the escape counter at `+0x213`.
   The original independent note proposed the wrong correction here.
3. **Confirmed in code:** `FE AA 55` schedules a factory reset and reboot.
   The final path writes `0x1234` at `0x2005F000`, then requests reset
   through AIRCR. This does not identify what the missing bootloader does
   with that mailbox value.
4. **Confirmed in code:** AF01's incoming first byte is discarded. The
   reply prefix `31` is a routing marker. UART address `12` instead encodes
   source 1, destination 2; replies swap source and destination.
5. **Confirmed in code:** `C3.wavePause` is 1 if the waveform timer pointer
   is zero; otherwise it is `S+0x11`. Its value alone does not establish
   whether host streaming is active. Both stored values were exercised.
6. **Confirmed in code:** the power fault source is `0x1FFFAA1E`, copied to
   `S+0x9E`, which is `0x1FFFAB6A`. They are two addresses, not aliases.
7. **Confirmed in code:** software fault boundaries include 501 mV on the
   reverse-sensor input, temperatures below -19 C or above 57 C, system
   temperature at least 85 C, output voltage at least 33001 mV, and voltage
   disagreement at least 5000 mV. Timing and latching conditions are in the
   command notes. Sensor names and physical circuit assignments remain
   inferred where no hardware identification exists.
8. **Confirmed in code:** the reviewed power fault producers set bits 0
   through 8. The separate charger word contributes bits 10 and 11 to EC.
   The former blanket description of C3 bits 9 through 15 as charger faults
   was unsupported. No universal absence claim is made about indirect writes.

## Interoperability consequences

- The shared remote-control path gates C8, E2, E8 and EE. The four
  no-grant cases return status 1 in the tested mode states. Reads and C6
  follow separate paths.
- A source-6 BE accessory-button press/release reaches the output-key
  worker without a remote grant in synthetic state. The actuator recorder
  receives an output-enable request. This extends the permission map; it
  does not show physical output activation or a hardware test after denial.
- USB reports need stream reassembly. A 127-byte framed reply produces
  payload chunks of 62, 62 and 3 bytes. Two complete OUT frames in one
  report overwrite the first in the exercised bridge path.
- Main transmit state holds one outstanding reply. Sending another request
  before acknowledgment can overwrite a pending response. Serialize client
  requests until actual transport behavior has been characterized.
- Binding, the remote grant, link state and the output request are separate.
  The tested UI link-loss path clears the grant while retaining an already
  set output request. It does not prove whole-device electrical behavior.
- The recovered CH58x code implements saved host IDs and a fast-binding
  branch. The normal WebLink request uses a zero fast flag. Hardware
  confirmation remains TBD-006.
- The USB descriptor uses usage page 1, usage 0; WebLink's filter uses
  usage 4. User-accessible USB connectivity and descriptor matching remain
  hardware questions, including the MP305B rear-port distinction.

These findings are research inputs. They do not change UR-008's existing
decision to disconnect after denial or approve any production design.

## Provenance and coverage

The workspace's app.bin is WebLink's 476160-byte application copy, with four
`FF` bytes at file offset `0x6AFC8`. The canonical restored image instead
holds identity magic there. All other application bytes agree. The companion
image and its two slices match byte for byte. Running the original scatter
routine reproduces all 2908 initialized RAM bytes. See
[input comparisons](verification/input-comparison.json) and
[run inputs](verification/run-inputs.json).

The original Ghidra imports had 2310 main, 243 CH58x and 380 PD functions.
The pending main helper added 143 candidate entries; the bridge helper added
12 callbacks. These are analysis entries, not measured code coverage. The
recovered main and canonical main differ by 144 versus 146 entry addresses;
CH58x differs by 27 versus four, including RAM aliases; PD differs by eight
versus 635. The richer canonical PD table recovery is retained.

HC32F4A0 register labels in recovered C come from the original project's SVD
choice. They are candidate names, not proof of that exact MCU. Literal
scoring gives similar matches for multiple HC32 parts and leaves the
`0x40054000` clock-controller conflict unresolved. The external WCH library
was modeled from the existing API map; the installed library was not dumped.
CH58x CSR decompiler warnings remain in the logs.

The original job scope was host interoperability. Power and PD internals,
complete register semantics, physical topology, bootloader behavior,
calibration and an executable replacement firmware remain open research.
The recovered update-staging vectors exercise an in-memory flash model.
They are not a verified firmware-update procedure.

## Verification files

[Environment](verification/environment.json),
[export checks](verification/export-checks.json),
[source snapshot](verification/workspace-before.json),
[table comparison](verification/table-comparison.json), and
[integrity audit](verification/integrity.json) record the completed pass.
The table comparison is textual: shorthand setup columns and abbreviated
maintenance frames differ from regenerated full rows. These differences
are not counted as failed firmware checks. The notes now contain the full
regenerated tables.

All original firmware inputs, projects and notes were retained outside the
repository. Captures and canonical per-function exports were not edited.
The new bundle manifest records the current recovered artifacts. The older
research-bundle manifest remains a historical snapshot of the earlier run.
