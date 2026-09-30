/* Address: ram:0000286e; name: FUN_ram_0000286e; body bytes: 48 */

/* WARNING: Removing unreachable block (ram,0x0000288a) */

void FUN_ram_0000286e(uint param_1)

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
  DAT_ram_4000340c = (short)((param_1 + 5) / 10);
  return;
}

