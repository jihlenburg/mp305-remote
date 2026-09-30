/* Address: ram:0005dbe8; name: FUN_ram_0005dbe8; body bytes: 338 */

bool FUN_ram_0005dbe8(int param_1)

{
  int iVar1;
  byte bVar2;
  
  gp = 0x20004000;
  if ((*(char *)(param_1 + 0x5c) == '\0') ||
     (iVar1 = tmos_memcmp(param_1 + 0x4e,param_1 + 0x5e,6), iVar1 != 0)) goto LAB_ram_0005dc60;
  if ((*(byte *)(param_1 + 0x10) & 2) == 0) {
    if (((DAT_ram_20001d61 != '\0') && (*(char *)(param_1 + 0x5d) != '\0')) &&
       ((*(byte *)(param_1 + 99) & 0xc0) == 0x40)) {
      iVar1 = FUN_ram_20000c8e(param_1 + 0x5c);
      *(int *)(param_1 + 100) = iVar1;
      if (iVar1 != 0) {
LAB_ram_0005dc46:
        *(undefined1 *)(param_1 + 0x5c) = 2;
        bVar2 = *(byte *)(param_1 + 0x4d) | 2;
        goto LAB_ram_0005dca6;
      }
    }
    if (*(char *)(param_1 + 0x5c) != '\x02') {
      gp = 0x20004000;
      return false;
    }
  }
  else {
    if (*(char *)(param_1 + 0x5d) == '\0') {
      gp = 0x20004000;
      return false;
    }
    if ((*(byte *)(param_1 + 99) & 0xc0) != 0x40) {
      gp = 0x20004000;
      return false;
    }
    if (DAT_ram_20001d61 == '\0') goto LAB_ram_0005dc60;
    iVar1 = FUN_ram_20000c8e(param_1 + 0x5c);
    *(int *)(param_1 + 100) = iVar1;
    bVar2 = 0xfe;
    if (iVar1 != 0) goto LAB_ram_0005dc46;
LAB_ram_0005dca6:
    *(byte *)(param_1 + 0x5d) = bVar2;
  }
LAB_ram_0005dc60:
  if ((*(char *)(param_1 + 0x54) != '\0') && (DAT_ram_20001d61 != '\0')) {
    if ((*(char *)(param_1 + 0x55) == '\0') || ((*(byte *)(param_1 + 0x5b) & 0xc0) != 0x40)) {
      iVar1 = FUN_ram_20000c00(param_1 + 0x54);
      *(int *)(param_1 + 100) = iVar1;
      if ((iVar1 != 0) && (*(undefined1 *)(param_1 + 0x54) = 2, *(char *)(iVar1 + 0x12) != '\0')) {
        *(undefined1 *)(param_1 + 0x54) = 3;
        gp = 0x20004000;
        return *(char *)(iVar1 + 1) != '\0';
      }
    }
    else {
      iVar1 = FUN_ram_20000c50();
      *(int *)(param_1 + 100) = iVar1;
      if (iVar1 != 0) {
        tmos_memcpy(iVar1 + 0x14,param_1 + 0x56,6);
        *(undefined1 *)(param_1 + 0x54) = 3;
        *(byte *)(param_1 + 0x55) = *(byte *)(*(int *)(param_1 + 100) + 3) | 2;
        tmos_memcpy(param_1 + 0x56,*(int *)(param_1 + 100) + 4,6);
      }
    }
  }
  return true;
}

