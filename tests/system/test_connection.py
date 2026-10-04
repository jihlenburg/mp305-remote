"""ST-006 to ST-011, ST-043 to ST-045: connecting, binding and the host ID.

SR-006 to SR-011 and SR-048 to SR-050. The Bluetooth entries that need the
bind prompt connect with `fresh_state_dir`, a new host ID the supply does not
recognise; the others use the default state directory (the remembered-host
path). ST-007 and ST-010 use the two-step native connect of DD-PY-031,
because after a failed `Mp305.connect` no object is left to call; it is the
installed library's own test hook (`mp305._native.Session.connect` and
`ready`).
"""

from __future__ import annotations

import logging
import pathlib
import re
import shutil
import time
from collections.abc import Callable
from typing import TYPE_CHECKING

import pytest

import mp305
from mp305 import ConnectionDeniedError, Event, EventKind, Mp305Error, Mp305TimeoutError
from tests.system.support import (
    AF01_UUID,
    AF02_UUID,
    CONFIRM_TEXT,
    USB_HOST_HINT,
    WEBLINK_HOST_ID,
    FrameLog,
    run_child,
    wait_until,
)

if TYPE_CHECKING:
    from tests.system.conftest import Guard, OptIns, Person, Unit


def _bind_flag(payload: bytes) -> int:
    """The fast flag of a bind payload: the last of its 18 bytes."""
    return payload[-1]


@pytest.mark.hil
@pytest.mark.spec("ST-006")
def test_st006_a_full_session_sends_only_the_four_requests(
    hil_unit: Unit, controls: Person, supply: Guard, frame_log: FrameLog
) -> None:
    """Step 1: connect, read, 5 V and 0.1 A, output on and off, close; nothing connected.

    Step 2 (inspect the allowlist and the never-send list of the transport)
    is an inspection of `mp305-core`'s `protocol::policy`, which the
    library does not expose; it is not part of this test.
    """
    dev = supply.connect()
    dev.read()
    dev.set_voltage(5.0)
    dev.set_current_limit(0.1)
    dev.output_on()
    dev.read()
    dev.output_off()
    dev.close()
    frame_log.settle()
    sent = frame_log.sent()
    assert sent
    assert {f.opcode for f in sent} <= {0x18, 0xE0, 0xC2, 0xC8}


@pytest.mark.hil
@pytest.mark.spec("ST-007")
def test_st007_a_denied_bind_closes_the_link(
    ble_unit: Unit,
    person: Person,
    supply: Guard,
    fresh_state_dir: pathlib.Path,
    frame_log: FrameLog,
) -> None:
    """Fresh host ID; the person presses deny; then `set_voltage(1.0)`."""
    host = mp305.host_id(fresh_state_dir)

    def on_prompt(event: Event) -> None:
        if event.prompt == "confirm_connection":
            person.say("The supply asks to confirm the connection: press DENY now.")

    native = supply.native_connect(fresh_state_dir)
    with pytest.raises(ConnectionDeniedError):
        native.ready(supply.native_dispatch(on_prompt))
    state = native.link_state()
    with pytest.raises(Mp305Error):
        native.set_voltage(1.0, None)
    frame_log.settle()
    # The link is closed: the connection ended denied.
    assert state == "denied"
    sent = frame_log.sent()
    assert [(f.route, f.opcode, f.payload) for f in sent] == [
        ("ble AF02", 0x18, host + b"\x00\x01"),
        ("ble AF02", 0x18, host + b"\x00\x00"),
    ]
    replies = frame_log.received(0x19)
    assert [f.payload for f in replies] == [b"\xff", b"\xff"]
    last = replies[-1]
    assert [f for f in sent if f.index > last.index] == []


@pytest.mark.hil
@pytest.mark.spec("ST-008")
def test_st008_the_bind_follows_the_notifications_and_the_mtu(
    ble_unit: Unit,
    person: Person,
    supply: Guard,
    fresh_state_dir: pathlib.Path,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Fresh host ID, the frame log on; the person presses allow.

    The frame log has no line of its own for the subscription to the two
    characteristics (DD-TRANS-010 subscribes without logging); the test
    takes the notifications that arrived on both as the evidence that both
    were enabled.
    """
    host = mp305.host_id(fresh_state_dir)
    supply.connect(state_dir=fresh_state_dir)
    frame_log.settle()
    mtus = frame_log.mtu()
    assert mtus, "no negotiated MTU in the frame log"
    mtu_index, mtu = mtus[0]
    observe("mtu", mtu)
    assert mtu >= 74
    sent = frame_log.sent()
    received = frame_log.received()
    # Notifications enabled on both characteristics.
    assert any(f.route == "ble AF01" for f in received)
    assert any(f.route == "ble AF02" for f in received)
    # Then the bind frame on AF02: 0x18, the stored host ID, 00, the flag.
    binds = [f for f in sent if f.opcode == 0x18]
    assert binds
    assert sent[0] == binds[0]
    assert mtu_index < binds[0].index
    for bind in binds:
        assert bind.route == "ble AF02"
        assert len(bind.payload) == 18
        assert bind.payload[:16] == host
        assert bind.payload[16] == 0
        assert _bind_flag(bind.payload) in (0, 1)
    wire_binds = [w for w in frame_log.wire() if w.direction == "tx" and w.data[:1] == b"\x18"]
    assert wire_binds
    assert all(w.characteristic == AF02_UUID for w in wire_binds)
    # No AF01 write before the 19 00 reply.
    allowed = [f for f in frame_log.received(0x19) if f.payload == b"\x00"]
    assert allowed
    assert [f for f in sent if f.route == "ble AF01" and f.index < allowed[0].index] == []
    assert [
        w
        for w in frame_log.wire()
        if w.direction == "tx" and w.characteristic == AF01_UUID and w.index < allowed[0].index
    ] == []


@pytest.mark.hil
@pytest.mark.spec("ST-009")
def test_st009_the_prompt_reaches_the_callback_and_logging_before_the_reply(
    ble_unit: Unit,
    person: Person,
    supply: Guard,
    fresh_state_dir: pathlib.Path,
    frame_log: FrameLog,
) -> None:
    """Fresh host ID, a callback and a log handler; the person waits 5 s, then presses allow."""
    calls: list[tuple[float, Event]] = []

    def on_prompt(event: Event) -> None:
        calls.append((time.time(), event))
        if event.prompt == "confirm_connection":
            person.say("The supply asks to confirm the connection. Do not press yet; wait 5 s.")
            person.countdown(5, "Press ALLOW now.")
        else:
            supply.default_prompt(event)

    supply.connect(state_dir=fresh_state_dir, on_prompt=on_prompt)
    frame_log.settle()
    prompts = [(t, e) for t, e in calls if e.prompt == "confirm_connection"]
    assert len(prompts) == 1
    called_at, event = prompts[0]
    assert event.kind is EventKind.PROMPT
    assert event.bound_s == 30
    assert event.text == CONFIRM_TEXT
    warnings = [
        r for r in frame_log.messages("mp305", logging.WARNING) if r.getMessage() == CONFIRM_TEXT
    ]
    assert len(warnings) == 1
    reply = [f for f in frame_log.received(0x19) if f.payload == b"\x00"][0]
    assert warnings[0].created < reply.created
    assert called_at < reply.created


@pytest.mark.hil
@pytest.mark.spec("ST-010")
def test_st010_the_bind_times_out_after_30_s(
    ble_unit: Unit,
    person: Person,
    supply: Guard,
    fresh_state_dir: pathlib.Path,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Fresh host ID; nobody presses anything. The time and any late `19 FF` settle TBD-008."""
    person.say(
        "The supply will ask to confirm the connection: do NOT press anything. "
        "The test waits about 30 s."
    )
    native = supply.native_connect(fresh_state_dir)
    error: Exception | None = None
    try:
        native.ready(supply.native_dispatch(lambda event: None))
    except Mp305Error as raised:
        error = raised
    failed_at = time.time()
    state = native.link_state()
    frame_log.settle(2.0)
    mtus = frame_log.mtu()
    records = frame_log.snapshot()
    connected_at = records[mtus[0][0]].created if mtus else frame_log.sent()[0].created
    closed = [r.created - connected_at for r in frame_log.link_closed()]
    prompt_binds = [f for f in frame_log.sent(0x18) if _bind_flag(f.payload) == 0]
    late = [
        f.created - connected_at
        for f in frame_log.received(0x19)
        if prompt_binds and f.index > prompt_binds[0].index
    ]
    observe("seconds_to_error", round(failed_at - connected_at, 3))
    observe("error", f"{type(error).__name__}: {error}")
    observe("link_closed_after_s", [round(c, 3) for c in closed])
    observe("disconnect_reported_before_error", any(c < failed_at - connected_at for c in closed))
    observe("replies_to_the_prompt_bind_after_s", [round(x, 3) for x in late])
    assert isinstance(error, Mp305TimeoutError), error
    assert re.search(r"\b30(\.0)? s\b", str(error)), str(error)
    assert failed_at - connected_at <= 31.0
    # The link is closed: the connection ended lost, not ready.
    assert state in ("lost", "closed")


@pytest.mark.hil
@pytest.mark.spec("ST-011")
def test_st011_usb_connects_without_a_bind(
    hid_unit: Unit,
    person: Person,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Over USB with the frame log on; the person watches the screen (TBD-004)."""
    person.say("Watch the supply's screen while the test connects over USB.")
    supply.connect()
    frame_log.settle()
    shown = person.ask("Did the supply show a prompt while the test connected?")
    observe("prompt_shown", shown)
    assert frame_log.sent(0x18) == []
    e1 = frame_log.received(0xE1)
    assert e1
    records = frame_log.snapshot()
    allowed = [
        i
        for i, r in enumerate(records)
        if r.name == "mp305.core.session" and r.getMessage().endswith("-> allowed")
    ]
    assert allowed, "no transition to allowed in the log"
    assert allowed[0] > e1[0].index


@pytest.mark.hil
@pytest.mark.spec("ST-043")
def test_st043_step1_a_usb_host_silences_the_bluetooth_session(
    ble_unit: Unit,
    opt_ins: OptIns,
    supply: Guard,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Step 1: a Bluetooth session streams while a second process connects over USB.

    The same unit's HID path comes from `MP305_HIL_DEVICE_HID`. The
    Bluetooth session has automatic reconnection on (SR-055), since a link
    the supply silences for 8 s ends after three unanswered polls and
    "recovers" can only mean a reconnection.
    """
    if opt_ins.device_hid is None:
        pytest.skip(
            "step 1 needs the same unit over USB too; set MP305_HIL_DEVICE_HID to its HID path"
        )
    dev = supply.connect(reconnect=True)
    dev.read()
    started = time.time()
    report, proc = run_child(
        """
        ident = os.environ["MP305_ST043_HID"]
        with Mp305.connect(ident, max_voltage=5.0, max_current=0.1) as usb:
            reading = usb.read()
            report(transport=usb.transport, read=reading is not None)
        """,
        env={"MP305_ST043_HID": opt_ins.device_hid},
        timeout=60.0,
    )
    closed_at = time.time()
    assert proc.returncode == 0, proc.stderr
    assert report == {"transport": "hid", "read": True}

    def recovered() -> bool:
        reading = dev.reading
        return (
            dev.link_state == "ready"
            and reading is not None
            and reading.wall_ns > int(closed_at * 1e9)
        )

    back = wait_until(recovered, 35.0, step=0.1)
    back_at = time.time()
    frame_log.settle()
    hints = [
        r
        for r in frame_log.messages("mp305", logging.WARNING)
        if USB_HOST_HINT in r.getMessage() and r.created >= started
    ]
    observe("usb_process_s", round(closed_at - started, 3))
    observe("hints", [r.getMessage() for r in hints])
    observe("recovered_after_s", round(back_at - closed_at, 3) if back else None)
    # The Bluetooth session reports the USB host.
    assert hints
    # It recovers within 30 s after the USB process closed.
    assert back
    assert back_at - closed_at <= 30.0


@pytest.mark.hil
@pytest.mark.spec("ST-043")
def test_st043_step2_a_second_connection_names_the_open_one(hil_unit: Unit, supply: Guard) -> None:
    """Step 2: a second connection to the same supply from this process."""
    dev = supply.connect()
    with pytest.raises(Mp305Error) as info:
        supply.connect()
    assert dev.identifier in str(info.value)


@pytest.mark.spec("ST-044")
def test_st044_the_host_id_per_state_directory(tmp_path: pathlib.Path) -> None:
    """Steps 1 and 2 without a supply, each read in a new process (a library start)."""
    first = tmp_path / "first"
    second = tmp_path / "second"
    code = 'report(id=mp305.host_id(os.environ["MP305_ST044_DIR"]).hex())'

    def start_and_read(directory: pathlib.Path) -> bytes:
        report, proc = run_child(code, env={"MP305_ST044_DIR": str(directory)}, timeout=60.0)
        assert proc.returncode == 0, proc.stderr
        return bytes.fromhex(report["id"])

    # Step 1: delete the state directory, start, read, restart, read.
    shutil.rmtree(first, ignore_errors=True)
    once = start_and_read(first)
    again = start_and_read(first)
    # Step 2: a second state directory.
    other = start_and_read(second)
    assert len(once) == 16
    assert once != bytes(16)
    assert once != WEBLINK_HOST_ID
    assert again == once
    assert other != once


@pytest.mark.hil
@pytest.mark.spec("ST-045")
def test_st045_a_remembered_host_binds_without_a_prompt(
    ble_unit: Unit,
    person: Person,
    supply: Guard,
    fresh_state_dir: pathlib.Path,
    frame_log: FrameLog,
    observe: Callable[[str, object], None],
) -> None:
    """Steps 1 to 3; the result settles TBD-006.

    Step 1 needs the prompt, so it starts from a fresh state directory; step
    2 is the remembered-host path with that same host ID. Step 3 asks the
    person to press deny, so that the third host ID does not
    take one of the five places the supply keeps (device-model.md 3); either
    answer shows the prompt.
    """
    host = mp305.host_id(fresh_state_dir)

    # Step 1: fresh host ID; the person presses allow; disconnect.
    first = frame_log.mark()
    dev = supply.connect(state_dir=fresh_state_dir)
    dev.close()
    frame_log.settle()
    step1 = [(f.direction, f.payload) for f in frame_log.frames(first) if f.route == "ble AF02"]
    observe("step1", [(d, p.hex()) for d, p in step1])
    assert step1[:4] == [
        ("tx", host + b"\x00\x01"),
        ("rx", b"\xff"),
        ("tx", host + b"\x00\x00"),
        ("rx", b"\x00"),
    ]

    # Step 2: the same ID again; the person watches the screen.
    second = frame_log.mark()
    prompts: list[Event] = []

    def unexpected(event: Event) -> None:
        prompts.append(event)
        person.say("A prompt appeared, which this step does not expect: press DENY now.")

    person.say("Watch the supply's screen: the test connects again with the same host ID.")
    dev = supply.connect(state_dir=fresh_state_dir, on_prompt=unexpected)
    events = dev.events()
    dev.close()
    frame_log.settle()
    shown = person.ask("Did the supply show a prompt just now?")
    step2 = [(f.direction, f.payload) for f in frame_log.frames(second) if f.route == "ble AF02"]
    observe("step2", [(d, p.hex()) for d, p in step2])
    observe("step2_prompt_shown", shown)
    assert step2[:2] == [("tx", host + b"\x00\x01"), ("rx", b"\x00")]
    assert prompts == []
    assert not shown
    binds = [e for e in events if e.kind is EventKind.BIND_RESULT]
    assert [e.recognised for e in binds] == [True]
    assert "bind: host recognised" in frame_log.texts("mp305", logging.INFO)

    # Step 3: delete the ID, connect again.
    shutil.rmtree(fresh_state_dir)
    third = frame_log.mark()
    seen: list[Event] = []

    def on_prompt(event: Event) -> None:
        seen.append(event)
        if event.prompt == "confirm_connection":
            person.say("The prompt is back. Press DENY now.")

    try:
        supply.connect(state_dir=fresh_state_dir, on_prompt=on_prompt)
    except ConnectionDeniedError:
        pass
    frame_log.settle()
    observe("step3_prompted", [e.prompt for e in seen])
    assert [e.prompt for e in seen if e.prompt == "confirm_connection"] == ["confirm_connection"]
    fast = [f for f in frame_log.sent(0x18, third)][0]
    assert _bind_flag(fast.payload) == 1
    assert fast.payload[:16] != host
