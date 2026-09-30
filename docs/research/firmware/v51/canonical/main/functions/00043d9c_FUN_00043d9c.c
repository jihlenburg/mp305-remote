/* Address: 00043d9c; name: FUN_00043d9c; body bytes: 400 */

undefined8 FUN_00043d9c(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *local_38;
  int local_34;
  int local_30;
  undefined4 local_2c;
  
  bVar1 = *(byte *)((int)param_1 + 0x1b);
  iVar2 = param_1[4];
  iVar6 = param_1[1];
  iVar8 = param_1[2];
  local_34 = param_1[5];
  iVar9 = param_1[3];
  local_38 = param_1;
  local_30 = param_3;
  local_2c = param_4;
  if (iVar2 == 0) {
    if (bVar1 < 0xfd) {
      local_38 = (int *)FUN_00040584(param_1[6]);
      iVar3 = *param_1;
      for (iVar2 = 0; iVar2 < iVar8; iVar2 = iVar2 + 1) {
        for (iVar5 = 0; iVar5 < param_2 * iVar6; iVar5 = iVar5 + param_2) {
          FUN_000400ba(&local_38,iVar3 + iVar5,bVar1);
        }
        iVar3 = iVar3 + iVar9;
      }
    }
    else if (param_2 == 3) {
      iVar2 = *param_1;
      for (iVar3 = 0; iVar3 < iVar6 * 3; iVar3 = iVar3 + 3) {
        *(char *)(iVar2 + iVar3) = (char)param_1[6];
        *(undefined1 *)(iVar2 + iVar3 + 1) = *(undefined1 *)((int)param_1 + 0x19);
        *(undefined1 *)(iVar2 + iVar3 + 2) = *(undefined1 *)((int)param_1 + 0x1a);
      }
      iVar3 = iVar2;
      for (iVar5 = 1; iVar3 = iVar3 + iVar9, iVar5 < iVar8; iVar5 = iVar5 + 1) {
        FUN_0004a404(iVar3,iVar2,iVar6 * 3);
      }
    }
    else if (param_2 == 4) {
      uVar4 = FUN_00040584(param_1[6]);
      iVar2 = *param_1;
      for (iVar3 = 0; iVar3 < iVar8; iVar3 = iVar3 + 1) {
        for (iVar5 = 0; iVar5 <= iVar6 + -0x10; iVar5 = iVar5 + 0x10) {
          *(undefined4 *)(iVar2 + iVar5 * 4) = uVar4;
          iVar7 = iVar2 + iVar5 * 4;
          *(undefined4 *)(iVar7 + 4) = uVar4;
          *(undefined4 *)(iVar7 + 8) = uVar4;
          *(undefined4 *)(iVar7 + 0xc) = uVar4;
          *(undefined4 *)(iVar7 + 0x10) = uVar4;
          *(undefined4 *)(iVar7 + 0x14) = uVar4;
          *(undefined4 *)(iVar7 + 0x18) = uVar4;
          *(undefined4 *)(iVar7 + 0x1c) = uVar4;
          *(undefined4 *)(iVar7 + 0x20) = uVar4;
          *(undefined4 *)(iVar7 + 0x24) = uVar4;
          *(undefined4 *)(iVar7 + 0x28) = uVar4;
          *(undefined4 *)(iVar7 + 0x2c) = uVar4;
          *(undefined4 *)(iVar7 + 0x30) = uVar4;
          *(undefined4 *)(iVar7 + 0x34) = uVar4;
          *(undefined4 *)(iVar7 + 0x38) = uVar4;
          *(undefined4 *)(iVar7 + 0x3c) = uVar4;
        }
        for (; iVar5 < iVar6; iVar5 = iVar5 + 1) {
          *(undefined4 *)(iVar2 + iVar5 * 4) = uVar4;
        }
        iVar2 = iVar2 + iVar9;
      }
    }
  }
  else if (bVar1 < 0xfd) {
    local_2c = FUN_00040584(param_1[6]);
    local_38 = (int *)*param_1;
    for (local_30 = 0; local_30 < iVar8; local_30 = local_30 + 1) {
      iVar5 = 0;
      for (iVar3 = 0; iVar3 < iVar6 * param_2; iVar3 = iVar3 + param_2) {
        FUN_000400ba(&local_2c,(int)local_38 + iVar3,
                     (uint)((int)(short)(ushort)*(byte *)(iVar2 + iVar5) * (int)(short)(ushort)bVar1
                           ) >> 8);
        iVar5 = iVar5 + 1;
      }
      local_38 = (int *)((int)local_38 + iVar9);
      iVar2 = iVar2 + local_34;
    }
  }
  else {
    local_30 = FUN_00040584(param_1[6]);
    local_38 = (int *)*param_1;
    for (iVar3 = 0; iVar3 < iVar8; iVar3 = iVar3 + 1) {
      iVar7 = 0;
      for (iVar5 = 0; iVar5 < iVar6 * param_2; iVar5 = iVar5 + param_2) {
        FUN_000400ba(&local_30,(int)local_38 + iVar5,*(undefined1 *)(iVar2 + iVar7));
        iVar7 = iVar7 + 1;
      }
      local_38 = (int *)((int)local_38 + iVar9);
      iVar2 = iVar2 + local_34;
    }
  }
  return CONCAT44(local_34,local_38);
}

