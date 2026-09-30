/* Address: 0003d476; name: FUN_0003d476; body bytes: 38 */

void FUN_0003d476(float param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 unaff_r4;
  uint in_fpscr;
  uint uVar5;
  uint uVar6;
  float fVar7;
  undefined4 uVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined8 unaff_d8;
  
  uVar3 = (undefined4)unaff_d8;
  uVar8 = (undefined4)((ulonglong)unaff_d8 >> 0x20);
  FUN_0003d49c(param_2);
  if (0x43b40000 < (int)param_1) {
    param_1 = param_1 - 360.0;
  }
  fVar13 = *(float *)(param_3 + 0x38);
  fVar9 = *(float *)(param_3 + 0x3c) - fVar13;
  fVar7 = *(float *)(param_3 + 0x3c) - param_1;
  in_fpscr = in_fpscr & 0xfffffff;
  if (fVar9 < 0.0) {
    fVar9 = fVar9 + 360.0;
  }
  if (fVar7 < 0.0) {
    fVar7 = fVar7 + 360.0;
  }
  fVar12 = fVar7 - fVar9;
  uVar6 = in_fpscr | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
  uVar5 = uVar6 | (uint)NAN(fVar12) << 0x1c;
  bVar1 = (byte)(uVar6 >> 0x18);
  if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar5 >> 0x1c) & 1)) {
    fVar12 = fVar9 - fVar7;
  }
  if ((int)fVar12 < 0x43340001) {
    uVar5 = in_fpscr | (uint)(fVar9 <= fVar7) << 0x1d;
    fVar12 = fVar13;
    fVar10 = param_1;
    if (((byte)(uVar5 >> 0x1d) == 0) ||
       (uVar5 = in_fpscr | (uint)(fVar7 <= fVar9) << 0x1d, fVar12 = param_1, fVar10 = fVar13,
       (byte)(uVar5 >> 0x1d) == 0)) {
      FUN_0003a970(fVar12,fVar10,param_3,0);
    }
  }
  else {
    FUN_0004d3d8(param_3);
  }
  *(float *)(param_3 + 0x38) = param_1;
  iVar2 = *(int *)(param_3 + 0x40);
  if (iVar2 == -0x8000) {
    return;
  }
  fVar7 = *(float *)(param_3 + 0x3c);
  fVar9 = *(float *)(param_3 + 0x38);
  uVar6 = uVar5 & 0xfffffff | (uint)(fVar9 <= fVar7) << 0x1d;
  if ((byte)(uVar6 >> 0x1d) == 0) {
    fVar7 = fVar7 + 360.0;
  }
  uVar5 = (*(byte *)(param_3 + 0x4c) & 7) >> 1;
  if (uVar5 == 0) {
    uVar3 = FUN_0004a388(iVar2,*(undefined4 *)(param_3 + 0x44),*(undefined4 *)(param_3 + 0x48),
                         (int)fVar9,(int)fVar7,uVar3,uVar8,unaff_r4);
    uVar8 = *(undefined4 *)(param_3 + 0x38);
    uVar11 = VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
  }
  else {
    if (uVar5 == 1) {
      fVar7 = (fVar9 + fVar7) * 0.5;
      iVar4 = (*(int *)(param_3 + 0x44) + *(int *)(param_3 + 0x48)) / 2;
      if (iVar2 < iVar4) {
        uVar3 = FUN_0004a388(iVar2,*(int *)(param_3 + 0x44),iVar4,(int)fVar9,(int)fVar7,uVar3,uVar8,
                             unaff_r4);
        uVar8 = VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
        FUN_0003d6f8(uVar8,param_3);
      }
      else {
        uVar3 = FUN_0004a388();
        FUN_0003d6f8(fVar7,param_3);
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
      }
      FUN_0003d614(fVar7,param_3);
      goto LAB_00065e1c;
    }
    if (uVar5 != 2) {
      return;
    }
    uVar3 = FUN_0004a388(iVar2,*(undefined4 *)(param_3 + 0x44),*(undefined4 *)(param_3 + 0x48),
                         (int)fVar7,(int)fVar9,uVar3,uVar8,unaff_r4);
    uVar11 = *(undefined4 *)(param_3 + 0x3c);
    uVar8 = VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
  }
  FUN_0003d450(uVar8,uVar11,param_3);
LAB_00065e1c:
  uVar3 = VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
  *(undefined4 *)(param_3 + 0x58) = uVar3;
  return;
}

