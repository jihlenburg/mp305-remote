/* Address: 0005de60; name: FUN_0005de60; body bytes: 208 */

void FUN_0005de60(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  if (param_3 == 0) {
    iVar2 = FUN_0004cb02(param_1,0x20000);
    local_20._0_2_ = (undefined2)iVar2;
    *(undefined2 *)(param_2 + 0x2c) = (undefined2)local_20;
    local_20._2_1_ = (undefined1)((uint)iVar2 >> 0x10);
    *(undefined1 *)(param_2 + 0x2e) = local_20._2_1_;
    local_20 = iVar2;
    uVar1 = FUN_0004cb94(param_1,0x20000);
    *(undefined1 *)(param_2 + 0x48) = uVar1;
    uVar3 = FUN_0004cb64(param_1,0x20000);
    *(undefined4 *)(param_2 + 0x3c) = uVar3;
  }
  else {
    iVar2 = FUN_00050a74(param_3,0x58,&local_20);
    if (iVar2 == 1) {
      *(undefined2 *)(param_2 + 0x2c) = (undefined2)local_20;
      uVar1 = local_20._2_1_;
    }
    else {
      uVar3 = FUN_0004cb02(param_1,0x20000);
      local_1c._0_2_ = (undefined2)uVar3;
      *(undefined2 *)(param_2 + 0x2c) = (undefined2)local_1c;
      local_1c._2_1_ = (undefined1)((uint)uVar3 >> 0x10);
      uVar1 = local_1c._2_1_;
      local_1c = uVar3;
    }
    *(undefined1 *)(param_2 + 0x2e) = uVar1;
    iVar2 = FUN_00050a74(param_3,0x59,&local_20);
    if (iVar2 == 1) {
      uVar1 = (undefined1)local_20;
    }
    else {
      uVar1 = FUN_0004cb94(param_1,0x20000);
    }
    *(undefined1 *)(param_2 + 0x48) = uVar1;
    iVar4 = FUN_00050a74(param_3,0x5b,&local_20);
    iVar2 = local_20;
    if (iVar4 != 1) {
      iVar2 = FUN_0004cb64(param_1,0x20000);
    }
    *(int *)(param_2 + 0x3c) = iVar2;
    iVar2 = FUN_00050a74(param_3,0x5a,&local_20);
    if (iVar2 == 1) goto LAB_0005defc;
  }
  local_20 = FUN_0004cb40(param_1,0x20000);
LAB_0005defc:
  *(int *)(param_2 + 0x20) = local_20;
  return;
}

