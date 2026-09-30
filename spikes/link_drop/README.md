# Spike: what does the MP305B do with its output when the link drops?

Throwaway experiment (docs/v-model/README.md, "spikes"). Answers TBD-005 and,
as a byproduct, gives the first hardware evidence for TBD-012 (`0xC8` and
`0xC9` on hardware).

## Question

When the Bluetooth link drops while the output is on:

1. Does the supply keep the output on, or switch it off by itself?
2. Does it keep remote control, or release it?

The answer decides how much of hazard H-004 the software can be trusted to
mitigate. If the supply de-energizes on link loss, most of the residual risk
falls away. If it stays on, the unclean-exit warning (UR-030) and the
bench-safety note (UR-031) are the mitigations, and the software cannot do
better.

## Why this changes device state, and the safety bounds

To observe the answer the spike has to switch the output on first. It
therefore changes device state and needs the user's go-ahead in the current
session (AGENTS.md, "Spikes"). It holds to the HIL safety rules:

- Nothing is connected to the output. The spike says so and asks the user to
  confirm it.
- Setpoints are 5.00 V and 0.100 A. The command builder refuses anything
  above 6.00 V or 150 mA, any mode other than DC, and rejects a malformed
  reading.
- The output is switched off in a `finally` block, including on any error,
  before the script exits.
- The spike reconnects read-only after the drop only to observe; it re-acquires
  remote control solely to switch the output off.

## Run (only at the bench, nothing connected to the output)

    MP305_HIL=1 MP305_HIL_DEVICE=<the CoreBluetooth UUID> \
      uv run --with bleak python spikes/link_drop/spike.py

The script refuses to run unless both variables are set and the user types a
confirmation. Output: a JSONL capture under docs/research/captures/ and a
printed summary. Record the run in LOGBOOK.md and the answer in
docs/research/protocol.md.
