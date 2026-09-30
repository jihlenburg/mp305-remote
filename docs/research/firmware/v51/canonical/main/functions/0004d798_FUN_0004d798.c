/* Address: 0004d798; name: FUN_0004d798; body bytes: 672 */

void FUN_0004d798(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  undefined4 local_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 local_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 local_f8;
  int local_f4;
  undefined4 uStack_f0;
  int local_ec;
  undefined4 local_e8;
  int iStack_e4;
  undefined4 uStack_e0;
  int local_dc;
  undefined4 local_d8;
  int iStack_d4;
  undefined4 local_d0;
  int iStack_cc;
  undefined1 auStack_c8 [28];
  undefined4 local_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  int local_9c;
  undefined1 auStack_98 [28];
  undefined4 local_7c;
  undefined1 auStack_2c [16];
  
  local_128 = *(undefined4 *)(param_1 + 0x18);
  uStack_124 = *(undefined4 *)(param_1 + 0x1c);
  uStack_120 = *(undefined4 *)(param_1 + 0x20);
  uStack_11c = *(undefined4 *)(param_1 + 0x24);
  FUN_0004bb3c(param_2,auStack_2c);
  uVar1 = FUN_0004bbb0(param_2);
  FUN_0003db32(auStack_2c,uVar1,uVar1);
  iVar2 = FUN_0003db4c(&local_118,&local_128,auStack_2c);
  if (iVar2 == 0) {
    return;
  }
  *(undefined4 *)(param_1 + 0x18) = local_118;
  *(undefined4 *)(param_1 + 0x1c) = uStack_114;
  *(undefined4 *)(param_1 + 0x20) = uStack_110;
  *(undefined4 *)(param_1 + 0x24) = uStack_10c;
  FUN_0004e5a6(param_2,0x19,param_1);
  FUN_0004e5a6(param_2,0x1a,param_1);
  FUN_0004e5a6(param_2,0x1b,param_1);
  iVar2 = FUN_0004cd84(param_2,0x100000);
  puVar3 = (undefined1 *)(param_2 + 0x14);
  puVar7 = puVar3;
  if (iVar2 != 0) {
    puVar7 = auStack_2c;
  }
  iVar2 = FUN_0003db4c(&local_108,&local_128,puVar7);
  if (iVar2 == 0) goto LAB_0004da26;
  uVar4 = FUN_0004ba5c(param_2);
  if (uVar4 == 0) {
LAB_0004d8a6:
    *(undefined4 *)(param_1 + 0x18) = local_118;
    *(undefined4 *)(param_1 + 0x1c) = uStack_114;
    *(undefined4 *)(param_1 + 0x20) = uStack_110;
    *(undefined4 *)(param_1 + 0x24) = uStack_10c;
  }
  else {
    *(undefined4 *)(param_1 + 0x18) = local_108;
    *(undefined4 *)(param_1 + 0x1c) = uStack_104;
    *(undefined4 *)(param_1 + 0x20) = uStack_100;
    *(undefined4 *)(param_1 + 0x24) = uStack_fc;
    iVar2 = FUN_0004c924(param_2,0,0x2d);
    if ((iVar2 == 0) || (iVar2 = FUN_0004c924(param_2,0,0xc), iVar2 == 0)) {
      for (uVar8 = 0; uVar8 < uVar4; uVar8 = uVar8 + 1) {
        FUN_0005a7ac(param_1,*(undefined4 *)(**(int **)(param_2 + 8) + uVar8 * 4));
      }
      goto LAB_0004d8a6;
    }
    FUN_00042a4c(auStack_c8);
    local_ac = *(undefined4 *)(param_2 + 0x14);
    uStack_a8 = *(undefined4 *)(param_2 + 0x18);
    uStack_a4 = *(undefined4 *)(param_2 + 0x1c);
    uStack_a0 = *(undefined4 *)(param_2 + 0x20);
    local_9c = iVar2;
    FUN_00041b74(auStack_98);
    iVar5 = FUN_0003db28(puVar3);
    iVar6 = FUN_0003db0a(puVar3);
    if (iVar5 < iVar6) {
      iVar5 = FUN_0003db28();
    }
    else {
      iVar5 = FUN_0003db0a(puVar3);
    }
    iVar5 = iVar5 >> 1;
    if (iVar2 < iVar5) {
      iVar5 = iVar2;
    }
    local_d0 = *(undefined4 *)(param_2 + 0x1c);
    iStack_cc = *(int *)(param_2 + 0x20);
    local_d8 = *(undefined4 *)(param_2 + 0x14);
    iStack_d4 = (iStack_cc - iVar5) + 1;
    iVar2 = FUN_0003db4c(&local_d8,&local_d8,&local_128);
    if (iVar2 != 0) {
      uVar1 = FUN_0004233c(param_1,0x10,&local_d8);
      for (uVar8 = 0; uVar8 < uVar4; uVar8 = uVar8 + 1) {
        FUN_0005a7ac(uVar1,*(undefined4 *)(**(int **)(param_2 + 8) + uVar8 * 4));
      }
      FUN_0004e5a6(param_2,0x1c,uVar1);
      FUN_0004e5a6(param_2,0x1d,uVar1);
      FUN_0004e5a6(param_2,0x1e,uVar1);
      FUN_000429dc(uVar1,auStack_c8);
      local_7c = uVar1;
      FUN_00042244(param_1,auStack_98,&local_d8);
    }
    local_e8 = *(undefined4 *)(param_2 + 0x14);
    iStack_e4 = *(int *)(param_2 + 0x18);
    uStack_e0 = *(undefined4 *)(param_2 + 0x1c);
    local_dc = iVar5 + -1 + iStack_e4;
    iVar2 = FUN_0003db4c(&local_e8,&local_e8,&local_128);
    if (iVar2 != 0) {
      uVar1 = FUN_0004233c(param_1,0x10,&local_e8);
      for (uVar8 = 0; uVar8 < uVar4; uVar8 = uVar8 + 1) {
        FUN_0005a7ac(uVar1,*(undefined4 *)(**(int **)(param_2 + 8) + uVar8 * 4));
      }
      FUN_0004e5a6(param_2,0x1c,uVar1);
      FUN_0004e5a6(param_2,0x1d,uVar1);
      FUN_0004e5a6(param_2,0x1e,uVar1);
      FUN_000429dc(uVar1,auStack_c8);
      local_7c = uVar1;
      FUN_00042244(param_1,auStack_98,&local_e8);
    }
    local_f8 = *(undefined4 *)(param_2 + 0x14);
    uStack_f0 = *(undefined4 *)(param_2 + 0x1c);
    local_f4 = *(int *)(param_2 + 0x18) + iVar5;
    local_ec = *(int *)(param_2 + 0x20) - iVar5;
    iVar2 = FUN_0003db4c(&local_f8,&local_f8,&local_128);
    if (iVar2 == 0) goto LAB_0004da26;
    *(undefined4 *)(param_1 + 0x18) = local_f8;
    *(int *)(param_1 + 0x1c) = local_f4;
    *(undefined4 *)(param_1 + 0x20) = uStack_f0;
    *(int *)(param_1 + 0x24) = local_ec;
    for (uVar8 = 0; uVar8 < uVar4; uVar8 = uVar8 + 1) {
      FUN_0005a7ac(param_1,*(undefined4 *)(**(int **)(param_2 + 8) + uVar8 * 4));
    }
  }
  FUN_0004e5a6(param_2,0x1c,param_1);
  FUN_0004e5a6(param_2,0x1d,param_1);
  FUN_0004e5a6(param_2,0x1e,param_1);
LAB_0004da26:
  *(undefined4 *)(param_1 + 0x18) = local_128;
  *(undefined4 *)(param_1 + 0x1c) = uStack_124;
  *(undefined4 *)(param_1 + 0x20) = uStack_120;
  *(undefined4 *)(param_1 + 0x24) = uStack_11c;
  return;
}

