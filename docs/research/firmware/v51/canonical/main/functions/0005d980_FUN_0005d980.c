/* Address: 0005d980; name: FUN_0005d980; body bytes: 136 */

void FUN_0005d980(int param_1,int *param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  iVar1 = FUN_0004c864(param_1,0);
  iVar2 = FUN_0004c8a6(param_1,0);
  iVar3 = FUN_0004c900(param_1,0);
  iVar4 = FUN_0004c7fe(param_1,0);
  iVar5 = FUN_0004ccf8(param_1);
  iVar6 = FUN_0004bbec(param_1);
  if ((iVar5 - iVar1) - iVar2 < (iVar6 - iVar3) - iVar4) {
    iVar4 = FUN_0004ccf8();
    uVar7 = (iVar4 - iVar1) - iVar2;
  }
  else {
    iVar2 = FUN_0004bbec(param_1);
    uVar7 = (iVar2 - iVar3) - iVar4;
  }
  uVar7 = uVar7 >> 1;
  *param_2 = uVar7 + iVar1 + *(int *)(param_1 + 0x14);
  param_2[1] = uVar7 + iVar3 + *(int *)(param_1 + 0x18);
  if (param_3 != (uint *)0x0) {
    *param_3 = uVar7;
  }
  return;
}

