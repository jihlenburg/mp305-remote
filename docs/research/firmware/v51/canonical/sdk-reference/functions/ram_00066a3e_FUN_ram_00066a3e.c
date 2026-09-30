/* Address: ram:00066a3e; name: FUN_ram_00066a3e; body bytes: 74 */

undefined4 FUN_ram_00066a3e(undefined4 param_1)

{
  gp = 0x20004000;
  if (DAT_ram_20001d61 != '\0') {
    if ((DAT_ram_20001db4 != 0) && (param_1 = 0x12, *(char *)(DAT_ram_20001db4 + 0xc) != '\0')) {
      return 0x12;
    }
    if ((DAT_ram_20001dd8 != 0) && (param_1 = 0x12, *(char *)(DAT_ram_20001dd8 + 0xb) != '\0')) {
      gp = 0x20004000;
      return 0x12;
    }
    if ((DAT_ram_20001de8 != 0) && (param_1 = 0x12, *(char *)(DAT_ram_20001de8 + 7) != '\0')) {
      gp = 0x20004000;
      return 0x12;
    }
  }
  FUN_ram_0005d946(param_1);
  return 0;
}

