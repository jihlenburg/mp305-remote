/* Address: 00010cb6; name: FUN_00010cb6; body bytes: 90 */

void FUN_00010cb6(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int local_28;
  int local_24;
  int iStack_20;
  int local_18 [2];
  
  local_24 = 0xffffffff;
  local_18[0] = 0;
  local_28 = param_2;
  iStack_20 = param_2;
  iVar1 = FUN_00010c80(local_18,&local_28,param_1);
  local_24 = param_2 + local_18[0];
  if (param_3 != (int *)0x0) {
    iVar2 = param_2;
    if (local_18[0] != 0) {
      iVar2 = local_24;
    }
    *param_3 = iVar2;
  }
  if ((local_18[0] != 0) && ((iVar1 < 1 || (local_28 != local_24)))) {
    local_24 = local_24 - param_2;
    local_28 = param_2;
    iStack_20 = param_2;
    FUN_00010c80(local_18,&local_28,param_1);
  }
  return;
}

