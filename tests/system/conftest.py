"""Fixtures of the system tests: the HIL gate, the opt-ins, the safety teardown and the run record.

The system tests drive the installed library (7-system-tests.md). A test that
uses a supply carries `@pytest.mark.hil`; the autouse fixture `_gate` makes
every such test request `hil_unit` first, which skips it before any I/O
unless `MP305_HIL=1` and `MP305_HIL_DEVICE` are set (AGENTS.md,
"Hardware-in-the-loop tests"). Every connection goes to the unit
`MP305_HIL_DEVICE` names and nowhere else. A test without the marker gets
the discovery and connect seams of the library replaced by a function that
fails, so it cannot reach a real transport.

The opt-ins, all in `OptIns` below:

- `MP305_HIL=1` and `MP305_HIL_DEVICE=<id>`: the HIL gate.
- `MP305_HIL_LOAD=A` or `B`: the named load (8-acceptance-tests.md, section 1)
  is on the output. Only the entries that name that load run then; every
  other HIL test skips, since it needs nothing on the output.
- `MP305_HIL_PERSON=1`: a person is at the supply, reads the instructions on
  stdout (run with `pytest -s`) and answers on stdin.
- `MP305_HIL_DEVICE_HID=<path>`: the HID path of the same unit, for the one
  entry that uses both transports at once (ST-043 step 1).
- `MP305_HIL_RECORD=<file.json>`: write the run's record there.
- `MP305_CSV_FILES=<a.csv><os.pathsep><b.csv>`: the CSV files ST-037 compares.

The safety rules of AGENTS.md are in the `supply` fixture (`Guard`): every
connection a test opens goes through it, and its teardown switches the
output off (reconnecting when the test's own link is gone), restores the
setpoints the supply had when the test started, has the person undo any
front-panel change the test registered, and closes every connection, also
when the test failed.
"""

from __future__ import annotations

import dataclasses
import datetime
import json
import logging
import os
import pathlib
import platform
import shutil
import subprocess
import sys
import time
from collections.abc import Callable, Iterator
from typing import Any

import pytest

import mp305
from mp305 import Event, Info, LiveMode, Mp305, Reading, _native
from mp305 import device as mp305_device
from mp305.types import event_from_native
from tests.system.support import ROOT, SAFE_CURRENT, SAFE_VOLTAGE, FrameLog, wait_until

_log = logging.getLogger("tests.system")


# The opt-ins, in one place.


@dataclasses.dataclass(frozen=True)
class OptIns:
    """What the environment of this run allows (see the module docstring)."""

    hil: bool
    device: str | None
    device_hid: str | None
    load: str | None
    load_problem: str | None
    person: bool
    record: pathlib.Path | None
    csv_files: tuple[pathlib.Path, ...]

    @classmethod
    def from_env(cls) -> OptIns:
        """Reads the variables once."""
        env = os.environ
        load = env.get("MP305_HIL_LOAD", "").strip().upper() or None
        problem = None
        if load is not None and load not in ("A", "B"):
            problem = f"MP305_HIL_LOAD must be A or B, got {env.get('MP305_HIL_LOAD')!r}"
            load = None
        record = env.get("MP305_HIL_RECORD", "").strip()
        csv = env.get("MP305_CSV_FILES", "").strip()
        return cls(
            hil=env.get("MP305_HIL", "") == "1",
            device=env.get("MP305_HIL_DEVICE", "").strip() or None,
            device_hid=env.get("MP305_HIL_DEVICE_HID", "").strip() or None,
            load=load,
            load_problem=problem,
            person=env.get("MP305_HIL_PERSON", "") == "1",
            record=pathlib.Path(record) if record else None,
            csv_files=tuple(pathlib.Path(p) for p in csv.split(os.pathsep) if p),
        )

    def gate_problem(self) -> str | None:
        """Why HIL tests may not run, or None when they may."""
        if not self.hil or self.device is None:
            return (
                "HIL: needs a real MP305B; set MP305_HIL=1 and MP305_HIL_DEVICE to the unit's "
                "Bluetooth identifier or HID path (AGENTS.md, Hardware-in-the-loop tests)"
            )
        if self.load_problem is not None:
            return f"HIL: {self.load_problem}"
        return None


OPT_INS = OptIns.from_env()
"""The opt-ins of this run."""


class NeedsPerson(BaseException):
    """Raised from a prompt callback in teardown when nobody is there to confirm.

    A `BaseException`, so that the library lets it through its dispatcher and
    ends the waiting call (DD-PY-044).
    """


# The person at the supply.


class Person:
    """Instructions on stdout and answers on stdin for the person at the supply."""

    def __init__(self, enabled: bool, interactive: bool) -> None:
        self.enabled = enabled
        self.interactive = interactive

    @property
    def available(self) -> bool:
        """Whether a person opted in and can see the instructions (`pytest -s`)."""
        return self.enabled and self.interactive

    def say(self, text: str) -> None:
        """Prints one instruction, with the time, for the person."""
        stamp = time.strftime("%H:%M:%S")
        print(f"\n>>> PERSON AT THE SUPPLY [{stamp}]: {text}", flush=True)

    def countdown(self, seconds: int, then: str) -> None:
        """Counts `seconds` down on stdout, one line per second, then prints `then`."""
        for left in range(seconds, 0, -1):
            print(f"    {left} ...", flush=True)
            time.sleep(1.0)
        self.say(then)

    def wait_enter(self, text: str) -> float:
        """Prints `text`, waits for Enter and returns the wall time of the press."""
        self.say(f"{text} Then press Enter.")
        input()
        return time.time()

    def ask(self, question: str) -> bool:
        """Asks a yes or no question and returns the answer."""
        while True:
            self.say(question)
            answer = input("    [y/n] ").strip().lower()
            if answer in ("y", "yes"):
                return True
            if answer in ("n", "no"):
                return False


def _interactive(config: pytest.Config) -> bool:
    """Whether stdout and stdin reach the terminal (`pytest -s`)."""
    return config.getoption("capture") == "no"


# The run record.


def _spec(item: pytest.Item) -> str | None:
    """The ST ID of a test, from its spec marker."""
    marker = item.get_closest_marker("spec")
    return str(marker.args[0]) if marker is not None and marker.args else None


def _info_dict(info: Info) -> dict[str, Any]:
    """The supply's `0xE1` values as JSON (SR-012)."""
    return {
        "model": info.model,
        "application_version": info.version,
        "hardware_revision": info.hardware,
        "bootloader": None if info.bootloader is None else info.bootloader.hex(),
        "name": info.name,
    }


class RunRecord:
    """What a run's verification record needs: OS, transport, supply versions, results.

    Written to `MP305_HIL_RECORD` at the end of the session when that is set
    (AGENTS.md, "Verification records").
    """

    def __init__(self) -> None:
        self.started = datetime.datetime.now(datetime.timezone.utc)
        self.unit: dict[str, Any] | None = None
        self.supply: dict[str, Any] | None = None
        self.supply_changes: list[dict[str, Any]] = []
        self.preflight: dict[str, Any] = {}
        self.tests: dict[str, dict[str, Any]] = {}
        self.observations: dict[str, dict[str, Any]] = {}
        self.logs: dict[str, list[tuple[str, FrameLog]]] = {}
        self.csv_files: list[str] = []

    def note_info(self, info: Info, nodeid: str | None) -> None:
        """Keeps the supply's versions once per session and notes any change."""
        values = _info_dict(info)
        if self.supply is None:
            self.supply = values
        elif values != self.supply:
            self.supply_changes.append({"test": nodeid, **values})
        if nodeid is not None:
            self.tests.setdefault(nodeid, {})["supply"] = values

    def observe(self, spec: str, key: str, value: Any) -> None:
        """Keeps one observation of an entry for the record (a TBD result, a timing)."""
        self.observations.setdefault(spec, {})[key] = value

    def keep_log(self, spec: str, transport: str, log: FrameLog) -> None:
        """Keeps a test's frame log for the log checks (ST-017, ST-039, ST-047)."""
        self.logs.setdefault(spec, []).append((transport, log))

    def logs_of(self, spec: str, transport: str | None = None) -> list[FrameLog]:
        """The frame logs an entry's tests kept in this session."""
        return [log for t, log in self.logs.get(spec, []) if transport is None or t == transport]

    def add_report(self, item: pytest.Item, report: pytest.TestReport) -> None:
        """Folds one phase report of a test into its result."""
        entry = self.tests.setdefault(item.nodeid, {})
        entry.setdefault("spec", _spec(item))
        entry.setdefault("hil", item.get_closest_marker("hil") is not None)
        if report.when == "call":
            entry["duration_s"] = round(report.duration, 3)
        if report.skipped:
            entry["outcome"] = "skipped"
            longrepr = report.longrepr
            if isinstance(longrepr, tuple) and len(longrepr) == 3:
                entry["reason"] = str(longrepr[2])
        elif report.failed:
            entry["outcome"] = "failed" if report.when == "call" else f"error in {report.when}"
            entry["reason"] = str(report.longreprtext)[-2000:]
        elif report.when == "call":
            entry["outcome"] = "passed"

    def results(self) -> dict[str, dict[str, Any]]:
        """The result per ST ID over all its tests."""
        out: dict[str, dict[str, Any]] = {}
        for entry in self.tests.values():
            spec = entry.get("spec")
            if spec is None or "outcome" not in entry:
                continue
            counts = out.setdefault(spec, {"passed": 0, "failed": 0, "skipped": 0})
            outcome = entry["outcome"]
            key = outcome if outcome in ("passed", "skipped") else "failed"
            counts[key] += 1
        for counts in out.values():
            if counts["failed"]:
                counts["outcome"] = "failed"
            elif counts["passed"] and counts["skipped"]:
                counts["outcome"] = "partial"
            elif counts["passed"]:
                counts["outcome"] = "passed"
            else:
                counts["outcome"] = "skipped"
        return dict(sorted(out.items()))

    def write(self, path: pathlib.Path) -> None:
        """Writes the record as JSON."""
        data = {
            "record": "system tests (7-system-tests.md)",
            "started": self.started.isoformat(timespec="seconds"),
            "finished": datetime.datetime.now(datetime.timezone.utc).isoformat(timespec="seconds"),
            "commit": _commit(),
            "os": {
                "system": platform.system(),
                "release": platform.release(),
                "version": platform.version(),
                "machine": platform.machine(),
                "platform": platform.platform(),
            },
            "python": sys.version,
            "mp305": mp305.__version__,
            "unit": self.unit,
            "opt_ins": {
                "hil": OPT_INS.hil,
                "load": OPT_INS.load,
                "person": OPT_INS.person,
                "device_hid": OPT_INS.device_hid,
            },
            "supply": self.supply,
            "supply_changes": self.supply_changes,
            "preflight": self.preflight,
            "results": self.results(),
            "tests": self.tests,
            "observations": self.observations,
            "csv_files": self.csv_files,
            "frame_logs": {
                spec: [{"transport": t, "lines": log.lines()} for t, log in logs]
                for spec, logs in sorted(self.logs.items())
            },
        }
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(data, indent=2, default=str) + "\n", encoding="utf-8")


def _commit() -> str:
    """The commit of the checkout, marked when the tree has changes (read-only calls)."""
    tool = shutil.which("git")
    if tool is None:
        return "unknown"
    try:
        head = subprocess.run(
            [tool, "rev-parse", "HEAD"], capture_output=True, text=True, cwd=ROOT, check=True
        ).stdout.strip()
        dirty = subprocess.run(
            [tool, "status", "--porcelain"], capture_output=True, text=True, cwd=ROOT, check=True
        ).stdout.strip()
    except (OSError, subprocess.CalledProcessError):
        return "unknown"
    return f"{head} (uncommitted changes)" if dirty else head


RECORD = RunRecord()
"""The record of this run."""


@pytest.hookimpl(wrapper=True)
def pytest_runtest_makereport(
    item: pytest.Item, call: pytest.CallInfo[None]
) -> Iterator[pytest.TestReport]:
    """Keeps the result of every system test for the run's record."""
    report: pytest.TestReport = yield
    RECORD.add_report(item, report)
    return report


def pytest_sessionfinish(session: pytest.Session, exitstatus: int) -> None:
    """Writes the run's record when `MP305_HIL_RECORD` names a file."""
    if OPT_INS.record is not None and RECORD.tests:
        RECORD.write(OPT_INS.record)


# The unit and the gate.


@dataclasses.dataclass(frozen=True)
class Unit:
    """The supply this run may talk to: `MP305_HIL_DEVICE` and its transport."""

    identifier: str
    transport: str


def _find_unit(identifier: str) -> Unit | None:
    """The transport of `identifier`, from discovery: USB first, then a Bluetooth scan."""
    for found in mp305.discover(1.0, bluetooth=False, usb=True):
        if found.identifier == identifier:
            return Unit(identifier, "hid")
    for found in mp305.discover(mp305_device.SCAN_DEFAULT_S, bluetooth=True, usb=False):
        if found.identifier == identifier:
            return Unit(identifier, "ble")
    return None


@pytest.fixture(scope="session")
def hil_unit() -> Unit:
    """The HIL gate, then the unit and its transport, found by discovery.

    Skips every test that requests it unless `MP305_HIL=1` and
    `MP305_HIL_DEVICE` are set; nothing touches a transport before that.
    It only scans and enumerates: no connection is made here, so the
    entries that only discover (ST-001 to ST-003) send nothing to the
    supply. The pre-flight connection is `preflight`, which every test that
    connects gets through `supply`.
    """
    problem = OPT_INS.gate_problem()
    if problem is not None:
        pytest.skip(problem)
    assert OPT_INS.device is not None
    unit = _find_unit(OPT_INS.device)
    if unit is None:
        pytest.fail(
            f"MP305_HIL_DEVICE={OPT_INS.device!r} was not found over USB or Bluetooth; "
            "is the supply on, with remote control enabled and no other app connected?"
        )
    RECORD.unit = {"identifier": unit.identifier, "transport": unit.transport}
    return unit


@pytest.fixture(scope="session")
def preflight(hil_unit: Unit, pytestconfig: pytest.Config) -> Unit:
    """One connection before the first test that connects.

    It connects with the default state directory, keeps the supply's
    versions for the record (SR-012) and stops the run when the output is on
    at the start (its close switches the output off).
    """
    unit = hil_unit
    person = Person(OPT_INS.person, _interactive(pytestconfig))

    def on_prompt(event: Event) -> None:
        if not person.available:
            raise NeedsPerson(event.prompt)
        person.say("Pre-flight check: press ALLOW on the supply's screen now.")

    try:
        dev = Mp305.connect(
            unit.identifier,
            on_prompt=on_prompt,
            max_voltage=SAFE_VOLTAGE,
            max_current=SAFE_CURRENT,
        )
    except NeedsPerson:
        RECORD.preflight = {
            "connected": False,
            "reason": "the supply does not recognise this installation's host ID",
        }
        return unit
    reading = dev.reading
    RECORD.note_info(dev.info, None)
    RECORD.preflight = {
        "connected": True,
        "output_on": None if reading is None else reading.output_on,
        "set_voltage": None if reading is None else reading.set_voltage,
        "set_current": None if reading is None else reading.set_current,
        "live_mode": None if reading is None else reading.live_mode.value,
    }
    dev.close()
    if reading is not None and reading.output_on:
        pytest.fail(
            "the output was on at the start of the run (the pre-flight close switched it off); "
            "check that nothing unexpected is connected, then start again"
        )
    return unit


@pytest.fixture(autouse=True)
def _gate(request: pytest.FixtureRequest, monkeypatch: pytest.MonkeyPatch) -> Iterator[None]:
    """The HIL gate for every `hil` test; no hardware for any other test.

    A `hil` test requests `hil_unit` (which skips without the HIL variables)
    and, while a load is declared, runs only when it asks for that load. Any
    other test gets the library's discovery and connect seams replaced by a
    function that fails, so that it cannot start a scan or open a device.
    """
    if request.node.get_closest_marker("hil") is not None:
        request.getfixturevalue("hil_unit")
        wants = {"load_a", "load_b"} & set(request.fixturenames)
        if OPT_INS.load is not None and not wants:
            pytest.skip(
                f"Load {OPT_INS.load} is on the output (MP305_HIL_LOAD={OPT_INS.load}); "
                "this entry needs nothing connected"
            )
    else:

        def forbidden(*args: object, **kwargs: object) -> Any:
            raise AssertionError("a test without the hil marker reached the real transport")

        monkeypatch.setattr(mp305_device, "_discover", forbidden)
        monkeypatch.setattr(mp305_device, "_open_session", forbidden)
    yield
    mp305.set_log_level(logging.WARNING)


@pytest.fixture
def ble_unit(hil_unit: Unit) -> Unit:
    """The unit, for an entry that runs over Bluetooth only."""
    if hil_unit.transport != "ble":
        pytest.skip(
            "this entry runs over Bluetooth; MP305_HIL_DEVICE names a USB HID unit "
            "(run again with the Bluetooth identifier)"
        )
    return hil_unit


@pytest.fixture
def hid_unit(hil_unit: Unit) -> Unit:
    """The unit, for an entry that runs over USB only."""
    if hil_unit.transport != "hid":
        pytest.skip(
            "this entry runs over USB; MP305_HIL_DEVICE names a Bluetooth unit "
            "(run again with the HID path)"
        )
    return hil_unit


@pytest.fixture
def person(hil_unit: Unit, pytestconfig: pytest.Config) -> Person:
    """The person at the supply; skips unless `MP305_HIL_PERSON=1` and `pytest -s`."""
    if not OPT_INS.person:
        pytest.skip("needs a person at the supply; set MP305_HIL_PERSON=1 and run with -s")
    if not _interactive(pytestconfig):
        pytest.skip("needs a person at the supply; run with -s so that the instructions show")
    return Person(True, True)


@pytest.fixture
def controls(hil_unit: Unit, pytestconfig: pytest.Config) -> Person:
    """For an entry that makes control calls: over Bluetooth a person must allow them.

    Over Bluetooth the first control call of a connection opens the supply's
    "Allow Remote Control" prompt (SR-018, SR-053), so the entry skips unless
    a person is there. Returns the person (an absent one over USB).
    """
    present = Person(OPT_INS.person, _interactive(pytestconfig))
    if hil_unit.transport == "ble" and not present.available:
        pytest.skip(
            "over Bluetooth every control call needs a person to allow remote control on the "
            "supply (SR-018); set MP305_HIL_PERSON=1 and run with -s"
        )
    return present


@pytest.fixture
def load_a(hil_unit: Unit) -> str:
    """Load A, the 100 ohm resistor of 8-acceptance-tests.md, is on the output."""
    if OPT_INS.load != "A":
        pytest.skip("needs Load A (100 ohm, 1 %) on the output; set MP305_HIL_LOAD=A")
    return "A"


@pytest.fixture
def load_b(hil_unit: Unit) -> str:
    """Load B, the 22 ohm resistor of 8-acceptance-tests.md, is on the output."""
    if OPT_INS.load != "B":
        pytest.skip("needs Load B (22 ohm) on the output; set MP305_HIL_LOAD=B")
    return "B"


@pytest.fixture
def fresh_state_dir(tmp_path: pathlib.Path) -> pathlib.Path:
    """A new state directory, so a new host ID that the supply does not recognise.

    The entries that need the bind prompt over Bluetooth use it (section 1 of
    7-system-tests.md). Every other connection uses the default state
    directory, the remembered-host path.
    """
    return tmp_path / "fresh-state"


@pytest.fixture
def observe(request: pytest.FixtureRequest) -> Callable[[str, Any], None]:
    """Keeps an observation of the test's entry for the run's record."""
    spec = _spec(request.node) or request.node.nodeid

    def keep(key: str, value: Any) -> None:
        RECORD.observe(spec, key, value)

    return keep


@pytest.fixture
def frame_log(request: pytest.FixtureRequest) -> Iterator[FrameLog]:
    """The library's log with the frame log on (`set_log_level(5)`).

    A `hil` test's log is kept under its ST ID for the log checks and the
    run's record.
    """
    log = FrameLog().start()
    yield log
    log.settle(0.3)
    log.stop()
    spec = _spec(request.node)
    if spec is not None and request.node.get_closest_marker("hil") is not None:
        transport = RECORD.unit["transport"] if RECORD.unit else "unknown"
        RECORD.keep_log(spec, transport, log)


@pytest.fixture
def mock_device() -> Iterator[Callable[..., Mp305]]:
    """A factory over `Mp305._from_mock` that closes every device at teardown."""
    devices: list[Mp305] = []

    def make(scripts: list[Any], **kwargs: Any) -> Mp305:
        device = Mp305._from_mock(scripts, **kwargs)
        devices.append(device)
        return device

    yield make
    for device in devices:
        try:
            device.close()
        except mp305.Mp305Error as error:
            _log.warning("close of %s at teardown failed: %s", device.identifier, error)


# The safety guard.


class HilMp305(Mp305):
    """An `Mp305` that tells its guard when the output was asked to switch on."""

    guard: Guard | None = None

    def output_on(self) -> None:
        """Notes the energize request, then switches the output on."""
        if self.guard is not None:
            self.guard.energized = True
        super().output_on()


PromptHandler = Callable[[Event], None]
"""A test's prompt callback."""


class Guard:
    """Opens every connection of a test and makes the supply safe again afterwards.

    `finish` runs in teardown, also after a failure, in this order: (1) the
    output off on every open connection in DC mode when the test asked for
    it on or a reading shows it on; (2) the front-panel changes the test
    registered, undone by the person; (3) on every open connection the
    output off if still on, the setpoints back to the values the supply had
    when the test first connected, then the close; (4) when the test asked
    for the output on and no open connection confirmed it off, or the
    setpoints were not restored, a new connection does (3). Teardown is keyed
    on "an output-on was requested", never only on a reading that a lost link
    could not deliver.
    """

    def __init__(self, unit: Unit, person: Person, nodeid: str) -> None:
        self.unit = unit
        self.person = person
        self.nodeid = nodeid
        self.devices: list[HilMp305] = []
        self.natives: list[_native.Session] = []
        self.energized = False
        self.original: tuple[float, float] | None = None
        self.restores: list[tuple[str, Callable[[], bool] | None]] = []
        self.in_teardown = False

    # Opening.

    def _prompt(self, handler: PromptHandler | None) -> PromptHandler:
        """The callback a connection gets: the test's while it runs, the guard's in teardown."""

        def dispatch(event: Event) -> None:
            if self.in_teardown:
                self._teardown_prompt(event)
            elif handler is not None:
                handler(event)
            else:
                self.default_prompt(event)

        return dispatch

    def default_prompt(self, event: Event) -> None:
        """Tells the person to press allow; skips the test when nobody is there."""
        if not self.person.available:
            pytest.skip(
                f"the supply shows a prompt ({event.prompt}) that a person must confirm; "
                "set MP305_HIL_PERSON=1 and run with -s"
            )
        if event.prompt == "confirm_connection":
            self.person.say("The supply asks to confirm the connection: press ALLOW now.")
        else:
            self.person.say("The supply asks to allow remote control: press ALLOW now.")

    def _teardown_prompt(self, event: Event) -> None:
        """In teardown a prompt needs the person to make the supply safe."""
        if not self.person.available:
            raise NeedsPerson(event.prompt)
        self.person.say(
            "Teardown: the supply asks for a confirmation so that the test can switch the "
            "output off and restore the setpoints: press ALLOW now."
        )

    def connect(
        self,
        *,
        state_dir: pathlib.Path | None = None,
        on_prompt: PromptHandler | None = None,
        reconnect: bool = False,
        max_voltage: float | None = SAFE_VOLTAGE,
        max_current: float | None = SAFE_CURRENT,
    ) -> HilMp305:
        """Connects to the unit of this run; the user limits default to 5 V and 0.1 A.

        `state_dir` None is the default state directory (the remembered-host
        path over Bluetooth). The setpoints of the first connection are the
        ones the teardown restores.
        """
        dev = HilMp305.connect(
            self.unit.identifier,
            on_prompt=self._prompt(on_prompt),
            reconnect=reconnect,
            max_voltage=max_voltage,
            max_current=max_current,
            state_dir=state_dir,
        )
        assert isinstance(dev, HilMp305)
        dev.guard = self
        self.devices.append(dev)
        RECORD.note_info(dev.info, self.nodeid)
        reading = dev.reading
        if self.original is None and reading is not None:
            self.original = (reading.set_voltage, reading.set_current)
        return dev

    def connect_when_back(self, timeout: float = 60.0) -> HilMp305:
        """`connect`, tried again every 2 s while the supply is not reachable yet.

        After a link loss or a killed process the supply needs a moment to
        notice the drop and to advertise again.
        """
        deadline = time.monotonic() + timeout
        while True:
            try:
                return self.connect()
            except (mp305.NotFoundError, mp305.LinkLostError):
                if time.monotonic() >= deadline:
                    raise
                time.sleep(2.0)

    def native_connect(self, state_dir: pathlib.Path | None = None) -> _native.Session:
        """The two-step native connect of DD-PY-031 (the test hook of ST-012), closed in teardown.

        It returns before the connect flow ran; `ready` waits for it.
        """
        native = _native.Session.connect(
            self.unit.identifier, state_dir, False, SAFE_VOLTAGE, SAFE_CURRENT
        )
        self.natives.append(native)
        return native

    def native_dispatch(
        self, handler: PromptHandler | None = None, events: list[Event] | None = None
    ) -> Callable[[tuple[int, str, dict[str, object]]], None]:
        """A dispatcher for a native session: keeps the events and routes prompts."""
        route = self._prompt(handler)

        def dispatch(t: tuple[int, str, dict[str, object]]) -> None:
            event = event_from_native(t)
            if events is not None:
                events.append(event)
            if event.prompt is not None:
                route(event)

        return dispatch

    def mark_energized(self) -> None:
        """Notes that something outside this guard (a child process) switched the output on."""
        self.energized = True

    def restore_by_person(self, instruction: str, verify: Callable[[], bool] | None = None) -> None:
        """Registers a change the person undoes in teardown, checked by `verify` when given."""
        self.restores.append((instruction, verify))

    def peek(self) -> Reading | None:
        """A reading from a short new connection (closed again), for a restore check."""
        dev = self.connect()
        try:
            return dev.read(timeout=3.0)
        finally:
            dev.close()

    # Teardown.

    @staticmethod
    def _open(dev: Mp305) -> bool:
        """Whether a connection can still send."""
        return not dev.closed and dev.link_state == "ready"

    @staticmethod
    def _dc(dev: Mp305) -> bool:
        """Whether the latest reading shows DC mode, the only mode the library controls."""
        reading = dev.reading
        return reading is not None and reading.live_mode is LiveMode.DC

    def _off(self, dev: Mp305, problems: list[str]) -> bool:
        """Switches the output off; True when a fresh reading then shows it off."""
        try:
            dev.output_off()
            return not dev.read(timeout=3.0).output_on
        except (mp305.Mp305Error, NeedsPerson) as error:
            problems.append(f"output-off on {dev.identifier} failed: {error!r}")
            return False

    def _restore_setpoints(self, dev: Mp305, problems: list[str]) -> bool:
        """Sets the setpoints of the test's start again, with the output confirmed off."""
        if self.original is None:
            return True
        try:
            reading = dev.read(timeout=3.0)
            if (reading.set_voltage, reading.set_current) == self.original:
                return True
            if reading.output_on or reading.live_mode is not LiveMode.DC:
                problems.append("setpoints not restored: the output is on or the mode is not DC")
                return False
            volts, amps = self.original
            # The user limits guarded the test; the restore puts back what the
            # supply had, with the output confirmed off.
            dev.set_limits(max_voltage=None, max_current=None)
            if reading.set_voltage != volts:
                dev.set_voltage(volts)
            if reading.set_current != amps:
                dev.set_current_limit(amps)
            return True
        except (mp305.Mp305Error, NeedsPerson) as error:
            problems.append(f"restoring the setpoints {self.original} failed: {error!r}")
            return False

    def _person_restore(
        self, instruction: str, verify: Callable[[], bool] | None, problems: list[str]
    ) -> None:
        """Has the person undo one front-panel change, then checks it when it can."""
        if not self.person.available:
            problems.append(f"nobody to restore: {instruction}")
            return
        if verify is None:
            self.person.wait_enter(f"Teardown: {instruction}")
            return
        self.person.say(f"Teardown: {instruction} The test waits until it sees the change.")

        def done() -> bool:
            try:
                return verify()
            except (mp305.Mp305Error, NeedsPerson):
                return False

        if not wait_until(done, 180.0, step=1.0):
            problems.append(f"not restored within 180 s: {instruction}")

    def _setpoints_unchanged(self) -> bool:
        """Whether the newest reading of the test still shows the setpoints of its start."""
        if self.original is None:
            return True
        readings = [r for r in (dev.reading for dev in self.devices) if r is not None]
        if not readings:
            return True
        newest = max(readings, key=lambda r: r.wall_ns)
        return (newest.set_voltage, newest.set_current) == self.original

    def finish(self) -> list[str]:
        """Makes the supply safe again; returns what could not be done."""
        self.in_teardown = True
        problems: list[str] = []
        confirmed_off = False
        restored = self._setpoints_unchanged()
        for native in self.natives:
            try:
                native.close(True, None)
            except mp305.Mp305Error as error:
                problems.append(f"close of a native session failed: {error!r}")
        # (1) The output off first, where the library can.
        for dev in reversed(self.devices):
            reading = dev.reading
            if (
                self._open(dev)
                and self._dc(dev)
                and (self.energized or (reading is not None and reading.output_on))
            ):
                confirmed_off = self._off(dev, problems) or confirmed_off
        # (2) Front-panel changes, undone by the person.
        for instruction, verify in self.restores:
            self._person_restore(instruction, verify, problems)
        # (3) Every open connection: off, setpoints, close.
        for dev in reversed(self.devices):
            if self._open(dev) and self._dc(dev):
                reading = dev.reading
                if reading is not None and reading.output_on:
                    confirmed_off = self._off(dev, problems) or confirmed_off
                else:
                    confirmed_off = True
                if not restored:
                    restored = self._restore_setpoints(dev, problems)
            state = dev.link_state
            try:
                dev.close()
            except mp305.Mp305Error as error:
                # The close of a link that is already gone reports the loss
                # (DD-PY-043); only a failed close of a ready link is a problem.
                if state == "ready":
                    problems.append(f"close of {dev.identifier} failed: {error!r}")
        # (4) A new connection when the test's own could not confirm.
        if (self.energized and not confirmed_off) or not restored:
            try:
                dev = self.connect_when_back(30.0)
            except (mp305.Mp305Error, NeedsPerson) as error:
                problems.append(f"the teardown connection failed: {error!r}")
                return problems
            try:
                reading = dev.read(timeout=3.0)
                if self.energized or reading.output_on:
                    if not self._off(dev, problems):
                        problems.append("the output could not be confirmed off")
                if not restored:
                    self._restore_setpoints(dev, problems)
            except (mp305.Mp305Error, NeedsPerson) as error:
                problems.append(f"the teardown connection failed: {error!r}")
            finally:
                try:
                    dev.close()
                except mp305.Mp305Error as error:
                    problems.append(f"close of the teardown connection failed: {error!r}")
        return problems


@pytest.fixture
def supply(
    preflight: Unit, request: pytest.FixtureRequest, pytestconfig: pytest.Config
) -> Iterator[Guard]:
    """The guard every connection to the supply goes through (see `Guard`)."""
    present = Person(OPT_INS.person, _interactive(pytestconfig))
    guard = Guard(preflight, present, request.node.nodeid)
    yield guard
    problems = guard.finish()
    if problems:
        text = "; ".join(problems)
        print(
            "\n!!! SAFETY: the teardown could not make the supply safe: "
            f"{text}. Check the supply now: switch the output off on its front panel and "
            "restore its settings by hand.",
            flush=True,
        )
        pytest.fail(f"teardown: {text}")


@pytest.fixture
def run_record() -> RunRecord:
    """The record of this run: kept frame logs, CSV files, observations."""
    return RECORD


@pytest.fixture
def opt_ins() -> OptIns:
    """The opt-ins of this run."""
    return OPT_INS
