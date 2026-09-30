/* Address: ram:00066be0; name: FUN_ram_00066be0; body bytes: 730 */

undefined4
FUN_ram_00066be0(undefined1 param_1,byte param_2,uint param_3,uint param_4,int param_5,uint param_6,
                undefined1 param_7,undefined4 param_8,undefined1 param_9,char param_10,char param_11
                ,undefined1 param_12,char param_13,undefined1 param_14,undefined1 param_15,
                undefined1 *param_16)

{
  ushort uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  byte bVar7;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 != 0) && (*(int *)(DAT_ram_20001db4 + 0x54) << 5 < 0)) {
    gp = 0x20004000;
    return 0xc;
  }
  if (3 < param_6) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((param_2 & 0x10) == 0) {
    if ((param_2 & 3) == 3) {
      gp = 0x20004000;
      return 0x12;
    }
    if ((param_2 & 8) != 0) {
      gp = 0x20004000;
      return 0x12;
    }
    if (param_11 == '\x03') {
      if ((DAT_ram_20001d9c & 4) == 0) {
        gp = 0x20004000;
        return 0xc;
      }
      if (param_13 != '\x03') {
LAB_ram_00066c88:
        if (param_13 == '\x02') {
          bVar7 = DAT_ram_20001d9c & 2;
          goto LAB_ram_00066ca4;
        }
      }
    }
    else {
      if (param_13 != '\x03') goto LAB_ram_00066c88;
      bVar7 = DAT_ram_20001d9c & 4;
LAB_ram_00066ca4:
      if (bVar7 == 0) {
        gp = 0x20004000;
        return 0xc;
      }
    }
  }
  else if (param_11 != '\x01') {
    gp = 0x20004000;
    return 0x12;
  }
  iVar3 = FUN_ram_00054de4();
  if (iVar3 == 0) {
    iVar3 = (*DAT_ram_20001dc4)(1);
    if (iVar3 == 0) {
      gp = 0x20004000;
      return 7;
    }
    *(undefined1 *)(iVar3 + 8) = param_1;
  }
  if (param_4 == 0x20) {
    if (param_13 == '\x03') {
      uVar1 = *(ushort *)(iVar3 + 0x1c);
      uVar5 = 0xf9;
    }
    else {
      if (param_13 != '\x01') goto LAB_ram_00066cfa;
      uVar1 = *(ushort *)(iVar3 + 0x1c);
      uVar5 = 0x2ed;
    }
    if (uVar5 < uVar1) {
      gp = 0x20004000;
      return 0x45;
    }
    if (uVar5 < *(ushort *)(iVar3 + 0x1e)) {
      gp = 0x20004000;
      return 0x45;
    }
  }
LAB_ram_00066cfa:
  *(byte *)(iVar3 + 0x60) = param_2;
  if ((param_2 & 0x10) == 0) {
    *(undefined1 *)(iVar3 + 0xe) = 7;
    bVar7 = param_2 & 4;
    if ((param_2 & 1) == 0) {
      if ((param_2 & 2) == 0) {
        uVar2 = 3;
        if (bVar7 != 0) {
          uVar2 = 6;
        }
        *(undefined1 *)(iVar3 + 0x5f) = uVar2;
        *(undefined1 *)(iVar3 + 0x5e) = 0;
        goto LAB_ram_00066d16;
      }
      uVar2 = 2;
      if (bVar7 != 0) {
        uVar2 = 5;
      }
      *(undefined1 *)(iVar3 + 0x5f) = uVar2;
      uVar2 = 2;
    }
    else {
      uVar2 = 4;
      if (bVar7 != 0) {
        uVar2 = 1;
      }
      *(undefined1 *)(iVar3 + 0x5f) = uVar2;
      uVar2 = 1;
    }
    *(undefined1 *)(iVar3 + 0x5e) = uVar2;
  }
  else {
    bVar7 = param_2 & 0xf;
    if (bVar7 == 5) {
      uVar2 = 0x81;
    }
    else {
      if (bVar7 == 0xd) {
        *(undefined1 *)(iVar3 + 0xe) = 1;
        *(undefined2 *)(iVar3 + 0x20) = 2;
        goto LAB_ram_00066d58;
      }
      uVar2 = 2;
      if (bVar7 == 2) {
        uVar2 = 6;
      }
      else if (bVar7 != 0) {
        *(undefined1 *)(iVar3 + 0xe) = 0;
        goto LAB_ram_00066d16;
      }
    }
    *(undefined1 *)(iVar3 + 0xe) = uVar2;
  }
LAB_ram_00066d16:
  if (param_4 < param_3) {
    gp = 0x20004000;
    return 0x11;
  }
  if (param_3 < 0x20) {
    gp = 0x20004000;
    return 0x11;
  }
  if (0x4000 < param_4) {
    gp = 0x20004000;
    return 0x11;
  }
  *(short *)(iVar3 + 0x20) = (short)(param_4 + param_3 >> 1);
LAB_ram_00066d58:
  *(char *)(iVar3 + 0xf) = (char)param_5;
  if (param_5 == 0) {
    *(undefined1 *)(iVar3 + 0x18) = 1;
  }
  else {
    *(undefined1 *)(iVar3 + 0x18) = 0;
    uVar6 = 0;
    do {
      if ((param_5 >> (uVar6 & 0x1f) & 1U) != 0) {
        *(char *)(iVar3 + 0x18) = *(char *)(iVar3 + 0x18) + '\x01';
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 != 3);
  }
  if ((param_2 & 0x20) == 0) {
    *(char *)(iVar3 + 0x35) = (char)param_6;
  }
  iVar4 = tmos_isbufset(param_8,0,6);
  if (iVar4 == 0) {
    *(undefined1 *)(iVar3 + 0x3c) = 1;
    *(undefined1 *)(iVar3 + 0x3d) = param_7;
    tmos_memcpy(iVar3 + 0x3e,param_8,6);
  }
  else {
    *(undefined1 *)(iVar3 + 0x3c) = 0;
  }
  *(undefined1 *)(iVar3 + 0xd) = param_9;
  if (param_10 == '\x7f') {
    *param_16 = DAT_ram_20001bd0;
  }
  else if (param_10 < '\a') {
    *(char *)(iVar3 + 0x15) = param_10;
  }
  else {
    *(undefined1 *)(iVar3 + 0x15) = 6;
  }
  uVar2 = FUN_ram_00061dd4((int)*(char *)(iVar3 + 0x15));
  *(undefined1 *)(iVar3 + 0x68) = uVar2;
  uVar2 = FUN_ram_00061d68();
  *(undefined1 *)(iVar3 + 0x15) = uVar2;
  *param_16 = uVar2;
  uVar2 = 2;
  if (param_11 != '\x03') {
    uVar2 = 0;
  }
  *(undefined1 *)(iVar3 + 100) = uVar2;
  *(undefined1 *)(iVar3 + 0x65) = param_12;
  if ((*(byte *)(iVar3 + 0x60) & 0x10) == 0) {
    if (2 < (byte)(param_13 - 1U)) {
      gp = 0x20004000;
      return 0x12;
    }
    *(char *)(iVar3 + 99) = param_13 + -1;
  }
  *(undefined1 *)(iVar3 + 0x61) = param_14;
  *(undefined1 *)(iVar3 + 0x67) = param_15;
  *(uint *)(iVar3 + 0x54) = *(uint *)(iVar3 + 0x54) | 0x8000000;
  return 0;
}

