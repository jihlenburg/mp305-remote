/* Address: 000166ec; name: FUN_000166ec; body bytes: 290 */

undefined4 FUN_000166ec(int param_1,uint *param_2,float *param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint in_fpscr;
  float fVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  iVar5 = 0;
  uVar7 = 2;
  if ((param_2 != (uint *)0x0) && (param_3 != (float *)0x0)) {
    uVar6 = *param_2;
    uVar4 = DAT_2003a60c >> ((DAT_40054020 & 0x7fff) >> 0xc);
    uVar3 = 1 << (uVar6 & 0xff);
    if (*(int *)(param_1 + 0x30) << 0x1b < 0) {
      iVar5 = (*(uint *)(param_1 + 0x30) & 3) + 1;
    }
    if (uVar6 == 0) {
      uVar7 = 3;
    }
    if (uVar3 != 0) {
      fVar11 = (float)VectorUnsignedToFloat(param_2[1],(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = (float)VectorUnsignedToFloat(param_2[2],(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = (float)VectorUnsignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      fVar12 = (float)VectorUnsignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      fVar12 = (fVar10 / fVar11) / fVar12;
      fVar10 = (float)VectorUnsignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar11 = (float)VectorUnsignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = fVar10 * 2.0 + fVar11 * 2.0 + fVar8;
      uVar7 = VectorFloatToUnsigned(fVar12,3);
      fVar11 = fVar12 - fVar8;
      fVar13 = (float)VectorUnsignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = (float)VectorUnsignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
      if (0x3effffff < (int)(fVar12 - fVar13)) {
        fVar10 = fVar10 + 1.0;
      }
      if ((fVar8 < fVar10) &&
         (uVar1 = in_fpscr & 0xfffffff | (uint)(fVar11 < 62.0) << 0x1f |
                  (uint)(fVar11 == 62.0) << 0x1e, bVar2 = (byte)(uVar1 >> 0x18),
         (bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != NAN(fVar11))) {
        uVar9 = VectorFloatToUnsigned(fVar10,3);
        fVar12 = (float)VectorUnsignedToFloat(param_2[1],(byte)(uVar1 >> 0x16) & 3);
        uVar7 = (undefined4)(((ulonglong)uVar4 / (ulonglong)uVar9) / (ulonglong)uVar3);
        fVar8 = (float)VectorUnsignedToFloat(uVar7,(byte)(uVar1 >> 0x16) & 3);
        fVar10 = (float)VectorUnsignedToFloat(uVar7,(byte)(uVar1 >> 0x16) & 3);
        uVar3 = VectorFloatToUnsigned(fVar11,3);
        *(uint *)(param_1 + 0x2c) = uVar6 << 0x10 | uVar3 >> 1 | (uVar3 - (uVar3 >> 1)) * 0x100;
        *param_3 = (fVar12 - fVar8) / fVar10;
        return 0;
      }
    }
  }
  return 0xfffffffd;
}

