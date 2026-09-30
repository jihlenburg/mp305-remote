/* Address: 0004407e; name: FUN_0004407e; body bytes: 3030 */

void FUN_0004407e(int *param_1,uint param_2)

{
  byte bVar1;
  undefined1 uVar2;
  ushort uVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  int local_60;
  undefined4 local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  int local_34;
  undefined4 local_30;
  int *local_2c;
  uint local_28;
  
  bVar1 = *(byte *)(param_1 + 8);
  local_2c = param_1;
  local_28 = param_2;
  if (bVar1 == 0x10) {
    iVar14 = param_1[1];
    iVar11 = param_1[2];
    bVar1 = *(byte *)((int)param_1 + 0x21);
    uVar16 = (uint)bVar1;
    iVar13 = *param_1;
    local_3c = param_1[3];
    iVar12 = param_1[6];
    local_40 = param_1[7];
    iVar15 = param_1[4];
    local_34 = param_1[5];
    if (*(char *)((int)param_1 + 0x22) == '\0') {
      if (iVar15 == 0) {
        iVar15 = 0;
        if (uVar16 < 0xfd) {
          for (; iVar15 < iVar11; iVar15 = iVar15 + 1) {
            iVar9 = 0;
            for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
              iVar17 = iVar12 + iVar8 * 4;
              FUN_000400ba(iVar17,iVar13 + iVar9,
                           (uint)((int)(short)(ushort)*(byte *)(iVar17 + 3) *
                                 (int)(short)(ushort)bVar1) >> 8);
              iVar9 = iVar9 + local_28;
            }
            iVar13 = iVar13 + local_3c;
            iVar12 = iVar12 + local_40;
          }
        }
        else {
          for (; iVar15 < iVar11; iVar15 = iVar15 + 1) {
            iVar9 = 0;
            for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
              iVar17 = iVar12 + iVar8 * 4;
              FUN_000400ba(iVar17,iVar13 + iVar9,*(undefined1 *)(iVar17 + 3));
              iVar9 = iVar9 + local_28;
            }
            iVar13 = iVar13 + local_3c;
            iVar12 = iVar12 + local_40;
          }
        }
      }
      else {
        iVar8 = 0;
        if (uVar16 < 0xfd) {
          while (iVar8 < iVar11) {
            iVar17 = 0;
            local_38 = iVar8;
            for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
              iVar8 = iVar12 + iVar9 * 4;
              FUN_000400ba(iVar8,iVar13 + iVar17,
                           (int)(short)(ushort)*(byte *)(iVar8 + 3) *
                           (int)(short)(ushort)*(byte *)(iVar15 + iVar9) * uVar16 >> 0x10);
              iVar17 = iVar17 + local_28;
            }
            iVar13 = iVar13 + local_3c;
            iVar15 = iVar15 + local_34;
            iVar12 = iVar12 + local_40;
            iVar8 = local_38 + 1;
          }
        }
        else {
          for (; iVar8 < iVar11; iVar8 = iVar8 + 1) {
            iVar17 = 0;
            for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
              iVar6 = iVar12 + iVar9 * 4;
              FUN_000400ba(iVar6,iVar13 + iVar17,
                           (uint)((int)(short)(ushort)*(byte *)(iVar6 + 3) *
                                 (int)(short)(ushort)*(byte *)(iVar15 + iVar9)) >> 8);
              iVar17 = iVar17 + local_28;
            }
            iVar13 = iVar13 + local_3c;
            iVar15 = iVar15 + local_34;
            iVar12 = iVar12 + local_40;
          }
        }
      }
    }
    else {
      for (local_30 = (int *)0x0; (int)local_30 < iVar11; local_30 = (int *)((int)local_30 + 1)) {
        local_38 = 0;
        for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
          uVar10 = *(uint *)(iVar12 + iVar8 * 4);
          bVar4 = (byte)(uVar10 >> 0x18);
          if (iVar15 == 0) {
            uVar7 = (uint)((int)(short)(ushort)bVar4 * (int)(short)(ushort)bVar1) >> 8;
          }
          else {
            uVar7 = (int)(short)(ushort)bVar4 * (int)(short)(ushort)*(byte *)(iVar15 + local_38) *
                    uVar16 >> 0x10;
          }
          FUN_00024a98(local_38 + iVar13,uVar10 & 0xffffff | uVar7 << 0x18,
                       *(undefined1 *)((int)param_1 + 0x22));
          local_38 = local_38 + local_28;
        }
        if (iVar15 != 0) {
          iVar15 = iVar15 + local_34;
        }
        iVar13 = iVar13 + local_3c;
        iVar12 = iVar12 + local_40;
      }
    }
    return;
  }
  if (bVar1 < 0x11) {
    if (bVar1 == 6) {
      iVar14 = param_1[1];
      iVar11 = param_1[2];
      local_4c = (uint)*(byte *)((int)param_1 + 0x21);
      iVar13 = *param_1;
      local_38 = param_1[3];
      iVar12 = param_1[6];
      local_28 = param_1[7];
      iVar15 = param_1[4];
      local_30 = (int *)param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar15 == 0) {
          if (local_4c < 0xfd) {
            for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar8),iVar13 + iVar9,local_4c);
                iVar9 = iVar9 + param_2;
              }
              iVar13 = iVar13 + local_38;
              iVar12 = iVar12 + local_28;
            }
          }
          else {
            for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                *(undefined1 *)(iVar13 + iVar9 + 2) = *(undefined1 *)(iVar12 + iVar8);
                *(undefined1 *)(iVar13 + iVar9 + 1) = *(undefined1 *)(iVar12 + iVar8);
                *(undefined1 *)(iVar13 + iVar9) = *(undefined1 *)(iVar12 + iVar8);
                iVar9 = iVar9 + param_2;
              }
              iVar13 = iVar13 + local_38;
              iVar12 = iVar12 + local_28;
            }
          }
        }
        else {
          local_48 = 0;
          if (local_4c < 0xfd) {
            for (; (int)local_48 < iVar11; local_48 = local_48 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar8),iVar13 + iVar9,
                             (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar8) *
                                   (int)(short)local_4c) >> 8);
                iVar9 = iVar9 + param_2;
              }
              iVar13 = iVar13 + local_38;
              iVar15 = iVar15 + (int)local_30;
              iVar12 = iVar12 + local_28;
            }
          }
          else {
            for (; (int)local_48 < iVar11; local_48 = local_48 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar8),iVar13 + iVar9,
                             *(undefined1 *)(iVar15 + iVar8));
                iVar9 = iVar9 + param_2;
              }
              iVar13 = iVar13 + local_38;
              iVar15 = iVar15 + (int)local_30;
              iVar12 = iVar12 + local_28;
            }
          }
        }
      }
      else {
        for (local_48 = 0; (int)local_48 < iVar11; local_48 = local_48 + 1) {
          local_54 = 0;
          for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
            uVar10 = (uint)*(byte *)(iVar12 + iVar8);
            uVar16 = local_4c;
            if (iVar15 != 0) {
              uVar16 = (uint)((int)(short)(ushort)*(byte *)(iVar15 + local_54) *
                             (int)(short)local_4c) >> 8;
            }
            FUN_00024a98(local_54 + iVar13,uVar10 << 0x10 | uVar10 << 8 | uVar10 | uVar16 << 0x18,
                         *(undefined1 *)((int)param_1 + 0x22));
            local_54 = local_54 + param_2;
          }
          if (iVar15 != 0) {
            iVar15 = iVar15 + (int)local_30;
          }
          iVar13 = iVar13 + local_38;
          iVar12 = iVar12 + local_28;
        }
      }
      return;
    }
    if (bVar1 == 7) {
      iVar12 = param_1[1];
      iVar13 = param_1[2];
      local_48 = (uint)*(byte *)((int)param_1 + 0x21);
      iVar11 = *param_1;
      local_2c = (int *)param_1[3];
      iVar15 = param_1[6];
      local_30 = (int *)param_1[7];
      iVar14 = param_1[4];
      local_34 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar14 == 0) {
          iVar14 = 0;
          if (local_48 < 0xfd) {
            for (; iVar14 < iVar13; iVar14 = iVar14 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
                cVar5 = FUN_00036f1a(iVar15,iVar8);
                FUN_000401f4(-cVar5,iVar11 + iVar9,local_48);
                iVar9 = iVar9 + param_2;
              }
              iVar11 = iVar11 + (int)local_2c;
              iVar15 = iVar15 + (int)local_30;
            }
          }
          else {
            for (; iVar14 < iVar13; iVar14 = iVar14 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
                cVar5 = FUN_00036f1a(iVar15,iVar8);
                cVar5 = -cVar5;
                *(char *)(iVar11 + iVar9 + 2) = cVar5;
                *(char *)(iVar11 + iVar9 + 1) = cVar5;
                *(char *)(iVar11 + iVar9) = cVar5;
                iVar9 = iVar9 + param_2;
              }
              iVar11 = iVar11 + (int)local_2c;
              iVar15 = iVar15 + (int)local_30;
            }
          }
        }
        else {
          local_54 = 0;
          if (local_48 < 0xfd) {
            for (; (int)local_54 < iVar13; local_54 = local_54 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
                cVar5 = FUN_00036f1a(iVar15,iVar8);
                FUN_000401f4(-cVar5,iVar11 + iVar9,
                             (uint)((int)(short)(ushort)*(byte *)(iVar14 + iVar8) *
                                   (int)(short)local_48) >> 8);
                iVar9 = iVar9 + param_2;
              }
              iVar11 = iVar11 + (int)local_2c;
              iVar15 = iVar15 + (int)local_30;
              iVar14 = iVar14 + local_34;
            }
          }
          else {
            for (; (int)local_54 < iVar13; local_54 = local_54 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
                cVar5 = FUN_00036f1a(iVar15,iVar8);
                FUN_000401f4(-cVar5,iVar11 + iVar9,*(undefined1 *)(iVar14 + iVar8));
                iVar9 = iVar9 + param_2;
              }
              iVar11 = iVar11 + (int)local_2c;
              iVar15 = iVar15 + (int)local_30;
              iVar14 = iVar14 + local_34;
            }
          }
        }
      }
      else {
        for (local_54 = 0; (int)local_54 < iVar13; local_54 = local_54 + 1) {
          local_60 = 0;
          for (iVar8 = 0; iVar8 < iVar12; iVar8 = iVar8 + 1) {
            iVar9 = FUN_00036f1a(iVar15,iVar8);
            uVar16 = iVar9 * 0xff;
            uVar10 = local_48;
            if (iVar14 != 0) {
              uVar10 = (uint)((int)(short)(ushort)*(byte *)(iVar14 + iVar8) * (int)(short)local_48)
                       >> 8;
            }
            FUN_00024a98(local_60 + iVar11,
                         (uVar16 & 0xff) << 0x10 | (uVar16 & 0xff) << 8 | uVar16 & 0xff |
                         uVar10 << 0x18,*(undefined1 *)((int)param_1 + 0x22));
            local_60 = local_60 + param_2;
          }
          if (iVar14 != 0) {
            iVar14 = iVar14 + local_34;
          }
          iVar11 = iVar11 + (int)local_2c;
          iVar15 = iVar15 + (int)local_30;
        }
      }
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
        iVar14 = param_1[1];
        iVar11 = param_1[2];
        local_4c = (uint)*(byte *)((int)param_1 + 0x21);
        iVar13 = *param_1;
        local_40 = param_1[3];
        iVar12 = param_1[6];
        local_28 = param_1[7];
        iVar15 = param_1[4];
        local_3c = param_1[5];
        if (*(char *)((int)param_1 + 0x22) == '\0') {
          if (iVar15 == 0) {
            if (local_4c < 0xfd) {
              for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
                iVar9 = 0;
                for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                  local_54 = CONCAT31(CONCAT21(CONCAT11(local_54._3_1_,
                                                        (char)((uint)((short)(*(ushort *)
                                                                               (iVar12 + iVar8 * 2)
                                                                             >> 0xb) * 0x83a) >> 8))
                                               ,(char)((uint)((short)(ushort)(((uint)*(ushort *)
                                                                                      (iVar12 + 
                                                  iVar8 * 2) << 0x15) >> 0x1a) * 0x40d) >> 8)),
                                      (char)((uint)((short)(*(byte *)(iVar12 + iVar8 * 2) & 0x1f) *
                                                   0x83a) >> 8));
                  FUN_000400ba(&local_54,iVar13 + iVar9,local_4c);
                  iVar9 = iVar9 + param_2;
                }
                iVar13 = iVar13 + local_40;
                iVar12 = iVar12 + local_28;
              }
            }
            else {
              for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
                iVar9 = 0;
                for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                  *(char *)(iVar13 + iVar9 + 2) =
                       (char)((uint)((short)(*(ushort *)(iVar12 + iVar8 * 2) >> 0xb) * 0x83a) >> 8);
                  *(char *)(iVar13 + iVar9 + 1) =
                       (char)((uint)((short)(ushort)(((uint)*(ushort *)(iVar12 + iVar8 * 2) << 0x15)
                                                    >> 0x1a) * 0x40d) >> 8);
                  *(char *)(iVar13 + iVar9) =
                       (char)((uint)((short)(*(byte *)(iVar12 + iVar8 * 2) & 0x1f) * 0x83a) >> 8);
                  iVar9 = iVar9 + param_2;
                }
                iVar13 = iVar13 + local_40;
                iVar12 = iVar12 + local_28;
              }
            }
          }
          else {
            local_48 = 0;
            if (local_4c < 0xfd) {
              for (; (int)local_48 < iVar11; local_48 = local_48 + 1) {
                iVar9 = 0;
                for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                  local_30 = (int *)CONCAT31(CONCAT21(CONCAT11(local_30._3_1_,
                                                               (char)((uint)((short)(*(ushort *)
                                                                                      (iVar12 + 
                                                  iVar8 * 2) >> 0xb) * 0x83a) >> 8)),
                                                  (char)((uint)((short)(ushort)(((uint)*(ushort *)
                                                                                        (iVar12 + 
                                                  iVar8 * 2) << 0x15) >> 0x1a) * 0x40d) >> 8)),
                                             (char)((uint)((short)(*(byte *)(iVar12 + iVar8 * 2) &
                                                                  0x1f) * 0x83a) >> 8));
                  FUN_000400ba(&local_30,iVar13 + iVar9,
                               (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar8) *
                                     (int)(short)local_4c) >> 8);
                  iVar9 = iVar9 + param_2;
                }
                iVar13 = iVar13 + local_40;
                iVar15 = iVar15 + local_3c;
                iVar12 = iVar12 + local_28;
              }
            }
            else {
              for (; (int)local_48 < iVar11; local_48 = local_48 + 1) {
                iVar9 = 0;
                for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                  local_38 = CONCAT31(CONCAT21(CONCAT11(local_38._3_1_,
                                                        (char)((uint)((short)(*(ushort *)
                                                                               (iVar12 + iVar8 * 2)
                                                                             >> 0xb) * 0x83a) >> 8))
                                               ,(char)((uint)((short)(ushort)(((uint)*(ushort *)
                                                                                      (iVar12 + 
                                                  iVar8 * 2) << 0x15) >> 0x1a) * 0x40d) >> 8)),
                                      (char)((uint)((short)(*(byte *)(iVar12 + iVar8 * 2) & 0x1f) *
                                                   0x83a) >> 8));
                  FUN_000400ba(&local_38,iVar13 + iVar9,*(undefined1 *)(iVar15 + iVar8));
                  iVar9 = iVar9 + param_2;
                }
                iVar13 = iVar13 + local_40;
                iVar15 = iVar15 + local_3c;
                iVar12 = iVar12 + local_28;
              }
            }
          }
        }
        else {
          for (local_48 = 0; (int)local_48 < iVar11; local_48 = local_48 + 1) {
            local_34 = 0;
            for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
              uVar3 = *(ushort *)(iVar12 + iVar8 * 2);
              uVar16 = local_4c;
              if (iVar15 != 0) {
                uVar16 = (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar8) * (int)(short)local_4c
                               ) >> 8;
              }
              FUN_00024a98(local_34 + iVar13,
                           ((uint)((short)(uVar3 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                           ((uint)((short)(ushort)(((uint)uVar3 << 0x15) >> 0x1a) * 0x40d) >> 8 &
                           0xff) << 8 | (uint)((short)(uVar3 & 0x1f) * 0x83a) >> 8 & 0xff |
                           uVar16 << 0x18,*(undefined1 *)((int)param_1 + 0x22));
              local_34 = local_34 + param_2;
            }
            if (iVar15 != 0) {
              iVar15 = iVar15 + local_3c;
            }
            iVar13 = iVar13 + local_40;
            iVar12 = iVar12 + local_28;
          }
        }
        return;
      }
      if (bVar1 != 0x15) {
        return;
      }
      iVar14 = param_1[1];
      iVar11 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar16 = (uint)bVar1;
      iVar13 = *param_1;
      local_3c = param_1[3];
      iVar12 = param_1[6];
      local_40 = param_1[7];
      iVar15 = param_1[4];
      local_34 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar15 == 0) {
          iVar15 = 0;
          if (uVar16 < 0xfd) {
            for (; iVar15 < iVar11; iVar15 = iVar15 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar8 * 2),iVar13 + iVar9,
                             (uint)((int)(short)(ushort)*(byte *)(iVar12 + iVar8 * 2 + 1) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar9 = iVar9 + local_28;
              }
              iVar13 = iVar13 + local_3c;
              iVar12 = iVar12 + local_40;
            }
          }
          else {
            for (; iVar15 < iVar11; iVar15 = iVar15 + 1) {
              iVar9 = 0;
              for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar8 * 2),iVar13 + iVar9,
                             *(undefined1 *)(iVar12 + iVar8 * 2 + 1));
                iVar9 = iVar9 + local_28;
              }
              iVar13 = iVar13 + local_3c;
              iVar12 = iVar12 + local_40;
            }
          }
        }
        else {
          iVar8 = 0;
          if (uVar16 < 0xfd) {
            while (iVar8 < iVar11) {
              iVar17 = 0;
              local_38 = iVar8;
              for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar9 * 2),iVar13 + iVar17,
                             (int)(short)(ushort)*(byte *)(iVar12 + iVar9 * 2 + 1) *
                             (int)(short)(ushort)*(byte *)(iVar15 + iVar9) * uVar16 >> 0x10);
                iVar17 = iVar17 + local_28;
              }
              iVar13 = iVar13 + local_3c;
              iVar15 = iVar15 + local_34;
              iVar12 = iVar12 + local_40;
              iVar8 = local_38 + 1;
            }
          }
          else {
            for (; iVar8 < iVar11; iVar8 = iVar8 + 1) {
              iVar17 = 0;
              for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
                FUN_000401f4(*(undefined1 *)(iVar12 + iVar9 * 2),iVar13 + iVar17,
                             (uint)((int)(short)(ushort)*(byte *)(iVar12 + iVar9 * 2 + 1) *
                                   (int)(short)(ushort)*(byte *)(iVar15 + iVar9)) >> 8);
                iVar17 = iVar17 + local_28;
              }
              iVar13 = iVar13 + local_3c;
              iVar15 = iVar15 + local_34;
              iVar12 = iVar12 + local_40;
            }
          }
        }
      }
      else {
        for (local_30 = (int *)0x0; (int)local_30 < iVar11; local_30 = (int *)((int)local_30 + 1)) {
          local_38 = 0;
          for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
            uVar2 = *(undefined1 *)(iVar12 + iVar8 * 2);
            iVar9 = iVar12 + iVar8 * 2;
            if (iVar15 == 0) {
              uVar10 = (uint)((int)(short)(ushort)*(byte *)(iVar9 + 1) * (int)(short)(ushort)bVar1)
                       >> 8;
            }
            else {
              uVar10 = (int)(short)(ushort)*(byte *)(iVar9 + 1) *
                       (int)(short)(ushort)*(byte *)(iVar15 + local_38) * uVar16 >> 0x10;
            }
            FUN_00024a98(local_38 + iVar13,
                         (uint)CONCAT12(uVar2,CONCAT11(uVar2,uVar2)) | uVar10 << 0x18,
                         *(undefined1 *)((int)param_1 + 0x22));
            local_38 = local_38 + local_28;
          }
          if (iVar15 != 0) {
            iVar15 = iVar15 + local_34;
          }
          iVar13 = iVar13 + local_3c;
          iVar12 = iVar12 + local_40;
        }
      }
      return;
    }
    local_28 = 4;
  }
  param_2 = param_2 & 0xff;
  iVar14 = param_1[2];
  local_54 = (uint)*(byte *)((int)param_1 + 0x21);
  iVar12 = *param_1;
  local_40 = param_1[3];
  iVar11 = param_1[6];
  local_44 = param_1[7];
  iVar15 = param_1[4];
  local_4c = param_1[5];
  iVar13 = param_1[1] * param_2;
  local_30 = param_1;
  local_2c = (int *)param_2;
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar15 == 0) {
      if (0xfc < local_54) {
        if (local_28 == param_2) {
          for (iVar15 = 0; iVar15 < iVar14; iVar15 = iVar15 + 1) {
            FUN_0004a404(iVar12,iVar11,iVar13);
            iVar12 = iVar12 + local_40;
            iVar11 = iVar11 + local_44;
          }
        }
        else {
          for (iVar15 = 0; iVar15 < iVar14; iVar15 = iVar15 + 1) {
            iVar9 = 0;
            for (iVar8 = 0; iVar8 < iVar13; iVar8 = iVar8 + param_2) {
              *(undefined1 *)(iVar12 + iVar8) = *(undefined1 *)(iVar11 + iVar9);
              *(undefined1 *)(iVar12 + iVar8 + 1) = *(undefined1 *)(iVar11 + iVar9 + 1);
              *(undefined1 *)(iVar12 + iVar8 + 2) = *(undefined1 *)(iVar11 + iVar9 + 2);
              iVar9 = iVar9 + local_28;
            }
            iVar12 = iVar12 + local_40;
            iVar11 = iVar11 + local_44;
          }
        }
        if (0xfc < local_54) {
          return;
        }
      }
      for (iVar15 = 0; iVar15 < iVar14; iVar15 = iVar15 + 1) {
        iVar8 = 0;
        for (iVar9 = 0; iVar9 < iVar13; iVar9 = iVar9 + param_2) {
          FUN_000400ba(iVar11 + iVar8,iVar12 + iVar9,local_54);
          iVar8 = iVar8 + local_28;
        }
        iVar12 = iVar12 + local_40;
        iVar11 = iVar11 + local_44;
      }
    }
    else {
      if (0xfc < local_54) {
        for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
          iVar9 = 0;
          local_50 = 0;
          for (iVar17 = 0; iVar17 < iVar13; iVar17 = iVar17 + param_2) {
            FUN_000400ba(iVar11 + iVar9,iVar12 + iVar17,*(undefined1 *)(iVar15 + local_50));
            local_50 = local_50 + 1;
            iVar9 = iVar9 + local_28;
          }
          iVar12 = iVar12 + local_40;
          iVar15 = iVar15 + local_4c;
          iVar11 = iVar11 + local_44;
        }
        if (iVar15 == 0) {
          return;
        }
        if (0xfc < local_54) {
          return;
        }
      }
      for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
        iVar9 = 0;
        local_50 = 0;
        for (iVar17 = 0; iVar17 < iVar13; iVar17 = iVar17 + param_2) {
          FUN_000400ba(iVar11 + iVar9,iVar12 + iVar17,
                       (uint)((int)(short)(ushort)*(byte *)(iVar15 + local_50) *
                             (int)(short)local_54) >> 8);
          local_50 = local_50 + 1;
          iVar9 = iVar9 + local_28;
        }
        iVar12 = iVar12 + local_40;
        iVar15 = iVar15 + local_4c;
        iVar11 = iVar11 + local_44;
      }
    }
  }
  else {
    for (iVar8 = 0; iVar8 < iVar14; iVar8 = iVar8 + 1) {
      iVar9 = 0;
      for (iVar17 = 0; iVar17 < iVar13; iVar17 = iVar17 + param_2) {
        uVar16 = local_54;
        if (iVar15 != 0) {
          uVar16 = (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar17) * (int)(short)local_54) >>
                   8;
        }
        local_50 = (uint)*(byte *)(iVar11 + iVar9 + 2) << 0x10 |
                   (uint)*(byte *)(iVar11 + iVar9 + 1) << 8 | (uint)*(byte *)(iVar11 + iVar9) |
                   uVar16 << 0x18;
        FUN_00024a98(iVar12 + iVar17,local_50,*(undefined1 *)((int)param_1 + 0x22));
        iVar9 = iVar9 + local_28;
      }
      if (iVar15 != 0) {
        iVar15 = iVar15 + local_4c;
      }
      iVar12 = iVar12 + local_40;
      iVar11 = iVar11 + local_44;
    }
  }
  return;
}

