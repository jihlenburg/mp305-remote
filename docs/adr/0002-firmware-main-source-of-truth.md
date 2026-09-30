# ADR-0002: The device firmware is the main source of truth for the protocol

- Status: Accepted
- Date: 2026-09-29
- Decided by: user
- Related: ADR-0004, ADR-0010, [docs/research/](../research/)

## Context

ISDT offers two ways to control the MP305B: the Polying app (iOS, iPadOS,
macOS on Apple Silicon, Android) and a browser page, WebLink
(https://www.isdt.co/weblink/), which covers Windows and Linux in a
Chromium-based browser. ISDT publishes no command set, no SCPI support and no
API. The product page and the manual (a PDF without a text layer) say nothing
about the wire format.

WebLink is a JavaScript app that talks to the device directly from the
browser. Its code, which anyone can download, shows:

- USB: WebHID, device filter vendor ID `0x28E9` (10473, registered to
  GigaDevice) or HID usage page 1 with usage 4, reports sent with report ID 1.
- Bluetooth LE: Web Bluetooth, service `0xAF00` with characteristics `0xAF01`
  (commands and replies) and `0xAF02` (bind handshake and BLE module info).
  WebLink treats the link as connected only once both are found. It also
  requests service `0xFEE0` with characteristic `0xFEE1`, but only for
  bootloader firmware updates.

On the user's unit, the `0xFEE0` service is absent in normal operation
(LOGBOOK 2026-09-29, GATT table).

Earlier on 2026-09-29 the working decision was to take the protocol from
WebLink's JavaScript. The user replaced that the same day: the device
firmware is the main source of truth, and every other finding comes on top
of it (LOGBOOK 2026-09-29, "Firmware is the main source of truth").

## Decision

Take the protocol from the device firmware. That firmware is the main source
of truth. Write findings from WebLink, from hardware captures and from
anywhere else into `docs/research/` on top of it, with the file names and
code excerpts they came from. Mark each item as confirmed in code (read in
the device firmware, or in WebLink's JavaScript), confirmed on hardware
(observed on the user's unit) or inferred. Where the firmware and another
finding differ, the project uses the firmware. For sources other than the
device firmware, production code relies only on items confirmed on hardware,
or on inferred items that the relevant DD accepts explicitly with a TBD.
Information read from the device firmware is used to its fullest, with no
limit on what it covers (ADR-0010).

Raw hardware captures are stored once, in `docs/research/captures/`, and are
never edited after recording. Fixture tests embed the frames they need and
cite the capture file.

## Alternatives considered

- Taking the protocol from WebLink's JavaScript and treating the firmware as
  a later check: rejected on 2026-09-29. WebLink findings stay in the
  research notes, on top of the firmware.
- Sniffing Bluetooth or USB traffic from the Polying app: an observation
  that comes on top of the firmware. It supplies bytes and little structure.
- Decompiling the Polying macOS or Android app: rejected. That is the
  companion app, not the device firmware.
- Asking ISDT for documentation: worth trying in parallel, but the project
  cannot wait for an answer.

## Consequences

- The project follows the device firmware. A firmware update can change the
  protocol, so every capture and every hardware test run cites the firmware
  version. WebLink and other findings are compared with that firmware.
- The device reports its versions in the `0xE1` reply, over Bluetooth as well
  as USB: bytes 1 to 4 are the main firmware version (WebLink's "System
  Version") and bytes 13 to 16 are WebLink's "Firmware Version" (LOGBOOK
  2026-09-29, "Corrections, second round"). They are recorded in the LOGBOOK
  with the date, cited from there, and read again after any firmware update.
- ISDT publishes firmware through public update manifests. WebLink offers an
  update whenever the manifest lists a newer version, so users may update at
  any time. A changed firmware version triggers a re-run of the read-only
  spike and a comparison with earlier captures.
- WebLink's assets have hashed file names that change with each release. The
  research notes record which version was read. The original WebLink asset
  files stay out of the repository. Interoperability information gathered
  from them stays in.
- Decompiling the device firmware is fully allowed, under Directive
  2009/24/EC (2009/24/EG), so that the library and the desktop app
  interoperate with the device (ADR-0010). There is no limit on the
  information contained in that firmware, and it is used to its fullest.
  The firmware image stays out of the repository. Interoperability
  information reconstructed or gathered from it stays in the repository, in
  whatever form it takes.
