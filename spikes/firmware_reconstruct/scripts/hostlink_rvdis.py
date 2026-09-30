import os
import sys, capstone
d=open(os.path.expanduser("~/mp305b-fw-re/bin/ch58x.bin"),'rb').read()
md=capstone.Cs(capstone.CS_ARCH_RISCV, capstone.CS_MODE_RISCV32|capstone.CS_MODE_RISCVC)
a=int(sys.argv[1],0); n=int(sys.argv[2]) if len(sys.argv)>2 else 60
for i in md.disasm(d[a-0x1000:a-0x1000+n*4], a):
    print('%08x: %-8s %s'%(i.address,i.mnemonic,i.op_str)); n-=1
    if n<=0: break
