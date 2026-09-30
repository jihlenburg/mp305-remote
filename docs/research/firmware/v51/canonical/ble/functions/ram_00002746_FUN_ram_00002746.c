/* Address: ram:00002746; name: FUN_ram_00002746; body bytes: 20 */

void FUN_ram_00002746(uint param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_e000e100 = param_1 << 8;
  DAT_ram_e000e104 = param_1 >> 0x18;
  return;
}

