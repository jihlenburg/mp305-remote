/* Address: ram:00004b14; name: FUN_ram_00004b14; body bytes: 136 */

void FUN_ram_00004b14(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_000047c6();
  thunk_FUN_ram_00004ddc();
  FUN_ram_00004810();
  FUN_ram_0000566a();
  DAT_ram_40002400 = DAT_ram_40002400 | 4;
  FUN_ram_000027b6(60000);
  DAT_ram_40002402 = DAT_ram_40002402 | 1;
  DAT_ram_e000e100 = 0x1000000;
  DAT_ram_40002800 = DAT_ram_40002800 | 4;
  FUN_ram_000027cc(6000000);
  DAT_ram_40002802 = DAT_ram_40002802 | 1;
  DAT_ram_e000e100 = 0x2000000;
  DAT_ram_20002fb5 = 1;
  return;
}

