#!/usr/bin/env python3
"""Run selected original Cortex-M functions offline, without peripheral I/O."""
from pathlib import Path
import struct,json,random
from unicorn import Uc,UC_ARCH_ARM,UC_MODE_THUMB,UC_MODE_MCLASS
from unicorn.arm_const import UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3,UC_ARM_REG_SP,UC_ARM_REG_LR,UC_ARM_REG_PC
ROOT=Path(__file__).resolve().parents[1]
IMAGE=(ROOT/'inputs/main-arm.bin').read_bytes()
STATE=0x1fffaacc; REQUEST=0x20030000; RESPONSE=0x20031000; STOP=0x90000
class Machine:
 def __init__(self):
  self.uc=Uc(UC_ARCH_ARM,UC_MODE_THUMB|UC_MODE_MCLASS)
  self.uc.mem_map(0,0x10000);self.uc.mem_write(0x1c,struct.pack('<I',0x8000));self.uc.mem_write(0x800c,bytes.fromhex('1020304050607080'));
  self.uc.mem_map(0x10000,0x80000);self.uc.mem_write(0x10000,IMAGE)
  self.uc.mem_map(STOP,0x1000);self.uc.mem_write(STOP,b'\x00\xbf')
  self.uc.mem_map(0x1ffe0000,0x60000)
 def call(self,addr,*args):
  for reg,v in zip([UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3],args):self.uc.reg_write(reg,v)
  self.uc.reg_write(UC_ARM_REG_SP,0x2003e000);self.uc.reg_write(UC_ARM_REG_LR,STOP|1)
  self.uc.emu_start(addr|1,STOP,count=1000000)
  assert self.uc.reg_read(UC_ARM_REG_PC)==STOP,'instruction limit exceeded'
  return self.uc.reg_read(UC_ARM_REG_R0)
 def handler(self,addr,request,kind=1):
  self.uc.mem_write(REQUEST,request);self.uc.mem_write(RESPONSE,b'\xcc'*512)
  n=self.call(addr,REQUEST,RESPONSE,kind,len(request)) if addr==0x1b634 else self.call(addr,REQUEST,len(request),RESPONSE,kind)
  return bytes(self.uc.mem_read(RESPONSE,n))

def settings_frame(**updates):
 vals=dict(limit=90,volume=2,screen_off=1,shutdown=15,direction=1,slope=200,ocp=300,flag53=1,flag54=1,usb_line=400)
 vals.update(updates)
 return bytes([0xc6,vals['limit'],vals['volume'],vals['screen_off'],vals['shutdown'],vals['direction']])+struct.pack('<HHBBH',vals['slope'],vals['ocp'],vals['flag53'],vals['flag54'],vals['usb_line'])

def encode_reference(slot):
 n=slot[2];address=(slot[0]<<4)|(slot[1]&15);inner=bytes([address,n])+slot[4:4+n];inner+=bytes([sum(inner)&255])
 return b'\xaa'+inner.replace(b'\xaa',b'\xaa\xaa')

def main():
 cases=[]
 def check(name,condition,details):
  assert condition,(name,details)
  cases.append({'name':name,'pass':True,'details':details})
 m=Machine();reply=m.handler(0x1caa4,settings_frame());s=bytes(m.uc.mem_read(STATE,0x200))
 check('C6 valid settings',reply==b'\xc7\x00' and s[0x2d]==90 and s[0x32]==2 and struct.unpack_from('<H',s,0x96)[0]==200,{'reply':reply.hex(),'state':s.hex()})
 check('C6 direction validated but unchanged',s[0x2f]==0,{'requested_direction':1,'stored_direction':s[0x2f]})
 m=Machine();reply=m.handler(0x1caa4,settings_frame(volume=4));s=bytes(m.uc.mem_read(STATE,0x200))
 check('C6 partial update on later invalid value',reply==b'\xc7\xff' and s[0x2d]==90 and s[0x32]==0 and s[0x48]==0,{'reply':reply.hex(),'limit':s[0x2d],'volume':s[0x32],'dirty':s[0x48]})
 for field,values in {'limit':[0,79,80,100,101,255],'volume':[0,3,4,255],'screen_off':[0,1,2],'shutdown':[0,30,31,255],'direction':[0,1,2],'slope':[0,1000,1001,65535],'ocp':[0,1000,1001,65535],'flag53':[0,1,2],'flag54':[0,1,2],'usb_line':[0,1000,1001,65535]}.items():
  for v in values:
   m=Machine();r=m.handler(0x1caa4,settings_frame(**{field:v}))
   valid=(80<=v<=100) if field=='limit' else v<=({'volume':3,'shutdown':30,'slope':1000,'ocp':1000,'usb_line':1000}.get(field,1))
   check(f'C6 {field}={v}',r==bytes([0xc7,0 if valid else 255]),{'reply':r.hex()})
 m=Machine();r=m.handler(0x1caa4,settings_frame()+b'\x5a',6);check('C6 type 6 route suffix',r==b'\xc7\x00\x5a',{'reply':r.hex()})
 for kind,n in [(1,31),(6,18)]:
  m=Machine();r=m.handler(0x1b634,b'\xe0\x5a',kind)
  check(f'E0 type {kind} layout',len(r)==n and (r[1:5]==b'\x01\x06\x00\x33' if kind==6 else r[1:9]==b'MP305B\0\0'),{'reply':r.hex()})
 rng=random.Random(305)
 for i in range(300):
  n=rng.randrange(1,124);payload=bytes(rng.choice([0xaa,rng.randrange(256)]) for _ in range(n));slot=bytes([rng.randrange(16),rng.randrange(16),n,0])+payload
  m=Machine();m.uc.mem_write(REQUEST,slot);length=m.call(0x15430,1,REQUEST,RESPONSE);actual=bytes(m.uc.mem_read(RESPONSE,length));expected=encode_reference(slot)
  check(f'frame encoder {i}',actual==expected,{'payload_bytes':n,'stuffed_bytes':length})
 result={'scope':'Offline emulation of original main-image instructions. No hardware accessed. E0 uses synthetic missing bootloader identity bytes 10 20 30 40 50 60 70 80 at address 0x800c, with pointer 0x8000 at 0x1c.','image_sha256':__import__('hashlib').sha256(IMAGE).hexdigest(),'cases':cases,'passed':len(cases),'failed':0}
 (ROOT/'exports/emulation-results.json').write_text(json.dumps(result,indent=2)+'\n')
 print(f'{len(cases)} checks passed')
if __name__=='__main__':main()
