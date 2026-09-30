/* Address: ram:0004e028; name: FUN_ram_0004e028; body bytes: 62 */

byte * FUN_ram_0004e028(uint param_1)

{
  byte *pbVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  pbVar1 = DAT_ram_20001d00;
  while( true ) {
    if (DAT_ram_20001d54 == cVar2) {
      return (byte *)0x0;
    }
    if ((*(short *)(pbVar1 + 2) != -1) && (*pbVar1 == param_1)) break;
    cVar2 = cVar2 + '\x01';
    pbVar1 = pbVar1 + 0x3c;
  }
  gp = 0x20004000;
  return pbVar1;
}

