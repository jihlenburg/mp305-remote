/* Address: ram:000010ce; name: FUN_ram_000010ce; body bytes: 64 */

void FUN_ram_000010ce(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_000018de(4,0,0,0);
  DAT_ram_40001806 = 4;
  DAT_ram_e000ed10 = DAT_ram_e000ed10 & 0xfffffff3;
  wfi();
  return;
}

