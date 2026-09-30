/* Address: 0003642c; name: FUN_0003642c; body bytes: 254 */

int FUN_0003642c(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  
  iVar1 = FUN_0004bf04();
  iVar7 = 0x1fffffff;
  if (iVar1 == 0) {
    iVar10 = 0x1fffffff;
  }
  else {
    iVar10 = 0x1fffffff;
    iVar2 = FUN_0004c91e(param_1,0);
    iVar3 = FUN_0004c81c(param_1,0);
    uVar4 = FUN_0004ba5c(param_1);
    for (uVar9 = 0; uVar9 < uVar4; uVar9 = uVar9 + 1) {
      iVar5 = *(int *)(**(int **)(param_1 + 8) + uVar9 * 4);
      iVar6 = FUN_0004cd92(iVar5,0x40001);
      if ((iVar6 == 0) && (iVar6 = FUN_0004cd84(iVar5,0x1000), iVar6 != 0)) {
        if (iVar1 == 1) {
          iVar6 = *(int *)(iVar5 + 0x18);
          iVar8 = *(int *)(param_1 + 0x18);
          iVar5 = iVar2;
LAB_000364ea:
          iVar8 = iVar8 + iVar5;
        }
        else {
          if (iVar1 != 2) {
            if (iVar1 != 3) goto LAB_0003651c;
            iVar6 = FUN_0003db0a(iVar5 + 0x14);
            iVar6 = *(int *)(iVar5 + 0x18) + iVar6 / 2;
            iVar5 = FUN_0003db0a(param_1 + 0x14);
            iVar8 = *(int *)(param_1 + 0x18);
            iVar5 = iVar2 + ((iVar5 - iVar2) - iVar3) / 2;
            goto LAB_000364ea;
          }
          iVar6 = *(int *)(iVar5 + 0x20);
          iVar8 = *(int *)(param_1 + 0x20) - iVar3;
        }
        iVar6 = iVar6 + param_4;
        if ((param_2 <= iVar6) && (iVar6 <= param_3)) {
          iVar6 = iVar6 - iVar8;
          iVar5 = iVar6;
          if (iVar6 < 1) {
            iVar5 = -iVar6;
          }
          iVar8 = iVar7;
          if (iVar7 < 1) {
            iVar8 = -iVar7;
          }
          if (iVar5 < iVar8) {
            iVar7 = iVar6;
          }
        }
      }
LAB_0003651c:
    }
    if (iVar7 != 0x1fffffff) {
      iVar10 = -iVar7;
    }
  }
  return iVar10;
}

