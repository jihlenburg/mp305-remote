/* Address: ram:00002764; name: FUN_ram_00002764; body bytes: 56 */

void FUN_ram_00002764(int param_1)

{
  byte bVar1;
  
  gp = &DAT_ram_20002000;
  bVar1 = DAT_ram_40001046 | 2;
  if (param_1 == 0) {
    bVar1 = DAT_ram_40001046 & 0xfd;
  }
  DAT_ram_40001046 = bVar1;
  DAT_ram_40001040 = 0;
  return;
}

