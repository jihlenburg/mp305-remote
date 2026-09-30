/* Address: 00020be8; name: FUN_00020be8; body bytes: 228 */

void FUN_00020be8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5,uint param_6,int param_7,int param_8,uint param_9,uint param_10,
                 uint param_11)

{
  uint uVar1;
  undefined1 uVar2;
  
  if (-1 < (int)(param_11 << 0x1e)) {
    if (((param_10 != 0) && ((param_11 & 1) != 0)) && ((param_11 & 0xc) != 0 || param_7 != 0)) {
      param_10 = param_10 - 1;
    }
    for (; (param_6 < param_9 && (param_6 < 0x20)); param_6 = param_6 + 1) {
      *(undefined1 *)(param_5 + param_6) = 0x30;
    }
    for (; (((param_11 & 1) != 0 && (param_6 < param_10)) && (param_6 < 0x20));
        param_6 = param_6 + 1) {
      *(undefined1 *)(param_5 + param_6) = 0x30;
    }
  }
  uVar1 = param_6;
  if ((int)(param_11 << 0x1b) < 0) {
    if ((((int)(param_11 << 0x15) < 0) || (param_6 == 0)) ||
       (((param_6 != param_9 && (param_6 != param_10)) || (uVar1 = param_6 - 1, uVar1 == 0)))) {
      if (param_8 == 0x10) goto LAB_00020c6e;
LAB_00020c68:
      if (param_8 == 2) {
        if (0x1f < uVar1) goto LAB_00020cb4;
        uVar2 = 0x62;
        goto LAB_00020c88;
      }
    }
    else {
      if (param_8 != 0x10) goto LAB_00020c68;
      uVar1 = param_6 - 2;
LAB_00020c6e:
      if ((int)(param_11 << 0x1a) < 0) {
        if (0x1f < uVar1) goto LAB_00020cb4;
        uVar2 = 0x58;
      }
      else {
        if (0x1f < uVar1) goto LAB_00020cb4;
        uVar2 = 0x78;
      }
LAB_00020c88:
      *(undefined1 *)(param_5 + uVar1) = uVar2;
      uVar1 = uVar1 + 1;
    }
    if (0x1f < uVar1) goto LAB_00020cb4;
    *(undefined1 *)(param_5 + uVar1) = 0x30;
    uVar1 = uVar1 + 1;
  }
  if (uVar1 < 0x20) {
    if (param_7 == 0) {
      if ((int)(param_11 << 0x1d) < 0) {
        uVar2 = 0x2b;
      }
      else {
        if (-1 < (int)(param_11 << 0x1c)) goto LAB_00020cb4;
        uVar2 = 0x20;
      }
    }
    else {
      uVar2 = 0x2d;
    }
    *(undefined1 *)(param_5 + uVar1) = uVar2;
    uVar1 = uVar1 + 1;
  }
LAB_00020cb4:
  FUN_00020dd6(param_1,param_2,param_3,param_4,param_5,uVar1,param_10,param_11);
  return;
}

