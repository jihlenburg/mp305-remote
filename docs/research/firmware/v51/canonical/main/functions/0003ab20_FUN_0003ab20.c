/* Address: 0003ab20; name: FUN_0003ab20; body bytes: 336 */

int FUN_0003ab20(int param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_30;
  uint local_2c;
  int local_28;
  int local_24;
  
  local_30 = param_1;
  if (param_2 < *(uint *)(param_1 + 0x70)) {
    local_2c = param_2;
    local_28 = param_3;
    local_24 = param_4;
    iVar1 = FUN_0004bb1a(param_1);
    iVar2 = FUN_0004bd90(param_1);
    if (-1 < (int)((uint)*(byte *)(param_1 + 0x74) << 0x1c)) {
LAB_0003ab52:
      iVar1 = FUN_0004d3d8(param_1);
      return iVar1;
    }
    uVar3 = *(byte *)(param_1 + 0x74) & 7;
    if (uVar3 == 1) {
      iVar4 = FUN_0004c696(param_1,0);
      iVar5 = FUN_0004c858(param_1,0);
      iVar2 = (iVar5 + iVar4 + *(int *)(param_1 + 0x14)) - iVar2;
      iVar4 = FUN_0004c924(param_1,&LAB_00050000,0x48);
      iVar5 = FUN_0004cbe4(param_1,0x20000);
      local_30 = *(int *)(param_1 + 0x14);
      local_2c = *(int *)(param_1 + 0x18) - (iVar4 + iVar5);
      local_24 = iVar4 + iVar5 + *(int *)(param_1 + 0x20);
      uVar3 = *(int *)(param_1 + 0x70) - 1;
      if (param_2 < uVar3) {
        local_30 = (((iVar1 * param_2) / uVar3 + iVar2) - iVar4) - iVar5;
        local_28 = (iVar1 * (param_2 + 1)) / uVar3 + iVar2 + iVar4 + iVar5;
        FUN_0004d40e(param_1,&local_30);
      }
      if (param_2 == 0) {
        return local_30;
      }
      uVar3 = *(int *)(param_1 + 0x70) - 1;
      local_30 = (((iVar1 * (param_2 - 1)) / uVar3 + iVar2) - iVar4) - iVar5;
      local_28 = (iVar1 * param_2) / uVar3 + iVar2 + iVar4 + iVar5;
    }
    else {
      if (uVar3 != 2) goto LAB_0003ab52;
      iVar4 = FUN_0004c828(param_1,0);
      uVar3 = (uint)(iVar1 + iVar4) / *(uint *)(param_1 + 0x70);
      iVar1 = FUN_0004c696(param_1,0);
      iVar5 = FUN_0004c858(param_1,0);
      iVar6 = *(int *)(param_1 + 0x14);
      FUN_0004bb3c(param_1,&local_30);
      iVar2 = (iVar5 + iVar1 + iVar6 + uVar3 * param_2) - iVar2;
      local_28 = iVar2 + uVar3;
      local_30 = iVar2 - iVar4;
    }
    FUN_0004d40e(param_1,&local_30);
  }
  return local_30;
}

