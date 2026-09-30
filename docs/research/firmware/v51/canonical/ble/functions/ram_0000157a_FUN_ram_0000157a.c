/* Address: ram:0000157a; name: FUN_ram_0000157a; body bytes: 60 */

void FUN_ram_0000157a(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_000018de(4,0,0,0);
  DAT_ram_40001046 = DAT_ram_40001046 | 1;
  DAT_ram_40001040 = 0;
  return;
}

