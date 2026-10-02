"""Scenarios on the scripted mock that make `mp305-core` raise each `Error` variant.

IT-040 (each core error reaches its exception of SR-032) and IT-050 (every
variant, mapped as AR-050 says) share them. Each scenario takes the
identifier to connect with, runs through the public API, `mp305.testing`
and `Mp305._from_mock`, closes what it opened and returns the exception the
library raised. `VARIANTS` names them as AR-050 does, in its order, each
with a pattern of the core's text for that variant (`Display` in
`crates/mp305-core/src/error.rs`), which tells the variants apart.

`NotReady` is the one scenario below the public API: `connect` and
`_from_mock` return only once the session is ready, so a control call
before it cannot be made through `Mp305`. The scenario uses the native mock
session the test support exposes for this (DD-PY-031, DD-PY-034:
`_native.Session.from_mock` on the handles of a `testing.MockRecord`).
"""

from __future__ import annotations

import contextlib
import logging
import pathlib
import tempfile
import threading
import time
from collections.abc import Callable, Iterator
from typing import Any

from mp305 import EventKind, Mp305, _native, testing
from tests.unit.support import c3_reply, reply, script, silent, wait_until

_log = logging.getLogger("tests")

Scenario = Callable[[str], Exception]
"""Runs one scenario on the given identifier and returns what it raised."""

SR_005_CAUSES = (
    "the supply is off or out of range",
    "another app (WebLink in a browser, ISDT's Polying app) is connected to it",
    "a USB host is talking to it",
    "remote control is disabled on the supply",
)
"""The four causes of SR-005, in its order."""


def raised(call: Callable[[], object]) -> Exception:
    """The exception `call` raises; an `AssertionError` when it raises none."""
    try:
        result = call()
    except Exception as error:
        return error
    if isinstance(result, Mp305):
        result.close()
    raise AssertionError("the call raised nothing")


@contextlib.contextmanager
def opened(scripts: list[Any], identifier: str, **kwargs: Any) -> Iterator[Mp305]:
    """A mock device, closed afterwards; a close error is logged, not raised."""
    device = Mp305._from_mock(scripts, identifier=identifier, **kwargs)
    try:
        yield device
    finally:
        try:
            device.close()
        except Exception as error:
            _log.warning("close of %s failed: %s", identifier, error)


def not_found(identifier: str) -> Exception:
    """The connection attempt finds no supply (`discovery::not_found`)."""
    return raised(lambda: Mp305._from_mock([{"not_found": True}], identifier=identifier))


def connection_denied(identifier: str) -> Exception:
    """The fast bind and the prompt bind are both answered `19 FF`."""
    s = script(replies=[reply(0x18, b"\xff")])
    return raised(lambda: Mp305._from_mock([s], identifier=identifier))


def remote_control_denied(identifier: str) -> Exception:
    """The remote-control request is answered `C9 01`."""
    s = script(replies=[reply(0xC8, b"\x01", repeat=1), reply(0xC8, b"\x00")])
    with opened([s], identifier) as dev:
        return raised(lambda: dev.set_voltage(1.0))


def remote_control_lost(identifier: str) -> Exception:
    """The request is granted, the command is answered `C9 01`."""
    s = script(
        replies=[
            reply(0xC8, b"\x00", repeat=1),
            reply(0xC8, b"\x01", repeat=1),
            reply(0xC8, b"\x00"),
        ]
    )
    with opened([s], identifier) as dev:
        return raised(lambda: dev.set_voltage(1.0))


def setpoint_range(identifier: str) -> Exception:
    """`output_on` under a 12 V user limit while the reading's setpoint is 13.00 V.

    The Python layer checks only the values a caller names, so this is the
    core's own refusal of a command that would keep a copied setpoint above
    the user limit with the output on (AR-025).
    """
    with opened([script()], identifier, max_voltage=12.0) as dev:
        return raised(dev.output_on)


def command_rejected(identifier: str) -> Exception:
    """The request is granted, the command is answered `C9 FF`."""
    s = script(
        replies=[
            reply(0xC8, b"\x00", repeat=1),
            reply(0xC8, b"\xff", repeat=1),
            reply(0xC8, b"\x00"),
        ]
    )
    with opened([s], identifier) as dev:
        return raised(lambda: dev.set_voltage(1.0))


def mode(identifier: str) -> Exception:
    """The reading says PD mode (`model` 2); `set_voltage`."""
    s = script(replies=[c3_reply(testing.c3(model=2))])
    with opened([s], identifier) as dev:
        return raised(lambda: dev.set_voltage(1.0))


def fault_active(identifier: str) -> Exception:
    """The reading shows the over-current fault (bit 5); `output_on`."""
    s = script(replies=[c3_reply(testing.c3(charge_error=1 << 5))])
    with opened([s], identifier) as dev:
        return raised(dev.output_on)


def not_ready(identifier: str) -> Exception:
    """A control call on the native mock session before `ready` (see the module docstring)."""
    rec = testing.MockRecord()
    s = script(replies=[reply(0x18, b"\x00", after_s=0.3)])
    native = _native.Session.from_mock([s], None, False, None, None, identifier, rec.handles)
    try:
        return raised(lambda: native.set_voltage(1.0, None))
    finally:
        with contextlib.suppress(Exception):
            native.ready(None)
        native.close(True, None)


def timeout(identifier: str) -> Exception:
    """The request is granted, the command gets no reply."""
    s = script(
        replies=[
            reply(0xC8, b"\x00", repeat=1),
            silent(0xC8, repeat=1),
            reply(0xC8, b"\x00"),
        ]
    )
    with opened([s], identifier) as dev:
        return raised(lambda: dev.set_voltage(1.0))


def link_lost(identifier: str) -> Exception:
    """The mock closes the link at 0.3 s, reconnection off; a control call after `LINK_LOST`."""
    with opened([script(close_at_s=0.3)], identifier, reconnect=False) as dev:
        seen: list[EventKind] = []
        if not wait_until(
            lambda: seen.extend(e.kind for e in dev.events()) or EventKind.LINK_LOST in seen, 3.0
        ):
            raise AssertionError("no LINK_LOST event within 3 s")
        return raised(lambda: dev.set_voltage(1.0))


def transport(identifier: str) -> Exception:
    """The connection attempt fails in the transport."""
    return raised(lambda: Mp305._from_mock([{"error": "boom"}], identifier=identifier))


def store(identifier: str) -> Exception:
    """The state directory of the mock session lies below a regular file."""
    with tempfile.TemporaryDirectory() as directory:
        blocker = pathlib.Path(directory) / "file"
        blocker.write_text("x")
        return raised(
            lambda: Mp305._from_mock([script()], identifier=identifier, state_dir=blocker / "state")
        )


def protocol(identifier: str) -> Exception:
    """`0xE0` is answered with a 3-byte `0xE1` payload, too short to decode."""
    s = script(replies=[reply(0xE0, b"\x01\x06\x00")])
    return raised(lambda: Mp305._from_mock([s], identifier=identifier))


def already_open(identifier: str) -> Exception:
    """A second session to an identifier whose session is still open (AR-030)."""
    with opened([script()], identifier):
        return raised(lambda: Mp305._from_mock([script()], identifier=identifier))


def cancelled(identifier: str) -> Exception:
    """A `set_voltage` in progress on one thread while another switches the output off.

    The command waits at least 100 ms for a settled reading and then 300 ms
    for its reply, so it is still in progress when the output-off arrives
    0.1 s after the thread started.
    """
    s = script(replies=[reply(0xC8, b"\x00", repeat=1), reply(0xC8, b"\x00", after_s=0.3)])
    with opened([s], identifier) as dev:
        dev.request_remote_control()
        outcome: dict[str, Exception] = {}

        def call() -> None:
            try:
                dev.set_voltage(1.0)
            except Exception as error:
                outcome["error"] = error

        thread = threading.Thread(target=call)
        thread.start()
        time.sleep(0.1)
        dev.output_off()
        thread.join(5.0)
        if "error" not in outcome:
            raise AssertionError("set_voltage was not cancelled by the output-off")
        return outcome["error"]


VARIANTS: dict[str, tuple[Scenario, str]] = {
    "NotFound": (not_found, r"no supply found: .+"),
    "ConnectionDenied": (connection_denied, r"the supply denied the connection"),
    "RemoteControlDenied": (remote_control_denied, r"the supply denied remote control"),
    "RemoteControlLost": (remote_control_lost, r"remote control is not held; request it again"),
    "SetpointRange": (setpoint_range, r"voltage 13 is outside 0 to 12"),
    "CommandRejected": (
        command_rejected,
        r"the supply rejected the command \(status 0xff, busy\)",
    ),
    "Mode": (mode, r"the supply is not in DC mode \(mode 2\)"),
    "FaultActive": (fault_active, r"the supply reports a fault: over current"),
    "NotReady": (not_ready, r"the session is not ready for control"),
    "Timeout": (timeout, r"no reply to 0xc8 within 1\.0 s"),
    "LinkLost": (link_lost, r"link lost: .+"),
    "Transport": (transport, r"transport: boom"),
    "Store": (store, r"store: .+"),
    "Protocol": (protocol, r"protocol: .+"),
    "AlreadyOpen": (already_open, r"a session to \S+ is already open in this process"),
    "Cancelled": (cancelled, r"the command was cancelled: superseded by an output-off.*"),
}
"""Every `Error` variant of AR-050, in its order: the scenario and the text pattern."""
