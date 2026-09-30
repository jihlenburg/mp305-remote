/* Address: 00019116; name: FUN_00019116; body bytes: 60 */

void FUN_00019116(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = (param_2 * 5 + 5U) / 10 - 1;
  if (0x3ff < uVar1) {
    uVar1 = 0x3ff;
  }
  FUN_00012cb0(param_1,3,(uVar1 << 6 & 0xffff) >> 8);
  FUN_00012cb0(param_1,4,uVar1 << 6 & 0xc0);
  return;
}

