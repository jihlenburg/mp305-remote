/* Address: 00046070; name: FUN_00046070; body bytes: 34 */

void FUN_00046070(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x2c) != 0) {
    FUN_0004b3a0();
    *(undefined4 *)(param_2 + 0x2c) = 0;
  }
  if (-1 < (int)((uint)*(byte *)(param_2 + 0x4c) << 0x1b)) {
    FUN_00046bec(*(undefined4 *)(param_2 + 0x38));
    *(undefined4 *)(param_2 + 0x38) = 0;
  }
  return;
}

