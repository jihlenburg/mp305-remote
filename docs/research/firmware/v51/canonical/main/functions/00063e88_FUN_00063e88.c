/* Address: 00063e88; name: FUN_00063e88; body bytes: 292 */

void FUN_00063e88(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_3c;
  uint local_38;
  int iStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  uint uStack_28;
  
  iStack_34 = param_1;
  local_30 = param_2;
  uStack_2c = param_3;
  uStack_28 = param_4;
  iVar1 = FUN_0004c924(param_1,0,0x6e);
  iVar2 = FUN_0004c924(param_1,0,0x6c);
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  iVar3 = FUN_0004c924(param_1,0,0x6d);
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  if (iVar3 == 0) {
    iVar3 = 1;
  }
  if (((iVar1 != 0) || (iVar2 != 0x100)) || (iVar3 != 0x100)) {
    local_3c = FUN_0004c924(param_1,0,0x6f);
    local_38 = FUN_0004c924(param_1,0,0x70);
    iVar4 = param_1 + 0x14;
    if (((local_3c & 0x7fffffff) >> 0x1d == 1) && ((int)(local_3c & 0x9fffffff) < 0x1fffffff)) {
      iVar5 = FUN_0003db28(iVar4);
      local_3c = local_3c & 0x9fffffff;
      if (0xfffffff < (int)local_3c) {
        local_3c = 0xfffffff - local_3c;
      }
      local_3c = (int)(local_3c * iVar5) / 100;
    }
    if (((local_38 & 0x7fffffff) >> 0x1d == 1) && ((int)(local_38 & 0x9fffffff) < 0x1fffffff)) {
      iVar4 = FUN_0003db0a(iVar4);
      local_38 = local_38 & 0x9fffffff;
      if (0xfffffff < (int)local_38) {
        local_38 = 0xfffffff - local_38;
      }
      local_38 = (int)(local_38 * iVar4) / 100;
    }
    local_3c = *(int *)(param_1 + 0x14) + local_3c;
    local_38 = *(int *)(param_1 + 0x18) + local_38;
    if (param_4 != 0) {
      iVar1 = -iVar1;
      iVar2 = (iVar2 + 0xffff) / iVar2;
      iVar3 = (iVar3 + 0xffff) / iVar3;
    }
    FUN_0004f0c4(local_30,uStack_2c,iVar1,iVar2,iVar3,&local_3c,param_4 ^ 1);
  }
  return;
}

