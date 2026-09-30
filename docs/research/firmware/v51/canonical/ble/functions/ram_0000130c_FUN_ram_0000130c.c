/* Address: ram:0000130c; name: FUN_ram_0000130c; body bytes: 250 */

void FUN_ram_0000130c(ushort param_1)

{
  gp = &DAT_ram_20002000;
  FUN_ram_000018de(4,0,0,0);
  DAT_ram_4000104e = DAT_ram_4000104e | 3;
  if (0x3fff < DAT_ram_40001038) {
    DAT_ram_4000102e = DAT_ram_4000102e & 0xfc | 1;
  }
  DAT_ram_40001024 = 0;
  DAT_ram_40001040 = 0;
  FUN_ram_00001406(0x25);
  DAT_ram_4000100f = DAT_ram_4000100f | 0x40;
  DAT_ram_40001040 = 0xa8;
  DAT_ram_40001020 = param_1 | 0x9000;
  DAT_ram_e000ed10 = DAT_ram_e000ed10 & 0xfffffff7 | 4;
  wfi();
  FUN_ram_000018de(4,0,0,0);
  DAT_ram_40001046 = DAT_ram_40001046 | 1;
  DAT_ram_40001040 = 0;
  return;
}

