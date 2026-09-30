#!/usr/bin/env python3
"""Restore the vendor container without the WebLink identity-word mutation."""
from pathlib import Path
import struct, hashlib, json, re
root=Path(__file__).resolve().parents[1]
b=(root/'inputs/MP305B-V51.fwd').read_bytes()
h=struct.unpack_from('<8I',b); key,check,appbase,datbase,apps,datas,baud,fast=h
assert len(b)==32+apps+datas and (apps+datas)%4==0
state=check; out=bytearray()
for (w,) in struct.iter_unpack('<I',b[32:]):
 out += struct.pack('<I',w^state); state=((state+key)^key)&0xffffffff
assert sum(w[0] for w in struct.iter_unpack('<I',out))&0xffffffff==check
app=out[:apps];data=out[apps:]
identity=struct.unpack_from('<I',app,28)[0]-appbase
assert app[identity:identity+4]==bytes.fromhex('33cc55aa')
prior=root/'inputs/MP305B-V51.plain.bin'
diffs=[]
if prior.exists():
 old=prior.read_bytes();assert len(old)==len(out)
 diffs=[i for i,(x,y) in enumerate(zip(out,old)) if x!=y]
 assert diffs==list(range(identity,identity+4))
images={'restored.bin':out,'main-arm.bin':app,'companion-data.bin':data,'pd-8051.bin':data[:0xb000],'ble-riscv.bin':data[0xb000:]}
manifest={'header':dict(zip(['key','checksum','app_base','data_base','app_size','data_size','baud','rapid_baud'],h)), 'identity_offset':hex(identity),'prior_plain_compared':prior.exists(),'prior_plain_differences':[hex(x) for x in diffs], 'images':{}}
for name,content in images.items():
 (root/'inputs'/name).write_bytes(content)
 manifest['images'][name]={'size':len(content),'sha256':hashlib.sha256(content).hexdigest()}
 strings=[]
 for m in re.finditer(rb'[\x20-\x7e]{5,}',content):strings.append(f'{m.start():08x}\t{m[0].decode()}')
 (root/'exports'/f'{name}.strings.tsv').write_text('\n'.join(strings)+'\n')
(root/'exports/restoration.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(manifest,indent=2))
