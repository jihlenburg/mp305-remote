/* Address: 0004aaf6; name: FUN_0004aaf6; body bytes: 44 */

void FUN_0004aaf6(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)(param_1 + 0x28);
  param_2 = uVar1 | param_2;
  if (uVar1 != param_2) {
    if ((int)((param_2 & ~uVar1) << 0x18) < 0) {
      FUN_00048400(0,param_1);
    }
    FUN_000654c4(param_1,param_2);
    return;
  }
  return;
}

