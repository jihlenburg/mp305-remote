/* Address: ram:000028d0; name: FUN_ram_000028d0; body bytes: 26 */

void FUN_ram_000028d0(char param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_40003402 = DAT_ram_40003402 & 0x3f | param_1 << 6;
  return;
}

