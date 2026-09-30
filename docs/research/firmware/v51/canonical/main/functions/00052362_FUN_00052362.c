/* Address: 00052362; name: FUN_00052362; body bytes: 12 */

void FUN_00052362(int param_1,byte param_2)

{
  *(byte *)(param_1 + 100) = *(byte *)(param_1 + 100) & 0xfd | (param_2 & 1) << 1;
  return;
}

