/* Address: ram:00001dc2; name: FUN_ram_00001dc2; body bytes: 40 */

void FUN_ram_00001dc2(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_40001057 = DAT_ram_40001057 & 0xfe;
  DAT_ram_4000105b = 0x80;
  DAT_ram_40001058 = 0xf;
  DAT_ram_40001059 = 0x35;
  return;
}

