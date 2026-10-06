# mp305b

Remote control for the ISDT MP305B portable bench power supply
(0 to 30 V, 0 to 5 A, 150 W), over Bluetooth LE or USB.

Repository: <https://github.com/jihlenburg/mp305-remote>. The name leaves
room for the MP305A later.

> Status: 0.1.0, the first release (2026-10-06). The Rust core, the desktop
> app and the Python library pass their unit and integration tests against
> a scripted mock of the supply on macOS, Linux and Windows, and the
> hands-on checks of [ADR-0019](docs/adr/0019-lean-first-release.md)
> passed on a real MP305B from macOS and from Linux (see "What was checked
> on a real supply"). Windows is not verified on hardware: there is no
> Windows test machine with a working path to the supply. The wheels of the
> Python library for macOS, Linux and Windows come out of the `wheels`
> workflow on the release tag; the desktop app is built from source
> (`scripts/bundle_macos.sh` on macOS). Nothing is on PyPI. See
> [TODO.md](TODO.md) and [LOGBOOK.md](LOGBOOK.md) for progress.

## What it is

- `mp305-app`, a desktop app for macOS, Linux and Windows to set voltage
  and current limit, switch the output, watch live readings on a chart and
  record them to CSV. It opens in the Retro theme, with Standard available
  in Details, and becomes a graph-free instrument panel at small window
  sizes, down to 320 by 320 points
  ([crates/mp305-app/README.md](crates/mp305-app/README.md)).
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

  A supply on a USB cable is also seen over Bluetooth until a USB host
  talks to it, and the library never picks between two entries. Pass
  `bluetooth=False` (or `usb=False`) to `connect` to choose the transport,
  or pass the identifier that `mp305.discover()` returned.

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

## What was checked on a real supply

Release 0.1.0 follows a short hands-on checklist
([ADR-0019](docs/adr/0019-lean-first-release.md)), not a full test
campaign. Everything below was done on one MP305B (firmware 1.6.0.51).
The supply's own readings are the reference; nothing was measured with a
second instrument.

Checked:

- The Python library from macOS, over Bluetooth and over USB, with
  `scripts/hardware_check.py`: find the supply, connect, read, set the
  voltage and the current limit, switch the output on, read at 2 per
  second, switch it off, put the old setpoints back, close. The loads were
  a 12 V lamp, once in constant current and once in constant voltage, and
  a 12 V module drawing 34 mA.
- The Python library from Linux (x86-64, Ubuntu 26.04, BlueZ 5.85, a USB
  Bluetooth adapter) over Bluetooth: the same script, and the part of the
  system tests that runs without a person at the supply (finding,
  connecting by identifier, 60 s of readings, streaming to CSV).
- The desktop app on macOS, over USB and over Bluetooth: connect, the
  remote-control prompt on the supply, set a limit, output on and off, the
  chart and a CSV recording.

Not checked:

- Windows on hardware. There is no Windows machine with a working path to
  the supply; on Windows the code has only run its tests against the mock.
- USB from Linux.
- The accuracy of the readings, load regulation, and the fault trips (over
  current, over voltage, over temperature).
- Automatic reconnection after a lost link, including a USB cable that
  was replugged, and the warning after an unclean exit.
- More than one supply at a time, and runs longer than a few minutes.
- The complete system and acceptance test specifications in
  `docs/v-model/`. They describe what could be verified and are a backlog,
  not a record of what was.

So treat 0.1.0 as an early release: set a hardware current limit on the
supply's front panel, and keep only a load on the output that is safe at
the supply's settings.

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
- USB: a HID device with vendor ID `0x28E9` and product ID `0x028A`,
  observed on the supply from macOS. No vendor driver is needed. On Linux
  a udev rule lets non-root users open the device. The
  [native app check](docs/v-model/records/2026-10-05-unit-app-retro-native.md)
  records the tested setup; it does not establish cross-platform USB coverage.
  The supply has no USB serial number, so its USB identifier is the device
  path, which changes when the cable is replugged or the supply is switched
  off and on. A running session with reconnection finds it again when it is
  the only MP305B on USB; with two of them on USB it does not reconnect by
  itself.

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
