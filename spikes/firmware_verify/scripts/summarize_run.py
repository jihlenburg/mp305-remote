"""Summarize offline case groups and fingerprint their records."""
from pathlib import Path
import hashlib
import json
import platform
import sys

root = Path(__file__).resolve().parents[1]
names = ['emulation-results', 'reconstruction-comparison', 'control-emulation',
         'read-reply-comparison', 'extended-emulation', 'ble-emulation',
         'settings-worker-emulation', 'storage-emulation', 'rtos-emulation',
         'permission-emulation', 'worker-comparison']
groups = []
for name in names:
    path = root / 'exports' / (name + '.json')
    result = json.loads(path.read_text())
    assert result['failed'] == 0
    assert result['passed'] == len(result['cases'])
    groups.append(dict(file=path.name, passed=result['passed'], failed=result['failed'],
                       sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
summary = dict(scope='Offline research checks; not V-model or hardware verification.',
               system=platform.platform(), python=sys.version, groups=groups,
               passed=sum(g['passed'] for g in groups), failed=0)
(root / 'exports/run-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
print(summary['passed'], 'offline checks passed')
