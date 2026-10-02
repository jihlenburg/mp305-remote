# Verification record: integration inspection, the layout of the crates and the core's I/O

Date: 2026-10-02. Level: integration (IT-001, IT-002). Method: inspection.

Commit: `6e8ed18` (the run was made on the tree that this commit holds). Diff summary: the integration tests and the fixes listed in
the record `2026-10-02-integration-automated.md`; nothing of the layout changed.

The inspection was made by a delegated agent that read the files without
changing them and gave file and line for every point; its tables were
checked in the main session, and the points that the fixes of this commit
touch were inspected again there on the final tree.

## IT-001 (AR-001): pass

| Point | Result |
|---|---|
| The workspace has the three crates; `spikes` is excluded | present |
| `mp305-core` is a library only | present |
| `mp305-app` keeps its logic in `src/lib.rs` with a thin `main.rs` (one call of `mp305_app::ui::launch`) | present |
| `mp305-py` builds as `cdylib` and `rlib` | present |
| `python/mp305/` wraps `mp305._native`, which `pyproject.toml` names; the helpers are pure Python | present |
| `tests/integration/` exists and holds the Python integration tests | present |

## IT-002 (AR-002): pass with the note below

| Point | Result |
|---|---|
| `btleplug` only in `transport::ble` and the discovery glue | present, note 1 |
| `hidapi` only in `transport::hid` and the discovery glue | present, note 1 |
| No sockets in `mp305-core` (Tokio without `net` and `fs`) | present |
| `std::fs` only in `store` | present |
| Every device constructor goes through `Guarded` | present |
| The whole `mp305-core` suite passes with `MP305_HIL` unset | pass (record `integration-automated`) |

## Notes and open points

1. `transport/guarded.rs` names `btleplug::platform::Adapter`,
   `PeripheralId` and `hidapi::HidApi` in the signatures of
   `Guarded::connect_ble` and `Guarded::open_hid`, which call only
   `ble::Ble::connect` and `hid::Hid::open`. This is the approved transport
   design (the guard cannot be bypassed), and IT-002 and AR-002 say
   "no such use" outside the listed modules. The corrected wording is
   drafted (architecture revision 11, integration tests revision 10),
   approval pending.
2. AR-002 cited AR-042 for the CSV writer; it is AR-034 (editorial, in the
   same revision).
