/* Address: ram:20002106; name: FUN_ram_20002106; body bytes: 206 */

void FUN_ram_20002106(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_200028d6(4,0,0,0);
  DAT_ram_40001806 = 4;
  if (0x3fff < DAT_ram_40001038) {
    DAT_ram_4000102e = DAT_ram_4000102e & 0xfc | 1;
  }
  DAT_ram_40001024 = 0;
  DAT_ram_4000104e = DAT_ram_4000104e | 3;
  DAT_ram_e000ed10 = DAT_ram_e000ed10 & 0xfffffff7 | 4;
  wfi();
  DAT_ram_4000104b = DAT_ram_4000104b & 0xdf;
  DAT_ram_40001040 = 0;
  return;
}

