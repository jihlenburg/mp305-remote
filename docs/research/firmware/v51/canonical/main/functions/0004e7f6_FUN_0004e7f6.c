/* Address: 0004e7f6; name: FUN_0004e7f6; body bytes: 22 */

void FUN_0004e7f6(int param_1,ushort param_2)

{
  FUN_0004af28();
  *(ushort *)(*(int *)(param_1 + 8) + 0x2a) =
       *(ushort *)(*(int *)(param_1 + 8) + 0x2a) & 0xfff3 | (param_2 & 3) << 2;
  return;
}

