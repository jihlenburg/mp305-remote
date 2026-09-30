/* Address: 00043748; name: FUN_00043748; body bytes: 358 */

void FUN_00043748(int *param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined1 auStack_40 [28];
  
  bVar1 = *(byte *)((int)param_1 + 0x1b);
  iVar9 = param_1[1];
  iVar10 = param_1[2];
  iVar11 = param_1[4];
  iVar2 = param_1[5];
  iVar3 = param_1[3];
  FUN_000404e2(auStack_40);
  if (iVar11 == 0) {
    if (bVar1 < 0xfd) {
      uVar7 = FUN_0004053c(param_1[6],bVar1);
      iVar11 = *param_1;
      for (iVar2 = 0; iVar2 < iVar10; iVar2 = iVar2 + 1) {
        for (iVar5 = 0; iVar5 < iVar9; iVar5 = iVar5 + 1) {
          puVar13 = (undefined4 *)(iVar11 + iVar5 * 4);
          uVar6 = FUN_00040106(uVar7,*puVar13,auStack_40);
          *puVar13 = uVar6;
        }
        iVar11 = iVar11 + iVar3;
      }
    }
    else {
      uVar7 = FUN_00040584(param_1[6]);
      iVar2 = *param_1;
      for (iVar11 = 0; iVar11 < iVar10; iVar11 = iVar11 + 1) {
        for (iVar5 = 0; iVar5 < iVar9 + -0x10; iVar5 = iVar5 + 0x10) {
          *(undefined4 *)(iVar2 + iVar5 * 4) = uVar7;
          iVar12 = iVar2 + iVar5 * 4;
          *(undefined4 *)(iVar12 + 4) = uVar7;
          *(undefined4 *)(iVar12 + 8) = uVar7;
          *(undefined4 *)(iVar12 + 0xc) = uVar7;
          *(undefined4 *)(iVar12 + 0x10) = uVar7;
          *(undefined4 *)(iVar12 + 0x14) = uVar7;
          *(undefined4 *)(iVar12 + 0x18) = uVar7;
          *(undefined4 *)(iVar12 + 0x1c) = uVar7;
          *(undefined4 *)(iVar12 + 0x20) = uVar7;
          *(undefined4 *)(iVar12 + 0x24) = uVar7;
          *(undefined4 *)(iVar12 + 0x28) = uVar7;
          *(undefined4 *)(iVar12 + 0x2c) = uVar7;
          *(undefined4 *)(iVar12 + 0x30) = uVar7;
          *(undefined4 *)(iVar12 + 0x34) = uVar7;
          *(undefined4 *)(iVar12 + 0x38) = uVar7;
          *(undefined4 *)(iVar12 + 0x3c) = uVar7;
        }
        for (; iVar5 < iVar9; iVar5 = iVar5 + 1) {
          *(undefined4 *)(iVar2 + iVar5 * 4) = uVar7;
        }
        iVar2 = iVar2 + iVar3;
      }
    }
  }
  else if (bVar1 < 0xfd) {
    uVar4 = FUN_0004053c(param_1[6],bVar1);
    iVar12 = *param_1;
    for (iVar5 = 0; iVar5 < iVar10; iVar5 = iVar5 + 1) {
      for (iVar8 = 0; iVar8 < iVar9; iVar8 = iVar8 + 1) {
        uVar4 = uVar4 & 0xffffff |
                ((uint)((int)(short)(ushort)*(byte *)(iVar11 + iVar8) * (int)(short)(ushort)bVar1)
                >> 8) << 0x18;
        puVar13 = (undefined4 *)(iVar12 + iVar8 * 4);
        uVar7 = FUN_00040106(uVar4,*puVar13,auStack_40);
        *puVar13 = uVar7;
      }
      iVar12 = iVar12 + iVar3;
      iVar11 = iVar11 + iVar2;
    }
  }
  else {
    uVar4 = FUN_0004053c(param_1[6],0xff);
    iVar12 = *param_1;
    for (iVar5 = 0; iVar5 < iVar10; iVar5 = iVar5 + 1) {
      for (iVar8 = 0; iVar8 < iVar9; iVar8 = iVar8 + 1) {
        uVar4 = uVar4 & 0xffffff | (uint)*(byte *)(iVar11 + iVar8) << 0x18;
        puVar13 = (undefined4 *)(iVar12 + iVar8 * 4);
        uVar7 = FUN_00040106(uVar4,*puVar13,auStack_40);
        *puVar13 = uVar7;
      }
      iVar11 = iVar11 + iVar2;
      iVar12 = iVar12 + iVar3;
    }
  }
  return;
}

