# Binding, denial and command permissions

## Additional recovered paths

The [independent recovery](v51/independent/README.md) adds four executed
no-grant cases for C8, E2, E8 and EE, one in each mode. Each returns status 1
in the tested state. It also traces source-6 BE accessory-button events
through the dispatcher and output-key worker. With a synthetic valid mode,
no fault, output off and no remote grant, a press/release reaches an
output-enable request. The actuator was replaced with an argument recorder;
no real output was activated. This is confirmed in code for those inputs,
not confirmed on hardware after a denial.

The [44 recovery assertions](v51/independent/verification/assertions.json)
include that path. The [host-link notes](v51/independent/notes/hostlink.md)
describe routing and UI input consumers. Binding and the remote-control
grant do not form a universal command authorization boundary. The existing
policy to disconnect after denial remains unchanged.


Updated 2026-09-30. The firmware does not implement a single permission
check for all commands. **Denying binding does not close the BLE link or
block telemetry and settings reads.** Binding state and permission to
control power are separate. Some settings writes also lack those checks.

## Why reads still work

The V51 path is **confirmed in code**:

1. Main UI decline callback
   [`0x2483C`](v51/canonical/main/functions/0002483c_bind_decline_ui.c)
   clears the bind decision at `S+0x46` and pending flag at `S+0x47`, then
   schedules a reply. It does not change the remote grant at `S+0x42`.
2. [`0x12690`](v51/canonical/main/functions/00012690_build_bind_reply.c)
   turns that decision into `19 FF`. This reports denial, not a transport
   disconnect instruction.
3. BLE AF01 handler
   [`0x4224`](v51/canonical/ble/functions/ram_00004224_handle_af01_write.c)
   forwards ordinary commands through `0x4074`. It checks an update/busy
   state, but does not check the binding result or saved-host membership.
4. Main dispatcher
   [`0x12F34`](v51/canonical/main/functions/00012f34_dispatch_command.c)
   calls the read handlers without a common bind or remote-grant guard.
5. C2, C4 and E0 construct replies from state and identity data without
   consulting either permission byte.

Here `S = 0x1FFFAACC`. The deny decision is transient: transmit service
`0x133BC` clears it again after building the response. It is unsuitable
as a lasting authorization flag even apart from the missing read checks.

This is also **confirmed on hardware** for the previously captured
V1.6.0.40 unit: after `19 FF`, AF01 still returned C4, C2 and E0 replies.
See [the bind observations](../protocol.md#13-bluetooth-bind-handshake) and
the 2026-09-29 deny capture described in LOGBOOK. V51 was analyzed offline;
it was not installed or tested on the device in this pass.

## What is checked

| Operation | V51 behavior | Evidence boundary |
|---|---|---|
| BLE link and GATT availability | Remain usable for the observed post-denial reads | Hardware capture; no claim about all pairing/security configurations |
| Binding `18/19` | UI decision, pending host ID and optional saved-host lookup | Main and BLE code; not a common command gate |
| C2 telemetry | No bind/grant check on the traced path | Dispatcher and handler executed after denial |
| C4 settings read | No bind/grant check on the traced path | Dispatcher and handler executed after denial |
| E0 identity | No bind/grant check on the traced path | Dispatcher and type-6 builder executed after denial |
| C6 settings write | No bind/grant check on the traced path; valid request changes settings and sets dirty flag | Dispatcher and original handler executed in synthetic RAM after denial |
| C8, remote selector 1 | Requires the separate remote-control grant; returns C9 status 1 without it | Original dispatcher and handler executed after denial with grant zero |
| C8, remote selector 2 | Requests remote control; behavior also depends on connection type | Separate control-handler analysis, not a post-denial hardware test |
| E2, E8, EE | Shared remote-control pattern with mode-specific guards | Reviewed code; complete post-denial state combinations not executed |
| Other writes, update commands and internal commands | No blanket permission guarantee established | Full command-by-command audit remains open |

The new [34 offline checks](v51/canonical/verification/permission-emulation.json)
execute the denial callback, reply builder, main dispatcher and selected
handlers. UI rendering calls and WCH memory-library calls are substituted.
They also verify that AF01 forwards the five selected opcodes for BLE
connection-state values 0, 1 and 2. No command was sent to real hardware.

An additional check starts with a synthetic remote grant of 1. The decline
callback leaves it at 1. This proves the callback itself does not revoke
that grant; it does not prove that this state is naturally reachable during
a real connection sequence or that other disconnect paths preserve it.

## Bug or feature?

**Inferred assessment:** repeated absence of a read guard, combined with
explicit checks in power-control handlers, suggests that visibility and
control were designed as different mechanisms. That is stronger evidence
for a structural separation than for an accidental single missing check.
However, firmware cannot establish the vendor's intended privacy policy
or whether its UI wording accurately describes that policy.

- If the prompt means “approve this host/binding request,” continued reads
  can be compatible with that narrow behavior.
- If it promises “deny this device all access,” the implementation does
  not enforce that promise on the observed paths.
- C6 shows that the unchecked surface extends beyond observation. It is
  inaccurate to summarize the device as enforcing “reads allowed, all
  writes denied.”

The project already decided to disconnect after denial and offer no
post-denial monitoring mode: UR-008 and draft SR-010 record that decision
(LOGBOOK 2026-09-29, TBD-001). These firmware findings do not change it.
Link state, binding outcome and remote-control grant still need distinct
representation in the later approved detailed design.

The [capture audit](v51/canonical/verification/capture-audit.json) rechecks
raw frame lengths and records the first C5, C3 and E1 replies after denial
with their original timestamps. It does not modify the evidence captures.
