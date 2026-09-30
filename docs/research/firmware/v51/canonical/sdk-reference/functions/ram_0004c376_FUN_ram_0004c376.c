/* Address: ram:0004c376; name: FUN_ram_0004c376; body bytes: 54 */

int FUN_ram_0004c376(uint param_1)

{
  int iVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  iVar1 = DAT_ram_20001a58;
  while( true ) {
    if (DAT_ram_20001a60 == cVar2) {
      return 0;
    }
    if ((*(short *)(iVar1 + 2) != 0) && (*(byte *)(iVar1 + 4) == param_1)) break;
    cVar2 = cVar2 + '\x01';
    iVar1 = iVar1 + 0x10;
  }
  gp = 0x20004000;
  return iVar1;
}

