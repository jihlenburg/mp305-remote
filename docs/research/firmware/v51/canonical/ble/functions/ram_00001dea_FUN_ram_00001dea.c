/* Address: ram:00001dea; name: FUN_ram_00001dea; body bytes: 46 */

void FUN_ram_00001dea(byte param_1)

{
  gp = &DAT_ram_20002000;
  DAT_ram_4000104e = DAT_ram_4000104e & 0xfc | param_1 & 3;
  DAT_ram_40001040 = 0;
  return;
}

