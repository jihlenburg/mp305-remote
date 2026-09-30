/* Address: ram:2000289e; name: FUN_ram_2000289e; body bytes: 56 */

byte FUN_ram_2000289e(void)

{
  int iVar1;
  byte bVar2;
  
  gp = &DAT_ram_20002000;
  iVar1 = 0x80000;
  FUN_ram_2000282c();
  do {
    FUN_ram_2000281a(5);
    FUN_ram_2000283a();
    bVar2 = FUN_ram_2000283a();
    FUN_ram_2000282c();
    if ((bVar2 & 1) == 0) {
      gp = &DAT_ram_20002000;
      return bVar2 | 1;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0;
}

