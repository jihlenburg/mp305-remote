/* Address: 00031c68; name: FUN_00031c68; body bytes: 1088 */

void FUN_00031c68(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auStack_14c [8];
  int local_144;
  uint local_140;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  undefined2 local_120;
  undefined1 local_11e;
  int local_11c;
  byte local_10f;
  int local_104;
  undefined1 auStack_100 [8];
  int local_f8;
  int local_f4;
  undefined2 local_df;
  undefined1 local_dd;
  int local_8c;
  int local_88;
  undefined4 local_84;
  undefined4 uStack_80;
  int local_7c;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  uint local_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int local_48;
  undefined1 auStack_44 [16];
  
  iVar4 = FUN_0003db4c(&local_58,param_1 + 0x14,param_2 + 0x18);
  if (iVar4 != 0) {
    iVar4 = *(int *)(param_2 + 0x18);
    local_84 = *(undefined4 *)(param_2 + 0x1c);
    iVar10 = *(int *)(param_2 + 0x20);
    uStack_80 = *(undefined4 *)(param_2 + 0x24);
    *(undefined4 *)(param_2 + 0x18) = local_58;
    *(undefined4 *)(param_2 + 0x1c) = uStack_54;
    *(undefined4 *)(param_2 + 0x20) = uStack_50;
    *(undefined4 *)(param_2 + 0x24) = uStack_4c;
    if (1 < *(uint *)(param_1 + 0x70)) {
      iVar5 = FUN_0004c696(param_1,0);
      iVar6 = FUN_0004c858(param_1,0);
      iVar7 = FUN_0004c8f4(param_1,0);
      local_88 = FUN_0004bb1a(param_1);
      local_104 = FUN_0004baf8(param_1);
      local_74 = FUN_0004bd90(param_1);
      local_74 = (*(int *)(param_1 + 0x14) + iVar6 + iVar5) - local_74;
      local_60 = FUN_0004bf14(param_1);
      local_60 = (*(int *)(param_1 + 0x18) + iVar5 + iVar7) - local_60;
      iVar5 = FUN_0003db4c(auStack_44,param_1 + 0x14,param_2 + 0x18);
      if (iVar5 != 0) {
        FUN_00042462(auStack_14c);
        FUN_0004cff4(param_1,&LAB_00050000,auStack_14c);
        FUN_00042ec4(auStack_100);
        FUN_0004d0bc(param_1,0x20000,auStack_100);
        iVar6 = FUN_0004cbe4(param_1,0x20000);
        iVar6 = iVar6 / 2;
        iVar7 = FUN_0004c6d2(param_1,0x20000);
        iVar7 = iVar7 / 2;
        iVar5 = iVar7;
        if (iVar6 < iVar7) {
          iVar5 = iVar6;
        }
        if (local_11c / 2 < iVar5) {
          local_10f = local_10f | 0x10;
        }
        if (local_11c == 1) {
          local_10f = local_10f | 0x10;
        }
        local_5c = (uint)(local_88 <= *(int *)(param_1 + 0x70));
        local_8c = param_1 + 0x2c;
        local_144 = FUN_0004a120();
        local_144 = local_144 + -1;
        local_f8 = local_144;
        for (iVar5 = FUN_0004a14a(param_1 + 0x2c); iVar5 != 0; iVar5 = FUN_0004a144(local_8c,iVar5))
        {
          if ((*(byte *)(iVar5 + 0x10) & 1) == 0) {
            local_120 = *(undefined2 *)(iVar5 + 8);
            local_11e = *(undefined1 *)(iVar5 + 10);
            local_df = *(undefined2 *)(iVar5 + 8);
            local_dd = *(undefined1 *)(iVar5 + 10);
            local_140 = 0;
            local_f4 = 0;
            if ((int)((uint)*(byte *)(param_1 + 0x74) << 0x1c) < 0) {
              local_7c = 0;
            }
            else {
              local_7c = *(int *)(iVar5 + 0xc);
            }
            local_130 = (float)VectorSignedToFloat(local_74,(byte)(in_fpscr >> 0x16) & 3);
            local_128 = (float)VectorSignedToFloat(local_74,(byte)(in_fpscr >> 0x16) & 3);
            iVar9 = param_1 + ((int)((uint)*(byte *)(iVar5 + 0x10) << 0x1b) >> 0x1f) * -4;
            iVar8 = *(int *)(iVar9 + 0x44);
            uVar11 = 0;
            fVar16 = (float)VectorSignedToFloat(local_60 +
                                                (local_104 -
                                                (local_104 *
                                                (*(int *)(*(int *)(iVar5 + 4) + local_7c * 4) -
                                                iVar8)) / (*(int *)(iVar9 + 0x4c) - iVar8)),
                                                (byte)(in_fpscr >> 0x16) & 3);
            local_48 = local_7c;
            fVar17 = fVar16;
            local_124 = fVar16;
            for (; uVar11 < *(uint *)(param_1 + 0x70); uVar11 = uVar11 + 1) {
              local_130 = local_128;
              local_12c = local_124;
              fVar13 = (float)VectorSignedToFloat(iVar6 + 1 + iVar10,(byte)(in_fpscr >> 0x16) & 3);
              uVar1 = in_fpscr & 0xfffffff;
              uVar2 = uVar1 | (uint)(local_128 < fVar13) << 0x1f |
                      (uint)(local_128 == fVar13) << 0x1e;
              in_fpscr = uVar2 | (uint)(NAN(local_128) || NAN(fVar13)) << 0x1c;
              bVar3 = (byte)(uVar2 >> 0x18);
              if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) break;
              fVar13 = (float)VectorUnsignedToFloat
                                        ((uVar11 * local_88) / (*(int *)(param_1 + 0x70) - 1U),
                                         (byte)(in_fpscr >> 0x16) & 3);
              fVar14 = (float)VectorSignedToFloat(local_74,(byte)(in_fpscr >> 0x16) & 3);
              fVar13 = fVar13 + fVar14;
              iVar12 = (local_7c + uVar11) -
                       *(uint *)(param_1 + 0x70) * ((local_7c + uVar11) / *(uint *)(param_1 + 0x70))
              ;
              iVar9 = param_1 + ((int)((uint)*(byte *)(iVar5 + 0x10) << 0x1b) >> 0x1f) * -4;
              iVar8 = *(int *)(iVar9 + 0x44);
              fVar14 = (float)VectorSignedToFloat(local_60 +
                                                  (local_104 -
                                                  (local_104 *
                                                  (*(int *)(*(int *)(iVar5 + 4) + iVar12 * 4) -
                                                  iVar8)) / (*(int *)(iVar9 + 0x4c) - iVar8)),
                                                  (byte)(in_fpscr >> 0x16) & 3);
              fVar15 = (float)VectorSignedToFloat((iVar4 - iVar6) + -1,(byte)(in_fpscr >> 0x16) & 3)
              ;
              in_fpscr = uVar1 | (uint)(fVar15 <= fVar13) << 0x1d;
              if (((byte)(in_fpscr >> 0x1d) != 0) && (uVar11 != 0)) {
                if (local_5c == 0) {
                  local_70 = (int)local_128 - iVar6;
                  local_68 = (int)local_128 + iVar6;
                  local_6c = (int)local_124 - iVar7;
                  local_64 = (int)local_124 + iVar7;
                  local_128 = fVar13;
                  local_124 = fVar14;
                  if ((*(int *)(*(int *)(iVar5 + 4) + local_48 * 4) != 0x7fffffff) &&
                     (*(int *)(*(int *)(iVar5 + 4) + iVar12 * 4) != 0x7fffffff)) {
                    local_140 = uVar11;
                    FUN_000423a0(param_2,auStack_14c);
                  }
                  fVar13 = local_128;
                  fVar14 = local_124;
                  if (((iVar6 != 0) && (iVar7 != 0)) &&
                     (*(int *)(*(int *)(iVar5 + 4) + local_48 * 4) != 0x7fffffff)) {
                    local_f4 = uVar11 - 1;
                    FUN_00042a98(param_2,auStack_100,&local_70);
                    fVar13 = local_128;
                    fVar14 = local_124;
                  }
                }
                else if ((*(int *)(*(int *)(iVar5 + 4) + local_48 * 4) != 0x7fffffff) &&
                        (*(int *)(*(int *)(iVar5 + 4) + iVar12 * 4) != 0x7fffffff)) {
                  local_124 = fVar17;
                  if (fVar17 <= fVar14) {
                    local_124 = fVar14;
                  }
                  if (fVar14 <= fVar16) {
                    fVar16 = fVar14;
                  }
                  in_fpscr = uVar1 | (uint)(local_128 == fVar13) << 0x1e;
                  fVar17 = local_124;
                  if ((byte)(in_fpscr >> 0x1e) == 0) {
                    local_130 = fVar13 - 1.0;
                    in_fpscr = uVar1 | (uint)(fVar16 == local_124) << 0x1e;
                    if ((byte)(in_fpscr >> 0x1e) != 0) {
                      local_124 = local_124 + 1.0;
                    }
                    local_12c = fVar16;
                    local_128 = local_130;
                    FUN_000423a0(param_2,auStack_14c);
                    fVar16 = fVar14;
                    fVar17 = fVar14;
                    fVar13 = local_128 + 1.0;
                    fVar14 = local_124;
                  }
                }
              }
              local_124 = fVar14;
              local_128 = fVar13;
              local_48 = iVar12;
            }
            if (((local_5c == 0) && (*(uint *)(param_1 + 0x70) == uVar11)) &&
               (*(int *)(*(int *)(iVar5 + 4) + local_48 * 4) != 0x7fffffff)) {
              local_f4 = uVar11 - 1;
              local_70 = (int)local_128 - iVar6;
              local_68 = (int)local_128 + iVar6;
              local_6c = (int)local_124 - iVar7;
              local_64 = (int)local_124 + iVar7;
              FUN_00042a98(param_2,auStack_100,&local_70);
            }
          }
          local_f8 = local_f8 + -1;
          local_144 = local_144 + -1;
        }
        *(int *)(param_2 + 0x18) = iVar4;
        *(undefined4 *)(param_2 + 0x1c) = local_84;
        *(int *)(param_2 + 0x20) = iVar10;
        *(undefined4 *)(param_2 + 0x24) = uStack_80;
      }
    }
  }
  return;
}

