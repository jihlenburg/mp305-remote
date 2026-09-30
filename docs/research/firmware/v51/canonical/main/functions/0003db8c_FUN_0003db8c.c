/* Address: 0003db8c; name: FUN_0003db8c; body bytes: 134 */

undefined4 FUN_0003db8c(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  int local_18;
  int iStack_14;
  
  local_18 = *param_1;
  if ((((local_18 < *param_2) || (iStack_14 = param_1[1], iStack_14 < param_2[1])) ||
      (param_2[2] < param_1[2])) || (param_2[3] < param_1[3])) {
    return 0;
  }
  if (param_3 != 0) {
    iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
    if (iVar1 == 0) {
      return 0;
    }
    iStack_14 = param_1[1];
    local_18 = param_1[2];
    iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
    if (iVar1 == 0) {
      return 0;
    }
    iStack_14 = param_1[3];
    local_18 = *param_1;
    iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
    if (iVar1 == 0) {
      return 0;
    }
    local_18 = param_1[2];
    iStack_14 = param_1[3];
    iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 1;
}

