/* Address: 0003caee; name: FUN_0003caee; body bytes: 12 */

void FUN_0003caee(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x54) = *(byte *)(param_1 + 0x54) & 0xf7 | (param_2 & 1) << 3;
  return;
}

