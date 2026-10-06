# ADR-0021: Unit identity by a nameplate in a program slot

- Status: Accepted
- Date: 2026-10-06
- Decided by: user, 2026-10-06 ("accept the ADR"); the implementation is
  for a release after 0.1.0
- Related: SR-004, SR-046, AR-029, AR-032, AR-033, DD-DISC-001, DD-DISC-006,
  DD-DISC-011, DD-SESS-001, DD-SESS-010, DD-SESS-042, DD-SESS-051,
  DD-STORE-004, DD-PY-040, DD-APP-009, DD-APP-015, ADR-0004, ADR-0019;
  `spikes/program_nameplate`, LOGBOOK 2026-10-06 ("A nameplate in a
  program slot"), device-model.md 1 and 9

## Context

The supply has no identity a host can read. Over Bluetooth the three unit
characters of the advertised name are a hash of the Bluetooth address, which
only the Bluetooth path sees. Over USB the identifier is the HID device
path, which changes with every plug, and the version reply holds the model
name, the hardware revision and a bootloader version, nothing per unit
(hardware, 2026-10-06). So the library cannot tell that a USB entry and a
Bluetooth entry are one supply, a session cannot find its supply again after
a replug except by assuming there is only one, and the unclean-exit marker
over USB needs a fixed key shared by every supply on USB. The code review of
2026-10-05 (R2, R3) resolved both strictly, because SR-004 forbids guessing.

The supply keeps programs in its serial flash, each with a 16-byte name and
a step count. `D4` lists them, and `D6` writes a header. Both work over both
transports, before the bind and without the remote-control grant. The spike
of 2026-10-06 wrote a header with a name and no steps over Bluetooth, read
it back over Bluetooth and over USB byte for byte, saw it survive a power
cycle and appear in the supply's program menu, and deleted it again. Every
frame matched the firmware notes. Settings (`C6`) have no spare field, and
every other persistent write is a functional table.

## Decision

1. A supply may carry a nameplate: a program with no steps whose name is
   `<label> #<token>`. The label is ASCII, chosen by the user, up to 11
   characters. The token is four characters the library draws at random
   when the nameplate is first written. The `#` marks the program as a
   nameplate. The library finds it by the marker in `D4` and never stores
   its slot number, so renumbering on the supply cannot break it.
2. The token is the identity; the label is for people. Renaming rewrites
   the same slot with the new label and the same token. Everything the host
   keeps about a unit is keyed by the token, so a renamed supply stays the
   same unit everywhere, and other hosts show the new label the next time
   they read the list. The first naming is the special case: a fresh token
   and the next free slot. Deleting the nameplate deletes the identity and
   is offered as "forget this supply". A list with two marked programs is
   an error that names both; the library picks neither.
3. The core gains the protocol operations `programs::list` (`D4`, `D5`)
   and `programs::header` (`D6`, `D7`), with fixture tests from the spike's
   captures. The session reads `D4` after `E0` at every connection, so its
   identity (the nameplate, if any, plus the transport-side identity) is
   known before `Ready`. `set_nameplate(label)` and `clear_nameplate()` are
   the only writes; they refuse while the output is on, since a header
   write switches the supply's output request off, and they write with the
   save flag set and the plain operation, which leaves no busy state.
4. The unclean-exit marker (SR-046) is keyed by the token when the supply
   has a nameplate; the rules of session DD revision 7 stay as the
   fallback. The store also keeps a cache from each operating-system
   identifier seen to the nameplate read behind it, so that a scan can show
   labels before any connection. The cache is advisory and never decides a
   connection on its own.
5. Discovery gains `peek(identifier)`: connect, read `E0` and `D4`, close.
   No bind, so no prompt on the supply, and no control command. With it:
   reconnection after a link loss peeks every cabled MP305B and keeps the
   one whose token matches the session's, so the restriction to exactly one
   supply on USB goes away; and `connect()` without an identifier may join
   one USB entry and one Bluetooth entry when the cache says they carry the
   same token, prefers USB, and verifies the token on the live connection
   before `Ready`, disconnecting and refusing on a mismatch. SR-004 is kept
   to the letter: the library connects only to a unit it has identified on
   the unit itself. Without a nameplate, R2 and R3 stay as they are.
6. The Python library accepts a label as a third kind of identifier,
   `Mp305.connect("Bench 1")`: a scan, then a peek of the candidates (USB
   first) until one carries that label. `Mp305.identity` returns the
   nameplate and the transport-side identity; `set_name(label)` names or
   renames; `clear_name()` forgets. Listing supplies and their names has
   two levels of certainty: `discover()` carries the cached label and token
   of every entry, instantly and from what the host remembers;
   `discover(identify=True)` peeks every entry and reads the nameplate from
   the supply itself (milliseconds over USB, a few seconds per supply over
   Bluetooth, no prompt, no control). Entries with the same token are one
   unit, and `units(found)` groups them, so a script can print each supply
   once with the transports it is reachable on. Neither lists what other
   programs are connected to; "connected" in this record means reachable.
7. In the app the friendly name becomes the nameplate: naming writes it to
   the supply, the name field in Details edits it, and the two entries of
   one unit collapse into one card with USB and Bluetooth as the choice
   underneath. After a scan the app peeks the USB entries at once and the
   Bluetooth entries in the background. A supply without a nameplate keeps
   the host-only name of app DD revision 5, with a button to write it to
   the supply.
8. Before the write path ships, one more spike on hardware covers a
   rejected header write (an id above 10, a full table) and a remote
   output-on after a write.

## Alternatives considered

- Encode an identity in a program's step values or in a PD profile: the
  values are functional, the profile writes carry the busy risk, and a name
  is user content by design, so the name is the right place.
- A pairing table on the host only (the user says once that two entries are
  one unit): no write to the supply, but the knowledge stays on one host,
  cannot be verified on the unit, and cannot survive a replug of a supply
  the host has not seen before.
- The Bluetooth unit characters as the identity: correct over Bluetooth,
  invisible over USB.
- Wait for ISDT to expose a serial number: no documentation exists and the
  firmware has none to expose.

## Consequences

- One program slot of ten is taken by the nameplate on a supply that has
  one, and the supply shows it in its program menu under the chosen name.
- Every connection sends one more read (`D4`, about 90 ms) before `Ready`.
- The identity model touches the protocol, session, store and discovery
  modules, the Python library and the app, and changes how SR-004 and
  SR-046 are met; the DD files of those modules and the two requirements
  get revisions. The ADR is accepted before any of that starts.
- The strict rules of R2 and R3 stay in force for supplies without a
  nameplate, so nothing in 0.1.0 changes.
- Size: about a week, a day each for the protocol operations, the session
  side, discovery with `peek`, and the app, half a day each for the store
  and the Python library, plus the spike of item 8.
