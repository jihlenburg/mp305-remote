/* Address: 0002dd0e; name: FUN_0002dd0e; body bytes: 1096 */

void FUN_0002dd0e(undefined4 param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  bool bVar13;
  undefined4 local_25c;
  int local_258;
  undefined4 uStack_254;
  int local_250;
  undefined4 local_248;
  undefined4 uStack_244;
  undefined4 local_240;
  undefined4 uStack_23c;
  int local_238;
  int local_234;
  int local_230;
  int local_22c;
  uint local_220;
  undefined1 auStack_218 [8];
  uint local_210;
  uint uStack_20c;
  int local_1fc;
  undefined4 local_1e0;
  undefined4 local_1dc;
  int local_1c4;
  int local_1c0;
  int local_1bc;
  int local_1b8;
  undefined1 auStack_1b4 [68];
  uint local_170;
  byte local_16b;
  undefined1 auStack_144 [8];
  uint local_13c;
  uint uStack_138;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  undefined1 auStack_c4 [32];
  undefined4 local_a4;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  int local_60;
  int local_5c;
  undefined1 auStack_54 [4];
  int local_50;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  iVar2 = FUN_00046698();
  iVar3 = FUN_00046718(param_1);
  iVar4 = FUN_0003db4c(&local_25c,iVar2 + 0x14,iVar3 + 0x18);
  if (iVar4 != 0) {
    local_248 = *(undefined4 *)(iVar3 + 0x18);
    uStack_244 = *(undefined4 *)(iVar3 + 0x1c);
    local_240 = *(undefined4 *)(iVar3 + 0x20);
    uStack_23c = *(undefined4 *)(iVar3 + 0x24);
    *(undefined4 *)(iVar3 + 0x18) = local_25c;
    *(int *)(iVar3 + 0x1c) = local_258;
    *(undefined4 *)(iVar3 + 0x20) = uStack_254;
    *(int *)(iVar3 + 0x24) = local_250;
    local_44 = FUN_0004c924(iVar2,0,0x30);
    local_30 = FUN_0004c912(iVar2,0);
    local_2c = FUN_0004c810(iVar2,0);
    local_34 = FUN_0004c876(iVar2,0);
    local_38 = FUN_0004c8b8(iVar2,0);
    local_220 = (uint)*(ushort *)(iVar2 + 0x28);
    *(undefined2 *)(iVar2 + 0x28) = 0;
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) | 8;
    FUN_00042ec4(auStack_1b4);
    FUN_0004d0bc(iVar2,&LAB_00050000,auStack_1b4);
    FUN_00041db4(auStack_c4);
    FUN_0004cf40(iVar2,&LAB_00050000,auStack_c4);
    *(short *)(iVar2 + 0x28) = (short)local_220;
    iVar11 = 0;
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xfff7;
    iVar4 = FUN_0004bf2c(iVar2);
    local_238 = 0;
    local_22c = local_44 + ((local_30 + *(int *)(iVar2 + 0x18)) - iVar4) + -1;
    local_230 = 0;
    local_3c = FUN_0004bf20(iVar2);
    iVar4 = FUN_0004c5d6(iVar2,0);
    bVar13 = iVar4 != 1;
    for (uVar5 = 0; uVar5 < *(uint *)(iVar2 + 0x30); uVar5 = uVar5 + 1) {
      local_40 = *(int *)(*(int *)(iVar2 + 0x38) + uVar5 * 4);
      local_234 = local_22c + 1;
      local_22c = local_40 + -1 + local_234;
      if (local_250 < local_234) break;
      if (bVar13) {
        local_230 = local_44 + ((*(int *)(iVar2 + 0x14) + local_34) - local_3c) + -1;
      }
      else {
        local_238 = (((*(int *)(iVar2 + 0x1c) - local_38) - local_3c) - local_44) + -1;
      }
      for (uVar10 = 0; uVar10 < *(uint *)(iVar2 + 0x2c); uVar10 = uVar10 + iVar4 + 1) {
        uVar12 = 0;
        pbVar6 = *(byte **)(*(int *)(iVar2 + 0x34) + iVar11 * 4);
        if (pbVar6 != (byte *)0x0) {
          uVar12 = (uint)*pbVar6;
        }
        if (bVar13) {
          local_238 = local_230 + 1;
          local_230 = *(int *)(*(int *)(iVar2 + 0x3c) + uVar10 * 4) + local_238 + -1;
        }
        else {
          local_230 = local_238 + -1;
          local_238 = (local_230 - *(int *)(*(int *)(iVar2 + 0x3c) + uVar10 * 4)) + 1;
        }
        iVar4 = 0;
        while (((iVar4 + uVar10 < *(int *)(iVar2 + 0x2c) - 1U &&
                (pbVar6 = *(byte **)(*(int *)(iVar2 + 0x34) + (iVar11 + iVar4) * 4),
                pbVar6 != (byte *)0x0)) && ((*pbVar6 & 1) != 0))) {
          iVar8 = *(int *)(*(int *)(iVar2 + 0x3c) + (uVar10 + iVar4) * 4 + 4);
          if (bVar13) {
            local_230 = iVar8 + local_230;
          }
          else {
            local_238 = local_238 - iVar8;
          }
          iVar4 = iVar4 + 1;
        }
        if (local_258 <= local_22c) {
          local_1c4 = local_238;
          local_1c0 = local_234;
          local_1bc = local_230;
          local_1b8 = local_22c;
          uVar7 = (uint)local_16b;
          if (((int)(uVar7 << 0x1d) < 0) && (*(int *)(iVar2 + 0x14) + local_34 < local_238)) {
            local_1c4 = local_238 - (int)local_170 / 2;
          }
          if (((int)(uVar7 << 0x1e) < 0) && (local_30 + *(int *)(iVar2 + 0x18) < local_234)) {
            local_1c0 = local_234 - (int)local_170 / 2;
          }
          if (((int)(uVar7 << 0x1c) < 0) && (local_230 < (*(int *)(iVar2 + 0x1c) - local_38) + -1))
          {
            local_1bc = (local_170 & 1) + (int)local_170 / 2 + local_230;
          }
          if (((local_16b & 1) != 0) && (local_22c < (*(int *)(iVar2 + 0x20) - local_2c) + -1)) {
            local_1b8 = (local_170 & 1) + (int)local_170 / 2 + local_22c;
          }
          uVar1 = 0;
          if ((*(uint *)(iVar2 + 0x44) == uVar5) && (*(uint *)(iVar2 + 0x40) == uVar10)) {
            uVar7 = (uint)*(ushort *)(iVar2 + 0x28);
            if ((-1 < (int)(uVar7 << 0x19)) && ((int)(uVar7 << 0x1a) < 0)) {
              uVar1 = 0x20;
            }
            if ((int)(uVar7 << 0x1e) < 0) {
              uVar1 = uVar1 | 2;
            }
            if ((int)(uVar7 << 0x1d) < 0) {
              uVar1 = uVar1 | 4;
            }
            if ((int)(uVar7 << 0x1c) < 0) {
              uVar1 = uVar1 | 8;
            }
            if (uVar1 == 0) goto LAB_0002e098;
            *(ushort *)(iVar2 + 0x28) = uVar1;
            *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) | 8;
            FUN_00042ec4(auStack_144);
            FUN_00041db4(auStack_218);
            FUN_0004d0bc(iVar2,&LAB_00050000,auStack_144);
            FUN_0004cf40(iVar2,&LAB_00050000,auStack_218);
            *(short *)(iVar2 + 0x28) = (short)local_220;
            *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xfff7;
          }
          else {
LAB_0002e098:
            FUN_0004a404(auStack_144,auStack_1b4,0x70);
            FUN_0004a404(auStack_218,auStack_c4,0x54);
          }
          local_210 = uVar5;
          uStack_20c = uVar10;
          local_13c = uVar5;
          uStack_138 = uVar10;
          FUN_00042a98(iVar3,auStack_144,&local_1c4);
          if (*(int *)(*(int *)(iVar2 + 0x34) + iVar11 * 4) != 0) {
            iVar8 = FUN_0004c876(iVar2,&LAB_00050000);
            local_5c = FUN_0004c8b8(iVar2,&LAB_00050000);
            local_60 = FUN_0004c912(iVar2,&LAB_00050000);
            local_c8 = FUN_0004c810(iVar2,&LAB_00050000);
            local_d4 = iVar8 + local_238;
            local_cc = local_230 - local_5c;
            local_d0 = local_60 + local_234;
            local_c8 = local_22c - local_c8;
            uVar7 = (uint)((int)(uVar12 << 0x1e) < 0);
            uVar9 = FUN_0003db28(&local_d4);
            FUN_00051970(auStack_54,*(int *)(*(int *)(iVar2 + 0x34) + iVar11 * 4) + 8,local_a4,
                         local_1dc,local_1e0,uVar9,uVar7);
            if (-1 < (int)(uVar12 << 0x1e)) {
              local_d0 = (local_234 + local_40 / 2) - local_50 / 2;
              local_c8 = local_40 / 2 + local_50 / 2 + local_234;
            }
            iVar8 = FUN_0003db4c(&local_70,&local_25c,&local_238);
            if (iVar8 != 0) {
              *(undefined4 *)(iVar3 + 0x18) = local_70;
              *(undefined4 *)(iVar3 + 0x1c) = uStack_6c;
              *(undefined4 *)(iVar3 + 0x20) = uStack_68;
              *(undefined4 *)(iVar3 + 0x24) = uStack_64;
              local_1fc = *(int *)(*(int *)(iVar2 + 0x34) + iVar11 * 4) + 8;
              FUN_00041d52(iVar3,auStack_218,&local_d4);
              *(undefined4 *)(iVar3 + 0x18) = local_25c;
              *(int *)(iVar3 + 0x1c) = local_258;
              *(undefined4 *)(iVar3 + 0x20) = uStack_254;
              *(int *)(iVar3 + 0x24) = local_250;
            }
          }
        }
        iVar11 = iVar11 + iVar4 + 1;
      }
    }
    *(undefined4 *)(iVar3 + 0x18) = local_248;
    *(undefined4 *)(iVar3 + 0x1c) = uStack_244;
    *(undefined4 *)(iVar3 + 0x20) = local_240;
    *(undefined4 *)(iVar3 + 0x24) = uStack_23c;
  }
  return;
}

