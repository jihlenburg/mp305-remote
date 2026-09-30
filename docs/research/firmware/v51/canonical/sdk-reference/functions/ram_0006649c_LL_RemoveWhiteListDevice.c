/* Address: ram:0006649c; name: LL_RemoveWhiteListDevice; body bytes: 120 */

undefined4 LL_RemoveWhiteListDevice(undefined1 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 auStack_16 [18];
  
  gp = 0x20004000;
  if ((((DAT_ram_20001db4 == 0) || (*(char *)(DAT_ram_20001db4 + 0xc) == '\0')) ||
      (*(char *)(DAT_ram_20001db4 + 0xd) == '\0')) &&
     (((DAT_ram_20001dd8 == 0 || (*(char *)(DAT_ram_20001dd8 + 0xb) == '\0')) ||
      ((*(byte *)(DAT_ram_20001dd8 + 0x10) & 1) == 0)))) {
    if (((DAT_ram_20001de8 != 0) && (*(char *)(DAT_ram_20001de8 + 7) != '\0')) &&
       (*(char *)(DAT_ram_20001de8 + 0xd) != '\0')) {
      gp = 0x20004000;
      return 0x12;
    }
    uStack_17 = param_1;
    tmos_memcpy(auStack_16,param_2,6);
    iVar1 = FUN_ram_00061882(&uStack_18);
    uVar2 = 0xc;
    if (iVar1 == 1) {
      uVar2 = 0;
    }
    return uVar2;
  }
  return 0x12;
}

