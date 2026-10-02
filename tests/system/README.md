# System tests

The automated part of [7-system-tests.md](../../docs/v-model/7-system-tests.md).
The tests drive the system through the installed Python library `mp305`.
Each test carries `@pytest.mark.spec("ST-nnn")`; each test that uses a
supply also carries `@pytest.mark.hil`.

Files:

| File | Entries |
|---|---|
| `conftest.py` | The HIL gate, the opt-ins, the safety guard (`supply` fixture), the run record |
| `support.py` | Frame log parsing, frame layouts, mock scripts, child processes, the CSV check |
| `test_connection.py` | ST-006 to ST-011, ST-043 to ST-045 |
| `test_control.py` | ST-018 to ST-025, ST-046, ST-048, ST-049 |
| `test_csv_format.py` | ST-037 |
| `test_discovery.py` | ST-001 to ST-004 |
| `test_faults.py` | ST-026, ST-027 |
| `test_framing.py` | ST-040 |
| `test_library.py` | ST-031, ST-032, ST-034, ST-035 |
| `test_link_loss.py` | ST-028, ST-029, ST-041, ST-050 |
| `test_readings.py` | ST-012 to ST-017, ST-033 |
| `test_wire_checks.py` | ST-017 step 1, ST-039, ST-047 (checks of frame logs kept earlier in the run) |

Entries with no code: ST-005, ST-030, ST-036, ST-038 (manual) and ST-042
(inspection); see "What is not automated" below.

## Running

Build the extension first, then always use `--no-sync`:

```sh
env -u CONDA_PREFIX uv run maturin develop -m crates/mp305-py/Cargo.toml
uv run --no-sync pytest tests/system
```

That runs the tests without a supply (the mock parts and the analyses). It
never touches a transport: without the `hil` marker a test gets the
library's discovery and connect replaced by a function that fails.

A HIL run, only when the owner asks for it in the current session
(AGENTS.md, "Working with the real device"):

```sh
MP305_HIL=1 MP305_HIL_DEVICE=<id> MP305_HIL_RECORD=<file.json> \
  uv run --no-sync pytest tests/system -m hil -s -rs
```

`<id>` is the Bluetooth identifier as the OS reports it (the CoreBluetooth
UUID on macOS) or the HID path. A run covers the transport of that one
identifier; run the suite once with the Bluetooth identifier and once with
the HID path to cover both columns of section 2 of the specification. A
test for the other transport skips with the reason.

Add the opt-ins for the entries that need them:

```sh
# A person at the supply (instructions on stdout, answers on stdin; needs -s).
MP305_HIL_PERSON=1
# Load A (100 ohm, 1 %) on the output: only ST-014, ST-015 and ST-022 run.
MP305_HIL_LOAD=A
# Load B (22 ohm) on the output: only ST-026 and ST-027 run.
MP305_HIL_LOAD=B
# ST-043 step 1 only: the HID path of the same unit, while MP305_HIL_DEVICE
# names it over Bluetooth.
MP305_HIL_DEVICE_HID=<path>
```

A sensible order is: one run with no load and no person, one with
`MP305_HIL_PERSON=1`, then one with `MP305_HIL_LOAD=A` and one with
`MP305_HIL_LOAD=B`, both with the person there. Over Bluetooth almost every
entry that controls the supply needs the person, since the supply asks to
allow remote control on its screen at the first control call of every
connection (SR-018).

ST-037 compares CSV files and uses no supply. Give it the file ST-034 wrote
(its path is in the run's record under `csv_files`) and one the app
recorded, separated by the OS path separator:

```sh
MP305_CSV_FILES=<library.csv>:<app.csv> uv run --no-sync pytest tests/system/test_csv_format.py
```

## The opt-ins

All are read once, in `OptIns` in `conftest.py`.

| Variable | Effect |
|---|---|
| `MP305_HIL=1` and `MP305_HIL_DEVICE` | The HIL gate. Without both, every `hil` test skips before any I/O. |
| `MP305_HIL_LOAD=A` or `B` | That load is on the output. Only the entries that name it run; every other `hil` test skips, since it needs nothing connected. |
| `MP305_HIL_PERSON=1` | A person is at the supply. Entries that need one (front panel, prompts, cables, power) skip without it, and also without `-s`. |
| `MP305_HIL_DEVICE_HID` | The same unit's HID path for ST-043 step 1. |
| `MP305_HIL_RECORD` | Where the run's JSON record goes; no file when unset. |
| `MP305_CSV_FILES` | The CSV files ST-037 compares. |

## Safety

The rules of AGENTS.md hold in every HIL test, and the fixtures enforce
them so that no test can leave them out:

- Every connection goes through the `supply` fixture (`Guard` in
  `conftest.py`) to the unit `MP305_HIL_DEVICE` names, with user limits of
  5 V and 0.1 A unless an entry needs others (ST-024 sets 4 V); the library
  then refuses any setpoint above them and any output-on while a copied
  setpoint is above them.
- Teardown, also after a failure: the output off on every open connection,
  the front-panel changes undone by the person, the setpoints back to the
  values the supply had when the test started (with the output confirmed
  off), every connection closed. When the test asked for the output on and
  its own link is gone (a link loss, a killed child process), the teardown
  connects again to switch the output off. When it cannot make the supply
  safe it prints `!!! SAFETY` with what to do on the front panel and fails
  the test.
- Before the first HIL test the run finds the unit's transport by discovery
  (USB first, then a 10 s Bluetooth scan) and connects once with the default
  state directory to read the supply's versions. If the output is on then,
  the run stops.

Before a run: nothing on the output (unless the run declares a load), the
output off, remote control enabled on the supply, DC mode, CC selected (not
OCP), no other app connected. Over Bluetooth the supply must recognise the
host ID of the default state directory: connect once with the library or the
app and press allow. The entries that need the bind prompt use a fresh state
directory instead; each one the person allows takes one of the five host
places the supply keeps (device-model.md 3), which can push the default host
ID out. Run those last and confirm the default host again afterwards if
needed.

## The run record

With `MP305_HIL_RECORD` set, the run writes a JSON file with the commit, the
OS, Python, the library version, the unit and its transport, the opt-ins,
the supply's versions from `0xE1` (model, application version, hardware
revision, bootloader and name; read once per run, and every change seen
later), the result per ST ID and per test (with skip reasons), the
observations the entries record for their TBDs, the CSV files written, and
the frame logs the tests kept. The verification record of the run
(`docs/v-model/records/`) cites it.

## What each test does to the supply

"Person" means the entry needs `MP305_HIL_PERSON=1`; "BLE person" means
only over Bluetooth (the remote-control prompt). Every test that changes
the setpoints or switches the output on is undone in teardown as described
above.

| Test | Transport | Opt-ins | What it does |
|---|---|---|---|
| ST-001 | BLE | person | Scans; the person disables remote control on the front panel, the test scans again; the person enables it again. |
| ST-002 | BLE | | Scans with the default time, 1 s and 60 s (about 75 s in all). |
| ST-003 | USB | | Enumerates USB. |
| ST-004 | both | | Scans, connects, closes. Step 2 adds a simulated second supply; nothing is sent. |
| ST-006 | both | BLE person | Connects, sets 5 V and 0.1 A, output on with nothing connected, output off, closes. |
| ST-007 | BLE | person | Fresh host ID; the person presses deny. |
| ST-008 | BLE | person | Fresh host ID; the person presses allow. |
| ST-009 | BLE | person | Fresh host ID; the person waits 5 s, then presses allow. |
| ST-010 | BLE | person | Fresh host ID; nobody presses anything (about 30 s). |
| ST-011 | USB | person | Connects; the person says whether the screen showed a prompt. |
| ST-012 | both | person (values) | Connects; the person compares the values with the screens. The second test connects through the native two-step connect and calls `output_off` before the first reading. |
| ST-013 | both | | Connects and reads for 60 s, output off. |
| ST-014 | both | Load A, person | The person sets 5.00 V and 0.100 A on the front panel; output on into Load A; 10 readings. |
| ST-015 | both | Load A, person | The person confirms CC; 5 V and 0.1 A, output on (CV), then 0.02 A (CC). |
| ST-016 | none | | Mock only. |
| ST-017 | none | | Mock only; step 1 checks the frame log of ST-013. |
| ST-018 | both | BLE person | Sets 1.00 V; over Bluetooth the person waits 3 s, then allows remote control. |
| ST-019 | both | person | Sets 3 V, 0.05 A, output off; the person sets 4 V on the front panel; the test sets 0.08 A. |
| ST-020 | both | BLE person | 20 voltage and current changes from 1 V to 4.8 V and 10 mA to 86 mA, output off. |
| ST-021 | both | person | The person selects program or PD mode; `set_voltage(1.0)` is refused; the person selects DC mode again. |
| ST-022 | both | Load A, BLE person | 5 V and 0.1 A into Load A, output on, five queued changes (1 V to 3 V) and output off. Step 4 (BLE, person): the person switches Bluetooth off on the host with the output on, then on again; the test reconnects and switches the output off after the person allows remote control. |
| ST-023 | both | BLE person; step 2 person | Sets 1.00 V; step 2 asks the person to take remote control away on the front panel if possible, then sets 1.5 V. Step 3 is mock only. |
| ST-024 | both | BLE person | User limit 4 V; five refused values, then 1.004 V and 1.006 V. |
| ST-025 | none | | Mock only. |
| ST-026 | both | Load B, person | The person selects OCP; 5 V and 0.1 A into Load B, output on (the supply trips), output on again (refused); the person selects CC again. |
| ST-027 | both | Load B, person | As ST-026 while streaming. Step 2 is mock only. |
| ST-028 | both | person | Readings with the output off; the person switches the supply off, Bluetooth off on the host, or pulls the USB cable, then undoes it. |
| ST-029 | both | BLE person | A `with` block: 5 V and 0.1 A, output on with nothing connected, then an exception or a normal end. |
| ST-031 | BLE (step 1), both (step 2) | person (step 1) | Step 1: a child process connects with a fresh host ID and interrupts itself during the bind wait; the person presses nothing (deny afterwards if the prompt stays). Step 2: reads while a thread counts. |
| ST-032 | none | | Inspects the exception classes. |
| ST-033 | both | | Connects and reads. |
| ST-034 | both | | Streams for 3 x 30 s and records 30 s to CSV, output off. |
| ST-035 | both | BLE person | Ramps the voltage 1 V to 5 V in 1 V steps with 1 s dwell, output as it is (off); then a ramp above a 4 V limit (refused). |
| ST-037 | none | | Reads CSV files. |
| ST-039 | BLE | | Checks the frame logs of ST-008 and ST-013 of the same run. |
| ST-040 | USB | | Sets 1.70 V and reads; the mock part needs no supply. |
| ST-041 | both | BLE person | A child process sets 5 V and 0.1 A and switches the output on with nothing connected and is killed with SIGKILL; the test reconnects, switches the output off; then a control run with an orderly close. |
| ST-043 | BLE and USB (step 1), both (step 2) | `MP305_HIL_DEVICE_HID` (step 1) | Step 1: a Bluetooth session with reconnection on while a child process connects over USB and reads once. Step 2: a second connection in the same process (refused). |
| ST-044 | none | | Reads host IDs from temporary state directories. |
| ST-045 | BLE | person | Fresh host ID: allow, reconnect without a prompt, then a new ID (the person presses deny). |
| ST-046 | USB | | Takes remote control, reads for 20 s, sets 1.00 V. |
| ST-047 | none | | Checks the frame logs of ST-006, ST-008 and ST-018 of the same run. |
| ST-048 | BLE | person | Sets 1.00 V three times: the person denies; nobody presses (about 60 s); the person allows after 10 s while a second call is queued. |
| ST-049 | both | person | Takes remote control; the person selects PD mode; the test closes; the person selects DC mode again. |
| ST-050 | BLE (steps 1, 4), USB (step 2) | person | Reconnection on: Bluetooth off for 20 s, or the USB cable out and in. Step 4: reconnection off, Bluetooth off. |

ST-039 and ST-047, and ST-017 step 1, carry the `hil` marker although they
send nothing: they check the frame logs that the HIL tests kept earlier in
the same run, and skip when those are missing.

After a pulled and re-plugged USB cable (ST-028, ST-050 step 2) the OS may
give the supply a new HID path; the later tests then no longer find
`MP305_HIL_DEVICE`. Run those entries last in a USB run, or start again
with the new path.

## What is not automated

| Entry | Why |
|---|---|
| ST-005 | Manual (needs WebLink in Chrome). |
| ST-030, ST-038 | Manual app sessions. |
| ST-036 | Inspection plus manual (install on each OS, start the app, the macOS bundle). |
| ST-042 | Inspection of the installed READMEs and the app's connection screen. |
| ST-006 step 2 | An inspection of `mp305-core`'s `protocol::policy`, which the library does not expose. |
| ST-040, a request over more than one report | No allowed request is longer than one report, and the mock records a request as one stream; the mock part checks a 70-byte reply over two reports instead. |
| ST-050 step 3 | The session reads the host ID once at connect, so deleting it from the state directory does not change what the reconnection presents, and the library cannot make the supply forget a host. |
| ST-003, the serial string | The library does not expose it. |
