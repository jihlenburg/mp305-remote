/* Address: 0002cd3c; name: FUN_0002cd3c; body bytes: 344 */

void FUN_0002cd3c(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined1 *local_58 [5];
  undefined1 local_44;
  undefined2 local_43;
  undefined1 local_41;
  int local_40;
  undefined1 local_3c;
  undefined1 *local_38;
  int local_2c;
  int iStack_28;
  
  fVar12 = *(float *)(param_2 + 0x1c);
  fVar11 = *(float *)(param_2 + 0x24);
  uVar2 = *(int *)(param_2 + 0x30) - 1;
  local_5c = (int)uVar2 >> 1;
  fVar13 = fVar11;
  if (fVar12 < fVar11) {
    fVar13 = fVar12;
  }
  local_68 = (int)fVar13;
  if (fVar11 < fVar12) {
    fVar11 = fVar12;
  }
  local_60 = (int)fVar11 + -1;
  local_64 = (int)*(float *)(param_2 + 0x20) - ((uVar2 & 1) + local_5c);
  local_5c = (int)*(float *)(param_2 + 0x20) + local_5c;
  local_2c = param_1;
  iStack_28 = param_2;
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
      iVar4 = FUN_0003db28(&local_68);
      iVar3 = local_5c;
      local_5c = local_64;
      iVar5 = *(int *)(param_2 + 0x38) + *(int *)(param_2 + 0x34);
      iVar10 = local_68 - iVar5 * (local_68 / iVar5);
      iVar6 = FUN_0004a318(iVar4);
      local_3c = 2;
      local_40 = iVar6;
      local_38 = (undefined1 *)&local_68;
      for (iVar5 = local_64; iVar5 <= iVar3; iVar5 = iVar5 + 1) {
        FUN_0004a57a(iVar6,0xff,iVar4);
        iVar7 = iVar10;
        for (iVar8 = 0; iVar8 < iVar4; iVar8 = iVar8 + 1) {
          iVar9 = *(int *)(param_2 + 0x34);
          if (iVar9 < iVar7) {
            if (iVar9 + *(int *)(param_2 + 0x38) < iVar7) {
              iVar7 = 0;
            }
            else {
              *(undefined1 *)(iVar6 + iVar8) = 0;
            }
          }
          else {
            iVar9 = (int)(short)((short)iVar9 - (short)iVar7);
            iVar8 = iVar8 + iVar9;
            iVar7 = iVar7 + iVar9;
          }
          iVar7 = iVar7 + 1;
          local_3c = 2;
        }
        FUN_0004337c(local_2c,local_58);
        local_64 = local_64 + 1;
        local_5c = local_5c + 1;
      }
      FUN_00046bec(iVar6);
    }
    else {
      local_58[0] = (undefined1 *)&local_68;
      FUN_0004337c(local_2c,local_58);
    }
  }
  return;
}

