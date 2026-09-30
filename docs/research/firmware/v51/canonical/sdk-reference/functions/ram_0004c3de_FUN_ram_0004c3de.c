/* Address: ram:0004c3de; name: FUN_ram_0004c3de; body bytes: 66 */

int FUN_ram_0004c3de(uint param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  
  gp = 0x20004000;
  cVar1 = '\0';
  iVar2 = DAT_ram_20001a58;
  while( true ) {
    if (DAT_ram_20001a61 == cVar1) {
      return 0;
    }
    if ((((*(short *)(iVar2 + 2) != 0) && (*(ushort *)(iVar2 + 6) == param_1)) &&
        (*(int *)(iVar2 + 0xc) != 0)) && (*(ushort *)(*(int *)(iVar2 + 0xc) + 2) == param_2)) break;
    cVar1 = cVar1 + '\x01';
    iVar2 = iVar2 + 0x10;
  }
  gp = 0x20004000;
  return iVar2;
}

