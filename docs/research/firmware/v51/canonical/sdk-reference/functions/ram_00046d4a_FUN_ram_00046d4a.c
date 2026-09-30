/* Address: ram:00046d4a; name: FUN_ram_00046d4a; body bytes: 36 */

void FUN_ram_00046d4a(void)

{
  gp = 0x20004000;
  if (DAT_ram_200019e4 != 0) {
    FUN_ram_20000104();
    DAT_ram_200019e4 = 0;
  }
  return;
}

