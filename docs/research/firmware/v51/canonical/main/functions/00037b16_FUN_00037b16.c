/* Address: 00037b16; name: FUN_00037b16; body bytes: 114 */

undefined8 FUN_00037b16(int param_1,int *param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_28;
  int *piStack_24;
  int local_20;
  undefined4 uStack_1c;
  
  local_28 = param_1;
  piStack_24 = param_2;
  local_20 = param_3;
  uStack_1c = param_4;
  uVar1 = FUN_0004cb3a(param_1,0);
  uVar2 = FUN_0004cb3a(param_1,0x40000);
  iVar3 = FUN_00046bd6(uVar1);
  iVar4 = FUN_00046bd6(uVar2);
  iVar5 = FUN_0004cb82(param_1,0);
  iVar5 = iVar5 + (iVar4 + iVar3) / 2;
  iVar3 = FUN_0004bbec(param_1);
  iVar3 = (*(int *)(param_1 + 0x18) + iVar3 / 2) - iVar5 / 2;
  param_2[1] = iVar3;
  param_2[3] = iVar3 + iVar5;
  FUN_0004bb3c(param_1,&local_28);
  *param_2 = local_28;
  param_2[2] = local_20;
  return CONCAT44(piStack_24,local_28);
}

