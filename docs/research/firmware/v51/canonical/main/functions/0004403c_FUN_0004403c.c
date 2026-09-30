/* Address: 0004403c; name: FUN_0004403c; body bytes: 3960 */

void FUN_0004403c(int *param_1)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  byte bVar5;
  char cVar6;
  char cVar7;
  ushort uVar8;
  short sVar9;
  undefined2 uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  short sVar17;
  ushort uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint uVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int local_54;
  int local_48;
  int local_40;
  int local_3c;
  int local_30;
  
  bVar2 = *(byte *)(param_1 + 8);
  if (bVar2 == 0x10) {
    iVar25 = param_1[1];
    iVar19 = param_1[2];
    bVar2 = *(byte *)((int)param_1 + 0x21);
    uVar12 = (uint)bVar2;
    iVar15 = *param_1;
    iVar11 = param_1[3];
    iVar24 = param_1[6];
    iVar13 = param_1[7];
    iVar27 = param_1[4];
    iVar14 = param_1[5];
    if (*(char *)((int)param_1 + 0x22) == '\0') {
      if (iVar27 == 0) {
        iVar14 = 0;
        if (uVar12 < 0xfd) {
          for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
            iVar28 = 0;
            for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
              uVar10 = FUN_00040048(iVar24 + iVar28,*(undefined2 *)(iVar15 + iVar27 * 2),
                                    (uint)((int)(short)(ushort)*(byte *)(iVar24 + iVar28 + 3) *
                                          (int)(short)(ushort)bVar2) >> 8);
              *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
              iVar28 = iVar28 + 4;
            }
            iVar15 = iVar15 + iVar11;
            iVar24 = iVar24 + iVar13;
          }
        }
        else {
          for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
            iVar28 = 0;
            for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
              uVar10 = FUN_00040048(iVar24 + iVar28,*(undefined2 *)(iVar15 + iVar27 * 2),
                                    *(undefined1 *)(iVar24 + iVar28 + 3));
              *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
              iVar28 = iVar28 + 4;
            }
            iVar15 = iVar15 + iVar11;
            iVar24 = iVar24 + iVar13;
          }
        }
      }
      else {
        iVar28 = 0;
        if (uVar12 < 0xfd) {
          for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
            iVar26 = 0;
            for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
              uVar10 = FUN_00040048(iVar24 + iVar26,*(undefined2 *)(iVar15 + iVar16 * 2),
                                    (int)(short)(ushort)*(byte *)(iVar24 + iVar26 + 3) *
                                    (int)(short)(ushort)*(byte *)(iVar27 + iVar16) * uVar12 >> 0x10)
              ;
              *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
              iVar26 = iVar26 + 4;
            }
            iVar15 = iVar15 + iVar11;
            iVar24 = iVar24 + iVar13;
            iVar27 = iVar27 + iVar14;
          }
        }
        else {
          for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
            iVar26 = 0;
            for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
              uVar10 = FUN_00040048(iVar24 + iVar26,*(undefined2 *)(iVar15 + iVar16 * 2),
                                    (uint)((int)(short)(ushort)*(byte *)(iVar24 + iVar26 + 3) *
                                          (int)(short)(ushort)*(byte *)(iVar27 + iVar16)) >> 8);
              *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
              iVar26 = iVar26 + 4;
            }
            iVar15 = iVar15 + iVar11;
            iVar27 = iVar27 + iVar14;
            iVar24 = iVar24 + iVar13;
          }
        }
      }
    }
    else {
      for (iVar28 = 0; iVar28 < iVar19; iVar28 = iVar28 + 1) {
        local_40 = 0;
        for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
          cVar6 = *(char *)((int)param_1 + 0x22);
          if (cVar6 == '\x01') {
            uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
            uVar18 = (uVar4 >> 0xb) + (ushort)(*(byte *)(iVar24 + local_40 + 2) >> 3);
            if (0x1e < uVar18) {
              uVar18 = 0x1f;
            }
            uVar23 = ((uVar4 & 0x7ff) >> 5) + (uint)(*(byte *)(iVar24 + local_40 + 1) >> 2);
            sVar9 = (short)uVar23;
            if (0x3e < uVar23) {
              sVar9 = 0x3f;
            }
            sVar9 = uVar18 * 0x800 + sVar9 * 0x20;
            uVar23 = (uVar4 & 0x1f) + (uint)(*(byte *)(iVar24 + local_40) >> 3);
            if (0x1e < uVar23) {
              uVar23 = 0x1f;
            }
LAB_000243da:
            sVar9 = (short)uVar23 + sVar9;
          }
          else {
            if (cVar6 == '\x02') {
              uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
              iVar26 = (uint)(uVar4 >> 0xb) - (uint)(*(byte *)(local_40 + iVar24 + 2) >> 3);
              if (iVar26 < 1) {
                iVar26 = 0;
              }
              iVar20 = ((uVar4 & 0x7ff) >> 5) - (uint)(*(byte *)(local_40 + iVar24 + 1) >> 2);
              if (iVar20 < 1) {
                iVar20 = 0;
              }
              sVar9 = (short)iVar26 * 0x800 + (short)iVar20 * 0x20;
              uVar23 = (uVar4 & 0x1f) - (uint)(*(byte *)(iVar24 + local_40) >> 3);
              if ((int)uVar23 < 1) {
                uVar23 = 0;
              }
              goto LAB_000243da;
            }
            if (cVar6 != '\x03') {
              return;
            }
            uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
            sVar9 = (short)((uint)((int)(short)(uVar4 >> 0xb) *
                                  (int)(short)(ushort)(*(byte *)(iVar24 + local_40 + 2) >> 3)) >> 5)
                    * 0x800 + (short)((uint)((int)(short)(ushort)(((uint)uVar4 << 0x15) >> 0x1a) *
                                            (int)(short)(ushort)(*(byte *)(iVar24 + local_40 + 1) >>
                                                                2)) >> 6) * 0x20 +
                    (short)((uint)((int)(short)(uVar4 & 0x1f) *
                                  (int)(short)(ushort)(*(byte *)(iVar24 + local_40) >> 3)) >> 5);
          }
          if (iVar27 == 0) {
            bVar3 = *(byte *)(local_40 + iVar24 + 3);
            uVar23 = (uint)bVar3;
            if (uVar12 < 0xfd) {
              uVar23 = (uint)((int)(short)(ushort)bVar3 * (int)(short)(ushort)bVar2) >> 8;
            }
          }
          else {
            uVar23 = (uint)*(byte *)(iVar27 + iVar16);
            if (uVar12 < 0xfd) {
              uVar23 = (int)(short)(ushort)*(byte *)(iVar27 + iVar16) *
                       (int)(short)(ushort)*(byte *)(local_40 + iVar24 + 3) * uVar12 >> 0x10;
            }
          }
          uVar10 = FUN_0003ff4c(sVar9,*(undefined2 *)(iVar15 + iVar16 * 2),uVar23);
          *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
          local_40 = local_40 + 4;
        }
        iVar15 = iVar15 + iVar11;
        iVar24 = iVar24 + iVar13;
        if (iVar27 != 0) {
          iVar27 = iVar27 + iVar14;
        }
      }
    }
    return;
  }
  if (bVar2 < 0x11) {
    if (bVar2 == 6) {
      iVar25 = param_1[1];
      iVar19 = param_1[2];
      bVar2 = *(byte *)((int)param_1 + 0x21);
      uVar12 = (uint)bVar2;
      iVar15 = *param_1;
      iVar11 = param_1[3];
      iVar24 = param_1[6];
      iVar13 = param_1[7];
      iVar27 = param_1[4];
      iVar14 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar27 == 0) {
          iVar14 = 0;
          if (uVar12 < 0xfd) {
            for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
              iVar28 = 0;
              for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar28),
                                      *(undefined2 *)(iVar15 + iVar27 * 2),uVar12);
                *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                iVar28 = iVar28 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar24 = iVar24 + iVar13;
            }
          }
          else {
            for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
              iVar28 = 0;
              for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
                uVar10 = FUN_0003bc5a(*(undefined1 *)(iVar24 + iVar28));
                *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                iVar28 = iVar28 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar24 = iVar24 + iVar13;
            }
          }
        }
        else {
          iVar28 = 0;
          if (uVar12 < 0xfd) {
            for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
              iVar26 = 0;
              for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar26),
                                      *(undefined2 *)(iVar15 + iVar16 * 2),
                                      (uint)((int)(short)(ushort)*(byte *)(iVar27 + iVar16) *
                                            (int)(short)(ushort)bVar2) >> 8);
                *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                iVar26 = iVar26 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar27 = iVar27 + iVar14;
              iVar24 = iVar24 + iVar13;
            }
          }
          else {
            for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
              iVar26 = 0;
              for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar26),
                                      *(undefined2 *)(iVar15 + iVar16 * 2),
                                      *(undefined1 *)(iVar27 + iVar16));
                *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                iVar26 = iVar26 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar27 = iVar27 + iVar14;
              iVar24 = iVar24 + iVar13;
            }
          }
        }
      }
      else {
        for (iVar28 = 0; iVar28 < iVar19; iVar28 = iVar28 + 1) {
          local_30 = 0;
          for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
            cVar6 = *(char *)((int)param_1 + 0x22);
            bVar3 = *(byte *)(iVar24 + local_30) >> 3;
            uVar23 = (uint)bVar3;
            bVar5 = *(byte *)(iVar24 + local_30) >> 2;
            if (cVar6 == '\x01') {
              uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
              uVar22 = uVar23 + (uVar4 >> 0xb);
              sVar9 = (short)uVar22;
              if (0x1e < uVar22) {
                sVar9 = 0x1f;
              }
              uVar22 = (uint)bVar5 + ((uVar4 & 0x7ff) >> 5);
              sVar17 = (short)uVar22;
              if (0x3e < uVar22) {
                sVar17 = 0x3f;
              }
              sVar9 = sVar9 * 0x800 + sVar17 * 0x20;
              uVar23 = uVar23 + (uVar4 & 0x1f);
              if (0x1e < uVar23) {
                uVar23 = 0x1f;
              }
LAB_0003ba22:
              sVar9 = (short)uVar23 + sVar9;
            }
            else {
              if (cVar6 == '\x02') {
                uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
                iVar26 = (uVar4 >> 0xb) - uVar23;
                if (iVar26 < 1) {
                  iVar26 = 0;
                }
                iVar20 = ((uVar4 & 0x7ff) >> 5) - (uint)bVar5;
                if (iVar20 < 1) {
                  iVar20 = 0;
                }
                sVar9 = (short)iVar26 * 0x800 + (short)iVar20 * 0x20;
                uVar23 = (uVar4 & 0x1f) - uVar23;
                if ((int)uVar23 < 1) {
                  uVar23 = 0;
                }
                goto LAB_0003ba22;
              }
              if (cVar6 != '\x03') {
                return;
              }
              uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
              sVar9 = (short)((uint)((int)(short)(uVar4 >> 0xb) * (int)(short)(ushort)bVar3) >> 5) *
                      0x800 + (short)((uint)((int)(short)(ushort)(((uint)uVar4 << 0x15) >> 0x1a) *
                                            (int)(short)(ushort)bVar5) >> 6) * 0x20 +
                      (short)((uint)((int)(short)(uVar4 & 0x1f) * (int)(short)(ushort)bVar3) >> 5);
            }
            if (iVar27 == 0) {
              if (uVar12 < 0xfd) {
                uVar10 = *(undefined2 *)(iVar15 + iVar16 * 2);
                uVar23 = uVar12;
                goto LAB_0003baba;
              }
            }
            else {
              uVar23 = (uint)*(byte *)(iVar27 + iVar16);
              if (uVar12 < 0xfd) {
                uVar23 = (uint)((int)(short)(ushort)*(byte *)(iVar27 + iVar16) *
                               (int)(short)(ushort)bVar2) >> 8;
              }
              uVar10 = *(undefined2 *)(iVar15 + iVar16 * 2);
LAB_0003baba:
              sVar9 = FUN_0003ff4c(sVar9,uVar10,uVar23);
            }
            *(short *)(iVar15 + iVar16 * 2) = sVar9;
            local_30 = local_30 + 4;
          }
          iVar15 = iVar15 + iVar11;
          iVar24 = iVar24 + iVar13;
          if (iVar27 != 0) {
            iVar27 = iVar27 + iVar14;
          }
        }
      }
      return;
    }
    if (bVar2 == 7) {
      iVar24 = param_1[1];
      iVar19 = param_1[2];
      bVar2 = *(byte *)((int)param_1 + 0x21);
      uVar12 = (uint)bVar2;
      iVar15 = *param_1;
      iVar11 = param_1[3];
      local_48 = param_1[6];
      iVar13 = param_1[7];
      iVar25 = param_1[4];
      iVar14 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar25 == 0) {
          iVar14 = 0;
          if (uVar12 < 0xfd) {
            for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
              iVar25 = 0;
              for (iVar27 = 0; iVar27 < iVar24; iVar27 = iVar27 + 1) {
                cVar6 = FUN_00036efc(local_48,iVar25);
                uVar10 = FUN_00040194(-cVar6,*(undefined2 *)(iVar15 + iVar27 * 2),uVar12);
                *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                iVar25 = iVar25 + 1;
              }
              iVar15 = iVar15 + iVar11;
              local_48 = local_48 + iVar13;
            }
          }
          else {
            for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
              iVar25 = 0;
              for (iVar27 = 0; iVar27 < iVar24; iVar27 = iVar27 + 1) {
                cVar6 = FUN_00036efc(local_48,iVar25);
                uVar10 = FUN_0003bc5a(-cVar6);
                *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                iVar25 = iVar25 + 1;
              }
              iVar15 = iVar15 + iVar11;
              local_48 = local_48 + iVar13;
            }
          }
        }
        else if (uVar12 < 0xfd) {
          for (iVar27 = 0; iVar27 < iVar19; iVar27 = iVar27 + 1) {
            iVar16 = 0;
            for (iVar28 = 0; iVar28 < iVar24; iVar28 = iVar28 + 1) {
              cVar6 = FUN_00036efc(local_48,iVar16);
              uVar10 = FUN_00040194(-cVar6,*(undefined2 *)(iVar15 + iVar28 * 2),
                                    (uint)((int)(short)(ushort)*(byte *)(iVar25 + iVar28) *
                                          (int)(short)(ushort)bVar2) >> 8);
              *(undefined2 *)(iVar15 + iVar28 * 2) = uVar10;
              iVar16 = iVar16 + 1;
            }
            iVar15 = iVar15 + iVar11;
            local_48 = iVar13 + local_48;
            iVar25 = iVar25 + iVar14;
          }
        }
        else {
          for (iVar27 = 0; iVar27 < iVar19; iVar27 = iVar27 + 1) {
            iVar28 = 0;
            for (iVar16 = 0; iVar16 < iVar24; iVar16 = iVar16 + 1) {
              cVar6 = FUN_00036efc(local_48,iVar28);
              uVar10 = FUN_00040194(-cVar6,*(undefined2 *)(iVar15 + iVar16 * 2),
                                    *(undefined1 *)(iVar25 + iVar16));
              *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
              iVar28 = iVar28 + 1;
            }
            iVar15 = iVar15 + iVar11;
            local_48 = iVar13 + local_48;
            iVar25 = iVar25 + iVar14;
          }
        }
      }
      else {
        for (iVar27 = 0; iVar27 < iVar19; iVar27 = iVar27 + 1) {
          local_54 = 0;
          for (iVar28 = 0; iVar28 < iVar24; iVar28 = iVar28 + 1) {
            cVar7 = FUN_00036efc(local_48,local_54);
            cVar7 = -cVar7;
            cVar6 = *(char *)((int)param_1 + 0x22);
            if (cVar6 == '\x01') {
              iVar16 = FUN_0003bc5a(cVar7);
              uVar23 = 0xffff;
              if ((uint)*(ushort *)(iVar15 + iVar28 * 2) + iVar16 < 0xffff) {
                iVar16 = FUN_0003bc5a(cVar7);
                uVar23 = iVar16 + (uint)*(ushort *)(iVar15 + iVar28 * 2);
              }
LAB_00038ba0:
              uVar23 = uVar23 & 0xffff;
            }
            else {
              if (cVar6 == '\x02') {
                iVar16 = FUN_0003bc5a(cVar7);
                if ((int)((uint)*(ushort *)(iVar15 + iVar28 * 2) - iVar16) < 1) {
                  uVar23 = 0;
                }
                else {
                  iVar16 = FUN_0003bc5a(cVar7);
                  uVar23 = (uint)*(ushort *)(iVar15 + iVar28 * 2) - iVar16;
                }
                goto LAB_00038ba0;
              }
              if (cVar6 != '\x03') {
                return;
              }
              uVar23 = FUN_0003bc5a(cVar7);
              uVar4 = *(ushort *)(iVar15 + iVar28 * 2);
              iVar16 = FUN_0003bc5a(cVar7);
              uVar18 = *(ushort *)(iVar15 + iVar28 * 2);
              uVar8 = FUN_0003bc5a(cVar7);
              uVar23 = ((int)(short)(uVar23 >> 3) * (int)(short)(uVar4 >> 0xb) & 0x1fU) << 0xb |
                       ((uint)((int)(short)(ushort)((uint)(iVar16 << 0x18) >> 0x1a) *
                              (int)(short)(ushort)(((uint)uVar18 << 0x15) >> 0x1a)) >> 6) << 5 |
                       (uint)((int)(short)(uVar8 & 0x1f) *
                             (int)(short)(*(byte *)(iVar15 + iVar28 * 2) & 0x1f)) >> 5;
            }
            uVar10 = (undefined2)uVar23;
            if (iVar25 == 0) {
              if (uVar12 < 0xfd) {
                uVar10 = *(undefined2 *)(iVar15 + iVar28 * 2);
                uVar22 = uVar12;
                goto LAB_00038c06;
              }
            }
            else {
              uVar22 = (uint)*(byte *)(iVar25 + iVar28);
              if (uVar12 < 0xfd) {
                uVar22 = (uint)((int)(short)(ushort)*(byte *)(iVar25 + iVar28) *
                               (int)(short)(ushort)bVar2) >> 8;
              }
              uVar10 = *(undefined2 *)(iVar15 + iVar28 * 2);
LAB_00038c06:
              uVar10 = FUN_0003ff4c(uVar23,uVar10,uVar22);
            }
            *(undefined2 *)(iVar15 + iVar28 * 2) = uVar10;
            local_54 = local_54 + 4;
          }
          iVar15 = iVar15 + iVar11;
          local_48 = local_48 + iVar13;
          if (iVar25 != 0) {
            iVar25 = iVar25 + iVar14;
          }
        }
      }
      return;
    }
    if (bVar2 != 0xf) {
      return;
    }
    iVar19 = 3;
  }
  else {
    if (bVar2 != 0x11) {
      if (bVar2 == 0x12) {
        iVar25 = param_1[1];
        iVar19 = param_1[2];
        bVar2 = *(byte *)((int)param_1 + 0x21);
        uVar12 = (uint)bVar2;
        iVar15 = *param_1;
        iVar11 = param_1[3];
        iVar24 = param_1[6];
        iVar13 = param_1[7];
        iVar27 = param_1[4];
        iVar14 = param_1[5];
        if (*(char *)((int)param_1 + 0x22) == '\0') {
          if (iVar27 == 0) {
            if (uVar12 < 0xfd) {
              for (iVar14 = 0; iVar14 < iVar19; iVar14 = iVar14 + 1) {
                for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
                  uVar10 = FUN_0003ff4c(*(undefined2 *)(iVar24 + iVar27 * 2),
                                        *(undefined2 *)(iVar15 + iVar27 * 2),uVar12);
                  *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                }
                iVar15 = iVar15 + iVar11;
                iVar24 = iVar24 + iVar13;
              }
            }
            else {
              for (iVar14 = 0; iVar14 < iVar19; iVar14 = iVar14 + 1) {
                FUN_0004a404(iVar15,iVar24,iVar25 << 1);
                iVar15 = iVar15 + iVar11;
                iVar24 = iVar24 + iVar13;
              }
            }
          }
          else {
            iVar28 = 0;
            if (uVar12 < 0xfd) {
              for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
                for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
                  uVar10 = FUN_0003ff4c(*(undefined2 *)(iVar24 + iVar16 * 2),
                                        *(undefined2 *)(iVar15 + iVar16 * 2),
                                        (uint)((int)(short)(ushort)*(byte *)(iVar27 + iVar16) *
                                              (int)(short)(ushort)bVar2) >> 8);
                  *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                }
                iVar15 = iVar15 + iVar11;
                iVar27 = iVar27 + iVar14;
                iVar24 = iVar24 + iVar13;
              }
            }
            else {
              for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
                for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
                  uVar10 = FUN_0003ff4c(*(undefined2 *)(iVar24 + iVar16 * 2),
                                        *(undefined2 *)(iVar15 + iVar16 * 2),
                                        *(undefined1 *)(iVar27 + iVar16));
                  *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                }
                iVar15 = iVar15 + iVar11;
                iVar27 = iVar27 + iVar14;
                iVar24 = iVar24 + iVar13;
              }
            }
          }
        }
        else {
          for (iVar28 = 0; iVar28 < iVar19; iVar28 = iVar28 + 1) {
            for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
              cVar6 = *(char *)((int)param_1 + 0x22);
              if (cVar6 == '\x01') {
                if (*(short *)(iVar24 + iVar16 * 2) != 0) {
                  uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
                  uVar18 = *(ushort *)(iVar24 + iVar16 * 2);
                  uVar8 = (uVar4 >> 0xb) + (uVar18 >> 0xb);
                  if (0x1e < uVar8) {
                    uVar8 = 0x1f;
                  }
                  uVar23 = ((uVar4 & 0x7ff) >> 5) + ((uVar18 & 0x7ff) >> 5);
                  sVar9 = (short)uVar23;
                  if (0x3e < uVar23) {
                    sVar9 = 0x3f;
                  }
                  sVar9 = uVar8 * 0x800 + sVar9 * 0x20;
                  uVar23 = (uVar18 & 0x1f) + (uVar4 & 0x1f);
                  if (0x1e < uVar23) {
                    uVar23 = 0x1f;
                  }
LAB_0005beae:
                  sVar9 = (short)uVar23 + sVar9;
LAB_0005be16:
                  if (iVar27 == 0) {
                    uVar10 = *(undefined2 *)(iVar15 + iVar16 * 2);
                    uVar23 = uVar12;
                  }
                  else {
                    uVar23 = (uint)*(byte *)(iVar27 + iVar16);
                    if (uVar12 < 0xfd) {
                      uVar23 = (uint)((int)(short)(ushort)*(byte *)(iVar27 + iVar16) *
                                     (int)(short)(ushort)bVar2) >> 8;
                    }
                    uVar10 = *(undefined2 *)(iVar15 + iVar16 * 2);
                  }
                  uVar10 = FUN_0003ff4c(sVar9,uVar10,uVar23);
                  *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                }
              }
              else if (cVar6 == '\x02') {
                if (*(short *)(iVar24 + iVar16 * 2) != 0) {
                  uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
                  uVar18 = *(ushort *)(iVar24 + iVar16 * 2);
                  iVar26 = (uint)(uVar4 >> 0xb) - (uint)(uVar18 >> 0xb);
                  if (iVar26 < 1) {
                    iVar26 = 0;
                  }
                  iVar20 = ((uVar4 & 0x7ff) >> 5) - ((uVar18 & 0x7ff) >> 5);
                  if (iVar20 < 1) {
                    iVar20 = 0;
                  }
                  sVar9 = (short)iVar26 * 0x800 + (short)iVar20 * 0x20;
                  uVar23 = (uVar4 & 0x1f) - (uVar18 & 0x1f);
                  if ((int)uVar23 < 1) {
                    uVar23 = 0;
                  }
                  goto LAB_0005beae;
                }
              }
              else {
                if (cVar6 != '\x03') {
                  return;
                }
                if (*(short *)(iVar24 + iVar16 * 2) != -1) {
                  uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
                  uVar18 = *(ushort *)(iVar24 + iVar16 * 2);
                  sVar9 = (short)((uint)((int)(short)(uVar4 >> 0xb) * (int)(short)(uVar18 >> 0xb))
                                 >> 5) * 0x800 +
                          (short)((uint)((int)(short)(ushort)(((uint)uVar4 << 0x15) >> 0x1a) *
                                        (int)(short)(ushort)(((uint)uVar18 << 0x15) >> 0x1a)) >> 6)
                          * 0x20 + (short)((uint)((int)(short)(uVar4 & 0x1f) *
                                                 (int)(short)(uVar18 & 0x1f)) >> 5);
                  goto LAB_0005be16;
                }
              }
            }
            iVar15 = iVar15 + iVar11;
            iVar24 = iVar24 + iVar13;
            if (iVar27 != 0) {
              iVar27 = iVar27 + iVar14;
            }
          }
        }
        return;
      }
      if (bVar2 != 0x15) {
        return;
      }
      iVar25 = param_1[1];
      iVar19 = param_1[2];
      bVar2 = *(byte *)((int)param_1 + 0x21);
      uVar12 = (uint)bVar2;
      iVar15 = *param_1;
      iVar11 = param_1[3];
      iVar24 = param_1[6];
      iVar13 = param_1[7];
      iVar27 = param_1[4];
      iVar14 = param_1[5];
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar27 == 0) {
          iVar14 = 0;
          if (uVar12 < 0xfd) {
            for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
              iVar28 = 0;
              for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar28 * 2),
                                      *(undefined2 *)(iVar15 + iVar27 * 2),
                                      (uint)((int)(short)(ushort)*(byte *)(iVar24 + iVar28 * 2 + 1)
                                            * (int)(short)(ushort)bVar2) >> 8);
                *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                iVar28 = iVar28 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar24 = iVar24 + iVar13;
            }
          }
          else {
            for (; iVar14 < iVar19; iVar14 = iVar14 + 1) {
              iVar28 = 0;
              for (iVar27 = 0; iVar27 < iVar25; iVar27 = iVar27 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar28 * 2),
                                      *(undefined2 *)(iVar15 + iVar27 * 2),
                                      *(undefined1 *)(iVar24 + iVar28 * 2 + 1));
                *(undefined2 *)(iVar15 + iVar27 * 2) = uVar10;
                iVar28 = iVar28 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar24 = iVar24 + iVar13;
            }
          }
        }
        else {
          iVar28 = 0;
          if (uVar12 < 0xfd) {
            for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
              iVar26 = 0;
              for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar26 * 2),
                                      *(undefined2 *)(iVar15 + iVar16 * 2),
                                      (int)(short)(ushort)*(byte *)(iVar24 + iVar26 * 2 + 1) *
                                      (int)(short)(ushort)*(byte *)(iVar27 + iVar16) * uVar12 >>
                                      0x10);
                *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                iVar26 = iVar26 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar27 = iVar27 + iVar14;
              iVar24 = iVar24 + iVar13;
            }
          }
          else {
            for (; iVar28 < iVar19; iVar28 = iVar28 + 1) {
              iVar26 = 0;
              for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
                uVar10 = FUN_00040194(*(undefined1 *)(iVar24 + iVar26 * 2),
                                      *(undefined2 *)(iVar15 + iVar16 * 2),
                                      (uint)((int)(short)(ushort)*(byte *)(iVar24 + iVar26 * 2 + 1)
                                            * (int)(short)(ushort)*(byte *)(iVar27 + iVar16)) >> 8);
                *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
                iVar26 = iVar26 + 1;
              }
              iVar15 = iVar15 + iVar11;
              iVar27 = iVar27 + iVar14;
              iVar24 = iVar24 + iVar13;
            }
          }
        }
      }
      else {
        for (iVar28 = 0; iVar28 < iVar19; iVar28 = iVar28 + 1) {
          local_40 = 0;
          for (iVar16 = 0; iVar16 < iVar25; iVar16 = iVar16 + 1) {
            bVar3 = *(byte *)(iVar24 + local_40 * 2);
            cVar6 = *(char *)((int)param_1 + 0x22);
            bVar5 = bVar3 >> 3;
            uVar23 = (uint)bVar5;
            bVar3 = bVar3 >> 2;
            if (cVar6 == '\x01') {
              uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
              uVar22 = uVar23 + (uVar4 >> 0xb);
              sVar9 = (short)uVar22;
              if (0x1e < uVar22) {
                sVar9 = 0x1f;
              }
              uVar22 = (uint)bVar3 + ((uVar4 & 0x7ff) >> 5);
              sVar17 = (short)uVar22;
              if (0x3e < uVar22) {
                sVar17 = 0x3f;
              }
              sVar9 = sVar9 * 0x800 + sVar17 * 0x20;
              uVar23 = uVar23 + (uVar4 & 0x1f);
              if (0x1e < uVar23) {
                uVar23 = 0x1f;
              }
LAB_00023406:
              sVar9 = (short)uVar23 + sVar9;
            }
            else {
              if (cVar6 == '\x02') {
                uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
                iVar26 = (uVar4 >> 0xb) - uVar23;
                if (iVar26 < 1) {
                  iVar26 = 0;
                }
                iVar20 = ((uVar4 & 0x7ff) >> 5) - (uint)bVar3;
                if (iVar20 < 1) {
                  iVar20 = 0;
                }
                sVar9 = (short)iVar26 * 0x800 + (short)iVar20 * 0x20;
                uVar23 = (uVar4 & 0x1f) - uVar23;
                if ((int)uVar23 < 1) {
                  uVar23 = 0;
                }
                goto LAB_00023406;
              }
              if (cVar6 != '\x03') {
                return;
              }
              uVar4 = *(ushort *)(iVar15 + iVar16 * 2);
              sVar9 = (short)((uint)((int)(short)(uVar4 >> 0xb) * (int)(short)(ushort)bVar5) >> 5) *
                      0x800 + (short)((uint)((int)(short)(ushort)(((uint)uVar4 << 0x15) >> 0x1a) *
                                            (int)(short)(ushort)bVar3) >> 6) * 0x20 +
                      (short)((uint)((int)(short)(uVar4 & 0x1f) * (int)(short)(ushort)bVar5) >> 5);
            }
            if (iVar27 == 0) {
              bVar3 = *(byte *)(iVar24 + local_40 * 2 + 1);
              uVar23 = (uint)bVar3;
              if (uVar12 < 0xfd) {
                uVar23 = (uint)((int)(short)(ushort)bVar3 * (int)(short)(ushort)bVar2) >> 8;
              }
            }
            else {
              uVar23 = (uint)*(byte *)(iVar27 + iVar16);
              if (uVar12 < 0xfd) {
                uVar23 = (int)(short)(ushort)*(byte *)(iVar27 + iVar16) *
                         (int)(short)(ushort)*(byte *)(iVar24 + local_40 * 2 + 1) * uVar12 >> 0x10;
              }
            }
            uVar10 = FUN_0003ff4c(sVar9,*(undefined2 *)(iVar15 + iVar16 * 2),uVar23);
            *(undefined2 *)(iVar15 + iVar16 * 2) = uVar10;
            local_40 = local_40 + 4;
          }
          iVar15 = iVar15 + iVar11;
          iVar24 = iVar24 + iVar13;
          if (iVar27 != 0) {
            iVar27 = iVar27 + iVar14;
          }
        }
      }
      return;
    }
    iVar19 = 4;
  }
  iVar27 = param_1[1];
  iVar11 = param_1[2];
  bVar2 = *(byte *)((int)param_1 + 0x21);
  uVar12 = (uint)bVar2;
  iVar24 = *param_1;
  iVar13 = param_1[3];
  iVar25 = param_1[6];
  iVar14 = param_1[7];
  iVar28 = param_1[4];
  iVar15 = param_1[5];
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar28 == 0) {
      if (uVar12 < 0xfd) {
        for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
          iVar16 = 0;
          for (iVar28 = 0; iVar28 < iVar27; iVar28 = iVar28 + 1) {
            uVar10 = FUN_00040048(iVar25 + iVar16,*(undefined2 *)(iVar24 + iVar28 * 2),uVar12);
            *(undefined2 *)(iVar24 + iVar28 * 2) = uVar10;
            iVar16 = iVar16 + iVar19;
          }
          iVar24 = iVar24 + iVar13;
          iVar25 = iVar25 + iVar14;
        }
      }
      else {
        for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
          iVar16 = 0;
          for (iVar28 = 0; iVar28 < iVar27; iVar28 = iVar28 + 1) {
            iVar26 = iVar25 + iVar16;
            pbVar1 = (byte *)(iVar25 + iVar16);
            iVar16 = iVar16 + iVar19;
            *(ushort *)(iVar24 + iVar28 * 2) =
                 (*(byte *)(iVar26 + 2) & 0xf8) * 0x100 + (*(byte *)(iVar26 + 1) & 0xfc) * 8 +
                 (ushort)(*pbVar1 >> 3);
          }
          iVar24 = iVar24 + iVar13;
          iVar25 = iVar25 + iVar14;
        }
      }
    }
    else {
      if (0xfc < uVar12) {
        for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
          iVar20 = 0;
          for (iVar26 = 0; iVar26 < iVar27; iVar26 = iVar26 + 1) {
            uVar10 = FUN_00040048(iVar25 + iVar20,*(undefined2 *)(iVar24 + iVar26 * 2),
                                  *(undefined1 *)(iVar28 + iVar26));
            *(undefined2 *)(iVar24 + iVar26 * 2) = uVar10;
            iVar20 = iVar20 + iVar19;
          }
          iVar24 = iVar24 + iVar13;
          iVar28 = iVar28 + iVar15;
          iVar25 = iVar25 + iVar14;
        }
        if (iVar28 == 0) {
          return;
        }
        if (0xfc < uVar12) {
          return;
        }
      }
      for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
        iVar20 = 0;
        for (iVar26 = 0; iVar26 < iVar27; iVar26 = iVar26 + 1) {
          uVar10 = FUN_00040048(iVar25 + iVar20,*(undefined2 *)(iVar24 + iVar26 * 2),
                                (uint)((int)(short)(ushort)*(byte *)(iVar28 + iVar26) *
                                      (int)(short)(ushort)bVar2) >> 8);
          *(undefined2 *)(iVar24 + iVar26 * 2) = uVar10;
          iVar20 = iVar20 + iVar19;
        }
        iVar24 = iVar24 + iVar13;
        iVar28 = iVar28 + iVar15;
        iVar25 = iVar25 + iVar14;
      }
    }
  }
  else {
    for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
      local_3c = 0;
      for (iVar26 = 0; iVar26 < iVar27; iVar26 = iVar26 + 1) {
        cVar6 = *(char *)((int)param_1 + 0x22);
        if (cVar6 == '\x01') {
          uVar4 = *(ushort *)(iVar24 + iVar26 * 2);
          uVar18 = (uVar4 >> 0xb) + (ushort)(*(byte *)(iVar25 + local_3c + 2) >> 3);
          if (0x1e < uVar18) {
            uVar18 = 0x1f;
          }
          uVar23 = ((uVar4 & 0x7ff) >> 5) + (uint)(*(byte *)(iVar25 + local_3c + 1) >> 2);
          sVar9 = (short)uVar23;
          if (0x3e < uVar23) {
            sVar9 = 0x3f;
          }
          sVar9 = uVar18 * 0x800 + sVar9 * 0x20;
          uVar23 = (uVar4 & 0x1f) + (uint)(*(byte *)(iVar25 + local_3c) >> 3);
          if (0x1e < uVar23) {
            uVar23 = 0x1f;
          }
LAB_0005cc16:
          sVar9 = (short)uVar23 + sVar9;
        }
        else {
          if (cVar6 == '\x02') {
            uVar4 = *(ushort *)(iVar24 + iVar26 * 2);
            iVar20 = (uint)(uVar4 >> 0xb) - (uint)(*(byte *)(iVar25 + local_3c + 2) >> 3);
            if (iVar20 < 1) {
              iVar20 = 0;
            }
            iVar21 = ((uVar4 & 0x7ff) >> 5) - (uint)(*(byte *)(iVar25 + local_3c + 1) >> 2);
            if (iVar21 < 1) {
              iVar21 = 0;
            }
            sVar9 = (short)iVar20 * 0x800 + (short)iVar21 * 0x20;
            uVar23 = (uVar4 & 0x1f) - (uint)(*(byte *)(iVar25 + local_3c) >> 3);
            if ((int)uVar23 < 1) {
              uVar23 = 0;
            }
            goto LAB_0005cc16;
          }
          if (cVar6 != '\x03') {
            return;
          }
          uVar4 = *(ushort *)(iVar24 + iVar26 * 2);
          sVar9 = (short)((uint)((int)(short)(uVar4 >> 0xb) *
                                (int)(short)(ushort)(*(byte *)(iVar25 + local_3c + 2) >> 3)) >> 5) *
                  0x800 + (short)((uint)((int)(short)(ushort)(((uint)uVar4 << 0x15) >> 0x1a) *
                                        (int)(short)(ushort)(*(byte *)(iVar25 + local_3c + 1) >> 2))
                                 >> 6) * 0x20 +
                  (short)((uint)((int)(short)(uVar4 & 0x1f) *
                                (int)(short)(ushort)(*(byte *)(iVar25 + local_3c) >> 3)) >> 5);
        }
        if (iVar28 == 0) {
          uVar10 = *(undefined2 *)(iVar24 + iVar26 * 2);
          uVar23 = uVar12;
        }
        else {
          uVar23 = (uint)*(byte *)(iVar28 + iVar26);
          if (uVar12 < 0xfd) {
            uVar23 = (uint)((int)(short)(ushort)*(byte *)(iVar28 + iVar26) *
                           (int)(short)(ushort)bVar2) >> 8;
          }
          uVar10 = *(undefined2 *)(iVar24 + iVar26 * 2);
        }
        uVar10 = FUN_0003ff4c(sVar9,uVar10,uVar23);
        *(undefined2 *)(iVar24 + iVar26 * 2) = uVar10;
        local_3c = local_3c + iVar19;
      }
      iVar24 = iVar24 + iVar13;
      iVar25 = iVar25 + iVar14;
      if (iVar28 != 0) {
        iVar28 = iVar28 + iVar15;
      }
    }
  }
  return;
}

