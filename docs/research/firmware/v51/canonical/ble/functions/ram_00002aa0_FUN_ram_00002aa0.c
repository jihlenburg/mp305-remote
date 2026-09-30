/* Address: ram:00002aa0; name: FUN_ram_00002aa0; body bytes: 22 */

void FUN_ram_00002aa0(undefined1 param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_40008030 = param_1;
  DAT_ram_40008032 = DAT_ram_40008032 & 0xfc;
  return;
}

