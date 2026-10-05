#!/bin/sh
# Implements: DD-APP-040 (derived app icon formats).
#
# Run on macOS with ImageMagick and iconutil to refresh the committed icons
# from the accepted source artwork. Normal builds use the committed files.

set -eu
cd "$(dirname "$0")/.."

command -v magick >/dev/null
command -v iconutil >/dev/null
icons="crates/mp305-app/assets/icons"
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT HUP INT TERM
iconset="$work/mp305.iconset"
mkdir -p "$iconset"

# Resize directly from the source each time and retain transparent corners.
for size in 16 24 32 48 64 128 256 512 1024; do
    magick "$icons/source.png" -resize "${size}x${size}" -strip "$work/$size.png"
done
cp "$work/256.png" "$icons/icon.png"
cp "$work/512.png" "$icons/icon-512.png"
magick "$work/16.png" "$work/24.png" "$work/32.png" "$work/48.png" \
    "$work/64.png" "$work/128.png" "$work/256.png" "$icons/mp305.ico"

for size in 16 32 128 256 512; do
    cp "$work/$size.png" "$iconset/icon_${size}x${size}.png"
    retina=$((size * 2))
    cp "$work/$retina.png" "$iconset/icon_${size}x${size}@2x.png"
done
iconutil -c icns "$iconset" -o "$icons/mp305.icns"
echo "Updated PNG, ICO and ICNS assets in $icons"
