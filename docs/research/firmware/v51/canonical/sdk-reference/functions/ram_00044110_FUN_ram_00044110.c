/* Address: ram:00044110; name: FUN_ram_00044110; body bytes: 60 */

void FUN_ram_00044110(void)

{
  gp = 0x20004000;
  if (DAT_ram_20001c0a != -1) {
    FUN_ram_0004de08(DAT_ram_20001c0a,&DAT_ram_200019f8,DAT_ram_20001d4c);
    DAT_ram_20001c0a = -1;
  }
  return;
}

