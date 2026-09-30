/* Address: 000261ec; name: FUN_000261ec; body bytes: 422 */

/* WARNING: Type propagation algorithm not settling */

void FUN_000261ec(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined *puVar8;
  uint uVar9;
  undefined *puVar10;
  uint uVar11;
  undefined4 local_30;
  
  iVar2 = FUN_00037a16(param_1);
  bVar1 = false;
  if (iVar2 == 0) {
    FUN_0004bc8c(param_1);
    iVar3 = FUN_00037a16();
    if (iVar3 == 0) {
      return;
    }
    iVar4 = FUN_00037b06(param_1);
    iVar5 = FUN_00037b0e(param_1);
    iVar2 = FUN_0004a318(iVar5 * 4 + 4);
    FUN_0004a404(iVar2,iVar3 + iVar4 * 4,iVar5 * 4);
    *(undefined4 *)(iVar2 + iVar5 * 4) = 0x1fffffff;
    bVar1 = true;
  }
  iVar3 = FUN_000277d8(iVar2);
  *(int *)(param_2 + 0x14) = iVar3;
  uVar6 = FUN_0004a318(iVar3 << 2);
  *(undefined4 *)(param_2 + 4) = uVar6;
  uVar6 = FUN_0004a318(*(int *)(param_2 + 0x14) << 2);
  *(undefined4 *)(param_2 + 0xc) = uVar6;
  for (uVar9 = 0; uVar9 < *(uint *)(param_2 + 0x14); uVar9 = uVar9 + 1) {
    iVar3 = -0x1fffffff;
    if (*(undefined **)(iVar2 + uVar9 * 4) == &DAT_1fffff9a) {
      for (uVar11 = 0; uVar7 = FUN_0004ba5c(param_1), uVar11 < uVar7; uVar11 = uVar11 + 1) {
        local_30 = FUN_0004b9de(param_1,uVar11);
        iVar4 = FUN_0004cd92(local_30,0x60001);
        if ((((iVar4 == 0) && (iVar4 = FUN_00037b0e(local_30), iVar4 == 1)) &&
            (uVar7 = FUN_00037b06(local_30), uVar7 == uVar9)) &&
           (iVar4 = FUN_0004bbec(local_30), iVar3 <= iVar4)) {
          iVar3 = FUN_0004bbec(local_30);
        }
      }
      if (iVar3 < 0) {
        *(undefined4 *)(*(int *)(param_2 + 0xc) + uVar9 * 4) = 0;
      }
      else {
        *(int *)(*(int *)(param_2 + 0xc) + uVar9 * 4) = iVar3;
      }
    }
  }
  puVar10 = (undefined *)0x0;
  iVar3 = 0;
  for (uVar9 = 0; uVar9 < *(uint *)(param_2 + 0x14); uVar9 = uVar9 + 1) {
    puVar8 = *(undefined **)(iVar2 + uVar9 * 4);
    if ((int)puVar8 < 0x1fffff9b) {
      if (puVar8 == &DAT_1fffff9a) {
        iVar3 = iVar3 + *(int *)(*(int *)(param_2 + 0xc) + uVar9 * 4);
      }
      else {
        iVar3 = iVar3 + (int)puVar8;
        *(undefined **)(*(int *)(param_2 + 0xc) + uVar9 * 4) = puVar8;
      }
    }
    else {
      puVar10 = &DAT_e0000065 + (int)(puVar10 + (int)puVar8);
    }
  }
  iVar4 = FUN_0004c8d6(param_1,0);
  iVar5 = FUN_0004baf8(param_1);
  iVar3 = (iVar4 * (1 - *(int *)(param_2 + 0x14)) + iVar5) - iVar3;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  uVar9 = 0;
  while ((uVar9 < *(uint *)(param_2 + 0x14) && (puVar10 != (undefined *)0x0))) {
    iVar4 = *(int *)(iVar2 + uVar9 * 4);
    if (0x1fffff9a < iVar4) {
      iVar5 = (iVar3 * (int)(&DAT_e0000065 + iVar4) + (int)puVar10 / 2) / (int)puVar10;
      puVar10 = puVar10 + -(int)(&DAT_e0000065 + iVar4);
      iVar3 = iVar3 - iVar5;
      *(int *)(*(int *)(param_2 + 0xc) + uVar9 * 4) = iVar5;
    }
    uVar9 = uVar9 + 1;
  }
  if (!bVar1) {
    return;
  }
  FUN_00046bec(iVar2,local_30,param_1,param_2);
  return;
}

