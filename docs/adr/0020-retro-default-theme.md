# ADR-0020: Retro as the desktop app default

- Status: Accepted
- Date: 2026-10-05
- Decided by: user
- Related: DD-APP-030, DD-APP-031, DD-APP-034, DD-APP-035, UT-APP-034

## Context

App DD revision 6 initially kept Standard as the startup theme while the
Retro presentation and compact layout were reviewed. After reviewing the
integrated app and compact refinements, the user requested Retro as the
default and authorised documentation updates, a commit and a push.

## Decision

Start every new app window in Retro. Keep Standard available in Details.
Theme selection lasts for the current window and affects presentation only.
This supersedes the earlier Standard startup choice in app DD revision 6.

## Alternatives considered

- Keep Standard at startup: does not meet the user's requested default.
- Save the last selected theme: adds persistence that the user did not
  request and would make startup depend on an earlier selection.
- Remove Standard: unnecessary; both themes already share controls and tests.

## Consequences

The first screen uses the reviewed Retro frame and typography. The app's
control behavior and responsive thresholds stay unchanged. Update the
startup regression check and current documentation; preserve earlier
verification records as evidence of the versions actually checked.
