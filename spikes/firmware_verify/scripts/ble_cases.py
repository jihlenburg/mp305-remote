"""Execute original RV32 bridge code with explicit SDK and I/O substitutes."""
from pathlib import Path
import struct,json
from unicorn import Uc,UC_ARCH_RISCV,UC_MODE_RISCV32,UC_HOOK_CODE
from unicorn.riscv_const import *
ROOT=Path(__file__).resolve().parents[1];IMAGE=(ROOT/'inputs/ble-riscv.bin').read_bytes();STOP=0x100000;REQ=0x20008000
class BLE:
 def __init__(self):
  self.u=Uc(UC_ARCH_RISCV,UC_MODE_RISCV32);self.u.mem_map(0,0x10000);self.u.mem_write(0x1000,IMAGE);self.u.mem_map(0x40000,0x1000);self.u.mem_map(STOP,0x1000);self.u.mem_map(0x20000000,0x20000)
  self.u.mem_write(0x20002000,IMAGE[8:8+0xc40]);self.u.mem_write(0x20002c40,IMAGE[0x8318:0x8318+0x310]);self.store=bytearray(b'\xff'*0x100);self.events=[]
  for slot,target in [(0x4003c,0x40100),(0x40048,0x40110),(0x4004c,0x40120)]:self.u.mem_write(slot,struct.pack('<I',target))
  self.u.hook_add(UC_HOOK_CODE,self.hook)
  self.u.mem_write(0x40100,b"\x67\x80\x00\x00");self.u.mem_write(0x40110,b"\x67\x80\x00\x00");self.u.mem_write(0x40120,b"\x67\x80\x00\x00")
 def hook(self,u,address,size,data):
  if address not in [0x40100,0x40110,0x40120,0x200028d6,0x6ff6,0x6f6c,0x4eca]:return
  a=[u.reg_read(UC_RISCV_REG_X10+i) for i in range(4)];ret=0
  if address==0x40100:ret=int(bytes(u.mem_read(a[0],a[2]))==bytes(u.mem_read(a[1],a[2])))
  elif address==0x40110:u.mem_write(a[0],bytes([a[1]&255])*a[2]);ret=a[0]
  elif address==0x40120:u.mem_write(a[0],bytes(u.mem_read(a[1],a[2])));ret=a[0]
  elif address==0x200028d6:
   cmd,off,ptr,n=a;assert off==0x6f00
   if cmd==11:u.mem_write(ptr,bytes(self.store[:n]))
   elif cmd==9:self.store[:n]=b'\xff'*n
   elif cmd==10:self.store[:n]=bytes(u.mem_read(ptr,n))
   else:raise AssertionError(a)
   self.events.append(dict(storage_command=cmd,length=n))
  else:self.events.append(dict(target=hex(address),bytes=bytes(u.mem_read(a[0],a[1])).hex(),length=a[1]));u.mem_write(0x20003a49,b'\x00') if address==0x4eca else None
  u.reg_write(UC_RISCV_REG_X10,ret);u.reg_write(UC_RISCV_REG_PC,u.reg_read(UC_RISCV_REG_X1))
 def call(self,addr,*args):
  for i,v in enumerate(args):self.u.reg_write(UC_RISCV_REG_X10+i,v)
  self.u.reg_write(UC_RISCV_REG_X1,STOP);self.u.reg_write(UC_RISCV_REG_X2,0x2000f000);self.u.reg_write(UC_RISCV_REG_X3,0x20002000);self.u.emu_start(addr,STOP,count=100000)
  assert self.u.reg_read(UC_RISCV_REG_PC)==STOP
  return self.u.reg_read(UC_RISCV_REG_X10)
if __name__ == '__main__':
 results=[]
 def check(name,ok,**details):
  assert ok,(name,details);results.append(dict(case=name,pass_result=True,**details))
 for route,tail in [(0,0x31),(1,0),(2,0)]:
  m=BLE();m.u.mem_write(REQ,b'\xc2\x11');m.call(0x4074,REQ,2,route)
  check(f'GATT to main route {route}',bytes(m.u.mem_read(0x20003a50,7))==bytes([6,2,3,0,0xc2,0x11,tail]) and m.u.mem_read(0x20003c58,1)==b'\x01')
 for tail,target,expected in [(0x31,'0x6ff6','31c300'),(0,'0x6f6c','c300')]:
  m=BLE();m.u.mem_write(0x20003b56,struct.pack('<H',3));m.u.mem_write(0x20003b58,bytes([0xc3,0,tail]));m.call(0x3fac,0);check(f'main reply route {tail}',m.events==[dict(target=target,bytes=expected,length=len(bytes.fromhex(expected)))],events=m.events)
 m=BLE()
 for i in range(1,8):
  host=bytes([i])*16;m.u.mem_write(REQ,host);m.call(0x7696,REQ);expected=b''.join(bytes([j])*16 for j in range(max(1,i-4),i+1));check(f'save host {i}',m.store[:len(expected)]==expected,stored=m.store[:80].hex())
 for i in range(1,9):
  m.u.mem_write(REQ,bytes([i])*16);found=m.call(0x773c,REQ);check(f'find host {i}',found==int(3<=i<=7),found=found)
 for total in [1,61,62,63,124,125,255]:
  m=BLE();data=bytes(range(total));m.u.mem_write(0x20003644,data);m.u.mem_write(0x20003a44,bytes([total]));m.u.mem_write(0x20003a4a,b'\x01')
  while m.u.mem_read(0x20003a4a,1)!=b'\x00':
   m.u.mem_write(0x20003a49,b'\x01');m.call(0x3e1a)
  chunks=[x for x in m.events if x.get('target')=='0x4eca'];check(f'USB queue length {total}',b''.join(bytes.fromhex(x['bytes']) for x in chunks)==data and all(x['length']<=62 for x in chunks),chunks=[x['length'] for x in chunks])
 (ROOT/'exports/ble-emulation.json').write_text(json.dumps(dict(scope='Original RV32 application instructions. SDK boolean memcmp/memset/memcpy, flash storage, GATT notification and USB sender explicitly substituted. No radio, physical flash or USB execution.',passed=len(results),failed=0,cases=results),indent=2)+'\n');print(len(results),'BLE bridge cases passed')
