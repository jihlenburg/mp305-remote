/* Address: ram:0004e354; name: FUN_ram_0004e354; body bytes: 56 */

undefined2 FUN_ram_0004e354(uint param_1)

{
  int iVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  iVar1 = DAT_ram_20001d00;
  while( true ) {
    if (DAT_ram_20001d54 == cVar2) {
      return 0xffff;
    }
    if (*(ushort *)(iVar1 + 0x30) == param_1) break;
    cVar2 = cVar2 + '\x01';
    iVar1 = iVar1 + 0x3c;
  }
  return *(undefined2 *)(iVar1 + 2);
}

