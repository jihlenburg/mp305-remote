/* Address: 0004b310; name: FUN_0004b310; body bytes: 116 */

void FUN_0004b310(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_2 + 4);
  if (iVar5 != 0) {
    iVar1 = FUN_0004bd90(iVar5);
    iVar2 = FUN_0004bf14(iVar5);
    iVar3 = FUN_0004c924(iVar5,0,0x10);
    iVar2 = (iVar3 + *(int *)(iVar5 + 0x18)) - iVar2;
    *(int *)(param_2 + 0x18) = iVar2;
    *(int *)(param_2 + 0x20) = iVar2 + -1;
    iVar3 = FUN_0004c924(iVar5,0,0x12);
    iVar1 = (iVar3 + *(int *)(iVar5 + 0x14)) - iVar1;
    *(int *)(param_2 + 0x14) = iVar1;
    *(int *)(param_2 + 0x1c) = iVar1 + -1;
  }
  uVar4 = 0x1002;
  *(undefined4 *)(param_2 + 0x24) = 0x1002;
  if (iVar5 != 0) {
    *(undefined4 *)(param_2 + 0x24) = 0x3002;
    uVar4 = 0x3302;
    *(undefined4 *)(param_2 + 0x24) = 0x3302;
  }
  *(uint *)(param_2 + 0x24) = uVar4 | 0x874;
  if (iVar5 != 0) {
    *(uint *)(param_2 + 0x24) = uVar4 | 0x8874;
  }
  return;
}

