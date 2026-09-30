/* Address: 00029106; name: FUN_00029106; body bytes: 902 */

void FUN_00029106(int param_1,int *param_2,int *param_3,int param_4,undefined4 param_5,
                 undefined2 param_6,undefined1 param_7)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *local_fc [5];
  undefined1 local_e8;
  undefined2 local_e7;
  undefined4 local_e4;
  undefined1 local_e0;
  int *local_dc;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  undefined4 local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  undefined1 *local_8c;
  undefined1 *local_88;
  undefined4 local_84;
  undefined1 auStack_80 [36];
  undefined1 auStack_5c [40];
  int local_34;
  int *piStack_30;
  int *piStack_2c;
  int iStack_28;
  
  local_34 = param_1;
  piStack_30 = param_2;
  piStack_2c = param_3;
  iStack_28 = param_4;
  iVar4 = FUN_0003db4c(&local_9c,param_2,*(undefined4 *)(param_1 + 8));
  if (iVar4 == 0) {
    return;
  }
  local_a0 = FUN_0003db28(&local_9c);
  FUN_0004a57a(local_fc,0,0x2c);
  uVar5 = FUN_0004a318(local_a0);
  local_8c = (undefined1 *)0x0;
  local_88 = (undefined1 *)0x0;
  local_84 = 0;
  local_e4 = uVar5;
  FUN_000454e8(auStack_80,param_3,param_5,1);
  local_8c = auStack_80;
  if (0 < param_4) {
    FUN_000454e8(auStack_5c,param_2,param_4,0);
    local_88 = auStack_5c;
  }
  local_fc[0] = &local_d0;
  local_e7 = param_6;
  local_e8 = param_7;
  local_b0 = *param_3;
  if (*param_3 < *param_2 + param_4) {
    local_b0 = *param_2 + param_4;
  }
  local_a8 = param_2[2] - param_4;
  if (param_3[2] <= param_2[2] - param_4) {
    local_a8 = param_3[2];
  }
  local_ac = param_3[1];
  if (param_3[1] < param_2[1] + param_4) {
    local_ac = param_2[1] + param_4;
  }
  local_a4 = param_3[3];
  if (param_2[3] - param_4 < param_3[3]) {
    local_a4 = param_2[3] - param_4;
  }
  local_dc = local_fc[0];
  iVar4 = FUN_0003db28(&local_b0);
  iVar6 = param_2[1];
  iVar8 = param_3[1];
  bVar1 = param_3[3] <= param_2[3];
  iVar7 = *param_2;
  iVar9 = *param_3;
  bVar2 = param_3[2] <= param_2[2];
  bVar3 = true;
  if ((((iVar7 <= iVar9 && bVar2) && iVar6 <= iVar8) && bVar1) && (iVar4 < 0x32)) {
    bVar3 = false;
  }
  local_e0 = 1;
  if ((bool)(iVar6 <= iVar8 & bVar3)) {
    local_d0 = local_b0;
    local_c8 = local_a8;
    local_cc = param_2[1];
    local_c4 = param_3[1] + -1;
    FUN_0004337c(local_34,local_fc);
  }
  if ((bool)(bVar1 & bVar3)) {
    local_d0 = local_b0;
    local_c8 = local_a8;
    local_cc = param_3[3] + 1;
    local_c4 = param_2[3];
    FUN_0004337c(local_34,local_fc);
  }
  if (*param_3 < param_3[2]) {
    if (iVar7 <= iVar9) {
LAB_0002927e:
      local_d0 = *param_2;
      local_c8 = *param_3 + -1;
      local_cc = local_ac;
      local_c4 = local_a4;
      FUN_0004337c(local_34,local_fc);
    }
LAB_00029298:
    if (!bVar2) goto LAB_000292b8;
    local_d0 = param_3[2] + 1;
  }
  else {
    if (iVar9 < iVar7) goto LAB_00029298;
    if (!bVar2) goto LAB_0002927e;
    local_d0 = *param_2;
  }
  local_c8 = param_2[2];
  local_cc = local_ac;
  local_c4 = local_a4;
  FUN_0004337c(local_34,local_fc);
LAB_000292b8:
  local_d0 = local_9c;
  if (bVar3) {
    local_c8 = local_94;
    if (local_b0 + -1 <= local_94) {
      local_c8 = local_b0 + -1;
    }
    iVar4 = FUN_0003db28(&local_d0);
    if (0 < iVar4) {
      iVar10 = local_98;
      if (iVar7 <= iVar9 || iVar6 <= iVar8) {
        for (; iVar10 < local_ac; iVar10 = iVar10 + 1) {
          local_cc = iVar10;
          local_c4 = iVar10;
          FUN_0004a57a(uVar5,0xff,iVar4);
          local_e0 = FUN_000452b4(&local_8c,uVar5,local_d0,iVar10,iVar4);
          FUN_0004337c(local_34,local_fc);
        }
      }
      iVar10 = local_a4;
      if (iVar7 <= iVar9 || bVar1) {
        while (iVar10 = iVar10 + 1, iVar10 <= local_90) {
          local_cc = iVar10;
          local_c4 = iVar10;
          FUN_0004a57a(uVar5,0xff,iVar4);
          local_e0 = FUN_000452b4(&local_8c,uVar5,local_d0,iVar10,iVar4);
          FUN_0004337c(local_34,local_fc);
        }
      }
    }
    if (local_9c <= local_a8 + 1) {
      local_9c = local_a8 + 1;
    }
    local_c8 = local_94;
    local_d0 = local_9c;
    iVar4 = FUN_0003db28(&local_d0);
    if (0 < iVar4) {
      iVar7 = local_98;
      if (bVar2 || iVar6 <= iVar8) {
        for (; iVar7 < local_ac; iVar7 = iVar7 + 1) {
          local_cc = iVar7;
          local_c4 = iVar7;
          FUN_0004a57a(uVar5,0xff,iVar4);
          local_e0 = FUN_000452b4(&local_8c,uVar5,local_d0,iVar7,iVar4);
          FUN_0004337c(local_34,local_fc);
        }
      }
      iVar6 = local_a4;
      if (bVar2 || bVar1) {
        while (iVar6 = iVar6 + 1, iVar6 <= local_90) {
          local_cc = iVar6;
          local_c4 = iVar6;
          FUN_0004a57a(uVar5,0xff,iVar4);
          local_e0 = FUN_000452b4(&local_8c,uVar5,local_d0,iVar6,iVar4);
          FUN_0004337c(local_34,local_fc);
        }
      }
    }
  }
  else {
    local_c8 = local_94;
    iVar4 = param_3[1] - param_2[1];
    if (param_3[1] - param_2[1] < param_4) {
      iVar4 = param_4;
    }
    for (iVar6 = 0; iVar6 < iVar4; iVar6 = iVar6 + 1) {
      iVar7 = param_2[1] + iVar6;
      iVar8 = param_2[3] - iVar6;
      if ((local_98 <= iVar7) || (iVar8 <= local_90)) {
        FUN_0004a57a(uVar5,0xff,local_a0);
        local_e0 = FUN_000452b4(&local_8c,uVar5,local_d0,iVar7,local_a0);
        if (local_98 <= iVar7) {
          local_cc = iVar7;
          local_c4 = iVar7;
          FUN_0004337c(local_34,local_fc);
        }
        if (iVar8 <= local_90) {
          local_cc = iVar8;
          local_c4 = iVar8;
          FUN_0004337c(local_34,local_fc);
        }
      }
    }
  }
  FUN_00045330(auStack_80);
  if (0 < param_4) {
    FUN_00045330(auStack_5c);
  }
  FUN_00046bec(uVar5);
  return;
}

