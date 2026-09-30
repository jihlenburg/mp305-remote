/* Address: ram:00044f96; name: FUN_ram_00044f96; body bytes: 38 */

void FUN_ram_00044f96(void)

{
  gp = 0x20004000;
  if (DAT_ram_200019e0 != 0) {
    FUN_ram_20000104();
    DAT_ram_200019e0 = 0;
  }
  return;
}

