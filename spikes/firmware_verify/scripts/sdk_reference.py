#!/usr/bin/env python3
"""Decode the supplementary WCH v1.8 reference, retaining separate provenance."""
from pathlib import Path
import re,struct,json,hashlib
root=Path(__file__).resolve().parents[1]
mem={};base=0
for l in (root/'reference/CH58xBLE_ROMx-v1.8.hex').read_text().splitlines():
 a=bytes.fromhex(l[1:]);assert sum(a)&255==0
 n=a[0];off=int.from_bytes(a[1:3],'big');typ=a[3]
 if typ==4:base=int.from_bytes(a[4:4+n],'big')<<16
 elif typ==2:base=int.from_bytes(a[4:4+n],'big')<<4
 elif typ==0:
  for j,v in enumerate(a[4:4+n]):mem[base+off+j]=v
lo=min(mem);hi=max(mem)+1;assert lo==0x40000 and hi<=0x70000;blob=bytes(mem.get(i,255) for i in range(lo,hi))
(root/'reference/wch-sdk-rom-v1.8.bin').write_bytes(blob)
h=(root/'reference/CH58xBLE_ROM-v1.8.h').read_text(errors='replace').replace('\\\n','')
rows=[]
for line in h.splitlines():
 m=re.match(r'#define\s+(\w+)\s+.*BLE_LIB_JT\((\d+)\)',line)
 if m:
  name,index=m[1],int(m[2]);slot=0x40034+index*4;target=struct.unpack_from('<I',blob,slot-lo)[0];rows.append((slot,target,name))
(root/'exports/wch-sdk-api.tsv').write_text('slot\ttarget_in_sdk_reference\tname\n'+''.join(f'{a:08x}\t{b:08x}\t{n}\n' for a,b,n in rows))
(root/'exports/wch-sdk-reference.json').write_text(json.dumps({'source':'https://github.com/openwch/ch583/tree/1e6af6a4299de36dfdd97e5791989a3a97981847/EVT/EXAM/BLE/LIB','base':hex(lo),'end_exclusive':hex(hi),'size':len(blob),'sha256':hashlib.sha256(blob).hexdigest(),'status':'Supplementary vendor v1.8 library, not present in ISDT FWD. Exact bytes installed on the unit are unverified.','api_entries':len(rows)},indent=2)+'\n')
print(hex(lo),hex(hi),len(rows))
