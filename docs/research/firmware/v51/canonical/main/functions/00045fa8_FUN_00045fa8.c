/* Address: 00045fa8; name: FUN_00045fa8; body bytes: 38 */

void FUN_00045fa8(int param_1)

{
  FUN_0004e0e6(param_1,1);
  *(undefined4 *)(param_1 + 0x48) = 0xffff;
  FUN_0004aa6e(*(undefined4 *)(param_1 + 0x2c),1);
  FUN_0004e5a6(param_1,0x24,0);
  return;
}

