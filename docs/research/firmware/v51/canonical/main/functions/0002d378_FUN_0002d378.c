/* Address: 0002d378; name: FUN_0002d378; body bytes: 732 */

void FUN_0002d378(undefined4 param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int local_1f4;
  int local_1f0;
  int local_1ec;
  int local_1e8;
  int local_1e4;
  int local_1e0;
  int local_1dc;
  undefined1 auStack_1d8 [8];
  uint local_1d0;
  byte local_18f;
  undefined1 auStack_168 [8];
  uint local_160;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_130;
  undefined4 local_12c;
  undefined1 local_11d;
  byte local_11c;
  undefined1 auStack_114 [112];
  undefined1 auStack_a4 [84];
  int local_50;
  int local_4c;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  iVar2 = FUN_00046698();
  if (*(int *)(iVar2 + 0x38) != 0) {
    local_38 = FUN_00046718(param_1);
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) | 8;
    FUN_0004bb3c(iVar2,&local_50);
    uVar1 = *(ushort *)(iVar2 + 0x28);
    uVar10 = (uint)uVar1;
    *(undefined2 *)(iVar2 + 0x28) = 0;
    iVar9 = 0;
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) | 8;
    FUN_00042ec4(auStack_114);
    FUN_00041db4(auStack_a4);
    FUN_0004d0bc(iVar2,&LAB_00050000,auStack_114);
    FUN_0004cf40(iVar2,&LAB_00050000,auStack_a4);
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xfff7;
    *(ushort *)(iVar2 + 0x28) = uVar1;
    local_2c = FUN_0004c8ee(iVar2,0);
    local_30 = FUN_0004c7f2(iVar2,0);
    local_34 = FUN_0004c852(iVar2,0);
    iVar3 = FUN_0004c89a(iVar2,0);
    for (uVar8 = 0; uVar8 < *(uint *)(iVar2 + 0x38); uVar8 = uVar8 + 1) {
      while (iVar4 = thunk_FUN_00050a1a(*(undefined4 *)(*(int *)(iVar2 + 0x2c) + iVar9 * 4),
                                        &DAT_0002d654), iVar4 == 0) {
        iVar9 = iVar9 + 1;
      }
      uVar5 = (uint)*(ushort *)(*(int *)(iVar2 + 0x34) + uVar8 * 2);
      if (-1 < (int)(uVar5 << 0x1b)) {
        uVar6 = (uint)((int)(uVar5 << 0x17) < 0);
        if ((int)(uVar5 << 0x19) < 0) {
          uVar6 = uVar6 | 0x80;
        }
        else if (*(uint *)(iVar2 + 0x40) == uVar8) {
          if ((int)(uVar10 << 0x1a) < 0) {
            uVar6 = uVar6 | 0x20;
          }
          if ((int)(uVar10 << 0x1e) < 0) {
            uVar6 = uVar6 | 2;
          }
          if ((int)(uVar10 << 0x1d) < 0) {
            uVar6 = uVar6 | 4;
          }
          if ((int)(uVar10 << 0x1c) < 0) {
            uVar6 = uVar6 | 8;
          }
        }
        FUN_0003d9da(&local_1f4,*(int *)(iVar2 + 0x30) + uVar8 * 0x10);
        local_1f4 = local_1f4 + local_50;
        local_1f0 = local_4c + local_1f0;
        local_1ec = local_50 + local_1ec;
        local_1e8 = local_1e8 + local_4c;
        if (uVar6 == 0) {
          FUN_0004a404(auStack_1d8,auStack_114,0x70);
          FUN_0004a404(auStack_168,auStack_a4,0x54);
        }
        else {
          *(short *)(iVar2 + 0x28) = (short)uVar6;
          *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) | 8;
          FUN_00042ec4(auStack_1d8);
          FUN_00041db4(auStack_168);
          FUN_0004d0bc(iVar2,&LAB_00050000,auStack_1d8);
          FUN_0004cf40(iVar2,&LAB_00050000,auStack_168);
          *(ushort *)(iVar2 + 0x28) = uVar1;
          *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xfff7;
        }
        if ((int)((uint)local_18f << 0x1b) < 0) {
          local_18f = (local_18f & 0xe0) + 0xf;
          if (local_1f4 == local_34 + *(int *)(iVar2 + 0x14)) {
            local_18f = local_18f & 0xfb;
          }
          if (local_1ec == *(int *)(iVar2 + 0x1c) - iVar3) {
            local_18f = local_18f & 0xf7;
          }
          if (local_1f0 == local_2c + *(int *)(iVar2 + 0x18)) {
            local_18f = local_18f & 0xfd;
          }
          if (local_1e8 == *(int *)(iVar2 + 0x20) - local_30) {
            local_18f = local_18f & 0xe0 | (local_18f >> 1 & 0xf) << 1;
          }
        }
        local_1d0 = uVar8;
        local_1e4 = FUN_0003db0a(&local_1f4);
        if (((int)(uVar6 << 0x1a) < 0) &&
           ((int)((uint)*(ushort *)(*(int *)(iVar2 + 0x34) + uVar8 * 2) << 0x15) < 0)) {
          local_1f0 = local_1f0 - local_1e4;
        }
        FUN_00042a98(local_38,auStack_1d8,&local_1f4);
        local_3c = local_148;
        local_40 = local_12c;
        uVar11 = *(undefined4 *)(*(int *)(iVar2 + 0x2c) + iVar9 * 4);
        uVar12 = local_130;
        uVar7 = FUN_0003db28(&local_50);
        FUN_00051970(&local_1e0,uVar11,local_3c,local_40,uVar12,uVar7,local_11d);
        iVar4 = FUN_0003db28(&local_1f4);
        local_1f4 = local_1f4 + (iVar4 - local_1e0) / 2;
        iVar4 = FUN_0003db0a(&local_1f4);
        local_1f0 = local_1f0 + (iVar4 - local_1dc) / 2;
        local_1ec = local_1f4 + local_1e0;
        local_1e8 = local_1f0 + local_1dc;
        if (((int)(uVar6 << 0x1a) < 0) &&
           ((int)((uint)*(ushort *)(*(int *)(iVar2 + 0x34) + uVar8 * 2) << 0x15) < 0)) {
          local_1f0 = local_1f0 - local_1e4 / 2;
          local_1e8 = local_1e8 - local_1e4 / 2;
        }
        local_11c = local_11c | 0x40;
        local_160 = uVar8;
        local_14c = uVar11;
        FUN_00041d52(local_38,auStack_168,&local_1f4);
      }
      iVar9 = iVar9 + 1;
    }
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xfff7;
  }
  return;
}

