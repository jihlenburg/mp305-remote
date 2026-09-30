import xml.etree.ElementTree as ET
t=ET.parse('svd/HC32F4A0.svd').getroot()
ps=t.find('peripherals'); byname={p.findtext('name'):p for p in ps.findall('peripheral')}
lo,hi=1<<32,0
out=open('out/hc32f4a0_regs.txt','w'); per=open('out/hc32f4a0_periph.txt','w')
for p in ps.findall('peripheral'):
    name=p.findtext('name'); base=int(p.findtext('baseAddress'),0)
    src=p
    if p.get('derivedFrom') and p.find('registers') is None: src=byname[p.get('derivedFrom')]
    ab=src.find('addressBlock'); size=int(ab.findtext('size'),0) if ab is not None else 0x400
    lo=min(lo,base); hi=max(hi,base+size)
    per.write(f"{base:08x} {size:x} {name}\n")
    r=src.find('registers')
    if r is None: continue
    for reg in r.iter('register'):
        off=int(reg.findtext('addressOffset'),0); sz=int(reg.findtext('size') or src.findtext('size') or '32',0)//8
        out.write(f"{base+off:08x} {sz} {name}_{reg.findtext('name')}\n")
print(hex(lo),hex(hi))
