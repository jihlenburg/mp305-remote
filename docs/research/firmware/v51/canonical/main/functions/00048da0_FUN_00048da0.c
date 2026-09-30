/* Address: 00048da0; name: FUN_00048da0; body bytes: 30 */

void FUN_00048da0(undefined4 param_1,int param_2)

{
  FUN_00048dbe(param_2);
  if (-1 < (int)((uint)*(byte *)(param_2 + 0x5c) << 0x1c)) {
    FUN_00046bec(*(undefined4 *)(param_2 + 0x2c));
  }
  *(undefined4 *)(param_2 + 0x2c) = 0;
  return;
}

