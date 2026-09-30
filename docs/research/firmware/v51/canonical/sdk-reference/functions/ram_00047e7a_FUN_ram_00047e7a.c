/* Address: ram:00047e7a; name: FUN_ram_00047e7a; body bytes: 46 */

undefined4 FUN_ram_00047e7a(void)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d50 & 5) == 0) {
    FUN_ram_000440a6(0);
    uVar1 = 0;
  }
  else {
    FUN_ram_000440a6(&DAT_ram_20001ad0);
    uVar1 = 0x13;
  }
  return uVar1;
}

