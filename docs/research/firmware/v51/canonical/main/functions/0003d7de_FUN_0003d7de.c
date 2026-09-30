/* Address: 0003d7de; name: FUN_0003d7de; body bytes: 414 */

void FUN_0003d7de(int *param_1,int *param_2,undefined4 param_3,int param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  uVar4 = param_2[2] - *param_2;
  iVar6 = *param_1;
  iVar5 = param_1[1];
  uVar7 = param_2[3] - param_2[1];
  switch(param_3) {
  default:
    uVar3 = 0;
    break;
  case 2:
    uVar3 = ((param_1[2] - iVar6) + 1) / 2 - (int)(uVar4 + 1) / 2;
    break;
  case 3:
    uVar3 = ((param_1[2] - iVar6) + 1) - (uVar4 + 1);
    break;
  case 4:
    uVar3 = 0;
    goto LAB_0003d87a;
  case 5:
    uVar3 = ((param_1[2] - iVar6) + 1) / 2 - (int)(uVar4 + 1) / 2;
    goto LAB_0003d87a;
  case 6:
    uVar3 = ((param_1[2] - iVar6) + 1) - (uVar4 + 1);
    goto LAB_0003d87a;
  case 7:
    uVar3 = 0;
    goto LAB_0003d89c;
  case 8:
    uVar3 = ((param_1[2] - iVar6) + 1) - (uVar4 + 1);
    goto LAB_0003d89c;
  case 9:
    uVar3 = ((param_1[2] - iVar6) + 1) / 2 - (int)(uVar4 + 1) / 2;
    goto LAB_0003d89c;
  case 10:
    uVar3 = 0;
    goto LAB_0003d8e4;
  case 0xb:
    uVar3 = ((param_1[2] - iVar6) + 1) / 2 - (int)(uVar4 + 1) / 2;
    goto LAB_0003d8e4;
  case 0xc:
    uVar3 = ((param_1[2] - iVar6) + 1) - (uVar4 + 1);
LAB_0003d8e4:
    uVar1 = ~uVar7;
    goto LAB_0003d964;
  case 0xd:
    uVar3 = 0;
    goto LAB_0003d916;
  case 0xe:
    uVar3 = ((param_1[2] - iVar6) + 1) / 2 - (int)(uVar4 + 1) / 2;
    goto LAB_0003d916;
  case 0xf:
    uVar3 = ((param_1[2] - iVar6) + 1) - (uVar4 + 1);
LAB_0003d916:
    uVar1 = (param_1[3] - iVar5) + 1;
    goto LAB_0003d964;
  case 0x10:
    uVar3 = ~uVar4;
    break;
  case 0x11:
    uVar3 = ~uVar4;
LAB_0003d89c:
    uVar1 = ((param_1[3] - iVar5) + 1) / 2 - (int)(uVar7 + 1) / 2;
    goto LAB_0003d964;
  case 0x12:
    uVar3 = ~uVar4;
LAB_0003d87a:
    uVar1 = ((param_1[3] - iVar5) + 1) - (uVar7 + 1);
    goto LAB_0003d964;
  case 0x13:
    iVar2 = param_1[2] - iVar6;
    uVar1 = 0;
    goto LAB_0003d962;
  case 0x14:
    iVar2 = param_1[2] - iVar6;
    uVar1 = ((param_1[3] - iVar5) + 1) / 2 - (int)(uVar7 + 1) / 2;
    goto LAB_0003d962;
  case 0x15:
    iVar2 = param_1[2] - iVar6;
    uVar1 = ((param_1[3] - iVar5) + 1) - (uVar7 + 1);
LAB_0003d962:
    uVar3 = iVar2 + 1;
    goto LAB_0003d964;
  }
  uVar1 = 0;
LAB_0003d964:
  param_4 = uVar3 + iVar6 + param_4;
  param_5 = uVar1 + iVar5 + param_5;
  *param_2 = param_4;
  param_2[1] = param_5;
  param_2[2] = param_4 + uVar4;
  param_2[3] = param_5 + uVar7;
  return;
}

