#!/usr/bin/env python3
"""Compare seven reconstructed read-reply builders against original ARM code."""
from emulate import Machine, ROOT
import ctypes,json,random
lib=ctypes.CDLL(str(ROOT/'reconstructed/libprotocol.dylib'))
lib.reconstructed_read.restype=ctypes.c_size_t
lib.reconstructed_read.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t,ctypes.c_void_p,ctypes.c_uint8]
rng=random.Random(3055102);rows=[]
handlers={0xc2:0x158bc,0xc4:0x15ef8,0xdc:0x1565c,0xde:0x15694,0xe4:0x15630,0xea:0x154ac,0xec:0x1555c}
for i in range(128):
 ram=bytearray(rng.randbytes(0x20000))
 ram[0x2a0:0x2a4]=(0 if i%2 else 1).to_bytes(4,'little')
 ram[0x1aafc]=i%4
 ram[0x1a408]=i%10
 kind=[1,3,6,6][i%4]
 for opcode,address in handlers.items():
  req=bytes([opcode,rng.randrange(256)]);m=Machine();m.uc.mem_write(0x1ffe0000,bytes(ram))
  expected=m.handler(address,req,kind);out=ctypes.create_string_buffer(100)
  n=lib.reconstructed_read(bytes(ram),req,len(req),out,kind)
  assert out.raw[:n]==expected,(i,hex(opcode),out.raw[:n].hex(),expected.hex())
  # No global-state mutation is expected from these reply builders.
  assert bytes(m.uc.mem_read(0x1ffe0000,len(ram)))==bytes(ram),(i,hex(opcode),'RAM changed')
  rows.append({'case':f'{opcode:02x} read reply {i}','pass':True,'route_type':kind,'reply':expected.hex()})
(ROOT/'exports/read-reply-comparison.json').write_text(json.dumps({'scope':'Seven reconstructed read-reply builders versus original ARM instructions. Synthetic randomized RAM with explicit branch cases. No hardware accessed.','passed':len(rows),'failed':0,'cases':rows},indent=2)+'\n')
print(len(rows),'read-reply comparisons passed')
