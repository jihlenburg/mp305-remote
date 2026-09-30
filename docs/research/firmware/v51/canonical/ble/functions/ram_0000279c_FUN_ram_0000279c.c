/* Address: ram:0000279c; name: FUN_ram_0000279c; body bytes: 26 */

void FUN_ram_0000279c(char param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_40002000 = param_1 << 6 | 5;
  return;
}

