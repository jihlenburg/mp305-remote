/* Address: 0006532e; name: FUN_0006532e; body bytes: 406 */

void FUN_0006532e(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  bool bVar9;
  int local_28;
  int local_24;
  
  local_28 = param_3;
  local_24 = param_4;
  iVar2 = FUN_00047eec();
  iVar3 = FUN_000482e0();
  if (iVar3 != 1) {
    return;
  }
  iVar3 = FUN_000482c2(iVar2);
  if (iVar3 != 0) {
    return;
  }
  FUN_00048288(iVar2,&local_28);
  FUN_0004eef4(param_1,&local_28,3);
  iVar3 = FUN_0003ac70(param_1);
  if ((param_2 != 0) && ((*(byte *)(param_1 + 0xa0) & 1) == 0)) {
    if (iVar3 == 0) {
      iVar4 = *(int *)(param_1 + 0x98);
      iVar5 = local_24;
    }
    else {
      iVar4 = *(int *)(param_1 + 0x94);
      iVar5 = local_28;
    }
    iVar5 = iVar5 - iVar4;
    if (iVar5 < 1) {
      iVar5 = -iVar5;
    }
    if (iVar5 < (int)(uint)*(byte *)(iVar2 + 0x24)) {
      return;
    }
  }
  if (*(int *)(param_1 + 0x9c) == 0) {
    FUN_00028100(param_1);
  }
  iVar5 = *(int *)(param_1 + 0x34) - *(int *)(param_1 + 0x30);
  iVar2 = FUN_0004c5ca(param_1,0);
  bVar1 = FUN_0003ac70(param_1);
  bVar9 = *(byte *)(param_1 + 0x4c) == (iVar2 == 1 & bVar1);
  if (iVar3 == 0) {
    iVar2 = FUN_0004c906(param_1,0);
    iVar4 = FUN_0004c804(param_1,0);
    iVar6 = FUN_0004bbec(param_1);
    iVar6 = (iVar6 - iVar4) - iVar2;
    if (bVar9) {
      iVar2 = -(local_24 - (*(int *)(param_1 + 0x20) + iVar4));
    }
    else {
      iVar2 = local_24 - (*(int *)(param_1 + 0x18) + iVar2);
    }
    iVar6 = (iVar5 * iVar2 + iVar6 / 2) / iVar6;
  }
  else {
    iVar2 = FUN_0004c86a();
    iVar4 = FUN_0004c8ac(param_1,0);
    iVar6 = FUN_0004ccf8(param_1);
    iVar6 = (iVar6 - iVar2) - iVar4;
    if (bVar9) {
      iVar2 = local_28 - (*(int *)(param_1 + 0x14) + iVar2);
    }
    else {
      iVar2 = (*(int *)(param_1 + 0x1c) - iVar4) - local_28;
    }
    if (iVar6 == 0) goto LAB_00065468;
    iVar6 = (iVar5 * iVar2 + iVar6 / 2) / iVar6;
  }
  iVar2 = iVar6 + *(int *)(param_1 + 0x30);
LAB_00065468:
  iVar5 = *(int *)(param_1 + 0x30);
  iVar4 = *(int *)(param_1 + 0x34);
  piVar8 = *(int **)(param_1 + 0x9c);
  if (piVar8 == (int *)(param_1 + 0x38)) {
    iVar4 = *(int *)(param_1 + 0x2c);
  }
  else {
    iVar5 = *(int *)(param_1 + 0x38);
  }
  iVar6 = iVar4;
  if (iVar2 < iVar4) {
    iVar6 = iVar2;
  }
  if ((iVar5 <= iVar6) && (iVar5 = iVar2, iVar4 <= iVar2)) {
    iVar5 = iVar4;
  }
  if (*piVar8 != iVar5) {
    *piVar8 = iVar5;
    if (iVar3 == 0) {
      uVar7 = 0x100;
    }
    else {
      uVar7 = 0x200;
    }
    FUN_0004e00e(param_1,uVar7);
    FUN_0004d3d8(param_1);
    FUN_0004e5a6(param_1,0x20,0);
  }
  return;
}

