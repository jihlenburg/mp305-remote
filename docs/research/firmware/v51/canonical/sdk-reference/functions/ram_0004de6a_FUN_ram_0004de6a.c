/* Address: ram:0004de6a; name: FUN_ram_0004de6a; body bytes: 170 */

void FUN_ram_0004de6a(void)

{
  uint uVar1;
  int iVar2;
  undefined2 *puVar3;
  
  gp = 0x20004000;
  DAT_ram_20001d55 = (undefined1)(DAT_ram_20001bd3 & 3);
  iVar2 = (DAT_ram_20001bd3 & 3) + (uint)(DAT_ram_20001bd3 >> 2);
  DAT_ram_20001d54 = (byte)iVar2;
  if (iVar2 != 0) {
    DAT_ram_20001d00 = FUN_ram_20000040(iVar2 * 0x3c,0x9001);
    tmos_memset(DAT_ram_20001d00,0,(uint)DAT_ram_20001d54 * 0x3c);
    uVar1 = (uint)DAT_ram_20001d54;
    puVar3 = (undefined2 *)(DAT_ram_20001d00 + 2);
    for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
      *puVar3 = 0xffff;
      *(undefined1 *)(puVar3 + 1) = 0;
      *(undefined4 *)(puVar3 + 0x15) = 0;
      puVar3 = puVar3 + 0x1e;
    }
    tmos_memset(&DAT_ram_20001d04,0,0x30);
    return;
  }
  return;
}

