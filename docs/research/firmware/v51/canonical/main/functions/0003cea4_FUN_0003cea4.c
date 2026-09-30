/* Address: 0003cea4; name: FUN_0003cea4; body bytes: 1426 */

/* Recovered from stored Thumb pointer at 0007a580; callback identification is inferred until
   reviewed. */

void FUN_0003cea4(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  bool bVar16;
  uint in_fpscr;
  uint uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44 [4];
  
  iVar3 = FUN_0004b9b2(&DAT_0007a574);
  if (iVar3 != 1) {
    return;
  }
  iVar3 = FUN_00046688(param_2);
  iVar4 = FUN_00046698(param_2);
  if (iVar3 != 2) {
    bVar16 = iVar3 == 8;
    do {
      if (bVar16) {
        *(uint *)(iVar4 + 0x4c) = *(uint *)(iVar4 + 0x4c) & 0xfffffffe;
        uVar7 = FUN_0004bbe2(iVar4);
        iVar3 = FUN_000472d4();
        FUN_00047eec();
        iVar4 = FUN_000482e0();
        if (iVar4 != 4) {
          return;
        }
        if (iVar3 == 0) {
          return;
        }
        FUN_0004743a(uVar7,0);
        return;
      }
      bVar16 = true;
    } while (iVar3 == 3);
    if (iVar3 == 0xe) {
      iVar3 = FUN_00046700(param_2);
      iVar12 = *(int *)(iVar4 + 0x40);
      if ((iVar3 == 0x13) || (iVar3 == 0x11)) {
        iVar3 = iVar12 + 1;
      }
      else {
        if ((iVar3 != 0x14) && (iVar3 != 0x12)) goto LAB_0003d252;
        iVar3 = iVar12 + -1;
      }
    }
    else {
      if (iVar3 != 0xf) {
        if (iVar3 == 0x13) {
          piVar14 = (int *)FUN_0004673a(param_2);
          FUN_000371f0(iVar4,&local_54,&local_4c);
          iVar3 = 0;
          if (*(int *)(iVar4 + 8) != 0) {
            iVar3 = *(int *)(*(int *)(iVar4 + 8) + 0x20);
          }
          iVar12 = FUN_0004c5ac(iVar4,0);
          local_4c = local_4c - (iVar12 + iVar3);
          FUN_0003ddf0(&local_48,local_54 - local_4c,local_50 - local_4c,local_54 + local_4c,
                       local_50 + local_4c);
          iVar9 = FUN_0003dcb8(&local_48,*piVar14,0x7fff);
          if (iVar9 == 0) {
            uVar7 = FUN_0003dfb4(((int *)*piVar14)[1] - local_50,*(int *)*piVar14 - local_54);
            fVar19 = (float)VectorUnsignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
            fVar22 = (float)VectorSignedToFloat(*(undefined4 *)(iVar4 + 0x2c),
                                                (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (fVar19 - fVar22) - *(float *)(iVar4 + 0x38);
            while (in_fpscr = in_fpscr & 0xfffffff | (uint)(0.0 <= fVar19) << 0x1d,
                  (byte)(in_fpscr >> 0x1d) == 0) {
              fVar19 = fVar19 + 360.0;
            }
            for (; 0x43b3ffff < (int)fVar19; fVar19 = fVar19 - 360.0) {
            }
            uVar8 = local_4c * 0x274;
            iVar9 = FUN_00040c08(0x32);
            uVar7 = VectorUnsignedToFloat
                              ((int)((ulonglong)(uint)(iVar9 * 0x168) / ((ulonglong)uVar8 / 100)),
                               (byte)(in_fpscr >> 0x16) & 3);
            iVar4 = FUN_0003cbf8(fVar19,uVar7,iVar4);
            if (iVar4 != 0) {
              FUN_0003db32(&local_48,iVar12 + iVar3 * 2);
              uVar2 = FUN_0003dcb8(&local_48,*piVar14,0x7fff);
              *(undefined1 *)(piVar14 + 1) = uVar2;
              return;
            }
          }
          *(undefined1 *)(piVar14 + 1) = 0;
          return;
        }
        if (iVar3 == 0x18) {
          iVar9 = FUN_0004c846(iVar4,0);
          iVar3 = FUN_0004c88e(iVar4,0);
          iVar10 = FUN_0004c8e2(iVar4,0);
          iVar11 = FUN_0004c7e6(iVar4,0);
          iVar12 = iVar3;
          if (iVar3 < iVar9) {
            iVar12 = iVar9;
          }
          iVar13 = iVar11;
          if (iVar11 < iVar10) {
            iVar13 = iVar10;
          }
          if (iVar13 < iVar12) {
            if (iVar3 < iVar9) {
              iVar3 = iVar9;
            }
          }
          else {
            iVar3 = iVar11;
            if (iVar11 < iVar10) {
              iVar3 = iVar10;
            }
          }
          iVar10 = FUN_0004c846(iVar4,0x30000);
          iVar12 = FUN_0004c88e(iVar4,0x30000);
          iVar11 = FUN_0004c8e2(iVar4,0x30000);
          iVar13 = FUN_0004c7e6(iVar4,0x30000);
          iVar9 = iVar12;
          if (iVar12 < iVar10) {
            iVar9 = iVar10;
          }
          iVar15 = iVar13;
          if (iVar13 < iVar11) {
            iVar15 = iVar11;
          }
          if (iVar15 < iVar9) {
            if (iVar12 < iVar10) {
              iVar12 = iVar10;
            }
          }
          else {
            iVar12 = iVar13;
            if (iVar13 < iVar11) {
              iVar12 = iVar11;
            }
          }
          iVar4 = FUN_0003b0f0(iVar4);
          iVar4 = iVar4 + ((iVar12 + 2) - iVar3);
          piVar14 = (int *)FUN_0004673a(param_2);
          if (iVar4 < *piVar14) {
            iVar4 = *piVar14;
          }
          *piVar14 = iVar4;
          return;
        }
        if (iVar3 != 0x1a) {
          return;
        }
        FUN_0003cd58(param_2);
        return;
      }
      iVar3 = FUN_0004673e(param_2);
      iVar12 = *(int *)(iVar4 + 0x40);
      iVar3 = iVar12 + iVar3;
    }
    FUN_0003d7bc(iVar4,iVar3);
LAB_0003d252:
    if (*(int *)(iVar4 + 0x40) == iVar12) {
      return;
    }
    FUN_0004e5a6(iVar4,0x20,0);
    return;
  }
  iVar3 = FUN_00047eec();
  if (iVar3 == 0) {
    return;
  }
  iVar12 = FUN_000482e0();
  if (iVar12 != 1) {
    return;
  }
  FUN_00048288(iVar3,&local_54);
  FUN_000371f0(iVar4,&local_4c,local_44);
  local_54 = local_54 - local_4c;
  local_50 = local_50 - local_48;
  if ((*(byte *)(iVar4 + 0x4c) & 1) == 0) {
    iVar3 = FUN_0004c5ac(iVar4,0x20000);
    local_44[0] = local_44[0] - iVar3;
    iVar12 = FUN_0004cd84(iVar4,0x10000);
    if ((iVar12 == 0) &&
       (iVar12 = (int)(local_44[0] + ((uint)(local_44[0] >> 0x1f) >> 0x1e)) >> 2, iVar3 < iVar12)) {
      iVar3 = iVar12;
    }
    local_44[0] = local_44[0] - iVar3;
    if (local_44[0] < 1) {
      local_44[0] = 1;
    }
    if (local_44[0] * local_44[0] < local_50 * local_50 + local_54 * local_54) {
      *(uint *)(iVar4 + 0x4c) = *(uint *)(iVar4 + 0x4c) | 1;
      uVar7 = FUN_00052708();
      *(undefined4 *)(iVar4 + 0x54) = uVar7;
    }
    if ((*(byte *)(iVar4 + 0x4c) & 1) == 0) {
      return;
    }
  }
  if ((local_54 == 0) && (local_50 == 0)) {
    return;
  }
  fVar19 = *(float *)(iVar4 + 0x3c);
  uVar8 = in_fpscr & 0xfffffff | (uint)(*(float *)(iVar4 + 0x38) <= fVar19) << 0x1d;
  if ((byte)(uVar8 >> 0x1d) == 0) {
    fVar19 = fVar19 + 360.0;
  }
  uVar7 = FUN_0003dfb4(local_50);
  fVar22 = (float)VectorUnsignedToFloat(uVar7,(byte)(uVar8 >> 0x16) & 3);
  fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(iVar4 + 0x2c),(byte)(uVar8 >> 0x16) & 3);
  fVar22 = (fVar22 - fVar20) - *(float *)(iVar4 + 0x38);
  while (uVar8 = uVar8 & 0xfffffff | (uint)(0.0 <= fVar22) << 0x1d, (byte)(uVar8 >> 0x1d) == 0) {
    fVar22 = fVar22 + 360.0;
  }
  for (; 0x43b3ffff < (int)fVar22; fVar22 = fVar22 - 360.0) {
  }
  uVar5 = local_44[0] * 0x274;
  iVar3 = FUN_00040c08(0x32);
  uVar7 = VectorUnsignedToFloat
                    ((int)((ulonglong)(uint)(iVar3 * 0x168) / ((ulonglong)uVar5 / 100)),
                     (byte)(uVar8 >> 0x16) & 3);
  uVar5 = -((int)((uint)*(byte *)(iVar4 + 0x4c) << 0x1c) >> 0x1f);
  iVar3 = FUN_0003cbf8(fVar22,uVar7,iVar4);
  if (iVar3 == 0) {
    return;
  }
  fVar21 = fVar19 - *(float *)(iVar4 + 0x38);
  fVar24 = *(float *)(iVar4 + 0x58) - *(float *)(iVar4 + 0x38);
  fVar18 = fVar22 - fVar24;
  uVar8 = uVar8 & 0xfffffff;
  uVar6 = uVar8 | (uint)(fVar18 < 0.0) << 0x1f | (uint)(fVar18 == 0.0) << 0x1e;
  uVar17 = uVar6 | (uint)NAN(fVar18) << 0x1c;
  bVar1 = (byte)(uVar6 >> 0x18);
  fVar20 = fVar18;
  if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar17 >> 0x1c) & 1)) {
    fVar20 = -fVar18;
  }
  fVar23 = 0.0;
  if ((int)fVar20 < 0x438c0001) {
    if ((-1 < *(int *)(iVar4 + 0x4c) << 0x1b) &&
       (fVar22 = fVar21, *(int *)(iVar4 + 0x4c) << 0x1c < 0)) {
      fVar22 = -fVar21;
    }
  }
  else {
    fVar22 = fVar21;
    if ((int)((uint)*(byte *)(iVar4 + 0x4c) << 0x1c) < 0) {
      fVar22 = fVar23;
    }
  }
  if (uVar5 == 0) {
    uVar6 = *(uint *)(iVar4 + 0x4c);
    if ((-1 < (int)(uVar6 << 0x1c)) || ((int)(uVar6 << 0x1b) < 0)) goto LAB_0003d100;
    uVar8 = uVar8 | (uint)(fVar18 < 0.0) << 0x1f | (uint)(fVar18 == 0.0) << 0x1e;
    uVar17 = uVar8 | (uint)NAN(fVar18) << 0x1c;
    bVar1 = (byte)(uVar8 >> 0x18);
    if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar17 >> 0x1c) & 1)) {
      fVar18 = -fVar18;
    }
    fVar18 = 360.0 - fVar18;
    fVar23 = fVar21;
  }
  else {
    uVar6 = *(uint *)(iVar4 + 0x4c);
    if (((int)(uVar6 << 0x1c) < 0) || ((int)(uVar6 << 0x1b) < 0)) goto LAB_0003d100;
    uVar8 = uVar8 | (uint)(fVar18 < 0.0) << 0x1f | (uint)(fVar18 == 0.0) << 0x1e;
    uVar17 = uVar8 | (uint)NAN(fVar18) << 0x1c;
    bVar1 = (byte)(uVar8 >> 0x18);
    if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar17 >> 0x1c) & 1)) {
      fVar18 = -fVar18;
    }
  }
  if (0x438c0000 < (int)fVar18) {
    *(uint *)(iVar4 + 0x4c) = uVar6 & 0xfffffff7 | (uVar5 & 1) << 3;
    fVar22 = fVar23;
  }
LAB_0003d100:
  fVar22 = fVar22 - fVar24;
  iVar3 = FUN_000526fc(*(undefined4 *)(iVar4 + 0x54));
  fVar20 = (float)VectorUnsignedToFloat
                            ((uint)(iVar3 * *(int *)(iVar4 + 0x50)) / 1000,
                             (byte)(uVar17 >> 0x16) & 3);
  uVar17 = uVar17 & 0xfffffff;
  uVar8 = uVar17 | (uint)(fVar22 < fVar20) << 0x1f | (uint)(fVar22 == fVar20) << 0x1e;
  bVar1 = (byte)(uVar8 >> 0x18);
  if ((!(bool)(bVar1 >> 6 & 1) && (bool)(bVar1 >> 7) == (NAN(fVar22) || NAN(fVar20))) ||
     (fVar20 = -fVar20, uVar8 = uVar17, fVar22 < fVar20)) {
    fVar22 = fVar20;
  }
  fVar18 = (float)VectorSignedToFloat(*(int *)(iVar4 + 0x48) - *(int *)(iVar4 + 0x44),
                                      (byte)(uVar8 >> 0x16) & 3);
  fVar20 = *(float *)(iVar4 + 0x38);
  iVar12 = *(int *)(iVar4 + 0x40);
  iVar3 = FUN_0004a388((int)(fVar20 + fVar24 + fVar22 +
                                      (((fVar19 - fVar20) * 8.0) / fVar18 + 4.0) * 0.0625),
                       (int)fVar20,(int)fVar19,*(int *)(iVar4 + 0x44),*(int *)(iVar4 + 0x48));
  if ((*(byte *)(iVar4 + 0x4c) & 7) >> 1 == 2) {
    iVar3 = (*(int *)(iVar4 + 0x48) - iVar3) + *(int *)(iVar4 + 0x44);
  }
  if (*(int *)(iVar4 + 0x40) != iVar3) {
    uVar7 = FUN_00052708();
    *(undefined4 *)(iVar4 + 0x54) = uVar7;
    FUN_0003d7bc(iVar4,iVar3);
    if ((iVar3 != iVar12) && (iVar12 = FUN_0004e5a6(iVar4,0x20,0), iVar12 != 1)) {
      return;
    }
  }
  if ((*(int *)(iVar4 + 0x44) != iVar3) && (*(int *)(iVar4 + 0x48) != iVar3)) {
    return;
  }
  uVar7 = FUN_00052708();
  *(undefined4 *)(iVar4 + 0x54) = uVar7;
  return;
}

