/* Address: 00014258; name: FUN_00014258; body bytes: 68 */

void FUN_00014258(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  FUN_0001416c(&DAT_40041000,1,9 < param_2);
  uVar1 = (uint)DAT_1fffa9ba;
  if (0xfff < DAT_1fffa9ba) {
    uVar1 = 0xfff;
  }
  uVar2 = (uint)DAT_1fffa9c2;
  if (0xfff < DAT_1fffa9c2) {
    uVar2 = 0xfff;
  }
  DAT_40041000 = uVar1 | uVar2 << 0x10;
  return;
}

