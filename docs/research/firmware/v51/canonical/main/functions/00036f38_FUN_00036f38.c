/* Address: 00036f38; name: FUN_00036f38; body bytes: 362 */

uint FUN_00036f38(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int local_78;
  int local_74;
  int local_58;
  int local_54;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int iStack_2c;
  undefined4 local_28;
  
  iStack_2c = param_1;
  local_28 = param_2;
  FUN_0004bb3c(param_1,&local_78);
  local_54 = FUN_0004ccf8(param_1);
  local_58 = FUN_0004bbec(param_1);
  iVar1 = FUN_0004c852(param_1,0);
  iVar2 = FUN_0004c89a(param_1,0);
  iVar3 = FUN_0004c8ee(param_1,0);
  iVar4 = FUN_0004c7f2(param_1,0);
  uVar5 = FUN_0004c8ca(param_1,0);
  uVar6 = FUN_0004c822(param_1,0);
  iVar7 = (uVar6 & 1) + (int)uVar6 / 2 + 1;
  iVar8 = (uVar5 & 1) + (int)uVar5 / 2 + 1;
  if (0xc < iVar8) {
    iVar8 = 0xd;
  }
  if (0xc < iVar7) {
    iVar7 = 0xd;
  }
  if (0xc < iVar2) {
    iVar2 = 0xd;
  }
  if (0xc < iVar3) {
    iVar3 = 0xd;
  }
  if (0xc < iVar4) {
    iVar4 = 0xd;
  }
  for (uVar5 = 0; uVar5 < *(uint *)(param_1 + 0x38); uVar5 = uVar5 + 1) {
    FUN_0003d9da(&local_40,*(int *)(param_1 + 0x30) + uVar5 * 0x10);
    iVar9 = iVar7;
    if ((local_40 <= iVar1) && (iVar9 = iVar1, 0xc < iVar1)) {
      iVar9 = 0xd;
    }
    local_40 = local_40 + (local_78 - iVar9);
    iVar9 = iVar8;
    if ((local_3c <= iVar3) && (iVar9 = iVar3, 0xc < iVar3)) {
      iVar9 = 0xd;
    }
    local_3c = (local_74 - iVar9) + local_3c;
    if (local_38 < (local_54 - iVar2) + -2) {
      local_38 = local_78 + local_38 + iVar7;
    }
    else {
      iVar9 = iVar2;
      if (0xc < iVar2) {
        iVar9 = 0xd;
      }
      local_38 = local_38 + local_78 + iVar9;
    }
    iVar9 = iVar8;
    if (((local_58 - iVar4) + -2 <= local_34) && (iVar9 = iVar4, 0xc < iVar4)) {
      iVar9 = 0xd;
    }
    local_34 = iVar9 + local_74 + local_34;
    iVar9 = FUN_0003dcb8(&local_40,local_28,0);
    if (iVar9 != 0) break;
  }
  if (*(uint *)(param_1 + 0x38) == uVar5) {
    uVar5 = 0xffff;
  }
  return uVar5;
}

