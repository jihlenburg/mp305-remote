/* Address: 0003d49c; name: FUN_0003d49c; body bytes: 176 */

void FUN_0003d49c(float param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 unaff_r4;
  uint in_fpscr;
  uint uVar6;
  uint uVar7;
  float fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined8 unaff_d8;
  
  uVar3 = (undefined4)unaff_d8;
  uVar9 = (undefined4)((ulonglong)unaff_d8 >> 0x20);
  if (0x43b40000 < (int)param_1) {
    param_1 = param_1 - 360.0;
  }
  fVar13 = *(float *)(param_2 + 0x3c);
  fVar10 = fVar13 - *(float *)(param_2 + 0x38);
  fVar8 = param_1 - *(float *)(param_2 + 0x38);
  uVar7 = in_fpscr & 0xfffffff;
  if (fVar10 < 0.0) {
    fVar10 = fVar10 + 360.0;
  }
  if (fVar8 < 0.0) {
    fVar8 = fVar8 + 360.0;
  }
  fVar12 = fVar8 - fVar10;
  uVar4 = uVar7 | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
  uVar6 = uVar4 | (uint)NAN(fVar12) << 0x1c;
  bVar1 = (byte)(uVar4 >> 0x18);
  if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar6 >> 0x1c) & 1)) {
    fVar12 = fVar10 - fVar8;
  }
  if ((int)fVar12 < 0x43340001) {
    uVar6 = uVar7 | (uint)(fVar10 <= fVar8) << 0x1d;
    fVar12 = param_1;
    if (((byte)(uVar6 >> 0x1d) == 0) ||
       (uVar6 = uVar7 | (uint)(fVar8 <= fVar10) << 0x1d, fVar12 = fVar13, fVar13 = param_1,
       (byte)(uVar6 >> 0x1d) == 0)) {
      FUN_0003a970(fVar12,fVar13,param_2,0);
    }
  }
  else {
    FUN_0004d3d8(param_2);
  }
  *(float *)(param_2 + 0x3c) = param_1;
  iVar2 = *(int *)(param_2 + 0x40);
  if (iVar2 == -0x8000) {
    return;
  }
  fVar13 = *(float *)(param_2 + 0x3c);
  fVar8 = *(float *)(param_2 + 0x38);
  uVar7 = uVar6 & 0xfffffff | (uint)(fVar8 <= fVar13) << 0x1d;
  if ((byte)(uVar7 >> 0x1d) == 0) {
    fVar13 = fVar13 + 360.0;
  }
  uVar4 = (*(byte *)(param_2 + 0x4c) & 7) >> 1;
  if (uVar4 == 0) {
    uVar3 = FUN_0004a388(iVar2,*(undefined4 *)(param_2 + 0x44),*(undefined4 *)(param_2 + 0x48),
                         (int)fVar8,(int)fVar13,uVar3,uVar9,unaff_r4);
    uVar9 = *(undefined4 *)(param_2 + 0x38);
    uVar11 = VectorSignedToFloat(uVar3,(byte)(uVar7 >> 0x16) & 3);
  }
  else {
    if (uVar4 == 1) {
      fVar13 = (fVar8 + fVar13) * 0.5;
      iVar5 = (*(int *)(param_2 + 0x44) + *(int *)(param_2 + 0x48)) / 2;
      if (iVar2 < iVar5) {
        uVar3 = FUN_0004a388(iVar2,*(int *)(param_2 + 0x44),iVar5,(int)fVar8,(int)fVar13,uVar3,uVar9
                             ,unaff_r4);
        uVar9 = VectorSignedToFloat(uVar3,(byte)(uVar7 >> 0x16) & 3);
        FUN_0003d6f8(uVar9,param_2);
      }
      else {
        uVar3 = FUN_0004a388();
        FUN_0003d6f8(fVar13,param_2);
        fVar13 = (float)VectorSignedToFloat(uVar3,(byte)(uVar7 >> 0x16) & 3);
      }
      FUN_0003d614(fVar13,param_2);
      goto LAB_00065e1c;
    }
    if (uVar4 != 2) {
      return;
    }
    uVar3 = FUN_0004a388(iVar2,*(undefined4 *)(param_2 + 0x44),*(undefined4 *)(param_2 + 0x48),
                         (int)fVar13,(int)fVar8,uVar3,uVar9,unaff_r4);
    uVar11 = *(undefined4 *)(param_2 + 0x3c);
    uVar9 = VectorSignedToFloat(uVar3,(byte)(uVar7 >> 0x16) & 3);
  }
  FUN_0003d450(uVar9,uVar11,param_2);
LAB_00065e1c:
  uVar3 = VectorSignedToFloat(uVar3,(byte)(uVar7 >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x58) = uVar3;
  return;
}

