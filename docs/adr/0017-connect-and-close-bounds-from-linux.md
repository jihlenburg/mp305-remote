# ADR-0017: Bounds for connect and close after the first runs on Linux

- Status: Accepted
- Date: 2026-10-04
- Decided by: user, on the agent's recommendation (2026-10-04, after ST-013 on a native Linux machine; the reviewed revision approved the same day)
- Related: AR-014, DD-PROTO-060, DD-LINK-040, DD-LINK-041, DD-DISC-011,
  IT-014, LOGBOOK 2026-10-04 ("ST-013 on halobox with the user at the
  supply: findings on Linux" and "Measurements and decisions for the
  bounds on Linux"), record `2026-10-04-system-linux-ble-halobox.md`

## Context

The first connections from Linux (the user's machine halobox, Ubuntu
26.04.1, BlueZ 5.85) showed three things that the runs on macOS had not.
The numbers are in the two LOGBOOK entries named above.

1. Every close failed with "the close did not complete within 1.0 s". The
   link bounds the close of the transport with the reply bound of 1 s
   (DD-LINK-041). A plain disconnect took 2.1 to 2.8 s in ten
   measurements on two adapters. The reason is in BlueZ itself, read in
   its source and not measured: a disconnect request first arms a timer
   of 2 s (`DISCONNECT_TIMER`, `src/device.c`, release 5.85), and the
   `Disconnect` call returns when the link is gone.
2. The connect, bounded with 10 s, was too slow through the machine's
   built-in adapter: plain connects took 15.6 s in one run and 15.7, 2.8,
   0.8 and 3.3 s in a second. Through a USB dongle on the same machine
   they took 0.8 to 2.1 s. The Linux kernel gives up creating an LE link
   after 20 s (`HCI_LE_CONN_TIMEOUT`, `include/net/bluetooth/hci.h`, read
   in release 6.12, not measured).
3. After a connect that the library had given up, the next scan did not
   find the supply. The library asks the OS to cancel such a connect, but
   on a spawned task (DD-DISC-011, revision 6). A program that ends right
   after the error, as a test run does, never gets that request out.
   BlueZ then completes the connect, and the supply stops advertising.

The review of the drafted revision found a fourth, in the code: a connect
that fails after the OS link is up (a failed service discovery or
subscription) leaves that link up, since only the check of the MTU
disconnects. On Linux the supply then stays connected and silent as in
point 3.

A fifth observation needs no design change: with two Bluetooth adapters
the library uses the first one the OS lists (DD-DISC-010), while an
identifier on Linux names one adapter, so the supply can be "not found".

## Decision

1. The close of the transport gets its own bound, `timing::CLOSE` of 5 s,
   on every platform. The link uses it where it used the reply bound
   (DD-LINK-040 step 5 and DD-LINK-041).
2. `timing::CONNECT` is 20 s instead of 10 s. It bounds the OS connect
   together with the service discovery and the subscriptions.
3. When that connect expires or fails, the library waits for the cancel
   at the OS (the peripheral's `disconnect`), bounded with
   `timing::CLOSE`, before it returns the error. The spawned best-effort
   cancel stays for a connect future that is dropped. The bound on a
   connect as a whole becomes `FIND + CONNECT + CLOSE`, 35 s
   (DD-DISC-011).
4. One Bluetooth adapter is the supported setup. The README says that the
   library uses the first adapter and that others are to be disabled or
   unplugged. No code changes for this.

## Alternatives considered

- A close bound of 3 s: the slowest disconnect measured was 2.84 s, so a
  loaded machine could exceed it.
- Keeping 1 s for the close: every close on Linux would report an error.
- Not waiting for the OS to finish the disconnect: BlueZ offers no call
  that returns earlier, and a close that returns before the link is gone
  would tell the caller the supply is free when it is not.
- Keeping 10 s for the connect and naming the dongle as the adapter for
  Linux: the library would stay unreliable with built-in adapters like
  the one measured.
- A connect bound of 30 s: the kernel gives up creating the link at 20 s
  anyway. With 20 s, a link that needs the 15.7 s measured leaves about
  4 s for the service discovery and the subscriptions; a link that comes
  up later than that is cut by the bound, which is accepted.
- Keeping the cancel best effort: fine for a program that keeps running,
  wrong for a script that exits on the error.
- Disconnecting inside the transport's connect on every error instead of
  in the discovery glue: it would change the transport design as well,
  and the glue has to cancel after an expiry in any case.
- Using the adapter that the identifier names: more code in discovery,
  and a second adapter would be needed to verify it.
- A discovery filter for Bluetooth LE only on BlueZ, so that a scan
  listens the whole time instead of about half of it: `btleplug` 0.13
  sets the filter itself and offers no way to change it. Not pursued.

## Consequences

- On Linux a close takes about 2.5 to 3 s. On macOS and Windows nothing
  changes in practice, since their close is fast. The output-off and the
  release go out before the transport closes, each under its own bound,
  and a lost link is reported before its transport is closed, so the
  longer close bound touches neither the safety sequence nor the 4 s
  bound of the loss report.
- A connect that stalls after the supply was seen is reported after up to
  35 s instead of 20 s. Reconnection attempts come every 5 to 35 s.
- ST-043 and ST-050 expect a recovery within 10 s. The design never
  guaranteed that (attempts came every 5 to 20 s before), and a stalled
  connect now pushes the worst case further out. Both entries sit in the
  system tests' revision 13, which is pending; their tolerance is to be
  settled there (TODO.md).
- The app's own bounds stay as they are (`CLOSE_BOUND` 5 s,
  `SHUTDOWN_BOUND` 3 s). On Linux a close without switch-off of about 3 s
  fits the first. At exit a close still running after 3 s is dropped with
  the runtime, as before.
- Open, and not answered by this decision: on Linux the Bluetooth service
  owns the connection, so a link may outlive the process that opened it.
  The app's dropped close at exit and a killed Python process are
  designed on "the link drops, the supply clears the grant" (DD-APP-023,
  the py DD). Whether that holds on BlueZ is to be checked on hardware
  (TODO.md); until then it is unverified on Linux.
- The find bound stays 10 s. On Linux a discovery of 10 s scans for
  Bluetooth LE for about 5.3 s, and the built-in adapter of halobox
  missed the supply in one of eight scans. Left open (TODO.md).
- IT-014's list of literals grows by those of the two bounds and of
  their sum. The error texts keep the form each module has: whole
  seconds in discovery ("20 s", "35 s"), one decimal in the link
  ("5.0 s").
