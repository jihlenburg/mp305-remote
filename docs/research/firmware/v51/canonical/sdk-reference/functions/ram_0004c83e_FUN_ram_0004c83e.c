/* Address: ram:0004c83e; name: FUN_ram_0004c83e; body bytes: 42 */

void FUN_ram_0004c83e(uint param_1,undefined1 param_2)

{
  gp = 0x20004000;
  if (0x204 < param_1) {
    param_1 = 0x204;
  }
  DAT_ram_20001a5e = (short)param_1 + -4;
  DAT_ram_20001a62 = param_2;
  DAT_ram_20001a64 = param_2;
  return;
}

