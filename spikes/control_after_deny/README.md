# Spike: does the MP305B grant remote control after a deny?

Throwaway experiment (docs/v-model/README.md, "spikes"). Answers TBD-002.

## Question

The supply answers read requests even after the user presses deny on the bind
prompt (LOGBOOK 2026-09-29, "Hardware: deny test", confirmed on hardware).
Open: does it also grant remote control to a host it denied?

WebLink acquires control by sending `0xC8` with `remoteCon = 2` (request
remote) and expecting `0xC9 = 0`. This spike sends that one request after a
deny and reads the reply:

- `0xC9 = 0`: the supply granted remote control although the user pressed
  deny. That is a gap in the supply's own protection, and the user may want
  to report it to ISDT.
- `0xC9 = 1` or anything else: the supply refused. The deny protects control
  as well as it should, and the residual part of hazard H-006 is smaller
  than feared.

Either way, the result tells the software how much to rely on the deny
(SR-010). The client refuses control after a deny and tells the user.

## Why it is safe

The single request the spike sends is built from a reading taken just before
it, so it carries the supply's current setpoints and mode unchanged, and the
command builder forces the output field to 0. It cannot switch the output on,
cannot change a setpoint, and cannot leave DC mode:

- Nothing is connected to the output. The spike asks the user to confirm it.
- The setpoints are copied from the reading unchanged, so the command changes
  no setting; the builder forces the output field to 0 and the mode to DC, and
  it caps the copied setpoint at the device maximum as a backstop against a
  garbage reading. Safety here rests on the output field being 0, not on a
  bench voltage or current cap (nothing is energized to cap).
- If the supply does grant control, the spike immediately releases it
  (`remoteCon = 0`) in a `finally` block. The output is never switched on, so
  there is nothing to switch off.
- The spike aborts if the user presses allow instead of deny, because the
  experiment needs a deny.

## Run (only at the bench, nothing connected to the output)

    MP305_HIL=1 MP305_HIL_DEVICE=<the CoreBluetooth UUID> \
      uv run --with bleak python spikes/control_after_deny/spike.py

The script refuses to run unless both variables are set and the user types a
confirmation. It then asks the user to press deny on the supply. Output: a
JSONL capture under docs/research/captures/ and a printed summary. Record the
run in LOGBOOK.md and the answer in docs/research/protocol.md.
