/* Address: 00049a3a; name: FUN_00049a3a; body bytes: 52 */

void FUN_00049a3a(int param_1,int param_2)

{
  if ((-1 < (int)((uint)*(byte *)(param_1 + 0x5c) << 0x1c)) && (*(int *)(param_1 + 0x2c) != 0)) {
    FUN_00046bec();
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  if (param_2 != 0) {
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 8;
    *(int *)(param_1 + 0x2c) = param_2;
  }
  FUN_000493d0(param_1);
  return;
}

