/* Address: 000520dc; name: FUN_000520dc; body bytes: 76 */

void FUN_000520dc(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_18;
  int local_14;
  
  local_18 = param_3;
  local_14 = param_4;
  FUN_00049080(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x4c),&local_18);
  iVar1 = FUN_0004cb8e(param_1,0);
  FUN_0004cb4c(param_1,0);
  iVar2 = FUN_00046bd6();
  local_14 = (local_14 - (iVar2 + iVar1)) + 1;
  local_18 = *(undefined4 *)(param_1 + 0x48);
  uVar3 = FUN_00048f08(*(undefined4 *)(param_1 + 0x2c),&local_18,1);
  uVar4 = *(undefined4 *)(param_1 + 0x48);
  FUN_00052370(param_1,uVar3);
  *(undefined4 *)(param_1 + 0x48) = uVar4;
  return;
}

