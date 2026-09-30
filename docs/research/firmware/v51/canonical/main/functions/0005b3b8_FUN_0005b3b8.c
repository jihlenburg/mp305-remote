/* Address: 0005b3b8; name: FUN_0005b3b8; body bytes: 478 */

void FUN_0005b3b8(int *param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint unaff_r8;
  int iVar13;
  undefined1 auStack_38 [8];
  int local_30;
  int local_2c;
  
  iVar12 = param_1[1];
  iVar3 = param_1[2];
  bVar1 = *(byte *)((int)param_1 + 0x21);
  uVar4 = (uint)bVar1;
  iVar10 = *param_1;
  local_2c = param_1[3];
  iVar11 = param_1[6];
  local_30 = param_1[7];
  iVar13 = param_1[4];
  iVar5 = param_1[5];
  FUN_000404ba(auStack_38);
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar13 == 0) {
      iVar5 = 0;
      if (uVar4 < 0xfd) {
        for (; iVar5 < iVar3; iVar5 = iVar5 + 1) {
          for (iVar13 = 0; iVar13 < iVar12; iVar13 = iVar13 + 1) {
            uVar7 = FUN_0003fe7c(*(undefined2 *)(iVar11 + iVar13 * 2));
            FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar7 & 0xff | uVar4 << 8,iVar10 + iVar13 * 2,
                         auStack_38);
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar10 = iVar10 + local_2c;
          iVar11 = iVar11 + local_30;
        }
      }
      else {
        for (; iVar5 < iVar3; iVar5 = iVar5 + 1) {
          for (iVar13 = 0; iVar13 < iVar12; iVar13 = iVar13 + 1) {
            uVar2 = FUN_0003fe7c(*(undefined2 *)(iVar11 + iVar13 * 2));
            *(undefined1 *)(iVar10 + iVar13 * 2) = uVar2;
            *(undefined1 *)(iVar10 + iVar13 * 2 + 1) = 0xff;
          }
          iVar10 = iVar10 + local_2c;
          iVar11 = iVar11 + local_30;
        }
      }
    }
    else {
      iVar6 = 0;
      if (uVar4 < 0xfd) {
        for (; iVar6 < iVar3; iVar6 = iVar6 + 1) {
          for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
            uVar4 = FUN_0003fe7c(*(undefined2 *)(iVar11 + iVar8 * 2));
            FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar4 & 0xff |
                         (int)(short)(ushort)*(byte *)(iVar13 + iVar8) * (int)(short)(ushort)bVar1 &
                         0xffffff00U,iVar10 + iVar8 * 2,auStack_38);
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar10 = iVar10 + local_2c;
          iVar13 = iVar13 + iVar5;
          iVar11 = iVar11 + local_30;
        }
      }
      else {
        for (; iVar6 < iVar3; iVar6 = iVar6 + 1) {
          for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
            uVar4 = FUN_0003fe7c(*(undefined2 *)(iVar11 + iVar8 * 2));
            FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar4 & 0xff | (uint)*(byte *)(iVar13 + iVar8) << 8
                         ,iVar10 + iVar8 * 2,auStack_38);
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar10 = iVar10 + local_2c;
          iVar13 = iVar13 + iVar5;
          iVar11 = iVar11 + local_30;
        }
      }
    }
  }
  else {
    for (iVar6 = 0; iVar6 < iVar3; iVar6 = iVar6 + 1) {
      for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
        uVar9 = FUN_0003fe7c(*(undefined2 *)(iVar11 + iVar8 * 2));
        uVar7 = uVar4;
        if (iVar13 != 0) {
          uVar7 = (uint)((int)(short)(ushort)*(byte *)(iVar13 + iVar8) * (int)(short)(ushort)bVar1)
                  >> 8;
        }
        FUN_000248e8(iVar10 + iVar8 * 2,unaff_r8 & 0xffff0000 | uVar9 & 0xff | uVar7 << 8,
                     *(undefined1 *)((int)param_1 + 0x22),auStack_38);
      }
      if (iVar13 != 0) {
        iVar13 = iVar13 + iVar5;
      }
      iVar10 = iVar10 + local_2c;
      iVar11 = iVar11 + local_30;
    }
  }
  return;
}

