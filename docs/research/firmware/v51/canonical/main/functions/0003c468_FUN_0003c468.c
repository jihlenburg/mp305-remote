/* Address: 0003c468; name: FUN_0003c468; body bytes: 338 */

undefined4 FUN_0003c468(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = *(int *)(param_5 + 0x28);
  iVar4 = iVar2 * param_2 >> 10;
  if (iVar2 < 1) {
    if (iVar4 < param_3) goto LAB_0003c484;
  }
  else if (param_3 < iVar4) {
LAB_0003c484:
    if (-1 < (int)((uint)*(byte *)(param_5 + 0x34) << 0x1e)) {
      return 0;
    }
    return 1;
  }
  iVar4 = iVar2 * (param_2 + param_4) >> 10;
  if (iVar2 < 1) {
    if (param_3 < iVar4) goto LAB_0003c4a0;
    iVar2 = *(int *)(param_5 + 0x24);
    param_3 = param_3 + 1;
  }
  else {
    if (iVar4 < param_3) {
LAB_0003c4a0:
      if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
        return 0;
      }
      return 1;
    }
    iVar2 = *(int *)(param_5 + 0x24);
  }
  iVar2 = param_3 * iVar2 * 0x100;
  uVar3 = iVar2 >> 10 & 0xff;
  if (uVar3 == 0) {
    iVar4 = 0xff;
  }
  else {
    iVar4 = 0xff - ((int)((0xff - uVar3) * *(int *)(param_5 + 0x30)) >> 8);
  }
  param_2 = (iVar2 >> 0x12) - param_2;
  iVar2 = param_2;
  if (uVar3 != 0) {
    if ((-1 < param_2) && (param_2 < param_4)) {
      uVar3 = 0xffU - ((int)((0xff - iVar4) * (0xff - uVar3)) >> 9) & 0xff;
      if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
        uVar3 = 0xff - uVar3;
      }
      uVar1 = FUN_00053592(*(undefined1 *)(param_1 + param_2),uVar3);
      *(undefined1 *)(param_1 + param_2) = uVar1;
    }
    iVar2 = param_2 + 1;
  }
  do {
    if (iVar4 <= *(int *)(param_5 + 0x30)) break;
    if ((-1 < iVar2) && (iVar2 < param_4)) {
      uVar3 = iVar4 - (*(int *)(param_5 + 0x30) >> 1) & 0xff;
      if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
        uVar3 = 0xff - uVar3;
      }
      uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar2),uVar3);
      *(undefined1 *)(param_1 + iVar2) = uVar1;
    }
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 - *(int *)(param_5 + 0x30);
  } while (iVar2 < param_4);
  if ((iVar2 < param_4) && (-1 < iVar2)) {
    uVar3 = (iVar4 * (iVar4 * *(int *)(param_5 + 0x24) >> 10) & 0x1ffffU) >> 9;
    if (*(int *)(param_5 + 0x28) < 0) {
      uVar3 = 0xff - uVar3;
    }
    if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
      uVar3 = 0xff - uVar3;
    }
    uVar1 = FUN_00053592(*(undefined1 *)(param_1 + iVar2),uVar3);
    *(undefined1 *)(param_1 + iVar2) = uVar1;
  }
  if ((int)((uint)*(byte *)(param_5 + 0x34) << 0x1e) < 0) {
    if (param_4 < param_2) {
      return 0;
    }
    if (param_2 < 0) {
      return 2;
    }
  }
  else {
    iVar2 = iVar2 + 1;
    if (iVar2 < 0) {
      return 0;
    }
    if (param_4 < iVar2) {
      return 2;
    }
    param_2 = param_4 - iVar2;
    param_1 = param_1 + iVar2;
  }
  FUN_0004a602(param_1,param_2);
  return 2;
}

