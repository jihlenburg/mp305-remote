/* Address: 0004e80c; name: FUN_0004e80c; body bytes: 22 */

void FUN_0004e80c(int param_1,ushort param_2)

{
  FUN_0004af28();
  *(ushort *)(*(int *)(param_1 + 8) + 0x2a) =
       *(ushort *)(*(int *)(param_1 + 8) + 0x2a) & 0xffcf | (param_2 & 3) << 4;
  return;
}

