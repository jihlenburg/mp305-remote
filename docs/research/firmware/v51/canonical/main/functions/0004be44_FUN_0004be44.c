/* Address: 0004be44; name: FUN_0004be44; body bytes: 166 */

int FUN_0004be44(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  
  iVar1 = FUN_0004c5be(param_1,0);
  if (iVar1 == 1) {
    iVar1 = 0;
    if (*(int *)(param_1 + 8) != 0) {
      iVar1 = *(int *)(*(int *)(param_1 + 8) + 0x18);
    }
  }
  else {
    uVar2 = FUN_0004ba5c(param_1);
    iVar6 = -0x1fffffff;
    for (uVar7 = 0; uVar7 < uVar2; uVar7 = uVar7 + 1) {
      iVar3 = *(int *)(**(int **)(param_1 + 8) + uVar7 * 4);
      iVar4 = FUN_0004cd92(iVar3,0x40001);
      iVar1 = iVar6;
      if (iVar4 == 0) {
        iVar1 = FUN_0004c924(iVar3,0,0x1b);
        iVar1 = iVar1 + *(int *)(iVar3 + 0x1c);
        if (iVar1 < iVar6) {
          iVar1 = iVar6;
        }
      }
      iVar6 = iVar1;
    }
    iVar1 = FUN_0004ca76(param_1,0);
    iVar3 = FUN_0004ca18(param_1,0);
    if (iVar6 != -0x1fffffff) {
      iVar6 = iVar6 - (*(int *)(param_1 + 0x1c) - iVar1);
    }
    iVar4 = FUN_0004c568(param_1);
    iVar5 = FUN_0004ccf8(param_1);
    uVar8 = FUN_0004bf20(param_1,iVar4 - ((iVar5 - iVar1) - iVar3));
    iVar1 = (int)((ulonglong)uVar8 >> 0x20) - (int)uVar8;
    if (iVar1 < iVar6) {
      iVar1 = iVar6;
    }
  }
  return iVar1;
}

