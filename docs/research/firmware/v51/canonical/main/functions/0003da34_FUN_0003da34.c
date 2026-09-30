/* Address: 0003da34; name: FUN_0003da34; body bytes: 214 */

uint FUN_0003da34(int *param_1,int *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  
  iVar1 = FUN_0003dc12(param_2,param_3);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = FUN_0003db8c(param_2,param_3,0);
    uVar2 = 0;
    if (iVar1 == 0) {
      iVar5 = param_2[3];
      iVar1 = param_2[1];
      iVar4 = *param_2;
      iVar3 = param_2[2];
      iVar6 = param_3[1] - iVar1;
      if (0 < iVar6) {
        *param_1 = iVar4;
        param_1[1] = iVar1;
        param_1[2] = iVar3;
        param_1[3] = iVar6 + iVar1;
      }
      uVar2 = (uint)(0 < iVar6);
      iVar6 = param_3[3];
      iVar1 = (iVar5 - iVar1) - (iVar6 - param_2[1]);
      if ((0 < iVar1) && (iVar6 < param_2[3])) {
        piVar8 = param_1 + uVar2 * 4;
        iVar5 = param_2[2];
        *piVar8 = *param_2;
        piVar8[1] = iVar6;
        piVar8[2] = iVar5;
        piVar8[3] = iVar1 + iVar6;
        uVar2 = uVar2 + 1;
      }
      iVar1 = param_3[1];
      if (param_3[1] <= param_2[1]) {
        iVar1 = param_2[1];
      }
      iVar5 = param_3[3];
      if (param_2[3] <= param_3[3]) {
        iVar5 = param_2[3];
      }
      iVar5 = iVar5 - iVar1;
      iVar7 = *param_3;
      iVar6 = *param_2;
      if ((0 < iVar7 - iVar6) && (0 < iVar5)) {
        piVar8 = param_1 + uVar2 * 4;
        *piVar8 = iVar6;
        piVar8[1] = iVar1;
        piVar8[2] = (iVar7 - iVar6) + iVar6;
        piVar8[3] = iVar1 + iVar5;
        uVar2 = uVar2 + 1;
      }
      iVar6 = param_3[2];
      iVar3 = (iVar3 - iVar4) - (iVar6 - *param_2);
      if (0 < iVar3) {
        param_1 = param_1 + uVar2 * 4;
        *param_1 = iVar6;
        param_1[1] = iVar1;
        param_1[2] = iVar3 + iVar6;
        param_1[3] = iVar5 + iVar1;
        uVar2 = uVar2 + 1;
      }
    }
  }
  return uVar2;
}

