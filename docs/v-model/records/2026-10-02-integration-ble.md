# Verification record: integration inspection, the Bluetooth transport glue

Date: 2026-10-02. Level: integration (IT-016). Method: inspection.

Commit: `6e8ed18` (the run was made on the tree that this commit holds). Diff summary: none in `transport/ble.rs`.

The inspection was made by a delegated agent that read the files without
changing them and gave file and line for every point; its tables were
checked in the main session, and the points that the fixes of this commit
touch were inspected again there on the final tree.

## IT-016 (AR-016): pass against the approved transport design, with the notes below

| Point | Result |
|---|---|
| Notifications are enabled on AF01 and AF02 on every connect, the notification stream taken first | present |
| Each notification is framed on its own and tagged with its characteristic | present |
| No bind, policy, retry or timing logic in the glue | present |
| The truncated-notification check | differs, note 1 |
| Writes with response; no MTU request, the negotiated value is read | present |
| An OS disconnect is reported as a transport error | differs, note 2 |
| The behaviour on the supply is recorded by ST-008 and ST-039 | referenced in the code; no system-level record exists yet |

## Notes and open points

1. The code and DD-TRANS-010 fail the connect with `Error::Transport`
   when the negotiated MTU is below 74, so that no notification can
   arrive truncated; there is no per-notification check. AR-016 and
   IT-016 still describe the earlier idea. The corrected wording is
   drafted, approval pending.
2. An OS disconnect ends the reader, the guard turns that into a closed
   link and `link` reports `LossReason::Disconnected`; no `Error::Transport`
   is created. Same correction.
3. ST-008 and ST-039 have not been run; they need the supply.
