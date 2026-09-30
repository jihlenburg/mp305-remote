/* Address: ram:00066514; name: LL_ClearWhiteList; body bytes: 88 */

undefined4 LL_ClearWhiteList(undefined4 param_1)

{
  gp = 0x20004000;
  if (((DAT_ram_20001db4 != 0) && (*(char *)(DAT_ram_20001db4 + 0xc) != '\0')) &&
     (param_1 = 0x12, *(char *)(DAT_ram_20001db4 + 0xd) != '\0')) {
    return 0x12;
  }
  if (((DAT_ram_20001dd8 != 0) && (*(char *)(DAT_ram_20001dd8 + 0xb) != '\0')) &&
     (param_1 = 0x12, (*(byte *)(DAT_ram_20001dd8 + 0x10) & 1) != 0)) {
    gp = 0x20004000;
    return 0x12;
  }
  if (((DAT_ram_20001de8 != 0) && (*(char *)(DAT_ram_20001de8 + 7) != '\0')) &&
     (param_1 = 0x12, *(char *)(DAT_ram_20001de8 + 0xd) != '\0')) {
    gp = 0x20004000;
    return 0x12;
  }
  FUN_ram_00061910(param_1);
  return 0;
}

