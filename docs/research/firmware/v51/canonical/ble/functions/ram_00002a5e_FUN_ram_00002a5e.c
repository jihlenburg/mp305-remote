/* Address: ram:00002a5e; name: FUN_ram_00002a5e; body bytes: 22 */

void FUN_ram_00002a5e(undefined1 param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_40008024 = param_1;
  DAT_ram_40008026 = DAT_ram_40008026 & 0xfc;
  return;
}

