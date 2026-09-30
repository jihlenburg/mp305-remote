/* Address: ram:00061910; name: FUN_ram_00061910; body bytes: 58 */

void FUN_ram_00061910(void)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e14;
  while (iVar1 != 0) {
    iVar1 = *(int *)(iVar1 + 8);
    FUN_ram_20000104();
  }
  DAT_ram_20001e14 = 0;
  DAT_ram_20001e10 = 0;
  return;
}

