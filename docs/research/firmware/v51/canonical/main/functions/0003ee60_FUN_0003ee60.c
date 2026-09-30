/* Address: 0003ee60; name: FUN_0003ee60; body bytes: 450 */

void FUN_0003ee60(int param_1,int param_2)

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
  uint uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  uint uVar18;
  int local_4c;
  
  if (param_2 == 0) {
    return;
  }
  FUN_00023730();
  *(int *)(param_1 + 0x2c) = param_2;
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
  iVar17 = 0;
  iVar7 = iVar4 * (1 - *(int *)(param_1 + 0x3c)) + iVar7;
  for (uVar8 = 0; uVar8 < *(uint *)(param_1 + 0x3c); uVar8 = uVar8 + 1) {
    uVar18 = 0;
    uVar15 = 0;
    while (((iVar9 = *(int *)(param_2 + uVar15 * 4), iVar9 != 0 &&
            (iVar9 = thunk_FUN_00050a1a(iVar9,&DAT_0003f024), iVar9 != 0)) &&
           (**(char **)(param_2 + uVar15 * 4) != '\0'))) {
      iVar9 = FUN_000370a2(*(undefined2 *)(*(int *)(param_1 + 0x34) + (iVar17 + uVar15) * 2));
      uVar18 = uVar18 + iVar9;
      uVar15 = uVar15 + 1;
    }
    if (uVar15 != 0) {
      uVar13 = *(uint *)(param_1 + 0x3c);
      local_4c = iVar5 * (1 - uVar15) + iVar6;
      if (local_4c < 0) {
        local_4c = 0;
      }
      iVar9 = 0;
      for (uVar16 = 0; uVar16 < uVar15; uVar16 = uVar16 + 1) {
        iVar10 = FUN_000370a2(*(undefined2 *)(*(int *)(param_1 + 0x34) + iVar17 * 2));
        uVar11 = local_4c * iVar9;
        iVar9 = iVar9 + iVar10;
        iVar12 = uVar16 * iVar5 + uVar11 / uVar18;
        iVar14 = uVar16 * iVar5 + ((uint)(iVar9 * local_4c) / uVar18 - 1);
        iVar10 = iVar12;
        if (cVar1 == '\x01') {
          iVar10 = iVar6 - iVar14;
          iVar14 = iVar6 - iVar12;
        }
        FUN_0003ddf0(*(int *)(param_1 + 0x30) + iVar17 * 0x10,iVar2 + iVar10,
                     uVar8 * iVar4 + (iVar7 * uVar8) / uVar13 + iVar3,iVar14 + iVar2,
                     (((uVar8 + 1) * iVar7) / uVar13 - 1) + uVar8 * iVar4 + iVar3);
        iVar17 = iVar17 + 1;
      }
      param_2 = param_2 + uVar15 * 4;
    }
    param_2 = param_2 + 4;
  }
  FUN_0004de6c(param_1);
  FUN_0004d3d8(param_1);
  return;
}

