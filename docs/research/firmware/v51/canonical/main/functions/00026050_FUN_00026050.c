/* Address: 00026050; name: FUN_00026050; body bytes: 402 */

undefined8 FUN_00026050(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  
  iVar1 = FUN_0004bf20();
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 0x18) = 0;
  }
  iVar2 = FUN_0004ca46(param_1,0);
  iVar3 = FUN_0004c9e8(param_1,0);
  iVar4 = FUN_0004c568(param_1);
  iVar4 = iVar4 + iVar3 + iVar2;
  iVar8 = -0x1fffffff;
  uVar5 = FUN_0004ba5c(param_1);
  iVar6 = FUN_0004c5b2(param_1,0);
  uVar9 = 0;
  if (iVar6 == 1) {
    for (; uVar9 < uVar5; uVar9 = uVar9 + 1) {
      iVar10 = -0x1fffffff;
      iVar6 = *(int *)(**(int **)(param_1 + 8) + uVar9 * 4);
      iVar7 = FUN_0004cd92(iVar6,0x40001);
      if (iVar7 == 0) {
        iVar7 = FUN_0004d498(iVar6);
        if (iVar7 == 0) {
          iVar7 = FUN_0004c594(iVar6,0);
          if ((((iVar7 == 0) || (iVar7 == 3)) || (iVar7 == 6)) || (iVar7 == 8)) {
            iVar10 = *(int *)(param_1 + 0x1c) - *(int *)(iVar6 + 0x14);
            goto LAB_000260f8;
          }
          iVar7 = FUN_0004cbfc(iVar6,0);
          if (iVar7 == 0) {
            iVar7 = FUN_0003db28(iVar6 + 0x14);
            iVar10 = FUN_0004c720(iVar6,0);
            iVar10 = iVar10 + iVar7 + iVar2;
          }
        }
        else {
          iVar10 = *(int *)(param_1 + 0x1c) - *(int *)(iVar6 + 0x14);
LAB_000260f8:
          iVar10 = iVar10 + 1;
        }
        iVar7 = FUN_0004c720(iVar6,0);
        if (iVar8 <= iVar7 + iVar10) {
          iVar8 = FUN_0004c720(iVar6,0);
          iVar8 = iVar8 + iVar10;
        }
      }
    }
    if (iVar8 != -0x1fffffff) {
      iVar8 = iVar8 + iVar3;
    }
  }
  else {
    for (; uVar9 < uVar5; uVar9 = uVar9 + 1) {
      iVar10 = -0x1fffffff;
      iVar6 = *(int *)(**(int **)(param_1 + 8) + uVar9 * 4);
      iVar7 = FUN_0004cd92(iVar6,0x40001);
      if (iVar7 == 0) {
        iVar7 = FUN_0004d498(iVar6);
        if (((iVar7 == 0) && (iVar7 = FUN_0004c594(iVar6,0), iVar7 != 0)) &&
           ((iVar7 != 1 && ((iVar7 != 4 && (iVar7 != 7)))))) {
          iVar7 = FUN_0004cbfc(iVar6,0);
          if (iVar7 == 0) {
            iVar7 = FUN_0003db28(iVar6 + 0x14);
            iVar10 = FUN_0004c732(iVar6,0);
            iVar10 = iVar10 + iVar7 + iVar3;
          }
        }
        else {
          iVar10 = (*(int *)(iVar6 + 0x1c) - *(int *)(param_1 + 0x14)) + 1;
        }
        iVar7 = FUN_0004c732(iVar6,0);
        if (iVar8 <= iVar7 + iVar10) {
          iVar8 = FUN_0004c732(iVar6,0);
          iVar8 = iVar8 + iVar10;
        }
      }
    }
    if (iVar8 != -0x1fffffff) {
      iVar8 = iVar8 + iVar2;
    }
  }
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(*(int *)(param_1 + 8) + 0x18) = -iVar1;
  }
  if ((iVar8 != -0x1fffffff) && (iVar4 < iVar8)) {
    iVar4 = iVar8;
  }
  return CONCAT44(iVar2,iVar4);
}

