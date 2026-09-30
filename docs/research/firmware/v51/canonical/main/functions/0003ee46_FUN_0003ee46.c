/* Address: 0003ee46; name: FUN_0003ee46; body bytes: 26 */

void FUN_0003ee46(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  uint uVar19;
  int iStack_4c;
  
  FUN_0004a404(*(undefined4 *)(param_1 + 0x34),param_2,*(int *)(param_1 + 0x38) << 1);
  iVar13 = *(int *)(param_1 + 0x2c);
  if (iVar13 == 0) {
    return;
  }
  FUN_00023730();
  *(int *)(param_1 + 0x2c) = iVar13;
  cVar1 = FUN_0004c924(param_1,0,0x27);
  iVar2 = FUN_0004c852(param_1,0);
  iVar3 = FUN_0004c690(param_1,0);
  iVar4 = FUN_0004c660(param_1,0);
  if (iVar4 << 0x1d < 0) {
    iVar2 = iVar2 + iVar3;
  }
  iVar3 = FUN_0004c8ee(param_1,0);
  iVar4 = FUN_0004c690(param_1,0);
  iVar5 = FUN_0004c660(param_1,0);
  if (iVar5 << 0x1e < 0) {
    iVar3 = iVar3 + iVar4;
  }
  iVar4 = FUN_0004c8ca(param_1,0);
  iVar5 = FUN_0004c822(param_1,0);
  iVar6 = FUN_0004bb1a(param_1);
  iVar7 = FUN_0004baf8(param_1);
  iVar18 = 0;
  iVar7 = iVar4 * (1 - *(int *)(param_1 + 0x3c)) + iVar7;
  for (uVar8 = 0; uVar8 < *(uint *)(param_1 + 0x3c); uVar8 = uVar8 + 1) {
    uVar19 = 0;
    uVar16 = 0;
    while (((iVar9 = *(int *)(iVar13 + uVar16 * 4), iVar9 != 0 &&
            (iVar9 = thunk_FUN_00050a1a(iVar9,&DAT_0003f024), iVar9 != 0)) &&
           (**(char **)(iVar13 + uVar16 * 4) != '\0'))) {
      iVar9 = FUN_000370a2(*(undefined2 *)(*(int *)(param_1 + 0x34) + (iVar18 + uVar16) * 2));
      uVar19 = uVar19 + iVar9;
      uVar16 = uVar16 + 1;
    }
    if (uVar16 != 0) {
      uVar14 = *(uint *)(param_1 + 0x3c);
      iStack_4c = iVar5 * (1 - uVar16) + iVar6;
      if (iStack_4c < 0) {
        iStack_4c = 0;
      }
      iVar9 = 0;
      for (uVar17 = 0; uVar17 < uVar16; uVar17 = uVar17 + 1) {
        iVar10 = FUN_000370a2(*(undefined2 *)(*(int *)(param_1 + 0x34) + iVar18 * 2));
        uVar11 = iStack_4c * iVar9;
        iVar9 = iVar9 + iVar10;
        iVar12 = uVar17 * iVar5 + uVar11 / uVar19;
        iVar15 = uVar17 * iVar5 + ((uint)(iVar9 * iStack_4c) / uVar19 - 1);
        iVar10 = iVar12;
        if (cVar1 == '\x01') {
          iVar10 = iVar6 - iVar15;
          iVar15 = iVar6 - iVar12;
        }
        FUN_0003ddf0(*(int *)(param_1 + 0x30) + iVar18 * 0x10,iVar2 + iVar10,
                     uVar8 * iVar4 + (iVar7 * uVar8) / uVar14 + iVar3,iVar15 + iVar2,
                     (((uVar8 + 1) * iVar7) / uVar14 - 1) + uVar8 * iVar4 + iVar3);
        iVar18 = iVar18 + 1;
      }
      iVar13 = iVar13 + uVar16 * 4;
    }
    iVar13 = iVar13 + 4;
  }
  FUN_0004de6c(param_1);
  FUN_0004d3d8(param_1);
  return;
}

