# Verification record: integration inspection, the timing constants

Date: 2026-10-02. Level: integration (IT-014). Method: inspection.

Commit: uncommitted. Diff summary: the literals found by this inspection replaced
by values derived from `protocol::timing`: the prompt bounds in
`crates/mp305-core/src/session/task.rs`, the scan default and range in
`crates/mp305-app/src/model.rs`, and the wait slice of the Python package
(`_native.WAIT_SLICE_S`, used in `python/mp305/_checks.py` and `device.py`).

The inspection was made by a delegated agent that read the files without
changing them and gave file and line for every point; its tables were
checked in the main session, and the points that the fixes of this commit
touch were inspected again there on the final tree.

## IT-014 (AR-014): pass after the fixes of this commit

| Point | Result |
|---|---|
| Every bound of AR-014 is a named constant in `protocol::timing` with a source comment (16 constants, `WAIT_SLICE` included) | present |
| No other module carries a bound as a duration literal | present after the fixes, notes 1 and 2 |
| `WAIT_SLICE` is used from `timing` by the binding and by the Python package | present |

The search covered every `Duration` constructor, `sleep`, `timeout` and
interval call and the integer literals 30, 70, 100, 500, 1000, 2000,
4000, 5000, 600, 600000, 10, 60 and 10000 in `crates/` (all three crates)
and in `python/mp305/`, split into production code and test code.

## Notes and open points

1. Found and fixed: `bound_s: 30` and `bound_s: 70` in the session's
   prompt events (now `timing::BIND` and `timing::REMOTE_PROMPT` in whole
   seconds); `SCAN_S_DEFAULT = 10` and `SCAN_S_RANGE = 1..=60` in the app's
   model (now from `timing::SCAN_DEFAULT`, `SCAN_MIN` and `SCAN_MAX`); the
   `0.1` of the Python package's own wait loops (now `_native.WAIT_SLICE_S`,
   a new constant of the native module next to the scan bounds). The
   native constant is an addition to the native API that the py DD is to
   name; the wording is to be put to the user.
2. Remaining hits, none of them a bound of AR-014 written as a duration:
   user texts that spell a bound out ("within 30 seconds", "every 5 s for
   up to 10 minutes"); `MAX_SECONDS = 60.0` in the binding, the general
   limit of float-second arguments; the fixture events of
   `_native.sample_events()` (test support); durations that AR-014 does
   not list (the HID read poll of 10 ms, the app's shutdown, close and
   frame-time bounds, the marker interval, `FRESH`); unit scaling,
   calendar arithmetic, byte lengths, UUIDs and log levels. About 600
   further literals sit in test code as scripted delays and expected
   values.
3. `timing::LINK_LOSS_REPORT` has no production use; the link design
   meets the 4 s by analysis and a test asserts it.
