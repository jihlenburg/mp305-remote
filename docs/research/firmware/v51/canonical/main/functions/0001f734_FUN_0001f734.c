/* Address: 0001f734; name: FUN_0001f734; body bytes: 36 */

uint FUN_0001f734(uint param_1)

{
  uint uVar1;
  
  if (5000 < param_1) {
    param_1 = 5000;
  }
  uVar1 = (uint)DAT_1fffaa80;
  if ((uVar1 != 0) && (150000000 / uVar1 < param_1)) {
    param_1 = 150000000 / uVar1 & 0xffff;
  }
  return param_1;
}

