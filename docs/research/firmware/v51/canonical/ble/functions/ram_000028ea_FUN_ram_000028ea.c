/* Address: ram:000028ea; name: FUN_ram_000028ea; body bytes: 42 */

void FUN_ram_000028ea(int param_1,byte param_2)

{
  gp = &DAT_ram_20002000;
  if (param_1 != 0) {
    DAT_ram_40003401 = param_2 | DAT_ram_40003401;
    DAT_ram_40003400 = DAT_ram_40003400 | 8;
    return;
  }
  DAT_ram_40003401 = ~param_2 & DAT_ram_40003401;
  return;
}

