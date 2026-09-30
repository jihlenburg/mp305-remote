/* Address: ram:00067342; name: FUN_ram_00067342; body bytes: 44 */

undefined4 FUN_ram_00067342(undefined4 param_1,uint param_2,uint param_3,byte param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 != 0) && (*(int *)(DAT_ram_20001db4 + 0x54) << 5 < 0)) {
    return 0xc;
  }
  iVar2 = FUN_ram_00054de4();
  if (iVar2 == 0) {
    gp = 0x20004000;
    return 0x42;
  }
  if (param_3 < param_2) {
    gp = 0x20004000;
    return 0x12;
  }
  if (param_2 < 6) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((*(byte *)(iVar2 + 0x60) & 0x33) != 0) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((*(char *)(iVar2 + 0x5e) != '\0') || ((*(uint *)(iVar2 + 0x54) & 4) != 0)) {
    gp = 0x20004000;
    return 0xc;
  }
  uVar3 = FUN_ram_00041bc6();
  if (uVar3 < 0x1f) {
    gp = 0x20004000;
    return 7;
  }
  if (*(char *)(iVar2 + 99) == '\x02') {
    uVar1 = *(ushort *)(iVar2 + 0x84);
    if (uVar1 < 0x2ee) {
      if (499 < uVar1) goto LAB_ram_000673dc;
      if (uVar1 < 0xfa) goto LAB_ram_00067402;
    }
    else {
      if (param_3 < 0x2d) {
        gp = 0x20004000;
        return 0x45;
      }
LAB_ram_000673dc:
      if (param_3 < 0x1f) {
        gp = 0x20004000;
        return 0x45;
      }
    }
    uVar3 = 0x10;
  }
  else {
    if ((*(char *)(iVar2 + 99) != '\0') || (*(ushort *)(iVar2 + 0x84) < 0x2ee))
    goto LAB_ram_00067402;
    uVar3 = 6;
  }
  if (param_3 <= uVar3) {
    gp = 0x20004000;
    return 0x45;
  }
LAB_ram_00067402:
  *(uint *)(iVar2 + 0x54) = *(uint *)(iVar2 + 0x54) | 2;
  *(short *)(iVar2 + 0x86) = (short)((int)(param_2 + param_3) >> 1);
  *(byte *)(iVar2 + 0x60) = param_4 | *(byte *)(iVar2 + 0x60);
  return 0;
}

