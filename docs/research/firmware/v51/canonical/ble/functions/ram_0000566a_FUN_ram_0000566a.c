/* Address: ram:0000566a; name: FUN_ram_0000566a; body bytes: 86 */

void FUN_ram_0000566a(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_e000e180 = 0x400000;
  FUN_ram_000029f8();
  FUN_ram_0000253e(0x800,2);
  FUN_ram_0000253e(0x400,2);
  FUN_ram_00003876(1);
  DAT_ram_20003a4a = 0;
  DAT_ram_20003a4b = 0;
  DAT_ram_20003a4d = 0;
  DAT_ram_20003a4c = 0;
  DAT_ram_20003a48 = 0;
  return;
}

