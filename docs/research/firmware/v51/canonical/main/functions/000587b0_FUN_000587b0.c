/* Address: 000587b0; name: FUN_000587b0; body bytes: 160 */

void FUN_000587b0(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (param_4 == 0) {
    iVar6 = param_2[1] - (param_3 >> 1);
    param_2[1] = iVar6;
    param_2[3] = param_3 + -1 + iVar6;
    *param_2 = *(int *)(param_1 + 0x14);
    param_2[2] = *(int *)(param_1 + 0x1c);
  }
  else {
    iVar6 = *param_2 - (param_3 >> 1);
    *param_2 = iVar6;
    param_2[2] = param_3 + -1 + iVar6;
    param_2[1] = *(int *)(param_1 + 0x18);
    param_2[3] = *(int *)(param_1 + 0x20);
  }
  iVar6 = FUN_0004c86a(param_1,0x30000);
  iVar1 = FUN_0004c8ac(param_1,0x30000);
  iVar2 = FUN_0004c906(param_1,0x30000);
  iVar3 = FUN_0004c804(param_1,0x30000);
  iVar4 = FUN_0004cbd8(param_1,0x30000);
  iVar5 = FUN_0004cba6(param_1,0x30000);
  *param_2 = *param_2 - (iVar6 + iVar4);
  param_2[2] = param_2[2] + iVar1 + iVar4;
  param_2[1] = param_2[1] - (iVar2 + iVar5);
  param_2[3] = param_2[3] + iVar5 + iVar3;
  return;
}

