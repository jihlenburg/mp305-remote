/* Address: ram:0004e400; name: FUN_ram_0004e400; body bytes: 74 */

int FUN_ram_0004e400(void)

{
  int iVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  iVar1 = DAT_ram_20001d00;
  while( true ) {
    if (DAT_ram_20001d54 == cVar2) {
      return 0;
    }
    if (((*(short *)(iVar1 + 2) != -1) && (*(int *)(iVar1 + 0x34) != 0)) &&
       ((byte)(*(char *)(*(int *)(iVar1 + 0x34) + 3) - 0x22U) < 10)) break;
    cVar2 = cVar2 + '\x01';
    iVar1 = iVar1 + 0x3c;
  }
  gp = 0x20004000;
  return iVar1;
}

