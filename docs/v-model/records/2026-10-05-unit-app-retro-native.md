# Native app inspection with the lamp

Date: 2026-10-05. Source: uncommitted over
`a395da7f54481394ffa1ce398009ca9f9d3e739d`, the integrated Retro theme and
responsive layout described in the earlier app verification record.
Platform: macOS 27.0.1, arm64. Binary: the running release bundle at
`target/release/bundle/MP305 Remote.app`.

Transport: USB, endpoint `DevSrvsID:4295529386`. The app reports system
version 1.6.0.51 and no hardware revision over USB. The second reported
version, 2.0.2.0, is recorded in LOGBOOK 2026-10-05, "Lamp operated through
the real egui controls", with the earlier Bluetooth release-check reference.
No firmware update occurred in this check.

The user requested inspection of the running app. Earlier authorisation in
the same conversation permits switching the attached 12 V, 1 W LED lamp
on and off. Initial output was off, with 12.00 V and 0.200 A setpoints.
No setpoint or limit was changed. The existing 12 V lamp configuration was
used, rather than the generic unloaded-bench defaults.

## Procedure and observations

1. Inspected the running discovery screen at approximately 918 by 580
   content points. Both USB and Bluetooth entries were present. Device cards
   display the name and connection type; full identities remain in their
   accessible labels. Selected USB and clicked Connect. Connection succeeded.
2. Inspected connected readings, aligned decimal columns, setpoint fields,
   Set buttons, graph controls and the footer. Output was off with zero
   measured current and power. Setpoint fields showed 12.00 V and 0.200 A.
3. Clicked Output ON. Settled readings were 12.00 V, 0.095 A and 1.13 W,
   CV. Opened Details and inspected the device facts. Clicked Output OFF
   while Details remained open; output became off, current and power zero.
   The event log recorded acknowledgement after 13 ms.
4. Closed Details and resized through a tall compact window to the native
   minimum, 320 by 272 content points. Graphs disappeared. Measurement and
   setpoint rows stayed aligned; both output controls and the footer fit.
5. Clicked Output ON at minimum size and opened compact Details. Readings
   in Details showed 12.00 V, 0.095 A and approximately 1.14 W. Clicked
   Output OFF with Details open. The output became off and current and power
   returned to zero; acknowledgement took 23 ms.
6. Closed Details and restored the original window dimensions. Graphs
   returned with the on/off history collected during compact mode. Final
   readings were 0.00 V, 0.000 A and 0.00 W, with output off. The original
   setpoints remained 12.00 V and 0.200 A. Left the app connected and open.

## Supplemental results

| Specification | Result |
|---|---|
| UT-APP-029 | Pass for native USB selection and connection. Setpoint editing and recording were not repeated in this check. |
| UT-APP-030 | Pass for Output OFF remaining usable with Details open, at full and minimum sizes. |
| UT-APP-031 | Pass for the observed native reading, field and button alignment. Cosmetic finding: the output-off status redundantly reads `OFF · off`. |
| UT-APP-035 | Pass for native resizing, compact control visibility, retained setpoints and restored graph history. |

This supplements the automated results; it is not an acceptance test or a
system matrix run. No production code changed and no automated tests were
rerun. The redundant output-off label is recorded in TODO.md.
