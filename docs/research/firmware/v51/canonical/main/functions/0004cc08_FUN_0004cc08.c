/* Address: 0004cc08; name: FUN_0004cc08; body bytes: 240 */

void FUN_0004cc08(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_28 = *param_2;
  local_24 = param_2[1];
  local_20 = *param_2;
  local_1c = param_2[3] + 1;
  local_18 = param_2[2] + 1;
  local_14 = param_2[1];
  local_10 = param_2[2] + 1;
  local_c = param_2[3] + 1;
  FUN_0004eefc(param_1,&local_28,4,param_3);
  iVar1 = local_20;
  if (local_28 < local_20) {
    iVar1 = local_28;
  }
  iVar2 = local_18;
  if (local_10 <= local_18) {
    iVar2 = local_10;
  }
  if (iVar1 < iVar2) {
    iVar1 = local_28;
    iVar2 = local_20;
    if (local_20 <= local_28) {
LAB_0004cc68:
      iVar1 = iVar2;
    }
  }
  else {
    iVar1 = local_18;
    iVar2 = local_10;
    if (local_10 <= local_18) goto LAB_0004cc68;
  }
  *param_2 = iVar1;
  iVar1 = local_20;
  if (local_20 < local_28) {
    iVar1 = local_28;
  }
  iVar2 = local_18;
  if (local_18 <= local_10) {
    iVar2 = local_10;
  }
  if (iVar2 < iVar1) {
    iVar1 = local_20;
    if (local_28 <= local_20) {
LAB_0004cc94:
      local_28 = iVar1;
    }
  }
  else {
    local_28 = local_18;
    iVar1 = local_10;
    if (local_18 <= local_10) goto LAB_0004cc94;
  }
  param_2[2] = local_28;
  iVar1 = local_24;
  if (local_1c <= local_24) {
    iVar1 = local_1c;
  }
  iVar2 = local_14;
  if (local_c <= local_14) {
    iVar2 = local_c;
  }
  if (iVar1 < iVar2) {
    iVar1 = local_24;
    iVar2 = local_1c;
    if (local_1c <= local_24) {
LAB_0004ccc2:
      iVar1 = iVar2;
    }
  }
  else {
    iVar1 = local_14;
    iVar2 = local_c;
    if (local_c <= local_14) goto LAB_0004ccc2;
  }
  param_2[1] = iVar1;
  iVar1 = local_24;
  if (local_24 <= local_1c) {
    iVar1 = local_1c;
  }
  iVar2 = local_14;
  if (local_14 <= local_c) {
    iVar2 = local_c;
  }
  if (iVar2 < iVar1) {
    iVar1 = local_1c;
    if (local_1c < local_24) goto LAB_0004ccf2;
  }
  else {
    local_24 = local_14;
    iVar1 = local_c;
    if (local_c < local_14) goto LAB_0004ccf2;
  }
  local_24 = iVar1;
LAB_0004ccf2:
  param_2[3] = local_24;
  return;
}

