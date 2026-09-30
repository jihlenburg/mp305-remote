/* Address: 00043fb8; name: FUN_00043fb8; body bytes: 3766 */

void FUN_00043fb8(int *param_1)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  char cVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined4 *puVar17;
  int iVar18;
  int local_70;
  int local_68;
  int local_5c;
  int local_58;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  uint local_3c;
  int local_38;
  undefined4 *local_34;
  undefined4 *local_30;
  undefined4 *local_2c;
  uint local_28;
  
  bVar1 = *(byte *)(param_1 + 8);
  if (bVar1 == 0x10) {
    iVar11 = param_1[1];
    iVar12 = param_1[2];
    bVar1 = *(byte *)((int)param_1 + 0x21);
    uVar7 = (uint)bVar1;
    local_48 = *param_1;
    local_40 = param_1[3];
    iVar10 = param_1[6];
    local_3c = param_1[7];
    iVar13 = param_1[4];
    local_38 = param_1[5];
    iVar15 = param_1[9] % 8;
    if (*(char *)((int)param_1 + 0x22) == '\0') {
      if (iVar13 == 0) {
        iVar13 = 0;
        if (uVar7 < 0xfd) {
          for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
            for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
              local_34 = (undefined4 *)(iVar10 + iVar16 * 4);
              local_38 = FUN_0003ff24(*local_34);
              cVar4 = FUN_00036ec0(local_48);
              local_44 = CONCAT31(local_44._1_3_,-cVar4);
              FUN_00040264(local_38,&local_44,
                           (uint)((int)(short)(ushort)*(byte *)((int)local_34 + 3) *
                                 (int)(short)(ushort)bVar1) >> 8);
              if ((byte)local_44 < 0x80) {
                FUN_00027368(local_48,iVar16 + iVar15);
              }
              else {
                FUN_0005e778();
              }
            }
            local_48 = local_48 + local_40;
            iVar10 = iVar10 + local_3c;
          }
        }
        else {
          for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
            for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
              puVar17 = (undefined4 *)(iVar10 + iVar16 * 4);
              local_38 = FUN_0003ff24(*puVar17);
              cVar4 = FUN_00036ec0(local_48);
              local_44 = CONCAT31(local_44._1_3_,-cVar4);
              FUN_00040264(local_38,&local_44,*(undefined1 *)((int)puVar17 + 3));
              if ((byte)local_44 < 0x80) {
                FUN_00027368(local_48,iVar16 + iVar15);
              }
              else {
                FUN_0005e778();
              }
            }
            local_48 = local_40 + local_48;
            iVar10 = iVar10 + local_3c;
          }
        }
      }
      else {
        iVar16 = 0;
        if (uVar7 < 0xfd) {
          for (; iVar16 < iVar12; iVar16 = iVar16 + 1) {
            for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
              local_2c = (undefined4 *)(iVar10 + iVar14 * 4);
              local_30 = (undefined4 *)FUN_0003ff24(*local_2c);
              local_44 = iVar14 + iVar15;
              cVar4 = FUN_00036ec0(local_48);
              local_34 = (undefined4 *)CONCAT31(local_34._1_3_,-cVar4);
              FUN_00040264(local_30,&local_34,
                           (int)(short)(ushort)*(byte *)(iVar13 + iVar14) *
                           (int)(short)(ushort)*(byte *)((int)local_2c + 3) * uVar7 >> 0x10);
              if ((byte)local_34 < 0x80) {
                FUN_00027368(local_48,local_44);
              }
              else {
                FUN_0005e778();
              }
            }
            local_48 = local_48 + local_40;
            iVar10 = iVar10 + local_3c;
            iVar13 = iVar13 + local_38;
          }
        }
        else {
          for (; iVar16 < iVar12; iVar16 = iVar16 + 1) {
            for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
              local_30 = (undefined4 *)(iVar10 + iVar14 * 4);
              local_34 = (undefined4 *)FUN_0003ff24(*local_30);
              cVar4 = FUN_00036ec0(local_48);
              local_44 = CONCAT31(local_44._1_3_,-cVar4);
              FUN_00040264(local_34,&local_44,
                           (uint)((int)(short)(ushort)*(byte *)(iVar13 + iVar14) *
                                 (int)(short)(ushort)*(byte *)((int)local_30 + 3)) >> 8);
              if ((byte)local_44 < 0x80) {
                FUN_00027368(local_48,iVar14 + iVar15);
              }
              else {
                FUN_0005e778();
              }
            }
            local_48 = local_48 + local_40;
            iVar10 = iVar10 + local_3c;
            iVar13 = iVar13 + local_38;
          }
        }
      }
    }
    else {
      for (local_44 = 0; local_44 < iVar12; local_44 = local_44 + 1) {
        for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
          uVar9 = *(uint *)(iVar10 + iVar16 * 4);
          bVar3 = (byte)(uVar9 >> 0x18);
          if (iVar13 == 0) {
            uVar8 = (uint)((int)(short)(ushort)bVar3 * (int)(short)(ushort)bVar1) >> 8;
          }
          else {
            uVar8 = (int)(short)(ushort)bVar3 * (int)(short)(ushort)*(byte *)(iVar13 + iVar16) *
                    uVar7 >> 0x10;
          }
          FUN_000249da(local_48,iVar16 + iVar15,uVar9 & 0xffffff | uVar8 << 0x18,
                       *(undefined1 *)((int)param_1 + 0x22));
        }
        if (iVar13 != 0) {
          iVar13 = iVar13 + local_38;
        }
        local_48 = local_48 + local_40;
        iVar10 = iVar10 + local_3c;
      }
    }
    return;
  }
  if (bVar1 < 0x11) {
    if (bVar1 == 6) {
      iVar11 = param_1[1];
      iVar12 = param_1[2];
      local_3c = (uint)*(byte *)((int)param_1 + 0x21);
      iVar16 = *param_1;
      local_30 = (undefined4 *)param_1[3];
      iVar10 = param_1[6];
      local_34 = (undefined4 *)param_1[7];
      iVar13 = param_1[4];
      local_4c = param_1[5];
      iVar15 = param_1[9] % 8;
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar13 == 0) {
          iVar13 = 0;
          if (local_3c < 0xfd) {
            for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
              iVar18 = 0;
              for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                local_5c = iVar18 + iVar15;
                cVar4 = FUN_00036ec0(iVar16);
                local_4c = CONCAT31(local_4c._1_3_,-cVar4);
                FUN_00040264(*(undefined1 *)(iVar10 + iVar14),&local_4c,local_3c);
                if ((byte)local_4c < 0x80) {
                  FUN_00027368(iVar16,local_5c);
                }
                else {
                  FUN_0005e778();
                }
                iVar18 = iVar18 + 1;
              }
              iVar16 = iVar16 + (int)local_30;
              iVar10 = iVar10 + (int)local_34;
            }
          }
          else {
            for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
              iVar18 = 0;
              for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                if (*(byte *)(iVar10 + iVar14) < 0x80) {
                  FUN_00027368(iVar16,iVar18 + iVar15);
                }
                else {
                  FUN_0005e778();
                }
                iVar18 = iVar18 + 1;
              }
              iVar16 = iVar16 + (int)local_30;
              iVar10 = iVar10 + (int)local_34;
            }
          }
        }
        else {
          local_58 = 0;
          if (local_3c < 0xfd) {
            for (; local_58 < iVar12; local_58 = local_58 + 1) {
              iVar18 = 0;
              for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                local_28 = (uint)*(byte *)(iVar10 + iVar14);
                local_40 = iVar18 + iVar15;
                cVar4 = FUN_00036ec0(iVar16);
                local_2c = (undefined4 *)CONCAT31(local_2c._1_3_,-cVar4);
                FUN_00040264(local_28,&local_2c,
                             (uint)((int)(short)(ushort)*(byte *)(iVar13 + iVar14) *
                                   (int)(short)local_3c) >> 8);
                if ((byte)local_2c < 0x80) {
                  FUN_00027368(iVar16,local_40);
                }
                else {
                  FUN_0005e778();
                }
                iVar18 = iVar18 + 1;
              }
              iVar16 = iVar16 + (int)local_30;
              iVar10 = iVar10 + (int)local_34;
              iVar13 = iVar13 + local_4c;
            }
          }
          else {
            for (; local_58 < iVar12; local_58 = local_58 + 1) {
              iVar18 = 0;
              for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                local_2c = (undefined4 *)(uint)*(byte *)(iVar10 + iVar14);
                local_40 = iVar18 + iVar15;
                cVar4 = FUN_00036ec0(iVar16);
                local_3c = CONCAT31(local_3c._1_3_,-cVar4);
                FUN_00040264(local_2c,&local_3c,*(undefined1 *)(iVar13 + iVar14));
                if ((byte)local_3c < 0x80) {
                  FUN_00027368(iVar16,local_40);
                }
                else {
                  FUN_0005e778();
                }
                iVar18 = iVar18 + 1;
              }
              iVar16 = iVar16 + (int)local_30;
              iVar10 = iVar10 + (int)local_34;
              iVar13 = iVar13 + local_4c;
            }
          }
        }
      }
      else {
        for (local_58 = 0; local_58 < iVar12; local_58 = local_58 + 1) {
          for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
            uVar9 = (uint)*(byte *)(iVar10 + iVar14);
            uVar7 = local_3c;
            if (iVar13 != 0) {
              uVar7 = (uint)((int)(short)(ushort)*(byte *)(iVar13 + iVar14) * (int)(short)local_3c)
                      >> 8;
            }
            FUN_000249da(iVar16,iVar14 + iVar15,uVar9 << 0x10 | uVar9 << 8 | uVar9 | uVar7 << 0x18,
                         *(undefined1 *)((int)param_1 + 0x22));
          }
          if (iVar13 != 0) {
            iVar13 = iVar13 + local_4c;
          }
          iVar16 = iVar16 + (int)local_30;
          iVar10 = iVar10 + (int)local_34;
        }
      }
      return;
    }
    if (bVar1 == 7) {
      iVar11 = param_1[1];
      iVar12 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      local_70 = *param_1;
      local_2c = (undefined4 *)param_1[3];
      local_4c = param_1[6];
      local_30 = (undefined4 *)param_1[7];
      iVar10 = param_1[4];
      local_50 = param_1[5];
      iVar13 = param_1[9] % 8;
      uVar2 = (ushort)bVar1;
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar10 == 0) {
          iVar10 = 0;
          if (bVar1 < 0xfd) {
            for (; iVar10 < iVar12; iVar10 = iVar10 + 1) {
              iVar16 = 0;
              for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
                sVar6 = FUN_00036ec0(local_4c,iVar15);
                sVar5 = FUN_00036ec0(local_70);
                if (((int)sVar5 * (int)(short)(0xff - (ushort)bVar1) +
                     (int)sVar6 * (int)(short)uVar2 & 0xffU) < 0x80) {
                  FUN_00027368(local_70,iVar16 + iVar13);
                }
                else {
                  FUN_0005e778();
                }
                iVar16 = iVar16 + 1;
              }
              local_70 = local_70 + (int)local_2c;
              local_4c = (int)local_30 + local_4c;
            }
          }
          else {
            for (; iVar10 < iVar12; iVar10 = iVar10 + 1) {
              iVar16 = 0;
              for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
                iVar14 = FUN_00036ec0(local_4c,iVar15);
                if (iVar14 == 0) {
                  FUN_00027368(local_70,iVar16 + iVar13);
                }
                else {
                  FUN_0005e778();
                }
                iVar16 = iVar16 + 1;
              }
              local_70 = local_70 + (int)local_2c;
              local_4c = local_4c + (int)local_30;
            }
          }
        }
        else {
          iVar15 = 0;
          if (bVar1 < 0xfd) {
            for (; iVar15 < iVar12; iVar15 = iVar15 + 1) {
              iVar14 = 0;
              for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
                bVar1 = *(byte *)(iVar10 + iVar16);
                if (bVar1 != 0) {
                  local_44 = FUN_00036ec0(local_4c,iVar16);
                  local_48 = iVar14 + iVar13;
                  iVar18 = FUN_00036ec0(local_70);
                  uVar7 = (uint)((int)(short)(ushort)bVar1 * (int)(short)uVar2) >> 8;
                  if ((iVar18 * (0xff - uVar7) + uVar7 * local_44 & 0xff) < 0x80) {
                    FUN_00027368(local_70,local_48);
                  }
                  else {
                    FUN_0005e778();
                  }
                }
                iVar14 = iVar14 + 1;
              }
              local_70 = (int)local_2c + local_70;
              local_4c = local_4c + (int)local_30;
              iVar10 = iVar10 + local_50;
            }
          }
          else {
            for (; iVar15 < iVar12; iVar15 = iVar15 + 1) {
              iVar14 = 0;
              for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
                bVar1 = *(byte *)(iVar10 + iVar16);
                local_48 = FUN_00036ec0(local_4c,iVar16);
                local_58 = iVar14 + iVar13;
                sVar6 = FUN_00036ec0(local_70);
                if (((int)sVar6 * (int)(short)(0xff - (ushort)bVar1) +
                     (int)(short)local_48 * (int)(short)(ushort)bVar1 & 0xffU) < 0x80) {
                  FUN_00027368(local_70,local_58);
                }
                else {
                  FUN_0005e778();
                }
                iVar14 = iVar14 + 1;
              }
              local_70 = local_70 + (int)local_2c;
              local_4c = local_4c + (int)local_30;
              iVar10 = iVar10 + local_50;
            }
          }
        }
      }
      else {
        for (local_38 = 0; local_38 < iVar12; local_38 = local_38 + 1) {
          iVar16 = 0;
          for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
            iVar14 = FUN_00036ec0(local_4c,iVar15);
            uVar7 = iVar14 * 0xff;
            if (iVar10 == 0) {
              uVar9 = (uint)bVar1;
            }
            else {
              uVar9 = (uint)((int)(short)(ushort)*(byte *)(iVar10 + iVar16) * (int)(short)uVar2) >>
                      8;
            }
            FUN_000249da(local_70,iVar16 + iVar13,
                         (uVar7 & 0xff) << 0x10 | (uVar7 & 0xff) << 8 | uVar7 & 0xff | uVar9 << 0x18
                         ,*(undefined1 *)((int)param_1 + 0x22));
            iVar16 = iVar16 + 1;
          }
          if (iVar10 != 0) {
            iVar10 = iVar10 + local_50;
          }
          local_70 = local_70 + (int)local_2c;
          local_4c = local_4c + (int)local_30;
        }
      }
      return;
    }
    if (bVar1 != 0xf) {
      return;
    }
    iVar10 = 3;
  }
  else {
    if (bVar1 != 0x11) {
      if (bVar1 == 0x12) {
        iVar11 = param_1[1];
        iVar12 = param_1[2];
        local_3c = (uint)*(byte *)((int)param_1 + 0x21);
        iVar16 = *param_1;
        local_30 = (undefined4 *)param_1[3];
        iVar10 = param_1[6];
        local_34 = (undefined4 *)param_1[7];
        iVar13 = param_1[4];
        local_4c = param_1[5];
        iVar15 = param_1[9] % 8;
        if (*(char *)((int)param_1 + 0x22) == '\0') {
          if (iVar13 == 0) {
            iVar13 = 0;
            if (local_3c < 0xfd) {
              for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
                iVar18 = 0;
                for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                  local_4c = FUN_0003fe7c(*(undefined2 *)(iVar10 + iVar14 * 2));
                  cVar4 = FUN_00036ec0(iVar16);
                  local_5c = CONCAT31(local_5c._1_3_,-cVar4);
                  FUN_00040264(local_4c,&local_5c,local_3c);
                  if ((byte)local_5c < 0x80) {
                    FUN_00027368(iVar16,iVar18 + iVar15);
                  }
                  else {
                    FUN_0005e778();
                  }
                  iVar18 = iVar18 + 1;
                }
                iVar10 = iVar10 + (int)local_34;
                iVar16 = iVar16 + (int)local_30;
              }
            }
            else {
              for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
                iVar18 = 0;
                for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                  uVar7 = FUN_0003fe7c(*(undefined2 *)(iVar10 + iVar14 * 2));
                  if (uVar7 < 0x80) {
                    FUN_00027368(iVar16,iVar18 + iVar15);
                  }
                  else {
                    FUN_0005e778();
                  }
                  iVar18 = iVar18 + 1;
                }
                iVar16 = iVar16 + (int)local_30;
                iVar10 = iVar10 + (int)local_34;
              }
            }
          }
          else {
            local_58 = 0;
            if (local_3c < 0xfd) {
              for (; local_58 < iVar12; local_58 = local_58 + 1) {
                iVar18 = 0;
                local_68 = 0;
                for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                  local_5c = CONCAT22(local_5c._2_2_,*(undefined2 *)(iVar10 + local_68 * 2));
                  local_2c = (undefined4 *)FUN_0003fe7c(local_5c);
                  local_48 = iVar14 + iVar15;
                  cVar4 = FUN_00036ec0(iVar16);
                  local_40 = CONCAT31(local_40._1_3_,-cVar4);
                  FUN_00040264(local_2c,&local_40,
                               (uint)((int)(short)(ushort)*(byte *)(iVar13 + iVar18) *
                                     (int)(short)local_3c) >> 8);
                  if ((byte)local_40 < 0x80) {
                    FUN_00027368(iVar16,local_48);
                  }
                  else {
                    FUN_0005e778();
                  }
                  iVar18 = iVar18 + 1;
                  local_68 = local_68 + 1;
                }
                iVar16 = iVar16 + (int)local_30;
                iVar13 = iVar13 + local_4c;
                iVar10 = iVar10 + (int)local_34;
              }
            }
            else {
              for (; local_58 < iVar12; local_58 = local_58 + 1) {
                iVar18 = 0;
                local_68 = 0;
                for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                  local_3c = FUN_0003fe7c(*(undefined2 *)(iVar10 + local_68 * 2));
                  local_48 = iVar14 + iVar15;
                  cVar4 = FUN_00036ec0(iVar16);
                  local_40 = CONCAT31(local_40._1_3_,-cVar4);
                  FUN_00040264(local_3c,&local_40,*(undefined1 *)(iVar13 + iVar18));
                  if ((byte)local_40 < 0x80) {
                    FUN_00027368(iVar16,local_48);
                  }
                  else {
                    FUN_0005e778();
                  }
                  iVar18 = iVar18 + 1;
                  local_68 = local_68 + 1;
                }
                iVar16 = iVar16 + (int)local_30;
                iVar10 = iVar10 + (int)local_34;
                iVar13 = iVar13 + local_4c;
              }
            }
          }
        }
        else {
          for (local_58 = 0; local_58 < iVar12; local_58 = local_58 + 1) {
            iVar14 = 0;
            for (iVar18 = 0; iVar18 < iVar11; iVar18 = iVar18 + 1) {
              uVar2 = *(ushort *)(iVar10 + iVar18 * 2);
              uVar7 = local_3c;
              if (iVar13 != 0) {
                uVar7 = (uint)((int)(short)(ushort)*(byte *)(iVar13 + iVar18) * (int)(short)local_3c
                              ) >> 8;
              }
              FUN_000249da(iVar16,iVar14 + iVar15,
                           ((uint)((short)(uVar2 >> 0xb) * 0x83a) >> 8 & 0xff) << 0x10 |
                           ((uint)((short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) * 0x40d) >> 8 &
                           0xff) << 8 | (uint)((short)(uVar2 & 0x1f) * 0x83a) >> 8 & 0xff |
                           uVar7 << 0x18,*(undefined1 *)((int)param_1 + 0x22));
              iVar14 = iVar14 + 1;
            }
            if (iVar13 != 0) {
              iVar13 = iVar13 + local_4c;
            }
            iVar10 = iVar10 + (int)local_34;
            iVar16 = iVar16 + (int)local_30;
          }
        }
        return;
      }
      if (bVar1 != 0x15) {
        return;
      }
      iVar11 = param_1[1];
      iVar12 = param_1[2];
      bVar1 = *(byte *)((int)param_1 + 0x21);
      uVar7 = (uint)bVar1;
      local_40 = *param_1;
      local_38 = param_1[3];
      iVar10 = param_1[6];
      local_34 = (undefined4 *)param_1[7];
      iVar13 = param_1[4];
      local_30 = (undefined4 *)param_1[5];
      iVar15 = param_1[9] % 8;
      if (*(char *)((int)param_1 + 0x22) == '\0') {
        if (iVar13 == 0) {
          iVar13 = 0;
          if (uVar7 < 0xfd) {
            for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
              iVar14 = 0;
              for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
                local_3c = iVar14 + iVar15;
                cVar4 = FUN_00036ec0(local_40);
                local_30 = (undefined4 *)CONCAT31(local_30._1_3_,-cVar4);
                FUN_00040264(*(undefined1 *)(iVar10 + iVar16 * 2),&local_30,
                             (uint)((int)(short)(ushort)*(byte *)(iVar10 + iVar16 * 2 + 1) *
                                   (int)(short)(ushort)bVar1) >> 8);
                if ((byte)local_30 < 0x80) {
                  FUN_00027368(local_40,local_3c);
                }
                else {
                  FUN_0005e778();
                }
                iVar14 = iVar14 + 1;
              }
              local_40 = local_38 + local_40;
              iVar10 = iVar10 + (int)local_34;
            }
          }
          else {
            for (; iVar13 < iVar12; iVar13 = iVar13 + 1) {
              iVar14 = 0;
              for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
                cVar4 = FUN_00036ec0(local_40);
                local_3c = CONCAT31(local_3c._1_3_,-cVar4);
                FUN_00040264(*(undefined1 *)(iVar10 + iVar16 * 2),&local_3c,
                             *(undefined1 *)(iVar10 + iVar16 * 2 + 1));
                if ((byte)local_3c < 0x80) {
                  FUN_00027368(local_40,iVar14 + iVar15);
                }
                else {
                  FUN_0005e778();
                }
                iVar14 = iVar14 + 1;
              }
              local_40 = local_40 + local_38;
              iVar10 = iVar10 + (int)local_34;
            }
          }
        }
        else {
          iVar16 = 0;
          if (uVar7 < 0xfd) {
            while (iVar16 < iVar12) {
              iVar18 = 0;
              local_28 = iVar16;
              for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                local_3c = iVar18 + iVar15;
                cVar4 = FUN_00036ec0(local_40);
                local_2c = (undefined4 *)CONCAT31(local_2c._1_3_,-cVar4);
                FUN_00040264(*(undefined1 *)(iVar10 + iVar14 * 2),&local_2c,
                             (int)(short)(ushort)*(byte *)(iVar10 + iVar14 * 2 + 1) *
                             (int)(short)(ushort)*(byte *)(iVar13 + iVar14) * uVar7 >> 0x10);
                if ((byte)local_2c < 0x80) {
                  FUN_00027368(local_40,local_3c);
                }
                else {
                  FUN_0005e778();
                }
                iVar18 = iVar18 + 1;
              }
              local_40 = local_40 + local_38;
              iVar10 = iVar10 + (int)local_34;
              iVar13 = iVar13 + (int)local_30;
              iVar16 = local_28 + 1;
            }
          }
          else {
            for (; iVar16 < iVar12; iVar16 = iVar16 + 1) {
              iVar18 = 0;
              for (iVar14 = 0; iVar14 < iVar11; iVar14 = iVar14 + 1) {
                local_3c = iVar18 + iVar15;
                cVar4 = FUN_00036ec0(local_40);
                local_2c = (undefined4 *)CONCAT31(local_2c._1_3_,-cVar4);
                FUN_00040264(*(undefined1 *)(iVar10 + iVar14 * 2),&local_2c,
                             (uint)((int)(short)(ushort)*(byte *)(iVar10 + iVar14 * 2 + 1) *
                                   (int)(short)(ushort)*(byte *)(iVar13 + iVar14)) >> 8);
                if ((byte)local_2c < 0x80) {
                  FUN_00027368(local_40,local_3c);
                }
                else {
                  FUN_0005e778();
                }
                iVar18 = iVar18 + 1;
              }
              local_40 = local_40 + local_38;
              iVar10 = iVar10 + (int)local_34;
              iVar13 = iVar13 + (int)local_30;
            }
          }
        }
      }
      else {
        for (local_28 = 0; (int)local_28 < iVar12; local_28 = local_28 + 1) {
          local_2c = (undefined4 *)0x0;
          for (iVar16 = 0; iVar16 < iVar11; iVar16 = iVar16 + 1) {
            uVar9 = (uint)*(byte *)(iVar10 + iVar16 * 2);
            iVar14 = iVar10 + iVar16 * 2;
            if (iVar13 == 0) {
              uVar8 = (uint)((int)(short)(ushort)*(byte *)(iVar14 + 1) * (int)(short)(ushort)bVar1)
                      >> 8;
            }
            else {
              uVar8 = (int)(short)(ushort)*(byte *)(iVar14 + 1) *
                      (int)(short)(ushort)*(byte *)(iVar13 + iVar16) * uVar7 >> 0x10;
            }
            local_3c = uVar9 << 0x10 | uVar9 << 8 | uVar9 | uVar8 << 0x18;
            FUN_000249da(local_40,(int)local_2c + iVar15,local_3c,
                         *(undefined1 *)((int)param_1 + 0x22));
            local_2c = (undefined4 *)((int)local_2c + 1);
          }
          if (iVar13 != 0) {
            iVar13 = iVar13 + (int)local_30;
          }
          local_40 = local_38 + local_40;
          iVar10 = iVar10 + (int)local_34;
        }
      }
      return;
    }
    iVar10 = 4;
  }
  iVar12 = param_1[1];
  iVar13 = param_1[2];
  local_34 = (undefined4 *)(uint)*(byte *)((int)param_1 + 0x21);
  local_70 = *param_1;
  local_38 = param_1[3];
  iVar11 = param_1[6];
  local_3c = param_1[7];
  iVar15 = param_1[4];
  local_44 = param_1[5];
  iVar16 = param_1[9] % 8;
  if (*(char *)((int)param_1 + 0x22) == '\0') {
    if (iVar15 == 0) {
      iVar15 = 0;
      if (local_34 < (undefined4 *)0xfd) {
        for (; iVar15 < iVar13; iVar15 = iVar15 + 1) {
          iVar18 = 0;
          for (iVar14 = 0; iVar14 < iVar12; iVar14 = iVar14 + 1) {
            local_44 = FUN_0003fef6(iVar11 + iVar18);
            cVar4 = FUN_00036ec0(local_70);
            local_48 = CONCAT31(local_48._1_3_,-cVar4);
            FUN_00040264(local_44,&local_48,local_34);
            if ((byte)local_48 < 0x80) {
              FUN_00027368(local_70,iVar14 + iVar16);
            }
            else {
              FUN_0005e778();
            }
            iVar18 = iVar18 + iVar10;
          }
          local_70 = local_70 + local_38;
          iVar11 = iVar11 + local_3c;
        }
      }
      else {
        for (; iVar15 < iVar13; iVar15 = iVar15 + 1) {
          iVar18 = 0;
          for (iVar14 = 0; iVar14 < iVar12; iVar14 = iVar14 + 1) {
            uVar7 = FUN_0003fef6(iVar11 + iVar18);
            if (uVar7 < 0x80) {
              FUN_00027368(local_70,iVar14 + iVar16);
            }
            else {
              FUN_0005e778();
            }
            iVar18 = iVar18 + iVar10;
          }
          local_70 = local_38 + local_70;
          iVar11 = iVar11 + local_3c;
        }
      }
    }
    else {
      local_5c = 0;
      if (local_34 < (undefined4 *)0xfd) {
        for (; local_5c < iVar13; local_5c = local_5c + 1) {
          iVar18 = 0;
          local_58 = 0;
          for (iVar14 = 0; iVar14 < iVar12; iVar14 = iVar14 + 1) {
            local_2c = (undefined4 *)FUN_0003fef6(local_58 + iVar11);
            local_40 = iVar14 + iVar16;
            cVar4 = FUN_00036ec0(local_70);
            local_30 = (undefined4 *)CONCAT31(local_30._1_3_,-cVar4);
            FUN_00040264(local_2c,&local_30,
                         (uint)((int)(short)(ushort)*(byte *)(iVar15 + iVar18) *
                               (int)(short)local_34) >> 8);
            if ((byte)local_30 < 0x80) {
              FUN_00027368(local_70,local_40);
            }
            else {
              FUN_0005e778();
            }
            iVar18 = iVar18 + 1;
            local_58 = local_58 + iVar10;
          }
          local_70 = local_70 + local_38;
          iVar11 = iVar11 + local_3c;
          iVar15 = iVar15 + local_44;
        }
      }
      else {
        for (; local_5c < iVar13; local_5c = local_5c + 1) {
          iVar18 = 0;
          local_58 = 0;
          for (iVar14 = 0; iVar14 < iVar12; iVar14 = iVar14 + 1) {
            local_30 = (undefined4 *)FUN_0003fef6(local_58 + iVar11);
            local_40 = iVar14 + iVar16;
            cVar4 = FUN_00036ec0(local_70);
            local_34 = (undefined4 *)CONCAT31(local_34._1_3_,-cVar4);
            FUN_00040264(local_30,&local_34,*(undefined1 *)(iVar15 + iVar18));
            if ((byte)local_34 < 0x80) {
              FUN_00027368(local_70,local_40);
            }
            else {
              FUN_0005e778();
            }
            iVar18 = iVar18 + 1;
            local_58 = local_58 + iVar10;
          }
          local_70 = local_38 + local_70;
          iVar11 = iVar11 + local_3c;
          iVar15 = iVar15 + local_44;
        }
      }
    }
  }
  return;
}

