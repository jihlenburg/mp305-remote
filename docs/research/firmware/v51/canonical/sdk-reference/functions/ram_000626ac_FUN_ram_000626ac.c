/* Address: ram:000626ac; name: FUN_ram_000626ac; body bytes: 132 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000626ac(void)

{
  gp = 0x20004000;
  DAT_ram_20001e8c = 0;
  DAT_ram_20001e90 = 0;
  DAT_ram_20001e84 = &DAT_ram_4000c300;
  DAT_ram_20001eb0 = &DAT_ram_4000c200;
  DAT_ram_20001efc = &DAT_ram_4000d000;
  DAT_ram_20001e88 = &DAT_ram_4000c100;
  DAT_ram_20001e9b = 1;
  DAT_ram_20001eac = DAT_ram_20001bbc;
  DAT_ram_20001ea8 = DAT_ram_20001bbc + 0x110;
  BLE_RegInit();
  _DAT_ram_e000e100 = 0x200000;
  return;
}

