#!/usr/bin/env python3
"""Export immutable image tables with processor addresses and raw bytes."""
from pathlib import Path
import json,struct
root=Path(__file__).resolve().parents[1];b=(root/'inputs/ble-riscv.bin').read_bytes()
def rd(a,n):
 if 0x1000<=a and a+n<=0x9680:return b[a-0x1000:a-0x1000+n]
 if 0x20002c40<=a and a+n<=0x20002f50:return rd(0x9318+a-0x20002c40,n)
 if 0x40000<=a and a+n<=0x6c780:return (root/'reference/wch-sdk-rom-v1.8.bin').read_bytes()[a-0x40000:a-0x40000+n]
 if 0x20002f50<=a<0x20006df0:return bytes(n)
 raise ValueError(hex(a))
def u32(a):return int.from_bytes(rd(a,4),'little')
def uuid(p):return '0x'+rd(p,2)[::-1].hex()
rows=[]
for service,start,count in [('AF00',0x20002c40,7),('DB00',0x20002cbc,4),('180A',0x20002d08,19)]:
 for i in range(count):
  a=start+16*i;r=rd(a,16);n=r[0];p=int.from_bytes(r[4:8],'little');v=int.from_bytes(r[12:16],'little');typ=uuid(p)
  row={'service':service,'index':i,'ram_address':hex(a),'uuid_length':n,'uuid':typ,'uuid_pointer':hex(p),'permissions':r[8],'initial_handle':int.from_bytes(r[10:12],'little'),'value_pointer':hex(v),'raw':r.hex()}
  if typ=='0x2800':row['service_uuid']=uuid(u32(v+4))
  if typ=='0x2803':row['properties']=rd(v,1)[0]
  if p>=0x40000:row['uuid_name_evidence']='UUID bytes read from separately sourced SDK v1.8 reference; pointer itself is in the ISDT image.'
  rows.append(row)
report=rd(0x8f4c,35);cfg=rd(0x8f70,41);dev=rd(0x8f9c,18)
assert dev[0:2]==b'\x12\x01' and cfg[0:2]==b'\x09\x02' and report[0:2]==b'\x05\x01'
usb={'report_descriptor_address':'0x8f4c','report_descriptor_data_offset':'0x12f4c','report_descriptor_hex':report.hex(),'configuration_address':'0x8f70','configuration_hex':cfg.hex(),'device_descriptor_address':'0x8f9c','device_descriptor_data_offset':'0x12f9c','device_descriptor_hex':dev.hex(),'vid':hex(int.from_bytes(dev[8:10],'little')),'pid':hex(int.from_bytes(dev[10:12],'little')),'reports':{'out':{'id':1,'bytes_after_id':63},'in':{'id':2,'bytes_after_id':63}},'firmware_tx_chunk_max':62}
ram=(root/'inputs/main-initialized-ram.bin').read_bytes()
limits=[{'index':i,'ram_address':hex(0x1ffe07e0+i*22),'u16_values':list(struct.unpack_from('<11H',ram,0x7e0+22*i))} for i in range(6)]
for name,obj in [('gatt-table.json',rows),('usb-descriptors.json',usb),('charger-limits.json',limits)]: (root/'exports'/name).write_text(json.dumps(obj,indent=2)+'\n')
print('Exported',len(rows),'GATT attributes, USB descriptors and six charger limit rows')
