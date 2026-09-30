/* Address: 00025f5c; name: FUN_00025f5c; body bytes: 236 */

int FUN_00025f5c(int param_1)

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
  
  iVar1 = FUN_0004bf2c();
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 0x1c) = 0;
  }
  iVar2 = FUN_0004caa4(param_1,0);
  iVar3 = FUN_0004c98a(param_1,0);
  iVar4 = FUN_0004c54c(param_1);
  iVar8 = -0x1fffffff;
  iVar4 = iVar4 + iVar2 + iVar3;
  uVar5 = FUN_0004ba5c(param_1);
  for (uVar9 = 0; uVar9 < uVar5; uVar9 = uVar9 + 1) {
    iVar10 = -0x1fffffff;
    iVar6 = *(int *)(**(int **)(param_1 + 8) + uVar9 * 4);
    iVar7 = FUN_0004cd92(iVar6,0x40001);
    if (iVar7 == 0) {
      iVar7 = FUN_0004d498(iVar6);
      if ((((iVar7 == 0) && (iVar7 = FUN_0004c594(iVar6,0), iVar7 != 0)) && (iVar7 != 1)) &&
         ((iVar7 != 2 && (iVar7 != 3)))) {
        iVar7 = FUN_0004cc02(iVar6,0);
        if (iVar7 == 0) {
          iVar7 = FUN_0003db0a(iVar6 + 0x14);
          iVar10 = FUN_0004c744(iVar6,0);
          iVar10 = iVar10 + iVar7 + iVar2;
        }
      }
      else {
        iVar10 = (*(int *)(iVar6 + 0x20) - *(int *)(param_1 + 0x18)) + 1;
      }
      iVar7 = FUN_0004c70e(iVar6,0);
      if (iVar8 <= iVar7 + iVar10) {
        iVar8 = FUN_0004c70e(iVar6,0);
        iVar8 = iVar8 + iVar10;
      }
    }
  }
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(*(int *)(param_1 + 8) + 0x1c) = -iVar1;
  }
  if ((iVar8 == -0x1fffffff) || (iVar1 = iVar8 + iVar3, iVar8 + iVar3 < iVar4)) {
    iVar1 = iVar4;
  }
  return iVar1;
}

