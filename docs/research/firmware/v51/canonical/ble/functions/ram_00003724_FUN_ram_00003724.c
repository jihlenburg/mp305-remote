/* Address: ram:00003724; name: FUN_ram_00003724; body bytes: 116 */

/* WARNING: Removing unreachable block (ram,0x00003770) */
/* WARNING: Removing unreachable block (ram,0x00003746) */
/* WARNING: Removing unreachable block (ram,0x0000375a) */
/* WARNING: Removing unreachable block (ram,0x00003786) */

void FUN_ram_00003724(void)

{
  gp = &DAT_ram_20002000;
  DAT_ram_20002f84 = DAT_ram_20002f84 + 1;
  DAT_ram_20002f7f = 1;
  if (DAT_ram_20002f84 % 10 == 0) {
    DAT_ram_20002f7e = 1;
  }
  if (DAT_ram_20002f84 % 100 == 0) {
    DAT_ram_20002f7d = 1;
  }
  if (DAT_ram_20002f84 % 500 == 0) {
    DAT_ram_20002f80 = 1;
  }
  if (DAT_ram_20002f84 % 1000 == 0) {
    DAT_ram_20002f7c = 1;
  }
  return;
}

