"""Find Thumb BL/B.W/B/literal references to given targets in app.bin (hostlink area)."""
import sys, struct, capstone
RE='/Users/jihlenburg/mp305b-fw-re/'
BASE=0x10000
d=open(RE+'bin/app.bin','rb').read()
targets=[int(x,0)&~1 for x in sys.argv[1:]]
md=capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB|capstone.CS_MODE_MCLASS)
md.skipdata=True
# linear sweep with resync every 2 bytes is expensive; do linear sweep once
for i in md.disasm(d, BASE):
    if i.mnemonic in ('bl','b.w','b','blx','bne.w','beq.w','bl.w') or i.mnemonic.startswith('b'):
        try:
            t=int(i.op_str.lstrip('#'),0)
        except Exception: continue
        if t in targets: print('%08x: %s %s'%(i.address,i.mnemonic,i.op_str))
for off in range(0,len(d)-3,2):
    v=struct.unpack('<I',d[off:off+4])[0]
    if (v&~1) in targets and v&1: print('literal %08x at %08x'%(v,off+BASE))
