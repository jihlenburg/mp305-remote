/* Address: 000379a6; name: FUN_000379a6; body bytes: 112 */

void FUN_000379a6(undefined4 param_1,int param_2,uint param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = param_3 >> 1;
  iVar4 = ((int)(param_3 << 0x1f) >> 0x1f) + 1;
  iVar1 = FUN_00052d00();
  iVar5 = (int)(iVar1 * (param_2 - uVar3)) >> 7;
  iVar1 = thunk_FUN_00052d12(param_1);
  iVar1 = (int)(iVar1 * (param_2 - uVar3)) >> 7;
  if (iVar5 < 1) {
    iVar5 = iVar5 + 0x80 >> 8;
    iVar2 = (iVar5 + uVar3) - iVar4;
    *param_4 = iVar5 - uVar3;
  }
  else {
    iVar5 = iVar5 + -0x80 >> 8;
    iVar2 = iVar5 + uVar3;
    *param_4 = (iVar5 - uVar3) + iVar4;
  }
  param_4[2] = iVar2;
  if (iVar1 < 1) {
    iVar1 = iVar1 + 0x80 >> 8;
    iVar5 = (iVar1 + uVar3) - iVar4;
    param_4[1] = iVar1 - uVar3;
  }
  else {
    iVar1 = iVar1 + -0x80 >> 8;
    iVar5 = iVar1 + uVar3;
    param_4[1] = (iVar1 - uVar3) + iVar4;
  }
  param_4[3] = iVar5;
  return;
}

