/* Address: ram:0004737a; name: FUN_ram_0004737a; body bytes: 44 */

undefined4 FUN_ram_0004737a(void)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d50 & 5) == 0) {
    return 0x12;
  }
  if (DAT_ram_20001a1c != 0) {
    DAT_ram_20001a12 = 1;
    uVar1 = FUN_ram_00046d6e();
    return uVar1;
  }
  return 0x10;
}

