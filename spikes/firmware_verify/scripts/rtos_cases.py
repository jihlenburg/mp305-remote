"""Run kernel resource primitives in synthetic RAM; no interrupts or hardware."""
from emulate import *
class Kernel(Machine):
 def __init__(self):
  super().__init__();self.uc.mem_map(0xe0000000,0x100000);self.uc.mem_write(0x1ffe0000,(ROOT/'inputs/main-initialized-ram.bin').read_bytes())
 def word(self,a):return int.from_bytes(self.uc.mem_read(a,4),'little')
 def create_task(self,depth,priority,name=b'probe_task'):
  self.uc.mem_write(REQUEST,name+b'\0');self.uc.mem_write(0x2003e000,struct.pack('<II',priority,RESPONSE));self.call(0x66ba4,0x1f209,REQUEST,depth,0);return self.word(RESPONSE)
results=[]
def check(name,ok,**details):
 assert ok,(name,details);results.append(dict(case=name,pass_result=True,**details))
m=Kernel();m.call(0x59aa4);initial=m.word(0x1ffe0064);check('heap initial free bytes',initial==0x4ff0,value=initial)
allocations=[]
for n in [1,8,80,512,2048,4096]:
 p=m.call(0x59f3c,n);check(f'heap allocate {n}',p!=0 and p%8==0,address=hex(p),free=m.word(0x1ffe0064));allocations.append(p)
for p in allocations[::2]+allocations[1::2]:m.call(0x65758,p)
check('heap coalesces all freed blocks',m.word(0x1ffe0064)==initial,free=m.word(0x1ffe0064))
for n in [0,0x5000,0xffffffff]:check(f'heap rejects size {n}',m.call(0x59f3c,n)==0)
for depth,priority in [(128,1),(1024,0),(512,3),(512,2),(512,4),(130,0),(260,2),(128,9)]:
 k=Kernel();t=k.create_task(depth,priority);check(f'task depth {depth} priority {priority}',t!=0 and k.word(t+0x2c)==min(priority,4) and k.word(t+0x40)==min(priority,4),tcb=hex(t),stack=hex(k.word(t+0x30)),priority=k.word(t+0x2c),free=k.word(0x1ffe0064));check(f'task fill depth {depth} priority {priority}',bytes(k.uc.mem_read(k.word(t+0x30),32))==b'\xa5'*32)
k=Kernel();k.uc.mem_write(0x2003a60c,struct.pack('<I',200000000));k.call(0x6579c);check('SysTick setup 1000 Hz formula',k.word(0xe000e014)==199999 and k.word(0xe000e010)==7,reload=k.word(0xe000e014),clock_input=200000000)
k=Kernel();q=k.call(0x666c4,10,16,0);check('queue object shape',k.word(q+0x3c)==10 and k.word(q+0x40)==16 and k.word(q+0x38)==0,queue=hex(q))
for i in range(10):k.uc.mem_write(REQUEST,bytes([i])*16);check(f'queue send {i}',k.call(0x667a0,q,REQUEST,0,0)==1)
check('queue full rejects zero-wait send',k.call(0x667a0,q,REQUEST,0,0)==0)
for i in range(10):check(f'queue FIFO receive {i}',k.call(0x6691c,q,RESPONSE,0)==1 and bytes(k.uc.mem_read(RESPONSE,16))==bytes([i])*16)
check('empty queue rejects zero-wait receive',k.call(0x6691c,q,RESPONSE,0)==0)
k=Kernel();t=k.create_task(128,2);q=k.call(0x666a0,1);check('mutex initially available',k.word(q)==0 and k.word(q+0x38)==1,mutex=hex(q));check('mutex take records owner',k.call(0x66a10,q,0)==1 and k.word(q+8)==t);check('normal mutex second take fails without wait',k.call(0x66a10,q,0)==0);check('mutex give clears owner',k.call(0x667a0,q,0,0,0)==1 and k.word(q+8)==0 and k.word(q+0x38)==1)
k=Kernel();e=k.call(0x664d6);check('event group starts empty',k.word(e)==0,event_group=hex(e))
for bits,mask,clear,allbits in [(3,3,1,0),(1,3,1,1),(3,3,0,1),(5,3,1,0)]:
 k.uc.mem_write(e,struct.pack('<I',bits));k.uc.mem_write(0x2003e000,struct.pack('<I',0));r=k.call(0x66554,e,mask,clear,allbits);match=(bits&mask)==mask if allbits else bool(bits&mask);expected=bits&~mask if match and clear else bits;check(f'event wait {bits}/{mask}/{clear}/{allbits}',r==bits and k.word(e)==expected,returned=r,remaining=k.word(e))
# Exercise highest-ready-priority selection and round robin without exception switching.
k=Kernel();a=k.create_task(128,2,b'A');b=k.create_task(128,2,b'B');k.call(0x65c14);x=k.word(0x1ffe0000);k.call(0x65c14);y=k.word(0x1ffe0000);check('equal priority rotates',x!=y and {x,y}=={a,b});c=k.create_task(128,4,b'C');k.call(0x65c14);check('highest ready priority wins',k.word(0x1ffe0000)==c)
(ROOT/'exports/rtos-emulation.json').write_text(json.dumps(dict(scope='Original ARM kernel primitives, recovered initial RAM and synthetic Cortex register memory. No real task execution, interrupt delivery, elapsed-time simulation or hardware. SysTick test uses a synthetic 200 MHz clock variable.',passed=len(results),failed=0,cases=results),indent=2)+'\n');print(len(results),'RTOS cases passed')
