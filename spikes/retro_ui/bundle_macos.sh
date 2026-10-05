#!/bin/sh
# Builds the isolated simulation preview, with no device transport.
set -eu
cd "$(dirname "$0")/../.."
CARGO_TARGET_DIR=target cargo build --release --manifest-path spikes/retro_ui/Cargo.toml
bundle="target/retro-preview/MP305 Retro Preview.app"
mkdir -p "$bundle/Contents/MacOS" "$bundle/Contents/Resources"
cp target/release/mp305-retro-preview "$bundle/Contents/MacOS/mp305-retro-preview"
cp spikes/retro_ui/assets/OFL-Antonio.txt "$bundle/Contents/Resources/"
cp crates/mp305-app/assets/fonts/OFL.txt "$bundle/Contents/Resources/OFL-B612.txt"
cp spikes/retro_ui/README.md "$bundle/Contents/Resources/"
cat > "$bundle/Contents/Info.plist" <<'PLIST'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0"><dict>
<key>CFBundleIdentifier</key><string>de.ihlems.mp305-retro-preview</string>
<key>CFBundleName</key><string>MP305 Retro Preview</string>
<key>CFBundleDisplayName</key><string>MP305 Retro Preview</string>
<key>CFBundleExecutable</key><string>mp305-retro-preview</string>
<key>CFBundlePackageType</key><string>APPL</string>
<key>CFBundleVersion</key><string>1</string>
<key>NSHighResolutionCapable</key><true/>
</dict></plist>
PLIST
codesign --force --sign - "$bundle"
codesign --verify --strict "$bundle"
