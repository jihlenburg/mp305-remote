/* Address: ram:00062262; name: FUN_ram_00062262; body bytes: 134 */

void FUN_ram_00062262(void)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = DAT_ram_20001eb0;
  gp = 0x20004000;
  if ((*DAT_ram_20001eb0 & 3) != 0) {
    DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
    *puVar2 = *puVar2 | 8;
  }
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f | 0x80;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffcdffff;
  DAT_ram_20001eb0[0x14] = 0x80;
  iVar1 = DAT_ram_20001e90;
  if (DAT_ram_20001e90 != 0) {
    **(uint **)(DAT_ram_20001e90 + 4) =
         **(uint **)(DAT_ram_20001e90 + 4) | *(uint *)(DAT_ram_20001e90 + 8);
    puVar2 = *(uint **)(iVar1 + 0x10);
    *puVar2 = *(uint *)(iVar1 + 0x14) | *puVar2;
  }
  DAT_ram_20001e9b = 0;
  return;
}

