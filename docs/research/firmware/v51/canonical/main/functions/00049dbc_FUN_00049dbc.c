/* Address: 00049dbc; name: FUN_00049dbc; body bytes: 598 */

void FUN_00049dbc(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined1 auStack_78 [28];
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  byte local_3b;
  int local_38;
  int local_34;
  
  iVar3 = FUN_0004b9b2(&DAT_0007ab24);
  if (iVar3 == 1) {
    iVar3 = FUN_00046688(param_2);
    iVar4 = FUN_00046698(param_2);
    if (iVar3 == 0x18) {
      iVar3 = FUN_0004c924(iVar4,0,0x48);
      piVar7 = (int *)FUN_0004673a(param_2);
      if (*piVar7 < iVar3) {
        *piVar7 = iVar3;
      }
    }
    else if (iVar3 == 0x31) {
      if ((*(int *)(iVar4 + 0x30) != 0) && (*(int *)(iVar4 + 0x2c) != 0)) {
        piVar7 = (int *)FUN_0004673a(param_2);
        iVar6 = 0;
        iVar3 = 0;
        for (uVar10 = 0; uVar10 < *(uint *)(iVar4 + 0x30); uVar10 = uVar10 + 1) {
          fVar11 = *(float *)(*(int *)(iVar4 + 0x2c) + uVar10 * 8);
          if ((((int)fVar11 & 0x7fffffffU) >> 0x1d != 1) ||
             (0x1ffffffe < (int)((int)fVar11 & 0x9fffffffU))) {
            fVar12 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
            uVar1 = in_fpscr & 0xfffffff | (uint)(fVar11 < fVar12) << 0x1f |
                    (uint)(fVar11 == fVar12) << 0x1e;
            in_fpscr = uVar1 | (uint)(NAN(fVar11) || NAN(fVar12)) << 0x1c;
            bVar2 = (byte)(uVar1 >> 0x18);
            if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
              fVar11 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
            }
            iVar6 = (int)fVar11;
          }
          fVar11 = *(float *)(*(int *)(iVar4 + 0x2c) + uVar10 * 8 + 4);
          if ((((int)fVar11 & 0x7fffffffU) >> 0x1d != 1) ||
             (0x1ffffffe < (int)((int)fVar11 & 0x9fffffffU))) {
            fVar12 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
            uVar1 = in_fpscr & 0xfffffff | (uint)(fVar11 < fVar12) << 0x1f |
                    (uint)(fVar11 == fVar12) << 0x1e;
            in_fpscr = uVar1 | (uint)(NAN(fVar11) || NAN(fVar12)) << 0x1c;
            bVar2 = (byte)(uVar1 >> 0x18);
            if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
              fVar11 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
            }
            iVar3 = (int)fVar11;
          }
        }
        *piVar7 = iVar6;
        piVar7[1] = iVar3;
      }
    }
    else if (((iVar3 == 0x1a) && (uVar5 = FUN_00046718(param_2), *(int *)(iVar4 + 0x30) != 0)) &&
            (*(int *)(iVar4 + 0x2c) != 0)) {
      FUN_0004bb3c(iVar4,&local_38);
      iVar3 = FUN_0004bf20(iVar4);
      iVar6 = FUN_0004bf2c(iVar4);
      iVar6 = local_34 - iVar6;
      FUN_00042462(auStack_78);
      FUN_0004cff4(iVar4,0,auStack_78);
      for (uVar10 = 0; uVar10 < *(int *)(iVar4 + 0x30) - 1U; uVar10 = uVar10 + 1) {
        uVar8 = FUN_0004ccf8(iVar4);
        uVar9 = FUN_0004bbec(iVar4);
        local_5c = (float)FUN_0005b2b4(*(undefined4 *)(*(int *)(iVar4 + 0x2c) + uVar10 * 8),uVar8);
        fVar11 = (float)VectorSignedToFloat(local_38 - iVar3,(byte)(in_fpscr >> 0x16) & 3);
        local_5c = local_5c + fVar11;
        local_58 = (float)FUN_0005b2b4(*(undefined4 *)(uVar10 * 8 + 4 + *(int *)(iVar4 + 0x2c)),
                                       uVar9);
        local_54 = (float)FUN_0005b2b4(*(undefined4 *)(*(int *)(iVar4 + 0x2c) + uVar10 * 8 + 8),
                                       uVar8);
        fVar11 = (float)VectorSignedToFloat(local_38 - iVar3,(byte)(in_fpscr >> 0x16) & 3);
        local_54 = local_54 + fVar11;
        fVar11 = (float)FUN_0005b2b4(*(undefined4 *)(*(int *)(iVar4 + 0x2c) + uVar10 * 8 + 0xc),
                                     uVar9);
        if ((*(byte *)(iVar4 + 0x34) & 1) == 0) {
          fVar12 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          local_58 = local_58 + fVar12;
          local_50 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          local_50 = fVar11 + local_50;
        }
        else {
          fVar12 = (float)VectorSignedToFloat(uVar9,(byte)(in_fpscr >> 0x16) & 3);
          fVar13 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          local_58 = (fVar12 - local_58) + fVar13;
          fVar12 = (float)VectorSignedToFloat(uVar9,(byte)(in_fpscr >> 0x16) & 3);
          local_50 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          local_50 = (fVar12 - fVar11) + local_50;
        }
        FUN_000423a0(uVar5,auStack_78);
        local_3b = local_3b & 0xfb;
      }
    }
  }
  return;
}

