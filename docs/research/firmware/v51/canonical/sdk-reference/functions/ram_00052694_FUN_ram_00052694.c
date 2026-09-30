/* Address: ram:00052694; name: FUN_ram_00052694; body bytes: 60 */

void FUN_ram_00052694(uint param_1,ushort *param_2)

{
  uint uVar1;
  uint uVar2;
  
  gp = 0x20004000;
  uVar2 = 0;
  while( true ) {
    uVar1 = (uint)(byte)(&DAT_ram_0006c0ec)[uVar2];
    if ((param_1 < uVar1) || (uVar1 == 0xff)) break;
    if (*param_2 <= uVar1) {
      *param_2 = (ushort)(byte)(&DAT_ram_0006c0ec)[uVar2];
      return;
    }
    uVar2 = uVar2 + 1 & 0xff;
  }
  return;
}

