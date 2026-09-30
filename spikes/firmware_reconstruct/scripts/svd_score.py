import struct, sys, glob, xml.etree.ElementTree as ET
d=open('bin/app.bin','rb').read()
lits=set()
for i in range(0,len(d)-3,4):
    w=struct.unpack_from('<I',d,i)[0]
    if 0x40000000<=w<0x40100000: lits.add(w)
def parse(fn):
    t=ET.parse(fn).getroot()
    per={}
    ps=t.find('peripherals')
    byname={}
    for p in ps.findall('peripheral'):
        byname[p.findtext('name')]=p
    regs={}
    bases={}
    for p in ps.findall('peripheral'):
        name=p.findtext('name'); base=int(p.findtext('baseAddress'),0)
        bases[base]=name
        src=p
        df=p.get('derivedFrom')
        if df and p.find('registers') is None: src=byname[df]
        r=src.find('registers')
        if r is None: continue
        for reg in r.iter('register'):
            off=int(reg.findtext('addressOffset'),0)
            regs[base+off]=f"{name}.{reg.findtext('name')}"
    return bases,regs
for fn in sorted(glob.glob('svd/*.svd')):
    bases,regs=parse(fn)
    hb=[l for l in lits if l in bases]; hr=[l for l in lits if l in regs]
    print(fn, 'bases',len(hb),'regs',len(hr), 'of',len(lits), '| 0x40054000=',bases.get(0x40054000,regs.get(0x40054000)),'0x40050810=',regs.get(0x40050810), '0x4010e800', regs.get(0x4010e800,bases.get(0x4010e800)))
