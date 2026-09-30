/* Address: 000493d0; name: FUN_000493d0; body bytes: 1194 */

void FUN_000493d0(int param_1)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int local_b0;
  undefined4 local_ac;
  undefined4 uStack_a8;
  uint local_a4 [4];
  int local_94;
  int local_90;
  undefined4 local_8c;
  undefined4 local_84;
  int local_80;
  int local_7c;
  undefined4 local_78;
  byte local_5c;
  undefined1 auStack_58 [28];
  int local_3c;
  int local_38;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    return;
  }
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 0x40;
  FUN_0004bab4(param_1,auStack_58);
  uVar4 = FUN_0003db28(auStack_58);
  uVar5 = FUN_0004cb34(param_1,0);
  iVar6 = FUN_0004cb7c(param_1,0);
  iVar7 = FUN_0004cb58(param_1,0);
  uStack_a8 = FUN_000375a2(param_1);
  local_b0 = iVar6;
  local_ac = uVar4;
  FUN_00051970(&local_3c,*(undefined4 *)(param_1 + 0x2c),uVar5,iVar7);
  FUN_0004deac(param_1);
  bVar3 = *(byte *)(param_1 + 0x5c) & 7;
  if (bVar3 == 2) {
    iVar7 = FUN_0004c5a0(param_1,0);
    iVar6 = FUN_0004c5a6(param_1,0);
    if (iVar6 == 0) {
      iVar6 = FUN_0003cb2e(0x28,300,10000);
    }
    FUN_0003c9f8(&local_b0);
    FUN_0003cb2a(&local_b0,param_1);
    FUN_0003cb0a(&local_b0,0xffffffff);
    FUN_0003cb02(&local_b0,300);
    FUN_0003cb0e(&local_b0,local_78);
    bVar1 = false;
    iVar8 = FUN_0003db28(auStack_58);
    if (iVar8 < local_3c) {
      iVar8 = FUN_0003db28(auStack_58);
      FUN_0003cb1e(&local_b0,0,iVar8 - local_3c);
      FUN_0003cafa(&local_b0,0x5e7a9);
      iVar8 = FUN_0003c9c4(param_1,0x5e7a9);
      uVar4 = local_8c;
      iVar10 = 0;
      bVar3 = 0;
      if (iVar8 != 0) {
        iVar10 = *(int *)(iVar8 + 0x34);
        bVar3 = *(byte *)(iVar8 + 0x54) & 1;
      }
      if ((iVar10 < local_80) && (local_5c = local_5c & 0xf7, local_7c = iVar10, bVar3 != 0)) {
        local_5c = local_5c | 1;
        local_8c = local_84;
        local_84 = uVar4;
      }
      FUN_0003caea(&local_b0,iVar6);
      FUN_0003cb06(&local_b0,local_80);
      if (iVar7 != 0) {
        FUN_000583f4(&local_b0,iVar7,*(byte *)(param_1 + 0x5c) & 7);
      }
      FUN_0003cb6c(&local_b0);
      bVar1 = true;
    }
    else {
      FUN_0003c97c(param_1,0x5e7a9);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    iVar8 = FUN_0003db0a(auStack_58);
    if ((iVar8 < local_38) && (!bVar1)) {
      iVar8 = FUN_0003db0a(auStack_58);
      iVar10 = FUN_00046bd6(uVar5);
      FUN_0003cb1e(&local_b0,0,(iVar8 - local_38) - iVar10);
      FUN_0003cafa(&local_b0,0x5e7af);
      iVar8 = FUN_0003c9c4(param_1,0x5e7af);
      uVar4 = local_8c;
      iVar10 = 0;
      bVar3 = 0;
      if (iVar8 != 0) {
        iVar10 = *(int *)(iVar8 + 0x34);
        bVar3 = *(byte *)(iVar8 + 0x54) & 1;
      }
      if ((iVar10 < local_80) && (local_5c = local_5c & 0xf7, local_7c = iVar10, bVar3 != 0)) {
        local_5c = local_5c | 1;
        local_8c = local_84;
        local_84 = uVar4;
      }
      FUN_0003caea(&local_b0,iVar6);
      FUN_0003cb06(&local_b0,local_80);
      if (iVar7 != 0) {
LAB_000495d0:
        FUN_000583f4(&local_b0,iVar7,*(byte *)(param_1 + 0x5c) & 7);
      }
LAB_00049708:
      FUN_0003cb6c(&local_b0);
      goto LAB_0004986e;
    }
  }
  else {
    if (bVar3 != 3) {
      if (bVar3 == 1) {
        iVar8 = FUN_0003db0a(auStack_58);
        if (((iVar8 < local_38) && (iVar8 = FUN_00046bd6(uVar5), iVar8 < local_38)) &&
           (uVar9 = FUN_00051c88(*(undefined4 *)(param_1 + 0x2c)), 3 < uVar9)) {
          iVar8 = FUN_0003db28(auStack_58);
          iVar10 = FUN_00046b72(uVar5,0x2e);
          local_94 = (iVar10 + iVar7) * -3 + iVar8;
          local_90 = FUN_0003db0a(auStack_58);
          iVar7 = FUN_00046bd6(uVar5);
          iVar8 = local_90 - (iVar7 + iVar6) * (local_90 / (iVar7 + iVar6));
          iVar7 = FUN_00046bd6(uVar5);
          local_90 = local_90 - iVar8;
          if (iVar8 < iVar7) {
            local_90 = local_90 - iVar6;
          }
          else {
            iVar6 = FUN_00046bd6(uVar5);
            local_90 = iVar6 + local_90;
          }
          iVar6 = FUN_00048f08(param_1,&local_94,0);
          uVar9 = FUN_00050a64(*(undefined4 *)(param_1 + 0x2c));
          local_a4[0] = FUN_00051c28(*(undefined4 *)(param_1 + 0x2c),iVar6);
          while (uVar2 = local_a4[0], uVar9 < local_a4[0] + 3) {
            FUN_00051d3c(*(undefined4 *)(param_1 + 0x2c),local_a4);
            iVar6 = iVar6 + -1;
          }
          uVar11 = 0;
          uVar12 = 0;
          do {
            iVar7 = FUN_00051d84(*(int *)(param_1 + 0x2c) + local_a4[0]);
            uVar11 = iVar7 + uVar11 & 0xff;
            FUN_00051cb0(*(undefined4 *)(param_1 + 0x2c),local_a4);
            if ((3 < uVar11) || (uVar9 < local_a4[0])) break;
            uVar12 = uVar12 + 1;
          } while (uVar12 < 4);
          iVar7 = *(int *)(param_1 + 0x2c) + uVar2;
          FUN_00048dbe();
          if (uVar11 < 5) {
            *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xdf;
            FUN_0004a404(param_1 + 0x30,iVar7,uVar11);
          }
          else {
            iVar8 = FUN_0004a318(uVar11 + 1);
            *(int *)(param_1 + 0x30) = iVar8;
            if (iVar8 == 0) goto LAB_0004986e;
            FUN_0004a404(iVar8,iVar7,uVar11);
            *(undefined1 *)(*(int *)(param_1 + 0x30) + uVar11) = 0;
            *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 0x20;
          }
          uVar9 = 0;
          do {
            iVar7 = uVar2 + uVar9;
            uVar9 = uVar9 + 1;
            *(undefined1 *)(*(int *)(param_1 + 0x2c) + iVar7) = 0x2e;
          } while (uVar9 < 3);
          *(undefined1 *)(*(int *)(param_1 + 0x2c) + uVar2 + 3) = 0;
          *(int *)(param_1 + 0x34) = iVar6 + 3;
        }
        else {
          *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
        }
      }
      goto LAB_0004986e;
    }
    iVar7 = FUN_0004c5a0(param_1,0);
    iVar6 = FUN_0004c5a6(param_1,0);
    if (iVar6 == 0) {
      iVar6 = FUN_0003cb2e(0x28,300,10000);
    }
    FUN_0003c9f8(&local_b0);
    FUN_0003cb2a(&local_b0,param_1);
    FUN_0003cb0a(&local_b0,0xffffffff);
    bVar1 = false;
    iVar8 = FUN_0003db28(auStack_58);
    if (iVar8 < local_3c) {
      iVar8 = FUN_00046b72(uVar5,0x20);
      FUN_0003cb1e(&local_b0,0,-(iVar8 * 3 + local_3c));
      FUN_0003cafa(&local_b0,0x5e7a9);
      FUN_0003caea(&local_b0,iVar6);
      iVar10 = FUN_0003c9c4(param_1,0x5e7a9);
      iVar8 = 0;
      if (iVar10 != 0) {
        iVar8 = *(int *)(iVar10 + 0x34);
      }
      if (iVar7 == 0) {
        if (iVar8 < local_80) {
          local_5c = local_5c & 0xf7;
          local_7c = iVar8;
        }
      }
      else {
        FUN_000583f4(&local_b0,iVar7,*(byte *)(param_1 + 0x5c) & 7);
      }
      FUN_0003cb6c(&local_b0);
      bVar1 = true;
    }
    else {
      FUN_0003c97c(param_1,0x5e7a9);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    iVar8 = FUN_0003db0a(auStack_58);
    if ((iVar8 < local_38) && (!bVar1)) {
      iVar8 = FUN_00046bd6(uVar5);
      FUN_0003cb1e(&local_b0,0,-(iVar8 + local_38));
      FUN_0003cafa(&local_b0,0x5e7af);
      FUN_0003caea(&local_b0,iVar6);
      iVar8 = FUN_0003c9c4(param_1,0x5e7af);
      iVar6 = 0;
      if (iVar8 != 0) {
        iVar6 = *(int *)(iVar8 + 0x34);
      }
      if (iVar7 != 0) goto LAB_000495d0;
      if (iVar6 < local_80) {
        local_5c = local_5c & 0xf7;
        local_7c = iVar6;
      }
      goto LAB_00049708;
    }
  }
  FUN_0003c97c(param_1,0x5e7af);
  *(undefined4 *)(param_1 + 0x58) = 0;
LAB_0004986e:
  FUN_0004d3d8(param_1);
  return;
}

