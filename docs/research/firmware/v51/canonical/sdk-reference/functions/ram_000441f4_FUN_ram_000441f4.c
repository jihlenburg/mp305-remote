/* Address: ram:000441f4; name: FUN_ram_000441f4; body bytes: 154 */

void FUN_ram_000441f4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  gp = 0x20004000;
  DAT_ram_20001c10 = param_1;
  DAT_ram_20001c14 = param_2;
  DAT_ram_20001c18 = param_3;
  iVar1 = tmos_isbufset(param_2,0xff,0x10);
  if ((iVar1 == 1) || (iVar1 = tmos_isbufset(param_2,0,0x10), iVar1 == 1)) {
    FUN_ram_000440ba(DAT_ram_20001c14,0x10);
  }
  iVar1 = tmos_isbufset(param_1,0xff,0x10);
  if ((iVar1 != 1) && (iVar1 = tmos_isbufset(param_1,0,0x10), iVar1 != 1)) {
    return;
  }
  FUN_ram_000440ba(DAT_ram_20001c10,0x10);
  return;
}

