/* Address: ram:00066eba; name: FUN_ram_00066eba; body bytes: 338 */

undefined4
FUN_ram_00066eba(undefined4 param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 param_5)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 != 0) && (*(int *)(DAT_ram_20001db4 + 0x54) << 5 < 0)) {
    gp = 0x20004000;
    return 0xc;
  }
  iVar2 = FUN_ram_00054de4();
  if (iVar2 == 0) {
    if (DAT_ram_20001db4 != 0) {
      gp = 0x20004000;
      return 0xc;
    }
    gp = 0x20004000;
    return 0x42;
  }
  if ((*(byte *)(iVar2 + 0xe) & 0xf) == 1) {
    gp = 0x20004000;
    return 0;
  }
  if ((*(byte *)(iVar2 + 0x60) & 0x10) == 0) {
    if ((param_2 & 0xfd) == 1) goto LAB_ram_00066f32;
    if (param_2 == 4) {
      if (*(int *)(iVar2 + 0x54) << 7 < 0) {
        gp = 0x20004000;
        return 0x12;
      }
      if (*(char *)(iVar2 + 0xc) != '\x01') {
        gp = 0x20004000;
        return 0x12;
      }
      if (*(short *)(iVar2 + 0x1c) == 0) {
        gp = 0x20004000;
        return 0x12;
      }
      if (param_4 != 0) {
        gp = 0x20004000;
        return 0x12;
      }
      goto LAB_ram_00066fba;
    }
LAB_ram_00066fe6:
    if (1 < (param_2 - 3 & 0xff)) {
      if (param_4 == 0) {
        gp = 0x20004000;
        return 0x12;
      }
      if (*(char *)(iVar2 + 0xc) == '\x01') {
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
LAB_ram_00066f32:
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    if (param_2 != 3) goto LAB_ram_00066fe6;
    if (param_4 == 0) {
      *(uint *)(iVar2 + 0x54) = *(uint *)(iVar2 + 0x54) & 0xfeffffff;
      gp = 0x20004000;
      return 0;
    }
  }
  if ((int)(uint)DAT_ram_20001dd6 < (int)(*(ushort *)(iVar2 + 0x1c) + param_4)) {
    gp = 0x20004000;
    return 7;
  }
  if ((*(char *)(iVar2 + 0xc) != '\0') && (*(short *)(iVar2 + 0x20) == 0x20)) {
    if (*(char *)(iVar2 + 99) == '\x03') {
      uVar3 = 0xf9;
    }
    else {
      if (*(char *)(iVar2 + 99) != '\x01') goto LAB_ram_00066f80;
      uVar3 = 0x2ed;
    }
    if (uVar3 < *(ushort *)(iVar2 + 0x1c)) {
      gp = 0x20004000;
      return 0x45;
    }
    if (uVar3 < *(ushort *)(iVar2 + 0x1e)) {
      gp = 0x20004000;
      return 0x45;
    }
  }
LAB_ram_00066f80:
  if (param_2 != 3) {
    gp = 0x20004000;
    return 7;
  }
  *(undefined4 *)(iVar2 + 0x28) = param_5;
  *(short *)(iVar2 + 0x1c) = (short)param_4;
LAB_ram_00066fba:
  sVar1 = FUN_ram_000428ec(1,200);
  *(ushort *)(iVar2 + 0x6a) = *(short *)(iVar2 + 0x6a) + 1U & 0xf | sVar1 << 4;
  gp = 0x20004000;
  return 0;
}

