from unicorn import *
from unicorn.arm_const import *
d=open('bin/app.bin','rb').read()
mu=Uc(UC_ARCH_ARM, UC_MODE_THUMB|UC_MODE_MCLASS)
mu.mem_map(0,0x200000); mu.mem_write(0x10000,d)
mu.mem_map(0x1FFE0000,0x80000)

mu.reg_write(UC_ARM_REG_SP,0x2003F600)
mu.reg_write(UC_ARM_REG_R0,0x83fc8); mu.reg_write(UC_ARM_REG_R1,0x1ffe0000); mu.reg_write(UC_ARM_REG_R2,0xb5c)
mu.reg_write(UC_ARM_REG_LR,0x1F0001)
mu.emu_start(0x11653,0x1F0000,count=10_000_000)
rw=bytes(mu.mem_read(0x1FFE0000,0xB5C))
open('bin/ram_rw_init.bin','wb').write(rw)
print('r1 end',hex(mu.reg_read(UC_ARM_REG_R1)),'nonzero',sum(1 for b in rw if b))
