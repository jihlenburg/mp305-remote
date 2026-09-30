"""Recheck retained capture bytes without changing captures or accessing hardware.

Usage: audit_captures.py CAPTURE_DIRECTORY OUTPUT_JSON
"""
import hashlib
import json
import sys
from pathlib import Path

directory, output = map(Path, sys.argv[1:])
records = []
for path in sorted(directory.glob('*-ble-readonly.jsonl')):
    lines = path.read_text().splitlines()
    rows = [json.loads(line) for line in lines]
    events = [row for row in rows if 'hex' in row and 'dir' in row]
    for row in events:
        assert len(bytes.fromhex(row['hex'])) == row['len'], (path.name, row)
    replies = [row for row in events if row['dir'] == 'RX']
    identities = []
    for row in replies:
        data = bytes.fromhex(row['hex'])
        if row['char'] == 'af01' and data[:2] == b'\x31\xe1':
            assert len(data) == 18 and data[6:14] == b'MP305B\0\0'
            identities.append(dict(t=row['t'], system_version=list(data[2:6]), hardware_bytes=data[14:18].hex()))
    denied = [row for row in replies if bytes.fromhex(row['hex']) == b'\x19\xff']
    after = []
    if denied:
        first = denied[0]['t']
        for opcode in [0xc5, 0xc3, 0xe1]:
            match = next(row for row in replies if row['t'] > first and row['char'] == 'af01' and bytes.fromhex(row['hex'])[:2] == bytes([0x31, opcode]))
            after.append(dict(t=match['t'], opcode=hex(opcode), length=match['len'], hex=match['hex']))
    records.append(dict(file=path.name, sha256=hashlib.sha256(path.read_bytes()).hexdigest(), byte_length_checks=len(events), identities=identities, denial_times=[row['t'] for row in denied], first_selected_replies_after_denial=after))
output.write_text(json.dumps(dict(scope='Read-only reanalysis of existing immutable hardware captures. No new hardware run. Embedded result labels were not used as field truth.', captures=records), indent=2) + '\n')
print(len(records), 'existing captures rechecked')
