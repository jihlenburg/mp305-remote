/* Address: ram:000536fe; name: FUN_ram_000536fe; body bytes: 330 */

uint FUN_ram_000536fe(int param_1)

{
  int iVar1;
  uint uVar2;
  
  gp = 0x20004000;
  if (DAT_ram_20001d61 != '\0') {
    if ((*(char *)(param_1 + 0x45) != '\0') && ((*(byte *)(param_1 + 0x4b) & 0xc0) == 0x40)) {
      if (*(int *)(param_1 + 0x30) != 0) {
        iVar1 = FUN_ram_0005d6c6(*(int *)(param_1 + 0x30) + 0x2a,param_1 + 0x46);
        if (iVar1 == 1) {
          *(undefined1 *)(param_1 + 0x44) = 2;
          *(byte *)(param_1 + 0x45) = *(byte *)(*(int *)(param_1 + 0x30) + 3) | 2;
          tmos_memcpy(*(int *)(param_1 + 0x30) + 0x14,param_1 + 0x46,6);
          gp = 0x20004000;
          return 1;
        }
      }
      if (((*(char *)(param_1 + 0x10) != '\x01') && ((*(byte *)(param_1 + 0x60) & 4) == 0)) &&
         (*(char *)(param_1 + 0x3c) == '\0')) {
        iVar1 = FUN_ram_20000c50(param_1 + 0x44);
        *(int *)(param_1 + 0x30) = iVar1;
        if (iVar1 != 0) {
          *(undefined1 *)(param_1 + 0x44) = 2;
          *(byte *)(param_1 + 0x45) = *(byte *)(iVar1 + 3) | 2;
          tmos_memcpy(iVar1 + 0x14,param_1 + 0x46,6);
          gp = 0x20004000;
          return 1;
        }
      }
    }
    if (((*(byte *)(param_1 + 0x3c) & 2) != 0) && (*(char *)(*(int *)(param_1 + 0x30) + 1) == '\0'))
    {
      gp = 0x20004000;
      return 0;
    }
  }
  if ((*(char *)(param_1 + 0x10) == '\x01') || ((*(byte *)(param_1 + 0x60) & 4) != 0)) {
    if (*(byte *)(param_1 + 0x45) != (*(byte *)(param_1 + 0x3d) & 1)) {
      return 0;
    }
    iVar1 = tmos_memcmp(param_1 + 0x3e,param_1 + 0x46,6);
    gp = 0x20004000;
    return (uint)(iVar1 != 0);
  }
  if ((((*(byte *)(param_1 + 0xd) & 1) == 0) || (*(char *)(param_1 + 0x13) != '\x03')) &&
     (((*(byte *)(param_1 + 0xd) & 2) == 0 || (*(char *)(param_1 + 0x13) != '\x05')))) {
    gp = 0x20004000;
    return 1;
  }
  uVar2 = FUN_ram_20000d70(*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48));
  return uVar2;
}

