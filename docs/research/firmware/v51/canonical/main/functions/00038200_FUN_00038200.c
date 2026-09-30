/* Address: 00038200; name: FUN_00038200; body bytes: 344 */

void FUN_00038200(int *param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint unaff_r8;
  int iVar10;
  uint uVar11;
  int iVar12;
  undefined1 auStack_34 [8];
  int local_2c;
  int local_28;
  
  iVar8 = param_1[1];
  iVar9 = param_1[2];
  bVar1 = *(byte *)((int)param_1 + 0x21);
  uVar11 = (uint)bVar1;
  iVar6 = *param_1;
  local_28 = param_1[3];
  iVar12 = param_1[6];
  local_2c = param_1[7];
  iVar10 = param_1[4];
  iVar3 = param_1[5];
  FUN_000404ba(auStack_34);
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar10 == 0) {
      iVar3 = 0;
      if (uVar11 < 0xfd) {
        for (; iVar3 < iVar9; iVar3 = iVar3 + 1) {
          for (iVar10 = 0; iVar10 < iVar8; iVar10 = iVar10 + 1) {
            iVar5 = FUN_00036e84(iVar12,iVar10);
            FUN_0003ff88(unaff_r8 & 0xffff0000 | iVar5 * 0xff & 0xffU | uVar11 << 8,
                         iVar6 + iVar10 * 2,auStack_34);
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar6 = iVar6 + local_28;
          iVar12 = iVar12 + local_2c;
        }
      }
      else {
        for (; iVar3 < iVar9; iVar3 = iVar3 + 1) {
          for (iVar10 = 0; iVar10 < iVar8; iVar10 = iVar10 + 1) {
            cVar2 = FUN_00036e84(iVar12,iVar10);
            *(char *)(iVar6 + iVar10 * 2) = -cVar2;
            *(undefined1 *)(iVar6 + iVar10 * 2 + 1) = 0xff;
          }
          iVar6 = iVar6 + local_28;
          iVar12 = iVar12 + local_2c;
        }
      }
    }
    else {
      iVar5 = 0;
      if (uVar11 < 0xfd) {
        for (iVar5 = 0; iVar5 < iVar9; iVar5 = iVar5 + 1) {
          for (iVar7 = 0; iVar7 < iVar8; iVar7 = iVar7 + 1) {
            iVar4 = FUN_00036e84(iVar12,iVar7);
            FUN_0003ff88(unaff_r8 & 0xffff0000 | iVar4 * 0xff & 0xffU |
                         (int)(short)(ushort)*(byte *)(iVar10 + iVar7) * (int)(short)(ushort)bVar1 &
                         0xffffff00U,iVar6 + iVar7 * 2,auStack_34);
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar6 = iVar6 + local_28;
          iVar12 = iVar12 + local_2c;
          iVar10 = iVar10 + iVar3;
        }
      }
      else {
        for (; iVar5 < iVar9; iVar5 = iVar5 + 1) {
          for (iVar7 = 0; iVar7 < iVar8; iVar7 = iVar7 + 1) {
            iVar4 = FUN_00036e84(iVar12,iVar7);
            FUN_0003ff88(unaff_r8 & 0xffff0000 | iVar4 * 0xff & 0xffU |
                         (uint)*(byte *)(iVar10 + iVar7) << 8,iVar6 + iVar7 * 2,auStack_34);
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar12 = iVar12 + local_2c;
          iVar6 = iVar6 + local_28;
          iVar10 = iVar10 + iVar3;
        }
      }
    }
  }
  return;
}

