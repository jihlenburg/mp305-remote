/* Address: ram:00042e10; name: FUN_ram_00042e10; body bytes: 78 */

void FUN_ram_00042e10(int param_1)

{
  gp = 0x20004000;
  if (((DAT_ram_20001bc4 != 0) && (DAT_ram_20001bf4 != (code *)0x0)) && (param_1 == 1)) {
    if (DAT_ram_20001b84 != 0) {
      (*DAT_ram_20001bf4)(DAT_ram_20001b88,DAT_ram_20001bc8 >> 2);
      FUN_ram_20000104(DAT_ram_20001b84);
      DAT_ram_20001b84 = 0;
      DAT_ram_20001b88 = 0;
    }
    return;
  }
  return;
}

