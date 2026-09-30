/* Address: ram:000473b6; name: FUN_ram_000473b6; body bytes: 30 */

undefined4 FUN_ram_000473b6(void)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d50 & 5) != 0) {
    DAT_ram_20001a0e = 1;
    uVar1 = FUN_ram_00046d9e();
    return uVar1;
  }
  return 0x12;
}

