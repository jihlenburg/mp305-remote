# Verification record: integration inspection, the USB HID transport glue

Date: 2026-10-02. Level: integration (IT-017). Method: inspection.

Commit: `6e8ed18` (the run was made on the tree that this commit holds). Diff summary: none in `transport/hid.rs` and
`transport/hid_report.rs`.

The inspection was made by a delegated agent that read the files without
changing them and gave file and line for every point; its tables were
checked in the main session, and the points that the fixes of this commit
touch were inspected again there on the final tree.

## IT-017 (AR-017): pass against the approved transport design, with the notes below

| Point | Result |
|---|---|
| No `AA` handling and no checksum handling in the transport | present |
| No length handling | differs, note 1 |
| Reports are built from `protocol::hid::encode`; the stream bytes go to `protocol::hid::Decoder` | present |
| Output reports `01 n bytes`, input report 2 | present |
| One write job per frame keeps its reports together | present |
| Device errors are reported as transport errors | differs, note 2 |
| `protocol::hid` run as the framing test (IT-010) | pass (record `integration-automated`) |
| The behaviour on the supply is recorded by ST-040 | referenced in the code; no system-level record exists yet |

## Notes and open points

1. The report form that AR-017 itself gives (`01 n bytes`, at most 62
   stream bytes) is packed and unpacked in the sibling file
   `transport/hid_report.rs`, and `hid.rs` compares the bytes written with
   the report length. Neither is frame-length handling; the entry's
   wording is corrected in the drafted revision.
2. A failed or short write is `Error::Transport`. A read error is logged
   and ends the I/O thread, which the link sees as a closed link. Same
   correction.
3. ST-040 has not been run; it needs the supply over USB.
