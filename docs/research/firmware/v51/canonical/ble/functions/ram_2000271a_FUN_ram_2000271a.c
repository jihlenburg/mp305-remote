/* Address: ram:2000271a; name: FUN_ram_2000271a; body bytes: 44 */

void FUN_ram_2000271a(void)

{
  gp = &DAT_ram_20002000;
  if ((DAT_ram_40002806 & 1) != 0) {
    DAT_ram_40002806 = 1;
    DAT_ram_20002fbc = DAT_ram_20002fbc + 100;
  }
  return;
}

