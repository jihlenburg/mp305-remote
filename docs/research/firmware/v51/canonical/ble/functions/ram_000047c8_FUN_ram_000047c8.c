/* Address: ram:000047c8; name: FUN_ram_000047c8; body bytes: 54 */

void FUN_ram_000047c8(void)

{
  int iVar1;
  int iVar2;
  
  gp = &DAT_ram_20002000;
  iVar1 = 0;
  do {
    iVar2 = (int)&DAT_ram_20003a50 + iVar1;
    iVar1 = iVar1 + 0x218;
    FUN_ram_00003598(iVar2);
  } while (iVar1 != 0x860);
  return;
}

