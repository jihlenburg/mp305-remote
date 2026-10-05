# App icon integration

Date: 2026-10-06. Source: uncommitted over
`25c82a6b201fad6f3bd944d3c5696fe002b788c7`. Platform: macOS 27.0.1,
arm64. Transport: none; the app was left on its connection screen, without
scanning or connecting. No supply commands were sent.

App DD revision 8 records the user's acceptance of the icon preview and
request to integrate it. The diff adds the accepted source image and derived
PNG/ICO/ICNS files, the viewport icon and Linux app ID, Windows resource build
script, macOS bundle icon, Linux launcher, regeneration script and build
instructions. Existing root README edits are outside this change.

## Commands and results

- `scripts/generate_app_icons.sh`: pass. Resized the source without changing
  its artwork. Pillow decoded all files as RGBA; PNG and every ICO
  representation have transparent corner pixels. ICO sizes: 16, 24, 32,
  48, 64, 128 and 256 pixels. `iconutil -c iconset
  crates/mp305-app/assets/icons/mp305.icns -o
  target/icon-review/bundle.iconset` also decoded the ICNS successfully.
- `magick montage -font /System/Library/Fonts/Helvetica.ttc
  'crates/mp305-app/assets/icons/mp305.ico[0-5]' -background '#eeeeee'
  -tile 6x1 -geometry +12+12 target/icon-review/light.png`, repeated with
  `#202124` and `dark.png`: pass. Visually inspected the native 16 through
  128 pixel sizes on both backgrounds; terminal and DC silhouettes remain
  distinguishable, with clean transparent corners. The 16-pixel image is
  necessarily less detailed. Local contact sheet: `target/icon-review/sizes.png`.
- `cargo clippy -p mp305-app --all-targets -- -D warnings`: pass.
- `cargo fmt --all --check`: pass after formatting the launch expression.
- `cargo test -p mp305-app`: pass, 147 unit tests and three integration
  tests; existing UI snapshots match. Output: `target/icon-review/app-tests.log`.
- `python3 scripts/check_traceability.py`: regenerated with zero defects;
  `python3 scripts/check_traceability.py --check`: pass.
- `sh -n scripts/generate_app_icons.sh scripts/bundle_macos.sh`: pass.
- `plutil -lint crates/mp305-app/packaging/macos/Info.plist`: pass.
- `scripts/bundle_macos.sh`: pass, release binary built and bundle signed.
- `codesign --verify --strict 'target/release/bundle/MP305 Remote.app'` and
  `codesign -dv 'target/release/bundle/MP305 Remote.app'`: pass; ad hoc
  signature, identifier `de.ihlems.mp305-remote`, bound plist and resources.
- Parsed the built plist with `plistlib`: both version keys are `0.1.0`,
  `CFBundleIconFile` is `mp305.icns`, and the bundled icon bytes equal the
  checked-in asset.
- Opened the release bundle. Its native connection screen appeared, with
  Connect disabled. Navigated Finder to `target/release/bundle`; its gallery,
  thumbnail and information pane all display the accepted icon. Left the
  app open without a connection, and closed the verification Finder window.
- `git diff --check`: pass.

## Windows resource check on macOS

Invoked the actual compiled app build script, selected as the newest
`target/debug/build/mp305-app-*/build-script-build`, with working directory
`crates/mp305-app`. Used these environment values (other values inherited):

```text
CARGO_CFG_TARGET_OS=windows
CARGO_CFG_TARGET_ENV=msvc
CARGO_CFG_TARGET_ARCH=x86_64
HOST=aarch64-apple-darwin
TARGET=x86_64-pc-windows-msvc
CARGO_PKG_VERSION=0.1.0
CARGO_PKG_VERSION_MAJOR=0
CARGO_PKG_VERSION_MINOR=1
CARGO_PKG_VERSION_PATCH=0
CARGO_PKG_NAME=mp305-app
CARGO_MANIFEST_DIR=/Users/jihlenburg/mp305b/crates/mp305-app
OUT_DIR=/Users/jihlenburg/mp305b/target/icon-review/windows-resource
RC_PATH=/opt/homebrew/opt/llvm@22/bin/llvm-rc
```

The process returned success. Parsed each resource header using its data
length and header length, advancing with four-byte alignment: seven icon
resources (type 3), one icon group (type 14) and one version resource
(type 16). Local output: `target/icon-review/windows-resource/resource.res`
and `compile.log`. This verifies the build script's Windows branch and
icon resource compilation, not a Windows executable link or native desktop.

## Inspection results

| Specification | Result |
|---|---|
| UT-APP-020 | Pass for the changed launch glue: the compiled-in PNG is decoded before the worker, errors log and return failure, the viewport receives the decoded icon, the Linux app ID matches the desktop-file name. Existing close/menu/glue paths remain unchanged. |
| UT-APP-021 | Pass for icon assets, plist, build scripts, Linux launcher and installation paths, plus the macOS bundle build, signature and Finder demonstration. Native Windows/Linux appearance is not covered. |
| IT-042 | Pass for the changed packaging metadata by inspection: the Bluetooth usage key, platform instructions and original packaging fields remain present. Other products are outside this incremental check. |

## Automated regression results

Counts map passing test names to their existing specification tags. This is
an incremental icon verification, not a new claim that every manual unit or
integration procedure has been rerun.

| Specification | Result |
|---|---|
| IT-003 | Pass, 1 automated test. |
| IT-041 | Pass, 2 automated tests. |
| UT-APP-001 | Pass, 3 automated tests. |
| UT-APP-002 | Pass, 3 automated tests. |
| UT-APP-003 | Pass, 1 automated test. |
| UT-APP-004 | Pass, 1 automated test. |
| UT-APP-005 | Pass, 1 automated test. |
| UT-APP-006 | Pass, 7 automated tests. |
| UT-APP-007 | Pass, 12 automated tests. |
| UT-APP-008 | Pass, 1 automated test. |
| UT-APP-009 | Pass, 13 automated tests. |
| UT-APP-010 | Pass, 4 automated tests. |
| UT-APP-011 | Pass, 2 automated tests. |
| UT-APP-012 | Pass, 13 automated tests. |
| UT-APP-013 | Pass, 4 automated tests. |
| UT-APP-014 | Pass, 3 automated tests. |
| UT-APP-015 | Pass, 3 automated tests. |
| UT-APP-016 | Pass, 5 automated tests. |
| UT-APP-017 | Pass, 5 automated tests. |
| UT-APP-018 | Pass, 4 automated tests. |
| UT-APP-019 | Pass, 8 automated tests. |
| UT-APP-021 | Pass, 1 automated test. |
| UT-APP-022 | Pass, 3 automated tests. |
| UT-APP-023 | Pass, 13 automated tests. |
| UT-APP-025 | Pass, 7 automated tests. |
| UT-APP-026 | Pass, 3 automated tests. |
| UT-APP-027 | Pass, 7 automated tests. |
| UT-APP-028 | Pass, 3 automated tests. |
| UT-APP-029 | Pass, 1 automated test. |
| UT-APP-030 | Pass, 1 automated test. |
| UT-APP-031 | Pass, 2 automated tests. |
| UT-APP-032 | Pass, 4 automated tests. |
| UT-APP-033 | Pass, 2 automated tests. |
| UT-APP-034 | Pass, 1 automated test. |
| UT-APP-035 | Pass, 4 automated tests. |
| UT-APP-036 | Pass, 1 automated test. |
| UT-APP-037 | Pass, 1 automated test. |

## Limits

Native Windows Explorer/taskbar and Linux X11/Wayland launcher appearance
were not checked on those hosts. Coverage was not remeasured: runtime edits
are within the existing UI-glue exclusion; no non-rendering application
logic changed. Build-time resource handling is inspected by UT-APP-021.
No hardware, system or acceptance matrix was run.
