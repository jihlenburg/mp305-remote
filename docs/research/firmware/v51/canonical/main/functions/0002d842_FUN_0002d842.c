/* Address: 0002d842; name: FUN_0002d842; body bytes: 566 */

void FUN_0002d842(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 auStack_c4 [28];
  undefined4 local_a8;
  undefined4 local_a4;
  int local_a0;
  int local_9c;
  undefined2 local_95;
  undefined1 local_93;
  undefined2 local_92;
  undefined1 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  int local_84;
  int local_80;
  char local_7a;
  undefined1 local_79;
  int local_74;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined1 auStack_54 [12];
  undefined4 local_48;
  int local_34 [2];
  int local_2c;
  int local_28;
  
  iVar2 = FUN_00046698();
  iVar3 = FUN_00046718(param_1);
  FUN_0004bab4(iVar2,auStack_54);
  uVar4 = FUN_000375a2(iVar2);
  FUN_00041db4(auStack_c4);
  local_a8 = *(undefined4 *)(iVar2 + 0x2c);
  local_84 = *(int *)(iVar2 + 0x54);
  local_80 = *(undefined4 *)(iVar2 + 0x58);
  if (((*(byte *)(iVar2 + 0x5c) & 7) != 3) && (iVar5 = FUN_0003db0a(auStack_54), 0x3ff < iVar5)) {
    local_74 = iVar2 + 0x38;
  }
  local_79 = (undefined1)uVar4;
  FUN_0004cf40(iVar2,0,auStack_c4);
  if (local_7a == '\0') {
    local_7a = '\x01';
  }
  local_a0 = *(int *)(iVar2 + 0x44);
  local_9c = *(int *)(iVar2 + 0x48);
  if ((local_a0 != 0xffff) && (local_9c != 0xffff)) {
    uVar6 = FUN_0004c924(iVar2,0x40000,0x58);
    uVar6 = FUN_0004eb66(iVar2,0x40000,uVar6);
    local_95 = (undefined2)uVar6;
    local_93 = (undefined1)((uint)uVar6 >> 0x10);
    uVar6 = FUN_0004c924(iVar2,0x40000,0x1c);
    local_92 = (undefined2)uVar6;
    local_90 = (undefined1)((uint)uVar6 >> 0x10);
  }
  bVar1 = *(byte *)(iVar2 + 0x5c) & 7;
  if (((bVar1 == 2) || (bVar1 == 3)) && ((local_7a == '\x02' || (local_7a == '\x03')))) {
    FUN_00051970(local_34,*(undefined4 *)(iVar2 + 0x2c),local_a4,local_88,local_8c,0x1fffffff,uVar4)
    ;
    iVar5 = FUN_0003db28(auStack_54);
    if (iVar5 < local_34[0]) {
      local_7a = '\x01';
    }
  }
  iVar5 = FUN_0003db4c(&local_6c,auStack_54,iVar3 + 0x18);
  if (iVar5 != 0) {
    if ((*(byte *)(iVar2 + 0x5c) & 7) == 0) {
      iVar5 = FUN_0004bf14(iVar2);
      FUN_0003ddd6(auStack_54,0,-iVar5);
      local_48 = *(undefined4 *)(iVar2 + 0x20);
    }
    bVar1 = *(byte *)(iVar2 + 0x5c) & 7;
    if ((bVar1 == 2) || (bVar1 == 3)) {
      uVar8 = *(undefined4 *)(iVar3 + 0x1c);
      uVar6 = *(undefined4 *)(iVar3 + 0x20);
      uVar9 = *(undefined4 *)(iVar3 + 0x24);
      uVar7 = *(undefined4 *)(iVar3 + 0x18);
      *(undefined4 *)(iVar3 + 0x18) = local_6c;
      *(undefined4 *)(iVar3 + 0x1c) = uStack_68;
      *(undefined4 *)(iVar3 + 0x20) = uStack_64;
      *(undefined4 *)(iVar3 + 0x24) = uStack_60;
      FUN_00041d52(iVar3,auStack_c4,auStack_54);
      *(undefined4 *)(iVar3 + 0x18) = uVar7;
      *(undefined4 *)(iVar3 + 0x1c) = uVar8;
      *(undefined4 *)(iVar3 + 0x20) = uVar6;
      *(undefined4 *)(iVar3 + 0x24) = uVar9;
    }
    else {
      FUN_00041d52(iVar3,auStack_c4,auStack_54);
    }
    uVar8 = *(undefined4 *)(iVar3 + 0x1c);
    uVar6 = *(undefined4 *)(iVar3 + 0x20);
    uVar9 = *(undefined4 *)(iVar3 + 0x24);
    uVar7 = *(undefined4 *)(iVar3 + 0x18);
    *(undefined4 *)(iVar3 + 0x18) = local_6c;
    *(undefined4 *)(iVar3 + 0x1c) = uStack_68;
    *(undefined4 *)(iVar3 + 0x20) = uStack_64;
    *(undefined4 *)(iVar3 + 0x24) = uStack_60;
    if ((*(byte *)(iVar2 + 0x5c) & 7) == 3) {
      FUN_00051970(&local_2c,*(undefined4 *)(iVar2 + 0x2c),local_a4,local_88,local_8c,0x1fffffff,
                   uVar4);
      iVar5 = FUN_0003db28(auStack_54);
      if (iVar5 < local_2c) {
        iVar5 = FUN_00046b72(local_a4,0x20);
        local_84 = iVar5 * 3 + *(int *)(iVar2 + 0x54) + local_2c;
        local_80 = *(undefined4 *)(iVar2 + 0x58);
        FUN_00041d52(iVar3,auStack_c4,auStack_54);
      }
      iVar5 = FUN_0003db0a(auStack_54);
      if (iVar5 < local_28) {
        local_84 = *(undefined4 *)(iVar2 + 0x54);
        local_80 = FUN_00046bd6(local_a4);
        local_80 = local_80 + *(int *)(iVar2 + 0x58) + local_28;
        FUN_00041d52(iVar3,auStack_c4,auStack_54);
      }
    }
    *(undefined4 *)(iVar3 + 0x18) = uVar7;
    *(undefined4 *)(iVar3 + 0x1c) = uVar8;
    *(undefined4 *)(iVar3 + 0x20) = uVar6;
    *(undefined4 *)(iVar3 + 0x24) = uVar9;
  }
  return;
}

