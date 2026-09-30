/* Address: 00052204; name: FUN_00052204; body bytes: 1188 */

void FUN_00052204(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  uint uVar12;
  uint uVar13;
  int extraout_r3;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  undefined1 auStack_f0 [32];
  byte local_d0;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  undefined1 auStack_78 [20];
  int *local_64;
  undefined4 local_5c;
  undefined4 local_54;
  int local_44;
  int local_40;
  uint local_34;
  uint local_30;
  int local_2c;
  int local_28;
  undefined1 auStack_24 [12];
  undefined4 local_18;
  
  iVar9 = FUN_0004b9b2(&PTR_DAT_0007af38);
  if (iVar9 != 1) {
    return;
  }
  iVar9 = FUN_00046688(param_2);
  iVar10 = FUN_00046698(param_2);
  if (iVar9 == 0x10) {
    FUN_00060710();
    return;
  }
  if (iVar9 == 0xe) {
    piVar11 = (int *)FUN_0004673a(param_2);
    iVar9 = *piVar11;
    if (iVar9 == 0x13) {
      FUN_00052370(iVar10,*(int *)(iVar10 + 0x4c) + 1);
      return;
    }
    if (iVar9 == 0x14) {
      FUN_000520c6(iVar10);
      return;
    }
    if (iVar9 == 0x11) {
      FUN_000520dc(iVar10);
      return;
    }
    if (iVar9 != 0x12) {
      if (iVar9 == 8) {
        FUN_00052128(iVar10);
        return;
      }
      if (iVar9 != 0x7f) {
        if (iVar9 == 2) {
          uVar2 = 0;
        }
        else {
          if (iVar9 != 3) {
            if ((iVar9 == 10) && (iVar9 = FUN_00052310(iVar10), iVar9 != 0)) {
              FUN_0004e5a6(iVar10,0x23,0);
              return;
            }
            FUN_00051db8(iVar10);
            return;
          }
          uVar2 = 0x7fff;
        }
        FUN_00052370(iVar10,uVar2);
        return;
      }
      iVar9 = *(int *)(iVar10 + 0x4c);
      FUN_00052370(iVar10,iVar9 + 1);
      if (*(int *)(iVar10 + 0x4c) != iVar9) {
        FUN_00052128(iVar10);
        return;
      }
      return;
    }
    FUN_00049080(*(undefined4 *)(iVar10 + 0x2c),*(undefined4 *)(iVar10 + 0x4c),&local_18);
    iVar9 = FUN_0004cb8e(iVar10,0);
    FUN_0004cb4c(iVar10,0);
    iVar3 = FUN_00046bd6();
    local_18 = *(undefined4 *)(iVar10 + 0x48);
    iVar4 = FUN_0004bbec(*(undefined4 *)(iVar10 + 0x2c));
    if (iVar3 + extraout_r3 + iVar9 + 1 < iVar4) {
      uVar2 = FUN_00048f08(*(undefined4 *)(iVar10 + 0x2c),&local_18,1);
      uVar6 = *(undefined4 *)(iVar10 + 0x48);
      FUN_00052370(iVar10,uVar2);
      *(undefined4 *)(iVar10 + 0x48) = uVar6;
    }
    return;
  }
  if ((((iVar9 != 1) && (iVar9 != 2)) && (iVar9 != 3)) && (iVar9 != 8)) {
    if (iVar9 == 0x1a) {
      iVar9 = FUN_00046698();
      uVar2 = FUN_00046718(param_2);
      pcVar7 = (char *)FUN_000491e8(*(undefined4 *)(iVar9 + 0x2c));
      if (((*pcVar7 == '\0') && (*(char **)(iVar9 + 0x30) != (char *)0x0)) &&
         (**(char **)(iVar9 + 0x30) != '\0')) {
        FUN_00041db4(auStack_78);
        FUN_0004cf40(iVar9,0x80000,auStack_78);
        if ((int)((uint)*(byte *)(iVar9 + 0x70) << 0x1c) < 0) {
          local_30 = local_30 | 0x1000000;
        }
        iVar10 = FUN_0004c87c(iVar9,0);
        iVar3 = FUN_0004c8be(iVar9,0);
        iVar4 = FUN_0004c918(iVar9,0);
        iVar5 = FUN_0004c816(iVar9,0);
        iVar8 = FUN_0004c6ae(iVar9,0);
        FUN_0003d9fe(&local_88,iVar9 + 0x14);
        local_88 = local_88 + iVar10 + iVar8;
        local_80 = local_80 - (iVar3 + iVar8);
        local_84 = local_84 + iVar4 + iVar8;
        local_7c = local_7c - (iVar5 + iVar8);
        local_5c = *(undefined4 *)(iVar9 + 0x30);
        FUN_00041d52(uVar2,auStack_78,&local_88);
      }
      return;
    }
    if (iVar9 != 0x1d) {
      return;
    }
    iVar9 = FUN_00046698();
    uVar2 = FUN_00046718(param_2);
    iVar10 = FUN_000491e8(*(undefined4 *)(iVar9 + 0x2c));
    if ((*(byte *)(iVar9 + 100) & 1) != 0) {
      FUN_00042ec4(auStack_f0);
      FUN_0004d0bc(iVar9,0x60000,auStack_f0);
      FUN_0003d9fe(&local_100,iVar9 + 0x50);
      local_100 = local_100 + *(int *)(*(int *)(iVar9 + 0x2c) + 0x14);
      local_fc = *(int *)(*(int *)(iVar9 + 0x2c) + 0x18) + local_fc;
      local_f8 = *(int *)(*(int *)(iVar9 + 0x2c) + 0x14) + local_f8;
      local_f4 = *(int *)(*(int *)(iVar9 + 0x2c) + 0x18) + local_f4;
      FUN_00042a98(uVar2,auStack_f0,&local_100);
      iVar3 = FUN_0004c6ae(iVar9,0x60000);
      iVar4 = FUN_0004c87c(iVar9,0x60000);
      iVar5 = FUN_0004c918(iVar9,0x60000);
      local_2c = 0;
      local_28 = 0;
      uVar6 = FUN_00051d84(*(int *)(iVar9 + 0x60) + iVar10);
      FUN_0004a404(&local_2c,*(int *)(iVar9 + 0x60) + iVar10,uVar6);
      local_100 = local_100 + iVar4 + iVar3;
      local_fc = local_fc + iVar3 + iVar5;
      uVar6 = FUN_0004c924(*(undefined4 *)(iVar9 + 0x2c),0,0x58);
      FUN_00041db4(&local_80);
      FUN_0004cf40(iVar9,0x60000,&local_80);
      if ((2 < local_d0) || (iVar9 = FUN_000402f4(local_54,uVar6), iVar9 == 0)) {
        local_64 = &local_2c;
        local_34 = local_34 | 0x40;
        FUN_00041d52(uVar2,&local_80,&local_100);
      }
    }
    return;
  }
  iVar9 = FUN_00047eec();
  if (iVar9 == 0) {
    return;
  }
  iVar10 = FUN_00046698(param_2);
  if (-1 < (int)((uint)*(byte *)(iVar10 + 100) << 0x1e)) {
    return;
  }
  iVar3 = FUN_000482e0(iVar9);
  if (iVar3 == 2) {
    return;
  }
  iVar3 = FUN_000482e0(iVar9);
  if (iVar3 == 4) {
    return;
  }
  FUN_0004bb3c(*(undefined4 *)(iVar10 + 0x2c),&local_44);
  FUN_00048288(iVar9,&local_34);
  FUN_000482e8(iVar9,auStack_24);
  if ((int)local_34 < 0) {
    return;
  }
  if ((int)local_30 < 0) {
    return;
  }
  local_2c = local_34 - local_44;
  local_28 = local_30 - local_40;
  iVar9 = FUN_00046688(param_2);
  iVar3 = FUN_0004ccf8(*(undefined4 *)(iVar10 + 0x2c));
  iVar4 = *(int *)(iVar10 + 0x2c);
  uVar2 = 0;
  if (local_2c < 0) {
LAB_0006523c:
    uVar12 = 1;
  }
  else {
    if (iVar3 <= local_2c) {
      uVar2 = 0x7fff;
      goto LAB_0006523c;
    }
    uVar2 = FUN_00048f08(iVar4,&local_2c,1);
    uVar12 = FUN_0004925c(*(undefined4 *)(iVar10 + 0x2c),&local_2c);
    uVar12 = uVar12 ^ 1;
  }
  bVar1 = *(byte *)(iVar10 + 0x70);
  if ((int)((uint)bVar1 << 0x1e) < 0) {
    if ((uVar12 == 0 && (bVar1 & 1) == 0) && (iVar9 == 1)) {
      *(undefined4 *)(iVar10 + 0x68) = uVar2;
      *(undefined4 *)(iVar10 + 0x6c) = 0xffff;
      *(byte *)(iVar10 + 0x70) = *(byte *)(iVar10 + 0x70) | 1;
      FUN_0004e00e(iVar10,0x300);
      goto LAB_000652b4;
    }
    if ((bVar1 & 1) == 0) goto LAB_000652bc;
    if (iVar9 == 2) {
      *(undefined4 *)(iVar10 + 0x6c) = uVar2;
      goto LAB_000652b4;
    }
    if ((iVar9 == 3) || (iVar9 == 8)) {
      FUN_0004aa6e(iVar10,0x300);
      goto LAB_000652b4;
    }
  }
  else {
LAB_000652b4:
    if ((*(byte *)(iVar10 + 0x70) & 1) == 0) {
LAB_000652bc:
      if (iVar9 != 1) {
        return;
      }
    }
  }
  FUN_00052370(iVar10,uVar2);
  if ((*(byte *)(iVar10 + 0x70) & 1) == 0) {
    return;
  }
  uVar13 = *(uint *)(iVar10 + 0x68);
  uVar12 = *(uint *)(iVar10 + 0x6c);
  if (uVar12 <= uVar13 && uVar13 != uVar12) {
    if ((*(uint *)(iVar4 + 0x44) == uVar12) && (*(uint *)(iVar4 + 0x48) == uVar13))
    goto LAB_00065316;
    *(uint *)(iVar4 + 0x44) = uVar12;
    uVar2 = *(undefined4 *)(iVar10 + 0x68);
  }
  else if (uVar12 <= uVar13) {
    uVar2 = 0xffff;
    if ((*(int *)(iVar4 + 0x44) == 0xffff) && (*(int *)(iVar4 + 0x48) == 0xffff)) goto LAB_00065316;
    *(undefined4 *)(iVar4 + 0x44) = 0xffff;
  }
  else {
    if ((*(uint *)(iVar4 + 0x44) == uVar13) && (*(uint *)(iVar4 + 0x48) == uVar12))
    goto LAB_00065316;
    *(uint *)(iVar4 + 0x44) = uVar13;
    uVar2 = *(undefined4 *)(iVar10 + 0x6c);
  }
  *(undefined4 *)(iVar4 + 0x48) = uVar2;
  FUN_0004d3d8(iVar10);
LAB_00065316:
  if ((iVar9 == 3) || (iVar9 == 8)) {
    *(byte *)(iVar10 + 0x70) = *(byte *)(iVar10 + 0x70) & 0xfe;
  }
  return;
}

