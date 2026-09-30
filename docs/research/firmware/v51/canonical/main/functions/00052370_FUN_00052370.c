/* Address: 00052370; name: FUN_00052370; body bytes: 212 */

void FUN_00052370(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int local_18;
  int local_14;
  
  if (*(int *)(param_1 + 0x4c) != param_2) {
    local_18 = param_3;
    local_14 = param_4;
    FUN_000491e8(*(undefined4 *)(param_1 + 0x2c));
    iVar1 = FUN_00051c88();
    if (param_2 < 0) {
      param_2 = param_2 + iVar1;
    }
    if ((iVar1 < param_2) || (param_2 == 0x7fff)) {
      param_2 = iVar1;
    }
    *(int *)(param_1 + 0x4c) = param_2;
    FUN_0004ef90(param_1);
    uVar2 = FUN_0004cb4c(param_1,0);
    FUN_00049080(*(undefined4 *)(param_1 + 0x2c),param_2,&local_18);
    iVar1 = FUN_00046bd6(uVar2);
    iVar3 = FUN_0004bf14(param_1);
    if (local_14 < iVar3) {
      FUN_0004e538(param_1,local_14,1);
    }
    iVar3 = FUN_0004baf8(param_1);
    iVar4 = FUN_0004bf14(param_1);
    if (iVar3 < (local_14 + iVar1) - iVar4) {
      FUN_0004e538(param_1,(local_14 - iVar3) + iVar1,1);
    }
    iVar3 = FUN_0004bd90(param_1);
    if (local_18 < iVar3) {
      FUN_0004e510(param_1,local_18,1);
    }
    iVar3 = FUN_0004bb1a(param_1);
    iVar4 = FUN_0004bd90(param_1);
    if (iVar3 < (local_18 + iVar1) - iVar4) {
      FUN_0004e510(param_1,(local_18 - iVar3) + iVar1,1);
    }
    *(int *)(param_1 + 0x48) = local_18;
    FUN_00060710(param_1);
    FUN_0005a550(param_1);
  }
  return;
}

