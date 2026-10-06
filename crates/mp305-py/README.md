# mp305

A Python library to control the ISDT MP305B bench power supply (0 to 30 V,
0 to 5 A, 150 W) over Bluetooth LE or USB. It is a thin, synchronous layer
on a Rust core that implements the device protocol.

The project is noncommercial. It is licensed under the GNU General Public
License v3.0 with the Commons Clause Condition v1.0.

## Installation

The library is not published to a package index yet. Build it from the
repository (Rust and [uv](https://docs.astral.sh/uv/) needed):

```sh
uv run maturin develop -m crates/mp305-py/Cargo.toml
```

Wheels are planned for GIL-enabled CPython 3.10 and later on macOS 13 and
later (arm64, x86_64), Linux manylinux_2_35 (x86_64, aarch64) and Windows 10
22H2 and later (x86_64). On macOS the first Bluetooth scan asks for the
Bluetooth permission of the terminal or app that runs Python.

The library uses the first Bluetooth adapter the operating system lists.
With more than one adapter, disable or unplug the others. On Linux `close`
takes two to three seconds over Bluetooth, because BlueZ waits 2 s before
it disconnects.

## Example

```python
import mp305

with mp305.Mp305.connect(max_voltage=12.0) as dev:  # one supply nearby
    print(dev.info.model, dev.info.version)
    dev.set_current_limit(0.1)  # A
    dev.set_voltage(5.0)  # V
    dev.output_on()
    for reading in mp305.stream(dev, rate=2.0, duration=5.0):
        print(reading.voltage, reading.current, reading.mode)
# Leaving the block switches the output off, releases remote control and
# disconnects, also when an exception is in flight. To leave the output on,
# call dev.close(output_off=False) as the last statement inside the block;
# the supply then keeps the output on with no host attached.
```

`mp305.discover()` lists the supplies in range; pass one `identifier` to
`Mp305.connect` when there are several. A supply on a USB cable is also seen
over Bluetooth until a USB host talks to it, so it can show up twice: pass
`bluetooth=False` (or `usb=False`) to `Mp305.connect` to choose the
transport. The library never picks between two entries. `mp305.to_csv()` records readings to
a CSV file and `mp305.ramp()` steps the voltage or the current limit. Over
Bluetooth the supply asks on its screen to confirm the first connection and
to allow remote control; pass `on_prompt` to be told while a call waits.

## Exceptions

Every exception derives from `mp305.Mp305Error`:

| Exception | When |
|---|---|
| `NotFoundError` | no supply was found, or several and no identifier was given |
| `ConnectionDeniedError` | the supply denied the connection |
| `RemoteControlDeniedError` | the supply denied remote control, or its prompt timed out |
| `RemoteControlLostError` | remote control is not held; request it again |
| `SetpointRangeError` | a value out of range (also a `ValueError`); nothing was sent |
| `CommandRejectedError` | the supply rejected a command (`status`, `reason`) |
| `ModeError` | the supply is not in DC mode |
| `FaultActiveError` | the supply reports a fault (`faults`) |
| `Mp305TimeoutError` | no reply or no new reading in time (also a `TimeoutError`) |
| `LinkLostError` | the link was lost or closed (also a `ConnectionError`) |

Ctrl-C raises `KeyboardInterrupt` within 0.5 s on the main thread. An
interrupted `output_off` or `close` finishes its sequence in the background,
and the process waits for it at exit.

## Bench safety for unattended runs

The software cannot switch the output off after a crash, so the bench
itself is the last line of defense:

- Set a hardware current limit and OCP mode on the supply's front panel.
- Keep only a safe load on the output.
- The supply keeps the output on when the link drops; only remote control is
  released.
- Prefer USB over Bluetooth for unattended runs.

A second Ctrl-C while `close` or `output_off` is finishing, or a killed
process, can leave the output on, and the next connect then warns. The
library cannot be used in a child process made by `os.fork()` after it
started, so `multiprocessing` needs the start method spawn or forkserver.
