# ADR-0005: egui for the desktop app

- Status: Accepted
- Date: 2026-09-29
- Decided by: user
- Related: ADR-0003, ADR-0008

## Context

The desktop app needs a device picker, voltage and current setpoints, an
output switch, a live readout, a scrolling voltage, current and power chart,
and CSV recording. It must run on macOS, Linux and Windows. The user does not
need a terminal UI and described the app as a tool, so appearance matters
less than getting it working reliably.

## Decision

Build the app with egui through `eframe`, and draw the chart with
`egui_plot`.

## Alternatives considered

| Option | Why not |
|---|---|
| Tauri | Best-looking result, but the UI would be HTML and TypeScript, a second language to maintain. The Linux webview (WebKitGTK) renders differently from the others. |
| Slint | Native look, but no built-in chart widget. |
| Iced | Clean Elm-style architecture, but more structure and boilerplate than an immediate-mode UI for a small tool, and charts need a third-party crate or hand-drawn canvas code. |
| Dioxus | Rust only, but still a system webview, with the same Linux issues as Tauri. |
| Electron, Qt, GTK, Flutter | Too heavy, poor packaging outside Linux, or a third language. |

## Consequences

- The app is one Rust binary of a few MB with no webview, and looks the same
  on all three platforms.
- Device I/O must stay off the UI thread, or a slow Bluetooth reply would
  freeze the window. eframe repaints only on input or on request, so
  the I/O side must call `egui::Context::request_repaint()` after new data
  arrives. The concrete task and channel design is decided at gate G3 in
  docs/v-model/3-architecture.md.
- egui, eframe and egui_plot are pre-1.0 as well. Versions are pinned
  exactly, and upgrades are deliberate and logged in the LOGBOOK.
- The app looks like a developer tool. That look is intended.
- Rendering code is hard to unit test. Keep it thin, and put the logic
  (state, commands, CSV writing, chart buffers) in plain modules that are
  unit tested. ADR-0008 (proposed) sets how drawing code is excluded from
  coverage.
