/* Address: ram:000018a6; name: FUN_ram_000018a6; body bytes: 56 */

byte FUN_ram_000018a6(void)

{
  int iVar1;
  byte bVar2;
  
  gp = &DAT_ram_20002000;
  iVar1 = 0x80000;
  FUN_ram_00001834();
  do {
    FUN_ram_00001822(5);
    FUN_ram_00001842();
    bVar2 = FUN_ram_00001842();
    FUN_ram_00001834();
    if ((bVar2 & 1) == 0) {
      gp = &DAT_ram_20002000;
      return bVar2 | 1;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0;
}

