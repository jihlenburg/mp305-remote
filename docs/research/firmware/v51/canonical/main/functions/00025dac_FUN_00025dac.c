/* Address: 00025dac; name: FUN_00025dac; body bytes: 416 */

/* WARNING: Type propagation algorithm not settling */

void FUN_00025dac(undefined4 param_1,undefined4 *param_2)

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
  
  iVar2 = FUN_0003727c(param_1);
  bVar1 = false;
  if (iVar2 == 0) {
    FUN_0004bc8c(param_1);
    iVar3 = FUN_0003727c();
    if (iVar3 == 0) {
      return;
    }
    iVar4 = FUN_00037284(param_1);
    iVar5 = FUN_0003728c(param_1);
    iVar2 = FUN_0004a318(iVar5 * 4 + 4);
    FUN_0004a404(iVar2,iVar3 + iVar4 * 4,iVar5 * 4);
    *(undefined4 *)(iVar2 + iVar5 * 4) = 0x1fffffff;
    bVar1 = true;
  }
  iVar3 = FUN_0004bb1a(param_1);
  iVar4 = FUN_000277d8(iVar2);
  param_2[4] = iVar4;
  uVar6 = FUN_0004a318(iVar4 << 2);
  *param_2 = uVar6;
  uVar6 = FUN_0004a318(param_2[4] << 2);
  param_2[2] = uVar6;
  for (uVar9 = 0; uVar9 < (uint)param_2[4]; uVar9 = uVar9 + 1) {
    iVar4 = -0x1fffffff;
    if (*(undefined **)(iVar2 + uVar9 * 4) == &DAT_1fffff9a) {
      for (uVar11 = 0; uVar7 = FUN_0004ba5c(param_1), uVar11 < uVar7; uVar11 = uVar11 + 1) {
        local_30 = FUN_0004b9de(param_1,uVar11);
        iVar5 = FUN_0004cd92(local_30,0x60001);
        if ((((iVar5 == 0) && (iVar5 = FUN_0003728c(local_30), iVar5 == 1)) &&
            (uVar7 = FUN_00037284(local_30), uVar7 == uVar9)) &&
           (iVar5 = FUN_0004ccf8(local_30), iVar4 <= iVar5)) {
          iVar4 = FUN_0004ccf8(local_30);
        }
      }
      if (iVar4 < 0) {
        *(undefined4 *)(param_2[2] + uVar9 * 4) = 0;
      }
      else {
        *(int *)(param_2[2] + uVar9 * 4) = iVar4;
      }
    }
  }
  puVar10 = (undefined *)0x0;
  iVar4 = 0;
  for (uVar9 = 0; uVar9 < (uint)param_2[4]; uVar9 = uVar9 + 1) {
    puVar8 = *(undefined **)(iVar2 + uVar9 * 4);
    if ((int)puVar8 < 0x1fffff9b) {
      if (puVar8 == &DAT_1fffff9a) {
        iVar4 = iVar4 + *(int *)(param_2[2] + uVar9 * 4);
      }
      else {
        iVar4 = iVar4 + (int)puVar8;
        *(undefined **)(param_2[2] + uVar9 * 4) = puVar8;
      }
    }
    else {
      puVar10 = &DAT_e0000065 + (int)(puVar10 + (int)puVar8);
    }
  }
  iVar5 = FUN_0004c83a(param_1,0);
  iVar4 = (iVar5 * (1 - param_2[4]) + iVar3) - iVar4;
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  uVar9 = 0;
  while ((uVar9 < (uint)param_2[4] && (puVar10 != (undefined *)0x0))) {
    iVar3 = *(int *)(iVar2 + uVar9 * 4);
    if (0x1fffff9a < iVar3) {
      iVar5 = (iVar4 * (int)(&DAT_e0000065 + iVar3) + (int)puVar10 / 2) / (int)puVar10;
      puVar10 = puVar10 + -(int)(&DAT_e0000065 + iVar3);
      iVar4 = iVar4 - iVar5;
      *(int *)(param_2[2] + uVar9 * 4) = iVar5;
    }
    uVar9 = uVar9 + 1;
  }
  if (!bVar1) {
    return;
  }
  FUN_00046bec(iVar2,local_30,param_1,param_2);
  return;
}

