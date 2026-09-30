/* Address: 0001416c; name: FUN_0001416c; body bytes: 24 */

void FUN_0001416c(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  
  uVar1 = (ushort)(1 << (param_2 + 9U & 0xff));
  if (param_3 == 1) {
    uVar1 = *(ushort *)(param_1 + 4) | uVar1;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 4) & ~uVar1;
  }
  *(ushort *)(param_1 + 4) = uVar1;
  return;
}

