/* Address: 0005a550; name: FUN_0005a550; body bytes: 438 */

void FUN_0005a550(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  int local_34;
  int local_30;
  int iStack_2c;
  int local_28;
  
  local_48 = FUN_0004cb4c(param_1,0);
  iVar1 = FUN_0004cb8e(param_1,0);
  local_44 = *(undefined4 *)(param_1 + 0x4c);
  iVar2 = FUN_000491e8(*(undefined4 *)(param_1 + 0x2c));
  iVar3 = FUN_00051c28(iVar2,local_44);
  iVar4 = FUN_00051cb0(iVar2 + iVar3,0);
  iVar5 = FUN_00046bd6(local_48);
  iVar6 = FUN_0003ac8c(iVar4);
  iVar8 = iVar4;
  if (iVar6 != 0) {
    iVar8 = 0x20;
  }
  iVar8 = FUN_00046b72(local_48,iVar8,0);
  FUN_00049080(*(undefined4 *)(param_1 + 0x2c),local_44,&local_40);
  uVar7 = FUN_000491e8(*(undefined4 *)(param_1 + 0x2c));
  iVar6 = FUN_0004b108(*(undefined4 *)(param_1 + 0x2c),0,uVar7);
  if (((*(int *)(*(int *)(param_1 + 0x2c) + 0x1c) <
        local_40 + *(int *)(*(int *)(param_1 + 0x2c) + 0x14) + iVar8) &&
      (-1 < (int)((uint)*(byte *)(param_1 + 0x70) << 0x1c))) && (iVar6 != 3)) {
    local_40 = 0;
    local_3c = iVar5 + iVar1 + local_3c;
    uVar7 = 0;
    if (iVar4 != 0) {
      iVar8 = FUN_00051d84(iVar2 + iVar3);
      iVar3 = iVar3 + iVar8;
      uVar7 = FUN_00051cb0(iVar2 + iVar3,0);
    }
    iVar8 = FUN_0003ac8c(uVar7);
    if (iVar8 != 0) {
      uVar7 = 0x20;
    }
    iVar8 = FUN_00046b72(local_48,uVar7,0);
  }
  *(int *)(param_1 + 0x60) = iVar3;
  iVar1 = FUN_0004c6ae(param_1,0x60000);
  iVar2 = FUN_0004c918(param_1,0x60000);
  iVar3 = FUN_0004c816(param_1,0x60000);
  iVar4 = FUN_0004c87c(param_1,0x60000);
  iVar6 = FUN_0004c8be(param_1,0x60000);
  local_34 = local_40 - (iVar4 + iVar1);
  local_30 = local_3c - (iVar2 + iVar1);
  iStack_2c = iVar6 + iVar1 + local_40 + iVar8 + -1;
  local_28 = iVar5 + -1 + local_3c + iVar3 + iVar1;
  FUN_0003d9fe(&local_5c);
  local_5c = local_5c + *(int *)(*(int *)(param_1 + 0x2c) + 0x14);
  local_58 = *(int *)(*(int *)(param_1 + 0x2c) + 0x18) + local_58;
  local_54 = *(int *)(*(int *)(param_1 + 0x2c) + 0x14) + local_54;
  local_50 = *(int *)(*(int *)(param_1 + 0x2c) + 0x18) + local_50;
  FUN_0004d40e(param_1,&local_5c);
  FUN_0003d9fe(param_1 + 0x50,&local_34);
  FUN_0003d9fe(&local_5c,param_1 + 0x50);
  local_5c = local_5c + *(int *)(*(int *)(param_1 + 0x2c) + 0x14);
  local_58 = *(int *)(*(int *)(param_1 + 0x2c) + 0x18) + local_58;
  local_54 = *(int *)(*(int *)(param_1 + 0x2c) + 0x14) + local_54;
  local_50 = *(int *)(*(int *)(param_1 + 0x2c) + 0x18) + local_50;
  FUN_0004d40e(param_1,&local_5c);
  return;
}

