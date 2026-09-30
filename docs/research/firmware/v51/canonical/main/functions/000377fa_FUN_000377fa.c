/* Address: 000377fa; name: FUN_000377fa; body bytes: 208 */

undefined4 FUN_000377fa(int param_1,uint *param_2,uint *param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint *local_20;
  int local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  FUN_00047eec();
  iVar1 = FUN_000482e0();
  if ((iVar1 == 1) || (iVar1 == 3)) {
    uVar2 = FUN_00047eec();
    FUN_00048288(uVar2,&local_20);
    if (param_3 != (uint *)0x0) {
      iVar1 = FUN_0004bf20(param_1);
      iVar1 = iVar1 + (int)local_20;
      iVar3 = FUN_0004c5d6(param_1,0);
      if (iVar3 == 1) {
        iVar3 = FUN_0004c8b8(param_1,0);
        iVar3 = (*(int *)(param_1 + 0x1c) - iVar3) - iVar1;
      }
      else {
        iVar4 = *(int *)(param_1 + 0x14);
        iVar3 = FUN_0004c876(param_1,0);
        iVar3 = (iVar1 - iVar4) - iVar3;
      }
      iVar1 = 0;
      uVar5 = 0;
      *param_3 = 0;
      while ((uVar5 < *(uint *)(param_1 + 0x2c) &&
             (iVar1 = iVar1 + *(int *)(*(int *)(param_1 + 0x3c) + uVar5 * 4), iVar1 <= iVar3))) {
        uVar5 = uVar5 + 1;
        *param_3 = uVar5;
      }
    }
    if (param_2 != (uint *)0x0) {
      iVar1 = FUN_0004bf2c(param_1);
      iVar1 = iVar1 + local_1c;
      iVar6 = *(int *)(param_1 + 0x18);
      iVar3 = FUN_0004c912(param_1,0);
      iVar4 = 0;
      uVar5 = 0;
      *param_2 = 0;
      while ((uVar5 < *(uint *)(param_1 + 0x30) &&
             (iVar4 = iVar4 + *(int *)(*(int *)(param_1 + 0x38) + uVar5 * 4),
             iVar4 <= (iVar1 - iVar6) - iVar3))) {
        uVar5 = uVar5 + 1;
        *param_2 = uVar5;
      }
    }
    uVar2 = 1;
  }
  else {
    if (param_3 != (uint *)0x0) {
      *param_3 = 0xffff;
    }
    if (param_2 != (uint *)0x0) {
      *param_2 = 0xffff;
    }
    uVar2 = 0;
  }
  return uVar2;
}

