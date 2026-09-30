/* Address: ram:00064170; name: RFEND_SetSensitivity; body bytes: 152 */

void RFEND_SetSensitivity(void)

{
  int iVar1;
  
  iVar1 = DAT_ram_20001efc;
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001efc + 0x5c) = *(uint *)(DAT_ram_20001efc + 0x5c) & 0x8fffffff;
  *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) & 0xff8fffff;
  *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) & 0xfff8ffff;
  *(uint *)(iVar1 + 0x50) = *(uint *)(iVar1 + 0x50) & 0xffff0fff | 0x9000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) | 0x7000000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) | 0x70000000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) | 0xf;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) | 0x70000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) & 0xffff0fff | 0x7000;
  *(uint *)(iVar1 + 0x48) = *(uint *)(iVar1 + 0x48) | 0x300;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) | 0x700;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) | 0x1000000;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) & 0xffffff8f;
  *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) | 7;
  return;
}

