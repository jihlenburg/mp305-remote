# mp305b

Remote control for the ISDT MP305B portable bench power supply
(0 to 30 V, 0 to 5 A, 150 W), over Bluetooth LE or USB.

Repository: <https://github.com/jihlenburg/mp305-remote>. The name leaves
room for the MP305A later.

> Status: implemented, not yet verified on the supply. The Rust core, the
> desktop app and the Python library exist and pass their unit and
> integration tests against a scripted mock of the supply. On a real
> MP305B only discovery has been tested so far; the system and acceptance
> tests on hardware are still to be run. Nothing is released: there are no
> published wheels or app binaries. See [TODO.md](TODO.md) and
> [LOGBOOK.md](LOGBOOK.md) for progress.

## What it is

- `mp305-app`, a desktop app for macOS, Linux and Windows to set voltage
  and current limit, switch the output, watch live readings on a chart and
  record them to CSV ([crates/mp305-app/README.md](crates/mp305-app/README.md)).
- `mp305`, a Python library for test scripts
  ([crates/mp305-py/README.md](crates/mp305-py/README.md)):

  ```python
  import mp305

  with mp305.Mp305.connect(max_voltage=12.0) as dev:  # one supply nearby
      dev.set_current_limit(0.1)  # A
      dev.set_voltage(5.0)  # V
      dev.output_on()
      for reading in mp305.stream(dev, rate=2.0, duration=5.0):
          print(reading.voltage, reading.current)
  # Leaving the block switches the output off, releases remote control and
  # disconnects, also when an exception is in flight.
  ```

Both sit on one Rust library, `mp305-core`, which implements the device
protocol, the two transports, and the rules for talking to the supply
safely (what may be sent, in which order, and what a lost link means).

## Building from source

Rust 1.95 or later (the app), Python 3.10 or later and
[uv](https://docs.astral.sh/uv/) are needed. On Linux also `pkg-config`,
`libdbus-1-dev` and `libudev-dev`.

```sh
cargo build --release -p mp305-app                      # the desktop app
uv run maturin develop -m crates/mp305-py/Cargo.toml    # the Python library
uv run --no-sync pytest                                 # its tests, on the mock
```

AGENTS.md lists the full set of commands. The tests need no hardware;
tests that use a real supply run only when asked for explicitly.

## How it talks to the device

ISDT does not document the protocol. The device firmware is the main source
of truth. Findings from the JavaScript of
[WebLink](https://www.isdt.co/weblink/), from a real unit, and from anywhere
else come on top of that firmware. Decompiling the device firmware is fully
allowed under Directive 2009/24/EC (2009/24/EG), so that the library and the
desktop app interoperate with the supply. There is no limit on the
information contained in that firmware, and the project uses it to its
fullest. The firmware image stays out of this repository. Interoperability
information reconstructed or gathered from it stays in the repository, in
whatever form it takes. In short:

- Bluetooth LE: the supply advertises a 29-character name starting with
  `0000MP305B` and the GATT service `0xAF00` (seen on the author's unit
  from macOS, Linux and Windows). The first time a host connects, the
  supply asks on its screen whether to allow the connection (seen from
  macOS), and according to the firmware it asks again before a host may
  control it.
- USB (from the firmware, not yet observed on hardware): a HID device with
  vendor ID `0x28E9` and product ID `0x028A`. No driver is needed. On
  Linux a udev rule lets non-root users open the device.

The library and the app use the first Bluetooth adapter the operating
system lists. With more than one adapter, disable or unplug the others: on
Linux an identifier names the adapter the supply was found through, so a
supply found through one adapter is not found through another. Closing a
Bluetooth connection takes two to three seconds on Linux, because BlueZ
waits 2 s before it disconnects.

[docs/research/device-model.md](docs/research/device-model.md) describes the
supply as a host sees it and says for every fact whether it comes from the
firmware or was seen on hardware. For the firmware itself, start with the
[readable firmware guide](docs/research/firmware/readable.md),
[hardware map](docs/research/device/hardware.md),
[RTOS resources](docs/research/firmware/rtos.md), or
[binding and permission analysis](docs/research/firmware/permissions.md).
The [verification record](docs/research/firmware/verification.md) states
what was checked and what remains unresolved.

## Documentation

- [AGENTS.md](AGENTS.md): working rules for contributors and AI agents
- [docs/v-model/](docs/v-model/): development process, requirements, design
  and test specifications
- [docs/adr/](docs/adr/): architecture decision records

## Safety

A bench power supply can damage whatever is connected to it. This software
can switch the output on and change its voltage. Check the setpoints before
you enable the output, and keep sensitive hardware disconnected while you try
things out.

## License

This project is strictly noncommercial. It is licensed under the **GNU General
Public License v3.0 with the Commons Clause Condition v1.0** (see [LICENSE](LICENSE)
and [ADR-0011](docs/adr/0011-licensing-gplv3-with-commons-clause.md)).

You may freely use, inspect, and modify the software for personal, educational,
research, and internal business operations (such as powering and testing DUTs on
an engineering bench). Selling the software, charging fees for distribution, or
offering paid commercial derivative products or services is strictly prohibited.

