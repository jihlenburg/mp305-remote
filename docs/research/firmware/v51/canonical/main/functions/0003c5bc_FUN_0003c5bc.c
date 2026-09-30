/* Address: 0003c5bc; name: FUN_0003c5bc; body bytes: 474 */

undefined4 FUN_0003c5bc(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar2 = *(int *)(param_5 + 0x24);
  iVar6 = iVar2 * param_3 >> 10;
  iVar7 = iVar6;
  if (0 < iVar2) {
    iVar7 = iVar6 + 1;
  }
  uVar5 = (uint)*(byte *)(param_5 + 0x34);
  if (iVar7 < param_2) {
    if (-1 < (int)(uVar5 << 0x1e)) {
      return 0;
    }
    return 1;
  }
  if (param_2 + param_4 < iVar6) {
    if ((int)(uVar5 << 0x1e) < 0) {
      return 0;
    }
    return 1;
  }
  iVar6 = iVar2 * param_3 * 0x100;
  iVar8 = iVar2 * (param_3 + 1) * 0x100;
  iVar7 = iVar6 >> 0x12;
  iVar4 = iVar8 >> 0x12;
  uVar3 = iVar6 >> 10 & 0xff;
  iVar6 = iVar7 - param_2;
  if (((iVar7 != iVar4) && (iVar2 < 0)) && (uVar3 == 0)) {
    uVar3 = 0xff;
    iVar6 = iVar6 + -1;
    iVar7 = iVar4;
  }
  if (iVar7 == iVar4) {
    if ((-1 < iVar6) && (iVar6 < param_4)) {
      uVar3 = uVar3 + (iVar8 >> 10 & 0xffU) >> 1;
      if ((int)(uVar5 << 0x1e) < 0) {
        uVar3 = 0xff - uVar3;
      }
      uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar6),uVar3);
      *(undefined1 *)(param_1 + iVar6) = uVar1;
    }
    if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
      iVar7 = iVar7 - param_2;
      if (param_4 <= iVar7) {
        return 0;
      }
LAB_0003c774:
      if (iVar7 < 0) {
        return 2;
      }
      goto LAB_0003c670;
    }
    iVar2 = iVar6 + 1;
    if (param_4 < iVar6 + 1) {
      iVar2 = param_4;
    }
joined_r0x0003c662:
    if (iVar2 == 0) {
      return 0;
    }
    if (iVar2 < 1) {
      return 2;
    }
  }
  else {
    if (-1 < iVar2) {
      iVar2 = (int)((0xff - uVar3) * *(int *)(param_5 + 0x28)) >> 10;
      if ((-1 < iVar6) && (iVar6 < param_4)) {
        uVar3 = 0xffU - ((int)((0xff - uVar3) * iVar2) >> 9) & 0xff;
        if ((int)(uVar5 << 0x1e) < 0) {
          uVar3 = 0xff - uVar3;
        }
        uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar6),uVar3);
        *(undefined1 *)(param_1 + iVar6) = uVar1;
      }
      iVar2 = 0xff - iVar2;
      iVar4 = iVar6 + 1;
      if ((-1 < iVar4) && (iVar4 < param_4)) {
        uVar5 = ((iVar2 * *(int *)(param_5 + 0x24) >> 10) * iVar2 & 0x1ffffU) >> 9;
        if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
          uVar5 = 0xff - uVar5;
        }
        uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar4),uVar5);
        *(undefined1 *)(param_1 + iVar4) = uVar1;
      }
      if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
        iVar7 = iVar7 - param_2;
        if (param_4 < iVar7) {
          return 0;
        }
        goto LAB_0003c774;
      }
      iVar2 = iVar6 + 2;
      if (param_4 < iVar6 + 2) {
        iVar2 = param_4;
      }
      goto joined_r0x0003c662;
    }
    iVar2 = (int)(uVar3 * -*(int *)(param_5 + 0x28)) >> 10;
    if ((-1 < iVar6) && (iVar6 < param_4)) {
      uVar3 = (iVar2 * uVar3 & 0x1ffff) >> 9;
      if ((int)(uVar5 << 0x1e) < 0) {
        uVar3 = 0xff - uVar3;
      }
      uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar6),uVar3);
      *(undefined1 *)(param_1 + iVar6) = uVar1;
    }
    iVar4 = iVar6 + -1;
    if ((-1 < iVar4) && (iVar4 < param_4)) {
      uVar5 = 0xffU - (((iVar2 + -0xff) * *(int *)(param_5 + 0x24) >> 10) * (0xff - iVar2) >> 9) &
              0xff;
      if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
        uVar5 = 0xff - uVar5;
      }
      uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar4),uVar5);
      *(undefined1 *)(param_1 + iVar4) = uVar1;
    }
    iVar2 = iVar6 + 1;
    if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
      iVar7 = (iVar7 - param_2) + -1;
      if (param_4 < iVar7) {
        return 2;
      }
      if (iVar7 < 1) {
        return 2;
      }
      goto LAB_0003c670;
    }
    if (param_4 < iVar2) {
      return 1;
    }
    if (iVar2 < 0) {
      return 2;
    }
  }
  iVar7 = param_4 - iVar2;
  param_1 = param_1 + iVar2;
LAB_0003c670:
  FUN_0004a602(param_1,iVar7);
  return 2;
}

