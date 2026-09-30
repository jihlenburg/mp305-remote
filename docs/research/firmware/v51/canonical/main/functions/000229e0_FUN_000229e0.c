/* Address: 000229e0; name: FUN_000229e0; body bytes: 468 */

void FUN_000229e0(int *param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  byte bVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined2 local_64;
  undefined2 local_60;
  undefined1 auStack_40 [16];
  int local_30;
  int local_2c;
  
  iVar11 = param_1[1];
  iVar5 = param_1[2];
  bVar3 = *(byte *)((int)param_1 + 0x21);
  uVar13 = (uint)bVar3;
  iVar10 = *param_1;
  local_2c = param_1[3];
  iVar9 = param_1[6];
  local_30 = param_1[7];
  iVar12 = param_1[4];
  iVar6 = param_1[5];
  FUN_000404ba(auStack_40);
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar12 == 0) {
      iVar6 = 0;
      if (uVar13 < 0xfd) {
        for (; iVar6 < iVar5; iVar6 = iVar6 + 1) {
          for (iVar12 = 0; iVar12 < iVar11; iVar12 = iVar12 + 1) {
            uVar1 = *(ushort *)(iVar9 + iVar12 * 2);
            local_64 = CONCAT11((char)((uint)((int)(short)(uVar1 >> 8) * (int)(short)(ushort)bVar3)
                                      >> 8),(char)uVar1);
            FUN_0003ff88(local_64,iVar10 + iVar12 * 2,auStack_40);
          }
          iVar10 = iVar10 + local_2c;
          iVar9 = iVar9 + local_30;
        }
      }
      else {
        for (; iVar6 < iVar5; iVar6 = iVar6 + 1) {
          for (iVar12 = 0; iVar12 < iVar11; iVar12 = iVar12 + 1) {
            FUN_0003ff88(*(undefined2 *)(iVar9 + iVar12 * 2),iVar10 + iVar12 * 2,auStack_40);
          }
          iVar10 = iVar10 + local_2c;
          iVar9 = iVar9 + local_30;
        }
      }
    }
    else {
      iVar7 = 0;
      if (uVar13 < 0xfd) {
        for (; iVar7 < iVar5; iVar7 = iVar7 + 1) {
          for (iVar8 = 0; iVar8 < iVar11; iVar8 = iVar8 + 1) {
            uVar1 = *(ushort *)(iVar9 + iVar8 * 2);
            local_60._0_1_ = (undefined1)uVar1;
            local_60 = CONCAT11((char)((int)(short)(uVar1 >> 8) *
                                       (int)(short)(ushort)*(byte *)(iVar12 + iVar8) * uVar13 >>
                                      0x10),(undefined1)local_60);
            FUN_0003ff88(local_60,iVar10 + iVar8 * 2,auStack_40);
          }
          iVar10 = iVar10 + local_2c;
          iVar12 = iVar12 + iVar6;
          iVar9 = iVar9 + local_30;
        }
      }
      else {
        for (; iVar7 < iVar5; iVar7 = iVar7 + 1) {
          for (iVar8 = 0; iVar8 < iVar11; iVar8 = iVar8 + 1) {
            uVar1 = *(ushort *)(iVar9 + iVar8 * 2);
            local_60._0_1_ = (undefined1)uVar1;
            local_60 = CONCAT11((char)((uint)((int)(short)(uVar1 >> 8) *
                                             (int)(short)(ushort)*(byte *)(iVar12 + iVar8)) >> 8),
                                (undefined1)local_60);
            FUN_0003ff88(local_60,iVar10 + iVar8 * 2,auStack_40);
          }
          iVar10 = iVar10 + local_2c;
          iVar12 = iVar12 + iVar6;
          iVar9 = iVar9 + local_30;
        }
      }
    }
  }
  else {
    for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
      for (iVar8 = 0; iVar8 < iVar11; iVar8 = iVar8 + 1) {
        uVar2 = *(undefined2 *)(iVar9 + iVar8 * 2);
        local_60._1_1_ = (byte)((ushort)uVar2 >> 8);
        if (iVar12 == 0) {
          uVar4 = (undefined1)
                  ((uint)((int)(short)(ushort)local_60._1_1_ * (int)(short)(ushort)bVar3) >> 8);
        }
        else {
          uVar4 = (undefined1)
                  ((int)(short)(ushort)local_60._1_1_ *
                   (int)(short)(ushort)*(byte *)(iVar12 + iVar8) * uVar13 >> 0x10);
        }
        local_60._0_1_ = (undefined1)uVar2;
        local_60 = CONCAT11(uVar4,(undefined1)local_60);
        FUN_000248e8(iVar10 + iVar8 * 2,local_60,*(undefined1 *)((int)param_1 + 0x22),auStack_40);
      }
      if (iVar12 != 0) {
        iVar12 = iVar12 + iVar6;
      }
      iVar10 = iVar10 + local_2c;
      iVar9 = iVar9 + local_30;
    }
  }
  return;
}

