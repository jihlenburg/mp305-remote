/* Address: 00037a1e; name: FUN_00037a1e; body bytes: 232 */

int FUN_00037a1e(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                int param_6,int param_7,int param_8,int param_9)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_40;
  undefined1 auStack_3c [4];
  int local_38;
  int iStack_34;
  int iStack_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  
  iStack_34 = param_1;
  iStack_30 = param_2;
  local_2c = param_3;
  uStack_28 = param_4;
  iVar1 = FUN_00046bd6(param_3);
  local_40 = iVar1 + param_8 + param_9;
  iVar1 = 0;
  uVar4 = param_2 * *(int *)(param_1 + 0x2c);
  for (uVar5 = uVar4; uVar5 < *(int *)(param_1 + 0x2c) + uVar4; uVar5 = uVar5 + 1) {
    pbVar2 = *(byte **)(*(int *)(param_1 + 0x34) + uVar5 * 4);
    if (pbVar2 != (byte *)0x0) {
      iVar6 = 0;
      iVar8 = *(int *)(*(int *)(param_1 + 0x3c) + iVar1 * 4);
      while ((((uint)(iVar6 + iVar1) < *(int *)(param_1 + 0x2c) - 1U &&
              (pbVar3 = *(byte **)(*(int *)(param_1 + 0x34) + (uVar5 + iVar6) * 4),
              pbVar3 != (byte *)0x0)) && ((*pbVar3 & 1) != 0))) {
        iVar7 = iVar1 + iVar6;
        iVar6 = iVar6 + 1;
        iVar8 = iVar8 + *(int *)(*(int *)(param_1 + 0x3c) + iVar7 * 4 + 4);
      }
      if ((int)((uint)*pbVar2 << 0x1e) < 0) {
        iVar6 = FUN_00046bd6(local_2c);
        if (local_40 < iVar6 + param_8 + param_9) {
          iVar6 = FUN_00046bd6(local_2c);
          local_40 = iVar6 + param_8 + param_9;
        }
      }
      else {
        FUN_00051970(auStack_3c,*(int *)(*(int *)(param_1 + 0x34) + uVar5 * 4) + 8,local_2c,
                     uStack_28,param_5,iVar8 - (param_7 + param_6),0);
        iVar8 = param_8 + param_9 + local_38;
        if (iVar8 <= local_40) {
          iVar8 = local_40;
        }
        uVar5 = uVar5 + iVar6;
        iVar1 = iVar1 + iVar6;
        local_40 = iVar8;
      }
    }
    iVar1 = iVar1 + 1;
  }
  return local_40;
}

