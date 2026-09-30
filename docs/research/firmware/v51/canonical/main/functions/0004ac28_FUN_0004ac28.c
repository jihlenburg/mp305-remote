/* Address: 0004ac28; name: FUN_0004ac28; body bytes: 740 */

void FUN_0004ac28(undefined4 param_1,int param_2,int param_3,uint param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  
  FUN_0004ef90(param_1);
  if (param_2 == 0) {
    param_2 = FUN_0004bc8c(param_1);
  }
  iVar7 = 0;
  iVar8 = 0;
  iVar1 = FUN_0004bc8c(param_1);
  iVar2 = FUN_0004c9e8(iVar1,0);
  iVar3 = FUN_0004caa4(iVar1,0);
  iVar4 = FUN_0004c9e8(param_2,0);
  iVar5 = FUN_0004caa4(param_2,0);
  if (param_3 == 0) {
    iVar7 = FUN_0004c5b2(param_2,0);
    if (iVar7 == 1) goto switchD_0004ac84_caseD_3;
switchD_0004ac84_caseD_1:
    iVar7 = iVar4;
    iVar8 = iVar5;
    goto switchD_0004ac84_default;
  }
  switch(param_3) {
  case 1:
    goto switchD_0004ac84_caseD_1;
  case 2:
    iVar7 = FUN_0004bb1a(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 / 2 - iVar8 / 2;
    goto LAB_0004ad00;
  case 3:
switchD_0004ac84_caseD_3:
    iVar7 = FUN_0004bb1a(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 - iVar8;
LAB_0004ad00:
    iVar7 = iVar7 + iVar4;
    iVar8 = iVar5;
    break;
  case 4:
    goto LAB_0004ad3e;
  case 5:
    iVar7 = FUN_0004bb1a(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar8 = iVar7 / 2 - iVar8 / 2;
    goto LAB_0004ad3c;
  case 6:
    iVar8 = FUN_0004bb1a(param_2);
    iVar7 = FUN_0004ccf8(param_1);
    iVar8 = iVar8 - iVar7;
LAB_0004ad3c:
    iVar4 = iVar8 + iVar4;
LAB_0004ad3e:
    iVar8 = FUN_0004baf8(param_2);
    iVar7 = FUN_0004bbec(param_1);
    iVar8 = iVar8 - iVar7;
LAB_0004ad08:
    iVar7 = iVar4;
    iVar8 = iVar8 + iVar5;
    break;
  case 7:
    goto LAB_0004ad66;
  case 8:
    iVar7 = FUN_0004bb1a(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 - iVar8;
    goto LAB_0004ad64;
  case 9:
    iVar7 = FUN_0004bb1a(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 / 2 - iVar8 / 2;
LAB_0004ad64:
    iVar4 = iVar7 + iVar4;
LAB_0004ad66:
    iVar7 = FUN_0004baf8(param_2);
    iVar8 = FUN_0004bbec(param_1);
    iVar8 = iVar7 / 2 - iVar8 / 2;
    goto LAB_0004ad08;
  case 10:
    goto switchD_0004ac84_caseD_a;
  case 0xb:
    iVar7 = FUN_0004ccf8(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 / 2 - iVar8 / 2;
    goto switchD_0004ac84_caseD_a;
  case 0xc:
    iVar7 = FUN_0004ccf8(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 - iVar8;
switchD_0004ac84_caseD_a:
    iVar8 = FUN_0004bbec(param_1);
    iVar8 = -iVar8;
    break;
  case 0xd:
    goto switchD_0004ac84_caseD_d;
  case 0xe:
    iVar7 = FUN_0004ccf8(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 / 2 - iVar8 / 2;
    goto switchD_0004ac84_caseD_d;
  case 0xf:
    iVar7 = FUN_0004ccf8(param_2);
    iVar8 = FUN_0004ccf8(param_1);
    iVar7 = iVar7 - iVar8;
switchD_0004ac84_caseD_d:
    iVar8 = FUN_0004bbec(param_2);
    break;
  case 0x10:
    iVar7 = FUN_0004ccf8(param_1);
    iVar7 = -iVar7;
    break;
  case 0x11:
    iVar7 = FUN_0004ccf8(param_1);
    iVar7 = -iVar7;
    goto LAB_0004ae28;
  case 0x12:
    iVar7 = FUN_0004ccf8(param_1);
    iVar7 = -iVar7;
    goto LAB_0004ae4e;
  case 0x13:
    iVar7 = FUN_0004ccf8(param_2);
    break;
  case 0x14:
    iVar7 = FUN_0004ccf8(param_2);
LAB_0004ae28:
    iVar8 = FUN_0004bbec(param_2);
    iVar4 = FUN_0004bbec(param_1);
    iVar8 = iVar8 / 2 - iVar4 / 2;
    break;
  case 0x15:
    iVar7 = FUN_0004ccf8(param_2);
LAB_0004ae4e:
    iVar8 = FUN_0004bbec(param_2);
    iVar4 = FUN_0004bbec(param_1);
    iVar8 = iVar8 - iVar4;
  }
switchD_0004ac84_default:
  if (((param_4 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar9 = param_4 & 0x9fffffff, (int)uVar9 < 0x1fffffff)) {
    iVar4 = FUN_0004ccf8(param_2);
    if (0xfffffff < (int)uVar9) {
      uVar9 = 0xfffffff - uVar9;
    }
    param_4 = (int)(uVar9 * iVar4) / 100;
  }
  if (((param_5 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar9 = param_5 & 0x9fffffff, (int)uVar9 < 0x1fffffff)) {
    iVar4 = FUN_0004bbec(param_2);
    if (0xfffffff < (int)uVar9) {
      uVar9 = 0xfffffff - uVar9;
    }
    param_5 = (int)(uVar9 * iVar4) / 100;
  }
  iVar4 = FUN_0004c5b2(iVar1,0);
  if (iVar4 == 1) {
    iVar4 = FUN_0004be44(iVar1);
    iVar4 = iVar4 + ((*(int *)(param_2 + 0x14) + param_4) - *(int *)(iVar1 + 0x14));
  }
  else {
    iVar4 = FUN_0004bd90();
    iVar4 = ((*(int *)(param_2 + 0x14) + param_4) - *(int *)(iVar1 + 0x14)) + iVar4;
  }
  iVar5 = FUN_0004bf14(iVar1);
  iVar6 = *(int *)(param_2 + 0x18);
  iVar1 = *(int *)(iVar1 + 0x18);
  FUN_0004e86a(param_1,1,0);
  FUN_0004e7c2(param_1,iVar7 + (iVar4 - iVar2),
               iVar8 + ((((iVar6 + param_5) - iVar1) + iVar5) - iVar3));
  return;
}

