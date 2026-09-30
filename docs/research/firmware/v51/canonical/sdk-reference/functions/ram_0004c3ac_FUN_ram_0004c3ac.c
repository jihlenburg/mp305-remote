/* Address: ram:0004c3ac; name: FUN_ram_0004c3ac; body bytes: 50 */

ushort * FUN_ram_0004c3ac(uint param_1)

{
  ushort *puVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  puVar1 = DAT_ram_20001cc4;
  while( true ) {
    if (DAT_ram_20001a63 == cVar2) {
      return (ushort *)0x0;
    }
    if ((*puVar1 != 0) && (*puVar1 == param_1)) break;
    cVar2 = cVar2 + '\x01';
    puVar1 = puVar1 + 8;
  }
  gp = 0x20004000;
  return puVar1;
}

