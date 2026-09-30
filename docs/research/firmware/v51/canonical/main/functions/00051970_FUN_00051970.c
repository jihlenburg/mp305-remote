/* Address: 00051970; name: FUN_00051970; body bytes: 184 */

void FUN_00051970(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,
                 undefined4 param_6,uint param_7)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  *param_1 = 0;
  param_1[1] = 0;
  if ((param_2 != 0) && (param_3 != 0)) {
    if ((param_7 & 1) != 0) {
      param_6 = 0x1fffffff;
    }
    piVar7 = param_1;
    iVar8 = param_2;
    uVar2 = FUN_00046bd6(param_3);
    uVar5 = (uint)uVar2;
    iVar6 = 0;
    while (*(char *)(param_2 + iVar6) != '\0') {
      iVar3 = param_2 + iVar6;
      iVar4 = FUN_0005175c(iVar3,param_3,param_4,param_6,0,param_7,iVar3,piVar7,iVar8);
      if (0x7fffffff < uVar5 + param_5 + param_1[1]) {
        return;
      }
      param_1[1] = param_1[1] + uVar5 + param_5;
      iVar3 = FUN_00051a28(iVar3,(iVar6 + iVar4) - iVar6,param_3,param_4);
      if (iVar3 <= *param_1) {
        iVar3 = *param_1;
      }
      *param_1 = iVar3;
      iVar6 = iVar6 + iVar4;
    }
    if ((iVar6 != 0) &&
       ((cVar1 = *(char *)(param_2 + iVar6 + -1), cVar1 == '\n' || (cVar1 == '\r')))) {
      param_1[1] = uVar5 + param_5 + param_1[1];
    }
    if (param_1[1] == 0) {
      param_1[1] = uVar5;
    }
    else {
      param_1[1] = param_1[1] - param_5;
    }
  }
  return;
}

