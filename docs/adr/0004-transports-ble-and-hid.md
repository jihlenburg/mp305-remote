# ADR-0004: Support Bluetooth LE and USB HID, Bluetooth first

- Status: Accepted
- Date: 2026-09-29
- Decided by: user
- Related: ADR-0002, ADR-0003

## Context

The MP305B offers two data links: Bluetooth LE and USB HID over its USB-C
port. The user's unit normally runs from a USB power adapter, not from the
computer. Bluetooth works in that setup with no cable to the computer. USB
needs a cable to the computer, and a computer's USB-C port supplies much less
power than a proper USB PD adapter.

USB HID is the more predictable link for automation: no pairing, no range
limit, and no need for Bluetooth permission on macOS.

## Decision

Support both links behind one transport trait in `mp305-core`. Implement
Bluetooth LE first, using `btleplug`, then USB HID, using the `hidapi` crate.
The device API does not know which link it is using.

## Alternatives considered

- Bluetooth only, or USB only: smaller scope, but each rules out a real use.
  Bluetooth only makes long unattended test runs depend on a radio link. USB
  only makes the user rewire their setup.
- USB first: simpler to bring up, but it does not match how the user runs the
  unit today.

## Consequences

- Bluetooth on macOS needs permission. A binary started from Terminal
  inherits Terminal's permission. A `.app` bundle must declare
  `NSBluetoothAlwaysUsageDescription` in its Info.plist.
- The device asks for allow or deny on its screen at every Bluetooth
  connection (LOGBOOK 2026-09-29). Unattended Bluetooth reconnects are
  therefore impossible, and USB HID is the likely transport for unattended
  runs, pending a check whether USB shows the same prompt.
- Linux needs BlueZ, and access to hidraw devices may need a udev rule. The
  README will document both.
- Building on Linux needs pkg-config, libdbus-1-dev (`btleplug` uses the
  `dbus` crate) and libudev-dev (the default hidraw backend of `hidapi`). For
  manylinux wheels, evaluate the `vendored` feature of `dbus` and the
  `linux-native-basic-udev` feature of `hidapi`, which avoid these system
  libraries.
- Integration tests run each device-level scenario over both transports once
  both exist.
