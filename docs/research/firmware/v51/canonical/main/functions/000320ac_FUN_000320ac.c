/* Address: 000320ac; name: FUN_000320ac; body bytes: 932 */

void FUN_000320ac(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  undefined1 auStack_134 [8];
  int local_12c;
  uint local_128;
  undefined2 local_113;
  undefined1 local_111;
  undefined1 auStack_c4 [8];
  int local_bc;
  uint local_b8;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  undefined2 local_98;
  undefined1 local_96;
  int local_94;
  byte local_87;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  int local_74;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  
  iVar1 = FUN_0003db4c(&local_60,param_1 + 0x14,param_2 + 0x18);
  if (iVar1 != 0) {
    local_84 = *(undefined4 *)(param_2 + 0x18);
    uStack_80 = *(undefined4 *)(param_2 + 0x1c);
    local_7c = *(undefined4 *)(param_2 + 0x20);
    uStack_78 = *(undefined4 *)(param_2 + 0x24);
    *(undefined4 *)(param_2 + 0x18) = local_60;
    *(undefined4 *)(param_2 + 0x1c) = uStack_5c;
    *(undefined4 *)(param_2 + 0x20) = uStack_58;
    *(undefined4 *)(param_2 + 0x24) = uStack_54;
    iVar1 = FUN_0004c696(param_1,0);
    iVar2 = FUN_0004c858(param_1,0);
    iVar3 = FUN_0004c8f4(param_1,0);
    local_4c = FUN_0004bb1a(param_1);
    uVar4 = FUN_0004baf8(param_1);
    local_48 = FUN_0004bd90(param_1);
    local_48 = (*(int *)(param_1 + 0x14) + iVar2 + iVar1) - local_48;
    local_44 = FUN_0004bf14(param_1);
    local_44 = (iVar3 + iVar1 + *(int *)(param_1 + 0x18)) - local_44;
    FUN_00042462(auStack_c4);
    FUN_0004cff4(param_1,&LAB_00050000,auStack_c4);
    FUN_00042ec4(auStack_134);
    FUN_0004d0bc(param_1,0x20000,auStack_134);
    iVar1 = FUN_0004cbe4(param_1,0x20000);
    iVar1 = iVar1 / 2;
    iVar3 = FUN_0004c6d2(param_1,0x20000);
    iVar3 = iVar3 / 2;
    iVar2 = iVar1;
    if (iVar3 <= iVar1) {
      iVar2 = iVar3;
    }
    if (local_94 / 2 < iVar2) {
      local_87 = local_87 | 0x10;
    }
    if (local_94 == 1) {
      local_87 = local_87 | 0x10;
    }
    local_74 = param_1 + 0x2c;
    for (piVar5 = (int *)FUN_0004a14a(); piVar5 != (int *)0x0;
        piVar5 = (int *)FUN_0004a144(local_74,piVar5)) {
      if ((*(byte *)(piVar5 + 4) & 1) == 0) {
        local_98 = (undefined2)piVar5[2];
        local_96 = *(undefined1 *)((int)piVar5 + 10);
        local_113 = (undefined2)piVar5[2];
        local_111 = *(undefined1 *)((int)piVar5 + 10);
        if ((int)((uint)*(byte *)(param_1 + 0x74) << 0x1c) < 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = piVar5[3];
        }
        local_a8 = (float)VectorSignedToFloat(local_48,(byte)(in_fpscr >> 0x16) & 3);
        local_a0 = (float)VectorSignedToFloat(local_48,(byte)(in_fpscr >> 0x16) & 3);
        local_40 = iVar2;
        if (*(int *)(piVar5[1] + iVar2 * 4) == 10) {
          local_9c = -5.368709e+08;
          local_a0 = -5.368709e+08;
        }
        else {
          iVar8 = param_1 + ((int)((uint)*(byte *)(piVar5 + 4) << 0x1c) >> 0x1f) * -4;
          uVar6 = FUN_0004a388(*(undefined4 *)(*piVar5 + iVar2 * 4),*(undefined4 *)(iVar8 + 0x54),
                               *(undefined4 *)(iVar8 + 0x5c),0,local_4c);
          local_a0 = (float)VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
          fVar11 = (float)VectorSignedToFloat(local_48,(byte)(in_fpscr >> 0x16) & 3);
          local_a0 = local_a0 + fVar11;
          iVar8 = param_1 + ((int)((uint)*(byte *)(piVar5 + 4) << 0x1b) >> 0x1f) * -4;
          uVar6 = FUN_0004a388(*(undefined4 *)(piVar5[1] + iVar2 * 4),*(undefined4 *)(iVar8 + 0x44),
                               *(undefined4 *)(iVar8 + 0x4c),0,uVar4);
          fVar12 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
          fVar11 = (float)VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
          local_9c = (float)VectorSignedToFloat(local_44,(byte)(in_fpscr >> 0x16) & 3);
          local_9c = (fVar12 - fVar11) + local_9c;
        }
        for (uVar9 = 0; uVar9 < *(uint *)(param_1 + 0x70); uVar9 = uVar9 + 1) {
          local_a8 = local_a0;
          local_a4 = local_9c;
          iVar10 = (iVar2 + uVar9) -
                   *(uint *)(param_1 + 0x70) * ((iVar2 + uVar9) / *(uint *)(param_1 + 0x70));
          iVar7 = *(int *)(piVar5[1] + iVar10 * 4);
          iVar8 = iVar10;
          if (iVar7 != 0x7fffffff) {
            iVar8 = param_1 + ((int)((uint)*(byte *)(piVar5 + 4) << 0x1b) >> 0x1f) * -4;
            uVar6 = FUN_0004a388(iVar7,*(undefined4 *)(iVar8 + 0x44),*(undefined4 *)(iVar8 + 0x4c),0
                                 ,uVar4);
            fVar12 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
            fVar11 = (float)VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
            local_9c = (float)VectorSignedToFloat(local_44,(byte)(in_fpscr >> 0x16) & 3);
            local_9c = (fVar12 - fVar11) + local_9c;
            iVar8 = param_1 + ((int)((uint)*(byte *)(piVar5 + 4) << 0x1c) >> 0x1f) * -4;
            uVar6 = FUN_0004a388(*(undefined4 *)(*piVar5 + iVar10 * 4),*(undefined4 *)(iVar8 + 0x54)
                                 ,*(undefined4 *)(iVar8 + 0x5c),0,local_4c);
            local_a0 = (float)VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
            fVar11 = (float)VectorSignedToFloat(local_48,(byte)(in_fpscr >> 0x16) & 3);
            local_a0 = local_a0 + fVar11;
            iVar8 = local_40;
            if (uVar9 != 0) {
              local_3c = (int)local_a8 - iVar1;
              local_34 = (int)local_a8 + iVar1;
              local_38 = (int)local_a4 - iVar3;
              local_30 = (int)local_a4 + iVar3;
              iVar8 = iVar10;
              if ((((*(int *)(piVar5[1] + local_40 * 4) != 0x7fffffff) &&
                   (*(int *)(piVar5[1] + iVar10 * 4) != 0x7fffffff)) &&
                  (local_b8 = uVar9, FUN_000423a0(param_2,auStack_c4), iVar1 != 0)) && (iVar3 != 0))
              {
                local_128 = uVar9;
                FUN_00042a98(param_2,auStack_134,&local_3c);
              }
            }
            local_40 = iVar8;
            iVar8 = local_40;
            if ((*(uint *)(param_1 + 0x70) == uVar9) &&
               (*(int *)(piVar5[1] + iVar10 * 4) != 0x7fffffff)) {
              local_3c = (int)local_a0 - iVar1;
              local_34 = (int)local_a0 + iVar1;
              local_38 = (int)local_9c - iVar3;
              local_30 = (int)local_9c + iVar3;
              local_128 = uVar9;
              FUN_00042a98(param_2,auStack_134,&local_3c);
              iVar8 = local_40;
            }
          }
          local_40 = iVar8;
        }
        local_bc = local_bc + 1;
        local_12c = local_12c + 1;
        *(undefined4 *)(param_2 + 0x18) = local_84;
        *(undefined4 *)(param_2 + 0x1c) = uStack_80;
        *(undefined4 *)(param_2 + 0x20) = local_7c;
        *(undefined4 *)(param_2 + 0x24) = uStack_78;
      }
    }
  }
  return;
}

