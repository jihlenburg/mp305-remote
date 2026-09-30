/* Address: 000485a4; name: FUN_000485a4; body bytes: 474 */

void FUN_000485a4(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  byte bVar9;
  int local_28;
  
  iVar2 = *(int *)(param_1 + 0x70);
  if (iVar2 == 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x98) & 0xf) == 0) {
    return;
  }
  bVar1 = *(byte *)(param_1 + 0x25);
  local_28 = param_4;
  iVar3 = FUN_0004cd84(iVar2,0x40);
  if (iVar3 == 0) {
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  iVar3 = FUN_0004bef4(iVar2);
  iVar4 = FUN_0004bf04(iVar2);
  bVar9 = *(byte *)(param_1 + 0x98) & 0xf;
  if (bVar9 == 0xc) {
    *(undefined4 *)(param_1 + 0x58) = 0;
    if (iVar4 != 0) {
      local_28 = FUN_0004877e(param_1,0xc);
      *(undefined4 *)(param_1 + 0x5c) = 0;
      FUN_0005e4e8(param_1,0,&local_28);
      iVar8 = FUN_0003642c(iVar2,0xe0000001,0x1fffffff,local_28);
      iVar8 = local_28 + iVar8;
      iVar5 = 0;
      goto LAB_00048690;
    }
    *(int *)(param_1 + 0x5c) = (int)((100 - (uint)bVar1) * *(int *)(param_1 + 0x5c)) / 100;
    uVar6 = FUN_0004bca4(iVar2);
    uVar7 = FUN_0004bf14(iVar2);
    local_28 = 0xc;
    uVar6 = FUN_00035d0c(iVar2,*(undefined4 *)(param_1 + 0x5c),uVar7,uVar6);
    uVar7 = 0;
    *(undefined4 *)(param_1 + 0x5c) = uVar6;
LAB_000486e0:
    FUN_0004e44e(iVar2,uVar7,uVar6);
LAB_00048696:
    if ((int)((uint)*(byte *)(param_1 + 10) << 0x1e) < 0) {
      return;
    }
  }
  else if (bVar9 == 3) {
    *(undefined4 *)(param_1 + 0x5c) = 0;
    if (iVar3 == 0) {
      *(int *)(param_1 + 0x58) = (int)((100 - (uint)bVar1) * *(int *)(param_1 + 0x58)) / 100;
      uVar6 = FUN_0004bd90(iVar2);
      uVar7 = FUN_0004be44(iVar2);
      local_28 = 3;
      uVar7 = FUN_00035d0c(iVar2,*(undefined4 *)(param_1 + 0x58),uVar6,uVar7);
      uVar6 = 0;
      *(undefined4 *)(param_1 + 0x58) = uVar7;
      goto LAB_000486e0;
    }
    local_28 = FUN_0004877e(param_1,3);
    *(undefined4 *)(param_1 + 0x58) = 0;
    FUN_0005e4e8(param_1,&local_28,0);
    iVar5 = FUN_00036328(iVar2,0xe0000001,0x1fffffff,local_28);
    iVar5 = local_28 + iVar5;
    iVar8 = 0;
LAB_00048690:
    FUN_0004e25c(iVar2,iVar5,iVar8,1);
    goto LAB_00048696;
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    return;
  }
  if (*(int *)(param_1 + 0x5c) != 0) {
    return;
  }
  if (iVar4 == 0) {
    iVar4 = FUN_0004bf14(iVar2);
    iVar8 = FUN_0004bca4(iVar2);
    if (iVar4 < 1) {
      if (0 < iVar8) {
        if (-1 < iVar4) goto LAB_00048708;
        goto LAB_00048710;
      }
    }
    else {
LAB_00048708:
      if (iVar8 < 0) {
        iVar4 = -iVar8;
LAB_00048710:
        FUN_0004e25c(iVar2,0,iVar4,1);
        if ((int)((uint)*(byte *)(param_1 + 10) << 0x1e) < 0) {
          return;
        }
      }
    }
  }
  if (iVar3 != 0) goto LAB_0004875c;
  iVar3 = FUN_0004bd90(iVar2);
  iVar4 = FUN_0004be44(iVar2);
  if (iVar3 < 1) {
    if (iVar4 < 1) goto LAB_0004875c;
    if (-1 < iVar3) goto LAB_00048746;
  }
  else {
LAB_00048746:
    if (-1 < iVar4) goto LAB_0004875c;
    iVar3 = -iVar4;
  }
  FUN_0004e25c(iVar2,iVar3,0,1);
  if ((int)((uint)*(byte *)(param_1 + 10) << 0x1e) < 0) {
    return;
  }
LAB_0004875c:
  FUN_0004e5a6(iVar2,0xb,param_1);
  if (-1 < (int)((uint)*(byte *)(param_1 + 10) << 0x1e)) {
    *(byte *)(param_1 + 0x98) = *(byte *)(param_1 + 0x98) & 0xf0;
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  return;
}

