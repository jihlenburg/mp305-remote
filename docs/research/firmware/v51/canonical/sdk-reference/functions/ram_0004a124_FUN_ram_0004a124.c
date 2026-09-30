/* Address: ram:0004a124; name: FUN_ram_0004a124; body bytes: 50 */

ushort * FUN_ram_0004a124(uint param_1)

{
  ushort *puVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar2 = '\0';
  puVar1 = DAT_ram_20001a4c;
  while( true ) {
    if (DAT_ram_20001d55 == cVar2) {
      return (ushort *)0x0;
    }
    if (*puVar1 == param_1) break;
    cVar2 = cVar2 + '\x01';
    puVar1 = puVar1 + 0x5c;
  }
  gp = 0x20004000;
  return puVar1;
}

