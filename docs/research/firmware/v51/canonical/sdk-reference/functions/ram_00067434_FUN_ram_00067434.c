/* Address: ram:00067434; name: FUN_ram_00067434; body bytes: 354 */

undefined4 FUN_ram_00067434(undefined4 param_1,uint param_2,int param_3,undefined4 param_4)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 != 0) && (*(int *)(DAT_ram_20001db4 + 0x54) << 5 < 0)) {
    gp = 0x20004000;
    return 0xc;
  }
  iVar3 = FUN_ram_00054de4();
  if (iVar3 == 0) {
    gp = 0x20004000;
    return 0x42;
  }
  if ((*(uint *)(iVar3 + 0x54) & 2) == 0) goto LAB_ram_000674d6;
  if (*(char *)(iVar3 + 99) == '\x02') {
    uVar5 = *(ushort *)(iVar3 + 0x84);
    if (uVar5 < 0x2ee) {
      if (499 < uVar5) goto LAB_ram_000674a8;
      if (uVar5 < 0xfa) goto LAB_ram_000674d6;
    }
    else {
      if (*(ushort *)(iVar3 + 0x86) < 0x2d) {
        gp = 0x20004000;
        return 0x45;
      }
LAB_ram_000674a8:
      if (*(ushort *)(iVar3 + 0x86) < 0x1f) {
        gp = 0x20004000;
        return 0x45;
      }
    }
    uVar1 = *(ushort *)(iVar3 + 0x86);
    uVar5 = 0x10;
  }
  else {
    if ((*(char *)(iVar3 + 99) != '\0') || (*(ushort *)(iVar3 + 0x84) < 0x2ee))
    goto LAB_ram_000674d6;
    uVar1 = *(ushort *)(iVar3 + 0x86);
    uVar5 = 6;
  }
  if (uVar1 <= uVar5) {
    gp = 0x20004000;
    return 0x45;
  }
LAB_ram_000674d6:
  if ((param_2 & 0xfd) == 1) {
    if (*(int *)(iVar3 + 0xa0) != 0) {
      FUN_ram_20000104();
      *(undefined4 *)(iVar3 + 0xa0) = 0;
    }
    *(undefined2 *)(iVar3 + 0x84) = 0;
    if (param_3 == 0) {
      if (param_2 == 3) {
        *(uint *)(iVar3 + 0x54) = *(uint *)(iVar3 + 0x54) & 0xfffffffe;
        gp = 0x20004000;
        return 0;
      }
      gp = 0x20004000;
      return 0x12;
    }
  }
  else if ((param_3 == 0) && (param_2 != 4)) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((((*(uint *)(iVar3 + 0x54) & 4) == 0) || ((param_2 - 3 & 0xff) < 2)) && (param_2 == 3)) {
    iVar4 = FUN_ram_20000040(param_3,0x105);
    *(int *)(iVar3 + 0xa0) = iVar4;
    if (iVar4 != 0) {
      tmos_memcpy(iVar4,param_4,param_3);
      *(short *)(iVar3 + 0x84) = (short)param_3;
      if ((*(uint *)(iVar3 + 0x54) & 0x400) != 0) {
        sVar2 = FUN_ram_000428ec(1,200);
        *(ushort *)(iVar3 + 0x8a) = *(short *)(iVar3 + 0x8a) + 1U & 0xf | sVar2 << 4;
        gp = 0x20004000;
        return 0;
      }
      gp = 0x20004000;
      return 0;
    }
  }
  return 0xc;
}

