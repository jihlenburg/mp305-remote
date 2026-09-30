/* Address: 00020e44; name: FUN_00020e44; body bytes: 1656 */

int FUN_00020e44(byte *param_1,uint *param_2,undefined4 param_3,code *param_4)

{
  byte bVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  char extraout_r1;
  int *piVar8;
  int iVar9;
  uint uVar10;
  undefined1 uVar11;
  uint *puVar12;
  int extraout_r2;
  undefined4 uVar13;
  uint uVar14;
  int iVar15;
  byte *pbVar16;
  byte *pbVar17;
  uint *puVar18;
  byte *unaff_r9;
  byte **unaff_r11;
  char **ppcVar19;
  bool bVar20;
  bool bVar21;
  bool bVar22;
  longlong lVar23;
  byte *local_88;
  undefined4 local_84;
  char **local_80;
  uint local_7c;
  undefined1 auStack_78 [32];
  char *local_58;
  char **local_54;
  byte *pbStack_50;
  int local_4c;
  char *local_48;
  byte local_3f [2];
  undefined1 local_3d [9];
  byte *pbStack_34;
  uint *puStack_30;
  undefined4 local_2c;
  code *pcStack_28;
  
  pcStack_28 = param_4;
  local_2c = param_3;
  puStack_30 = param_2;
  pbStack_34 = param_1;
  iVar15 = 0;
LAB_00021232:
  uVar5 = (uint)*param_1;
  if (uVar5 == 0) {
    return iVar15;
  }
  if (uVar5 == 0x25) {
    uVar14 = 0;
    pbVar17 = (byte *)0x0;
    local_7c = 0;
    while( true ) {
      pbVar16 = param_1 + 1;
      uVar5 = 1 << (*pbVar16 - 0x20 & 0xff);
      if ((uVar5 & 0x12809) == 0) break;
      uVar14 = uVar14 | uVar5;
      param_1 = pbVar16;
    }
    if (*pbVar16 == 0x2a) {
      puVar12 = param_2 + 1;
      local_7c = *param_2;
      if ((int)local_7c < 0) {
        uVar14 = uVar14 | 0x2000;
        local_7c = -local_7c;
      }
      uVar14 = uVar14 | 2;
      pbVar16 = param_1 + 2;
    }
    else {
      for (; puVar12 = param_2, *pbVar16 - 0x30 < 10; pbVar16 = pbVar16 + 1) {
        uVar14 = uVar14 | 2;
        local_7c = (uint)*pbVar16 + local_7c * 10 + -0x30;
      }
    }
    param_1 = pbVar16;
    puVar18 = puVar12;
    if (*pbVar16 == 0x2e) {
      param_1 = pbVar16 + 1;
      uVar14 = uVar14 | 4;
      if (*param_1 == 0x2a) {
        puVar18 = puVar12 + 1;
        pbVar17 = (byte *)*puVar12;
        param_1 = pbVar16 + 2;
      }
      else {
        for (; *param_1 - 0x30 < 10; param_1 = param_1 + 1) {
          pbVar17 = (byte *)((uint)*param_1 + (int)pbVar17 * 10 + -0x30);
        }
      }
    }
    bVar1 = *param_1;
    if (bVar1 == 0x6c) {
      uVar14 = uVar14 | 0x100000;
LAB_00020f1a:
      if (param_1[1] == bVar1) {
        uVar14 = uVar14 + 0x100000;
        param_1 = param_1 + 1;
      }
    }
    else if (bVar1 < 0x6d) {
      if (bVar1 != 0x4c) {
        if (bVar1 == 0x68) {
          uVar14 = uVar14 | 0x300000;
          goto LAB_00020f1a;
        }
        if (bVar1 != 0x6a) goto LAB_00020f28;
        uVar14 = uVar14 | 0x200000;
      }
    }
    else if ((bVar1 != 0x74) && (bVar1 != 0x7a)) goto LAB_00020f28;
    param_1 = param_1 + 1;
LAB_00020f28:
    uVar5 = (uint)*param_1;
    bVar22 = SBORROW4(uVar5,0x66);
    bVar20 = (int)(uVar5 - 0x66) < 0;
    bVar21 = uVar5 == 0x66;
LAB_00020f2c:
    while (!bVar21) {
      param_2 = puVar18;
      if (bVar20 == bVar22) {
        if (uVar5 == 0x70) {
          uVar14 = uVar14 | 4;
          pbVar17 = &NMI;
          local_88 = (byte *)0x10;
        }
        else if (uVar5 < 0x71) {
          if (uVar5 == 0x67) break;
          if (uVar5 == 0x69) goto LAB_00021046;
          if (uVar5 == 0x6e) {
            uVar5 = (uVar14 & 0x7fffff) >> 0x14;
            if (uVar5 == 2) {
              piVar8 = (int *)*puVar18;
              *piVar8 = iVar15;
              piVar8[1] = iVar15 >> 0x1f;
            }
            else if (uVar5 == 3) {
              *(short *)*puVar18 = (short)iVar15;
            }
            else if (uVar5 == 4) {
              *(char *)*puVar18 = (char)iVar15;
            }
            else {
              *(int *)*puVar18 = iVar15;
            }
            param_2 = puVar18 + 1;
            goto LAB_00021230;
          }
          if (uVar5 != 0x6f) goto LAB_00020f7c;
          local_88 = (byte *)0x8;
        }
        else {
          if (uVar5 == 0x73) {
            unaff_r11 = (byte **)*puVar18;
            iVar7 = -1;
            goto LAB_00020fd6;
          }
          if (uVar5 != 0x75) {
            if (uVar5 == 0x78) goto LAB_000210b0;
            goto LAB_00020f7c;
          }
          local_88 = (byte *)0xa;
        }
LAB_000210d2:
        uVar5 = (uVar14 & 0x7fffff) >> 0x14;
        if (uVar5 == 2) {
          puVar12 = (uint *)((uint)((int)puVar18 + 7) & 0xfffffff8);
          param_2 = puVar12 + 2;
          uVar4 = *puVar12;
          uVar10 = puVar12[1];
        }
        else {
          param_2 = puVar18 + 1;
          uVar4 = *puVar18;
          uVar10 = 0;
          if (uVar5 == 3) {
            uVar4 = uVar4 & 0xffff;
          }
          if (uVar5 == 4) {
            uVar4 = uVar4 & 0xff;
          }
        }
        unaff_r9 = (byte *)0x0;
        if ((int)(uVar14 << 0x1c) < 0) {
          if (*param_1 == 0x70) {
            local_84 = (byte *)CONCAT31(local_84._1_3_,0x40);
            unaff_r9 = (byte *)0x1;
          }
          else if ((local_88 == (byte *)0x10) && (uVar4 != 0 || uVar10 != 0)) {
            local_84._0_2_ = CONCAT11(*param_1,0x30);
            unaff_r9 = (byte *)0x2;
          }
          if ((local_88 == (byte *)0x8) &&
             ((uVar4 != 0 || uVar10 != 0 || ((int)(uVar14 << 0x1d) < 0)))) {
            local_84 = (byte *)CONCAT31(local_84._1_3_,0x30);
            unaff_r9 = (byte *)0x1;
            pbVar17 = pbVar17 + -1;
          }
        }
LAB_0002115c:
        lVar23 = CONCAT44(uVar10,uVar4);
        if (*param_1 == 0x58) {
          local_58 = "0123456789ABCDEF";
        }
        else {
          local_58 = "0123456789abcdef";
        }
        local_80 = &local_58;
        while( true ) {
          if (lVar23 == 0) break;
          lVar23 = FUN_00010388((int)lVar23,(int)((ulonglong)lVar23 >> 0x20),local_88,0);
          local_80 = (char **)((int)local_80 + -1);
          *(char *)local_80 = local_58[extraout_r2];
        }
        ppcVar19 = (char **)((int)&local_58 - (int)local_80);
        if ((int)(uVar14 << 0x1d) < 0) {
          uVar14 = uVar14 & 0xfffeffff;
        }
        else {
          pbVar17 = (byte *)0x1;
        }
        if ((int)ppcVar19 < (int)pbVar17) {
          local_88 = pbVar17 + -(int)ppcVar19;
        }
        else {
          local_88 = (byte *)0x0;
        }
        local_7c = local_7c - (int)(local_88 + (int)ppcVar19 + (int)unaff_r9);
        if (-1 < (int)(uVar14 << 0xf)) {
          iVar7 = FUN_0002151c(local_7c,uVar14,local_2c,param_4);
          iVar15 = iVar15 + iVar7;
        }
        for (iVar7 = 0; iVar7 < (int)unaff_r9; iVar7 = iVar7 + 1) {
          (*param_4)(*(undefined1 *)((int)&local_84 + iVar7),local_2c);
          iVar15 = iVar15 + 1;
        }
        if ((int)(uVar14 << 0xf) < 0) {
          iVar7 = FUN_0002151c(local_7c,uVar14,local_2c,param_4);
          iVar15 = iVar15 + iVar7;
        }
        while (pbVar17 = local_88 + -1, bVar21 = 0 < (int)local_88, local_88 = pbVar17, bVar21) {
          (*param_4)(0x30,local_2c);
          iVar15 = iVar15 + 1;
        }
        while (unaff_r11 = (byte **)((int)ppcVar19 + -1), uVar5 = local_7c, 0 < (int)ppcVar19) {
          cVar3 = *(char *)local_80;
          local_80 = (char **)((int)local_80 + 1);
          (*param_4)(cVar3,local_2c);
          iVar15 = iVar15 + 1;
          ppcVar19 = (char **)unaff_r11;
        }
        goto LAB_0002122a;
      }
      if (uVar5 == 0x58) {
LAB_000210b0:
        local_88 = (byte *)0x10;
        goto LAB_000210d2;
      }
      if (0x58 < uVar5) {
        if (uVar5 == 99) {
          local_88._0_2_ = (ushort)(byte)*puVar18;
          iVar7 = 1;
          unaff_r11 = &local_88;
LAB_00020fd6:
          param_2 = puVar18 + 1;
          iVar9 = 0;
          if ((int)(uVar14 << 0x1d) < 0) {
            for (; (iVar9 < (int)pbVar17 &&
                   ((iVar9 < iVar7 || (*(char *)((int)unaff_r11 + iVar9) != '\0'))));
                iVar9 = iVar9 + 1) {
            }
          }
          else {
            for (; (iVar9 < iVar7 || (*(char *)((int)unaff_r11 + iVar9) != '\0')); iVar9 = iVar9 + 1
                ) {
            }
          }
          uVar5 = local_7c - iVar9;
          iVar7 = FUN_0002151c(uVar5,uVar14,local_2c,param_4);
          iVar15 = iVar7 + iVar15 + iVar9;
          while (bVar21 = iVar9 != 0, iVar9 = iVar9 + -1, bVar21) {
            (*param_4)(*(char *)unaff_r11,local_2c);
            unaff_r11 = (byte **)((int)unaff_r11 + 1);
          }
          unaff_r9 = (byte *)0xffffffff;
          goto LAB_0002122a;
        }
        if (uVar5 == 100) {
LAB_00021046:
          uVar5 = (uVar14 & 0x7fffff) >> 0x14;
          local_88 = (byte *)0xa;
          if (uVar5 == 2) {
            puVar12 = (uint *)((uint)((int)puVar18 + 7) & 0xfffffff8);
            param_2 = puVar12 + 2;
            uVar4 = *puVar12;
            uVar10 = puVar12[1];
          }
          else {
            param_2 = puVar18 + 1;
            uVar4 = *puVar18;
            if (uVar5 == 3) {
              uVar4 = (uint)(short)uVar4;
            }
            uVar10 = (int)uVar4 >> 0x1f;
            if (uVar5 == 4) {
              uVar4 = (uint)(char)uVar4;
              uVar10 = (int)uVar4 >> 0x1f;
            }
          }
          if ((int)uVar10 < 0) {
            bVar21 = uVar4 != 0;
            uVar4 = -uVar4;
            uVar10 = -(uint)bVar21 - uVar10;
            uVar11 = 0x2d;
LAB_00021098:
            local_84 = (byte *)CONCAT31(local_84._1_3_,uVar11);
            unaff_r9 = (byte *)0x1;
          }
          else {
            if ((int)(uVar14 << 0x14) < 0) {
              uVar11 = 0x2b;
              goto LAB_00021098;
            }
            unaff_r9 = (byte *)0x0;
            if ((uVar14 & 1) != 0) {
              uVar11 = 0x20;
              goto LAB_00021098;
            }
          }
          goto LAB_0002115c;
        }
        if (uVar5 == 0x65) break;
        goto LAB_00020f7c;
      }
      if (uVar5 == 0) {
        return iVar15;
      }
      bVar22 = SBORROW4(uVar5,0x45);
      bVar20 = (int)(uVar5 - 0x45) < 0;
      bVar21 = uVar5 == 0x45;
      if (!bVar21) goto code_r0x00020f3e;
    }
    goto LAB_00021270;
  }
  goto LAB_00020f7c;
code_r0x00020f3e:
  bVar22 = SBORROW4(uVar5,0x46);
  bVar20 = (int)(uVar5 - 0x46) < 0;
  bVar21 = uVar5 == 0x46;
  if (!bVar21) goto code_r0x00020f42;
  goto LAB_00020f2c;
code_r0x00020f42:
  if (uVar5 != 0x47) {
LAB_00020f7c:
    (*param_4)(uVar5,local_2c);
    iVar15 = iVar15 + 1;
    goto LAB_00021230;
  }
LAB_00021270:
  if (-1 < (int)(uVar14 << 0x1d)) {
    pbVar17 = (byte *)0x6;
  }
  puVar6 = (undefined4 *)((uint)((int)puVar18 + 7) & 0xfffffff8);
  param_2 = puVar6 + 2;
  uVar13 = *puVar6;
  if ((puVar6[1] & 0x80000000) == 0) {
    if ((int)(uVar14 << 0x14) < 0) {
      local_3d._1_4_ = "+";
    }
    else if ((uVar14 & 1) == 0) {
      local_3d._1_4_ = "";
    }
    else {
      local_3d._1_4_ = " ";
    }
  }
  else {
    local_3d._1_4_ = "-";
  }
  bVar1 = *param_1;
  uVar5 = puVar6[1] & 0x7fffffff;
  if (bVar1 == 0x65) {
LAB_000212cc:
    if ((int)pbVar17 < 0x11) {
      local_88 = pbVar17 + 1;
    }
    else {
      local_88 = (byte *)0x11;
    }
    local_84 = (byte *)0x0;
    FUN_0002075c(&local_58,auStack_78,uVar13,uVar5);
    unaff_r9 = pbVar17 + 1;
    local_48 = local_58;
    local_88 = pbStack_50;
LAB_00021396:
    unaff_r11 = (byte **)0x0;
    local_84 = (byte *)0x1;
    local_88 = pbStack_50;
    local_80 = local_54;
    local_58 = local_48;
  }
  else if (bVar1 < 0x66) {
    if (bVar1 == 0x45) goto LAB_000212cc;
    if (bVar1 == 0x46) goto LAB_000212f8;
    if (bVar1 == 0x47) goto LAB_0002133a;
  }
  else if (bVar1 == 0x66) {
LAB_000212f8:
    local_84 = (byte *)0x1;
    local_80 = (char **)0x80000000;
    local_88 = pbVar17;
    FUN_0002075c(&local_58,auStack_78,uVar13,uVar5);
    unaff_r11 = (byte **)0x0;
    local_48 = local_58;
    local_88 = pbStack_50;
    unaff_r9 = pbStack_50;
    if (local_4c == 0) {
      unaff_r9 = (byte *)((int)local_54 + (int)(pbVar17 + 1));
    }
    if (-1 < (int)pbVar17 - (int)unaff_r9) {
      unaff_r11 = (byte **)(-1 - ((int)pbVar17 - (int)unaff_r9));
      unaff_r9 = pbVar17 + 1;
    }
    local_84 = unaff_r9 + -(int)pbVar17;
  }
  else {
    if (bVar1 != 0x67) goto LAB_000213c0;
LAB_0002133a:
    if ((int)pbVar17 < 1) {
      pbVar17 = (byte *)0x1;
    }
    local_88 = pbVar17;
    if (0x11 < (int)pbVar17) {
      local_88 = (byte *)0x11;
    }
    local_84 = (byte *)0x0;
    FUN_0002075c(&local_58,auStack_78,uVar13,uVar5);
    local_88 = pbStack_50;
    unaff_r11 = (byte **)0x0;
    local_48 = local_58;
    unaff_r9 = pbVar17;
    if (-1 < (int)(uVar14 << 0x1c)) {
      if ((int)pbStack_50 < (int)pbVar17) {
        unaff_r9 = pbStack_50;
      }
      for (; (1 < (int)unaff_r9 && (unaff_r9[(int)(local_58 + -1)] == 0x30));
          unaff_r9 = unaff_r9 + -1) {
      }
    }
    if (((int)pbVar17 <= (int)local_54) || ((int)local_54 < -4)) goto LAB_00021396;
    if ((int)local_54 < 1) {
      pbVar17 = unaff_r9 + -(int)local_54;
      unaff_r11 = (byte **)local_54;
LAB_000213b0:
      unaff_r9 = pbVar17;
    }
    else {
      pbVar17 = (byte *)((int)local_54 + 1);
      if ((int)unaff_r9 < (int)pbVar17) goto LAB_000213b0;
    }
    local_84 = (byte *)((int)local_54 + (1 - (int)unaff_r11));
    local_80 = (char **)0x80000000;
  }
LAB_000213c0:
  if ((-1 < (int)(uVar14 << 0x1c)) && ((int)unaff_r9 <= (int)local_84)) {
    local_84 = (byte *)0xffffffff;
  }
  local_3d[0] = 0;
  pbVar17 = local_3f + 2;
  if (local_80 != (char **)0x80000000) {
    local_58 = (char *)0x2;
    local_54 = (char **)0x2b;
    if ((int)local_80 < 0) {
      local_80 = (char **)-(int)local_80;
      local_54 = (char **)0x2d;
    }
    while ((pcVar2 = local_58, local_58 = local_58 + -1, 0 < (int)pcVar2 ||
           (local_80 != (char **)0x0))) {
      local_80 = (char **)FUN_00010b80(local_80,10);
      pbVar17 = pbVar17 + -1;
      *pbVar17 = extraout_r1 + 0x30;
    }
    pbVar17[-1] = (byte)local_54;
    pbVar17 = pbVar17 + -2;
    *pbVar17 = *param_1 & 0x20 | 0x45;
  }
  local_80 = (char **)(local_3f + (2 - (int)pbVar17));
  local_7c = (local_7c -
             (int)(unaff_r9 + ((int)local_84 >> 0x1f) + (uint)(*(char *)local_3d._1_4_ != '\0') +
                  (int)(local_3f + (2 - (int)pbVar17)))) - 1;
  if (-1 < (int)(uVar14 << 0xf)) {
    iVar7 = FUN_0002151c(local_7c,uVar14,local_2c,param_4);
    iVar15 = iVar15 + iVar7;
  }
  if (*(char *)local_3d._1_4_ != '\0') {
    (*param_4)(*(char *)local_3d._1_4_,local_2c);
    iVar15 = iVar15 + 1;
  }
  iVar7 = iVar15;
  pbVar16 = unaff_r9;
  if ((int)(uVar14 << 0xf) < 0) {
    iVar7 = FUN_0002151c(local_7c,uVar14,local_2c,param_4);
    iVar7 = iVar15 + iVar7;
  }
  while (iVar15 = iVar7, unaff_r9 = pbVar16 + -1, 0 < (int)pbVar16) {
    if (((int)unaff_r11 < 0) || ((int)local_88 <= (int)unaff_r11)) {
      cVar3 = '0';
    }
    else {
      cVar3 = local_48[(int)unaff_r11];
    }
    (*param_4)(cVar3,local_2c);
    unaff_r11 = (byte **)((int)unaff_r11 + 1);
    local_84 = local_84 + -1;
    iVar7 = iVar15 + 1;
    pbVar16 = unaff_r9;
    if (local_84 == (byte *)0x0) {
      (*param_4)(0x2e,local_2c);
      iVar7 = iVar15 + 2;
    }
  }
  while (ppcVar19 = local_80, local_80 = (char **)((int)local_80 + -1), uVar5 = local_7c,
        0 < (int)ppcVar19) {
    (*param_4)(*pbVar17,local_2c);
    iVar15 = iVar15 + 1;
    pbVar17 = pbVar17 + 1;
  }
LAB_0002122a:
  iVar7 = FUN_000214f8(uVar5,uVar14,local_2c,param_4);
  iVar15 = iVar15 + iVar7;
LAB_00021230:
  param_1 = param_1 + 1;
  goto LAB_00021232;
}

