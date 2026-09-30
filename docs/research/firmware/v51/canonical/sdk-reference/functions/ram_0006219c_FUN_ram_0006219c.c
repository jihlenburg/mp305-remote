/* Address: ram:0006219c; name: FUN_ram_0006219c; body bytes: 44 */

void FUN_ram_0006219c(void)

{
  gp = 0x20004000;
  if ((DAT_ram_20001e9d == '\0') && ((byte)(DAT_ram_20001e9b - 6U) < 3)) {
    DAT_ram_20001e9c = DAT_ram_20001e9b;
    DAT_ram_20001e9d = '\x01';
  }
  return;
}

