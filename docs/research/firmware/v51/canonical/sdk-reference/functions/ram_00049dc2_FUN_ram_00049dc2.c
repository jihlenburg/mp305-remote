/* Address: ram:00049dc2; name: FUN_ram_00049dc2; body bytes: 36 */

ushort * FUN_ram_00049dc2(uint param_1,ushort *param_2)

{
  uint uVar1;
  
  gp = 0x20004000;
  uVar1 = 0;
  while( true ) {
    if (DAT_ram_20001d55 <= uVar1) {
      return (ushort *)0x0;
    }
    if (*param_2 == param_1) break;
    uVar1 = uVar1 + 1;
    param_2 = param_2 + 2;
  }
  gp = 0x20004000;
  return param_2;
}

