/* Address: ram:00066066; name: FUN_ram_00066066; body bytes: 36 */

undefined4 FUN_ram_00066066(void)

{
  gp = 0x20004000;
  if ((DAT_ram_20001de8 != 0) && (*(char *)(DAT_ram_20001de8 + 7) != '\0')) {
    FUN_ram_000597c8(0xc);
    return 0;
  }
  return 0xc;
}

