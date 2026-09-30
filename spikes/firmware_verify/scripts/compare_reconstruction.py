#!/usr/bin/env python3
"""Compare compilable reconstructed C with the original ARM instruction stream."""
from emulate import Machine,ROOT,STATE,REQUEST,RESPONSE,settings_frame,encode_reference
import ctypes,random,json,struct
lib=ctypes.CDLL(str(ROOT/'reconstructed/libprotocol.dylib'))
lib.reconstructed_c6.restype=ctypes.c_size_t;lib.reconstructed_c6.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t,ctypes.c_void_p,ctypes.c_uint8]
lib.reconstructed_encode.restype=ctypes.c_size_t;lib.reconstructed_encode.argtypes=[ctypes.c_void_p,ctypes.c_void_p]
rng=random.Random(30551);results=[]
for i in range(400):
 seed=bytes(rng.randrange(256) for _ in range(0x200));kind=rng.choice([1,6]);changes={}
 for field,valid,invalid in [('limit',[80,100,90],[0,79,101,255]),('volume',[0,3],[4,255]),('screen_off',[0,1],[2,255]),('shutdown',[0,30],[31,255]),('direction',[0,1],[2,255]),('slope',[0,1000],[1001,65535]),('ocp',[0,1000],[1001,65535]),('flag53',[0,1],[2,255]),('flag54',[0,1],[2,255]),('usb_line',[0,1000],[1001,65535])]:
  changes[field]=rng.choice(invalid if rng.random()<0.1 else valid)
 req=settings_frame(**changes)+bytes([rng.randrange(256)]);m=Machine();m.uc.mem_write(STATE,seed);expected=m.handler(0x1caa4,req,kind);expected_state=bytes(m.uc.mem_read(STATE,len(seed)))
 state=ctypes.create_string_buffer(seed,len(seed));reply=ctypes.create_string_buffer(10);n=lib.reconstructed_c6(state,req,len(req),reply,kind)
 assert reply.raw[:n]==expected and state.raw==expected_state,('c6',i)
 results.append({'case':f'C6 C versus ARM {i}','pass':True,'reply':expected.hex()})
for i in range(300):
 n=rng.randrange(1,124);payload=bytes(rng.choice([170,rng.randrange(256)]) for _ in range(n));slot=bytes([3,1,n,0])+payload
 m=Machine();m.uc.mem_write(REQUEST,slot);n_arm=m.call(0x15430,1,REQUEST,RESPONSE);expected=bytes(m.uc.mem_read(RESPONSE,n_arm));out=ctypes.create_string_buffer(600);n_c=lib.reconstructed_encode(slot,out)
 assert out.raw[:n_c]==expected==encode_reference(slot)
 # Feed exact encoded bytes into the original decoder, including stuffing and checksum.
 receiver=Machine();received=[]
 for value in expected:
  p=receiver.call(0x146b8,1,value)
  if p:received.append(bytes(receiver.uc.mem_read(p,4+len(payload))))
 assert received==[slot],('decoder',i,received,slot)
 # A changed checksum must not produce an accepted frame.
 bad=Machine();wrong=bytearray(expected);wrong[-1]^=1
 assert not any(bad.call(0x146b8,1,value) for value in wrong),('bad checksum',i)
 results.append({'case':f'encoder C versus ARM and decoder roundtrip {i}','pass':True,'payload_length':len(payload),'bad_checksum_rejected':True})
(ROOT/'exports/reconstruction-comparison.json').write_text(json.dumps({'scope':'Selected reconstructed C functions versus original ARM instructions. Each case uses fresh synthetic RAM. No physical device or peripheral execution.','passed':len(results),'failed':0,'cases':results},indent=2)+'\n')
print(len(results),'differential and frame cases passed')
