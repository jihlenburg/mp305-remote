/* Address: ram:000074d2; name: FUN_ram_000074d2; body bytes: 96 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000074d2(void)

{
  int iVar1;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined1 auStack_20 [24];
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_00040048)(auStack_20,0xff,0xe,in_a3,in_a4,_DAT_ram_00040048);
  FUN_ram_200028d6(0xb,0x6e00,&DAT_ram_200042b0,0x16);
  iVar1 = (*_DAT_ram_0004003c)(auStack_20,&DAT_ram_200042b0,0xe);
  if (iVar1 == 0) {
    (*_DAT_ram_0004004c)(&DAT_ram_20002e89,&DAT_ram_200042b0,0xe);
  }
  return;
}

