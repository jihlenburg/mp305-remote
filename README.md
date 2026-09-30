# mp305b

Remote control for the ISDT MP305B portable bench power supply
(0 to 30 V, 0 to 5 A, 150 W), over Bluetooth LE or USB.

Repository: <https://github.com/jihlenburg/mp305-remote>. The name leaves
room for the MP305A later.

> Status: design phase. Nothing is ready to install yet. The project follows
> a V-model process, and the user requirements are being written now. See
> [TODO.md](TODO.md) and [LOGBOOK.md](LOGBOOK.md) for progress.

## What it will be

- A desktop app for macOS, Linux and Windows to set voltage and current,
  switch the output, watch live readings on a chart, and record them to CSV.
- A Python library for test scripts:

  ```python
  # Planned API, subject to the design review
  from mp305 import Mp305

  psu = Mp305.connect()
  psu.set_voltage(5.0)
  psu.set_current(0.5)
  psu.output(True)
  print(psu.measure())
  ```

Both sit on one Rust library, `mp305-core`, which implements the device
protocol and the two transports.

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
whatever form it takes. So far:

- Bluetooth LE (confirmed on the author's unit): the supply advertises a name
  starting with `0000MP30` and GATT service `0xAF00`. Each time a host
  connects, the supply asks on its screen whether to allow the connection.
- USB (not yet checked on hardware): WebLink looks for a HID device with
  vendor ID `0x28E9` or HID usage page 1 / usage 4. No driver is needed. On
  Linux, a udev rule may be needed so that non-root users can open the device.

Start with the [readable firmware guide](docs/research/firmware/readable.md),
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

