/* Address: ram:000025e4; name: FUN_ram_000025e4; body bytes: 26 */

void FUN_ram_000025e4(int param_1,ushort param_2)

{
  gp = &DAT_ram_20002000;
  if (param_1 == 0) {
    DAT_ram_40001018 = ~param_2 & DAT_ram_40001018;
  }
  else {
    DAT_ram_40001018 = param_2 | DAT_ram_40001018;
  }
  return;
}

