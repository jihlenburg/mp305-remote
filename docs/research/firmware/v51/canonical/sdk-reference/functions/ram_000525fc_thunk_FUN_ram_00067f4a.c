/* Address: ram:000525fc; name: thunk_FUN_ram_00067f4a; body bytes: 4 */

undefined4 thunk_FUN_ram_00067f4a(undefined1 param_1,undefined4 param_2,undefined1 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 auStack_16 [14];
  
  gp = 0x20004000;
  if ((DAT_ram_20001d61 != '\0') &&
     ((((DAT_ram_20001db4 != 0 && (*(char *)(DAT_ram_20001db4 + 0xc) != '\0')) ||
       ((DAT_ram_20001dd8 != 0 && (*(char *)(DAT_ram_20001dd8 + 0xb) != '\0')))) ||
      ((DAT_ram_20001de8 != 0 && (*(char *)(DAT_ram_20001de8 + 7) != '\0')))))) {
    return 0x12;
  }
  uStack_17 = param_1;
  tmos_memcpy(auStack_16,param_2,6);
  iVar2 = FUN_ram_20000c00(&uStack_18);
  if (iVar2 == 0) {
    uVar1 = 0x12;
  }
  else {
    *(undefined1 *)(iVar2 + 1) = param_3;
    uVar1 = 0;
  }
  return uVar1;
}

