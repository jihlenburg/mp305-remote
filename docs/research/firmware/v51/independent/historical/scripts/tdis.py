import sys, capstone
BASE=0x10000
d=open('bin/app.bin','rb').read()
md=capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB|capstone.CS_MODE_MCLASS)
a=int(sys.argv[1],0)&~1; n=int(sys.argv[2]) if len(sys.argv)>2 else 40
for i in md.disasm(d[a-BASE:a-BASE+n*4], a):
    extra=''
    if i.mnemonic.startswith('ldr') and 'pc' in i.op_str and '[' in i.op_str:
        try:
            off=int(i.op_str.split('#')[1].rstrip(']'),0); la=((i.address+4)&~3)+off
            extra='  ; =0x%08x'%int.from_bytes(d[la-BASE:la-BASE+4],'little')
        except Exception: pass
    print('%08x: %-8s %s%s'%(i.address,i.mnemonic,i.op_str,extra)); n-=1
    if n<=0: break
