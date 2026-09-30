/* Address: 0002c7a8; name: FUN_0002c7a8; body bytes: 278 */

void FUN_0002c7a8(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_bc;
  undefined4 uStack_b8;
  undefined1 auStack_a0 [28];
  undefined4 local_84;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined1 auStack_3c [4];
  undefined4 local_38;
  undefined4 local_30;
  int local_2c;
  
  iVar2 = FUN_00046698();
  iVar3 = FUN_0004bc8c();
  FUN_00041db4(auStack_a0);
  FUN_0004cf40(iVar3,0,auStack_a0);
  iVar4 = FUN_00046718(param_1);
  uVar5 = *(undefined4 *)(iVar4 + 0x18);
  uVar7 = *(undefined4 *)(iVar4 + 0x1c);
  local_bc = *(undefined4 *)(iVar4 + 0x20);
  uStack_b8 = *(undefined4 *)(iVar4 + 0x24);
  local_2c = iVar4 + 0x18;
  iVar6 = FUN_0003db4c(&local_4c,local_2c,iVar3 + 0x14);
  if (iVar6 != 0) {
    *(undefined4 *)(iVar4 + 0x18) = local_4c;
    *(undefined4 *)(iVar4 + 0x1c) = uStack_48;
    *(undefined4 *)(iVar4 + 0x20) = uStack_44;
    *(undefined4 *)(iVar4 + 0x24) = uStack_40;
    FUN_00037b16(iVar3,auStack_3c);
    local_d4 = *(undefined4 *)(iVar2 + 0x14);
    local_d0 = *(undefined4 *)(iVar2 + 0x18);
    local_cc = *(undefined4 *)(iVar2 + 0x1c);
    local_c8 = local_38;
    iVar3 = FUN_0003db4c(&local_d4,local_2c);
    if (iVar3 != 0) {
      uVar11 = *(undefined4 *)(iVar4 + 0x20);
      uVar8 = *(undefined4 *)(iVar4 + 0x24);
      puVar1 = (undefined4 *)(iVar4 + 0x18);
      uVar9 = *puVar1;
      uVar10 = *(undefined4 *)(iVar4 + 0x1c);
      *puVar1 = local_d4;
      *(undefined4 *)(iVar4 + 0x1c) = local_d0;
      *(undefined4 *)(iVar4 + 0x20) = local_cc;
      *(undefined4 *)(iVar4 + 0x24) = local_c8;
      local_84 = FUN_000491e8(iVar2);
      FUN_00041d52(iVar4,auStack_a0,iVar2 + 0x14);
      *puVar1 = uVar9;
      *(undefined4 *)(iVar4 + 0x1c) = uVar10;
      *(undefined4 *)(iVar4 + 0x20) = uVar11;
      *(undefined4 *)(iVar4 + 0x24) = uVar8;
    }
    local_d4 = *(undefined4 *)(iVar2 + 0x14);
    local_d0 = local_30;
    local_cc = *(undefined4 *)(iVar2 + 0x1c);
    local_c8 = *(undefined4 *)(iVar2 + 0x20);
    iVar3 = FUN_0003db4c(&local_d4,local_2c);
    if (iVar3 != 0) {
      uVar11 = *(undefined4 *)(iVar4 + 0x20);
      uVar8 = *(undefined4 *)(iVar4 + 0x24);
      puVar1 = (undefined4 *)(iVar4 + 0x18);
      uVar9 = *puVar1;
      uVar10 = *(undefined4 *)(iVar4 + 0x1c);
      *puVar1 = local_d4;
      *(undefined4 *)(iVar4 + 0x1c) = local_d0;
      *(undefined4 *)(iVar4 + 0x20) = local_cc;
      *(undefined4 *)(iVar4 + 0x24) = local_c8;
      local_84 = FUN_000491e8(iVar2);
      FUN_00041d52(iVar4,auStack_a0,iVar2 + 0x14);
      *puVar1 = uVar9;
      *(undefined4 *)(iVar4 + 0x1c) = uVar10;
      *(undefined4 *)(iVar4 + 0x20) = uVar11;
      *(undefined4 *)(iVar4 + 0x24) = uVar8;
    }
    *(undefined4 *)(iVar4 + 0x20) = local_bc;
    *(undefined4 *)(iVar4 + 0x24) = uStack_b8;
    *(undefined4 *)(iVar4 + 0x18) = uVar5;
    *(undefined4 *)(iVar4 + 0x1c) = uVar7;
  }
  return;
}

