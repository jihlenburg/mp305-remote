/* Address: 000435ea; name: FUN_000435ea; body bytes: 348 */

undefined8 FUN_000435ea(int *param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint unaff_r8;
  uint uVar10;
  int iVar11;
  int *piStack_38;
  undefined4 uStack_34;
  int local_30;
  undefined4 local_2c;
  
  bVar1 = *(byte *)((int)param_1 + 0x1b);
  uVar10 = (uint)bVar1;
  iVar7 = param_1[1];
  iVar9 = param_1[2];
  iVar8 = param_1[4];
  local_2c = param_1[5];
  local_30 = param_1[3];
  piStack_38 = param_1;
  uStack_34 = param_2;
  FUN_000404ba(&piStack_38);
  if (iVar8 == 0) {
    if (uVar10 < 0xfd) {
      uVar4 = FUN_00040396(param_1[6]);
      iVar3 = *param_1;
      for (iVar8 = 0; iVar8 < iVar9; iVar8 = iVar8 + 1) {
        for (iVar11 = 0; iVar11 < iVar7; iVar11 = iVar11 + 1) {
          FUN_0003ff88(uVar4 & 0xff | uVar10 << 8,iVar3 + iVar11 * 2,&piStack_38);
        }
        iVar3 = iVar3 + local_30;
      }
    }
    else {
      uVar2 = FUN_00040396(param_1[6]);
      local_2c._0_2_ = CONCAT11(0xff,uVar2);
      iVar8 = *param_1;
      for (iVar3 = 0; iVar3 < iVar9; iVar3 = iVar3 + 1) {
        for (iVar11 = 0; iVar11 < iVar7 + -0x10; iVar11 = iVar11 + 0x10) {
          puVar5 = (undefined2 *)(iVar8 + iVar11 * 2);
          *puVar5 = (undefined2)local_2c;
          puVar5[1] = (undefined2)local_2c;
          puVar5[2] = (undefined2)local_2c;
          puVar5[3] = (undefined2)local_2c;
          puVar5[4] = (undefined2)local_2c;
          puVar5[5] = (undefined2)local_2c;
          puVar5[6] = (undefined2)local_2c;
          puVar5[7] = (undefined2)local_2c;
          puVar5[8] = (undefined2)local_2c;
          puVar5[9] = (undefined2)local_2c;
          puVar5[10] = (undefined2)local_2c;
          puVar5[0xb] = (undefined2)local_2c;
          puVar5[0xc] = (undefined2)local_2c;
          puVar5[0xd] = (undefined2)local_2c;
          puVar5[0xe] = (undefined2)local_2c;
          puVar5[0xf] = (undefined2)local_2c;
        }
        for (; iVar11 < iVar7; iVar11 = iVar11 + 1) {
          *(undefined2 *)(iVar8 + iVar11 * 2) = (undefined2)local_2c;
        }
        iVar8 = iVar8 + local_30;
      }
    }
  }
  else if (uVar10 < 0xfd) {
    uVar10 = FUN_00040396(param_1[6]);
    uVar10 = unaff_r8 & 0xffffff00 | uVar10 & 0xff;
    iVar11 = *param_1;
    for (iVar3 = 0; iVar3 < iVar9; iVar3 = iVar3 + 1) {
      for (iVar6 = 0; iVar6 < iVar7; iVar6 = iVar6 + 1) {
        uVar10 = uVar10 & 0xffff00ff |
                 (int)(short)(ushort)*(byte *)(iVar8 + iVar6) * (int)(short)(ushort)bVar1 &
                 0xffffff00U;
        FUN_0003ff88(uVar10,iVar11 + iVar6 * 2,&piStack_38);
      }
      iVar11 = iVar11 + local_30;
      iVar8 = iVar8 + local_2c;
    }
  }
  else {
    uVar10 = FUN_00040396(param_1[6]);
    uVar10 = unaff_r8 & 0xffffff00 | uVar10 & 0xff;
    iVar11 = *param_1;
    for (iVar3 = 0; iVar3 < iVar9; iVar3 = iVar3 + 1) {
      for (iVar6 = 0; iVar6 < iVar7; iVar6 = iVar6 + 1) {
        uVar10 = uVar10 & 0xffff00ff | (uint)*(byte *)(iVar8 + iVar6) << 8;
        FUN_0003ff88(uVar10,iVar11 + iVar6 * 2,&piStack_38);
      }
      iVar8 = iVar8 + local_2c;
      iVar11 = iVar11 + local_30;
    }
  }
  return CONCAT44(uStack_34,piStack_38);
}

