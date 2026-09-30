/* Address: ram:00066a88; name: FUN_ram_00066a88; body bytes: 86 */

undefined4 FUN_ram_00066a88(int param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d61 == '\0') ||
     ((((DAT_ram_20001db4 == 0 || (uVar1 = 0x12, *(char *)(DAT_ram_20001db4 + 0xc) == '\0')) &&
       ((DAT_ram_20001dd8 == 0 || (uVar1 = 0x12, *(char *)(DAT_ram_20001dd8 + 0xb) == '\0')))) &&
      ((DAT_ram_20001de8 == 0 || (uVar1 = 0x12, *(char *)(DAT_ram_20001de8 + 7) == '\0')))))) {
    DAT_ram_20001d61 = (char)param_1;
    if (param_1 == 0) {
      DAT_ram_20001e30 = DAT_ram_20001e30 & 0xfffff9ff;
    }
    else {
      DAT_ram_20001e30 = DAT_ram_20001e30 | 0x600;
    }
    uVar1 = 0;
  }
  return uVar1;
}

