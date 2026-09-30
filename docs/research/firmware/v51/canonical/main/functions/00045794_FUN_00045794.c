/* Address: 00045794; name: FUN_00045794; body bytes: 900 */

void FUN_00045794(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,int param_5,
                 undefined4 param_6,int param_7,undefined4 param_8,int param_9,int param_10)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  uint local_b0;
  undefined4 local_ac;
  uint uStack_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  uint local_98;
  int local_94;
  uint local_90;
  uint local_7c;
  int local_74;
  undefined1 auStack_6c [16];
  int local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 uStack_34;
  int *piStack_30;
  undefined4 local_2c;
  int local_28;
  
  local_4c = -*(int *)(param_7 + 0x2c);
  local_54 = *(undefined4 *)(param_7 + 0x30);
  local_50 = *(undefined4 *)(param_7 + 0x34);
  local_40 = *(int *)(param_7 + 0x40);
  local_3c = *(int *)(param_7 + 0x44);
  iVar8 = local_4c % 10;
  sVar1 = (short)(local_4c / 10);
  uStack_34 = param_1;
  piStack_30 = param_2;
  local_2c = param_3;
  local_28 = param_4;
  iVar2 = thunk_FUN_00052d12((int)sVar1);
  local_c0 = thunk_FUN_00052d12((int)(short)(sVar1 + 1));
  iVar3 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
  iVar4 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5b));
  local_5c = (local_c0 * iVar8 + (10 - iVar8) * iVar2) / 10 >> 5;
  local_58 = (iVar4 * iVar8 + iVar3 * (10 - iVar8)) / 10 >> 5;
  local_48 = local_40 << 8;
  local_44 = local_3c << 8;
  iVar2 = FUN_0003db28(param_2);
  iVar3 = FUN_0003db0a(param_2);
  local_9c = iVar2;
  if (param_9 == 6) {
    if (*(byte *)(param_7 + 0x4b) < 2) {
      iVar4 = 2;
    }
    else {
      iVar4 = 4;
    }
    iVar4 = iVar2 * iVar4;
  }
  else {
    if (param_9 != 0xf) {
      if (param_9 == 0x14) {
        iVar4 = iVar2 << 1;
      }
      else {
        iVar4 = FUN_0004034e(param_9);
        iVar4 = iVar4 * iVar2;
        if ((param_9 != 0x12) && (param_9 != 0x14)) goto LAB_0004587e;
      }
      local_90 = iVar4 * iVar3 + param_10;
      goto LAB_00045880;
    }
    iVar4 = FUN_0004034e(0x10);
    iVar4 = iVar4 * iVar2;
  }
LAB_0004587e:
  local_90 = 0;
LAB_00045880:
  local_98 = (*(ushort *)(param_7 + 0x4c) & 0x1fff) >> 0xc;
  local_7c = (uint)(*(int *)(param_7 + 0x2c) != 0);
  local_94 = 0;
  local_74 = 0;
  local_a0 = 0;
  local_a4 = 0;
  if (local_7c == 0) {
    iVar8 = *(int *)(param_7 + 0x40) +
            (*(int *)(param_7 + 0x30) * ((local_28 - *(int *)(param_7 + 0x40)) + -1) >> 8);
    iVar7 = *(int *)(param_7 + 0x44) +
            (*(int *)(param_7 + 0x34) * ((param_5 - *(int *)(param_7 + 0x44)) + -1) >> 8);
    iVar6 = *param_2;
    if (iVar8 < *param_2) {
      iVar6 = iVar8;
    }
    if (param_2[2] <= iVar8) {
      iVar8 = param_2[2];
    }
    iVar5 = param_2[1];
    if (iVar7 < param_2[1]) {
      iVar5 = iVar7;
    }
    if (param_2[3] <= iVar7) {
      iVar7 = param_2[3];
    }
    FUN_00063fb0(auStack_6c,iVar6,iVar5,&local_bc,&local_b8);
    FUN_00063fb0(auStack_6c,iVar8,iVar7,&local_b4,&local_b0);
    if (1 < iVar2) {
      local_a4 = ((local_b4 - local_bc) * 0x100) / (iVar2 + -1);
    }
    if (1 < iVar3) {
      local_a0 = (int)((local_b0 - local_b8) * 0x100) / (iVar3 + -1);
    }
    local_94 = local_bc + 0x80;
    local_74 = local_b8 + 0x80;
  }
  iVar8 = 0;
  do {
    if (iVar3 <= iVar8) {
      return;
    }
    if (local_7c == 0) {
      iVar6 = local_74 + (iVar8 * local_a0 >> 8);
      iVar7 = 0;
    }
    else {
      FUN_00063fb0(auStack_6c,*param_2,param_2[1] + iVar8,&local_b4,&local_c0);
      FUN_00063fb0(auStack_6c,param_2[2],param_2[1] + iVar8,&local_bc,&local_b8);
      iVar7 = 0;
      local_a4 = 0;
      if (1 < iVar2) {
        local_a4 = ((local_bc - local_b4) * 0x100) / (iVar2 + -1);
        iVar7 = ((local_b8 - local_c0) * 0x100) / (iVar2 + -1);
      }
      local_94 = local_b4 + 0x80;
      iVar6 = local_c0 + 0x80;
    }
    if (param_9 == 0x10) {
      local_b4 = param_10;
      local_b0 = local_98;
      local_c0 = local_a4;
      local_bc = iVar7;
      local_b8 = iVar2;
      FUN_000639d8(local_2c,local_28,param_5,param_6,local_94,iVar6);
    }
    else if (param_9 < 0x11) {
      if (param_9 == 6) {
        if (*(byte *)(param_7 + 0x4b) < 2) {
          local_b4 = param_10;
          local_b0 = local_98;
          local_c0 = local_a4;
          local_bc = iVar7;
          local_b8 = iVar2;
          FUN_00063bae(local_2c,local_28,param_5,param_6,local_94,iVar6);
        }
        else {
          local_b4 = param_10;
          local_b0 = local_98;
          local_c0 = local_a4;
          local_bc = iVar7;
          local_b8 = iVar2;
          FUN_00063d18(local_2c,local_28,param_5,param_6,local_94,iVar6);
        }
      }
      else if (param_9 == 0xe) {
        local_b4 = param_10;
        local_b0 = local_98;
        local_c0 = local_a4;
        local_bc = iVar7;
        local_b8 = iVar2;
        FUN_00063874(local_2c,local_28,param_5,param_6,local_94,iVar6);
      }
      else if (param_9 == 0xf) {
        local_ac = 3;
        goto LAB_00045a0e;
      }
    }
    else if (param_9 == 0x11) {
      local_ac = 4;
LAB_00045a0e:
      local_b0 = local_98;
      local_b4 = param_10;
      local_c0 = local_a4;
      local_bc = iVar7;
      local_b8 = iVar2;
      FUN_0006423e(local_2c,local_28,param_5,param_6,local_94,iVar6);
    }
    else {
      if (param_9 == 0x12) {
        local_ac = 0;
      }
      else {
        if (param_9 != 0x14) goto LAB_00045afa;
        local_ac = 1;
      }
      local_b4 = param_10;
      local_b0 = local_90;
      uStack_a8 = local_98;
      local_c0 = local_a4;
      local_bc = iVar7;
      local_b8 = iVar2;
      FUN_0006405a(local_2c,local_28,param_5,param_6,local_94,iVar6);
    }
LAB_00045afa:
    param_10 = param_10 + iVar4;
    if (local_90 != 0) {
      local_90 = local_9c + local_90;
    }
    iVar8 = iVar8 + 1;
  } while( true );
}

