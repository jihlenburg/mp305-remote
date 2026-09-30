/* Address: 0005df30; name: FUN_0005df30; body bytes: 172 */

void FUN_0005df30(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  if (param_3 == 0) {
    uVar4 = FUN_0004c6f6(param_1,param_4);
    local_20._0_2_ = (undefined2)uVar4;
    *(undefined2 *)(param_2 + 0x2c) = (undefined2)local_20;
    local_20._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
    *(undefined1 *)(param_2 + 0x2e) = local_20._2_1_;
    local_20 = uVar4;
    uVar1 = FUN_0004c6fc(param_1,param_4);
    *(undefined1 *)(param_2 + 0x3c) = uVar1;
    uVar4 = FUN_0004c708(param_1,param_4);
    *(undefined4 *)(param_2 + 0x30) = uVar4;
  }
  else {
    iVar2 = FUN_00050a74(param_3,0x48,&local_20);
    iVar3 = local_20;
    if (iVar2 != 1) {
      iVar3 = FUN_0004c708(param_1,param_4);
    }
    *(int *)(param_2 + 0x30) = iVar3;
    iVar3 = FUN_00050a74(param_3,0x4c,&local_20);
    if (iVar3 == 1) {
      *(undefined2 *)(param_2 + 0x2c) = (undefined2)local_20;
      uVar1 = local_20._2_1_;
    }
    else {
      uVar4 = FUN_0004c6f6(param_1,param_4);
      local_1c._0_2_ = (undefined2)uVar4;
      *(undefined2 *)(param_2 + 0x2c) = (undefined2)local_1c;
      local_1c._2_1_ = (undefined1)((uint)uVar4 >> 0x10);
      uVar1 = local_1c._2_1_;
      local_1c = uVar4;
    }
    *(undefined1 *)(param_2 + 0x2e) = uVar1;
    iVar3 = FUN_00050a74(param_3,0x4d,&local_20);
    if (iVar3 == 1) {
      uVar1 = (undefined1)local_20;
    }
    else {
      uVar1 = FUN_0004c6fc(param_1,param_4);
    }
    *(undefined1 *)(param_2 + 0x3c) = uVar1;
  }
  return;
}

