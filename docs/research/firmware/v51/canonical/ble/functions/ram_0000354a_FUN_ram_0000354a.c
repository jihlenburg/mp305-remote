/* Address: ram:0000354a; name: FUN_ram_0000354a; body bytes: 78 */

void FUN_ram_0000354a(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_4000100e = DAT_ram_4000100e | 8;
  DAT_ram_40001031 = DAT_ram_40001031 | 0x20;
  DAT_ram_40001040 = 0;
  DAT_ram_e000e100 = 0x10000000;
  return;
}

