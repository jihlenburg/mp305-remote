/* Address: ram:000045d4; name: FUN_ram_000045d4; body bytes: 84 */

void FUN_ram_000045d4(int param_1)

{
  byte bVar1;
  
  gp = &DAT_ram_20002000;
  param_1 = param_1 * 0x218;
  bVar1 = (&DAT_ram_20003b58)[param_1];
  if (bVar1 == 0xba) {
    FUN_ram_00004486(&DAT_ram_20003b58 + param_1,(&DAT_ram_20003b56)[param_1]);
    return;
  }
  if (bVar1 < 0xbb) {
    if (bVar1 != 0xb8) {
      return;
    }
    FUN_ram_00003f20();
    return;
  }
  if (bVar1 == 0xbc) {
    FUN_ram_00003f3a();
    return;
  }
  if (bVar1 != 0xbe) {
    return;
  }
  FUN_ram_00003f76();
  return;
}

