/* Address: 0002c234; name: FUN_0002c234; body bytes: 1100 */

void FUN_0002c234(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  undefined1 *puVar17;
  int *piVar18;
  int *piVar19;
  int *piVar20;
  bool bVar21;
  int local_264;
  int local_260;
  int local_25c;
  int local_258;
  int local_254;
  int local_24c [2];
  int local_244;
  code *local_234;
  undefined4 local_230;
  int local_220;
  undefined1 auStack_1e0 [28];
  int local_1c4;
  byte local_1b1;
  int local_1b0;
  undefined1 local_198;
  undefined1 local_188;
  undefined1 local_174;
  undefined1 auStack_170 [28];
  undefined4 local_154;
  undefined1 local_150;
  undefined1 local_135;
  undefined1 local_128;
  undefined1 local_118;
  undefined1 local_104;
  int local_fc;
  int local_f8;
  int local_f4;
  undefined1 auStack_f0 [32];
  undefined1 local_d0;
  undefined1 local_b5;
  undefined1 local_a8;
  undefined1 local_98;
  int local_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  undefined1 auStack_5c [28];
  int local_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  undefined4 local_2c;
  
  iVar6 = FUN_00046698();
  local_2c = FUN_00046718(param_1);
  FUN_0004bb3c(iVar6,&local_264);
  uVar7 = FUN_0004c924(iVar6,0,0x68);
  uVar8 = FUN_0004c924(iVar6,0,0x69);
  FUN_0003db32(&local_264,uVar7,uVar8);
  local_244 = FUN_0003db28(&local_264);
  local_24c[0] = FUN_0003db0a(&local_264);
  iVar9 = *(int *)(iVar6 + 0x34) - *(int *)(iVar6 + 0x30);
  if (iVar9 == 0) {
    iVar9 = 1;
  }
  bVar2 = false;
  uVar10 = (*(byte *)(iVar6 + 0x70) & 0x3f) >> 3;
  if (uVar10 == 1) {
LAB_0002c2ae:
    bVar2 = true;
  }
  else if (uVar10 != 2) {
    if (local_24c[0] <= local_244) goto LAB_0002c2ae;
    bVar2 = false;
  }
  local_220 = FUN_0003e1fc(iVar6);
  local_f4 = FUN_0004c84c(iVar6,0);
  local_f8 = FUN_0004c894(iVar6,0);
  local_fc = FUN_0004c8e8(iVar6,0);
  local_254 = FUN_0004c7ec(iVar6,0);
  piVar11 = (int *)(iVar6 + 0x3c);
  FUN_0003d9c8(piVar11,&local_264);
  *(int *)(iVar6 + 0x3c) = *(int *)(iVar6 + 0x3c) + local_f4;
  *(int *)(iVar6 + 0x44) = *(int *)(iVar6 + 0x44) - local_f8;
  *(int *)(iVar6 + 0x40) = *(int *)(iVar6 + 0x40) + local_fc;
  *(int *)(iVar6 + 0x48) = *(int *)(iVar6 + 0x48) - local_254;
  if (bVar2) {
    iVar12 = FUN_0003db0a();
    if (iVar12 < 4) {
      iVar12 = local_24c[0] / 2 + -2 + *(int *)(iVar6 + 0x18);
      *(int *)(iVar6 + 0x40) = iVar12;
      *(int *)(iVar6 + 0x48) = iVar12 + 4;
    }
  }
  else {
    iVar12 = FUN_0003db28(piVar11);
    if (iVar12 < 4) {
      iVar12 = local_244 / 2 + -2 + *(int *)(iVar6 + 0x14);
      *(int *)(iVar6 + 0x3c) = iVar12;
      *(int *)(iVar6 + 0x44) = iVar12 + 4;
    }
  }
  iVar13 = FUN_0003db28(piVar11);
  iVar12 = FUN_0003db0a(piVar11);
  if (bVar2) {
    iVar1 = 0x44;
    local_234 = FUN_0003db28;
    piVar20 = piVar11;
    iVar12 = iVar13;
  }
  else {
    local_234 = FUN_0003db0a;
    piVar20 = (int *)(iVar6 + 0x40);
    iVar1 = 0x48;
  }
  if (*(int *)(iVar6 + 0x6c) == -1) {
    iVar13 = ((*(int *)(iVar6 + 0x38) - *(int *)(iVar6 + 0x30)) * iVar12) / iVar9;
  }
  else {
    iVar13 = ((*(int *)(iVar6 + 100) - *(int *)(iVar6 + 0x30)) * iVar12) / iVar9;
    iVar14 = *(int *)(iVar6 + 0x6c) *
             (((*(int *)(iVar6 + 0x68) - *(int *)(iVar6 + 0x30)) * iVar12) / iVar9 - iVar13);
    iVar13 = iVar13 + ((int)(iVar14 + ((uint)(iVar14 >> 0x1f) >> 0x18)) >> 8);
  }
  if (*(int *)(iVar6 + 0x5c) == -1) {
    iVar14 = ((*(int *)(iVar6 + 0x2c) - *(int *)(iVar6 + 0x30)) * iVar12) / iVar9;
  }
  else {
    iVar14 = ((*(int *)(iVar6 + 0x54) - *(int *)(iVar6 + 0x30)) * iVar12) / iVar9;
    iVar15 = *(int *)(iVar6 + 0x5c) *
             (((*(int *)(iVar6 + 0x58) - *(int *)(iVar6 + 0x30)) * iVar12) / iVar9 - iVar14);
    iVar14 = iVar14 + ((int)(iVar15 + ((uint)(iVar15 >> 0x1f) >> 0x18)) >> 8);
  }
  cVar4 = FUN_0004c924(iVar6,0,0x27);
  if ((!bVar2) || (cVar5 = '\x01', cVar4 != '\x01')) {
    cVar5 = '\0';
  }
  bVar21 = *(char *)(iVar6 + 0x4c) == cVar5;
  piVar19 = (int *)(iVar6 + iVar1);
  if (!bVar21) {
    iVar14 = -iVar14;
    iVar13 = -iVar13;
    piVar19 = piVar20;
    piVar20 = (int *)(iVar6 + iVar1);
  }
  if (bVar2) {
    *piVar19 = *piVar20 + iVar14;
    *piVar20 = *piVar20 + iVar13;
  }
  else {
    *piVar20 = (*piVar19 - iVar14) + 1;
    *piVar19 = *piVar19 - iVar13;
  }
  if (local_220 == 0) {
    iVar9 = (*local_234)(piVar11);
    if (iVar9 < 2) {
      FUN_0004e5a6(iVar6,0x1f,0);
      return;
    }
  }
  else {
    iVar9 = (-*(int *)(iVar6 + 0x30) * iVar12) / iVar9;
    piVar16 = piVar19;
    piVar18 = piVar19;
    if (bVar2) {
      if (bVar21) {
        iVar9 = iVar9 + *piVar20;
        piVar18 = piVar20;
      }
      else {
        iVar9 = (*piVar20 - iVar9) + 1;
        piVar16 = piVar20;
      }
      iVar12 = *piVar19;
    }
    else {
      if (bVar21) {
        iVar9 = (*piVar19 - iVar9) + 1;
        piVar18 = piVar20;
      }
      else {
        iVar9 = iVar9 + *piVar19;
        piVar16 = piVar20;
      }
      iVar12 = *piVar20;
    }
    if (iVar9 < iVar12) {
      *piVar16 = iVar12;
      *piVar18 = iVar9;
    }
    else {
      *piVar18 = iVar12;
      *piVar16 = iVar9;
    }
  }
  FUN_0003d9c8(&local_80,piVar11);
  FUN_00042ec4(auStack_1e0);
  FUN_0004d0bc(iVar6,0x20000,auStack_1e0);
  iVar9 = FUN_0004c924(iVar6,0,0xc);
  iVar6 = local_244;
  if (local_24c[0] <= local_244) {
    iVar6 = local_24c[0];
  }
  if (iVar6 >> 1 < iVar9) {
    iVar9 = iVar6 >> 1;
  }
  iVar6 = FUN_0003db28(piVar11);
  iVar12 = FUN_0003db0a(piVar11);
  if (iVar6 < iVar12) {
    iVar6 = FUN_0003db28();
  }
  else {
    iVar6 = FUN_0003db0a(piVar11);
  }
  iVar12 = local_1c4;
  if (iVar6 >> 1 < local_1c4) {
    iVar12 = iVar6 >> 1;
  }
  bVar21 = false;
  if (bVar2) {
    if ((local_1b1 & 7) == 2) {
LAB_0002c53e:
      bVar21 = true;
    }
  }
  else if ((local_1b1 & 7) == 1) goto LAB_0002c53e;
  if (local_1b0 != 0) {
    bVar21 = true;
  }
  bVar3 = true;
  if ((((local_f4 < 0) || (local_f8 < 0)) || (local_fc < 0)) ||
     (((local_254 < 0 || (iVar9 <= iVar12)) ||
      (iVar6 = FUN_0003db8c(&local_80,&local_264,iVar9), iVar6 != 0)))) {
    bVar3 = false;
    if (!bVar21) {
      puVar17 = auStack_1e0;
      goto LAB_0002c672;
    }
    FUN_0001046a(auStack_f0,auStack_1e0,0x70);
    local_a8 = 0;
    local_b5 = 0;
    local_98 = 0;
    local_d0 = 0;
    FUN_00042a98(local_2c,auStack_f0,&local_80);
  }
  else {
    local_198 = 0;
    local_188 = 0;
  }
  local_174 = 0;
  FUN_0001046a(auStack_170,auStack_1e0,0x70);
  local_118 = 0;
  local_128 = 0;
  local_104 = 0;
  local_6c = local_80;
  local_68 = iStack_7c;
  local_64 = iStack_78;
  local_60 = iStack_74;
  if (bVar21) {
    if (bVar2) {
      local_6c = local_f4 + local_264;
      local_64 = local_25c - local_f8;
    }
    else {
      local_68 = local_fc + local_260;
      local_60 = local_258 - local_254;
    }
    local_154 = 0;
  }
  uVar7 = FUN_0004233c(local_2c,0x10,&local_6c);
  FUN_00042a98(uVar7,auStack_170,&local_6c);
  FUN_00042a4c(auStack_5c);
  if (bVar3) {
    local_40 = local_264;
    iStack_3c = local_260;
    iStack_38 = local_25c;
    iStack_34 = local_258;
    iStack_30 = iVar9;
    FUN_000429dc(uVar7,auStack_5c);
  }
  if (bVar21) {
    local_40 = local_80;
    iStack_3c = iStack_7c;
    iStack_38 = iStack_78;
    iStack_34 = iStack_74;
    iStack_30 = iVar12;
    FUN_000429dc(uVar7,auStack_5c);
  }
  FUN_00041b74(local_24c);
  local_230 = uVar7;
  FUN_00042244(local_2c,local_24c,&local_6c);
  FUN_0001046a(auStack_170,auStack_1e0,0x70);
  local_150 = 0;
  local_135 = 0;
  puVar17 = auStack_170;
LAB_0002c672:
  FUN_00042a98(local_2c,puVar17,&local_80);
  return;
}

