/* Address: ram:00002a74; name: FUN_ram_00002a74; body bytes: 22 */

void FUN_ram_00002a74(undefined1 param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_40008028 = param_1;
  DAT_ram_4000802a = DAT_ram_4000802a & 0xfc;
  return;
}

