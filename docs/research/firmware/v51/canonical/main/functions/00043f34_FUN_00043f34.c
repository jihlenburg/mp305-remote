/* Address: 00043f34; name: FUN_00043f34; body bytes: 578 */

void FUN_00043f34(int *param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined1 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint extraout_r1;
  int iVar11;
  int iVar12;
  int iVar13;
  uint unaff_r8;
  uint uVar14;
  int iVar15;
  uint uVar16;
  int local_6c;
  int local_60;
  int local_48;
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [4];
  int local_34;
  int iStack_30;
  int *piStack_2c;
  int local_28;
  
  bVar1 = *(byte *)(param_1 + 8);
  if (bVar1 == 0x10) {
    iVar12 = param_1[1];
    iVar5 = param_1[2];
    bVar1 = *(byte *)((int)param_1 + 0x21);
    uVar16 = (uint)bVar1;
    iVar11 = *param_1;
    piStack_2c = (int *)param_1[3];
    iVar7 = param_1[6];
    iStack_30 = param_1[7];
    iVar13 = param_1[4];
    iVar6 = param_1[5];
    FUN_000404ba(auStack_3c);
    if (*(char *)((int)param_1 + 0x22) == '\0') {
      if (iVar13 == 0) {
        iVar6 = 0;
        if (uVar16 < 0xfd) {
          for (; iVar6 < iVar5; iVar6 = iVar6 + 1) {
            for (iVar13 = 0; iVar13 < iVar12; iVar13 = iVar13 + 1) {
              puVar4 = (undefined4 *)(iVar7 + iVar13 * 4);
              uVar16 = FUN_0003ff24(*puVar4);
              FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar16 & 0xff |
                           (int)(short)(ushort)*(byte *)((int)puVar4 + 3) *
                           (int)(short)(ushort)bVar1 & 0xffffff00U,iVar11 + iVar13 * 2,auStack_3c);
              unaff_r8 = unaff_r8 & 0xffffff00;
            }
            iVar11 = iVar11 + (int)piStack_2c;
            iVar7 = iVar7 + iStack_30;
          }
        }
        else {
          for (; iVar6 < iVar5; iVar6 = iVar6 + 1) {
            for (iVar13 = 0; iVar13 < iVar12; iVar13 = iVar13 + 1) {
              puVar4 = (undefined4 *)(iVar7 + iVar13 * 4);
              uVar16 = FUN_0003ff24(*puVar4);
              FUN_0003ff88((uint)param_1 & 0xffff0000 | uVar16 & 0xff |
                           (uint)*(byte *)((int)puVar4 + 3) << 8,iVar11 + iVar13 * 2,auStack_3c);
              param_1 = (int *)((uint)param_1 & 0xffffff00);
            }
            iVar11 = iVar11 + (int)piStack_2c;
            iVar7 = iVar7 + iStack_30;
          }
        }
      }
      else {
        iVar15 = 0;
        if (uVar16 < 0xfd) {
          for (; iVar15 < iVar5; iVar15 = iVar15 + 1) {
            for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
              puVar4 = (undefined4 *)(iVar7 + iVar8 * 4);
              uVar14 = FUN_0003ff24(*puVar4);
              FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar14 & 0xff |
                           (uVar16 * (int)(short)(ushort)*(byte *)((int)puVar4 + 3) *
                                     (int)(short)(ushort)*(byte *)(iVar13 + iVar8) >> 0x10) << 8,
                           iVar11 + iVar8 * 2,auStack_3c);
              unaff_r8 = unaff_r8 & 0xffffff00;
            }
            iVar11 = iVar11 + (int)piStack_2c;
            iVar13 = iVar13 + iVar6;
            iVar7 = iVar7 + iStack_30;
          }
        }
        else {
          for (; iVar15 < iVar5; iVar15 = iVar15 + 1) {
            for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
              puVar4 = (undefined4 *)(iVar7 + iVar8 * 4);
              uVar16 = FUN_0003ff24(*puVar4);
              FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar16 & 0xff |
                           (int)(short)(ushort)*(byte *)((int)puVar4 + 3) *
                           (int)(short)(ushort)*(byte *)(iVar13 + iVar8) & 0xffffff00U,
                           iVar11 + iVar8 * 2,auStack_3c);
              unaff_r8 = unaff_r8 & 0xffffff00;
            }
            iVar11 = iVar11 + (int)piStack_2c;
            iVar13 = iVar13 + iVar6;
            iVar7 = iVar7 + iStack_30;
          }
        }
      }
    }
    else {
      for (iVar15 = 0; iVar15 < iVar5; iVar15 = iVar15 + 1) {
        for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
          puVar4 = (undefined4 *)(iVar7 + iVar8 * 4);
          uVar14 = FUN_0003ff24(*puVar4);
          uVar2 = (ushort)*(byte *)((int)puVar4 + 3);
          if (iVar13 == 0) {
            uVar10 = (uint)((int)(short)uVar2 * (int)(short)(ushort)bVar1) >> 8;
          }
          else {
            uVar10 = uVar16 * (int)(short)uVar2 * (int)(short)(ushort)*(byte *)(iVar13 + iVar8) >>
                     0x10;
          }
          FUN_000248e8(iVar11 + iVar8 * 2,unaff_r8 & 0xffff0000 | uVar14 & 0xff | uVar10 << 8,
                       *(undefined1 *)((int)param_1 + 0x22),auStack_3c);
        }
        if (iVar13 != 0) {
          iVar13 = iVar13 + iVar6;
        }
        iVar11 = iVar11 + (int)piStack_2c;
        iVar7 = iVar7 + iStack_30;
      }
    }
    return;
  }
  if (bVar1 < 0x11) {
    if (bVar1 == 6) {
      iVar12 = param_1[1];
      iVar5 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar16 = (uint)bVar1;
      iVar7 = *param_1;
      piStack_2c = (int *)param_1[3];
      iVar11 = param_1[6];
      iStack_30 = param_1[7];
      iVar13 = param_1[4];
      iVar6 = param_1[5];
      FUN_000404ba(auStack_38);
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar13 == 0) {
          if (uVar16 < 0xfd) {
            for (uVar14 = 0; (int)uVar14 < iVar5; uVar14 = uVar14 + 1) {
              uVar10 = uVar14;
              for (iVar6 = 0; iVar6 < iVar12; iVar6 = iVar6 + 1) {
                uVar10 = FUN_0003ff88(uVar10 & 0xffff0000 | (uint)*(byte *)(iVar11 + iVar6) |
                                      uVar16 << 8,iVar7 + iVar6 * 2,auStack_38);
              }
              iVar7 = iVar7 + (int)piStack_2c;
              iVar11 = iVar11 + iStack_30;
            }
          }
          else {
            for (iVar6 = 0; iVar6 < iVar5; iVar6 = iVar6 + 1) {
              for (iVar13 = 0; iVar13 < iVar12; iVar13 = iVar13 + 1) {
                *(undefined1 *)(iVar7 + iVar13 * 2) = *(undefined1 *)(iVar11 + iVar13);
                *(undefined1 *)(iVar7 + iVar13 * 2 + 1) = 0xff;
              }
              iVar7 = iVar7 + (int)piStack_2c;
              iVar11 = iVar11 + iStack_30;
            }
          }
        }
        else {
          uVar14 = 0;
          if (uVar16 < 0xfd) {
            for (; (int)uVar14 < iVar5; uVar14 = uVar14 + 1) {
              uVar16 = uVar14;
              for (iVar15 = 0; iVar15 < iVar12; iVar15 = iVar15 + 1) {
                uVar16 = FUN_0003ff88(uVar16 & 0xffff0000 | (uint)*(byte *)(iVar11 + iVar15) |
                                      (int)(short)(ushort)*(byte *)(iVar13 + iVar15) *
                                      (int)(short)(ushort)bVar1 & 0xffffff00U,iVar7 + iVar15 * 2,
                                      auStack_38);
              }
              iVar7 = iVar7 + (int)piStack_2c;
              iVar13 = iVar13 + iVar6;
              iVar11 = iVar11 + iStack_30;
            }
          }
          else {
            for (; (int)uVar14 < iVar5; uVar14 = uVar14 + 1) {
              uVar16 = uVar14;
              for (iVar15 = 0; iVar15 < iVar12; iVar15 = iVar15 + 1) {
                uVar16 = FUN_0003ff88(uVar16 & 0xffff0000 | (uint)*(byte *)(iVar11 + iVar15) |
                                      (uint)*(byte *)(iVar13 + iVar15) << 8,iVar7 + iVar15 * 2,
                                      auStack_38);
              }
              iVar7 = iVar7 + (int)piStack_2c;
              iVar13 = iVar13 + iVar6;
              iVar11 = iVar11 + iStack_30;
            }
          }
        }
      }
      else {
        for (uVar14 = 0; (int)uVar14 < iVar5; uVar14 = uVar14 + 1) {
          uVar10 = uVar14;
          for (iVar15 = 0; iVar15 < iVar12; iVar15 = iVar15 + 1) {
            if (iVar13 == 0) {
              uVar10 = uVar10 & 0xffff0000 | (uint)*(byte *)(iVar11 + iVar15) | uVar16 << 8;
            }
            else {
              uVar10 = uVar10 & 0xffff0000 | (uint)*(byte *)(iVar11 + iVar15) |
                       (int)(short)(ushort)*(byte *)(iVar13 + iVar15) * (int)(short)(ushort)bVar1 &
                       0xffffff00U;
            }
            FUN_000248e8(iVar7 + iVar15 * 2,uVar10,*(undefined1 *)((int)param_1 + 0x22),auStack_38);
            uVar10 = extraout_r1;
          }
          if (iVar13 != 0) {
            iVar13 = iVar13 + iVar6;
          }
          iVar7 = iVar7 + (int)piStack_2c;
          iVar11 = iVar11 + iStack_30;
        }
      }
      return;
    }
    if (bVar1 == 7) {
      FUN_00038200();
      return;
    }
    if (bVar1 != 0xf) {
      return;
    }
    local_28 = 3;
  }
  else {
    if (bVar1 != 0x11) {
      if (bVar1 == 0x12) {
        FUN_0005b3b8();
        return;
      }
      if (bVar1 != 0x15) {
        return;
      }
      FUN_000229e0();
      return;
    }
    local_28 = 4;
  }
  iVar13 = param_1[1];
  iVar5 = param_1[2];
  bVar1 = *(byte *)((int)param_1 + 0x21);
  uVar16 = (uint)bVar1;
  iVar11 = *param_1;
  local_34 = param_1[3];
  iVar12 = param_1[6];
  iVar6 = param_1[7];
  iVar15 = param_1[4];
  iVar7 = param_1[5];
  piStack_2c = param_1;
  FUN_000404ba(auStack_3c);
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar15 == 0) {
      if (0xfc < uVar16) {
        for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
          unaff_r8 = 0;
          for (iVar15 = 0; iVar15 < iVar13; iVar15 = iVar15 + 1) {
            uVar3 = FUN_0003fef6(iVar12 + unaff_r8);
            *(undefined1 *)(iVar11 + iVar15 * 2) = uVar3;
            *(undefined1 *)(iVar11 + iVar15 * 2 + 1) = 0xff;
            unaff_r8 = unaff_r8 + local_28;
          }
          iVar11 = iVar11 + local_34;
          iVar12 = iVar12 + iVar6;
        }
        if (0xfc < uVar16) {
          return;
        }
      }
      for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
        iVar8 = 0;
        for (iVar15 = 0; iVar15 < iVar13; iVar15 = iVar15 + 1) {
          uVar14 = FUN_0003fef6(iVar12 + iVar8);
          FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar14 & 0xff | uVar16 << 8,iVar11 + iVar15 * 2,
                       auStack_3c);
          iVar8 = iVar8 + local_28;
          unaff_r8 = unaff_r8 & 0xffffff00;
        }
        iVar11 = iVar11 + local_34;
        iVar12 = iVar12 + iVar6;
      }
    }
    else {
      if (0xfc < uVar16) {
        for (iVar8 = 0; iVar8 < iVar5; iVar8 = iVar8 + 1) {
          local_48 = 0;
          local_60 = 0;
          for (iVar9 = 0; iVar9 < iVar13; iVar9 = iVar9 + 1) {
            uVar14 = FUN_0003fef6(local_60 + iVar12);
            FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar14 & 0xff |
                         (uint)*(byte *)(iVar15 + local_48) << 8,iVar11 + iVar9 * 2,auStack_3c);
            local_48 = local_48 + 1;
            local_60 = local_60 + local_28;
            unaff_r8 = unaff_r8 & 0xffffff00;
          }
          iVar11 = iVar11 + local_34;
          iVar15 = iVar15 + iVar7;
          iVar12 = iVar12 + iVar6;
        }
        if (iVar15 == 0) {
          return;
        }
        if (0xfc < uVar16) {
          return;
        }
      }
      for (iVar8 = 0; iVar8 < iVar5; iVar8 = iVar8 + 1) {
        local_6c = 0;
        local_60 = 0;
        for (iVar9 = 0; iVar9 < iVar13; iVar9 = iVar9 + 1) {
          uVar16 = FUN_0003fef6(local_60 + iVar12);
          FUN_0003ff88(unaff_r8 & 0xffff0000 | uVar16 & 0xff |
                       (int)(short)(ushort)*(byte *)(iVar15 + local_6c) * (int)(short)(ushort)bVar1
                       & 0xffffff00U,iVar11 + iVar9 * 2,auStack_3c);
          local_6c = local_6c + 1;
          local_60 = local_60 + local_28;
          unaff_r8 = unaff_r8 & 0xffffff00;
        }
        iVar11 = iVar11 + local_34;
        iVar15 = iVar15 + iVar7;
        iVar12 = iVar12 + iVar6;
      }
    }
  }
  else {
    for (iVar8 = 0; iVar8 < iVar5; iVar8 = iVar8 + 1) {
      iVar9 = 0;
      for (uVar14 = 0; (int)uVar14 < iVar13; uVar14 = uVar14 + 1) {
        uVar10 = FUN_0003fef6(iVar9 + iVar12);
        if (iVar15 == 0) {
          uVar10 = uVar14 & 0xffff0000 | uVar10 & 0xff | uVar16 << 8;
        }
        else {
          uVar10 = uVar14 & 0xffff0000 | uVar10 & 0xff |
                   (int)(short)(ushort)*(byte *)(iVar15 + uVar14) * (int)(short)(ushort)bVar1 &
                   0xffffff00U;
        }
        FUN_000248e8(iVar11 + uVar14 * 2,uVar10,*(undefined1 *)((int)param_1 + 0x22),auStack_3c);
        iVar9 = iVar9 + local_28;
      }
      if (iVar15 != 0) {
        iVar15 = iVar15 + iVar7;
      }
      iVar11 = iVar11 + local_34;
      iVar12 = iVar12 + iVar6;
    }
  }
  return;
}

