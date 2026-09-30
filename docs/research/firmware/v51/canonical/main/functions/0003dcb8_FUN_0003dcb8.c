/* Address: 0003dcb8; name: FUN_0003dcb8; body bytes: 234 */

undefined4 FUN_0003dcb8(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  local_28 = *param_1;
  if ((*param_2 < local_28) || (param_1[2] < *param_2)) {
    return 0;
  }
  if (param_2[1] < param_1[1]) {
    return 0;
  }
  if (param_1[3] < param_2[1]) {
    return 0;
  }
  if (param_3 < 1) {
    return 1;
  }
  iVar3 = ((param_1[2] - local_28) + 1) / 2;
  iVar1 = ((param_1[3] - param_1[1]) + 1) / 2;
  if (iVar3 < iVar1) {
    iVar1 = iVar3;
  }
  if (iVar1 < param_3) {
    param_3 = iVar1;
  }
  local_20 = *param_1 + param_3;
  local_24 = param_1[1];
  local_1c = param_1[1] + param_3;
  iVar1 = FUN_0003dcb8(&local_28,param_2,0);
  if (iVar1 == 0) {
    local_24 = param_1[3] - param_3;
    local_1c = param_1[3];
    iVar1 = FUN_0003dcb8(&local_28,param_2,0);
    if (iVar1 == 0) {
      local_28 = param_1[2] - param_3;
      local_20 = param_1[2];
      iVar1 = FUN_0003dcb8(&local_28,param_2,0);
      if (iVar1 == 0) {
        local_24 = param_1[1];
        local_1c = param_1[1] + param_3;
        iVar1 = FUN_0003dcb8(&local_28,param_2,0);
        if (iVar1 == 0) {
          return 1;
        }
        local_28 = local_28 - param_3;
        goto LAB_0003dd8e;
      }
      local_28 = local_28 - param_3;
    }
    else {
      local_20 = local_20 + param_3;
    }
    local_24 = local_24 - param_3;
  }
  else {
    local_20 = local_20 + param_3;
LAB_0003dd8e:
    local_1c = local_1c + param_3;
  }
  uVar2 = FUN_0004f2a8(&local_28,param_2);
  return uVar2;
}

