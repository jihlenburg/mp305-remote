/* Address: ram:00066b68; name: FUN_ram_00066b68; body bytes: 120 */

undefined4 FUN_ram_00066b68(undefined4 param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((param_2 & 1) == 0) {
    if (param_3 < 8) {
      *(char *)(iVar1 + 0x144) = (char)param_3;
      goto LAB_ram_00066b9a;
    }
LAB_ram_00066b8e:
    uVar2 = 0x11;
  }
  else {
LAB_ram_00066b9a:
    if ((param_2 & 2) == 0) {
      if (7 < param_4) goto LAB_ram_00066b8e;
      *(char *)(iVar1 + 0x145) = (char)param_4;
    }
    if (param_5 != 0) {
      if ((param_5 & DAT_ram_20001da2 & 3) == 1) {
        *(undefined2 *)(iVar1 + 0x148) = 1;
      }
      else {
        *(undefined2 *)(iVar1 + 0x148) = 0;
      }
    }
    *(undefined1 *)(iVar1 + 0x1e) = 1;
    *(uint *)(iVar1 + 0xa4) = *(uint *)(iVar1 + 0xa4) | 0x1000;
    uVar2 = 0;
  }
  return uVar2;
}

