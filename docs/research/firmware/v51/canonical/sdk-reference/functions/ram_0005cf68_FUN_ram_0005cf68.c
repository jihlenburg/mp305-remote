/* Address: ram:0005cf68; name: FUN_ram_0005cf68; body bytes: 106 */

undefined4 FUN_ram_0005cf68(undefined4 param_1)

{
  int iVar1;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 uStack_16;
  char cStack_15;
  undefined1 uStack_14;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    gp = 0x20004000;
    return 2;
  }
  uStack_17 = (undefined1)param_1;
  uStack_16 = (undefined1)((uint)param_1 >> 8);
  if (*(char *)(iVar1 + 0x160) == '\x7f') {
    cStack_15 = -1;
  }
  else {
    cStack_15 = *(char *)(iVar1 + 0x160) - *(char *)(iVar1 + 0x32);
    if ((*(byte *)(iVar1 + 0x16a) & 0x10) == 0) {
      if ((*(byte *)(iVar1 + 0x16a) & 0x20) == 0) {
        uStack_14 = 2;
      }
      else {
        uStack_14 = 1;
      }
      goto LAB_ram_0005cfb2;
    }
  }
  uStack_14 = 0;
LAB_ram_0005cfb2:
  FUN_ram_00068302(&uStack_18);
  return 0;
}

