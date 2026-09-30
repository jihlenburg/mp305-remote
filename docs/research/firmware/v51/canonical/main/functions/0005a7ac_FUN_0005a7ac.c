/* Address: 0005a7ac; name: FUN_0005a7ac; body bytes: 620 */

void FUN_0005a7ac(undefined4 param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 local_c0;
  int local_bc;
  undefined4 local_b8;
  int local_b4;
  undefined4 local_b0;
  int local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined1 auStack_a0 [28];
  int local_84;
  int local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_60;
  int local_5c;
  undefined2 local_54;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_38;
  char local_34 [4];
  undefined4 *local_30;
  undefined4 local_2c;
  int iStack_28;
  
  local_2c = param_1;
  iStack_28 = param_2;
  iVar3 = FUN_0004cd84(param_2,1);
  if ((iVar3 == 0) && (bVar1 = FUN_0004c924(param_2,0,0x60), 1 < bVar1)) {
    iVar3 = FUN_0004bc3e(param_2);
    if (iVar3 == 0) {
      FUN_0004d798(local_2c,param_2);
      return;
    }
    iVar4 = FUN_0003be80(local_2c,param_2,iVar3,&local_b0,&local_d0);
    if (iVar4 == 1) {
      iVar4 = FUN_0003db0a(&local_b0);
      uVar5 = FUN_0003db0a(&local_b0);
      if (iVar3 == 1) {
        iVar3 = FUN_0003db28(&local_b0);
        iVar4 = FUN_0004034e(*(undefined1 *)(DAT_2003a430 + 0x3b));
        iVar4 = (0x6000 / iVar3) / iVar4;
        uVar5 = (uint)(0x6000 / iVar3) >> 2;
      }
      local_c0 = local_b0;
      local_b8 = local_a8;
      local_bc = local_ac;
      local_b4 = local_ac;
      iVar3 = param_2 + 0x14;
      while (local_b4 < local_a4) {
        local_b4 = iVar4 + -1 + local_bc;
        if (local_a4 < local_b4) {
          local_b4 = local_a4;
        }
        iVar6 = FUN_0003dc12(&local_c0,iVar3);
        if (iVar6 == 0) {
LAB_0005a88e:
          local_b4 = (uVar5 - 1) + local_bc;
          if (local_a4 < local_b4) {
            local_b4 = local_a4;
          }
          uVar11 = 0x10;
        }
        else {
          local_34[0] = '\0';
          local_30 = &local_c0;
          FUN_0004e5a6(param_2,0x17,local_34);
          if (local_34[0] != '\0') goto LAB_0005a88e;
          uVar11 = 0x12;
        }
        iVar6 = FUN_0004233c(local_2c,uVar11,&local_c0);
        FUN_0004d798(iVar6,param_2);
        uVar7 = FUN_0004c924(param_2,0,0x6f);
        uVar8 = FUN_0004c924(param_2,0,0x70);
        if (((uVar7 & 0x7fffffff) >> 0x1d == 1) &&
           (uVar9 = uVar7 & 0x9fffffff, (int)uVar9 < 0x1fffffff)) {
          iVar10 = FUN_0003db28(iVar3);
          if (0xfffffff < (int)uVar9) {
            uVar9 = 0xfffffff - uVar9;
          }
          uVar7 = (int)(uVar9 * iVar10) / 100;
        }
        if (((uVar8 & 0x7fffffff) >> 0x1d == 1) &&
           (uVar9 = uVar8 & 0x9fffffff, (int)uVar9 < 0x1fffffff)) {
          iVar10 = FUN_0003db0a(iVar3);
          if (0xfffffff < (int)(uVar8 & 0x9fffffff)) {
            uVar9 = 0xfffffff - uVar9;
          }
          uVar8 = (int)(uVar9 * iVar10) / 100;
        }
        FUN_00041b74(auStack_a0);
        local_60 = (*(int *)(param_2 + 0x14) + uVar7) - *(int *)(iVar6 + 4);
        local_5c = (*(int *)(param_2 + 0x18) + uVar8) - *(int *)(iVar6 + 8);
        local_54._0_1_ = bVar1;
        for (local_74 = FUN_0004c924(param_2,0,0x6e); 0xe10 < local_74; local_74 = local_74 + -0xe10
            ) {
        }
        for (; local_74 < 0; local_74 = local_74 + 0xe10) {
        }
        local_70 = FUN_0004c924(param_2,0,0x6c);
        local_6c = FUN_0004c924(param_2,0,0x6d);
        local_68 = FUN_0004c924(param_2,0,0x71);
        local_64 = FUN_0004c924(param_2,0,0x72);
        bVar2 = FUN_0004c924(param_2,0,0x67);
        local_54 = CONCAT11(local_54._1_1_ & 0xf0 | bVar2 & 0xf,(byte)local_54);
        local_54 = local_54 & 0xefff | (ushort)((*(uint *)(DAT_2003a430 + 0x38) >> 0x10 & 1) << 0xc)
        ;
        local_38 = FUN_0004c924(param_2,0,0x73);
        local_4c = local_d0;
        uStack_48 = uStack_cc;
        uStack_44 = uStack_c8;
        uStack_40 = uStack_c4;
        local_84 = iVar6;
        FUN_00042244(local_2c,auStack_a0,&local_c0);
        local_bc = local_b4 + 1;
      }
    }
  }
  return;
}

