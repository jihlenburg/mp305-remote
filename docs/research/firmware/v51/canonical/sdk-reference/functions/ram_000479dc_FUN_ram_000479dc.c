/* Address: ram:000479dc; name: FUN_ram_000479dc; body bytes: 50 */

void FUN_ram_000479dc(void)

{
  gp = 0x20004000;
  if ((DAT_ram_20001d50 & 4) != 0) {
    FUN_ram_000440b0(&DAT_ram_20001a14);
    DAT_ram_20001c0a = 0xffff;
    return;
  }
  FUN_ram_000440b0(0);
  return;
}

