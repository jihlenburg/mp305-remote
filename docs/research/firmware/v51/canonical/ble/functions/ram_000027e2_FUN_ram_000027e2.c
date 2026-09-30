/* Address: ram:000027e2; name: FUN_ram_000027e2; body bytes: 48 */

/* WARNING: Removing unreachable block (ram,0x000027fe) */

void FUN_ram_000027e2(uint param_1)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  iVar1 = FUN_ram_000026e8();
  if (param_1 == 0) {
    param_1 = 0xffffffff;
  }
  else {
    param_1 = ((uint)(iVar1 * 10) >> 3) / param_1;
  }
  DAT_ram_4000300c = (short)((param_1 + 5) / 10);
  return;
}

