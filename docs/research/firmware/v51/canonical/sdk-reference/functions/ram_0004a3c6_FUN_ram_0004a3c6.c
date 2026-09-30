/* Address: ram:0004a3c6; name: FUN_ram_0004a3c6; body bytes: 46 */

ushort * FUN_ram_0004a3c6(uint param_1)

{
  uint uVar1;
  ushort *puVar2;
  
  gp = 0x20004000;
  uVar1 = 0;
  puVar2 = DAT_ram_20001a50;
  do {
    if (*puVar2 == param_1) {
      gp = 0x20004000;
      return puVar2;
    }
    uVar1 = uVar1 + 1;
    puVar2 = puVar2 + 3;
  } while (uVar1 < DAT_ram_20001d55 + 1);
  return (ushort *)0x0;
}

