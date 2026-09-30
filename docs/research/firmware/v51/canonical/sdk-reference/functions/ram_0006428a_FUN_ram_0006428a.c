/* Address: ram:0006428a; name: FUN_ram_0006428a; body bytes: 56 */

void FUN_ram_0006428a(void)

{
  int iVar1;
  
  iVar1 = DAT_ram_20001efc;
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001efc + 0x58) = *(uint *)(DAT_ram_20001efc + 0x58) & 0xfffeffff;
  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 0x10000;
  *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffeff;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffeffff;
  *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x100;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x10000;
  return;
}

