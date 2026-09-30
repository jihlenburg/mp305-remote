/* Address: 0002ce94; name: FUN_0002ce94; body bytes: 750 */

void FUN_0002ce94(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int local_190;
  uint local_18c;
  int local_178;
  int local_170;
  int local_168;
  int local_164;
  int local_160;
  int local_15c;
  undefined1 *local_158;
  undefined1 *local_154;
  undefined1 *local_150;
  undefined1 *local_14c;
  int *local_144 [5];
  undefined1 local_130;
  undefined2 local_12f;
  undefined1 local_12d;
  int local_12c;
  undefined1 local_128;
  int *local_124;
  undefined1 auStack_118 [56];
  undefined1 auStack_e0 [56];
  undefined1 auStack_a8 [56];
  undefined1 auStack_70 [68];
  int local_2c;
  int iStack_28;
  
  iVar9 = param_2 + 0x1c;
  local_2c = param_1;
  iStack_28 = param_2;
  if (*(float *)(param_2 + 0x28) <= *(float *)(param_2 + 0x20)) {
    FUN_0004f24c(&local_190,param_2 + 0x24);
  }
  else {
    FUN_0004f24c(&local_190,iVar9);
    iVar9 = param_2 + 0x24;
  }
  uVar4 = local_18c;
  iVar1 = local_190;
  FUN_0004f24c(&local_190,iVar9);
  uVar5 = local_18c;
  iVar11 = local_190;
  iVar10 = local_18c;
  iVar12 = local_190 - iVar1;
  iVar13 = local_18c - uVar4;
  iVar9 = iVar12;
  if (iVar12 < 1) {
    iVar9 = -iVar12;
  }
  iVar6 = iVar13;
  if (iVar13 < 1) {
    iVar6 = -iVar13;
  }
  if (iVar6 < iVar9 == 0) {
    iVar8 = iVar12;
    if (iVar12 < 1) {
      iVar8 = -iVar12;
    }
    iVar8 = iVar8 << 5;
    iVar2 = iVar13;
    if (iVar13 < 1) {
      iVar2 = -iVar13;
    }
  }
  else {
    iVar8 = iVar13;
    if (iVar13 < 1) {
      iVar8 = -iVar13;
    }
    iVar8 = iVar8 << 5;
    iVar2 = iVar12;
    if (iVar12 < 1) {
      iVar2 = -iVar12;
    }
  }
  iVar8 = *(int *)(param_2 + 0x30) * (uint)(byte)(&DAT_00082cfc)[iVar8 / iVar2] + 0x3f;
  uVar3 = iVar8 >> 7;
  iVar8 = iVar8 >> 8;
  local_178 = (uVar3 & 1) + iVar8;
  local_168 = local_190;
  if (iVar1 < local_190) {
    local_168 = iVar1;
  }
  local_168 = local_168 - uVar3;
  if (local_190 < iVar1) {
    local_190 = iVar1;
  }
  local_160 = local_190 + uVar3;
  uVar7 = local_18c;
  if ((int)uVar4 < (int)local_18c) {
    uVar7 = uVar4;
  }
  local_164 = uVar7 - uVar3;
  if ((int)local_18c < (int)uVar4) {
    local_18c = uVar4;
  }
  local_15c = uVar3 + local_18c;
  local_18c = (uint)(iVar6 < iVar9);
  iVar9 = FUN_0003db4c(&local_168,&local_168,*(undefined4 *)(local_2c + 8));
  if (iVar9 != 0) {
    FUN_0001049c(&local_158,0x14);
    local_158 = auStack_118;
    local_154 = auStack_e0;
    if (local_18c == 0) {
      local_190 = uVar5;
      local_18c = 0;
      FUN_000453c0(auStack_118,iVar1 + local_178,uVar4,iVar11 + local_178);
      iVar9 = iVar11 - iVar8;
      iVar8 = iVar1 - iVar8;
      uVar3 = uVar4;
      local_190 = iVar10;
    }
    else {
      if (iVar12 < 1) {
        local_190 = local_178 + uVar5;
        local_18c = 0;
        FUN_000453c0(auStack_118,iVar1,uVar4 + local_178,iVar11);
        iVar9 = -iVar8;
      }
      else {
        local_190 = uVar5 - iVar8;
        local_18c = 0;
        FUN_000453c0(auStack_118,iVar1,uVar4 - iVar8,iVar11);
        iVar9 = local_178;
      }
      local_190 = iVar9 + uVar5;
      iVar8 = iVar1;
      uVar3 = uVar4 + iVar9;
      iVar9 = iVar11;
    }
    local_18c = 1;
    FUN_000453c0(auStack_e0,iVar8,uVar3,iVar9);
    if (-1 < (int)((uint)*(byte *)(param_2 + 0x3d) << 0x1b)) {
      local_190 = uVar4 + iVar12;
      local_18c = 3;
      FUN_000453c0(auStack_a8,iVar1,uVar4,iVar1 - iVar13);
      local_190 = uVar5 + iVar12;
      local_18c = 2;
      FUN_000453c0(auStack_70,iVar11,uVar5,iVar11 - iVar13);
      local_150 = auStack_a8;
      local_14c = auStack_70;
    }
    iVar9 = FUN_0003db28(&local_168);
    FUN_0004f604();
    uVar4 = FUN_000408b0();
    uVar5 = FUN_0003db14(&local_168);
    if (uVar5 < uVar4) {
      uVar4 = FUN_0003db14(&local_168);
    }
    iVar10 = FUN_0004a318(uVar4);
    iVar1 = local_15c;
    local_15c = local_164;
    iVar12 = 0;
    FUN_0004a57a(iVar10,0xff,uVar4);
    FUN_0004a5fa(local_144,0x2c);
    local_144[0] = &local_168;
    local_12f = *(undefined2 *)(param_2 + 0x2c);
    local_12d = *(undefined1 *)(param_2 + 0x2e);
    local_130 = *(undefined1 *)(param_2 + 0x3c);
    local_12c = iVar10;
    local_124 = local_144[0];
    for (iVar11 = local_164; iVar11 <= iVar1; iVar11 = iVar11 + 1) {
      local_170 = iVar10 + iVar12;
      local_190 = iVar9;
      iVar13 = FUN_000452b4(&local_158,local_170,local_168,iVar11);
      local_128 = (undefined1)iVar13;
      if (iVar13 == 0) {
        FUN_0004a5fa(local_170,iVar9);
      }
      iVar12 = iVar12 + iVar9;
      if ((uint)(iVar12 + iVar9) < uVar4) {
        local_15c = local_15c + 1;
      }
      else {
        local_128 = 2;
        FUN_0004337c(local_2c,local_144);
        iVar12 = 0;
        local_164 = local_15c + 1;
        local_15c = local_164;
        FUN_0004a57a(iVar10,0xff,uVar4);
      }
    }
    if (local_164 != local_15c) {
      local_15c = local_15c + -1;
      local_128 = 2;
      FUN_0004337c(local_2c,local_144);
    }
    FUN_00046bec(iVar10);
    FUN_00045330(auStack_118);
    FUN_00045330(auStack_e0);
    if (-1 < (int)((uint)*(byte *)(param_2 + 0x3d) << 0x1b)) {
      FUN_00045330(auStack_a8);
      FUN_00045330(auStack_70);
    }
  }
  return;
}

