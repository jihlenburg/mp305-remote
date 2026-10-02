#!/bin/sh
# Scans for Bluetooth LE advertisements for 15 s with BlueZ and prints what
# it knows about every device whose name has the MP305B layout. No
# connection is made. Run as root in the guest.
set -eu
systemctl start bluetooth
sleep 2
date -u +%Y-%m-%dT%H:%M:%SZ
bluetoothctl --timeout 15 scan le > /tmp/mp305-scan.txt 2>&1 || true
bluetoothctl devices | while read -r _ addr name; do
    case "$name" in
        ????MP30*)
            grep -a "$addr" /tmp/mp305-scan.txt | sed 's/\x1b\[[0-9;]*m//g'
            bluetoothctl info "$addr"
            ;;
    esac
done
echo "devices seen: $(bluetoothctl devices | wc -l)"
