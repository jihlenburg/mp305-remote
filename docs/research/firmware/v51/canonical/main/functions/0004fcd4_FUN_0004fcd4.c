/* Address: 0004fcd4; name: FUN_0004fcd4; body bytes: 10 */

void FUN_0004fcd4(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0xc) = param_2;
    *(undefined4 *)(param_1 + 0x10) = param_3;
  }
  return;
}

