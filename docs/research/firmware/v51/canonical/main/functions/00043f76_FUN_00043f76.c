/* Address: 00043f76; name: FUN_00043f76; body bytes: 3142 */

void FUN_00043f76(int *param_1)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  int local_6c;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 *local_34;
  int local_30;
  int *local_2c;
  int local_28;
  
  bVar1 = *(byte *)(param_1 + 8);
  if (bVar1 == 0x10) {
    iVar15 = param_1[1];
    iVar6 = param_1[2];
    bVar1 = *(byte *)((int)param_1 + 0x21);
    uVar19 = (uint)bVar1;
    iVar14 = *param_1;
    local_2c = (int *)param_1[3];
    iVar13 = param_1[6];
    local_30 = param_1[7];
    iVar16 = param_1[4];
    local_44 = param_1[5];
    FUN_000404e2(&local_40);
    if (*(char *)((int)param_1 + 0x22) == '\0') {
      if (iVar16 == 0) {
        iVar16 = 0;
        if (uVar19 < 0xfd) {
          for (; iVar16 < iVar6; iVar16 = iVar16 + 1) {
            for (iVar17 = 0; iVar17 < iVar15; iVar17 = iVar17 + 1) {
              uVar19 = *(uint *)(iVar13 + iVar17 * 4);
              puVar12 = (undefined4 *)(iVar14 + iVar17 * 4);
              uVar8 = FUN_00040106(uVar19 & 0xffffff |
                                   ((uint)((int)(short)(ushort)(byte)(uVar19 >> 0x18) *
                                          (int)(short)(ushort)bVar1) >> 8) << 0x18,*puVar12,
                                   &local_40);
              *puVar12 = uVar8;
            }
            iVar14 = iVar14 + (int)local_2c;
            iVar13 = iVar13 + local_30;
          }
        }
        else {
          for (; iVar16 < iVar6; iVar16 = iVar16 + 1) {
            for (iVar17 = 0; iVar17 < iVar15; iVar17 = iVar17 + 1) {
              puVar12 = (undefined4 *)(iVar14 + iVar17 * 4);
              uVar8 = FUN_00040106(*(undefined4 *)(iVar13 + iVar17 * 4),*puVar12,&local_40);
              *puVar12 = uVar8;
            }
            iVar14 = iVar14 + (int)local_2c;
            iVar13 = iVar13 + local_30;
          }
        }
      }
      else {
        iVar17 = 0;
        if (uVar19 < 0xfd) {
          for (; iVar17 < iVar6; iVar17 = iVar17 + 1) {
            for (iVar7 = 0; iVar7 < iVar15; iVar7 = iVar7 + 1) {
              uVar10 = *(uint *)(iVar13 + iVar7 * 4);
              puVar12 = (undefined4 *)(iVar14 + iVar7 * 4);
              uVar8 = FUN_00040106(uVar10 & 0xffffff |
                                   ((int)(short)(ushort)(byte)(uVar10 >> 0x18) *
                                    (int)(short)(ushort)*(byte *)(iVar16 + iVar7) * uVar19 >> 0x10)
                                   << 0x18,*puVar12,&local_40);
              *puVar12 = uVar8;
            }
            iVar14 = iVar14 + (int)local_2c;
            iVar16 = iVar16 + local_44;
            iVar13 = iVar13 + local_30;
          }
        }
        else {
          for (; iVar17 < iVar6; iVar17 = iVar17 + 1) {
            for (iVar7 = 0; iVar7 < iVar15; iVar7 = iVar7 + 1) {
              uVar19 = *(uint *)(iVar13 + iVar7 * 4);
              puVar12 = (undefined4 *)(iVar14 + iVar7 * 4);
              uVar8 = FUN_00040106(uVar19 & 0xffffff |
                                   ((uint)((int)(short)(ushort)(byte)(uVar19 >> 0x18) *
                                          (int)(short)(ushort)*(byte *)(iVar16 + iVar7)) >> 8) <<
                                   0x18,*puVar12,&local_40);
              *puVar12 = uVar8;
            }
            iVar14 = iVar14 + (int)local_2c;
            iVar16 = iVar16 + local_44;
            iVar13 = iVar13 + local_30;
          }
        }
      }
    }
    else {
      for (iVar17 = 0; iVar17 < iVar6; iVar17 = iVar17 + 1) {
        for (iVar7 = 0; iVar7 < iVar15; iVar7 = iVar7 + 1) {
          uVar10 = *(uint *)(iVar13 + iVar7 * 4);
          bVar3 = (byte)(uVar10 >> 0x18);
          if (iVar16 == 0) {
            uVar11 = (uint)((int)(short)(ushort)bVar3 * (int)(short)(ushort)bVar1) >> 8;
          }
          else {
            uVar11 = (int)(short)(ushort)bVar3 * (int)(short)(ushort)*(byte *)(iVar16 + iVar7) *
                     uVar19 >> 0x10;
          }
          FUN_00024934(iVar14 + iVar7 * 4,uVar10 & 0xffffff | uVar11 << 0x18,
                       *(undefined1 *)((int)param_1 + 0x22),&local_40);
        }
        if (iVar16 != 0) {
          iVar16 = iVar16 + local_44;
        }
        iVar14 = iVar14 + (int)local_2c;
        iVar13 = iVar13 + local_30;
      }
    }
    return;
  }
  if (bVar1 < 0x11) {
    if (bVar1 == 6) {
      iVar16 = param_1[1];
      iVar6 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar19 = (uint)bVar1;
      iVar15 = *param_1;
      local_3c = param_1[3];
      iVar14 = param_1[6];
      local_40 = param_1[7];
      iVar17 = param_1[4];
      iVar13 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar17 == 0) {
          if (uVar19 < 0xfd) {
            for (iVar13 = 0; iVar13 < iVar6; iVar13 = iVar13 + 1) {
              iVar7 = 0;
              for (iVar17 = 0; iVar17 < iVar16; iVar17 = iVar17 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar14 + iVar17),iVar15 + iVar7 * 4,uVar19);
                iVar7 = iVar7 + 1;
              }
              iVar15 = iVar15 + local_3c;
              iVar14 = iVar14 + local_40;
            }
          }
          else {
            for (iVar13 = 0; iVar13 < iVar6; iVar13 = iVar13 + 1) {
              iVar7 = 0;
              for (iVar17 = 0; iVar17 < iVar16; iVar17 = iVar17 + 1) {
                iVar9 = iVar15 + iVar7 * 4;
                *(undefined1 *)(iVar9 + 3) = *(undefined1 *)(iVar14 + iVar17);
                *(undefined1 *)(iVar9 + 2) = *(undefined1 *)(iVar14 + iVar17);
                *(undefined1 *)(iVar9 + 1) = *(undefined1 *)(iVar14 + iVar17);
                *(undefined1 *)(iVar15 + iVar7 * 4) = *(undefined1 *)(iVar14 + iVar17);
                iVar7 = iVar7 + 1;
              }
              iVar15 = iVar15 + local_3c;
              iVar14 = iVar14 + local_40;
            }
          }
        }
        else {
          iVar7 = 0;
          if (uVar19 < 0xfd) {
            for (; iVar7 < iVar6; iVar7 = iVar7 + 1) {
              iVar18 = 0;
              for (iVar9 = 0; iVar9 < iVar16; iVar9 = iVar9 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar14 + iVar9),iVar15 + iVar18 * 4,
                             (uint)((int)(short)(ushort)*(byte *)(iVar17 + iVar9) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar18 = iVar18 + 1;
              }
              iVar15 = iVar15 + local_3c;
              iVar17 = iVar17 + iVar13;
              iVar14 = iVar14 + local_40;
            }
          }
          else {
            for (; iVar7 < iVar6; iVar7 = iVar7 + 1) {
              iVar18 = 0;
              for (iVar9 = 0; iVar9 < iVar16; iVar9 = iVar9 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar14 + iVar9),iVar15 + iVar18 * 4,
                             *(undefined1 *)(iVar17 + iVar9));
                iVar18 = iVar18 + 1;
              }
              iVar15 = iVar15 + local_3c;
              iVar17 = iVar17 + iVar13;
              iVar14 = iVar14 + local_40;
            }
          }
        }
      }
      else {
        FUN_000404e2(&local_38);
        for (iVar7 = 0; iVar7 < iVar6; iVar7 = iVar7 + 1) {
          iVar18 = 0;
          for (iVar9 = 0; iVar9 < iVar16; iVar9 = iVar9 + 1) {
            uVar11 = (uint)*(byte *)(iVar14 + iVar9);
            uVar10 = uVar19;
            if (iVar17 != 0) {
              uVar10 = (uint)((int)(short)(ushort)*(byte *)(iVar17 + iVar18) *
                             (int)(short)(ushort)bVar1) >> 8;
            }
            FUN_00024934(iVar15 + iVar18 * 4,uVar11 << 0x10 | uVar11 << 8 | uVar11 | uVar10 << 0x18,
                         *(undefined1 *)((int)param_1 + 0x22),&local_38);
            iVar18 = iVar18 + 1;
          }
          if (iVar17 != 0) {
            iVar17 = iVar17 + iVar13;
          }
          iVar15 = iVar15 + local_3c;
          iVar14 = iVar14 + local_40;
        }
      }
      return;
    }
    if (bVar1 == 7) {
      iVar14 = param_1[1];
      iVar15 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar19 = (uint)bVar1;
      iVar13 = *param_1;
      local_38 = param_1[3];
      iVar17 = param_1[6];
      local_3c = param_1[7];
      iVar16 = param_1[4];
      iVar6 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar16 == 0) {
          iVar6 = 0;
          if (uVar19 < 0xfd) {
            for (; iVar6 < iVar15; iVar6 = iVar6 + 1) {
              iVar7 = 0;
              for (iVar16 = 0; iVar16 < iVar14; iVar16 = iVar16 + 1) {
                cVar4 = FUN_00036ea2(iVar17,iVar16);
                FUN_0004022a(-cVar4,iVar13 + iVar7 * 4,uVar19);
                iVar7 = iVar7 + 1;
              }
              iVar13 = iVar13 + local_38;
              iVar17 = iVar17 + local_3c;
            }
          }
          else {
            for (; iVar6 < iVar15; iVar6 = iVar6 + 1) {
              iVar7 = 0;
              for (iVar16 = 0; iVar16 < iVar14; iVar16 = iVar16 + 1) {
                cVar4 = FUN_00036ea2(iVar17,iVar16);
                iVar9 = iVar13 + iVar7 * 4;
                cVar4 = -cVar4;
                *(char *)(iVar9 + 3) = cVar4;
                *(char *)(iVar9 + 2) = cVar4;
                *(char *)(iVar9 + 1) = cVar4;
                *(char *)(iVar13 + iVar7 * 4) = cVar4;
                iVar7 = iVar7 + 1;
              }
              iVar13 = iVar13 + local_38;
              iVar17 = iVar17 + local_3c;
            }
          }
        }
        else {
          iVar7 = 0;
          if (uVar19 < 0xfd) {
            for (; iVar7 < iVar15; iVar7 = iVar7 + 1) {
              iVar18 = 0;
              for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
                cVar4 = FUN_00036ea2(iVar17,iVar9);
                FUN_0004022a(-cVar4,iVar13 + iVar18 * 4,
                             (uint)((int)(short)(ushort)*(byte *)(iVar16 + iVar9) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar18 = iVar18 + 1;
              }
              iVar17 = iVar17 + local_3c;
              iVar13 = iVar13 + local_38;
              iVar16 = iVar16 + iVar6;
            }
          }
          else {
            for (; iVar7 < iVar15; iVar7 = iVar7 + 1) {
              iVar18 = 0;
              for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
                cVar4 = FUN_00036ea2(iVar17,iVar9);
                FUN_0004022a(-cVar4,iVar13 + iVar18 * 4,*(undefined1 *)(iVar16 + iVar9));
                iVar18 = iVar18 + 1;
              }
              iVar17 = iVar17 + local_3c;
              iVar13 = iVar13 + local_38;
              iVar16 = iVar16 + iVar6;
            }
          }
        }
      }
      else {
        FUN_000404e2(&local_34);
        for (iVar7 = 0; iVar7 < iVar15; iVar7 = iVar7 + 1) {
          iVar18 = 0;
          for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
            iVar5 = FUN_00036ea2(iVar17,iVar9);
            uVar10 = iVar5 * 0xff;
            uVar11 = uVar19;
            if (iVar16 != 0) {
              uVar11 = (uint)((int)(short)(ushort)*(byte *)(iVar16 + iVar18) *
                             (int)(short)(ushort)bVar1) >> 8;
            }
            FUN_00024934(iVar13 + iVar18 * 4,
                         (uVar10 & 0xff) << 0x10 | (uVar10 & 0xff) << 8 | uVar10 & 0xff |
                         uVar11 << 0x18,*(undefined1 *)((int)param_1 + 0x22),&local_34);
            iVar18 = iVar18 + 1;
          }
          if (iVar16 != 0) {
            iVar16 = iVar16 + iVar6;
          }
          iVar13 = iVar13 + local_38;
          iVar17 = iVar17 + local_3c;
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
        iVar16 = param_1[1];
        iVar6 = param_1[2];
        bVar1 = *(byte *)((int)param_1 + 0x21);
        uVar19 = (uint)bVar1;
        iVar15 = *param_1;
        local_2c = (int *)param_1[3];
        iVar14 = param_1[6];
        local_30 = param_1[7];
        iVar17 = param_1[4];
        iVar13 = param_1[5];
        FUN_000404e2(&local_44);
        if (*(char *)((int)param_1 + 0x22) == '\0') {
          if (iVar17 == 0) {
            uVar19 = uVar19 << 0x18;
            for (iVar13 = 0; iVar13 < iVar6; iVar13 = iVar13 + 1) {
              for (iVar17 = 0; iVar17 < iVar16; iVar17 = iVar17 + 1) {
                uVar2 = *(ushort *)(iVar14 + iVar17 * 2);
                uVar19 = uVar19 & 0xff000000 |
                         ((uint)((short)(uVar2 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                         ((uint)((short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) * 0x40d) >> 8 & 0xff
                         ) << 8 | (uint)((short)(uVar2 & 0x1f) * 0x83a) >> 8 & 0xff;
                puVar12 = (undefined4 *)(iVar15 + iVar17 * 4);
                uVar8 = FUN_00040106(uVar19,*puVar12,&local_44);
                *puVar12 = uVar8;
              }
              iVar15 = iVar15 + (int)local_2c;
              iVar14 = iVar14 + local_30;
            }
          }
          else {
            iVar7 = 0;
            if (uVar19 < 0xfd) {
              for (; iVar7 < iVar6; iVar7 = iVar7 + 1) {
                for (iVar9 = 0; iVar9 < iVar16; iVar9 = iVar9 + 1) {
                  uVar2 = *(ushort *)(iVar14 + iVar9 * 2);
                  local_34 = (undefined4 *)(iVar15 + iVar9 * 4);
                  uVar8 = FUN_00040106(((uint)((int)(short)(ushort)*(byte *)(iVar17 + iVar9) *
                                              (int)(short)(ushort)bVar1) >> 8) << 0x18 |
                                       ((uint)((short)(uVar2 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                                       ((uint)((short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) *
                                              0x40d) >> 8 & 0xff) << 8 |
                                       (uint)((short)(uVar2 & 0x1f) * 0x83a) >> 8 & 0xff,*local_34,
                                       &local_44);
                  *local_34 = uVar8;
                }
                iVar15 = iVar15 + (int)local_2c;
                iVar14 = iVar14 + local_30;
                iVar17 = iVar17 + iVar13;
              }
            }
            else {
              for (; iVar7 < iVar6; iVar7 = iVar7 + 1) {
                for (iVar9 = 0; iVar9 < iVar16; iVar9 = iVar9 + 1) {
                  uVar2 = *(ushort *)(iVar14 + iVar9 * 2);
                  puVar12 = (undefined4 *)(iVar15 + iVar9 * 4);
                  uVar8 = FUN_00040106((uint)*(byte *)(iVar17 + iVar9) << 0x18 |
                                       ((uint)((short)(uVar2 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                                       ((uint)((short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) *
                                              0x40d) >> 8 & 0xff) << 8 |
                                       (uint)((short)(uVar2 & 0x1f) * 0x83a) >> 8 & 0xff,*puVar12,
                                       &local_44);
                  *puVar12 = uVar8;
                }
                iVar15 = iVar15 + (int)local_2c;
                iVar17 = iVar17 + iVar13;
                iVar14 = iVar14 + local_30;
              }
            }
          }
        }
        else {
          for (iVar7 = 0; iVar7 < iVar6; iVar7 = iVar7 + 1) {
            for (iVar9 = 0; iVar9 < iVar16; iVar9 = iVar9 + 1) {
              uVar2 = *(ushort *)(iVar14 + iVar9 * 2);
              uVar11 = ((uint)((short)(uVar2 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                       ((uint)((short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) * 0x40d) >> 8 & 0xff)
                       << 8;
              uVar10 = (uint)((short)(uVar2 & 0x1f) * 0x83a) >> 8 & 0xff;
              if (iVar17 == 0) {
                uVar10 = uVar11 | uVar10 | uVar19 << 0x18;
              }
              else {
                uVar10 = uVar11 | uVar10 |
                         ((uint)((int)(short)(ushort)*(byte *)(iVar17 + iVar9) *
                                (int)(short)(ushort)bVar1) >> 8) << 0x18;
              }
              FUN_00024934(iVar15 + iVar9 * 4,uVar10,*(undefined1 *)((int)param_1 + 0x22),&local_44)
              ;
            }
            if (iVar17 != 0) {
              iVar17 = iVar17 + iVar13;
            }
            iVar15 = iVar15 + (int)local_2c;
            iVar14 = iVar14 + local_30;
          }
        }
        return;
      }
      if (bVar1 != 0x15) {
        return;
      }
      iVar17 = param_1[1];
      iVar6 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar19 = (uint)bVar1;
      iVar16 = *param_1;
      local_40 = param_1[3];
      iVar15 = param_1[6];
      iVar13 = param_1[7];
      iVar7 = param_1[4];
      iVar14 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar7 == 0) {
          iVar14 = 0;
          if (uVar19 < 0xfd) {
            for (; iVar14 < iVar6; iVar14 = iVar14 + 1) {
              iVar9 = 0;
              for (iVar7 = 0; iVar7 < iVar17; iVar7 = iVar7 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar15 + iVar7 * 2),iVar16 + iVar9 * 4,
                             (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar7 * 2 + 1) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar9 = iVar9 + 1;
              }
              iVar16 = iVar16 + local_40;
              iVar15 = iVar15 + iVar13;
            }
          }
          else {
            for (; iVar14 < iVar6; iVar14 = iVar14 + 1) {
              iVar9 = 0;
              for (iVar7 = 0; iVar7 < iVar17; iVar7 = iVar7 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar15 + iVar7 * 2),iVar16 + iVar9 * 4,
                             *(undefined1 *)(iVar15 + iVar7 * 2 + 1));
                iVar9 = iVar9 + 1;
              }
              iVar16 = iVar16 + local_40;
              iVar15 = iVar15 + iVar13;
            }
          }
        }
        else {
          iVar9 = 0;
          if (uVar19 < 0xfd) {
            for (; iVar9 < iVar6; iVar9 = iVar9 + 1) {
              iVar5 = 0;
              for (iVar18 = 0; iVar18 < iVar17; iVar18 = iVar18 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar15 + iVar18 * 2),iVar16 + iVar5 * 4,
                             (int)(short)(ushort)*(byte *)(iVar15 + iVar18 * 2 + 1) *
                             (int)(short)(ushort)*(byte *)(iVar7 + iVar18) * uVar19 >> 0x10);
                iVar5 = iVar5 + 1;
              }
              iVar16 = iVar16 + local_40;
              iVar7 = iVar7 + iVar14;
              iVar15 = iVar15 + iVar13;
            }
          }
          else {
            for (; iVar9 < iVar6; iVar9 = iVar9 + 1) {
              iVar5 = 0;
              for (iVar18 = 0; iVar18 < iVar17; iVar18 = iVar18 + 1) {
                FUN_0004022a(*(undefined1 *)(iVar15 + iVar18 * 2),iVar16 + iVar5 * 4,
                             (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar18 * 2 + 1) *
                                   (int)(short)(ushort)*(byte *)(iVar7 + iVar18)) >> 8);
                iVar5 = iVar5 + 1;
              }
              iVar16 = iVar16 + local_40;
              iVar7 = iVar7 + iVar14;
              iVar15 = iVar15 + iVar13;
            }
          }
        }
      }
      else {
        FUN_000404e2(&local_38);
        for (iVar9 = 0; iVar9 < iVar6; iVar9 = iVar9 + 1) {
          local_6c = 0;
          for (iVar18 = 0; iVar18 < iVar17; iVar18 = iVar18 + 1) {
            uVar10 = (uint)*(byte *)(iVar15 + iVar18 * 2);
            iVar5 = iVar15 + iVar18 * 2;
            if (iVar7 == 0) {
              uVar11 = (uint)((int)(short)(ushort)*(byte *)(iVar5 + 1) * (int)(short)(ushort)bVar1)
                       >> 8;
            }
            else {
              uVar11 = (int)(short)(ushort)*(byte *)(iVar5 + 1) *
                       (int)(short)(ushort)*(byte *)(iVar7 + local_6c) * uVar19 >> 0x10;
            }
            FUN_00024934(iVar16 + local_6c * 4,
                         uVar10 << 0x10 | uVar10 << 8 | uVar10 | uVar11 << 0x18,
                         *(undefined1 *)((int)param_1 + 0x22),&local_38);
            local_6c = local_6c + 1;
          }
          if (iVar7 != 0) {
            iVar7 = iVar7 + iVar14;
          }
          iVar16 = iVar16 + local_40;
          iVar15 = iVar15 + iVar13;
        }
      }
      return;
    }
    local_28 = 4;
  }
  iVar15 = param_1[1];
  iVar16 = param_1[2];
  bVar1 = *(byte *)((int)param_1 + 0x21);
  uVar19 = (uint)bVar1;
  iVar14 = *param_1;
  local_30 = param_1[3];
  iVar13 = param_1[6];
  local_34 = (undefined4 *)param_1[7];
  iVar17 = param_1[4];
  iVar6 = param_1[5];
  local_2c = param_1;
  FUN_000404e2(&local_44);
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar17 == 0) {
      if (0xfc < uVar19) {
        if (local_28 == 4) {
          for (iVar6 = 0; iVar6 < iVar16; iVar6 = iVar6 + 1) {
            FUN_0004a404(iVar14,iVar13,iVar15 << 2);
            iVar14 = iVar14 + local_30;
            iVar13 = iVar13 + (int)local_34;
          }
        }
        else {
          if (local_28 != 3) {
            return;
          }
          for (iVar6 = 0; iVar6 < iVar16; iVar6 = iVar6 + 1) {
            iVar7 = 0;
            for (iVar17 = 0; iVar17 < iVar15; iVar17 = iVar17 + 1) {
              iVar9 = iVar14 + iVar17 * 4;
              *(undefined1 *)(iVar9 + 2) = *(undefined1 *)(iVar13 + iVar7 + 2);
              *(undefined1 *)(iVar9 + 1) = *(undefined1 *)(iVar13 + iVar7 + 1);
              *(undefined1 *)(iVar14 + iVar17 * 4) = *(undefined1 *)(iVar13 + iVar7);
              *(undefined1 *)(iVar9 + 3) = 0xff;
              iVar7 = iVar7 + 3;
            }
            iVar14 = iVar14 + local_30;
            iVar13 = iVar13 + (int)local_34;
          }
        }
        if (0xfc < uVar19) {
          return;
        }
      }
      uVar19 = uVar19 << 0x18;
      for (iVar6 = 0; iVar6 < iVar16; iVar6 = iVar6 + 1) {
        iVar17 = 0;
        for (iVar7 = 0; iVar7 < iVar15; iVar7 = iVar7 + 1) {
          uVar19 = uVar19 & 0xff000000 | (uint)*(byte *)(iVar13 + iVar17 + 2) << 0x10 |
                   (uint)*(byte *)(iVar13 + iVar17 + 1) << 8 | (uint)*(byte *)(iVar13 + iVar17);
          puVar12 = (undefined4 *)(iVar14 + iVar7 * 4);
          uVar8 = FUN_00040106(uVar19,*puVar12,&local_44);
          *puVar12 = uVar8;
          iVar17 = iVar17 + local_28;
        }
        iVar14 = iVar14 + local_30;
        iVar13 = iVar13 + (int)local_34;
      }
    }
    else {
      if (0xfc < uVar19) {
        for (iVar7 = 0; iVar7 < iVar16; iVar7 = iVar7 + 1) {
          iVar9 = 0;
          for (iVar18 = 0; iVar18 < iVar15; iVar18 = iVar18 + 1) {
            puVar12 = (undefined4 *)(iVar14 + iVar18 * 4);
            uVar8 = FUN_00040106((uint)*(byte *)(iVar17 + iVar18) << 0x18 |
                                 (uint)*(byte *)(iVar9 + iVar13 + 2) << 0x10 |
                                 (uint)*(byte *)(iVar9 + iVar13 + 1) << 8 |
                                 (uint)*(byte *)(iVar13 + iVar9),*puVar12,&local_44);
            *puVar12 = uVar8;
            iVar9 = iVar9 + local_28;
          }
          iVar14 = iVar14 + local_30;
          iVar17 = iVar17 + iVar6;
          iVar13 = iVar13 + (int)local_34;
        }
        if (iVar17 == 0) {
          return;
        }
        if (0xfc < uVar19) {
          return;
        }
      }
      for (iVar7 = 0; iVar7 < iVar16; iVar7 = iVar7 + 1) {
        iVar9 = 0;
        for (iVar18 = 0; iVar18 < iVar15; iVar18 = iVar18 + 1) {
          puVar12 = (undefined4 *)(iVar14 + iVar18 * 4);
          uVar8 = FUN_00040106(((uint)((int)(short)(ushort)*(byte *)(iVar17 + iVar18) *
                                      (int)(short)(ushort)bVar1) >> 8) << 0x18 |
                               (uint)*(byte *)(iVar9 + iVar13 + 2) << 0x10 |
                               (uint)*(byte *)(iVar9 + iVar13 + 1) << 8 |
                               (uint)*(byte *)(iVar13 + iVar9),*puVar12,&local_44);
          *puVar12 = uVar8;
          iVar9 = iVar9 + local_28;
        }
        iVar14 = iVar14 + local_30;
        iVar17 = iVar17 + iVar6;
        iVar13 = iVar13 + (int)local_34;
      }
    }
  }
  else {
    for (iVar7 = 0; iVar7 < iVar16; iVar7 = iVar7 + 1) {
      iVar9 = 0;
      for (iVar18 = 0; iVar18 < iVar15; iVar18 = iVar18 + 1) {
        uVar10 = (uint)*(byte *)(iVar13 + iVar9 + 2) << 0x10 |
                 (uint)*(byte *)(iVar13 + iVar9 + 1) << 8;
        if (iVar17 == 0) {
          uVar10 = uVar10 | *(byte *)(iVar13 + iVar9) | uVar19 << 0x18;
        }
        else {
          uVar10 = uVar10 | *(byte *)(iVar13 + iVar9) |
                   ((uint)((int)(short)(ushort)*(byte *)(iVar17 + iVar18) *
                          (int)(short)(ushort)bVar1) >> 8) << 0x18;
        }
        FUN_00024934(iVar14 + iVar18 * 4,uVar10,*(undefined1 *)((int)param_1 + 0x22),&local_44);
        iVar9 = iVar9 + local_28;
      }
      if (iVar17 != 0) {
        iVar17 = iVar17 + iVar6;
      }
      iVar14 = iVar14 + local_30;
      iVar13 = iVar13 + (int)local_34;
    }
  }
  return;
}

