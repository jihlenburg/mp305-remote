/* Address: 0003924c; name: FUN_0003924c; body bytes: 1514 */

void FUN_0003924c(int param_1,int param_2,int param_3,uint param_4,int *param_5,int *param_6)

{
  ushort uVar1;
  ushort uVar2;
  byte bVar3;
  short sVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  ushort *puVar13;
  int *piVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  uint local_e8;
  uint local_e4;
  int local_e0;
  uint local_dc;
  uint local_d8;
  uint local_d4;
  uint local_d0;
  int *local_cc;
  uint local_c8;
  uint local_c4;
  undefined1 local_c0;
  int *local_bc;
  undefined1 local_b8;
  undefined2 local_b7;
  undefined1 local_b5;
  uint local_b4;
  undefined1 local_b0;
  int *local_ac;
  uint local_a8;
  byte local_a4;
  int local_98;
  uint local_94;
  uint local_90;
  undefined4 local_8c;
  int local_84;
  uint local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  ushort *local_58;
  int local_50;
  int local_4c;
  int local_34;
  int iStack_30;
  int iStack_2c;
  uint local_28;
  
  if (((*(int *)(param_2 + 0x2c) == 0) && (*(int *)(param_2 + 0x30) == 0x100)) &&
     (*(int *)(param_2 + 0x34) == 0x100)) {
    local_80 = 0;
  }
  else {
    local_80 = 1;
  }
  uVar15 = (uint)(*(int *)(param_2 + 0x68) != 0);
  puVar13 = *(ushort **)(param_3 + 0x2c);
  local_90 = *(uint *)(puVar13 + 8);
  uVar1 = puVar13[4];
  uVar17 = (uint)uVar1;
  uVar2 = *puVar13;
  uVar18 = (uint)(uVar2 >> 8);
  local_34 = param_1;
  iStack_30 = param_2;
  iStack_2c = param_3;
  local_28 = param_4;
  FUN_0004a57a(&local_cc,0,0x2c);
  local_b8 = *(undefined1 *)(param_2 + 0x4c);
  local_a4 = *(byte *)(param_2 + 0x4d) & 0xf;
  uVar5 = (undefined1)(uVar2 >> 8);
  local_c4 = uVar17;
  if (local_80 == 0 && uVar15 == 0) {
    if (uVar18 == 0xe) {
      iVar6 = FUN_0003db4c(&local_e8,param_5,*(undefined4 *)(local_34 + 8));
      if (iVar6 == 0) {
        return;
      }
      local_b4 = local_90;
      local_c8 = 0;
      local_ac = param_5;
      local_b7 = *(undefined2 *)(param_2 + 0x48);
      local_b5 = *(undefined1 *)(param_2 + 0x4a);
      local_b0 = 2;
      local_a8 = uVar17;
LAB_0003935a:
      local_cc = param_5;
      FUN_0004337c(local_34,&local_cc);
      return;
    }
    if (uVar18 == 0x14) {
      if (*(byte *)(param_2 + 0x4b) < 3) {
        iVar6 = FUN_0003db0a(param_5);
        iVar7 = FUN_0003db28(param_5);
        local_c8 = local_90;
        local_bc = param_5;
        local_b4 = ((uVar17 * iVar7) / (uint)puVar13[2]) * iVar6 + local_90;
        local_ac = param_5;
        local_b0 = 2;
        local_c0 = 0x12;
        local_a8 = (uint)(uVar1 >> 1);
        goto LAB_0003935a;
      }
    }
    else if (*(byte *)(param_2 + 0x4b) < 3) {
      local_bc = param_5;
      local_c8 = local_90;
      local_c0 = uVar5;
      goto LAB_0003935a;
    }
  }
  if (((uVar15 & ~local_80) != 0) && (*(byte *)(param_2 + 0x4b) < 3)) {
    iVar6 = FUN_000477b0(&local_84,*(undefined4 *)(param_2 + 0x68),0);
    if (((iVar6 == 1) && (local_58 != (ushort *)0x0)) &&
       ((*local_58 >> 8 == 0xe || (*local_58 >> 8 == 6)))) {
      local_b4 = *(uint *)(local_58 + 8);
      local_a8 = (uint)local_58[4];
      iVar7 = FUN_0003db28();
      piVar14 = (int *)(param_2 + 0x54);
      if (iVar7 < 0) {
        piVar14 = param_5;
      }
      local_e8 = (*(uint *)(local_58 + 2) >> 0x10) - 1;
      FUN_0003ddf0(&local_e0,0,0,(*(uint *)(local_58 + 2) & 0xffff) - 1);
      local_e8 = 0;
      FUN_0003d7de(piVar14,&local_e0,9,0);
      local_ac = &local_e0;
      local_b0 = 2;
    }
    local_bc = param_5;
    local_cc = param_5;
    local_c8 = local_90;
    local_c0 = uVar5;
    FUN_0004337c(local_34,&local_cc);
    if (iVar6 != 1) {
      return;
    }
    FUN_000476f0(&local_84);
    return;
  }
  local_68 = *param_6;
  local_64 = param_6[1];
  local_60 = param_6[2];
  local_5c = param_6[3];
  local_cc = &local_68;
  local_8c = FUN_0003db28(param_5);
  local_d0 = FUN_0003db0a(param_5);
  uVar8 = FUN_0003db28(&local_68);
  uVar9 = FUN_0003db0a(&local_68);
  uVar15 = uVar18;
  if ((uVar18 == 6) && (2 < *(byte *)(param_2 + 0x4b))) {
    uVar15 = 0x10;
  }
  if (local_80 == 0) {
LAB_0003945a:
    local_84 = FUN_0004034e(uVar15);
    if (uVar15 == 0x14) {
LAB_00039476:
      local_e8 = uVar8 * 3;
      FUN_0004f604();
      iVar6 = FUN_000408b0();
      FUN_0004f604();
      FUN_0004087c();
      iVar7 = FUN_0004034e();
      uVar16 = (uint)(iVar7 * iVar6 * 4) / local_e8;
      uVar10 = local_e8;
      if ((int)uVar9 < (int)uVar16) {
        uVar16 = uVar9;
      }
      goto LAB_000394e2;
    }
  }
  else {
    if ((uVar15 == 0xf) || (uVar15 == 0x11)) {
      uVar15 = 0x10;
    }
    else {
      if (uVar15 == 0x12) {
        uVar15 = 0x14;
        local_84 = FUN_0004034e(0x14);
        goto LAB_00039476;
      }
      if (uVar15 != 6) goto LAB_0003945a;
      uVar15 = 0x15;
    }
    local_84 = FUN_0004034e(uVar15);
  }
  iVar6 = FUN_0004034e(uVar15);
  local_dc = uVar8 * iVar6;
  FUN_0004f604();
  iVar6 = FUN_000408b0();
  FUN_0004f604();
  FUN_0004087c();
  iVar7 = FUN_0004034e();
  uVar16 = (uint)(iVar7 * iVar6 * 4) / local_dc;
  uVar10 = local_dc;
  if ((int)uVar9 < (int)uVar16) {
    uVar16 = uVar9;
  }
LAB_000394e2:
  local_94 = FUN_0004a318(uVar16 * uVar10);
  if (local_94 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_c0 = (undefined1)uVar15;
  local_6c = local_5c;
  local_50 = uVar16 - 1;
  local_5c = local_50 + local_64;
  local_bc = &local_68;
  local_c8 = local_94;
  if (uVar15 == 0x14) {
    local_c4 = uVar8 << 1;
    local_b4 = local_94 + uVar8 * uVar16 * 2;
    local_b0 = 2;
    local_c0 = 0x12;
    local_ac = local_bc;
    local_a8 = uVar8;
  }
  else if (uVar15 == 0xe) {
    local_b0 = 2;
    local_b7 = *(undefined2 *)(param_2 + 0x48);
    local_b5 = *(undefined1 *)(param_2 + 0x4a);
    local_c8 = 0;
    local_b4 = local_94;
    local_ac = local_bc;
    local_a8 = uVar8;
  }
  else {
    iVar6 = FUN_0004034e(uVar15);
    local_c4 = uVar8 * iVar6;
  }
  do {
    if (local_6c < local_64) {
      FUN_00046bec(local_94);
      return;
    }
    local_7c = local_68;
    local_78 = local_64;
    local_74 = local_60;
    local_70 = local_5c;
    FUN_0003ddd6(&local_7c,-*param_5,-param_5[1]);
    if (local_80 == 0) {
      if (1 < *(byte *)(param_2 + 0x4b)) {
        iVar6 = FUN_0003db0a(&local_7c);
        if (uVar18 == 6) {
          iVar7 = uVar17 * local_78 + local_7c + local_90;
          uVar9 = local_94;
          for (iVar19 = 0; iVar19 < iVar6; iVar19 = iVar19 + 1) {
            for (iVar11 = 0; iVar11 < (int)uVar8; iVar11 = iVar11 + 1) {
              iVar12 = uVar9 + iVar11 * 4;
              *(undefined1 *)(iVar12 + 2) = *(undefined1 *)(iVar7 + iVar11);
              *(undefined1 *)(iVar12 + 1) = *(undefined1 *)(iVar7 + iVar11);
              *(undefined1 *)(uVar9 + iVar11 * 4) = *(undefined1 *)(iVar7 + iVar11);
              *(undefined1 *)(iVar12 + 3) = 0xff;
            }
            uVar9 = uVar9 + uVar8 * 4;
            iVar7 = iVar7 + uVar17;
          }
        }
        else if (uVar15 == 0x14) {
          local_e4 = (uint)(uVar1 >> 1);
          local_e0 = local_90 + local_e4 * local_78 * 2 + local_7c * 2;
          local_d4 = local_90 + local_d0 * local_e4 * 2 + local_e4 * local_78 + local_7c;
          local_dc = local_94;
          local_d8 = local_b4;
          local_4c = uVar8 << 1;
          for (iVar7 = 0; iVar7 < iVar6; iVar7 = iVar7 + 1) {
            FUN_0004a404(local_dc,local_e0,local_4c);
            FUN_0004a404(local_d8,local_d4,uVar8);
            local_e0 = local_e0 + local_e4 * 2;
            local_d4 = local_e4 + local_d4;
            local_dc = local_dc + uVar8 * 2;
            local_d8 = local_d8 + uVar8;
          }
        }
        else if (uVar15 != 0xe) {
          local_98 = local_90 + local_7c * local_84 + local_78 * uVar17;
          local_e4 = local_94;
          local_dc = uVar8 * local_84;
          for (iVar7 = 0; iVar7 < iVar6; iVar7 = iVar7 + 1) {
            FUN_0004a404(local_e4,local_98,local_dc);
            local_e4 = uVar8 * local_84 + local_e4;
            local_98 = local_98 + uVar17;
          }
        }
        goto LAB_000396e2;
      }
    }
    else {
      local_d4 = local_94;
      local_dc = local_28;
      local_e8 = local_d0;
      local_e4 = uVar17;
      local_e0 = param_2;
      local_d8 = uVar18;
      FUN_00045794(local_34,&local_7c,local_90,local_8c);
LAB_000396e2:
      bVar3 = *(byte *)(param_2 + 0x4b);
      if (2 < bVar3) {
        local_e4 = *(uint *)(param_2 + 0x48);
        sVar4 = 0xff - (ushort)bVar3;
        uVar2 = (ushort)bVar3;
        if ((uVar15 == 0x14) || (uVar15 == 0x12)) {
          local_98 = (int)(short)(ushort)((local_e4 << 0x18) >> 0x1b) * (int)(short)uVar2;
          local_d4 = (int)(short)((ushort)local_e4 >> 10) * (int)(short)uVar2;
          local_e4 = (int)(short)((ushort)(local_e4 >> 8) >> 0xb) * (int)(short)uVar2;
          local_e8 = local_94;
          iVar6 = FUN_0003db14(&local_68);
          for (iVar7 = 0; iVar7 < iVar6; iVar7 = iVar7 + 1) {
            uVar2 = *(ushort *)(local_e8 + iVar7 * 2);
            *(ushort *)(local_e8 + iVar7 * 2) =
                 (((uVar2 >> 0xb) * sVar4 + (short)local_e4) * 8 & 0xf800) +
                 ((ushort)((int)(short)(ushort)(((uint)uVar2 << 0x15) >> 0x1a) * (int)sVar4 +
                           local_d4 >> 3) & 0x7e0) +
                 (short)((uint)((int)(short)(uVar2 & 0x1f) * (int)sVar4 + local_98) >> 8);
          }
        }
        else if (uVar15 != 0xe) {
          iVar6 = FUN_0003db14(&local_68);
          local_dc = (int)(short)(ushort)(byte)(local_e4 >> 8) * (int)(short)(ushort)bVar3;
          local_d4 = iVar6 * local_84;
          for (uVar9 = 0; uVar9 < local_d4; uVar9 = uVar9 + local_84) {
            *(char *)(local_94 + uVar9) =
                 (char)((uint)((int)(short)(ushort)*(byte *)(local_94 + uVar9) * (int)sVar4 +
                              (int)(short)((ushort)local_e4 & 0xff) * (int)(short)(ushort)bVar3) >>
                       8);
            iVar6 = local_94 + uVar9;
            *(char *)(iVar6 + 1) =
                 (char)((int)(short)(ushort)*(byte *)(iVar6 + 1) * (int)sVar4 + local_dc >> 8);
            *(char *)(iVar6 + 2) =
                 (char)((uint)((int)(short)(ushort)*(byte *)(iVar6 + 2) * (int)sVar4 +
                              (int)(short)(ushort)(byte)(local_e4 >> 0x10) * (int)(short)uVar2) >> 8
                       );
          }
        }
      }
    }
    FUN_0004337c(local_34,&local_cc);
    local_64 = local_5c + 1;
    local_5c = local_64 + local_50;
    if ((local_6c < local_5c) && (local_5c = local_6c, uVar15 == 0x14)) {
      iVar6 = FUN_0003db0a(&local_68);
      local_b4 = local_94 + uVar8 * iVar6 * 2;
    }
  } while( true );
}

