/* Address: ram:00066994; name: FUN_ram_00066994; body bytes: 170 */

undefined4
FUN_ram_00066994(undefined1 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 auStack_4c [3];
  undefined1 uStack_49;
  undefined1 auStack_48 [22];
  undefined1 auStack_32 [16];
  undefined1 auStack_22 [22];
  
  gp = 0x20004000;
  if ((DAT_ram_20001d61 == '\0') ||
     ((((DAT_ram_20001db4 == 0 || (uVar1 = 0xc, *(char *)(DAT_ram_20001db4 + 0xc) == '\0')) &&
       ((DAT_ram_20001dd8 == 0 || (uVar1 = 0xc, *(char *)(DAT_ram_20001dd8 + 0xb) == '\0')))) &&
      ((DAT_ram_20001de8 == 0 || (uVar1 = 0xc, *(char *)(DAT_ram_20001de8 + 7) == '\0')))))) {
    uVar1 = 7;
    if (DAT_ram_20001e18 < DAT_ram_20001e19) {
      uVar1 = 0x12;
      if ((DAT_ram_20001e28 & 0x40) != 0) {
        uStack_49 = param_1;
        tmos_memcpy(auStack_48,param_2,6);
        tmos_memcpy(auStack_22,param_3,0x10);
        tmos_memcpy(auStack_32,param_4,0x10);
        uVar1 = FUN_ram_0005d7f0(auStack_4c);
        return uVar1;
      }
    }
  }
  return uVar1;
}

