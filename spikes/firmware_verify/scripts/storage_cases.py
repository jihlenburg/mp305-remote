"""Observe original serial-storage command formatting with mocked bus functions."""
from emulate import *
from unicorn import UC_HOOK_CODE
results=[]
def run(addr,*args):
 m=Machine();events=[]
 def hook(u,a,size,data):
  r=[u.reg_read(x) for x in [UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2]]
  if a not in [0x15384,0x153e0,0x12d10,0x12cec,0x1f3cc]:return
  if a==0x12d10:events.append(['tx',bytes(u.mem_read(r[0],r[1])).hex()])
  elif a==0x12cec:events.append(['rx',r[1]]);u.mem_write(r[0],bytes(r[1]))
  elif a==0x1f3cc:events.append(['ready'])
  else:events.append(['select' if a==0x15384 else 'deselect',r[0],r[1]])
  u.reg_write(UC_ARM_REG_R0,1 if a==0x1f3cc else 0);u.reg_write(UC_ARM_REG_PC,u.reg_read(UC_ARM_REG_LR))
 m.uc.hook_add(UC_HOOK_CODE,hook);m.uc.mem_write(REQUEST,bytes(range(256))*3);ret=m.call(addr,*args);return ret,events
for addr,cmd in [(0x1bdc6,0xd8),(0x1bdf6,0x20)]:
 for offset in [0,0x160000,0x1f0000,0x7fffff]:
  ret,ev=run(addr,offset);tx=[x[1] for x in ev if x[0]=='tx'];expected=['06',bytes([cmd,(offset>>16)&255,(offset>>8)&255,offset&255]).hex(),'04'];assert tx==expected;results.append(dict(function=hex(addr),offset=hex(offset),events=ev,pass_result=True))
for offset in [0,0x162000,0x7fffff]:
 ret,ev=run(0x1bef8,offset,RESPONSE,31);assert [x for x in ev if x[0]=='tx']==[['tx',bytes([3,(offset>>16)&255,(offset>>8)&255,offset&255]).hex()]] and ['rx',31] in ev;results.append(dict(function='0x1bef8',offset=hex(offset),events=ev,pass_result=True))
for n in [1,255,256,257,600]:
 ret,ev=run(0x1bf3a,0x162000,REQUEST,n);tx=[x[1] for x in ev if x[0]=='tx'];chunks=[bytes.fromhex(tx[i+2]) for i in range(0,len(tx),4)];assert ret==1 and b''.join(chunks)==(bytes(range(256))*3)[:n] and all(len(c)<=256 for c in chunks);results.append(dict(function='0x1bf3a',length=n,events=ev,pass_result=True))
(ROOT/'exports/storage-emulation.json').write_text(json.dumps(dict(scope='Original ARM storage drivers; bus reads/writes, chip-select helpers and ready polling substituted. Verifies command formatting only; no storage chip accessed.',passed=len(results),failed=0,cases=results),indent=2)+'\n');print(len(results),'storage cases passed')
