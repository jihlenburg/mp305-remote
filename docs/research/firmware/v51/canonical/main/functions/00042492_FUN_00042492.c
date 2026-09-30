/* Address: 00042492; name: FUN_00042492; body bytes: 592 */

int FUN_00042492(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar2 = *(int *)(param_5 + 0xc);
  iVar1 = *(int *)(param_5 + 0x10);
  iVar5 = param_3 - iVar2;
  iVar6 = param_5 + 0x18;
  iVar4 = param_2 - *(int *)(param_5 + 8);
  iVar7 = param_5 + 0x50;
  iVar8 = param_2;
  iVar9 = param_3;
  iVar10 = param_4;
  if (iVar1 < 0xb4) {
    iVar3 = *(int *)(param_5 + 0x14);
    if ((((iVar3 < 0xb4) && (iVar1 != 0)) && (iVar3 != 0)) && (iVar3 < iVar1)) {
      if (param_3 < iVar2) {
        return 1;
      }
      iVar2 = (iVar5 + 1) * *(int *)(param_5 + 0x3c) >> 10;
      if ((((iVar1 - 0x10fU < 0x59) && (iVar2 < 0)) || ((iVar1 - 1U < 0x5a && (iVar2 < 0)))) ||
         ((iVar1 - 0x5bU < 0xb3 && (0 < iVar2)))) {
        iVar2 = 0;
      }
      if ((((iVar3 - 0x10fU < 0x59) && (iVar2 < 0)) || ((iVar3 - 1U < 0x5a && (iVar2 < 0)))) ||
         ((iVar3 - 0x5bU < 0xb3 && (0 < iVar2)))) {
        iVar2 = 0;
      }
      iVar1 = 1;
      iVar4 = (iVar2 + ((iVar5 * *(int *)(param_5 + 0x74) >> 10) - iVar2 >> 1)) - iVar4;
      if (param_4 < iVar4) {
        iVar4 = param_4;
      }
      if ((0 < iVar4) &&
         (iVar1 = FUN_000426e2(param_1,param_2,param_3,iVar4,iVar6,param_1,param_2,param_3,param_4),
         iVar1 == 0)) {
        FUN_0004a602(param_1,iVar4);
      }
      if (param_4 < iVar4) {
        iVar4 = param_4;
      }
      if (iVar4 < 0) {
        iVar4 = 0;
      }
      goto LAB_00042620;
    }
  }
  else if (((0xb4 < iVar1) && (iVar3 = *(int *)(param_5 + 0x14), 0xb4 < iVar3)) && (iVar3 < iVar1))
  {
    if (iVar2 < param_3) {
      return 1;
    }
    iVar2 = (iVar5 + 1) * *(int *)(param_5 + 0x3c) >> 10;
    if ((((iVar1 - 0x10fU < 0x59) && (iVar2 < 0)) || ((iVar1 - 1U < 0x5a && (iVar2 < 0)))) ||
       ((iVar1 - 0x5bU < 0xb3 && (0 < iVar2)))) {
      iVar2 = 0;
    }
    if ((((iVar3 - 0x10fU < 0x59) && (iVar2 < 0)) || ((iVar3 - 1U < 0x5a && (iVar2 < 0)))) ||
       ((iVar3 - 0x5bU < 0xb3 && (0 < iVar2)))) {
      iVar2 = 0;
    }
    iVar1 = 1;
    iVar4 = (iVar2 + ((iVar5 * *(int *)(param_5 + 0x74) >> 10) - iVar2 >> 1)) - iVar4;
    if (param_4 < iVar4) {
      iVar4 = param_4;
    }
    if ((0 < iVar4) &&
       (iVar1 = FUN_000426e2(param_1,param_2,param_3,iVar4,iVar7,param_1,param_2,param_3,param_4),
       iVar1 == 0)) {
      FUN_0004a602(param_1,iVar4);
    }
    if (param_4 < iVar4) {
      iVar4 = param_4;
    }
    iVar7 = iVar6;
    if (iVar4 < 0) {
      iVar4 = 0;
    }
LAB_00042620:
    iVar7 = FUN_000426e2(param_1 + iVar4,param_2 + iVar4,param_3,param_4 - iVar4,iVar7,param_1,iVar8
                         ,iVar9,iVar10);
    if (iVar7 == 0) {
      FUN_0004a602(param_1 + iVar4,param_4 - iVar4);
    }
    if (iVar1 != iVar7) {
      return 2;
    }
    return iVar1;
  }
  iVar5 = 1;
  iVar4 = 1;
  if (iVar1 == 0xb4) {
    if (iVar2 <= param_3) goto LAB_00042666;
  }
  else if (iVar1 == 0) {
    if (param_3 < iVar2) goto LAB_00042666;
  }
  else {
    if (iVar1 < 0xb4) {
      if (param_3 < iVar2) {
LAB_00042666:
        iVar5 = 3;
        goto LAB_0004267c;
      }
    }
    else if (iVar2 <= param_3) goto LAB_00042666;
    iVar5 = FUN_000426e2(param_1,param_2,param_3,param_4,iVar6,param_1,param_2,param_3,param_4);
  }
LAB_0004267c:
  iVar2 = *(int *)(param_5 + 0x14);
  iVar1 = iVar5;
  if (iVar2 == 0xb4) {
    if (*(int *)(param_5 + 0xc) <= param_3) goto joined_r0x000426c0;
  }
  else if (iVar2 == 0) {
    if (param_3 < *(int *)(param_5 + 0xc)) goto joined_r0x000426c0;
  }
  else if (iVar2 < 0xb4) {
    if (*(int *)(param_5 + 0xc) <= param_3) {
LAB_000426a8:
      iVar4 = FUN_000426e2(param_1,param_2,param_3,param_4,iVar7,param_1,iVar8,iVar9,iVar10);
      iVar1 = iVar4;
      if (iVar5 == 0) {
        return 0;
      }
      goto joined_r0x000426c0;
    }
  }
  else if (param_3 < *(int *)(param_5 + 0xc)) goto LAB_000426a8;
  iVar4 = 3;
joined_r0x000426c0:
  if (iVar1 == 0) {
    return 0;
  }
  if (iVar5 == 3) {
    if (iVar4 == 3) {
      return 0;
    }
  }
  else if ((iVar5 == 1) && (iVar4 == 1)) {
    return 1;
  }
  return 2;
}

