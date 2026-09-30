/* Address: 0005ddbc; name: FUN_0005ddbc; body bytes: 162 */

void FUN_0005ddbc(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = param_3;
  local_14 = param_4;
  if (param_3 == 0) {
    uVar4 = FUN_0004c6f6(param_1,0);
    local_18._0_2_ = (undefined2)uVar4;
    *(undefined2 *)(param_2 + 0x1c) = (undefined2)local_18;
    local_18._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    *(undefined1 *)(param_2 + 0x1e) = local_18._2_1_;
    local_18 = uVar4;
    uVar1 = FUN_0004c6fc(param_1,0);
    *(undefined1 *)(param_2 + 0x3c) = uVar1;
    uVar4 = FUN_0004c708(param_1,0);
    *(undefined4 *)(param_2 + 0x20) = uVar4;
    return;
  }
  iVar2 = FUN_00050a74(param_3,0x50,&local_18);
  iVar3 = local_18;
  if (iVar2 != 1) {
    iVar3 = FUN_0004c708(param_1,0);
  }
  *(int *)(param_2 + 0x20) = iVar3;
  iVar3 = FUN_00050a74(param_3,0x52,&local_18);
  if (iVar3 == 1) {
    *(undefined2 *)(param_2 + 0x1c) = (undefined2)local_18;
    uVar1 = local_18._2_1_;
  }
  else {
    uVar4 = FUN_0004c6f6(param_1,0);
    local_14._0_2_ = (undefined2)uVar4;
    *(undefined2 *)(param_2 + 0x1c) = (undefined2)local_14;
    local_14._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    uVar1 = local_14._2_1_;
    local_14 = uVar4;
  }
  *(undefined1 *)(param_2 + 0x1e) = uVar1;
  iVar3 = FUN_00050a74(param_3,0x53,&local_18);
  if (iVar3 == 1) {
    uVar1 = (undefined1)local_18;
  }
  else {
    uVar1 = FUN_0004c6fc(param_1,0);
  }
  *(undefined1 *)(param_2 + 0x3c) = uVar1;
  return;
}

