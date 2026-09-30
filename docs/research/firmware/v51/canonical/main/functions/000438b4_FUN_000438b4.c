/* Address: 000438b4; name: FUN_000438b4; body bytes: 462 */

void FUN_000438b4(int *param_1)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  
  bVar1 = *(byte *)((int)param_1 + 0x1b);
  iVar11 = param_1[1];
  iVar12 = param_1[2];
  iVar14 = param_1[4];
  iVar5 = param_1[5];
  iVar6 = param_1[3];
  uVar7 = FUN_00040396(param_1[6]);
  uVar7 = uVar7 >> 7;
  iVar10 = *param_1;
  iVar15 = param_1[7] % 8;
  sVar3 = (short)uVar7;
  if (iVar14 == 0) {
    iVar5 = 0;
    if (bVar1 < 0xfd) {
      for (; iVar5 < iVar12; iVar5 = iVar5 + 1) {
        for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
          iVar8 = iVar14 + iVar15;
          if (((uint)((int)(short)(0xff - (ushort)bVar1) *
                      (int)(short)(*(byte *)(iVar10 + ((int)(iVar8 + ((uint)(iVar8 >> 0x1f) >> 0x1d)
                                                            ) >> 3)) >> (7U - iVar8 % 8 & 0xff) & 1)
                     + (int)(short)(ushort)bVar1 * (int)sVar3) / 0xff & 0xff) == 0) {
            FUN_00027368(iVar10);
          }
          else {
            FUN_0005e778();
          }
        }
        iVar10 = iVar10 + iVar6;
      }
    }
    else {
      for (; iVar5 < iVar12; iVar5 = iVar5 + 1) {
        for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
          if (uVar7 == 0) {
            FUN_00027368(iVar10,iVar14 + iVar15);
          }
          else {
            FUN_0005e778();
          }
        }
        iVar10 = iVar10 + iVar6;
      }
    }
  }
  else {
    iVar8 = 0;
    if (bVar1 < 0xfd) {
      for (; iVar8 < iVar12; iVar8 = iVar8 + 1) {
        for (iVar13 = 0; iVar13 < iVar11; iVar13 = iVar13 + 1) {
          if (*(byte *)(iVar14 + iVar13) != 0) {
            iVar9 = iVar13 + iVar15;
            uVar2 = (ushort)((uint)((int)(short)(ushort)*(byte *)(iVar14 + iVar13) *
                                   (int)(short)(ushort)bVar1) / 0xff) & 0xff;
            if (((uint)((int)(short)(0xff - uVar2) *
                        (int)(short)(*(byte *)(iVar10 + ((int)(iVar9 + ((uint)(iVar9 >> 0x1f) >>
                                                                       0x1d)) >> 3)) >>
                                     (7U - iVar9 % 8 & 0xff) & 1) + (int)(short)uVar2 * (int)sVar3)
                 / 0xff & 0xff) == 0) {
              FUN_00027368(iVar10);
            }
            else {
              FUN_0005e778();
            }
          }
        }
        iVar10 = iVar10 + iVar6;
        iVar14 = iVar14 + iVar5;
      }
    }
    else {
      for (; iVar8 < iVar12; iVar8 = iVar8 + 1) {
        for (iVar13 = 0; iVar13 < iVar11; iVar13 = iVar13 + 1) {
          bVar1 = *(byte *)(iVar14 + iVar13);
          if (bVar1 != 0) {
            uVar4 = uVar7;
            if (bVar1 != 0xff) {
              iVar9 = iVar13 + iVar15;
              uVar4 = (uint)((int)(short)(0xff - (ushort)bVar1) *
                             (int)(short)(*(byte *)(iVar10 + ((int)(iVar9 + ((uint)(iVar9 >> 0x1f)
                                                                            >> 0x1d)) >> 3)) >>
                                          (7U - iVar9 % 8 & 0xff) & 1) +
                            (int)(short)(ushort)bVar1 * (int)sVar3) / 0xff & 0xff;
            }
            if (uVar4 == 0) {
              FUN_00027368(iVar10,iVar13 + iVar15);
            }
            else {
              FUN_0005e778(iVar10);
            }
          }
        }
        iVar10 = iVar10 + iVar6;
        iVar14 = iVar14 + iVar5;
      }
    }
  }
  return;
}

