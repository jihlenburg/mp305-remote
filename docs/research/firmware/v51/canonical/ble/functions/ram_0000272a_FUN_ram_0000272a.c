/* Address: ram:0000272a; name: FUN_ram_0000272a; body bytes: 28 */

void FUN_ram_0000272a(uint *param_1)

{
  gp = &DAT_ram_20002000;
  *param_1 = DAT_ram_e000e000 >> 8 | DAT_ram_e000e004 << 0x18;
  DAT_ram_e000e180 = 0xffffffff;
  DAT_ram_e000e184 = 0xffffffff;
  return;
}

