#!/usr/bin/env python3
"""Stage an offline verification run outside the repository.

Firmware and generated binaries remain in a new scratch directory.
Existing analysis workspaces are never overwritten.
"""
import argparse
import hashlib
import json
import shutil
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--scratch', type=Path, required=True)
parser.add_argument('--firmware', type=Path, required=True)
parser.add_argument('--plain', type=Path, help='Optional earlier WebLink plain image')
args = parser.parse_args()
spike = Path(__file__).resolve().parents[1]
repository = spike.parents[1]
target = args.scratch.resolve()
if target == repository or repository in target.parents:
    parser.error('The scratch directory must be outside the repository.')
if target.exists():
    parser.error('Use a new scratch directory; existing analyses are preserved.')
firmware = args.firmware.read_bytes()
digest = hashlib.sha256(firmware).hexdigest()
if digest != '4991311993065586c2c8004bcef060945492751eda98c4d537a6eb19306170f9':
    parser.error('Firmware hash differs from the analyzed MP305B V51 container.')
target.mkdir(parents=True)
for name in ['scripts', 'reconstructed', 'notes']:
    shutil.copytree(spike / name, target / name, ignore=shutil.ignore_patterns('__pycache__', '*.pyc'))
for name in ['inputs', 'exports', 'logs']:
    (target / name).mkdir()
(target / 'inputs/MP305B-V51.fwd').write_bytes(firmware)
if args.plain:
    shutil.copy2(args.plain, target / 'inputs/MP305B-V51.plain.bin')
(target / '.mp305-offline-scratch').write_text('Prepared by prepare_run.py; no device I/O.\n')
sources = {str(p.relative_to(target)): hashlib.sha256(p.read_bytes()).hexdigest()
           for directory in ['scripts', 'reconstructed', 'inputs']
           for p in sorted((target / directory).rglob('*')) if p.is_file()}
(target / 'exports/run-inputs.json').write_text(json.dumps(sources, indent=2) + '\n')
print(target)
