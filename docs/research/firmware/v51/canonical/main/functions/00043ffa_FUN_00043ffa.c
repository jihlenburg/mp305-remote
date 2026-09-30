/* Address: 00043ffa; name: FUN_00043ffa; body bytes: 2758 */

void FUN_00043ffa(int *param_1)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  char cVar4;
  undefined1 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  undefined4 *puVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int local_68;
  int local_5c;
  
  bVar1 = *(byte *)(param_1 + 8);
  if (bVar1 == 0x10) {
    iVar19 = param_1[1];
    iVar17 = param_1[2];
    bVar1 = *(byte *)((int)param_1 + 0x21);
    uVar14 = (uint)bVar1;
    iVar18 = *param_1;
    iVar7 = param_1[3];
    iVar10 = param_1[6];
    iVar8 = param_1[7];
    iVar20 = param_1[4];
    iVar9 = param_1[5];
    if (*(char *)((int)param_1 + 0x22) == '\0') {
      if (iVar20 == 0) {
        iVar9 = 0;
        if (uVar14 < 0xfd) {
          for (; iVar9 < iVar17; iVar9 = iVar9 + 1) {
            for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
              puVar15 = (undefined4 *)(iVar10 + iVar20 * 4);
              uVar12 = FUN_0003ff24(*puVar15);
              FUN_00040280(uVar12,iVar18 + iVar20,
                           (uint)((int)(short)(ushort)*(byte *)((int)puVar15 + 3) *
                                 (int)(short)(ushort)bVar1) >> 8);
            }
            iVar18 = iVar18 + iVar7;
            iVar10 = iVar10 + iVar8;
          }
        }
        else {
          for (; iVar9 < iVar17; iVar9 = iVar9 + 1) {
            for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
              puVar15 = (undefined4 *)(iVar10 + iVar20 * 4);
              uVar12 = FUN_0003ff24(*puVar15);
              FUN_00040280(uVar12,iVar18 + iVar20,*(undefined1 *)((int)puVar15 + 3));
            }
            iVar18 = iVar18 + iVar7;
            iVar10 = iVar10 + iVar8;
          }
        }
      }
      else {
        iVar21 = 0;
        if (uVar14 < 0xfd) {
          for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
            for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
              puVar15 = (undefined4 *)(iVar10 + iVar11 * 4);
              uVar12 = FUN_0003ff24(*puVar15);
              FUN_00040280(uVar12,iVar18 + iVar11,
                           (int)(short)(ushort)*(byte *)((int)puVar15 + 3) *
                           (int)(short)(ushort)*(byte *)(iVar20 + iVar11) * uVar14 >> 0x10);
            }
            iVar18 = iVar18 + iVar7;
            iVar20 = iVar20 + iVar9;
            iVar10 = iVar10 + iVar8;
          }
        }
        else {
          for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
            for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
              puVar15 = (undefined4 *)(iVar10 + iVar11 * 4);
              uVar12 = FUN_0003ff24(*puVar15);
              FUN_00040280(uVar12,iVar18 + iVar11,
                           (uint)((int)(short)(ushort)*(byte *)((int)puVar15 + 3) *
                                 (int)(short)(ushort)*(byte *)(iVar20 + iVar11)) >> 8);
            }
            iVar18 = iVar18 + iVar7;
            iVar20 = iVar20 + iVar9;
            iVar10 = iVar10 + iVar8;
          }
        }
      }
    }
    else {
      for (iVar21 = 0; iVar21 < iVar17; iVar21 = iVar21 + 1) {
        for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
          uVar6 = *(uint *)(iVar10 + iVar11 * 4);
          bVar3 = (byte)(uVar6 >> 0x18);
          if (iVar20 == 0) {
            uVar16 = (uint)((int)(short)(ushort)bVar3 * (int)(short)(ushort)bVar1) >> 8;
          }
          else {
            uVar16 = (int)(short)(ushort)bVar3 * (int)(short)(ushort)*(byte *)(iVar20 + iVar11) *
                     uVar14 >> 0x10;
          }
          FUN_00024a4c(iVar18 + iVar11,uVar6 & 0xffffff | uVar16 << 0x18,
                       *(undefined1 *)((int)param_1 + 0x22));
        }
        if (iVar20 != 0) {
          iVar20 = iVar20 + iVar9;
        }
        iVar18 = iVar18 + iVar7;
        iVar10 = iVar10 + iVar8;
      }
    }
    return;
  }
  if (bVar1 < 0x11) {
    if (bVar1 == 6) {
      iVar19 = param_1[1];
      iVar17 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar14 = (uint)bVar1;
      iVar18 = *param_1;
      iVar7 = param_1[3];
      iVar10 = param_1[6];
      iVar8 = param_1[7];
      iVar20 = param_1[4];
      iVar9 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar20 == 0) {
          if (uVar14 < 0xfd) {
            for (iVar9 = 0; iVar9 < iVar17; iVar9 = iVar9 + 1) {
              iVar21 = 0;
              for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar20),iVar18 + iVar21,uVar14);
                iVar21 = iVar21 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar10 = iVar10 + iVar8;
            }
          }
          else {
            for (iVar9 = 0; iVar9 < iVar17; iVar9 = iVar9 + 1) {
              FUN_0004a404(iVar18,iVar10,iVar19);
              iVar18 = iVar18 + iVar7;
              iVar10 = iVar10 + iVar8;
            }
          }
        }
        else {
          iVar21 = 0;
          if (uVar14 < 0xfd) {
            for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
              iVar13 = 0;
              for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar11),iVar18 + iVar13,
                             (uint)((int)(short)(ushort)*(byte *)(iVar20 + iVar11) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar13 = iVar13 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar20 = iVar20 + iVar9;
              iVar10 = iVar10 + iVar8;
            }
          }
          else {
            for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
              iVar13 = 0;
              for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar11),iVar18 + iVar13,
                             *(undefined1 *)(iVar20 + iVar11));
                iVar13 = iVar13 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar20 = iVar20 + iVar9;
              iVar10 = iVar10 + iVar8;
            }
          }
        }
      }
      else {
        for (iVar21 = 0; iVar21 < iVar17; iVar21 = iVar21 + 1) {
          iVar13 = 0;
          for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
            uVar16 = (uint)*(byte *)(iVar10 + iVar11);
            uVar6 = uVar14;
            if (iVar20 != 0) {
              uVar6 = (uint)((int)(short)(ushort)*(byte *)(iVar20 + iVar13) *
                            (int)(short)(ushort)bVar1) >> 8;
            }
            FUN_00024a4c(iVar18 + iVar13,uVar16 << 0x10 | uVar16 << 8 | uVar16 | uVar6 << 0x18,
                         *(undefined1 *)((int)param_1 + 0x22));
            iVar13 = iVar13 + 1;
          }
          if (iVar20 != 0) {
            iVar20 = iVar20 + iVar9;
          }
          iVar18 = iVar18 + iVar7;
          iVar10 = iVar10 + iVar8;
        }
      }
      return;
    }
    if (bVar1 == 7) {
      iVar10 = param_1[1];
      iVar18 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar14 = (uint)bVar1;
      iVar9 = *param_1;
      iVar17 = param_1[3];
      iVar20 = param_1[6];
      iVar7 = param_1[7];
      iVar19 = param_1[4];
      iVar8 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar19 == 0) {
          iVar8 = 0;
          if (uVar14 < 0xfd) {
            for (; iVar8 < iVar18; iVar8 = iVar8 + 1) {
              iVar21 = 0;
              for (iVar19 = 0; iVar19 < iVar10; iVar19 = iVar19 + 1) {
                cVar4 = FUN_00036ede(iVar20,iVar19);
                FUN_00040280(-cVar4,iVar9 + iVar21,uVar14);
                iVar21 = iVar21 + 1;
              }
              iVar9 = iVar9 + iVar17;
              iVar20 = iVar20 + iVar7;
            }
          }
          else {
            for (; iVar8 < iVar18; iVar8 = iVar8 + 1) {
              iVar21 = 0;
              for (iVar19 = 0; iVar19 < iVar10; iVar19 = iVar19 + 1) {
                cVar4 = FUN_00036ede(iVar20,iVar19);
                FUN_00040280(-cVar4,iVar9 + iVar21,uVar14);
                iVar21 = iVar21 + 1;
              }
              iVar9 = iVar9 + iVar17;
              iVar20 = iVar20 + iVar7;
            }
          }
        }
        else {
          iVar21 = 0;
          if (uVar14 < 0xfd) {
            for (; iVar21 < iVar18; iVar21 = iVar21 + 1) {
              iVar13 = 0;
              for (iVar11 = 0; iVar11 < iVar10; iVar11 = iVar11 + 1) {
                cVar4 = FUN_00036ede(iVar20,iVar11);
                FUN_00040280(-cVar4,iVar9 + iVar13,
                             (uint)((int)(short)(ushort)*(byte *)(iVar19 + iVar11) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar13 = iVar13 + 1;
              }
              iVar20 = iVar20 + iVar7;
              iVar9 = iVar9 + iVar17;
              iVar19 = iVar19 + iVar8;
            }
          }
          else {
            for (; iVar21 < iVar18; iVar21 = iVar21 + 1) {
              iVar13 = 0;
              for (iVar11 = 0; iVar11 < iVar10; iVar11 = iVar11 + 1) {
                cVar4 = FUN_00036ede(iVar20,iVar11);
                FUN_00040280(-cVar4,iVar9 + iVar13,*(undefined1 *)(iVar19 + iVar11));
                iVar13 = iVar13 + 1;
              }
              iVar9 = iVar9 + iVar17;
              iVar19 = iVar19 + iVar8;
              iVar20 = iVar20 + iVar7;
            }
          }
        }
      }
      else {
        for (iVar21 = 0; iVar21 < iVar18; iVar21 = iVar21 + 1) {
          iVar13 = 0;
          for (iVar11 = 0; iVar11 < iVar10; iVar11 = iVar11 + 1) {
            iVar22 = FUN_00036ede(iVar20,iVar11);
            uVar6 = iVar22 * 0xff;
            uVar16 = uVar14;
            if (iVar19 != 0) {
              uVar16 = (uint)((int)(short)(ushort)*(byte *)(iVar19 + iVar13) *
                             (int)(short)(ushort)bVar1) >> 8;
            }
            FUN_00024a4c(iVar9 + iVar13,
                         (uVar6 & 0xff) << 0x10 | (uVar6 & 0xff) << 8 | uVar6 & 0xff |
                         uVar16 << 0x18,*(undefined1 *)((int)param_1 + 0x22));
            iVar13 = iVar13 + 1;
          }
          if (iVar19 != 0) {
            iVar19 = iVar19 + iVar8;
          }
          iVar9 = iVar9 + iVar17;
          iVar20 = iVar20 + iVar7;
        }
      }
      return;
    }
    if (bVar1 != 0xf) {
      return;
    }
    iVar17 = 3;
  }
  else {
    if (bVar1 != 0x11) {
      if (bVar1 == 0x12) {
        iVar19 = param_1[1];
        iVar17 = param_1[2];
        bVar1 = *(byte *)((int)param_1 + 0x21);
        iVar18 = *param_1;
        iVar7 = param_1[3];
        iVar10 = param_1[6];
        iVar8 = param_1[7];
        iVar20 = param_1[4];
        iVar9 = param_1[5];
        if (*(char *)((int)param_1 + 0x22) == '\0') {
          if (iVar20 == 0) {
            iVar9 = 0;
            if (bVar1 < 0xfd) {
              for (; iVar9 < iVar17; iVar9 = iVar9 + 1) {
                iVar21 = 0;
                for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
                  uVar12 = FUN_0003fe7c(*(undefined2 *)(iVar10 + iVar20 * 2));
                  FUN_00040280(uVar12,iVar18 + iVar21,bVar1);
                  iVar21 = iVar21 + 1;
                }
                iVar18 = iVar18 + iVar7;
                iVar10 = iVar10 + iVar8;
              }
            }
            else {
              for (; iVar9 < iVar17; iVar9 = iVar9 + 1) {
                iVar21 = 0;
                for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
                  uVar5 = FUN_0003fe7c(*(undefined2 *)(iVar10 + iVar20 * 2));
                  *(undefined1 *)(iVar18 + iVar21) = uVar5;
                  iVar21 = iVar21 + 1;
                }
                iVar18 = iVar18 + iVar7;
                iVar10 = iVar10 + iVar8;
              }
            }
          }
          else {
            iVar21 = 0;
            if (bVar1 < 0xfd) {
              for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
                iVar13 = 0;
                for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
                  uVar12 = FUN_0003fe7c(*(undefined2 *)(iVar10 + iVar11 * 2));
                  FUN_00040280(uVar12,iVar18 + iVar13,
                               (uint)((int)(short)(ushort)*(byte *)(iVar20 + iVar11) *
                                     (int)(short)(ushort)bVar1) >> 8);
                  iVar13 = iVar13 + 1;
                }
                iVar18 = iVar18 + iVar7;
                iVar20 = iVar20 + iVar9;
                iVar10 = iVar10 + iVar8;
              }
            }
            else {
              for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
                iVar13 = 0;
                for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
                  uVar12 = FUN_0003fe7c(*(undefined2 *)(iVar10 + iVar11 * 2));
                  FUN_00040280(uVar12,iVar18 + iVar13,*(undefined1 *)(iVar20 + iVar11));
                  iVar13 = iVar13 + 1;
                }
                iVar18 = iVar18 + iVar7;
                iVar20 = iVar20 + iVar9;
                iVar10 = iVar10 + iVar8;
              }
            }
          }
        }
        else {
          for (iVar21 = 0; iVar21 < iVar17; iVar21 = iVar21 + 1) {
            iVar11 = 0;
            for (iVar13 = 0; iVar13 < iVar19; iVar13 = iVar13 + 1) {
              uVar2 = *(ushort *)(iVar10 + iVar13 * 2);
              uVar6 = ((uint)((short)(uVar2 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                      ((uint)((short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) * 0x40d) >> 8 & 0xff)
                      << 8;
              uVar14 = (uint)((short)(uVar2 & 0x1f) * 0x83a) >> 8 & 0xff;
              if (iVar20 == 0) {
                uVar14 = uVar6 | uVar14 | (uint)bVar1 << 0x18;
              }
              else {
                uVar14 = uVar6 | uVar14 |
                         ((uint)((int)(short)(ushort)*(byte *)(iVar20 + iVar13) *
                                (int)(short)(ushort)bVar1) >> 8) << 0x18;
              }
              FUN_00024a4c(iVar11 + iVar18,uVar14,*(undefined1 *)((int)param_1 + 0x22));
              iVar11 = iVar11 + 1;
            }
            if (iVar20 != 0) {
              iVar20 = iVar20 + iVar9;
            }
            iVar18 = iVar18 + iVar7;
            iVar10 = iVar10 + iVar8;
          }
        }
        return;
      }
      if (bVar1 != 0x15) {
        return;
      }
      iVar19 = param_1[1];
      iVar17 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar14 = (uint)bVar1;
      iVar18 = *param_1;
      iVar7 = param_1[3];
      iVar10 = param_1[6];
      iVar8 = param_1[7];
      iVar20 = param_1[4];
      iVar9 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar20 == 0) {
          iVar9 = 0;
          if (uVar14 < 0xfd) {
            for (; iVar9 < iVar17; iVar9 = iVar9 + 1) {
              iVar21 = 0;
              for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar20 * 2),iVar18 + iVar21,
                             (uint)((int)(short)(ushort)*(byte *)(iVar10 + iVar20 * 2 + 1) *
                                   (int)(short)(ushort)bVar1) >> 8);
                iVar21 = iVar21 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar10 = iVar10 + iVar8;
            }
          }
          else {
            for (; iVar9 < iVar17; iVar9 = iVar9 + 1) {
              iVar21 = 0;
              for (iVar20 = 0; iVar20 < iVar19; iVar20 = iVar20 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar20 * 2),iVar18 + iVar21,
                             *(undefined1 *)(iVar10 + iVar20 * 2 + 1));
                iVar21 = iVar21 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar10 = iVar10 + iVar8;
            }
          }
        }
        else {
          iVar21 = 0;
          if (uVar14 < 0xfd) {
            for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
              iVar13 = 0;
              for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar11 * 2),iVar18 + iVar13,
                             (int)(short)(ushort)*(byte *)(iVar10 + iVar11 * 2 + 1) *
                             (int)(short)(ushort)*(byte *)(iVar20 + iVar11) * uVar14 >> 0x10);
                iVar13 = iVar13 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar20 = iVar20 + iVar9;
              iVar10 = iVar10 + iVar8;
            }
          }
          else {
            for (; iVar21 < iVar17; iVar21 = iVar21 + 1) {
              iVar13 = 0;
              for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
                FUN_00040280(*(undefined1 *)(iVar10 + iVar11 * 2),iVar18 + iVar13,
                             (uint)((int)(short)(ushort)*(byte *)(iVar10 + iVar11 * 2 + 1) *
                                   (int)(short)(ushort)*(byte *)(iVar20 + iVar11)) >> 8);
                iVar13 = iVar13 + 1;
              }
              iVar18 = iVar18 + iVar7;
              iVar20 = iVar20 + iVar9;
              iVar10 = iVar10 + iVar8;
            }
          }
        }
      }
      else {
        for (iVar21 = 0; iVar21 < iVar17; iVar21 = iVar21 + 1) {
          local_5c = 0;
          for (iVar11 = 0; iVar11 < iVar19; iVar11 = iVar11 + 1) {
            uVar16 = (uint)*(byte *)(iVar10 + iVar11 * 2);
            uVar6 = uVar16 << 0x10 | uVar16 << 8;
            if (iVar20 == 0) {
              uVar6 = uVar6 | uVar16 | uVar14 << 0x18;
            }
            else {
              uVar6 = uVar6 | uVar16 |
                      ((uint)((int)(short)(ushort)*(byte *)(iVar20 + local_5c) *
                             (int)(short)(ushort)bVar1) >> 8) << 0x18;
            }
            FUN_00024a4c(local_5c + iVar18,uVar6,*(undefined1 *)((int)param_1 + 0x22));
            local_5c = local_5c + 1;
          }
          if (iVar20 != 0) {
            iVar20 = iVar20 + iVar9;
          }
          iVar18 = iVar18 + iVar7;
          iVar10 = iVar10 + iVar8;
        }
      }
      return;
    }
    iVar17 = 4;
  }
  iVar20 = param_1[1];
  iVar7 = param_1[2];
  bVar1 = *(byte *)((int)param_1 + 0x21);
  iVar19 = *param_1;
  iVar8 = param_1[3];
  iVar18 = param_1[6];
  iVar9 = param_1[7];
  iVar21 = param_1[4];
  iVar10 = param_1[5];
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar21 == 0) {
      if (0xfc < bVar1) {
        for (iVar10 = 0; iVar10 < iVar7; iVar10 = iVar10 + 1) {
          iVar11 = 0;
          for (iVar21 = 0; iVar21 < iVar20; iVar21 = iVar21 + 1) {
            uVar5 = FUN_0003fef6(iVar18 + iVar11);
            *(undefined1 *)(iVar19 + iVar21) = uVar5;
            iVar11 = iVar11 + iVar17;
          }
          iVar19 = iVar19 + iVar8;
          iVar18 = iVar18 + iVar9;
        }
        if (0xfc < bVar1) {
          return;
        }
      }
      for (iVar10 = 0; iVar10 < iVar7; iVar10 = iVar10 + 1) {
        iVar11 = 0;
        for (iVar21 = 0; iVar21 < iVar20; iVar21 = iVar21 + 1) {
          uVar12 = FUN_0003fef6(iVar18 + iVar11);
          FUN_00040280(uVar12,iVar19 + iVar21,bVar1);
          iVar11 = iVar11 + iVar17;
        }
        iVar19 = iVar19 + iVar8;
        iVar18 = iVar18 + iVar9;
      }
    }
    else {
      if (0xfc < bVar1) {
        for (iVar11 = 0; iVar11 < iVar7; iVar11 = iVar11 + 1) {
          iVar22 = 0;
          local_5c = 0;
          for (iVar13 = 0; iVar13 < iVar20; iVar13 = iVar13 + 1) {
            uVar12 = FUN_0003fef6(local_5c + iVar18);
            FUN_00040280(uVar12,iVar19 + iVar13,*(undefined1 *)(iVar21 + iVar22));
            iVar22 = iVar22 + 1;
            local_5c = local_5c + iVar17;
          }
          iVar19 = iVar19 + iVar8;
          iVar21 = iVar21 + iVar10;
          iVar18 = iVar18 + iVar9;
        }
        if (iVar21 == 0) {
          return;
        }
        if (0xfc < bVar1) {
          return;
        }
      }
      for (iVar11 = 0; iVar11 < iVar7; iVar11 = iVar11 + 1) {
        iVar22 = 0;
        local_68 = 0;
        for (iVar13 = 0; iVar13 < iVar20; iVar13 = iVar13 + 1) {
          uVar12 = FUN_0003fef6(iVar18 + iVar22);
          FUN_00040280(uVar12,iVar19 + iVar13,
                       (uint)((int)(short)(ushort)*(byte *)(iVar21 + local_68) *
                             (int)(short)(ushort)bVar1) >> 8);
          local_68 = local_68 + 1;
          iVar22 = iVar22 + iVar17;
        }
        iVar19 = iVar19 + iVar8;
        iVar21 = iVar21 + iVar10;
        iVar18 = iVar18 + iVar9;
      }
    }
  }
  else {
    for (iVar11 = 0; iVar11 < iVar7; iVar11 = iVar11 + 1) {
      iVar13 = 0;
      for (iVar22 = 0; iVar22 < iVar20; iVar22 = iVar22 + 1) {
        uVar14 = (uint)*(byte *)(iVar18 + iVar13 + 2) << 0x10 |
                 (uint)*(byte *)(iVar18 + iVar13 + 1) << 8;
        if (iVar21 == 0) {
          uVar14 = uVar14 | *(byte *)(iVar18 + iVar13) | (uint)bVar1 << 0x18;
        }
        else {
          uVar14 = uVar14 | *(byte *)(iVar18 + iVar13) |
                   ((uint)((int)(short)(ushort)*(byte *)(iVar21 + iVar22) *
                          (int)(short)(ushort)bVar1) >> 8) << 0x18;
        }
        FUN_00024a4c(iVar19 + iVar22,uVar14,*(undefined1 *)((int)param_1 + 0x22));
        iVar13 = iVar13 + iVar17;
      }
      if (iVar21 != 0) {
        iVar21 = iVar21 + iVar10;
      }
      iVar19 = iVar19 + iVar8;
      iVar18 = iVar18 + iVar9;
    }
  }
  return;
}

