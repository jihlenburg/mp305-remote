/* Address: 0005e278; name: FUN_0005e278; body bytes: 594 */

void FUN_0005e278(int *param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar1 = FUN_0004bc8c(param_2);
  iVar2 = FUN_0004cd84(iVar1,0x10);
  if (iVar2 == 0) {
    return;
  }
  uVar3 = FUN_0004bd40(iVar1);
  iVar2 = FUN_0004bf04(iVar1);
  piVar7 = (int *)(param_2 + 0x14);
  if (iVar2 == 0) {
    piVar7 = param_1;
  }
  iVar4 = FUN_0004cad4(iVar1,0);
  iVar5 = FUN_0004c9ba(iVar1,0);
  iVar9 = ((*(int *)(iVar1 + 0x18) + iVar4) - piVar7[1]) - param_3[1];
  iVar10 = param_3[1] - ((*(int *)(iVar1 + 0x20) - iVar5) - piVar7[3]);
  iVar6 = FUN_0004bbec(iVar1);
  iVar8 = 0;
  if (iVar9 < 0) {
LAB_0005e30a:
    if (0 < iVar10) {
      iVar9 = FUN_0004bca4(iVar1);
      iVar8 = -iVar10;
      if (iVar9 - iVar10 < 0) goto LAB_0005e31e;
    }
  }
  else if (iVar10 < 0) {
    if (iVar9 < 1) goto LAB_0005e30a;
    iVar10 = FUN_0004bf14(iVar1);
    iVar8 = iVar9;
    if (-1 < iVar10 - iVar9) goto LAB_0005e320;
LAB_0005e31e:
    iVar8 = 0;
  }
LAB_0005e320:
  if (iVar2 != 0) {
    if (iVar2 == 1) {
      iVar2 = (*(int *)(iVar1 + 0x18) + iVar4) - (piVar7[1] + iVar8);
    }
    else if (iVar2 == 2) {
      iVar2 = (*(int *)(iVar1 + 0x20) - iVar5) - (piVar7[3] + iVar8);
    }
    else {
      if (iVar2 != 3) goto LAB_0005e34e;
      iVar9 = *(int *)(iVar1 + 0x18);
      iVar2 = FUN_0003db0a(piVar7);
      iVar2 = (iVar9 + iVar4 + ((iVar6 - iVar4) - iVar5) / 2) - (iVar8 + iVar2 / 2 + piVar7[1]);
    }
    iVar8 = iVar8 + iVar2;
  }
LAB_0005e34e:
  iVar2 = FUN_0004bef4(iVar1);
  if (iVar2 != 0) {
    param_1 = (int *)(param_2 + 0x14);
  }
  iVar5 = FUN_0004ca18(iVar1,0);
  iVar9 = FUN_0004ca76(iVar1,0);
  iVar6 = ((*(int *)(iVar1 + 0x14) + iVar5) - *param_1) - *param_3;
  iVar10 = *param_3 - ((*(int *)(iVar1 + 0x1c) - iVar9) - param_1[2]);
  iVar4 = 0;
  if (iVar6 < 0) {
LAB_0005e3d8:
    if (0 < iVar10) {
      iVar6 = FUN_0004be44(iVar1);
      iVar4 = -iVar10;
      if (iVar6 - iVar10 < 0) goto LAB_0005e3e8;
    }
  }
  else if (iVar10 < 0) {
    if (iVar6 < 1) goto LAB_0005e3d8;
    iVar10 = FUN_0004bd90(iVar1);
    iVar4 = iVar6;
    if (-1 < iVar10 - iVar6) goto LAB_0005e3ea;
LAB_0005e3e8:
    iVar4 = 0;
  }
LAB_0005e3ea:
  iVar6 = FUN_0004ccf8(iVar1);
  if (iVar2 == 0) goto LAB_0005e426;
  if (iVar2 == 1) {
    iVar9 = *(int *)(iVar1 + 0x14) + iVar5;
    iVar2 = *param_1;
LAB_0005e420:
    iVar9 = iVar9 - (iVar2 + iVar4);
  }
  else {
    if (iVar2 == 2) {
      iVar9 = *(int *)(iVar1 + 0x1c) - iVar9;
      iVar2 = param_1[2];
      goto LAB_0005e420;
    }
    if (iVar2 != 3) goto LAB_0005e426;
    iVar10 = *(int *)(iVar1 + 0x14);
    iVar2 = FUN_0003db28(param_1);
    iVar9 = (iVar10 + iVar5 + ((iVar6 - iVar5) - iVar9) / 2) - (iVar4 + iVar2 / 2 + *param_1);
  }
  iVar4 = iVar4 + iVar9;
LAB_0005e426:
  FUN_0003c97c(iVar1,0x5e5b3);
  FUN_0003c97c(iVar1,0x5e59d);
  if (((uVar3 & 1) == 0) && (iVar4 < 0)) {
    iVar4 = 0;
  }
  if ((-1 < (int)(uVar3 << 0x1e)) && (0 < iVar4)) {
    iVar4 = 0;
  }
  if ((-1 < (int)(uVar3 << 0x1d)) && (iVar8 < 0)) {
    iVar8 = 0;
  }
  if ((-1 < (int)(uVar3 << 0x1c)) && (0 < iVar8)) {
    iVar8 = 0;
  }
  iVar2 = 0;
  if (param_4 != 0) {
    iVar2 = iVar4;
  }
  *param_3 = *param_3 + iVar2;
  iVar2 = iVar8;
  if (param_4 == 0) {
    iVar2 = 0;
  }
  param_3[1] = param_3[1] + iVar2;
  FUN_0004e25c(iVar1,iVar4,iVar8,param_4);
  return;
}

