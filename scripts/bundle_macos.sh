#!/bin/sh
# Implements: DD-APP-040 (the macOS bundle).
#
# Builds the desktop app in release mode and makes the bundle
# target/release/bundle/MP305 Remote.app afresh, for local builds: the host
# architecture, an ad hoc signature, no hardened runtime, no Developer ID,
# no notarisation and no icon. Run it from anywhere in the repository; it
# stops at the first error.

set -eu

cd "$(dirname "$0")/.."

bundle="target/release/bundle/MP305 Remote.app"
plist="$bundle/Contents/Info.plist"

# 1. The release binary.
cargo build --release -p mp305-app

# 2. The bundle, made afresh.
rm -rf "$bundle"
mkdir -p "$bundle/Contents/MacOS" "$bundle/Contents/Resources"
cp target/release/mp305-app "$bundle/Contents/MacOS/mp305-app"
cp crates/mp305-app/packaging/macos/Info.plist "$plist"
cp crates/mp305-app/README.md "$bundle/Contents/Resources/README.md"

# 3. The package version of mp305-app, from cargo metadata.
version=$(cargo metadata --no-deps --format-version 1 | python3 -c '
import json, sys
packages = json.load(sys.stdin)["packages"]
print(next(p["version"] for p in packages if p["name"] == "mp305-app"))
')
if [ -z "$version" ]; then
    echo "bundle_macos.sh: no version for mp305-app in cargo metadata" >&2
    exit 1
fi
plutil -replace CFBundleShortVersionString -string "$version" "$plist"
plutil -replace CFBundleVersion -string "$version" "$plist"
plutil -lint "$plist"

# 4. The ad hoc signature, which binds the Info.plist (and its Bluetooth
# usage key) to the bundle, and its check.
codesign --force --sign - "$bundle"
codesign --verify --strict "$bundle"

echo "bundle_macos.sh: $bundle, version $version"
