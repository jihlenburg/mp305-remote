/* Address: 0002d188; name: FUN_0002d188; body bytes: 326 */

void FUN_0002d188(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined1 *local_58 [5];
  undefined1 local_44;
  undefined2 local_43;
  undefined1 local_41;
  undefined4 local_40;
  undefined1 local_3c;
  undefined1 *local_38;
  undefined4 local_2c;
  
  uVar2 = *(int *)(param_2 + 0x30) - 1;
  local_60 = (int)uVar2 >> 1;
  local_68 = (int)*(float *)(param_2 + 0x1c) - ((uVar2 & 1) + local_60);
  local_60 = (int)*(float *)(param_2 + 0x1c) + local_60;
  fVar7 = *(float *)(param_2 + 0x28);
  if (*(float *)(param_2 + 0x20) < *(float *)(param_2 + 0x28)) {
    fVar7 = *(float *)(param_2 + 0x20);
  }
  local_64 = (int)fVar7;
  fVar7 = *(float *)(param_2 + 0x28);
  if (*(float *)(param_2 + 0x28) < *(float *)(param_2 + 0x20)) {
    fVar7 = *(float *)(param_2 + 0x20);
  }
  local_5c = (int)fVar7 + -1;
  iVar3 = FUN_0003db4c(&local_68,&local_68,*(undefined4 *)(param_1 + 8));
  if (iVar3 != 0) {
    if ((*(int *)(param_2 + 0x38) == 0) || (*(int *)(param_2 + 0x34) == 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    FUN_0004a5fa(local_58,0x2c);
    local_43 = *(undefined2 *)(param_2 + 0x2c);
    local_41 = *(undefined1 *)(param_2 + 0x2e);
    local_44 = *(undefined1 *)(param_2 + 0x3c);
    if (bVar1) {
      local_58[0] = (undefined1 *)&local_68;
      local_2c = FUN_0003db28(&local_68);
      iVar3 = local_5c;
      local_5c = local_64;
      uVar4 = FUN_0004a318(local_2c);
      local_3c = 2;
      iVar5 = *(int *)(param_2 + 0x38) + *(int *)(param_2 + 0x34);
      iVar6 = local_64 - iVar5 * (local_64 / iVar5);
      local_40 = uVar4;
      local_38 = (undefined1 *)&local_68;
      for (iVar5 = local_64; iVar5 <= iVar3; iVar5 = iVar5 + 1) {
        FUN_0004a57a(uVar4,0xff,local_2c);
        local_3c = iVar6 <= *(int *)(param_2 + 0x34);
        if (*(int *)(param_2 + 0x38) + *(int *)(param_2 + 0x34) <= iVar6) {
          iVar6 = 0;
        }
        iVar6 = iVar6 + 1;
        FUN_0004337c(param_1,local_58);
        local_64 = local_64 + 1;
        local_5c = local_5c + 1;
      }
      FUN_00046bec(uVar4);
    }
    else {
      local_58[0] = (undefined1 *)&local_68;
      FUN_0004337c(param_1,local_58);
    }
  }
  return;
}

