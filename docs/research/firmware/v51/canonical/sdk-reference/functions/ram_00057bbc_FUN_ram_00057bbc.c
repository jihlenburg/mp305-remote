/* Address: ram:00057bbc; name: FUN_ram_00057bbc; body bytes: 52 */

int FUN_ram_00057bbc(uint param_1)

{
  byte bVar1;
  int iVar2;
  
  gp = 0x20004000;
  bVar1 = 0;
  iVar2 = DAT_ram_20001e00;
  while( true ) {
    if (*(ushort *)(iVar2 + 10) == param_1) {
      gp = 0x20004000;
      return iVar2;
    }
    if (*(ushort *)(iVar2 + 10) == 0xffff) break;
    bVar1 = bVar1 + 1;
    iVar2 = iVar2 + 0x10;
    if (DAT_ram_20001bcb < bVar1) {
      return 0;
    }
  }
  gp = 0x20004000;
  return iVar2;
}

