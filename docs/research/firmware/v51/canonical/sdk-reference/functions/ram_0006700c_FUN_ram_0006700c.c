/* Address: ram:0006700c; name: FUN_ram_0006700c; body bytes: 396 */

undefined4
FUN_ram_0006700c(undefined4 param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 param_5)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 != 0) && (*(int *)(DAT_ram_20001db4 + 0x54) << 5 < 0)) {
    gp = 0x20004000;
    return 0xc;
  }
  iVar3 = FUN_ram_00054de4();
  if (iVar3 == 0) {
    if (DAT_ram_20001db4 != 0) {
      gp = 0x20004000;
      return 0xc;
    }
    gp = 0x20004000;
    return 0x42;
  }
  if ((*(byte *)(iVar3 + 0xe) & 0xf) == 1) {
    gp = 0x20004000;
    return 0;
  }
  if ((*(byte *)(iVar3 + 0x60) & 0x10) == 0) {
    if ((param_2 & 0xfd) == 1) goto LAB_ram_00067084;
    if (param_2 == 4) {
      if (*(int *)(iVar3 + 0x54) << 6 < 0) {
        gp = 0x20004000;
        return 0x12;
      }
      if (*(char *)(iVar3 + 0xc) != '\x01') {
        gp = 0x20004000;
        return 0x12;
      }
      if (*(short *)(iVar3 + 0x1e) == 0) {
        gp = 0x20004000;
        return 0x12;
      }
      if (param_4 != 0) {
        gp = 0x20004000;
        return 0x12;
      }
      goto LAB_ram_00067140;
    }
LAB_ram_0006716c:
    if (1 < (param_2 - 3 & 0xff)) {
      if (param_4 == 0) {
        gp = 0x20004000;
        return 0x12;
      }
      if (*(char *)(iVar3 + 0xc) == '\x01') {
        return 0xc;
      }
    }
  }
  else {
    if (param_2 != 3) {
      gp = 0x20004000;
      return 0x12;
    }
    if (0x1f < param_4) {
      gp = 0x20004000;
      return 0x12;
    }
LAB_ram_00067084:
    *(undefined2 *)(iVar3 + 0x1e) = 0;
    if (param_2 != 3) goto LAB_ram_0006716c;
    if (param_4 == 0) {
      *(uint *)(iVar3 + 0x54) = *(uint *)(iVar3 + 0x54) & 0xfdffffff;
      gp = 0x20004000;
      return 0;
    }
  }
  if ((int)(uint)DAT_ram_20001dd6 < (int)(*(ushort *)(iVar3 + 0x1e) + param_4)) {
    gp = 0x20004000;
    return 7;
  }
  if ((*(char *)(iVar3 + 0xc) != '\0') && (*(short *)(iVar3 + 0x20) == 0x20)) {
    if (*(char *)(iVar3 + 99) == '\x03') {
      uVar1 = *(ushort *)(iVar3 + 0x1c);
      uVar4 = 0xf9;
    }
    else {
      if (*(char *)(iVar3 + 99) != '\x01') goto LAB_ram_000670d2;
      uVar1 = *(ushort *)(iVar3 + 0x1c);
      uVar4 = 0x2ed;
    }
    if (uVar4 < uVar1) {
      gp = 0x20004000;
      return 0x45;
    }
    if (uVar4 < *(ushort *)(iVar3 + 0x1e)) {
      gp = 0x20004000;
      return 0x45;
    }
  }
LAB_ram_000670d2:
  if (param_2 != 3) {
    gp = 0x20004000;
    return 7;
  }
  if ((((*(int *)(iVar3 + 0x2c) != 0) && ((*(byte *)(iVar3 + 0x66) & 2) != 0)) &&
      ((*(byte *)(iVar3 + 0x35) & 2) != 0)) &&
     ((*(int *)(iVar3 + 0x30) != 0 && (*(char *)(*(int *)(iVar3 + 0x30) + 10) != '\0')))) {
    FUN_ram_0005d790();
    tmos_memcpy(iVar3 + 0x36,*(int *)(iVar3 + 0x30) + 0xc,6);
  }
  *(undefined4 *)(iVar3 + 0x2c) = param_5;
  *(short *)(iVar3 + 0x1e) = (short)param_4;
LAB_ram_00067140:
  sVar2 = FUN_ram_000428ec(1,200);
  *(ushort *)(iVar3 + 0x6a) = *(short *)(iVar3 + 0x6a) + 1U & 0xf | sVar2 << 4;
  gp = 0x20004000;
  return 0;
}

