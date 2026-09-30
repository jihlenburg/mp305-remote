/* Address: 0004e7d8; name: FUN_0004e7d8; body bytes: 30 */

void FUN_0004e7d8(int param_1,uint param_2)

{
  ushort uVar1;
  
  FUN_0004af28();
  uVar1 = *(ushort *)(*(int *)(param_1 + 8) + 0x2a);
  if ((uVar1 & 0x3ff) >> 6 != param_2) {
    *(ushort *)(*(int *)(param_1 + 8) + 0x2a) = uVar1 & 0xfc3f | (ushort)((param_2 & 0xf) << 6);
  }
  return;
}

