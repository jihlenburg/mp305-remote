/* Address: ram:000558e4; name: FUN_ram_000558e4; body bytes: 84 */

void FUN_ram_000558e4(void)

{
  gp = 0x20004000;
  if (DAT_ram_20001b67 == '\0') {
    TMOS_ProcessEventRegister(FUN_ram_000526d0);
    FUN_ram_000527d8();
  }
  DAT_ram_20001dc4 = FUN_ram_00052b5e;
  DAT_ram_20001dc8 = FUN_ram_00054dfe;
  DAT_ram_20001dcc = FUN_ram_000555fe;
  DAT_ram_20001dd0 = &LAB_ram_00054da6;
  return;
}

