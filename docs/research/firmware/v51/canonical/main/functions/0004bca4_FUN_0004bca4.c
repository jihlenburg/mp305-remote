/* Address: 0004bca4; name: FUN_0004bca4; body bytes: 144 */

int FUN_0004bca4(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  
  uVar1 = FUN_0004ba5c();
  iVar6 = -0x1fffffff;
  for (uVar7 = 0; uVar7 < uVar1; uVar7 = uVar7 + 1) {
    iVar4 = *(int *)(**(int **)(param_1 + 8) + uVar7 * 4);
    iVar3 = FUN_0004cd92(iVar4,0x40001);
    iVar2 = iVar6;
    if (iVar3 == 0) {
      iVar2 = FUN_0004c924(iVar4,0,0x19);
      iVar2 = iVar2 + *(int *)(iVar4 + 0x20);
      if (iVar2 < iVar6) {
        iVar2 = iVar6;
      }
    }
    iVar6 = iVar2;
  }
  iVar2 = FUN_0004cad4(param_1,0);
  iVar3 = FUN_0004c9ba(param_1,0);
  if (iVar6 != -0x1fffffff) {
    iVar6 = iVar6 - (*(int *)(param_1 + 0x20) - iVar3);
  }
  iVar4 = FUN_0004c54c(param_1);
  iVar5 = FUN_0004bbec(param_1);
  uVar8 = FUN_0004bf2c(param_1,iVar4 - ((iVar5 - iVar2) - iVar3));
  iVar2 = (int)((ulonglong)uVar8 >> 0x20) - (int)uVar8;
  if (iVar2 < iVar6) {
    iVar2 = iVar6;
  }
  return iVar2;
}

