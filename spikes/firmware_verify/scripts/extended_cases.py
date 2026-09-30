"""Probe framing boundaries, deferred program replies and control payload offsets."""
from emulate import *
results=[]
def check(name,ok,**details):
 assert ok,(name,details)
 results.append(dict(case=name,pass_result=True,**details))
def decode(frame):
 m=Machine();out=[]
 for b in frame:
  p=m.call(0x146b8,1,b)
  if p:
   n=m.uc.mem_read(p+2,1)[0];out.append(bytes(m.uc.mem_read(p,n+4)))
 return out
for address in range(256):
 slot=bytes([address>>4,address&15,3,0,0xc2,0xaa,7]);out=decode(encode_reference(slot))
 check(f'address {address:02x}',out==([] if address==0xaa else [slot]),accepted=bool(out))
for n in range(1,256):
 slot=bytes([3,1,n,0])+bytes([0xaa])*n
 check(f'length {n}',decode(encode_reference(slot))==[slot])
slot=bytes([3,1,1,0,0xc2]);frame=encode_reference(slot)
for n in range(1,7):
 out=decode(bytes([0xaa])*n+frame[1:]);check(f'leading AA count {n}',out==([slot] if n%2 else []),accepted=bool(out))
check('zero length rejected',decode(encode_reference(bytes([3,1,0,0])))==[])
for n in [0,1,9,10,11,20,100]:
 for kind in [1,6]:
  m=Machine();index=3;m.uc.mem_write(0x1fffa3fe+index,b'\x07');m.uc.mem_write(0x1fffa3f4+index,bytes([n]));records=bytes(i%256 for i in range(1200));m.uc.mem_write(0x1fff8f7c,records)
  got=[]
  for cursor in range(0,max(1,n),10):
   r=m.handler(0x15ca0,bytes([0xd8,index,0x31]),kind);end=min(cursor+10,n)
   expected=b'\xd9\x07'+records[cursor*12:end*12]+(b'\x31' if kind==6 else b'')
   check(f'D9 steps {n} route {kind} cursor {cursor}',r==expected and m.uc.mem_read(0x1ffe0187,1)[0]==end,reply=r.hex());got.append(r)
def control(addr,mode,frame):
 m=Machine();m.uc.mem_map(0xe0000000,0x100000);m.uc.mem_write(0x1ffe0000,(ROOT/'inputs/main-initialized-ram.bin').read_bytes());m.uc.mem_write(STATE+0x30,bytes([mode]));m.uc.mem_write(STATE+0x42,b'\x01');m.uc.mem_write(STATE+3,b'\x02');return m,m.handler(addr,frame)
m,r=control(0x1b4d0,1,bytes([0xe2,1,3,0,1]));check('E2 request offsets',r==b'\xe3\x00' and m.uc.mem_read(STATE+0x4c,1)==b'\x03',reply=r.hex())
m,r=control(0x1d520,2,bytes([0xe8,1,0x34,0x12,7,0,2]));check('E8 request offsets',r==b'\xe9\x00' and m.uc.mem_read(STATE+0x9c,2)==b'\x34\x12' and m.uc.mem_read(0x1fff9bb9,1)==b'\x07',reply=r.hex())
for t,(low,high) in enumerate([(4250,4450),(4150,4250),(4050,4150),(3600,3700),(2350,2450),(3,13)]):
 for v in [low-1,low,high,high+1]:
  frame=bytes([0xee,1,t])+struct.pack('<H',v)+bytes([2])+struct.pack('<H',1234)+bytes([0,3]);m,r=control(0x13d44,3,frame)
  valid=low<=v<=high;check(f'EE type {t} voltage {v}',r==bytes([0xef,0 if valid else 255]),reply=r.hex())
  if valid:check(f'EE stored fields type {t} voltage {v}',m.uc.mem_read(STATE+0x1c8,2)==struct.pack('<H',v) and m.uc.mem_read(STATE+0x1c6,2)==struct.pack('<H',1234) and m.uc.mem_read(STATE+0x1ca,1)==bytes([t]))
(ROOT/'exports/extended-emulation.json').write_text(json.dumps(dict(scope='Original ARM instructions, synthetic memory. No hardware. E2/E8/EE cases keep output off.',passed=len(results),failed=0,cases=results),indent=2)+'\n');print(len(results),'extended cases passed')
