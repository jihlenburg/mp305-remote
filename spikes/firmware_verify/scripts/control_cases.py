#!/usr/bin/env python3
"""Check original DC control behavior in synthetic memory, without device I/O."""
from emulate import Machine,STATE,ROOT
import struct,json
results=[]
def run(label,remote=1,mode=0,granted=1,connection=2,voltage=500,current=100,requested_mode=0,expect=0):
 m=Machine();m.uc.mem_map(0xe0000000,0x100000)
 m.uc.mem_write(STATE+0x30,bytes([mode]));m.uc.mem_write(STATE+0x42,bytes([granted]));m.uc.mem_write(STATE+3,bytes([connection]))
 frame=bytes([0xc8,remote])+struct.pack('<HH',voltage,current)+bytes([0,0,0,0,requested_mode,0])
 r=m.handler(0x1b7f4,frame)
 assert r==(b'' if expect is None else bytes([0xc9,expect])),(label,r)
 row={'case':label,'reply':r.hex(),'voltage_requested_raw':struct.unpack('<I',m.uc.mem_read(0x1fffa940,4))[0],'current_requested_raw':struct.unpack('<I',m.uc.mem_read(0x1fffa944,4))[0],'grant':m.uc.mem_read(STATE+0x42,1)[0],'requested_mode':m.uc.mem_read(STATE+0x31,1)[0]};results.append(row);return row
run('valid control')
run('not granted',granted=0,expect=1)
for mode in [1,2,3]:run(f'wrong active mode {mode}',mode=mode,expect=255)
run('invalid remote selector',remote=3,expect=255)
run('release remote',remote=0)
run('request remote over connection type 2',remote=2,granted=0)
run('request remote pending on connection type 1',remote=2,connection=1,granted=0,expect=None)
run('request remote pending without connection',remote=2,connection=0,granted=0,expect=None)
run('maximum voltage',voltage=3050)
run('above maximum voltage',voltage=3051,expect=255)
run('maximum current',current=5100)
r=run('later invalid current preserves changed voltage',voltage=1234,current=5101,expect=255);assert r['voltage_requested_raw']==1234 and r['current_requested_raw']==0
for mode in [1,2,3]:
 r=run(f'mode switch to {mode} skips voltage/current',requested_mode=mode,voltage=65535,current=65535);assert r['requested_mode']==mode and r['voltage_requested_raw']==0 and r['current_requested_raw']==0
run('invalid requested mode',requested_mode=4,expect=255)
(ROOT/'exports/control-emulation.json').write_text(json.dumps({'scope':'Original ARM C8 instructions, synthetic RAM and Cortex system registers. No hardware.', 'passed':len(results),'failed':0,'cases':results},indent=2)+'\n');print(len(results),'control cases passed')
