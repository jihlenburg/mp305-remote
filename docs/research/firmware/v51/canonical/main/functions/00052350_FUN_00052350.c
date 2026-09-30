/* Address: 00052350; name: FUN_00052350; body bytes: 18 */

undefined4 FUN_00052350(int param_1)

{
  undefined4 uVar1;
  
  if (-1 < (int)((uint)*(byte *)(param_1 + 0x70) << 0x1d)) {
    uVar1 = FUN_000491e8(*(undefined4 *)(param_1 + 0x2c));
    return uVar1;
  }
  return *(undefined4 *)(param_1 + 0x34);
}

