/* Address: ram:000055c0; name: FUN_ram_000055c0; body bytes: 170 */

void FUN_ram_000055c0(void)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  FUN_ram_000054fa();
  FUN_ram_00003876(1);
  iVar1 = (int)DAT_ram_20002f54;
  DAT_ram_20003a49 = 1;
  DAT_ram_20003a48 = 1;
  DAT_ram_20003a4a = 0;
  DAT_ram_20003a4b = 0;
  DAT_ram_20003a4d = 0;
  DAT_ram_20003a4c = 0;
  FUN_ram_00001d1a((int)DAT_ram_20002f54 + 0x40,0,0x40);
  FUN_ram_00001d1a(iVar1,0,0x40);
  DAT_ram_20002f50 = &DAT_ram_20004774;
  DAT_ram_20002f54 = &DAT_ram_20004834;
  DAT_ram_20002f58 = &DAT_ram_200048b4;
  DAT_ram_20002f5c = &DAT_ram_20004934;
  FUN_ram_00002966();
  DAT_ram_e000e100 = 0x400000;
  return;
}

