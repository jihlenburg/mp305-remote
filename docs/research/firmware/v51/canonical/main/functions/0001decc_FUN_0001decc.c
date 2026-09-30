/* Address: 0001decc; name: FUN_0001decc; body bytes: 24 */

void FUN_0001decc(int param_1,int param_2,ushort param_3)

{
  param_1 = param_1 + param_2 * 4;
  *(ushort *)(param_1 + 0x140) = *(ushort *)(param_1 + 0x140) & 0xfcff | param_3 & 0x300;
  return;
}

