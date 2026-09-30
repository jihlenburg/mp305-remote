/* Address: 00052de0; name: FUN_00052de0; body bytes: 1234 */

uint FUN_00052de0(code *param_1,int param_2,uint param_3,byte *param_4,uint *param_5)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined8 *puVar6;
  uint *puVar7;
  char *pcVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  char *pcVar16;
  uint uVar17;
  bool bVar18;
  bool bVar19;
  byte *local_28;
  
  uVar12 = 0;
  local_28 = param_4;
  if (param_2 == 0) {
    param_1 = (code *)0x20dd5;
  }
LAB_00053132:
  uVar5 = (uint)*local_28;
  if (uVar5 == 0) {
    uVar5 = uVar12;
    if (param_3 <= uVar12) {
      uVar5 = param_3 - 1;
    }
    (*param_1)(0,param_2,uVar5,param_3);
    return uVar12;
  }
  if (uVar5 == 0x25) {
    uVar5 = 0;
    while( true ) {
      while( true ) {
        while( true ) {
          while( true ) {
            local_28 = local_28 + 1;
            bVar1 = *local_28;
            if (bVar1 != 0x2b) break;
            uVar5 = uVar5 | 4;
          }
          if (0x2b < bVar1) break;
          if (bVar1 == 0x20) {
            uVar5 = uVar5 | 8;
          }
          else {
            if (bVar1 != 0x23) goto LAB_00052e28;
            uVar5 = uVar5 | 0x10;
          }
        }
        if (bVar1 != 0x2d) break;
        uVar5 = uVar5 | 2;
      }
      if (bVar1 != 0x30) break;
      uVar5 = uVar5 | 1;
    }
LAB_00052e28:
    uVar14 = 0;
    iVar3 = FUN_00020bcc(bVar1);
    if (iVar3 == 0) {
      if (*local_28 == 0x2a) {
        uVar14 = *param_5;
        param_5 = param_5 + 1;
        if ((int)uVar14 < 0) {
          uVar5 = uVar5 | 2;
          uVar14 = -uVar14;
        }
        local_28 = local_28 + 1;
      }
    }
    else {
      uVar14 = FUN_000202e8(&local_28);
    }
    uVar17 = 0;
    if (*local_28 == 0x2e) {
      local_28 = local_28 + 1;
      uVar5 = uVar5 | 0x400;
      iVar3 = FUN_00020bcc(*local_28);
      if (iVar3 == 0) {
        if (*local_28 == 0x2a) {
          uVar17 = *param_5;
          param_5 = param_5 + 1;
          if ((int)uVar17 < 1) {
            uVar17 = 0;
          }
          local_28 = local_28 + 1;
        }
      }
      else {
        uVar17 = FUN_000202e8(&local_28);
      }
    }
    bVar1 = *local_28;
    if (bVar1 == 0x6c) {
      local_28 = local_28 + 1;
      uVar9 = uVar5 | 0x100;
      uVar5 = uVar9;
      if (*local_28 != 0x6c) goto LAB_00052f02;
LAB_00052f26:
      uVar9 = uVar5 | 0x200;
    }
    else {
      uVar9 = uVar5;
      if (bVar1 < 0x6d) {
        if (bVar1 != 0x68) {
          if (bVar1 != 0x6a) goto LAB_00052f02;
          goto LAB_00052f26;
        }
        local_28 = local_28 + 1;
        uVar9 = uVar5 | 0x80;
        if (*local_28 != 0x68) goto LAB_00052f02;
        uVar9 = uVar5 | 0xc0;
      }
      else {
        if ((bVar1 != 0x74) && (bVar1 != 0x7a)) goto LAB_00052f02;
        uVar9 = uVar5 | 0x100;
      }
    }
    local_28 = local_28 + 1;
LAB_00052f02:
    uVar5 = (uint)*local_28;
    bVar19 = SBORROW4(uVar5,0x65);
    iVar3 = uVar5 - 0x65;
    bVar18 = uVar5 == 0x65;
LAB_00052f08:
    if (!bVar18) {
      if (iVar3 < 0 == bVar19) {
        if (uVar5 == 0x70) goto LAB_00052f68;
        if (uVar5 < 0x71) {
          if (uVar5 == 0x66) goto LAB_00053144;
          if (uVar5 == 0x67) goto LAB_00053170;
          if ((uVar5 == 0x69) || (bVar18 = false, uVar5 == 0x6f)) goto LAB_00052f68;
        }
        else {
          if (uVar5 == 0x73) {
            puVar7 = param_5 + 1;
            pcVar16 = (char *)*param_5;
            pcVar8 = pcVar16;
            uVar5 = uVar17;
            if (uVar17 == 0) {
              uVar5 = 0xffffffff;
            }
            while ((*pcVar8 != '\0' && (uVar5 != 0))) {
              pcVar8 = pcVar8 + 1;
              uVar5 = uVar5 - 1;
            }
            uVar5 = (int)pcVar8 - (int)pcVar16;
            if (((int)(uVar9 << 0x15) < 0) && (uVar17 <= uVar5)) {
              uVar5 = uVar17;
            }
            uVar13 = uVar12;
            uVar15 = uVar5;
            if (-1 < (int)(uVar9 << 0x1e)) {
              while (uVar5 = uVar15 + 1, uVar13 = uVar12, uVar15 < uVar14) {
                (*param_1)(0x20,param_2,uVar12,param_3);
                uVar12 = uVar12 + 1;
                uVar15 = uVar5;
              }
            }
            while ((cVar2 = *pcVar16, cVar2 != '\0' &&
                   ((-1 < (int)(uVar9 << 0x15) ||
                    (bVar18 = uVar17 != 0, uVar17 = uVar17 - 1, bVar18))))) {
              pcVar16 = pcVar16 + 1;
              (*param_1)(cVar2,param_2,uVar13,param_3);
              uVar13 = uVar13 + 1;
            }
            param_5 = puVar7;
            if ((int)(uVar9 << 0x1e) < 0) {
              while (uVar5 < uVar14) {
                (*param_1)(0x20,param_2,uVar13,param_3);
                uVar13 = uVar13 + 1;
                uVar5 = uVar5 + 1;
              }
            }
            goto LAB_0005312c;
          }
          if ((uVar5 == 0x75) || (bVar18 = false, uVar5 == 0x78)) goto LAB_00052f68;
        }
        goto LAB_00052f20;
      }
      if (uVar5 != 0x50) {
        if (uVar5 < 0x51) {
          if (uVar5 != 0x25) goto code_r0x00052f16;
          uVar5 = 0x25;
          goto LAB_000532a0;
        }
        if ((uVar5 != 0x58) && (uVar5 != 0x62)) {
          if (uVar5 == 99) {
            uVar5 = 1;
            uVar17 = uVar5;
            if (-1 < (int)(uVar9 << 0x1e)) {
              while (uVar5 = uVar17 + 1, uVar17 < uVar14) {
                (*param_1)(0x20,param_2,uVar12,param_3);
                uVar12 = uVar12 + 1;
                uVar17 = uVar5;
              }
            }
            uVar13 = uVar12 + 1;
            puVar7 = param_5 + 1;
            (*param_1)((byte)*param_5,param_2,uVar12,param_3);
            param_5 = puVar7;
            if ((int)(uVar9 << 0x1e) < 0) {
              while (uVar5 < uVar14) {
                (*param_1)(0x20,param_2,uVar13,param_3);
                uVar13 = uVar13 + 1;
                uVar5 = uVar5 + 1;
              }
            }
            goto LAB_0005312c;
          }
          bVar18 = false;
          if (uVar5 == 100) goto LAB_00052f68;
          goto LAB_00052f20;
        }
      }
LAB_00052f68:
      if ((uVar5 == 0x78) || (uVar5 == 0x58)) {
LAB_00052f9c:
        if (*local_28 == 0x58) {
LAB_00052fb2:
          uVar10 = 0x10;
          uVar9 = uVar9 | 0x20;
        }
        else {
LAB_00052fa2:
          uVar10 = 0x10;
          if (*local_28 == 0x50) goto LAB_00052fb2;
        }
LAB_00052fb8:
        if ((*local_28 != 0x69) && (*local_28 != 100)) goto LAB_00052fc2;
      }
      else {
        if ((uVar5 == 0x70) || (uVar5 == 0x50)) {
          uVar9 = uVar9 | 0x110;
          if (local_28[1] == 0x56) {
            local_28 = local_28 + 1;
            goto LAB_00052f9c;
          }
          goto LAB_00052fa2;
        }
        if (uVar5 == 0x6f) {
          uVar10 = 8;
        }
        else {
          if (uVar5 != 0x62) {
            uVar10 = 10;
            uVar9 = uVar9 & 0xffffffef;
            goto LAB_00052fb8;
          }
          uVar10 = 2;
        }
LAB_00052fc2:
        uVar9 = uVar9 & 0xfffffff3;
      }
      if ((int)(uVar9 << 0x15) < 0) {
        uVar9 = uVar9 & 0xfffffffe;
      }
      bVar1 = *local_28;
      if ((bVar1 == 0x69) || (bVar1 == 100)) {
        if ((int)(uVar9 << 0x16) < 0) {
          piVar4 = (int *)((uint)((int)param_5 + 7) & 0xfffffff8);
          iVar3 = *piVar4;
          iVar11 = piVar4[1];
          bVar18 = iVar11 < 0;
          if ((int)(-(uint)(iVar3 != 0) - iVar11) < 0 ==
              (SBORROW4(0,iVar11) != SBORROW4(-iVar11,(uint)(iVar3 != 0)))) {
            bVar19 = iVar3 != 0;
            iVar3 = -iVar3;
            iVar11 = -(uint)bVar19 - iVar11;
          }
LAB_0005300a:
          param_5 = (uint *)(piVar4 + 2);
          uVar13 = FUN_00020d4c(param_1,param_2,uVar12,param_3,iVar3,iVar11,bVar18);
          goto LAB_0005312c;
        }
        if ((int)(uVar9 << 0x17) < 0) {
LAB_0005306c:
          uVar5 = *param_5;
        }
        else if ((int)(uVar9 << 0x19) < 0) {
          uVar5 = (uint)(byte)*param_5;
        }
        else {
          if (-1 < (int)(uVar9 << 0x18)) goto LAB_0005306c;
          uVar5 = (uint)(short)(ushort)*param_5;
        }
        uVar13 = uVar5 >> 0x1f;
        if ((int)uVar5 < 1) {
          uVar5 = -uVar5;
        }
      }
      else {
        if (bVar1 == 0x56) {
          iVar3 = FUN_00052de0(param_1,param_2 + uVar12,param_3 - uVar12,*(undefined4 *)*param_5,
                               *(undefined4 *)((undefined4 *)*param_5)[1]);
          uVar13 = uVar12 + iVar3;
          param_5 = param_5 + 1;
          goto LAB_0005312c;
        }
        if ((int)(uVar9 << 0x16) < 0) {
          bVar18 = false;
          piVar4 = (int *)((uint)((int)param_5 + 7) & 0xfffffff8);
          iVar3 = *piVar4;
          iVar11 = piVar4[1];
          goto LAB_0005300a;
        }
        if ((int)(uVar9 << 0x17) < 0) {
          uVar5 = *param_5;
          uVar13 = 0;
        }
        else {
          if ((int)(uVar9 << 0x19) < 0) {
            uVar5 = (uint)(byte)*param_5;
          }
          else if ((int)(uVar9 << 0x18) < 0) {
            uVar5 = (uint)(ushort)*param_5;
          }
          else {
            uVar5 = *param_5;
          }
          uVar13 = 0;
        }
      }
      param_5 = param_5 + 1;
      uVar13 = FUN_00020ccc(param_1,param_2,uVar12,param_3,uVar5,uVar13,uVar10,uVar17,uVar14,uVar9);
      goto LAB_0005312c;
    }
    goto LAB_00053170;
  }
  goto LAB_000532a0;
code_r0x00052f16:
  bVar19 = SBORROW4(uVar5,0x45);
  iVar3 = uVar5 - 0x45;
  bVar18 = uVar5 == 0x45;
  if (!bVar18) goto code_r0x00052f1a;
  goto LAB_00052f08;
code_r0x00052f1a:
  if (uVar5 == 0x46) {
LAB_00053144:
    if (uVar5 == 0x46) {
      uVar9 = uVar9 | 0x20;
    }
    puVar6 = (undefined8 *)((uint)((int)param_5 + 7) & 0xfffffff8);
    param_5 = (uint *)(puVar6 + 1);
    uVar13 = FUN_000208e0((int)*puVar6,param_1,param_2,uVar12,param_3,uVar17,uVar14,uVar9);
  }
  else {
    bVar18 = uVar5 == 0x47;
LAB_00052f20:
    if (bVar18) {
LAB_00053170:
      if ((uVar5 == 0x67) || (uVar5 == 0x47)) {
        uVar9 = uVar9 | 0x800;
      }
      if ((uVar5 == 0x45) || (uVar5 == 0x47)) {
        uVar9 = uVar9 | 0x20;
      }
      puVar6 = (undefined8 *)((uint)((int)param_5 + 7) & 0xfffffff8);
      param_5 = (uint *)(puVar6 + 1);
      uVar13 = FUN_00020368((int)*puVar6,param_1,param_2,uVar12,param_3,uVar17,uVar14,uVar9);
    }
    else {
LAB_000532a0:
      uVar13 = uVar12 + 1;
      (*param_1)(uVar5,param_2,uVar12,param_3);
    }
  }
LAB_0005312c:
  local_28 = local_28 + 1;
  uVar12 = uVar13;
  goto LAB_00053132;
}

