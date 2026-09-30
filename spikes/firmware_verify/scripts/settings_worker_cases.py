"""Check deferred settings normalization with UI callees explicitly stubbed."""
from emulate import *
from unicorn import UC_HOOK_CODE
results=[];ram=(ROOT/'inputs/main-initialized-ram.bin').read_bytes()
tables=[('limit',0x2d,0x778,5,1),('shutdown',0x33,0x77d,6,1),('slope',0x96,0x784,10,2),('ocp',0x98,0x798,6,2),('usb_line',0xa4,0x7a4,11,2)]
ui={0x4b9de,0x581ac,0x57204,0x4e8b2,0x564b4,0x4e5a6,0x5836c,0x57288,0x4037c,0x56fc0,0x56d0c}
def hook(u,a,size,data):
 if a in ui:u.reg_write(UC_ARM_REG_R0,0);u.reg_write(UC_ARM_REG_PC,u.reg_read(UC_ARM_REG_LR))
for name,off,t,n,width in tables:
 values=[int.from_bytes(ram[t+i*width:t+(i+1)*width],'little') for i in range(n)]
 for v in sorted(set([0,*values,*[x-1 for x in values if x>0],values[-1]+1])):
  m=Machine();m.uc.mem_write(0x1ffe0000,ram);m.uc.mem_write(STATE+0x48,b'\x01');m.uc.mem_write(STATE+off,v.to_bytes(width,'little'));m.uc.hook_add(UC_HOOK_CODE,hook);m.call(0x128a4)
  expected=next((x for x in values if x>=v),v);actual=int.from_bytes(m.uc.mem_read(STATE+off,width),'little');assert actual==expected,(name,v,actual,expected)
  results.append(dict(field=name,input=v,output=actual,table=values,pass_result=True))
(ROOT/'exports/settings-worker-emulation.json').write_text(json.dumps(dict(scope='Original ARM settings worker 0x128a4. UI callees replaced with no-op returns. Tables from original startup recovery. No UI rendering, persistence or hardware.',passed=len(results),failed=0,cases=results),indent=2)+'\n');print(len(results),'settings worker cases passed')
