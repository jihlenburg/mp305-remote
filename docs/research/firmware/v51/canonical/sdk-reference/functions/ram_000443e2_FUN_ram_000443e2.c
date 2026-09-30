/* Address: ram:000443e2; name: FUN_ram_000443e2; body bytes: 36 */

void FUN_ram_000443e2(void)

{
  gp = 0x20004000;
  *DAT_ram_20001c18 = *DAT_ram_20001c18 + 1;
  if (DAT_ram_20001c07 != -1) {
    tmos_set_event(DAT_ram_20001c07,0x4000);
    return;
  }
  return;
}

