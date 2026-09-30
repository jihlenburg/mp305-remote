/* Address: 0004d58e; name: FUN_0004d58e; body bytes: 242 */

void FUN_0004d58e(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_38 [16];
  undefined1 auStack_28 [16];
  
  iVar4 = *(int *)(param_1 + 4);
  if (iVar4 != 0) {
    iVar1 = FUN_0004cd84(param_1,0x40000);
    if (iVar1 == 0) {
      iVar1 = FUN_0004bf20(iVar4);
      iVar1 = *(int *)(iVar4 + 0x14) - iVar1;
      iVar2 = FUN_0004bf2c(iVar4);
      iVar2 = *(int *)(iVar4 + 0x18) - iVar2;
    }
    else {
      iVar1 = *(int *)(iVar4 + 0x14);
      iVar2 = *(int *)(iVar4 + 0x18);
    }
    iVar3 = FUN_0004c9e8(iVar4,0);
    param_2 = param_2 + iVar1 + iVar3;
    iVar1 = FUN_0004caa4(iVar4,0);
    param_3 = param_3 + iVar2 + iVar1;
  }
  param_2 = param_2 - *(int *)(param_1 + 0x14);
  param_3 = param_3 - *(int *)(param_1 + 0x18);
  if ((param_2 != 0) || (param_3 != 0)) {
    FUN_0004d3d8(param_1);
    FUN_0004bb3c(param_1,auStack_28);
    iVar1 = 0;
    if (iVar4 != 0) {
      FUN_0004bab4(iVar4,auStack_38);
      iVar1 = FUN_0003db8c(auStack_28,auStack_38,0);
      if (iVar1 == 0) {
        FUN_0004e560(iVar4);
      }
    }
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_2;
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + param_3;
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + param_2;
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + param_3;
    FUN_0004d528(param_1,param_2,param_3,0);
    if (iVar4 == 0) {
      FUN_0004d3d8(param_1);
    }
    else {
      FUN_0004e5a6(iVar4,0x27,param_1);
      FUN_0004d3d8(param_1);
      iVar2 = FUN_0003db8c(param_1 + 0x14,auStack_38,0);
      if ((iVar1 != 0) || (iVar2 != 0)) {
        FUN_0004e560(iVar4);
      }
    }
  }
  return;
}

