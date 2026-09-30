# 1. User requirements (UR)

Status: draft

The user requirements and the hazard list for the v1 remote control of the
ISDT MP305B bench power supply. The v1 scope was agreed in the conversation
of 2026-09-29 (TODO.md, "Agreed v1 scope"). Protocol facts cite
[docs/research/protocol.md](../research/protocol.md) and carry its evidence
labels.

"The software" means both products: the desktop app `mp305-app` and the
Python library `mp305`. "The supply" means the MP305B.

## 1. Hazards and functional safety (IEC 61508)

The MP305B delivers up to 30 V and 5 A (150 W) at its output. WebLink lets
the user enter up to 30.5 V and 5.1 A (confirmed in code). A wrong command,
setpoint corruption, a missed state change or a missed fault can destroy the
device under test (DUT) or start a fire, causing direct property damage and
indirectly human injury. Under ADR-0008, this software is treated as an
electrical safety-related system according to IEC 61508. Every hazard must be
systematically mitigated and verified.


| ID | Hazard | Cause | Severity | Mitigation |
|---|---|---|---|---|
| H-001 | The output switches on without the user asking for it. | `0xC8` carries the whole output state, including on or off. A command built from stale or default values switches the output (protocol.md 5.1, confirmed in code). | critical | UR-004, UR-005, UR-023; SR-019, SR-020, SR-021 (draft) |
| H-002 | Commands reach a different supply than the user meant. | The user's unit advertises the name `0000MP305B` followed by padding and a few characters of unknown meaning (confirmed on hardware); other units probably look the same (inferred). No serial number is readable over Bluetooth (protocol.md 4.4, confirmed on hardware). | critical | UR-002, UR-010; SR-001, SR-004 (draft) |
| H-003 | Voltage or current limit changes to a value the user did not choose. | The software sends remembered setpoints after a (re)connect, or a full-state `0xC8` undoes a change made on the front panel (protocol.md 5.1, confirmed in code). | high | UR-004, UR-023, UR-024; SR-019, SR-028 (draft) |
| H-004 | The output stays on after the software exits, crashes or loses the link. | WebLink sends nothing on disconnect, and what the supply does when the link drops is unknown (protocol.md 5.2, TBD-005). A crashed host cannot send anything. | high | UR-006, UR-018, UR-024, UR-030, UR-031; SR-022, SR-028, SR-029, SR-030, SR-046, SR-047 (draft). Mitigations chosen 2026-09-29: an unclean-exit warning (UR-030), a bench-safety note for unattended runs (UR-031) and the TBD-005 spike. Residual risk: a hard crash or a kill during a live output still cannot switch it off; UR-030 surfaces it on the next start. The TBD-005 spike establishes what the supply itself does on link loss. The user reviews what remains at G1 (TBD-015). |
| H-005 | The user reads or sets a value in the wrong unit or scale. | The protocol uses 10 mV, 1 mA and 10 mW steps (protocol.md 4.1, confirmed in code). | high | UR-003, UR-012, UR-017; SR-014, SR-024 (draft) |
| H-006 | Someone other than the person at the bench controls or watches the supply. | The supply answers read requests even after the bind is denied (protocol.md 1.3, confirmed on hardware). Whether it also accepts `0xC8` is unknown (TBD-002). | high | UR-008, UR-016; SR-006, SR-010 (draft). Mitigations chosen 2026-09-29: the TBD-002 spike establishes whether the supply enforces the bind before granting remote control. Until then the software refuses all control after a deny (SR-010). If the supply does not enforce it, that gap is in the device and the software cannot close it. The user reviews what remains at G1 (TBD-015). |
| H-007 | A setpoint exceeds what the DUT can take. | Typing error, or a script with a wrong value. | high | UR-007, UR-012; SR-024, SR-040 (draft) |
| H-008 | The output runs, or is switched on, while the supply reports a fault. | A protection trip (OCP, OVP, overheat, reversed output) goes unnoticed (protocol.md 4.5, confirmed in code). | critical | UR-009; SR-026, SR-027 (draft) |
| H-009 | The supply is left in its bootloader and unusable. | An interrupted firmware update: WebLink's update flow erases the application and has no timeout or abort (protocol.md 5.5, confirmed in code). | high | UR-025; SR-006 (draft) |

## 2. User requirements

### 2.1 Core control and monitoring

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| UR-001 | The software shall connect to an MP305B over Bluetooth LE and over USB HID. | user, conversation 2026-09-29; ADR-0004 | must | T | draft | The user's unit usually runs on a USB power adapter, so Bluetooth is the everyday link. USB HID is the candidate for unattended runs (TBD-004). |
| UR-002 | The software shall let the user choose the target supply explicitly, by an identifier that tells two supplies apart, and shall never pick a supply on its own when more than one is found. | user, conversation 2026-09-29 (v1 scope: connect); H-002 | must | T | draft | All units advertise the same name. Over Bluetooth the identifier is the one the OS assigns (for example the macOS CoreBluetooth UUID). A stable serial number is TBD-007. |
| UR-003 | The software shall take setpoints and show readings in volts, amperes and watts. | user, conversation 2026-09-29 (v1 scope: set voltage and current limit); H-005 | must | T | draft | Raw device units never reach the user. |
| UR-004 | After connecting, the software shall read the supply's setpoints, output state and fault state and show them before it allows any control action. | H-001, H-003 | must | D | draft | The user sees what the supply is doing before touching it. |
| UR-005 | The software shall switch the output on only when the user explicitly asks for it. Connecting, changing a setpoint, or starting a recording shall never switch the output on. | H-001 | must | D | draft | Output on is always a separate, deliberate action. |
| UR-006 | The software shall provide an output-off action that is available whenever the supply is connected, allowed and in DC mode, including after the supply has taken remote control away, and has the supply accept the output-off command within 0.5 s. In any other mode it shall tell the user to switch the output off on the supply. | H-004; user, conversation 2026-09-29 (0.5 s) | must | T | draft | The quick way to make the bench safe. The acknowledgment limit is 0.5 s, tighter than the 1 s that was proposed. How fast the output voltage then falls depends on the load, so the limit applies to the supply's acknowledgment. |
| UR-007 | The software shall let the user set a maximum voltage and a maximum current limit, and shall reject any setpoint above them without sending it to the supply. | H-007 | should | T | draft | A second guard for delicate DUTs. |
| UR-008 | Over Bluetooth, the software shall tell the user to confirm the connection on the supply's screen and wait for the answer. If the supply does not report the connection as allowed, the software shall report the refusal and disconnect, without reading or controlling anything. | H-006; LOGBOOK 2026-09-29, "Hardware: deny test"; user, conversation 2026-09-29 (TBD-001) | must | T | draft | The supply asks allow or deny at every connection (protocol.md 1.3, confirmed on hardware). There is no read-only mode after a deny. A deny means the person at the bench said no. Whether USB needs the same is TBD-004. How long the supply waits for an answer is TBD-008. |
| UR-009 | The software shall watch the supply's fault bits while connected, tell the user about every active fault as soon as it is reported, naming the fault, and refuse to switch the output on while any fault is active. | H-008 | must | T | draft | Faults such as OCP, OVP and overheat trip the output (protocol.md 4.5). How a trip shows in the readings is TBD-016. |
| UR-023 | When the user changes one setting (voltage, current limit or output state), the software shall leave every other setting as the supply currently reports it. | H-001, H-003 | must | T | draft | Protects changes made on the front panel. `0xC8` always carries all settings (protocol.md 5.1). |
| UR-024 | When the link to the supply is lost, the software shall tell the user at once that the output may still be on, and shall not reconnect or send any command until the user asks it to. | H-003, H-004 | must | D | draft | The supply's behavior on link loss is unknown (TBD-005). A Bluetooth reconnect needs a person at the supply anyway (UR-008), unless TBD-006 finds a way for the supply to remember a host. |
| UR-025 | The software shall not update the supply's firmware. | H-009 | must | I | draft | ISDT's WebLink and Polying do this. v1 stays out of the bootloader. |
| UR-026 | After connecting, the software shall show the supply's model, application version and hardware revision. | user, conversation 2026-09-29 (firmware update check); AGENTS.md, "Captures and firmware version" | should | D | draft | The versions come from `0xE1` (protocol.md 4.4, confirmed on hardware). Hardware test records must cite them. |
| UR-027 | When a search finds no supply, the software shall tell the user that the supply may be busy with another app, for example WebLink in a browser or ISDT's Polying app. | user, conversation 2026-09-29; LOGBOOK 2026-09-29, "Hardware: advertising test" | should | D | draft | A supply connected elsewhere is not found (protocol.md 1.2, inferred), which looks like a fault to the user. |

### 2.2 Desktop app (`mp305-app`)

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| UR-010 | The app shall list the supplies it finds with name, identifier and signal strength, and connect only to the one the user picks. | user, conversation 2026-09-29 (v1 scope); H-002 | must | D | draft | The app's form of UR-002. |
| UR-011 | The app shall show measured voltage, current and power, the setpoints, the output state and the regulation mode (CV or CC), updated at least twice per second. | user, conversation 2026-09-29 | must | D | draft | The Bluetooth poll cycle reached about 4.4 readings per second (LOGBOOK 2026-09-29, "Hardware: read-only Bluetooth LE spike"). |
| UR-012 | The app shall provide input fields for voltage and current limit that reject values outside the supply's setpoint range and outside the limits of UR-007. | user, conversation 2026-09-29 (v1 scope); H-005, H-007 | must | D | draft | The range the supply accepts is TBD-003. |
| UR-013 | The app shall show a scrolling chart of measured voltage, current and power over time. | user, conversation 2026-09-29 | must | D | draft | Part of the agreed v1 scope. |
| UR-014 | The app shall record readings to a CSV file that the user starts and stops. | user, conversation 2026-09-29 | must | D | draft | Part of the agreed v1 scope. |

### 2.3 Python library (`mp305`)

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| UR-015 | The library shall offer a synchronous API to find and connect to a supply, set voltage and current limit, switch the output, and read measurements. | ADR-0006, ADR-0007 (proposed) | must | T | draft | Lab scripts and notebooks read most naturally with blocking calls. ADR-0007 still needs the user's approval. |
| UR-016 | The library shall raise a distinct exception type for each of: a setpoint out of range, a denied connection, a command the supply rejects, a timeout, and a lost link. | ADR-0007 (proposed); H-006 | must | T | draft | A script can then react to each case, for example stop a test run cleanly. |
| UR-017 | The library shall return each reading as a typed object with voltage, current and power in V, A and W as floats, plus output state, regulation mode and active faults. | user, conversation 2026-09-29 (v1 scope: read voltage, current, power, CV/CC); H-005, H-008 | must | T | draft | Scripts compare and log values without knowing the protocol's raw units. |
| UR-018 | The library shall provide a context manager that switches the output off and releases remote control when the block ends, also when it ends with an exception. | H-004 | should | T | draft | A crashing script still leaves the bench safe, as long as the Python process itself survives. |
| UR-028 | The library shall stream readings at a rate the user chooses and write them to a CSV file with a helper. | user, conversation 2026-09-29 (v1 scope) | must | T | draft | The library gets streaming and CSV logging but no chart. |
| UR-029 | The library shall provide a helper that ramps the voltage or the current limit from a start value to an end value in steps, driven from the host. | user, conversation 2026-09-29 (v1 scope, nice to have) | could | T | draft | The supply's own program mode is out of v1 scope. |
| UR-030 | While the software holds remote control with the output reported on, it shall keep a persistent marker naming the supply and the time. On its next start, before any control action, it shall warn the user if a marker for the supply being connected shows a previous session that did not end with the output switched off. | H-004; user, conversation 2026-09-29 (TBD-015) | should | T | draft | A crash or a lost link can leave the output on with nobody told. The marker turns a silent stuck-on output into a warning the next time the user connects. It does not switch the output off by itself, so it is a warning, not a guarantee. Verification is T, not D as in the analogous UR-024: the marker and the warning are testable through the library's exposed state (ST-041), while the app side is demonstrated (AT-030). |
| UR-031 | The user documentation of the app and the library shall carry a bench-safety note for unattended runs: set a hardware current limit and OCP mode on the front panel, keep only a safe load on the output, and prefer USB HID over Bluetooth, since a dropped Bluetooth link cannot be reconnected without a person at the supply. | H-004; user, conversation 2026-09-29 (TBD-015) | should | I | draft | The software cannot switch the output off after a crash, so the last line of defense is how the bench itself is set up. Written guidance is the honest mitigation for a risk the software cannot remove. |

### 2.4 Design constraints

| ID | Requirement | Parent or source | Priority | Verification | Status | Rationale |
|---|---|---|---|---|---|---|
| UR-019 | The protocol, the transports and the device API shall be implemented once, in the Rust crate `mp305-core`, and used by both products. | ADR-0003 | must | I | draft | One protocol implementation for both products. |
| UR-020 | The desktop app shall be written in Rust with egui and run on macOS, Linux and Windows. | ADR-0005 | must | I | draft | Settled constraint. |
| UR-021 | The Python library shall be built on `mp305-core` with PyO3. | ADR-0006 | must | I | draft | Settled constraint. |

## 3. Open points

The user accepts this list explicitly at G1. Each point has a TODO item.

| ID | Open point | Affects | How it gets settled |
|---|---|---|---|
| TBD-001 | After a denied bind, does the software offer read-only monitoring, or refuse the connection entirely? | UR-008, H-006 | Settled 2026-09-29: refuse and disconnect. |
| TBD-002 | Does the supply accept `0xC8` without a successful bind? | H-006, UR-008 | Spike, only with the user's explicit approval; a positive result may be reported to ISDT |
| TBD-003 | Which voltage and current setpoints does the supply accept in DC mode? Image 1.6.0.51 rejects a `0xC8` above 30.50 V and 5.100 A (firmware.md). The rated numbers are 30.0 V and 5.0 A. What the output does at the top of the firmware range is still open. | UR-012 | Spike with the user's approval |
| TBD-004 | Does USB HID need a confirmation on the supply, like Bluetooth? | UR-001, UR-008 | Spike over USB |
| TBD-005 | What does the supply do with the output and with remote control when the link drops? | H-004, UR-024 | Spike with the user's approval, nothing on the output |
| TBD-006 | Can a host be remembered (`fastBinding = 1` or a host-specific ID), so that a Bluetooth reconnect needs no confirmation? | UR-008, UR-024 | Spike with the user's approval (sends a bind frame WebLink never sends) |
| TBD-007 | Is a unique serial number readable over USB HID (`0xE1` device ID field)? | UR-002 | Spike over USB |
| TBD-008 | How long does the supply wait for allow or deny, and what does it reply when nobody presses a button? | UR-008 | Spike over Bluetooth |
| TBD-009 | Which machines (Linux, Windows) are available for acceptance runs on hardware? | 8-acceptance-tests.md coverage table | Settled 2026-09-29: only the Mac. Linux and Windows have no hardware coverage. That gap is accepted or rejected at G1. |
| TBD-016 | How an over-current trip shows in `0xC3`: `chargeError` bit 5, the output switching off, or both. The OCP delay of 50 ms decoded from `0xC5` is also unchecked. | UR-009, H-008, AT-009 | HIL test with the user's approval (AT-009 setup), and a check of the settings menu |
| TBD-015 | The residual risk of H-004 and H-006 that remains after the chosen mitigations. | H-004, H-006 | Mitigations chosen 2026-09-29 (H-004: UR-030, UR-031, TBD-005 spike; H-006: TBD-002 spike). The residual risk is re-assessed and accepted or rejected at G1, after the spikes have run. |

## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-09-29 | Initial draft of user requirements and hazard list for G1 | not yet approved |
| 2 | 2026-09-29 | Fixed the hazard mitigation column, which named unrelated URs. Rewrote UR-002, UR-006, UR-008, UR-009, UR-011 to UR-013 and UR-016 to UR-018 so that they are testable and match the hardware findings (bind prompt at every connection, reads after a deny, no serial over Bluetooth). Added H-009, UR-023 to UR-029 (including the Python streaming and CSV helper and the ramp helper from the v1 scope) and the TBD list. | not yet approved |
| 3 | 2026-09-29 | Settled points: TBD-001 (refuse and disconnect after a deny, UR-008), UR-006 tightened to 0.5 s, TBD-009 (Mac only), residual risks of H-004 and H-006 not accepted (new TBD-015). | not yet approved |
| 4 | 2026-09-29 | Independent review findings: UR-009 refuses output on during a fault (H-008 was only partly mitigated); UR-006 limited to allowed DC connections; hazard mitigations list the draft SRs; H-002 evidence relabeled; UR parents name a user source; rationales filled in; TBD-016 added. | not yet approved |
| 5 | 2026-09-29 | TBD-015 mitigations: UR-030 (unclean-exit warning) and UR-031 (bench-safety note) added, H-004 and H-006 mitigation columns updated, TBD-015 reframed as the residual risk decided at G1. | not yet approved |
| 6 | 2026-09-29 | UR-022 withdrawn. H-006 and TBD-015 no longer name a firmware-image check. | not yet approved |
| 7 | 2026-09-30 | Editorial: rationales and settled TBD notes state the decision directly. No requirement text changed. | not yet approved |
