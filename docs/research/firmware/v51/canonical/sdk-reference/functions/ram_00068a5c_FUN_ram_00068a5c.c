/* Address: ram:00068a5c; name: FUN_ram_00068a5c; body bytes: 42 */

undefined1 FUN_ram_00068a5c(int param_1)

{
  int iVar1;
  undefined1 auStack_20 [12];
  undefined1 uStack_14;
  
  gp = 0x20004000;
  iVar1 = tmos_snv_read(param_1 * 6 + 0x20U & 0xfe,0x10,auStack_20);
  if (iVar1 != 0) {
    uStack_14 = 0;
  }
  return uStack_14;
}

