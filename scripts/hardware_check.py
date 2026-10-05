"""Hands-on check of the library against a real MP305B.

Finds the supply, connects, reads, sets a voltage and a current limit,
switches the output on for a few seconds and off again, puts the old
setpoints back and closes. Prints one line per step and a summary.

    uv run --no-sync python scripts/hardware_check.py
    uv run --no-sync python scripts/hardware_check.py --usb
    uv run --no-sync python scripts/hardware_check.py --voltage 12 --seconds 10

The output is switched on. Connect only a load that may see the chosen
voltage and current. Defaults: 5 V, 0.1 A, 5 s. Over Bluetooth the supply
asks on its screen before it lets a host control it: press ALLOW there
when this script says so.
"""

from __future__ import annotations

import argparse
import sys
import time
from collections.abc import Callable

import mp305

STEPS: list[tuple[str, bool, str]] = []
"""The steps so far: name, whether it passed, and a note."""


def note(name: str, ok: bool, text: str = "") -> bool:
    """Prints and keeps the outcome of one step."""
    STEPS.append((name, ok, text))
    print(f"[{'ok' if ok else 'FAIL'}] {name}{': ' + text if text else ''}", flush=True)
    return ok


def on_prompt(event: mp305.Event) -> None:
    """Tells the person what the supply is asking."""
    print(f">>> On the supply: press ALLOW now ({event.text})", flush=True)


def wait_for(
    dev: mp305.Mp305, wanted: Callable[[mp305.Reading], bool], seconds: float
) -> mp305.Reading | None:
    """Reads until a reading satisfies `wanted`; None when none did in time."""
    end = time.monotonic() + seconds
    while time.monotonic() < end:
        reading = dev.read(timeout=2.0)
        if wanted(reading):
            return reading
    return None


def line(reading: mp305.Reading) -> str:
    """One reading as text."""
    return (
        f"{reading.voltage:6.2f} V  {reading.current:6.3f} A  {reading.power:6.2f} W  "
        f"set {reading.set_voltage:.2f} V / {reading.set_current:.3f} A  "
        f"output {'on' if reading.output_on else 'off'}  {reading.mode_text}"
    )


def find(args: argparse.Namespace) -> str | None:
    """The identifier of the one supply to use, or None."""
    if args.identifier:
        return str(args.identifier)
    found = mp305.discover(args.scan, bluetooth=not args.usb, usb=not args.ble)
    for supply in found:
        print(f"     found {supply.description}", flush=True)
    if len(found) != 1:
        hint = ""
        if sorted(f.transport for f in found) == ["ble", "hid"]:
            hint = (
                "; a supply on a USB cable is also seen over Bluetooth until a USB host"
                " talks to it, so pass --usb or --ble to choose a transport"
            )
        note(
            "find the supply",
            False,
            f"{len(found)} found; one expected (or pass --identifier){hint}",
        )
        return None
    signal = "" if found[0].rssi is None else f", signal {found[0].rssi} dBm"
    note("find the supply", True, f"{found[0].transport}{signal}")
    return found[0].identifier


def exercise(dev: mp305.Mp305, args: argparse.Namespace) -> None:
    """Reads, sets, switches on and off, and restores; notes each step."""
    info = dev.info
    note("connect", True, f"{dev.transport}, {info.model} {info.version} hardware {info.hardware}")
    first = dev.read(timeout=5.0)
    note("first reading", True, line(first))
    if first.live_mode is not mp305.LiveMode.DC:
        note("DC mode", False, f"the supply is in {first.live_mode.value} mode; select DC")
        return
    if first.output_on:
        note("output off at the start", False, "the output is on; switch it off and start again")
        return
    old = (first.set_voltage, first.set_current)

    dev.set_current_limit(args.current)
    dev.set_voltage(args.voltage)
    reading = wait_for(
        dev,
        lambda r: (
            abs(r.set_voltage - args.voltage) < 0.006 and abs(r.set_current - args.current) < 0.0006
        ),
        5.0,
    )
    note("set voltage and current limit", reading is not None, line(reading or dev.read()))

    if not args.no_output:
        dev.output_on()
        on = wait_for(dev, lambda r: r.output_on, 5.0)
        note("output on", on is not None, line(on or dev.read()))
        count = 0
        for reading in mp305.stream(dev, 2.0, duration=args.seconds):
            count += 1
            print(f"     {line(reading)}", flush=True)
        note("readings while on", count > 0, f"{count} in {args.seconds:g} s")
        dev.output_off()
        off = wait_for(dev, lambda r: not r.output_on, 5.0)
        note("output off", off is not None, line(off or dev.read()))

    dev.set_voltage(old[0])
    dev.set_current_limit(old[1])
    reading = wait_for(
        dev,
        lambda r: abs(r.set_voltage - old[0]) < 0.006 and abs(r.set_current - old[1]) < 0.0006,
        5.0,
    )
    note("old setpoints back", reading is not None, line(reading or dev.read()))


def main() -> int:
    """Runs the check and returns the process's exit code."""
    parser = argparse.ArgumentParser(description="Hands-on check of the library on a real MP305B.")
    which = parser.add_mutually_exclusive_group()
    which.add_argument("--ble", action="store_true", help="Bluetooth only")
    which.add_argument("--usb", action="store_true", help="USB only")
    parser.add_argument("--identifier", help="the supply's identifier, instead of a scan")
    parser.add_argument("--voltage", type=float, default=5.0, help="volts to set (default 5)")
    parser.add_argument("--current", type=float, default=0.1, help="amps to limit to (default 0.1)")
    parser.add_argument("--seconds", type=float, default=5.0, help="how long the output stays on")
    parser.add_argument("--scan", type=float, default=10.0, help="scan time in s")
    parser.add_argument("--no-output", action="store_true", help="never switch the output on")
    args = parser.parse_args()
    if not (0.0 < args.voltage <= 30.0 and 0.0 < args.current <= 5.0):
        parser.error("voltage must be within 0 to 30 V and current within 0 to 5 A")

    print(f"mp305 {mp305.__version__}: {args.voltage:g} V, {args.current:g} A", flush=True)
    try:
        identifier = find(args)
        if identifier is None:
            return 1
        # Leaving the block switches the output off, releases remote
        # control and disconnects, also after an error.
        with mp305.Mp305.connect(identifier, on_prompt=on_prompt) as dev:
            exercise(dev, args)
        note("close", True)
    except mp305.Mp305Error as error:
        note("the library reported", False, f"{type(error).__name__}: {error}")
    except KeyboardInterrupt:
        note("interrupted", False, "the library switches the output off on the way out")
    failed = [name for name, ok, _ in STEPS if not ok]
    print(
        f"\n{len(STEPS) - len(failed)} of {len(STEPS)} steps passed"
        + (f"; failed: {', '.join(failed)}" if failed else ""),
        flush=True,
    )
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
