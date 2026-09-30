#!/usr/bin/env python3
"""Execute the two main-image scatter-load routines to recover initial SRAM."""
from emulate import Machine,ROOT
import struct,json,hashlib
m=Machine();table=struct.unpack('<8I',bytes(m.uc.mem_read(0x83fa8,32)));rows=[]
for i in range(0,8,4):
 src,dst,n,fn=table[i:i+4];m.call(fn,src,dst,n)
 rows.append({'source':hex(src),'destination':hex(dst),'size':n,'function':hex(fn)})
b=bytes(m.uc.mem_read(0x1ffe0000,0xb5c))
(ROOT/'inputs/main-initialized-ram.bin').write_bytes(b)
(ROOT/'exports/main-scatter-load.json').write_text(json.dumps({'table_address':'0x83fa8','rows':rows,'initialized_ram_sha256':hashlib.sha256(b).hexdigest(),'method':'Offline execution of original ARM instructions with Unicorn; no device I/O.'},indent=2)+'\n')
print('Recovered',len(b),'initialized RAM bytes; zeroed BSS ends at',hex(table[5]+table[6]))
