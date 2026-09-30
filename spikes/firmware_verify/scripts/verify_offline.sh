#!/bin/sh
# Run in an external directory created by prepare_run.py. No device I/O.
set -eu
MP305_SCRATCH=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$MP305_SCRATCH"
test -f .mp305-offline-scratch
MP305_PYTHON=${MP305_PYTHON:-python3}
"$MP305_PYTHON" scripts/restore.py > logs/restoration.log
"$MP305_PYTHON" scripts/recover_ram.py
case $(uname -s) in
  Darwin) MP305_LINK_FLAGS=-dynamiclib ;;
  *) MP305_LINK_FLAGS='-shared -fPIC' ;;
esac
# The filename is shared by the ctypes experiments on all platforms.
clang -std=c11 -Wall -Wextra -Werror -O2 $MP305_LINK_FLAGS reconstructed/protocol.c reconstructed/read_replies.c reconstructed/workers.c -o reconstructed/libprotocol.dylib
for MP305_CASE in emulate compare_reconstruction control_cases compare_read_replies extended_cases ble_cases settings_worker_cases storage_cases rtos_cases permission_cases worker_comparison
do
  "$MP305_PYTHON" "scripts/$MP305_CASE.py"
done
"$MP305_PYTHON" scripts/summarize_run.py
