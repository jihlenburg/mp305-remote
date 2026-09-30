/* Address: 0004e822; name: FUN_0004e822; body bytes: 40 */

void FUN_0004e822(int param_1,uint param_2)

{
  ushort uVar1;
  
  FUN_0004af28();
  uVar1 = *(ushort *)(*(int *)(param_1 + 8) + 0x2a);
  if ((uVar1 & 3) != param_2) {
    *(ushort *)(*(int *)(param_1 + 8) + 0x2a) = uVar1 & 0xfffc | (ushort)param_2 & 3;
    FUN_0004d3d8(param_1);
    return;
  }
  return;
}

