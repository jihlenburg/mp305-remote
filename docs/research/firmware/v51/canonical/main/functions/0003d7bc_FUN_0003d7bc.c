/* Address: 0003d7bc; name: FUN_0003d7bc; body bytes: 318 */

void FUN_0003d7bc(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint in_fpscr;
  uint uVar5;
  undefined4 uVar6;
  float fVar7;
  undefined4 uVar8;
  float fVar9;
  
  if (*(int *)(param_1 + 0x40) == param_2) {
    return;
  }
  if (*(int *)(param_1 + 0x48) < param_2) {
    param_2 = *(int *)(param_1 + 0x48);
  }
  if (param_2 < *(int *)(param_1 + 0x44)) {
    param_2 = *(int *)(param_1 + 0x44);
  }
  if (*(int *)(param_1 + 0x40) == param_2) {
    return;
  }
  *(int *)(param_1 + 0x40) = param_2;
  iVar1 = *(int *)(param_1 + 0x40);
  if (iVar1 == -0x8000) {
    return;
  }
  fVar7 = *(float *)(param_1 + 0x3c);
  fVar9 = *(float *)(param_1 + 0x38);
  uVar5 = in_fpscr & 0xfffffff | (uint)(fVar9 <= fVar7) << 0x1d;
  if ((byte)(uVar5 >> 0x1d) == 0) {
    fVar7 = fVar7 + 360.0;
  }
  uVar3 = (*(byte *)(param_1 + 0x4c) & 7) >> 1;
  if (uVar3 == 0) {
    uVar2 = FUN_0004a388(iVar1,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48),
                         (int)fVar9,(int)fVar7);
    uVar6 = *(undefined4 *)(param_1 + 0x38);
    uVar8 = VectorSignedToFloat(uVar2,(byte)(uVar5 >> 0x16) & 3);
  }
  else {
    if (uVar3 == 1) {
      fVar7 = (fVar9 + fVar7) * 0.5;
      iVar4 = (*(int *)(param_1 + 0x44) + *(int *)(param_1 + 0x48)) / 2;
      if (iVar1 < iVar4) {
        uVar2 = FUN_0004a388(iVar1,*(int *)(param_1 + 0x44),iVar4,(int)fVar9,(int)fVar7);
        uVar6 = VectorSignedToFloat(uVar2,(byte)(uVar5 >> 0x16) & 3);
        FUN_0003d6f8(uVar6,param_1);
      }
      else {
        uVar2 = FUN_0004a388();
        FUN_0003d6f8(fVar7,param_1);
        fVar7 = (float)VectorSignedToFloat(uVar2,(byte)(uVar5 >> 0x16) & 3);
      }
      FUN_0003d614(fVar7,param_1);
      goto LAB_00065e1c;
    }
    if (uVar3 != 2) {
      return;
    }
    uVar2 = FUN_0004a388(iVar1,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48),
                         (int)fVar7,(int)fVar9);
    uVar8 = *(undefined4 *)(param_1 + 0x3c);
    uVar6 = VectorSignedToFloat(uVar2,(byte)(uVar5 >> 0x16) & 3);
  }
  FUN_0003d450(uVar6,uVar8,param_1);
LAB_00065e1c:
  uVar2 = VectorSignedToFloat(uVar2,(byte)(uVar5 >> 0x16) & 3);
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  return;
}

