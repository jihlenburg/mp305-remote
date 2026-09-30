/* Address: ram:00064208; name: FUN_ram_00064208; body bytes: 130 */

void FUN_ram_00064208(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_ram_20001efc;
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001efc + 0x50) = *(uint *)(DAT_ram_20001efc + 0x50) & 0xfffeffff;
  *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) | 0x200000;
  *(uint *)(iVar2 + 0xc) = *(uint *)(iVar2 + 0xc) | 0x10;
  *(uint *)(iVar2 + 0xc) = *(uint *)(iVar2 + 0xc) & 0xffffffef;
  iVar2 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 0xc) = *(uint *)(DAT_ram_20001efc + 0xc) | 0x10;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x1000;
  iVar3 = DAT_ram_20001efc;
  do {
  } while ((*(uint *)(iVar2 + 0x9c) >> 8 & 1) == 0);
  puVar1 = (uint *)(DAT_ram_20001efc + 0x9c);
  *(uint *)(DAT_ram_20001efc + 0x50) = *(uint *)(DAT_ram_20001efc + 0x50) | 0x10000;
  *(uint *)(iVar3 + 0x50) = *(uint *)(iVar3 + 0x50) & 0xffffffe0 | *puVar1 & 0x1f;
  *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) & 0xffdfffff;
  return;
}

