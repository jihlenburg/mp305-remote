# Spike: a nameplate in a program slot

Throwaway experiment (see [docs/v-model/README.md](../../docs/v-model/README.md)).
Production code never imports this code and never copies it. The
documentation, lint and coverage rules do not apply here.

## Question

The supply has no serial number a host can read, so one unit cannot be
recognised over USB and over Bluetooth, or after a replug. Its programs
have 16-byte names in nonvolatile storage, and the firmware notes say the
program list (`D4`) is a plain read and the header write (`D6`) takes a
name, a step count and a save flag. Can a host write a program header
with a name and no steps, and read that name back over both transports
and after a power cycle, so that the name serves as a nameplate?

## How to run

```sh
uv run --no-sync --with bleak python spikes/program_nameplate/spike.py
uv run --no-sync --with bleak python spikes/program_nameplate/spike.py --write "mp305 7F3A"
uv run --no-sync --with bleak python spikes/program_nameplate/spike.py --delete 2
uv run --no-sync --with bleak --with hidapi python spikes/program_nameplate/spike.py --usb
```

Without options the script reads `DC` and `D4` over Bluetooth and writes
nothing. `--write` adds a header with the next contiguous id, `--delete`
removes one, `--usb` reads the same two commands over USB HID. Every frame
is on an allow-list in the script. The supply must be on with remote
control enabled and nothing else connected; a header write switches the
supply's output request off. Each run writes a capture to
`docs/research/captures/`. Use `--no-sync`, or uv reinstalls the cached
Python extension over the one `maturin develop` built.

## Answer (2026-10-06, MP305B 1.6.0.51, the user's unit)

Yes.

- `D4` over Bluetooth (`12 D4` on AF01) answered `31 D5 01`, then the one
  program: `Test1`, padded with one zero byte and `FF` bytes to 16, and its
  step count 6. `DC` answered `31 DD 01 06`.
- `D6` with id 2, the name `mp305 7F3A` padded with zero bytes, 0 steps,
  save 1, op 0 (`12 D6 02 6D 70 33 30 35 20 37 46 33 41 00 00 00 00 00 00
  00 01 00`) answered `31 D7 00` after 90 ms. `D4` right after listed the
  new program as id 2 with 0 steps; the selected program stayed id 1.
- The user switched the supply off and on: `D4` still lists it, and the
  supply shows it in its program menu.
- Over USB (`AA 12 01 D4 E7` in report 1) the reply `AA 21 24 D5 02 ...`
  carries the same two programs with the same bytes.

Captures: `2026-10-06T020651-program-nameplate.jsonl` (the first read),
`2026-10-06T020733-program-nameplate.jsonl` (the write),
`2026-10-06T020902-program-nameplate.jsonl` (after the power cycle),
`2026-10-06T020948-program-nameplate-usb.jsonl` (USB). The frames match
the firmware notes (`docs/research/firmware/v51/independent/notes/commands.md`,
5.10, 5.11, 5.14) byte for byte.

- The user ran `--delete 2`: `12 D6 02` with 16 zero bytes, `00 01 01`
  answered `31 D7 00` after 90 ms, and `D4` listed the one program `Test1`
  again (`2026-10-06T021310-program-nameplate.jsonl`).

Not tried: a rejected write (an id above 10), and whether the host can
switch the output on afterwards (the write clears the busy flag on paper,
since `save` was 1 and `op` was 0).
