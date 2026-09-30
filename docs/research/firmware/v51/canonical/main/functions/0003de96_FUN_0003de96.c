/* Address: 0003de96; name: FUN_0003de96; body bytes: 64 */

undefined4 FUN_0003de96(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int extraout_r3;
  
  if (*(uint *)(param_1 + 4) <= param_2) {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 4) - 1;
  if (uVar1 != param_2) {
    iVar2 = FUN_0003de0e(param_1);
    FUN_0004a538(iVar2,*(int *)(param_1 + 0xc) + iVar2,
                 *(int *)(param_1 + 0xc) * ((*(int *)(param_1 + 4) - extraout_r3) + -1));
    uVar1 = *(int *)(param_1 + 4) - 1;
  }
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0003def8(param_1);
  return 1;
}

