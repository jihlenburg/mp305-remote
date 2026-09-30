/* Address: 00035fe2; name: FUN_00035fe2; body bytes: 6710 */

/* WARNING: Type propagation algorithm not settling */

void FUN_00035fe2(int param_1)

{
  undefined2 *puVar1;
  char *pcVar2;
  undefined1 uVar3;
  undefined3 uVar4;
  byte *pbVar5;
  int ***pppiVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  byte *pbVar12;
  int **ppiVar13;
  undefined4 *puVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  undefined1 *puVar19;
  undefined4 uVar20;
  int *piVar21;
  code *pcVar22;
  int iVar23;
  undefined1 *puVar24;
  int iVar25;
  undefined1 *puVar26;
  undefined4 *puVar27;
  code *pcVar28;
  code *pcVar29;
  uint uVar30;
  code *pcVar31;
  byte *pbVar32;
  undefined4 uVar33;
  byte bVar34;
  uint **ppuVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  uint *local_24c;
  undefined4 uStack_248;
  int local_240;
  int iStack_23c;
  undefined4 uStack_238;
  undefined4 uStack_234;
  int local_230;
  int local_22c;
  undefined4 uStack_228;
  int local_224;
  undefined1 auStack_220 [140];
  int *local_194;
  int local_190;
  uint local_18c;
  undefined1 local_188;
  undefined1 **local_184;
  undefined1 local_180;
  undefined2 local_17f;
  undefined1 local_17d;
  int local_17c;
  undefined1 *local_178;
  int *local_174;
  undefined1 *local_170;
  undefined1 *local_16c;
  undefined1 *local_168;
  uint **local_164;
  undefined1 *local_160;
  undefined1 *local_15c;
  undefined1 *local_158;
  undefined1 *local_154;
  undefined1 *local_150;
  undefined1 *local_14c;
  undefined1 auStack_148 [4];
  int *local_144;
  int **local_140;
  int iStack_13c;
  int **local_138;
  undefined1 auStack_134 [20];
  int **local_120;
  ushort *local_11c;
  byte *local_114;
  int *local_110;
  int **local_10c;
  uint local_108;
  code *local_104;
  uint uStack_100;
  int *local_fc;
  uint **local_f8;
  uint *local_f4;
  uint local_f0;
  undefined4 *local_ec;
  int local_e8;
  int local_e4;
  uint local_e0;
  int **local_dc;
  int **local_d8;
  uint **local_d4;
  int local_d0;
  int **local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  uint **local_bc;
  undefined4 **local_b8;
  uint local_b4;
  int local_b0;
  int local_ac;
  uint local_a4;
  byte *local_a0;
  undefined1 local_9c;
  undefined4 **local_98;
  undefined1 auStack_94 [8];
  int local_8c;
  undefined1 auStack_88 [8];
  undefined1 local_80;
  undefined2 local_7f;
  undefined1 local_7d;
  int **local_78;
  undefined1 *local_74;
  uint local_70;
  int *local_6c;
  int local_68;
  int ***local_64;
  int local_60;
  undefined2 local_5c;
  undefined1 local_5a;
  undefined1 local_59;
  int local_58;
  undefined4 local_54;
  undefined2 local_50;
  undefined1 local_4e;
  uint local_4c;
  undefined4 local_48;
  uint **local_44;
  undefined4 ***local_40;
  int **local_3c;
  int *local_38;
  int local_34;
  int local_30;
  int *local_2c;
  code *local_28;
  
  iVar25 = *(int *)(param_1 + 0x1c);
  switch(*(undefined1 *)(iVar25 + 4)) {
  default:
    return;
  case 1:
    FUN_00044bbc(param_1,*(undefined4 *)(iVar25 + 0x4c),iVar25 + 8);
    return;
  case 2:
    FUN_000440c4(param_1,*(undefined4 *)(iVar25 + 0x4c),iVar25 + 8);
    return;
  case 3:
    iVar16 = *(int *)(iVar25 + 0x4c);
    local_c8 = (*(int *)(iVar25 + 8) + *(int *)(iVar16 + 0x2c)) - *(int *)(iVar16 + 0x28);
    local_c0 = *(int *)(iVar16 + 0x28) + *(int *)(iVar16 + 0x2c) + *(int *)(iVar25 + 0x10);
    local_c4 = (*(int *)(iVar25 + 0xc) + *(int *)(iVar16 + 0x30)) - *(int *)(iVar16 + 0x28);
    local_bc = (uint **)(*(int *)(iVar25 + 0x14) + *(int *)(iVar16 + 0x30) + *(int *)(iVar16 + 0x28)
                        );
    iVar23 = *(int *)(iVar16 + 0x24) / 2;
    local_fc = (int *)((local_c8 - iVar23) + -1);
    local_f4 = (uint *)(iVar23 + 1 + local_c0);
    local_f8 = (uint **)((local_c4 - *(int *)(iVar16 + 0x24) / 2) + -1);
    local_f0 = *(int *)(iVar16 + 0x24) / 2 + 1 + (int)local_bc;
    local_3c = (int **)(uint)*(byte *)(iVar16 + 0x34);
    if ((int **)0xfd < local_3c) {
      local_3c = (int **)0xff;
    }
    iVar23 = FUN_0003db4c(&local_38,&local_fc,*(undefined4 *)(param_1 + 8));
    if (iVar23 != 0) {
      FUN_0003da10(auStack_88,(int *)(iVar25 + 8));
      FUN_0003db32(auStack_88,0xffffffff,0xffffffff);
      local_8c = *(int *)(iVar16 + 0x1c);
      iVar25 = FUN_0003db28(auStack_88);
      iVar23 = FUN_0003db0a(auStack_88);
      if (iVar25 < iVar23) {
        iVar25 = FUN_0003db28();
      }
      else {
        iVar25 = FUN_0003db0a(auStack_88);
      }
      if (iVar25 >> 1 < local_8c) {
        local_8c = iVar25 >> 1;
      }
      iVar25 = *(int *)(iVar16 + 0x1c);
      iVar23 = FUN_0003db28(&local_c8);
      iVar17 = FUN_0003db0a(&local_c8);
      if (iVar23 < iVar17) {
        iVar23 = FUN_0003db28();
      }
      else {
        iVar23 = FUN_0003db0a(&local_c8);
      }
      if (iVar23 >> 1 < iVar25) {
        iVar25 = iVar23 >> 1;
      }
      iVar23 = *(int *)(iVar16 + 0x24) + iVar25;
      local_74 = (undefined1 *)FUN_0004a318(iVar23 * iVar23 * 2);
      FUN_0005ed38(&local_c8,local_74,*(undefined4 *)(iVar16 + 0x24),iVar25);
      bVar34 = *(byte *)(iVar16 + 0x35);
      uVar15 = bVar34 & 1;
      local_6c = (int *)0x0;
      local_68 = 0;
      if ((bVar34 & 1) == 0) {
        FUN_000454e8(&local_60,auStack_88,local_8c,1);
        local_6c = &local_60;
      }
      FUN_0003db28(&local_fc);
      pbVar12 = (byte *)FUN_0004a318();
      FUN_0004a57a(&local_b8,0,0x2c);
      local_b8 = &local_110;
      local_a4 = CONCAT31(*(undefined3 *)(iVar16 + 0x20),*(undefined1 *)(iVar16 + 0x34));
      local_a0 = pbVar12;
      local_98 = local_b8;
      iVar25 = FUN_0003db28(&local_fc);
      puVar14 = (undefined4 *)((int)local_fc + iVar25 / 2);
      iVar25 = FUN_0003db0a(&local_fc);
      iVar25 = (int)local_f8 + iVar25 / 2;
      local_108 = (uint)local_f4;
      local_110 = (int *)(((int)local_f4 - iVar23) + 1);
      local_10c = (int **)local_f8;
      local_d0 = iVar23 + -1;
      if ((int)local_110 <= (int)puVar14) {
        local_110 = puVar14;
      }
      local_104 = (code *)(local_d0 + (int)local_f8);
      if (iVar25 <= local_d0 + (int)local_f8) {
        local_104 = (code *)iVar25;
      }
      iVar17 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar17 != 0) && (iVar17 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar17 == 0)) {
        local_d4 = (uint **)FUN_0003db28(&local_ec);
        local_114 = local_74 +
                    (int)local_ec +
                    ((local_e8 - (int)local_f8) * iVar23 - ((int)local_f4 - iVar23)) + -1;
        local_64 = (int ***)uVar15;
        if (((bVar34 & 1) != 0) &&
           (iVar17 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), iVar17 != 0)) {
          local_64 = (int ***)0x1;
        }
        if (0 < (int)local_d4) {
          local_110 = local_ec;
          local_108 = local_e4;
          local_9c = 2;
          local_a0 = pbVar12;
          for (iVar17 = local_e8; iVar17 <= (int)local_e0; iVar17 = iVar17 + 1) {
            local_104 = (code *)iVar17;
            local_10c = (int **)iVar17;
            if (local_64 == (int ***)0x0) {
              FUN_0004a404(pbVar12,local_114,iVar23);
              local_120 = (int **)local_d4;
              iVar8 = FUN_000452b4(&local_6c,pbVar12,local_ec,iVar17);
              local_9c = (undefined1)iVar8;
              if (iVar8 == 1) {
                local_9c = 2;
              }
            }
            else {
              local_a0 = local_114;
            }
            FUN_0004337c(param_1,&local_b8);
            local_114 = local_114 + iVar23;
          }
        }
      }
      local_108 = (uint)local_f4;
      local_110 = (int *)(((int)local_f4 - iVar23) + 1);
      local_10c = (int **)((local_f0 - iVar23) + 1);
      local_104 = (code *)local_f0;
      if ((int)local_110 <= (int)puVar14) {
        local_110 = puVar14;
      }
      local_d4 = (uint **)(iVar25 + 1);
      if ((int)local_10c <= (int)local_d4) {
        local_10c = (int **)(iVar25 + 1);
      }
      iVar17 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar17 != 0) && (iVar17 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar17 == 0)) {
        local_78 = (int **)FUN_0003db28(&local_ec);
        local_114 = local_74 +
                    (int)local_ec +
                    (((int)local_104 - local_e0) * iVar23 - ((int)local_f4 - iVar23)) + -1;
        pppiVar6 = (int ***)uVar15;
        if (((bVar34 & 1) != 0) &&
           (iVar17 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), iVar17 != 0)) {
          local_64 = (int ***)0x1;
          pppiVar6 = local_64;
        }
        local_64 = pppiVar6;
        if (0 < (int)local_78) {
          local_110 = local_ec;
          local_108 = local_e4;
          local_9c = 2;
          local_a0 = pbVar12;
          for (uVar18 = local_e0; local_e8 <= (int)uVar18; uVar18 = uVar18 - 1) {
            local_104 = (code *)uVar18;
            local_10c = (int **)uVar18;
            if (local_64 == (int ***)0x0) {
              FUN_0004a404(pbVar12,local_114,iVar23);
              local_120 = local_78;
              iVar17 = FUN_000452b4(&local_6c,pbVar12,local_ec,uVar18);
              local_9c = (undefined1)iVar17;
              if (iVar17 == 1) {
                local_9c = 2;
              }
            }
            else {
              local_a0 = local_114;
            }
            FUN_0004337c(param_1,&local_b8);
            local_114 = local_114 + iVar23;
          }
        }
      }
      local_110 = (int *)((int)local_fc + iVar23);
      local_108 = (int)local_f4 - iVar23;
      local_10c = (int **)local_f8;
      local_104 = (code *)(local_d0 + (int)local_f8);
      if (iVar25 <= local_d0 + (int)local_f8) {
        local_104 = (code *)iVar25;
      }
      iVar17 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar17 != 0) && (iVar17 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar17 == 0)) {
        local_dc = (int **)FUN_0003db28(&local_ec);
        local_114 = local_74 + (local_e8 - (int)local_10c) * iVar23;
        pppiVar6 = (int ***)uVar15;
        if (((bVar34 & 1) != 0) &&
           (iVar17 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), iVar17 != 0)) {
          local_64 = (int ***)0x1;
          pppiVar6 = local_64;
        }
        local_64 = pppiVar6;
        if (0 < (int)local_dc) {
          local_a0 = pbVar12;
          if (local_64 != (int ***)0x0) {
            local_a0 = (byte *)0x0;
          }
          local_110 = local_ec;
          local_108 = local_e4;
          for (iVar17 = local_e8; iVar17 <= (int)local_e0; iVar17 = iVar17 + 1) {
            local_104 = (code *)iVar17;
            local_10c = (int **)iVar17;
            if (local_64 == (int ***)0x0) {
              FUN_0004a57a(pbVar12,*local_114,local_dc);
              local_120 = local_dc;
              iVar8 = FUN_000452b4(&local_6c,pbVar12,local_ec,iVar17);
              local_9c = (undefined1)iVar8;
              if (iVar8 == 1) {
                local_9c = 2;
              }
            }
            else {
              bVar7 = *local_114;
              if (local_3c != (int **)0xff) {
                bVar7 = (byte)((uint)((int)(short)(ushort)bVar7 *
                                     (int)(short)(ushort)*(byte *)(iVar16 + 0x34)) >> 8);
              }
              local_a4 = CONCAT31(local_a4._1_3_,bVar7);
            }
            FUN_0004337c(param_1,&local_b8);
            local_114 = local_114 + iVar23;
          }
        }
      }
      local_a4 = CONCAT31(local_a4._1_3_,*(undefined1 *)(iVar16 + 0x34));
      local_110 = (int *)((int)local_fc + iVar23);
      local_108 = (int)local_f4 - iVar23;
      local_10c = (int **)((local_f0 - iVar23) + 1);
      local_104 = (code *)local_f0;
      if ((int)local_10c <= (int)local_d4) {
        local_10c = (int **)(iVar25 + 1);
      }
      iVar17 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar17 != 0) && (iVar17 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar17 == 0)) {
        local_dc = (int **)FUN_0003db28(&local_ec);
        local_114 = local_74 + ((int)local_104 - local_e0) * iVar23;
        if (0 < (int)local_dc) {
          pbVar32 = pbVar12;
          if ((bVar34 & 1) != 0) {
            FUN_0003dc3a(&local_ec,auStack_88,local_8c);
            local_a0 = (byte *)0x0;
            pbVar32 = local_a0;
          }
          local_a0 = pbVar32;
          local_110 = local_ec;
          local_108 = local_e4;
          for (uVar18 = local_e0; local_e8 <= (int)uVar18; uVar18 = uVar18 - 1) {
            local_104 = (code *)uVar18;
            local_10c = (int **)uVar18;
            if ((bVar34 & 1) == 0) {
              FUN_0004a57a(pbVar12,*local_114,local_dc);
              local_120 = local_dc;
              iVar17 = FUN_000452b4(&local_6c,pbVar12,local_ec,uVar18);
              local_9c = (undefined1)iVar17;
              if (iVar17 == 1) {
                local_9c = 2;
              }
            }
            else {
              FUN_0003dc3a(&local_ec,auStack_88,local_8c);
              bVar7 = *local_114;
              if (local_3c != (int **)0xff) {
                bVar7 = (byte)((uint)((int)(short)(ushort)bVar7 *
                                     (int)(short)(ushort)*(byte *)(iVar16 + 0x34)) >> 8);
              }
              local_a4 = CONCAT31(local_a4._1_3_,bVar7);
            }
            FUN_0004337c(param_1,&local_b8);
            local_114 = local_114 + iVar23;
          }
        }
      }
      local_a4 = CONCAT31(local_a4._1_3_,*(undefined1 *)(iVar16 + 0x34));
      local_110 = (int *)(((int)local_f4 - iVar23) + 1);
      local_108 = (uint)local_f4;
      local_10c = (int **)((int)local_f8 + iVar23);
      if ((int)local_d4 <= (int)local_10c) {
        local_10c = (int **)(iVar25 + 1);
      }
      local_104 = (code *)(local_f0 - iVar23);
      if ((int)(local_f0 - iVar23) <= iVar25) {
        local_104 = (code *)iVar25;
      }
      if ((int)local_110 <= (int)puVar14) {
        local_110 = puVar14;
      }
      iVar16 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar16 != 0) && (iVar16 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar16 == 0)) {
        local_dc = (int **)FUN_0003db28(&local_ec);
        local_114 = local_74 + (int)local_ec + (local_d0 * iVar23 - ((int)local_f4 - iVar23)) + -1;
        pbVar32 = pbVar12;
        uVar18 = uVar15;
        if (((bVar34 & 1) != 0) &&
           (iVar16 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), pbVar32 = local_114, iVar16 != 0))
        {
          uVar18 = 1;
        }
        local_a0 = pbVar32;
        if (0 < (int)local_dc) {
          local_110 = local_ec;
          local_108 = local_e4;
          local_9c = 2;
          for (iVar16 = local_e8; iVar16 <= (int)local_e0; iVar16 = iVar16 + 1) {
            local_10c = (int **)iVar16;
            local_104 = (code *)iVar16;
            if (uVar18 == 0) {
              FUN_0004a404(pbVar12,local_114,local_dc);
              local_120 = local_dc;
              iVar17 = FUN_000452b4(&local_6c,pbVar12,local_ec,iVar16);
              local_9c = (undefined1)iVar17;
              if (iVar17 == 1) {
                local_9c = 2;
              }
            }
            FUN_0004337c(param_1,&local_b8);
          }
        }
      }
      puVar19 = local_74;
      for (iVar16 = 0; iVar16 < iVar23; iVar16 = iVar16 + 1) {
        puVar24 = puVar19;
        puVar26 = puVar19 + iVar23;
        for (iVar17 = 0; puVar26 = puVar26 + -1, iVar17 < iVar23 / 2; iVar17 = iVar17 + 1) {
          uVar3 = *puVar24;
          *puVar24 = *puVar26;
          *puVar26 = uVar3;
          puVar24 = puVar24 + 1;
        }
        puVar19 = puVar19 + iVar23;
      }
      local_110 = local_fc;
      local_108 = (int)local_fc + local_d0;
      local_10c = (int **)((int)local_f8 + iVar23);
      if ((int)local_d4 <= (int)local_10c) {
        local_10c = (int **)(iVar25 + 1);
      }
      local_104 = (code *)(local_f0 - iVar23);
      if ((int)(local_f0 - iVar23) <= iVar25) {
        local_104 = (code *)iVar25;
      }
      local_dc = (int **)((int)puVar14 + -1);
      if ((int)local_dc <= (int)local_108) {
        local_108 = (int)puVar14 + -1;
      }
      iVar16 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar16 != 0) && (iVar16 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar16 == 0)) {
        local_78 = (int **)FUN_0003db28(&local_ec);
        local_114 = local_74 + (int)local_ec + (local_d0 * iVar23 - (int)local_110);
        pbVar32 = pbVar12;
        uVar18 = uVar15;
        if (((bVar34 & 1) != 0) &&
           (iVar16 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), pbVar32 = local_114, iVar16 != 0))
        {
          uVar18 = 1;
        }
        local_a0 = pbVar32;
        if (0 < (int)local_78) {
          local_110 = local_ec;
          local_108 = local_e4;
          local_9c = 2;
          for (iVar16 = local_e8; iVar16 <= (int)local_e0; iVar16 = iVar16 + 1) {
            local_10c = (int **)iVar16;
            local_104 = (code *)iVar16;
            if (uVar18 == 0) {
              FUN_0004a404(pbVar12,local_114,local_78);
              local_120 = local_78;
              iVar17 = FUN_000452b4(&local_6c,pbVar12,local_ec,iVar16);
              local_9c = (undefined1)iVar17;
              if (iVar17 == 1) {
                local_9c = 2;
              }
            }
            FUN_0004337c(param_1,&local_b8);
          }
        }
      }
      local_110 = local_fc;
      local_108 = (int)local_fc + local_d0;
      local_10c = (int **)local_f8;
      if ((int)local_dc <= (int)local_108) {
        local_108 = (int)puVar14 + -1;
      }
      local_104 = (code *)(local_d0 + (int)local_f8);
      if (iVar25 <= local_d0 + (int)local_f8) {
        local_104 = (code *)iVar25;
      }
      iVar16 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar16 != 0) && (iVar16 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar16 == 0)) {
        local_3c = (int **)FUN_0003db28(&local_ec);
        pbVar32 = local_74 + (int)local_ec + ((local_e8 - (int)local_10c) * iVar23 - (int)local_110)
        ;
        pppiVar6 = (int ***)uVar15;
        if (((bVar34 & 1) != 0) &&
           (iVar16 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), iVar16 != 0)) {
          local_64 = (int ***)0x1;
          pppiVar6 = local_64;
        }
        local_64 = pppiVar6;
        local_a0 = pbVar12;
        if (0 < (int)local_3c) {
          local_110 = local_ec;
          local_108 = local_e4;
          local_9c = 2;
          for (iVar16 = local_e8; iVar16 <= (int)local_e0; iVar16 = iVar16 + 1) {
            local_10c = (int **)iVar16;
            local_104 = (code *)iVar16;
            pbVar5 = pbVar32;
            if (local_64 == (int ***)0x0) {
              FUN_0004a404(pbVar12,pbVar32,iVar23);
              local_120 = local_3c;
              iVar17 = FUN_000452b4(&local_6c,pbVar12,local_ec,iVar16);
              local_9c = (undefined1)iVar17;
              pbVar5 = local_a0;
              if (iVar17 == 1) {
                local_9c = 2;
              }
            }
            local_a0 = pbVar5;
            FUN_0004337c(param_1,&local_b8);
            pbVar32 = pbVar32 + iVar23;
          }
        }
      }
      local_110 = local_fc;
      local_108 = (int)local_fc + local_d0;
      local_10c = (int **)((local_f0 - iVar23) + 1);
      local_104 = (code *)local_f0;
      if ((int)local_10c <= (int)local_d4) {
        local_10c = (int **)(iVar25 + 1);
      }
      if ((int)local_dc <= (int)local_108) {
        local_108 = (int)puVar14 + -1;
      }
      iVar16 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if ((iVar16 != 0) && (iVar16 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar16 == 0)) {
        local_d8 = (int **)FUN_0003db28(&local_ec);
        pbVar32 = local_74 + (int)local_ec + (((int)local_104 - local_e0) * iVar23 - (int)local_110)
        ;
        if (((bVar34 & 1) != 0) &&
           (iVar16 = FUN_0003dc3a(&local_ec,auStack_88,local_8c), iVar16 != 0)) {
          uVar15 = 1;
        }
        if (0 < (int)local_d8) {
          local_110 = local_ec;
          local_108 = local_e4;
          local_9c = 2;
          local_a0 = pbVar12;
          for (uVar18 = local_e0; local_e8 <= (int)uVar18; uVar18 = uVar18 - 1) {
            local_10c = (int **)uVar18;
            local_104 = (code *)uVar18;
            pbVar5 = pbVar32;
            if (uVar15 == 0) {
              FUN_0004a404(pbVar12,pbVar32,iVar23);
              local_120 = local_d8;
              iVar16 = FUN_000452b4(&local_6c,pbVar12,local_ec,uVar18);
              local_9c = (undefined1)iVar16;
              pbVar5 = local_a0;
              if (iVar16 == 1) {
                local_9c = 2;
              }
            }
            local_a0 = pbVar5;
            FUN_0004337c(param_1,&local_b8);
            pbVar32 = pbVar32 + iVar23;
          }
        }
      }
      local_110 = (int *)((int)local_fc + iVar23);
      local_108 = (int)local_f4 - iVar23;
      local_10c = (int **)((int)local_f8 + iVar23);
      if ((int)local_d4 <= (int)local_10c) {
        local_10c = (int **)(iVar25 + 1);
      }
      local_104 = (code *)iVar25;
      if (iVar25 < (int)(local_f0 - iVar23)) {
        local_104 = (code *)(local_f0 - iVar23);
      }
      local_a0 = pbVar12;
      iVar25 = FUN_0003db4c(&local_ec,&local_110,*(undefined4 *)(param_1 + 8));
      if (((iVar25 != 0) && (iVar25 = FUN_0003db8c(&local_ec,auStack_88,local_8c), iVar25 == 0)) &&
         (ppiVar13 = (int **)FUN_0003db28(&local_ec), 0 < (int)ppiVar13)) {
        local_110 = local_ec;
        local_108 = local_e4;
        for (iVar25 = local_e8; iVar25 <= (int)local_e0; iVar25 = iVar25 + 1) {
          local_10c = (int **)iVar25;
          local_104 = (code *)iVar25;
          FUN_0004a57a(pbVar12,0xff,ppiVar13);
          local_120 = ppiVar13;
          local_9c = FUN_000452b4(&local_6c,pbVar12,local_ec,iVar25);
          FUN_0004337c(param_1,&local_b8);
        }
      }
      if ((bVar34 & 1) == 0) {
        FUN_00045330(&local_60);
      }
      FUN_00046bec(local_74);
      FUN_00046bec(pbVar12);
    }
    return;
  case 4:
    iVar23 = *(int *)(iVar25 + 0x4c);
    local_2c = (int *)(iVar25 + 8);
    if (*(byte *)(iVar23 + 0x48) < 3) {
      return;
    }
    local_28 = (code *)0x2cc79;
    local_fc = *(int **)(iVar23 + 0x20);
    local_34 = param_1;
    local_30 = iVar23;
    iVar25 = FUN_0003db4c(&local_54,local_2c,*(undefined4 *)(param_1 + 8));
    if (iVar25 == 0) {
      return;
    }
    uVar15 = (uint)*(byte *)(iVar23 + 0x4a);
    if (uVar15 == 0) {
      uVar15 = 1;
    }
    if ((*(byte *)(iVar23 + 0x4b) & 1) == 0) {
      local_e0 = FUN_0003db28(local_2c,*(undefined4 *)(iVar23 + 0x1c));
    }
    else {
      local_108 = *(undefined4 *)(iVar23 + 0x38);
      local_104 = (code *)0x1fffffff;
      uStack_100 = (uint)*(byte *)(iVar23 + 0x4b);
      FUN_00051970(&local_e0,*(undefined4 *)(iVar23 + 0x1c),*(undefined4 *)(iVar23 + 0x20),
                   *(undefined4 *)(iVar23 + 0x3c));
    }
    local_f0 = local_e0;
    iVar16 = FUN_00046bd6(local_fc);
    iVar17 = *(int *)(iVar23 + 0x38) + iVar16;
    FUN_0004f266(&local_f8,*local_2c,local_2c[1]);
    local_c0 = *(int *)(iVar23 + 0x40);
    iVar25 = 0;
    local_f4 = (uint *)((int)local_f4 + *(int *)(iVar23 + 0x44));
    puVar14 = *(undefined4 **)(iVar23 + 0x50);
    if (((puVar14 != (undefined4 *)0x0) && (*(int *)(iVar23 + 0x44) == 0)) &&
       (iVar8 = local_2c[1], iVar8 < 0)) {
      iVar9 = puVar14[2] - iVar8;
      if (iVar9 < 1) {
        iVar9 = iVar8 - puVar14[2];
      }
      if (iVar17 * -2 + 0x400 < iVar9) {
        *puVar14 = 0xffffffff;
      }
      piVar21 = *(int **)(iVar23 + 0x50);
      if ((piVar21 != (int *)0x0) && (-1 < *piVar21)) {
        local_f4 = (uint *)((int)local_f4 + piVar21[1]);
        iVar25 = *piVar21;
      }
    }
    local_104 = (code *)(uint)*(byte *)(iVar23 + 0x4b);
    local_108 = 0;
    iVar8 = FUN_0005175c(*(int *)(iVar23 + 0x1c) + iVar25,local_fc,*(undefined4 *)(iVar23 + 0x3c),
                         local_f0);
    iVar8 = iVar8 + iVar25;
    while ((int)local_f4 + iVar16 < *(int *)(*(int *)(local_34 + 8) + 4)) {
      local_104 = (code *)(uint)*(byte *)(iVar23 + 0x4b);
      local_108 = 0;
      iVar9 = FUN_0005175c(*(int *)(iVar23 + 0x1c) + iVar8,local_fc,*(undefined4 *)(iVar23 + 0x3c),
                           local_f0);
      local_f4 = (uint *)((int)local_f4 + iVar17);
      piVar21 = *(int **)(iVar23 + 0x50);
      if (((piVar21 != (int *)0x0) && (-0x401 < (int)local_f4)) && (*piVar21 < 0)) {
        *piVar21 = iVar8;
        *(int *)(*(int *)(iVar23 + 0x50) + 4) = (int)local_f4 - local_2c[1];
        *(int *)(*(int *)(iVar23 + 0x50) + 8) = local_2c[1];
      }
      pcVar2 = (char *)(*(int *)(iVar23 + 0x1c) + iVar8);
      iVar25 = iVar8;
      iVar8 = iVar9 + iVar8;
      if (*pcVar2 == '\0') {
        return;
      }
    }
    local_e0 = uVar15;
    if (uVar15 == 2) {
      iVar16 = FUN_00051a28(*(int *)(iVar23 + 0x1c) + iVar25,iVar8 - iVar25,local_fc,
                            *(undefined4 *)(iVar23 + 0x3c));
      iVar9 = FUN_0003db28(local_2c);
      local_f8 = (uint **)((int)local_f8 + (iVar9 - iVar16) / 2);
    }
    else if (uVar15 == 3) {
      iVar16 = FUN_00051a28(*(int *)(iVar23 + 0x1c) + iVar25,iVar8 - iVar25,local_fc,
                            *(undefined4 *)(iVar23 + 0x3c));
      iVar9 = FUN_0003db28(local_2c);
      local_f8 = (uint **)((int)local_f8 + (iVar9 - iVar16));
    }
    uVar30 = *(uint *)(iVar23 + 0x24);
    uVar18 = *(uint *)(iVar23 + 0x28);
    uVar15 = uVar30;
    if (uVar18 < uVar30) {
      uVar15 = uVar18;
      uVar18 = uVar30;
    }
    FUN_00041ac4(&local_70);
    local_59 = *(undefined1 *)(iVar23 + 0x48);
    local_64 = (int ***)&local_bc;
    puVar1 = (undefined2 *)(iVar23 + 0x2c);
    local_5c = *puVar1;
    local_5a = *(undefined1 *)(iVar23 + 0x2e);
    FUN_00041964(&local_a0);
    local_80 = *(undefined1 *)(iVar23 + 0x48);
    local_ac = (int)*(char *)((int)local_fc + 0x16);
    if (local_ac == 0) {
      local_ac = 1;
    }
    break;
  case 5:
    FUN_00044f88(param_1,*(undefined4 *)(iVar25 + 0x4c),iVar25 + 8);
    return;
  case 6:
    piVar21 = *(int **)(*(int *)(iVar25 + 0x4c) + 0x1c);
    if (*piVar21 != 0) {
      FUN_0001046a(&local_80,*(int *)(iVar25 + 0x4c),0x6c);
      local_64 = (int ***)*piVar21;
      FUN_00044f88(param_1,&local_80,iVar25 + 8);
    }
    return;
  case 7:
    FUN_00045006(param_1,*(undefined4 *)(iVar25 + 0x4c));
    return;
  case 8:
    iVar23 = *(int *)(iVar25 + 0x4c);
    local_28 = (code *)(iVar25 + 8);
    if (((2 < *(byte *)(iVar23 + 0x3c)) && (uVar15 = *(uint *)(iVar23 + 0x20), uVar15 != 0)) &&
       (*(float *)(iVar23 + 0x24) != *(float *)(iVar23 + 0x28))) {
      if ((int)(uint)*(ushort *)(iVar23 + 0x34) < (int)uVar15) {
        uVar15 = (uint)*(ushort *)(iVar23 + 0x34);
      }
      local_cc = *(int ***)local_28;
      local_c8 = *(int *)(iVar25 + 0xc);
      local_c4 = *(int *)(iVar25 + 0x10);
      local_c0 = *(int *)(iVar25 + 0x14);
      local_30 = param_1;
      local_2c = (int *)iVar23;
      iVar25 = FUN_0003db4c(&local_240,&local_cc,*(undefined4 *)(param_1 + 8));
      if (iVar25 != 0) {
        if (*(int *)(iVar23 + 0x38) == 0) {
          if ((*(float *)(iVar23 + 0x24) + 360.0 == *(float *)(iVar23 + 0x28)) ||
             (*(float *)(iVar23 + 0x24) == *(float *)(iVar23 + 0x28) + 360.0)) {
            FUN_00041086(&local_70);
            local_50 = *(undefined2 *)(iVar23 + 0x1c);
            local_4e = *(undefined1 *)(iVar23 + 0x1e);
            local_48._0_2_ = CONCAT11(0xf,*(undefined1 *)(iVar23 + 0x3c));
            local_54 = 0x7fff;
            local_4c = uVar15;
            FUN_000440c4(local_30,&local_70,&local_cc);
            return;
          }
        }
        local_dc = (int **)((int)local_cc + *(int *)(iVar23 + 0x20));
        local_d8 = (int **)(*(int *)(iVar23 + 0x20) + local_c8);
        local_d4 = (uint **)(local_c4 - *(int *)(iVar23 + 0x20));
        local_d0 = local_c0 - *(int *)(iVar23 + 0x20);
        iVar25 = (int)*(float *)(iVar23 + 0x28);
        for (iVar16 = (int)*(float *)(iVar23 + 0x24); 0x167 < iVar16; iVar16 = iVar16 + -0x168) {
        }
        for (; 0x167 < iVar25; iVar25 = iVar25 + -0x168) {
        }
        local_168 = (undefined1 *)0x0;
        local_164 = (uint **)0x0;
        local_160 = (undefined1 *)0x0;
        local_15c = (undefined1 *)0x0;
        FUN_00045204(auStack_220,*(undefined4 *)(iVar23 + 0x2c),*(undefined4 *)(iVar23 + 0x30),
                     iVar16,iVar25);
        local_168 = auStack_220;
        FUN_000454e8(&local_b8,&local_cc,0x7fff,0);
        local_164 = (uint **)&local_b8;
        local_3c = (int **)0x0;
        iVar17 = FUN_0003db28(&local_dc);
        if ((0 < iVar17) && (iVar17 = FUN_0003db0a(&local_dc), 0 < iVar17)) {
          FUN_000454e8(auStack_94,&local_dc,0x7fff,1);
          local_160 = auStack_94;
          local_3c = (int **)0x1;
        }
        iVar17 = FUN_0003db0a(&local_240);
        iVar8 = FUN_0003db28(&local_240);
        iVar9 = FUN_0004a318();
        local_230 = local_240;
        local_22c = iStack_23c;
        uStack_228 = uStack_238;
        local_224 = uStack_234;
        FUN_0001049c(&local_194,0x2c);
        local_180 = *(undefined1 *)(iVar23 + 0x3c);
        local_194 = &local_230;
        local_38 = (int *)0x0;
        local_17c = iVar9;
        local_174 = local_194;
        if (((*(int *)(iVar23 + 0x38) == 0) ||
            (iVar10 = FUN_000477b0(auStack_148,*(int *)(iVar23 + 0x38),0), iVar10 == 0)) ||
           (local_11c == (ushort *)0x0)) {
          local_17f = *(undefined2 *)(iVar23 + 0x1c);
          local_17d = *(undefined1 *)(iVar23 + 0x1e);
        }
        else {
          local_158 = (undefined1 *)0x0;
          local_154 = (undefined1 *)0x0;
          local_150 = (undefined1 *)(local_11c[2] - 1);
          local_14c = (undefined1 *)((*(uint *)(local_11c + 2) >> 0x10) - 1);
          FUN_0003ddd6(&local_158,*(int *)(iVar23 + 0x2c) - (uint)(local_11c[2] >> 1),
                       *(int *)(iVar23 + 0x30) - (uint)(local_11c[2] >> 1));
          local_184 = &local_158;
          local_190 = *(int *)(local_11c + 8);
          local_18c = (uint)local_11c[4];
          local_188 = (undefined1)(*local_11c >> 8);
          if (*local_11c >> 8 == 0x14) {
            local_188 = 0x12;
            iVar10 = FUN_0003db0a(local_184);
            local_38 = (int *)(local_18c * iVar10 + local_190);
          }
        }
        local_bc = (uint **)0x0;
        if ((*(byte *)(iVar23 + 0x3d) & 1) != 0) {
          local_bc = (uint **)FUN_0004a318();
          FUN_0004a57a(local_bc,0xff,uVar15 * uVar15);
          local_44 = (uint **)(uVar15 - 1);
          local_4c = 0;
          local_48 = 0;
          local_40 = (undefined4 ***)local_44;
          FUN_000454e8(&local_70,&local_4c,(int)uVar15 / 2,0);
          local_24c = &local_70;
          uStack_248 = 0;
          ppuVar35 = local_bc;
          for (iVar10 = 0; iVar10 < (int)uVar15; iVar10 = iVar10 + 1) {
            iVar11 = FUN_000452b4(&local_24c,ppuVar35,0,iVar10,uVar15);
            if (iVar11 == 0) {
              FUN_0004a57a(ppuVar35,0,uVar15);
            }
            ppuVar35 = (uint **)((int)ppuVar35 + uVar15);
          }
          FUN_000379a6((int)(short)iVar16,*(undefined2 *)(iVar23 + 0x34),uVar15 & 0xff,&local_fc);
          FUN_0003ddd6(&local_fc,*(undefined4 *)(iVar23 + 0x2c),*(undefined4 *)(iVar23 + 0x30));
          FUN_000379a6((int)(short)iVar25,*(undefined2 *)(iVar23 + 0x34),uVar15 & 0xff,&local_ec);
          FUN_0003ddd6(&local_ec,*(undefined4 *)(iVar23 + 0x2c),*(undefined4 *)(iVar23 + 0x30));
        }
        local_224 = local_22c;
        for (iVar25 = 0; iVar25 < iVar17; iVar25 = iVar25 + 1) {
          FUN_0004a57a(iVar9,0xff,iVar8);
          iVar16 = FUN_000452b4(&local_168,iVar9,local_230,local_22c,iVar8);
          local_178 = (undefined1 *)CONCAT31(local_178._1_3_,(char)iVar16);
          if ((*(byte *)(iVar23 + 0x3d) & 1) != 0) {
            if (((int)local_f8 <= local_22c) && (local_22c <= (int)local_f0)) {
              if (iVar16 == 0) {
                FUN_0004a57a(iVar9,0,iVar8);
                local_178 = (undefined1 *)CONCAT31(local_178._1_3_,2);
              }
              FUN_00021708(local_bc,&local_230,&local_fc,iVar9,uVar15);
            }
            if ((local_e8 <= local_22c) && (local_22c <= (int)local_e0)) {
              if ((char)local_178 == '\0') {
                FUN_0004a57a(iVar9,0,iVar8);
                local_178 = (undefined1 *)CONCAT31(local_178._1_3_,2);
              }
              FUN_00021708(local_bc,&local_230,&local_ec,iVar9,uVar15);
            }
          }
          if ((local_38 != (int *)0x0) && ((char)local_178 != '\0')) {
            puVar19 = local_184[1];
            puVar26 = *local_184;
            for (iVar16 = 0; iVar16 < iVar8; iVar16 = iVar16 + 1) {
              *(char *)(iVar9 + iVar16) =
                   (char)((uint)((int)(short)(ushort)*(byte *)(iVar9 + iVar16) *
                                (int)(short)(ushort)*(byte *)((int)local_38 +
                                                             iVar16 + (local_230 - (int)puVar26) +
                                                                      (local_18c >> 1) *
                                                                      (local_22c - (int)puVar19)))
                         >> 8);
            }
            if ((char)local_178 == '\x01') {
              local_178 = (undefined1 *)CONCAT31(local_178._1_3_,2);
            }
          }
          FUN_0004337c(local_30,&local_194);
          local_22c = local_22c + 1;
          local_224 = local_224 + 1;
        }
        FUN_00045330(auStack_220);
        FUN_00045330(&local_b8);
        if (local_3c != (int **)0x0) {
          FUN_00045330(auStack_94);
        }
        FUN_00046bec(iVar9);
        if (*(int *)(iVar23 + 0x38) != 0) {
          FUN_000476f0(auStack_148);
        }
        if (local_bc != (uint **)0x0) {
          FUN_00046bec();
        }
      }
    }
    return;
  case 9:
    pcVar22 = *(code **)(iVar25 + 0x4c);
    fVar37 = *(float *)(pcVar22 + 0x2c);
    fVar36 = *(float *)(pcVar22 + 0x34);
    fVar38 = fVar36;
    if (fVar37 < fVar36) {
      fVar38 = fVar37;
    }
    fVar39 = *(float *)(pcVar22 + 0x3c);
    if ((fVar38 < fVar39) && (fVar39 = fVar36, fVar37 < fVar36)) {
      fVar39 = fVar37;
    }
    local_ec = (undefined4 *)(int)fVar39;
    fVar37 = *(float *)(pcVar22 + 0x30);
    fVar36 = *(float *)(pcVar22 + 0x38);
    fVar38 = fVar36;
    if (fVar37 < fVar36) {
      fVar38 = fVar37;
    }
    fVar39 = *(float *)(pcVar22 + 0x40);
    if ((fVar38 < fVar39) && (fVar39 = fVar36, fVar37 < fVar36)) {
      fVar39 = fVar37;
    }
    local_e8 = (int)fVar39;
    fVar37 = *(float *)(pcVar22 + 0x2c);
    fVar36 = *(float *)(pcVar22 + 0x34);
    fVar38 = fVar36;
    if (fVar36 < fVar37) {
      fVar38 = fVar37;
    }
    fVar39 = *(float *)(pcVar22 + 0x3c);
    if ((fVar39 < fVar38) && (fVar39 = fVar36, fVar36 < fVar37)) {
      fVar39 = fVar37;
    }
    local_e4 = (int)fVar39;
    fVar37 = *(float *)(pcVar22 + 0x30);
    fVar36 = *(float *)(pcVar22 + 0x38);
    fVar38 = fVar36;
    if (fVar36 < fVar37) {
      fVar38 = fVar37;
    }
    fVar39 = *(float *)(pcVar22 + 0x40);
    if ((fVar39 < fVar38) && (fVar39 = fVar36, fVar36 < fVar37)) {
      fVar39 = fVar37;
    }
    local_e0 = (uint)fVar39;
    local_2c = (int *)param_1;
    local_28 = pcVar22;
    iVar25 = FUN_0003db4c(&local_fc,&local_ec,*(undefined4 *)(param_1 + 8));
    if (iVar25 != 0) {
      pcVar28 = pcVar22 + 0x2c;
      pcVar31 = pcVar22 + 0x34;
      pcVar29 = pcVar22 + 0x3c;
      if (*(float *)(pcVar22 + 0x2c) == *(float *)(pcVar22 + 0x34)) {
        FUN_0004f24c(&local_150,pcVar28);
        local_170 = local_150;
        local_16c = local_14c;
        FUN_0004f24c(&local_154,pcVar31);
        local_168 = local_154;
        local_164 = (uint **)local_150;
        FUN_0004f24c(&local_158,pcVar29);
        local_160 = local_158;
        local_15c = local_154;
      }
      else if (*(float *)(pcVar22 + 0x2c) == *(float *)(pcVar22 + 0x3c)) {
        FUN_0004f24c(&local_150,pcVar28);
        local_170 = local_150;
        local_16c = local_14c;
        FUN_0004f24c(&local_154,pcVar29);
        local_168 = local_154;
        local_164 = (uint **)local_150;
        FUN_0004f24c(&local_154,pcVar31);
        local_160 = local_154;
        local_15c = local_150;
      }
      else if (*(float *)(pcVar22 + 0x34) == *(float *)(pcVar22 + 0x3c)) {
        FUN_0004f24c(&local_150,pcVar31);
        local_170 = local_150;
        local_16c = local_14c;
        FUN_0004f24c(&local_150,pcVar29);
        local_168 = local_150;
        local_164 = (uint **)local_14c;
        FUN_0004f24c(&local_150,pcVar28);
        local_160 = local_150;
        local_15c = local_14c;
      }
      else {
        FUN_0004f24c(&local_150,pcVar28);
        local_170 = local_150;
        local_16c = local_14c;
        FUN_0004f24c(&local_154,pcVar31);
        local_168 = local_154;
        local_164 = (uint **)local_150;
        FUN_0004f24c(&local_158,pcVar29);
        local_160 = local_158;
        local_15c = local_154;
        if ((int)local_164 < (int)local_16c) {
          FUN_0004f26c(&local_170,&local_168);
        }
        if ((int)local_15c < (int)local_16c) {
          FUN_0004f26c(&local_170,&local_160);
        }
        if ((int)local_164 < (int)local_15c) {
          FUN_0004f26c(&local_168,&local_160);
        }
      }
      if ((int)local_164 < (int)local_16c) {
        FUN_0004f26c(&local_170,&local_168);
      }
      local_38 = (int *)0x0;
      uVar15 = (uint)(((int)local_16c - (int)local_164) * ((int)local_160 - (int)local_170) +
                     ((int)local_15c - (int)local_16c) * ((int)local_168 - (int)local_170)) >> 0x1f;
      local_34 = 0;
      local_178 = (undefined1 *)local_164;
      local_40 = (undefined4 ***)0x0;
      local_3c = (int **)0x0;
      local_174 = (int *)uVar15;
      FUN_000453c0(&local_78,local_170,local_16c,local_168);
      uVar15 = uVar15 ^ 1;
      local_178 = local_15c;
      local_174 = (int *)uVar15;
      FUN_000453c0(auStack_134,local_170,local_16c,local_160);
      local_174 = (int *)uVar15;
      if (local_164 == (uint **)local_15c) {
        local_174 = (int *)0x2;
      }
      local_178 = local_15c;
      FUN_000453c0(&local_b0,local_168,local_164,local_160);
      local_40 = &local_78;
      local_3c = (int **)auStack_134;
      local_38 = &local_b0;
      puVar19 = (undefined1 *)FUN_0003db28(&local_fc);
      iVar25 = FUN_0004a318();
      local_144 = local_fc;
      local_140 = (int **)local_f8;
      iStack_13c = (int)local_f4;
      local_138 = (int **)local_f8;
      local_c8 = *(int *)(pcVar22 + 0x1c);
      local_b4 = local_b4 & 0xffffff00;
      local_d8 = (int **)0x0;
      bVar34 = (byte)pcVar22[0x2b] & 7;
      local_dc = &local_144;
      local_c4 = iVar25;
      local_bc = (uint **)&local_144;
      uVar33 = FUN_0003db0a(&local_ec);
      uVar20 = FUN_0003db28(&local_ec);
      piVar21 = (int *)FUN_000470ce(pcVar22 + 0x20,uVar20,uVar33);
      iVar23 = 0;
      ppuVar35 = local_f8;
      if ((piVar21 != (int *)0x0) && (bVar34 == 2)) {
        local_d8 = (int **)((int)local_fc * 3 + (int)local_ec * -3 + *piVar21);
        iVar23 = (int)local_fc + (piVar21[1] - (int)local_ec);
        local_d0 = CONCAT31(local_d0._1_3_,0xf);
        local_cc = &local_144;
      }
      for (; (int)ppuVar35 <= (int)local_f0; ppuVar35 = (uint **)((int)ppuVar35 + 1)) {
        local_140 = (int **)ppuVar35;
        local_138 = (int **)ppuVar35;
        FUN_0004a57a(iVar25,0xff,puVar19);
        local_178 = puVar19;
        iVar16 = FUN_000452b4(&local_40,iVar25,local_fc,ppuVar35);
        local_c0 = CONCAT31(local_c0._1_3_,(char)iVar16);
        if (bVar34 == 1) {
          uVar4 = *(undefined3 *)(*piVar21 + ((int)ppuVar35 - local_e8) * 3);
          bVar7 = *(byte *)(piVar21[1] + ((int)ppuVar35 - local_e8));
          local_c8 = CONCAT31(uVar4,bVar7);
          if ((byte)pcVar22[0x1c] < 0xfd) {
            local_c8 = CONCAT31(uVar4,(char)((uint)((int)(short)(ushort)bVar7 *
                                                   (int)(short)(ushort)(byte)pcVar22[0x1c]) >> 8));
          }
LAB_00045f12:
          FUN_0004337c(local_2c,&local_dc);
        }
        else {
          if ((bVar34 != 2) || (iVar23 == 0)) goto LAB_00045f12;
          if (iVar16 == 2) {
            for (iVar16 = 0; local_c4 = iVar25, iVar16 < (int)puVar19; iVar16 = iVar16 + 1) {
              if (*(byte *)(iVar23 + iVar16) < 0xfd) {
                *(char *)(iVar25 + iVar16) =
                     (char)((uint)((int)(short)(ushort)*(byte *)(iVar25 + iVar16) *
                                  (int)(short)(ushort)*(byte *)(iVar23 + iVar16)) >> 8);
              }
            }
            goto LAB_00045f12;
          }
          if (iVar16 == 1) {
            local_c0 = CONCAT31(local_c0._1_3_,2);
            local_c4 = iVar23;
            goto LAB_00045f12;
          }
          if (iVar16 != 0) goto LAB_00045f12;
        }
      }
      FUN_00046bec(iVar25);
      FUN_00045330(&local_b0);
      FUN_00045330(&local_78);
      FUN_00045330(auStack_134);
      if (piVar21 != (int *)0x0) {
        thunk_FUN_00046bec(piVar21);
      }
    }
    return;
  case 10:
    iVar23 = *(int *)(iVar25 + 0x4c);
    iVar25 = FUN_0003db4c(&local_6c,iVar23 + 0x1c,*(undefined4 *)(param_1 + 8));
    if (iVar25 != 0) {
      puVar27 = *(undefined4 **)(param_1 + 4);
      piVar21 = puVar27 + 1;
      uVar33 = *puVar27;
      local_70 = *(int *)(iVar23 + 0x20) - 1;
      puVar14 = *(undefined4 **)(param_1 + 8);
      FUN_0003ddf0(&local_5c,*puVar14,puVar14[1],puVar14[2]);
      FUN_0003ddd6(&local_5c,-*piVar21,-puVar27[2]);
      FUN_000411ca(uVar33,&local_5c);
      puVar14 = *(undefined4 **)(param_1 + 8);
      local_70 = puVar14[3];
      FUN_0003ddf0(&local_5c,*puVar14,*(int *)(iVar23 + 0x28) + 1,puVar14[2]);
      FUN_0003ddd6(&local_5c,-*piVar21,-puVar27[2]);
      FUN_000411ca(uVar33,&local_5c);
      local_70 = *(uint *)(iVar23 + 0x28);
      FUN_0003ddf0(&local_5c,**(undefined4 **)(param_1 + 8),*(undefined4 *)(iVar23 + 0x20),
                   *(int *)(iVar23 + 0x1c) + -1);
      FUN_0003ddd6(&local_5c,-*piVar21,-puVar27[2]);
      FUN_000411ca(uVar33,&local_5c);
      local_70 = *(uint *)(iVar23 + 0x28);
      FUN_0003ddf0(&local_5c,*(int *)(iVar23 + 0x24) + 1,*(undefined4 *)(iVar23 + 0x20),
                   *(undefined4 *)(*(int *)(param_1 + 8) + 8));
      FUN_0003ddd6(&local_5c,-*piVar21,-puVar27[2]);
      FUN_000411ca(uVar33,&local_5c);
      FUN_000454e8(&local_4c,iVar23 + 0x1c,*(undefined4 *)(iVar23 + 0x2c),0);
      local_28 = (code *)&local_4c;
      uVar15 = FUN_0003db28(&local_6c);
      iVar23 = FUN_0004a318();
      for (iVar25 = local_68; iVar25 <= local_60; iVar25 = iVar25 + 1) {
        FUN_0004a57a(iVar23,0xff,uVar15);
        local_70 = uVar15;
        iVar16 = FUN_000452b4(&local_28,iVar23,local_6c,iVar25);
        if (iVar16 != 1) {
          iVar17 = FUN_00042398(puVar27,(int)local_6c - *piVar21,iVar25 - puVar27[2]);
          if (iVar16 == 0) {
            FUN_0004a57a(iVar17,0,uVar15 << 2);
          }
          else {
            for (uVar18 = 0; uVar18 < uVar15; uVar18 = uVar18 + 1) {
              if (*(byte *)(iVar23 + uVar18) != 0xff) {
                iVar16 = iVar17 + uVar18 * 4;
                *(char *)(iVar16 + 3) =
                     (char)((uint)((int)(short)(ushort)*(byte *)(iVar16 + 3) *
                                  (int)(short)(ushort)*(byte *)(iVar23 + uVar18)) >> 8);
              }
            }
          }
        }
      }
      FUN_00046bec(iVar23);
      FUN_00045330(&local_4c);
    }
    return;
  }
  do {
    if (*(char *)(*(int *)(iVar23 + 0x1c) + iVar25) == '\0') break;
    local_f8 = (uint **)(local_c0 + (int)local_f8);
    local_a4 = 0;
    local_d0 = *(int *)(iVar23 + 0x1c) + iVar25;
    local_d4 = local_f8;
    while (local_a4 < (uint)(iVar8 - iVar25)) {
      local_108 = 0;
      if ((uVar15 != 0xffff) && (uVar18 != 0xffff)) {
        local_108 = FUN_00051c60(*(undefined4 *)(iVar23 + 0x1c),iVar25 + local_a4);
      }
      FUN_0005172c(local_d0,&local_c4,&local_c8,&local_a4);
      iVar16 = FUN_00046b72(local_fc,local_c4,local_c8);
      local_b8 = (undefined4 **)local_f4;
      local_104 = (code *)(iVar16 + -1);
      local_b4 = (int)local_104 + (int)local_f8;
      local_bc = local_f8;
      local_b0 = iVar17 + -1 + (int)local_f4;
      if ((uint)(iVar8 - iVar25) <= local_a4) {
        if ((*(byte *)(iVar23 + 0x4c) & 1) != 0) {
          local_44 = local_d4;
          local_3c = (int **)((int)local_104 + (int)local_f8);
          local_40 = (undefined4 ***)
                     ((int)local_f4 +
                     ((local_fc[3] - local_fc[4]) - (int)*(char *)((int)local_fc + 0x15)));
          local_38 = (int *)((int)local_40 + local_ac + -1);
          local_7f = *puVar1;
          local_7d = *(undefined1 *)(iVar23 + 0x2e);
          (*local_28)(local_34,0,&local_a0,&local_44);
        }
        if ((int)((uint)*(byte *)(iVar23 + 0x4c) << 0x1e) < 0) {
          local_44 = local_d4;
          local_3c = (int **)((int)local_104 + (int)local_f8);
          local_40 = (undefined4 ***)
                     (((local_fc[3] - local_fc[4]) * 2) / 3 +
                      (int)*(char *)((int)local_fc + 0x16) / 2 + (int)local_f4);
          local_38 = (int *)(local_ac + -1 + (int)local_40);
          local_7f = *puVar1;
          local_7d = *(undefined1 *)(iVar23 + 0x2e);
          (*local_28)(local_34,0,&local_a0,&local_44);
        }
      }
      if ((((uVar15 == 0xffff) || (uVar18 == 0xffff)) || (local_108 < uVar15)) ||
         (uVar18 <= local_108)) {
        local_5c = *puVar1;
        local_5a = *(undefined1 *)(iVar23 + 0x2e);
      }
      else {
        local_5c = *(undefined2 *)(iVar23 + 0x2f);
        local_5a = *(undefined1 *)(iVar23 + 0x31);
        local_7f = *(undefined2 *)(iVar23 + 0x32);
        local_7d = *(undefined1 *)(iVar23 + 0x34);
        (*local_28)(local_34,0,&local_a0,&local_bc);
      }
      local_108 = local_c4;
      local_104 = local_28;
      FUN_0002cb6c(local_34,&local_70,&local_f8,local_fc);
      if (0 < iVar16) {
        local_f8 = (uint **)((int)local_f8 + iVar16 + *(int *)(iVar23 + 0x3c));
      }
    }
    local_104 = (code *)(uint)*(byte *)(iVar23 + 0x4b);
    local_108 = 0;
    iVar16 = FUN_0005175c(*(int *)(iVar23 + 0x1c) + iVar8,local_fc,*(undefined4 *)(iVar23 + 0x3c),
                          local_f0);
    iVar16 = iVar16 + iVar8;
    local_f8 = (uint **)*local_2c;
    if (local_e0 == 2) {
      iVar25 = FUN_00051a28(*(int *)(iVar23 + 0x1c) + iVar8,iVar16 - iVar8,local_fc,
                            *(undefined4 *)(iVar23 + 0x3c));
      iVar9 = FUN_0003db28(local_2c);
      local_f8 = (uint **)((int)local_f8 + (iVar9 - iVar25) / 2);
    }
    else if (local_e0 == 3) {
      iVar25 = FUN_00051a28(*(int *)(iVar23 + 0x1c) + iVar8,iVar16 - iVar8,local_fc,
                            *(undefined4 *)(iVar23 + 0x3c));
      iVar9 = FUN_0003db28(local_2c);
      local_f8 = (uint **)((iVar9 - iVar25) + (int)local_f8);
    }
    local_f4 = (uint *)((int)local_f4 + iVar17);
    iVar25 = iVar8;
    iVar8 = iVar16;
  } while ((int)local_f4 <= *(int *)(*(int *)(local_34 + 8) + 0xc));
  if (local_58 != 0) {
    FUN_000413fe();
  }
  return;
}

