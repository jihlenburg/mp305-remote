# DD: csv module of `mp305-core`

Status: approved (G4 csv, user, 2026-10-01, revision 2; revision 3 approved 2026-10-01)

Refines AR-034 of [3-architecture.md](../3-architecture.md) (approved at
G3). The module writes readings in the one CSV format of SR-037 to any
`std::io::Write` sink the product opens, so that the app's recording and
the library's helper produce byte-identical files. It opens no files and
knows nothing about the device. Its two pure functions, `header()` and
`format_row()`, are the whole format; the `Writer` only moves their
output to a sink, and the Python helper `to_csv()` of AR-040 formats every
row through the native `format_row` (section 3, decision 1), so no second
implementation of the format exists. Coverage target 85 % (ADR-0008, "rest
of `mp305-core`"). Revision 2 resolves the independent review of revision
1 (LOGBOOK, "Store, csv and discovery design reviews").

Rust module tree: `mp305_core::csv` (one file, `//! Implements:
DD-CSV-nnn`) and `mp305_core::civil` (one file, the calendar conversion
and the two RFC 3339 formatters, specified and tested here as DD-CSV-003;
`session::texts::rfc3339` switches to it once the session implementation
has landed, an editorial change to DD-SESS-061 recorded in section 3).
The input is `session::TimedReading` (DD-SESS-004).

## 1. The format and the writer

| ID | Design item | Refines | Status | Rationale |
|---|---|---|---|---|
| DD-CSV-001 | `header() -> &'static str` is `time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n`. `format_row(reading: &TimedReading, origin: SystemTime) -> String` is one row with its `\n`. `Writer<W: Write>::new(sink: W) -> io::Result<Writer<W>>` writes the header and flushes, with the `t_s` origin unset; `Writer::with_origin(sink: W, origin: SystemTime) -> io::Result<Writer<W>>` fixes the origin in advance. `write(&mut self, reading: &TimedReading) -> io::Result<()>` sets the origin to `reading.wall` if unset, builds the row with `format_row`, sends it with one `write_all`, then `flush`es; `rows()` (a `u64`, `saturating_add`) counts a row once its `write_all` succeeded, even if the flush then fails; after an error the writer stays usable and a partial line may remain in the sink, which the product's own recovery (a new file) handles. `rows(&self) -> u64`, `into_inner(self) -> W`. Errors are the sink's `io::Error`, unchanged; the module adds no `Error` variant. The app passes the `wall` of the latest reading when the user starts recording as the origin, not `SystemTime::now()`, because `wall` is derived from the session's instant origin (DD-SESS-004) and a clock step between the two would shift every `t_s`. | AR-034 | approved | SR-037: one header, one row per reading, flushed at least once per second (AR-034 says after each row, which is stricter and costs nothing at 4 rows per second). I/O errors stay `io::Error` because the sink is the product's file, not the device. One `write_all` per row keeps a failed write from splitting a row across two attempts. |
| DD-CSV-002 | The row, fields in header order, separated by `,`, terminated by `\n`, UTF-8, `.` as the decimal point, no quoting (no field can contain `,`, `"` or a line break). Both time columns come from the same integer: `ms = milliseconds since the Unix epoch of reading.wall`, truncated (a time before the epoch is 0). `time_iso` is `civil::rfc3339_millis(ms)` (`2026-10-01T10:00:00.250Z`). `t_s` is the signed difference of `ms` and `origin_ms` (`u64::abs_diff`, the sign from a comparison; `ms` itself from `Duration::as_millis` converted with `u64::try_from`, saturating at `u64::MAX`) printed as `<sign><d / 1000>.<d % 1000 as three digits>` with integer division and remainder on the absolute value (`12.250`, `-1.000`, and `0.000` never `-0.000`). The electrical columns come from the raw integers of `reading.reading.raw`, not from floats: `voltage_V` and `set_voltage_V` are `raw / 100` and `raw % 100` as `<int>.<two digits>` (`13.00`); `current_A` and `set_current_A` are `raw / 1000` and `raw % 1000` as `<int>.<three digits>` (`1.000`); `power_W` is `raw / 100` and `raw % 100` as `<int>.<two digits>`. `output` is `1` or `0` from `reading.output_on`; `mode` is `reading.regulation` as `off`, `cv`, `cc`, `held_above` or `unknown_<n>`; `faults` is `reading.faults.iter()` mapped through `Fault`'s `Display`, in bit order, joined with `;`, empty when none (`reversed output;over current`). | AR-034 | approved | SR-037 names the columns and the decimal point; the precisions are the device's resolutions (10 mV, 1 mA, device-model.md 8), and the integer route cannot produce a rounding artefact; `mode` is SR-033's `mode` (the regulation mode) in a lowercase spelling that no spreadsheet reinterprets (section 3, decision 2); `;` inside the faults field keeps the file comma-separated without quoting. |
| DD-CSV-003 | `civil`: `from_unix(seconds: u64) -> Civil { year: i64, month: u8, day: u8, hour: u8, minute: u8, second: u8 }` (proleptic Gregorian, UTC, Howard Hinnant's days-to-civil algorithm; under `arithmetic_side_effects` every integer `+`, `-` and `*` is written as a `checked_*`, `saturating_*` or `wrapping_*` method, and only `/` and `%` by a non-zero literal appear as operators); `rfc3339(at: SystemTime) -> String` at second precision with a `Z` suffix (`2026-10-01T10:00:00Z`); `rfc3339_millis(ms: u64) -> String` and `rfc3339_millis_of(at: SystemTime) -> String` with three fraction digits, truncated (`2026-10-01T10:00:00.250Z`). A time before the epoch formats as the epoch. | AR-034, AR-028 | approved | A spreadsheet or pandas parses this form directly; std has no calendar, and about 25 lines of tested arithmetic are cheaper than a dependency. One module serves the CSV, the marker text (DD-SESS-061) and the Python reading's ISO text. |

## 2. Unit test specification

Tests live next to the code under `#[cfg(test)]`. The reading fixture is
`protocol::fixtures::C3_CAPTURE` parsed with `telemetry::parse` and wrapped
in a `TimedReading` with the given `wall` (the fixtures module arrives
with the session implementation; the csv implementation follows it). The
capture decodes to `out_state` 0, voltage 0, current 0, power 0, setpoints
1300 and 1000, output 0, `chargeError` 0. A reading with other values is
built from a `RawReading` with the named fields set and
`Reading::from_raw`. A "counting sink" is a `Write` wrapper over a
`Vec<u8>` that counts `flush` calls and can be told to fail its next
`write` or its next `flush`.

| UT | Verifies | Input | Expected result | Test |
|---|---|---|---|---|
| UT-CSV-001 | DD-CSV-001 | `Writer::new(counting sink)`; no rows. | The sink holds exactly `header()` and `header()` is the line of DD-CSV-001; `flush` was called once; `rows() == 0`; `into_inner` returns the sink. | `crates/mp305-core/src/csv.rs` |
| UT-CSV-002 | DD-CSV-002 | `Writer::new`; write the capture reading at `wall` 2026-10-01T10:00:00.250Z, then the capture with `chargeError` bits 0 and 5 at 10:00:00.500Z. | The two rows are exactly `2026-10-01T10:00:00.250Z,0.000,0.00,0.000,0.00,13.00,1.000,0,off,` and `2026-10-01T10:00:00.500Z,0.250,0.00,0.000,0.00,13.00,1.000,0,off,reversed output;over current`, each with `\n`; `flush` called three times; `rows() == 2`. | `crates/mp305-core/src/csv.rs` |
| UT-CSV-003 | DD-CSV-002 | `Writer::with_origin(sink, 10:00:00Z)`; write readings at 10:00:12.250Z and at 09:59:59.000Z; a reading with `output` 1 and `out_state` 2 (`Cc`); one with `out_state` 7; one at `wall` 10:00:00.2505Z with the origin 10:00:00Z; one with `out_state` 1 (`Cv`) and one with `out_state` 3 (`HeldAboveSetpoint`). | `t_s` `12.250` and `-1.000`; `output` `1`; `mode` `cc` and `unknown_7`; `mode` `cv` and `held_above` for the last two; the row at 10:00:00.2505Z has `time_iso` ending `.250Z` and `t_s` `0.250` (both truncated). | `crates/mp305-core/src/csv.rs` |
| UT-CSV-004 | DD-CSV-002 | Readings from a `RawReading` with voltage 1234, current 5, power 617, and with 65535 in all three. | `12.34,0.005,6.17` and `655.35,65.535,655.35` in the three measured columns. | `crates/mp305-core/src/csv.rs` |
| UT-CSV-005 | DD-CSV-003 | `civil::from_unix` of 0, of 951782400 (2000-02-29), of 1790848800; `rfc3339_millis` of 0, of 1709251199999 (2024-02-29T23:59:59.999Z), of 1790848800000; `rfc3339` of a time before the epoch; `rfc3339_millis_of(10:00:00.0004Z)`. | `1970-01-01 00:00:00`, `2000-02-29 00:00:00`, `2026-10-01 10:00:00` as `Civil` values; `1970-01-01T00:00:00.000Z`, `2024-02-29T23:59:59.999Z`, `2026-10-01T10:00:00.000Z`; `1970-01-01T00:00:00Z`; `2026-10-01T10:00:00.000Z` (truncated). | `crates/mp305-core/src/civil.rs` |
| UT-CSV-006 | DD-CSV-001 | A sink that fails its next `write` with `io::Error::other("disk full")`; `write(reading)`; then a good write. Then a sink whose next `flush` fails; `write(reading)`. | `Err` with that text and `rows()` unchanged; the next write succeeds and `rows() == 1`; the flush error is returned and `rows()` still grew by one. | `crates/mp305-core/src/csv.rs` |
| UT-CSV-007 | DD-CSV-002 | Every `Fault` variant and `Unknown(12)` in one reading (bits 0 to 8 and 12 set). | The `faults` field lists the nine names in bit order then `unknown fault bit 12`, joined with `;`, containing no `,`. | `crates/mp305-core/src/csv.rs` |

## 3. Decisions for G4

| # | Decision | Options | Recommendation |
|---|---|---|---|
| 1 | How the Python helper `to_csv()` (AR-040, "pure Python package") uses this module without a second implementation of the format. | (a) `mp305-py` exposes `csv_header()` and `format_csv_row(reading, origin)` natively; `to_csv()` stays in Python, opens the file with `encoding="utf-8", newline=""` (so Windows writes `\n`, not `\r\n`) and passes the origin explicitly (the first reading's wall, or the user's choice), so the origin rule has one home too; it writes what the native functions return. (b) A native `CsvWriter(path)` class over `std::fs::File`, and `to_csv()` wraps it. | (a): the file handling stays in Python where the user sees it, and the format has one home. Recorded here for the mp305-py DD; AR-040 is unchanged. |
| 2 | The user-visible spellings: `mode` as `off`, `cv`, `cc`, `held_above`, `unknown_<n>` (SR-033's enum names are `OFF`, `CV`, `CC`, `HELD_ABOVE`, `UNKNOWN`; `RegulationMode`'s `Display` is for logs), and `;` between fault names. | (a) As drafted (lowercase, no spaces, `;`). (b) SR-033's uppercase names and `;`. (c) A quoted, comma-separated faults field. | (a): lowercase identifiers survive every spreadsheet and script untouched, and `;` avoids quoting rules. |
| 3 | The calendar conversion moves from `session::texts` (DD-SESS-061) to `crate::civil`, owned by this DD. | (a) As drafted, with an editorial note on DD-SESS-061 after the session implementation lands (`texts::rfc3339` becomes a call into `civil`). (b) Keep it in `session::texts` and have `csv` call a `pub(crate)` helper there. | (a): the function serves three callers and belongs to neither session nor csv. |

## 4. Revisions

| Rev | Date | Change | Approved by |
|---|---|---|---|
| 1 | 2026-10-01 | First draft for G4 of the csv module | superseded by rev 2 |
| 2 | 2026-10-01 | Independent review resolved: `header()` and `format_row()` as the pure format for the Python helper (decision 1); both time columns from one truncated millisecond value and `t_s` formatted with integer arithmetic; the electrical columns from the raw integers; one `write_all` per row and the `rows()` rule after an error; the origin recommendation for the app; the `civil` module owned here (decision 3); literal rows in UT-CSV-002; UT-CSV-003 built from `RawReading`; the non-zero formatting test UT-CSV-004; the spellings put to the user (decision 2); `io::Error::other`. From the re-check: the Python file mode and explicit origin in decision 1, the exact lint rule and `abs_diff` for `t_s`. | user, 2026-10-01 (G4 csv) |
| 3 | 2026-10-01 | UT-CSV-003 gains the `cv` and `held_above` spellings of the mode column, which no entry covered. No design item changed. | user, 2026-10-01 |
