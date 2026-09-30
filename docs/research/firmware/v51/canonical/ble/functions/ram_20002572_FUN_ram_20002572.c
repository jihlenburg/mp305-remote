/* Address: ram:20002572; name: FUN_ram_20002572; body bytes: 60 */

void FUN_ram_20002572(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_200028d6(4,0,0,0);
  DAT_ram_40001046 = DAT_ram_40001046 | 1;
  DAT_ram_40001040 = 0;
  return;
}

