/* Address: 0004da38; name: FUN_0004da38; body bytes: 410 */

void FUN_0004da38(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  
  iVar1 = FUN_0004d498(param_1);
  if (iVar1 != 0) {
    return;
  }
  iVar1 = FUN_0004bc8c(param_1);
  uVar2 = FUN_0004cbfc(param_1,0);
  uVar3 = FUN_0004cc02(param_1,0);
  if (iVar1 == 0) goto LAB_0004db9c;
  iVar4 = FUN_0004bb1a();
  iVar5 = FUN_0004baf8(iVar1);
  if (((uVar2 & 0x7fffffff) >> 0x1d == 1) && (uVar6 = uVar2 & 0x9fffffff, (int)uVar6 < 0x1fffffff))
  {
    if (0xfffffff < (int)uVar6) {
      uVar6 = 0xfffffff - uVar6;
    }
    uVar2 = (int)(uVar6 * iVar4) / 100;
  }
  if (((uVar3 & 0x7fffffff) >> 0x1d == 1) && (uVar6 = uVar3 & 0x9fffffff, (int)uVar6 < 0x1fffffff))
  {
    if (0xfffffff < (int)uVar6) {
      uVar6 = 0xfffffff - uVar6;
    }
    uVar3 = (int)(iVar5 * uVar6) / 100;
  }
  uVar6 = FUN_0004c924(param_1,0,0x6a);
  uVar7 = FUN_0004c924(param_1,0,0x6b);
  iVar8 = FUN_0004ccf8(param_1);
  iVar9 = FUN_0004bbec(param_1);
  if (((uVar6 & 0x7fffffff) >> 0x1d == 1) && (uVar10 = uVar6 & 0x9fffffff, (int)uVar10 < 0x1fffffff)
     ) {
    if (0xfffffff < (int)uVar10) {
      uVar10 = 0xfffffff - uVar10;
    }
    uVar6 = (int)(uVar10 * iVar8) / 100;
  }
  if (((uVar7 & 0x7fffffff) >> 0x1d == 1) && (uVar10 = uVar7 & 0x9fffffff, (int)uVar10 < 0x1fffffff)
     ) {
    if (0xfffffff < (int)uVar10) {
      uVar10 = 0xfffffff - uVar10;
    }
    uVar7 = (int)(iVar9 * uVar10) / 100;
  }
  uVar2 = uVar6 + uVar2;
  uVar3 = uVar3 + uVar7;
  iVar11 = FUN_0004c594(param_1,0);
  if (iVar11 == 0) {
    iVar1 = FUN_0004c5b2(iVar1,0);
    if (iVar1 == 1) goto switchD_0004db50_caseD_3;
    goto switchD_0004db50_caseD_1;
  }
  switch(iVar11) {
  default:
    goto switchD_0004db50_caseD_1;
  case 2:
    iVar4 = iVar4 / 2 - iVar8 / 2;
    break;
  case 3:
switchD_0004db50_caseD_3:
    iVar4 = iVar4 - iVar8;
    break;
  case 4:
    goto switchD_0004db50_caseD_4;
  case 5:
    iVar4 = iVar4 / 2 - iVar8 / 2;
    goto LAB_0004dbbc;
  case 6:
    iVar4 = iVar4 - iVar8;
LAB_0004dbbc:
    uVar2 = uVar2 + iVar4;
switchD_0004db50_caseD_4:
    iVar5 = iVar5 - iVar9;
LAB_0004db96:
    uVar3 = uVar3 + iVar5;
    goto switchD_0004db50_caseD_1;
  case 7:
    goto switchD_0004db50_caseD_7;
  case 8:
    iVar4 = iVar4 - iVar8;
    goto LAB_0004dbd4;
  case 9:
    iVar4 = iVar4 / 2 - iVar8 / 2;
LAB_0004dbd4:
    uVar2 = uVar2 + iVar4;
switchD_0004db50_caseD_7:
    iVar5 = iVar5 / 2 - iVar9 / 2;
    goto LAB_0004db96;
  }
  uVar2 = uVar2 + iVar4;
switchD_0004db50_caseD_1:
LAB_0004db9c:
  FUN_0004d58e(param_1,uVar2,uVar3);
  return;
}

