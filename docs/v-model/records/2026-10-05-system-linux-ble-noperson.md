# Verification record: system tests on Linux over Bluetooth, the entries without a person

Date: 2026-10-05, 00:20 to 00:26 local time (2026-10-04T22:20 to 22:26
UTC). Level: system. Scope: every automated system test that needs
neither a person, a load nor USB, run from the user's machine "halobox"
within the user's go-ahead of this session ("fire at will", after the
question whether to run the Linux entries that need no person).

Commit: `5e7a84d` (a clone of the public repository on the machine; the
library's code is that of `1cbcb09`).

Machine: Ubuntu 26.04.1 LTS, Linux 7.0.0-31-generic, x86_64, no virtual
machine. BlueZ 5.85. CPython 3.10.20, pytest 9.1.1, Rust 1.93.1.
Adapter: the ASUS USB-BT600 dongle as the machine's only Bluetooth
adapter (the built-in one unbound from `btusb` for the run, bound again
afterwards). Transport: Bluetooth LE. Firmware of the supply, read in
the run: System Version 1.6.0.51, Firmware Version 2.0.2.0. The supply
was on with remote control enabled; nobody was at it.

## Command

```sh
MP305_HIL=1 MP305_HIL_DEVICE=<the BlueZ identifier> MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system -m hil -s -rs -v
```

No opt-in besides `MP305_HIL`. 9 tests passed, 1 failed, 42 skipped.

## Results

| ST | Result | Observation |
|---|---|---|
| ST-002 | pass | default scan 10.046 s; 1 s scan 1.040 s; 60 s scan 60.041 s |
| ST-004 | pass | connect by identifier; a simulated second supply is refused |
| ST-012 | pass for the automated part | a control call before the first reading is refused ("the session is not ready for control"); the comparison with the screens needs a person |
| ST-013 | pass | 147 readings in 60 s; the shortest time from a reply to the next request 100 ms |
| ST-017 | pass for step 1 | no overlapping requests in the frame log of ST-013 |
| ST-031 | pass for step 2 | a thread counts while a call blocks; step 1 needs a person |
| ST-033 | pass | a reading is typed and immutable |
| ST-034 | **fail** | counts in 30 s: 3 at 0.1 per second, 60 at 2 per second, 86 at 4 per second (120 expected, 10 % allowed); the library logged "the supply delivers fewer readings than the requested rate" |
| ST-039 | pass for the log of ST-013 | the Bluetooth frames have the stated shape; the log of ST-008 needs a person |
| ST-043 | pass for step 2 | a second connection names the open one; step 1 needs the unit over USB too |

Skipped, with the reason the tests gave: 21 need a person at the supply,
9 need a person for the remote-control prompt over Bluetooth, 4 run over
USB, 4 need Load A, 2 need Load B, 1 needs the unit over USB too, 1
(ST-047) needs frame logs of entries that need a person.

Pre-flight: connected, output off, setpoints 12.0 V and 0.5 A, live mode
DC. No control command was sent in the run; the output stayed off. Sent:
bind, information requests, reading requests, and the release frame of
each close.

## ST-034 on Linux

The failure is the rate of 4 per second. Over this link the supply's
readings arrive at 2.5 to 3.3 per second (ST-013: 147 in 60 s here, 195
in the run of 00:08), so 86 in 30 s is what the link delivered. The
library did what SR-034 says for a transport that cannot keep up: it
delivered what it got and logged the warning. The entry's expected
result, "counts within 10 % of the rate", is not met at 4 per second.
The result stays a failure; it is not accepted as a deviation by this
record.

Likely cause, not shown: BlueZ's default connection interval of 30 to
50 ms (`conn_min_interval` 24 and `conn_max_interval` 40 in the kernel's
debug settings of the adapter), where each poll needs a write with its
response and a notification. Two tries with a shorter interval set for
the adapter did not get as far as a count: with 15 ms BlueZ aborted the
connect ("le-connection-abort-by-local"), and with 15 to 20 ms a write of
`0xC2` did not complete within 1 s and the link was reported lost. The
settings were put back to 24 and 40 afterwards. In the second try the
pre-flight and the test sent bind, information and reading requests; the
output stayed off.

## Other observations

- The log bridge reported 1073 and 1633 dropped records during the run
  (the TRACE lines of the Bluetooth dependencies, TODO.md). ST-017 step
  1 and ST-039 passed on the kept logs.
- `2026-10-05T002024-system-linux-ble-noperson.json` is the run's record
  file, written by the test run and then reduced and masked with the
  record writer's own functions of commit `44b2463` (the run itself was
  on the commit before): no address of another device, the supply's
  address with its maker's prefix only, no dependency lines.

## Open

ST-034 on Linux over Bluetooth (the rate of 4 per second). The entries
that need a person, a load or USB have not run on Linux.
