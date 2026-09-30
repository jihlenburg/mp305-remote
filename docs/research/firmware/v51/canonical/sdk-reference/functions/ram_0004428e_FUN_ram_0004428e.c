/* Address: ram:0004428e; name: FUN_ram_0004428e; body bytes: 80 */

undefined4 FUN_ram_0004428e(undefined1 param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  tmos_memset(&DAT_ram_20001c04,0,0x20);
  DAT_ram_20001c07 = param_1;
  DAT_ram_20001d50 = param_2;
  iVar1 = thunk_FUN_ram_000651a6();
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = 0x12;
  }
  DAT_ram_20001c04 = iVar1 == 0;
  return uVar2;
}

