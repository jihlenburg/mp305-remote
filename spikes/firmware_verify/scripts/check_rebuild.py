#!/usr/bin/env python3
"""Compare the fresh Ghidra rebuild's function entries with current exports."""
from pathlib import Path
import csv,json
root=Path(__file__).resolve().parents[1];rows=[]
for old,new in [('arm','arm'),('ble-final','ble'),('pd-tables','pd'),('sdk-v18','sdk')]:
 a=list(csv.DictReader((root/'exports'/old/'functions.tsv').open(),delimiter='\t'))
 b=list(csv.DictReader((root/'rebuild-validated/exports'/new/'functions.tsv').open(),delimiter='\t'))
 aset={f['address'] for f in a};bset={f['address'] for f in b}
 row={'canonical_export':old,'fresh_export':new,'canonical_functions':len(a),'fresh_functions':len(b),'only_canonical':sorted(aset-bset),'only_fresh':sorted(bset-aset),'same_entries':aset==bset,'decompiler_completed':all(f['decompiled']=='true' for f in b)};rows.append(row)
 # Entry stability, not byte-identical pseudocode, is the reproduction criterion.
 assert row['same_entries'] and row['decompiler_completed'],row
for p in (root/'rebuild-validated/logs').glob('*.log'):
 assert not any('ERROR' in line for line in p.read_text().splitlines()),p
(root/'logs/rebuild-comparison.json').write_text(json.dumps({'scope':'A complete fresh import and scripted refinement reproduced these entry sets. This checks reproducibility, not semantic correctness of every function.','images':rows},indent=2)+'\n')
print(json.dumps(rows,indent=2))
