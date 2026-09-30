/* Address: ram:00049522; name: FUN_ram_00049522; body bytes: 50 */

ushort * FUN_ram_00049522(uint param_1)

{
  ushort *puVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  puVar1 = DAT_ram_20001a34;
  while( true ) {
    if (DAT_ram_20001d54 == cVar2) {
      return (ushort *)0x0;
    }
    if (*puVar1 == param_1) break;
    cVar2 = cVar2 + '\x01';
    puVar1 = puVar1 + 0x14;
  }
  gp = 0x20004000;
  return puVar1;
}

