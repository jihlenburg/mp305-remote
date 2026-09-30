/* Address: ram:00004810; name: FUN_ram_00004810; body bytes: 178 */

void FUN_ram_00004810(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_400010a8 = DAT_ram_400010a8 | 0x1000;
  DAT_ram_400010c8 = DAT_ram_400010c8 | 0x4010;
  FUN_ram_00002498(0x1000,4);
  FUN_ram_0000253e(0x4010,4);
  DAT_ram_40005003 = 0xf0;
  FUN_ram_000025fe(1);
  FUN_ram_0000268a(1,0,1,0);
  FUN_ram_0000268a(8,0,1,0);
  FUN_ram_0000268a(0x40,0,1,0);
  FUN_ram_000025e4(1,1);
  FUN_ram_0000253e(0x800000,0);
  FUN_ram_0000279c(1);
  DAT_ram_4000200c = &LAB_ram_00001770;
  DAT_ram_40002002 = DAT_ram_40002002 | 2;
  DAT_ram_e000e410 = 0;
  DAT_ram_e000e100 = 0x10000;
  return;
}

