/* Address: 0003711e; name: FUN_0003711e; body bytes: 210 */

void FUN_0003711e(int param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  *param_4 = 0;
  for (uVar1 = 0; uVar1 < param_3; uVar1 = uVar1 + 1) {
    *param_4 = *(int *)(*(int *)(param_1 + 0x3c) + uVar1 * 4) + *param_4;
  }
  iVar2 = FUN_0004c5d6(param_1,0);
  if (iVar2 == 1) {
    iVar2 = FUN_0004bf20(param_1);
    *param_4 = iVar2 + *param_4;
    iVar2 = FUN_0004ccf8(param_1);
    iVar3 = FUN_0004c8b8(param_1,0);
    iVar3 = (iVar2 - *param_4) - iVar3;
    param_4[2] = iVar3;
    *param_4 = iVar3 - *(int *)(*(int *)(param_1 + 0x3c) + param_3 * 4);
  }
  else {
    iVar2 = FUN_0004bf20(param_1);
    *param_4 = *param_4 - iVar2;
    iVar2 = FUN_0004c876(param_1,0);
    iVar3 = *param_4;
    *param_4 = iVar2 + iVar3;
    param_4[2] = iVar2 + iVar3 + *(int *)(*(int *)(param_1 + 0x3c) + param_3 * 4) + -1;
  }
  param_4[1] = 0;
  for (uVar1 = 0; uVar1 < param_2; uVar1 = uVar1 + 1) {
    param_4[1] = *(int *)(*(int *)(param_1 + 0x38) + uVar1 * 4) + param_4[1];
  }
  iVar2 = FUN_0004c912(param_1,0);
  param_4[1] = iVar2 + param_4[1];
  iVar2 = FUN_0004bf2c(param_1);
  iVar3 = param_4[1];
  param_4[1] = iVar3 - iVar2;
  param_4[3] = (iVar3 - iVar2) + *(int *)(*(int *)(param_1 + 0x38) + param_2 * 4) + -1;
  return;
}

