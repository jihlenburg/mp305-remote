/* Address: 0004bd90; name: FUN_0004bd90; body bytes: 172 */

int FUN_0004bd90(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined8 uVar9;
  
  iVar1 = FUN_0004c5be(param_1,0);
  if (iVar1 == 1) {
    iVar2 = FUN_0004ca76(param_1,0);
    iVar3 = FUN_0004ca18(param_1,0);
    uVar4 = FUN_0004ba5c(param_1);
    iVar1 = 0x1fffffff;
    for (uVar8 = 0; uVar8 < uVar4; uVar8 = uVar8 + 1) {
      iVar7 = *(int *)(**(int **)(param_1 + 8) + uVar8 * 4);
      iVar5 = FUN_0004cd92(iVar7,0x40001);
      iVar6 = iVar1;
      if (iVar5 == 0) {
        iVar6 = FUN_0004c924(iVar7,0,0x1a);
        iVar6 = *(int *)(iVar7 + 0x14) - iVar6;
        if (iVar1 < iVar6) {
          iVar6 = iVar1;
        }
      }
      iVar1 = iVar6;
    }
    if (iVar1 == 0x1fffffff) {
      iVar1 = -0x1fffffff;
    }
    else {
      iVar1 = (*(int *)(param_1 + 0x14) + iVar3) - iVar1;
    }
    iVar6 = FUN_0004c568(param_1);
    iVar7 = FUN_0004ccf8(param_1);
    uVar9 = FUN_0004bf20(param_1,iVar6 - ((iVar7 - iVar2) - iVar3));
    iVar2 = (int)uVar9 + (int)((ulonglong)uVar9 >> 0x20);
    if (iVar2 < iVar1) {
      iVar2 = iVar1;
    }
  }
  else {
    iVar2 = 0;
    if (*(int *)(param_1 + 8) != 0) {
      iVar2 = -*(int *)(*(int *)(param_1 + 8) + 0x18);
    }
  }
  return iVar2;
}

