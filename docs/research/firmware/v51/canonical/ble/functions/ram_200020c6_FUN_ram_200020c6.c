/* Address: ram:200020c6; name: FUN_ram_200020c6; body bytes: 64 */

void FUN_ram_200020c6(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_200028d6(4,0,0,0);
  DAT_ram_40001806 = 4;
  DAT_ram_e000ed10 = DAT_ram_e000ed10 & 0xfffffff3;
  wfi();
  return;
}

