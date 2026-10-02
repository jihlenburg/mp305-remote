# Verification record: integration inspection, packaging and documentation

Date: 2026-10-02. Level: integration (IT-042). Method: inspection.

Commit: uncommitted. Diff summary: none in the packaging files.

The inspection was made by a delegated agent that read the files without
changing them and gave file and line for every point; its tables were
checked in the main session, and the points that the fixes of this commit
touch were inspected again there on the final tree.

## IT-042 (AR-042): pass with the note below

| Point | Result |
|---|---|
| The macOS bundle's `Info.plist` declares `NSBluetoothAlwaysUsageDescription` | present |
| The wheel matrix: CPython 3.10 and later (abi3), macOS 13 arm64 and x86_64, manylinux_2_35 x86_64 and aarch64, Windows x86_64 | present, note 1 |
| The `.pyi` stub and `py.typed` ship with the package | present |
| The bench-safety note in the app's README and in the library's README | present |
| The app's connection screen shows the note and links to it | present |

## Notes and open points

1. SR-036 names Windows 10 22H2 as the minimum; a wheel tag cannot
   express a Windows version, and the matrix builds on `windows-latest`.
   The minimum is stated in the library's README. IT-042's wording says
   so in the drafted revision.
2. The wheel workflow has never run; the bundle script has not been run
   beyond a syntax check (record `unit-app`, note 7).
