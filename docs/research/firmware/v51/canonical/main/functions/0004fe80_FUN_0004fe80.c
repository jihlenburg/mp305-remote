/* Address: 0004fe80; name: FUN_0004fe80; body bytes: 8 */

void FUN_0004fe80(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x40) = param_2;
  *(undefined4 *)(param_1 + 0x44) = param_3;
  FUN_0004d3d8();
  return;
}

