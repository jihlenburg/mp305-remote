/* Address: 0004747e; name: FUN_0004747e; body bytes: 330 */

void FUN_0004747e(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 undefined4 param_7)

{
  int iVar1;
  int iVar2;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  if (((param_4 == 0) && (param_5 == 0x100)) && (param_6 == 0x100)) {
    param_1[3] = param_3 + -1;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = param_2 + -1;
    return;
  }
  FUN_0001049c(&local_40,0x20);
  local_38 = param_2;
  local_2c = param_3;
  local_28 = param_2;
  local_24 = param_3;
  FUN_0004f292(&local_40,param_4,param_5,param_6,param_7,1);
  FUN_0004f292(&local_38,param_4,param_5,param_6,param_7,1);
  FUN_0004f292(&local_30,param_4,param_5,param_6,param_7,1);
  FUN_0004f292(&local_28,param_4,param_5,param_6,param_7,1);
  iVar1 = local_40;
  if (local_38 <= local_40) {
    iVar1 = local_38;
  }
  iVar2 = local_30;
  if (local_28 <= local_30) {
    iVar2 = local_28;
  }
  if (iVar1 < iVar2) {
    iVar1 = local_40;
    iVar2 = local_38;
    if (local_38 <= local_40) {
LAB_00047534:
      iVar1 = iVar2;
    }
  }
  else {
    iVar1 = local_30;
    iVar2 = local_28;
    if (local_28 <= local_30) goto LAB_00047534;
  }
  *param_1 = iVar1;
  iVar1 = local_40;
  if (local_40 <= local_38) {
    iVar1 = local_38;
  }
  iVar2 = local_30;
  if (local_30 <= local_28) {
    iVar2 = local_28;
  }
  if (iVar2 < iVar1) {
    iVar1 = local_38;
    if (local_40 <= local_38) {
LAB_00047562:
      local_40 = iVar1;
    }
  }
  else {
    local_40 = local_30;
    iVar1 = local_28;
    if (local_30 <= local_28) goto LAB_00047562;
  }
  param_1[2] = local_40 + -1;
  iVar1 = local_3c;
  if (local_34 <= local_3c) {
    iVar1 = local_34;
  }
  iVar2 = local_2c;
  if (local_24 <= local_2c) {
    iVar2 = local_24;
  }
  if (iVar1 < iVar2) {
    iVar1 = local_3c;
    iVar2 = local_34;
    if (local_34 <= local_3c) {
LAB_00047592:
      iVar1 = iVar2;
    }
  }
  else {
    iVar1 = local_2c;
    iVar2 = local_24;
    if (local_24 <= local_2c) goto LAB_00047592;
  }
  param_1[1] = iVar1;
  iVar1 = local_3c;
  if (local_3c <= local_34) {
    iVar1 = local_34;
  }
  iVar2 = local_2c;
  if (local_2c <= local_24) {
    iVar2 = local_24;
  }
  if (iVar2 < iVar1) {
    iVar1 = local_34;
    if (local_34 < local_3c) goto LAB_000475c2;
  }
  else {
    local_3c = local_2c;
    iVar1 = local_24;
    if (local_24 < local_2c) goto LAB_000475c2;
  }
  local_3c = iVar1;
LAB_000475c2:
  param_1[3] = local_3c + -1;
  return;
}

