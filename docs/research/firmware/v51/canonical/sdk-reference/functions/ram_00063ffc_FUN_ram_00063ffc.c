/* Address: ram:00063ffc; name: FUN_ram_00063ffc; body bytes: 372 */

void FUN_ram_00063ffc(void)

{
  int iVar1;
  
  gp = 0x20004000;
  FUN_ram_00063fc6();
  iVar1 = DAT_ram_20001efc;
  *(undefined4 *)(DAT_ram_20001efc + 0x28) = 0x480;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) & 0x8fffffff | 0x20000000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) & 0xf8ffffff | 0x4000000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) & 0xfffffff0 | 9;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) & 0xfff8ffff;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) | 0x80000000;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) & 0xfffffff8 | 3;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) & 0xffffff8f | 0x30;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) & 0xfffff8ff | 0x300;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) & 0xfeffffff;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) | 0x2000000;
  *(uint *)(iVar1 + 0x50) = *(uint *)(iVar1 + 0x50) & 0xffff0fff | 0x4000;
  *(uint *)(iVar1 + 0x54) = *(uint *)(iVar1 + 0x54) & 0xfffffff0 | 0xc;
  *(uint *)(iVar1 + 0x54) = *(uint *)(iVar1 + 0x54) | 0x80;
  *(uint *)(iVar1 + 0x54) = *(uint *)(iVar1 + 0x54) & 0xffffefff;
  *(uint *)(iVar1 + 0x3c) = *(uint *)(iVar1 + 0x3c) & 0xffff0fff | 0x8000;
  *(uint *)(iVar1 + 0x3c) = *(uint *)(iVar1 + 0x3c) & 0xf8ffffff | 0x2000000;
  *(uint *)(iVar1 + 0x3c) = *(uint *)(iVar1 + 0x3c) & 0x1fffffff | 0x40000000;
  *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) | 0x700000;
  *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) & 0xf8ffffff;
  *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) & 0xffffcfff | 0x2000;
  *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) & 0xfffcffff | 0x20000;
  *(uint *)(iVar1 + 0x30) = *(uint *)(iVar1 + 0x30) & 0xfffffff0;
  *(uint *)(iVar1 + 0x30) = *(uint *)(iVar1 + 0x30) & 0xffffff0f;
  *(uint *)(iVar1 + 0x30) = *(uint *)(iVar1 + 0x30) & 0xfffff8ff;
  *(uint *)(iVar1 + 0x30) = *(uint *)(iVar1 + 0x30) | 0x700000;
  *(uint *)(iVar1 + 0x30) = *(uint *)(iVar1 + 0x30) & 0x8fffffff | 0x50000000;
  *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) & 0xff07ffff | 0x880000;
  *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) | 0x80000000;
  return;
}

