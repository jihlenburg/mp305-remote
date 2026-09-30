/* Address: ram:000604ba; name: FUN_ram_000604ba; body bytes: 70 */

void FUN_ram_000604ba(void)

{
  gp = 0x20004000;
  if (DAT_ram_20001b67 == '\0') {
    TMOS_ProcessEventRegister(FUN_ram_000526d0);
    FUN_ram_000527d8();
    DAT_ram_20001ddc = FUN_ram_0005db64;
    return;
  }
  DAT_ram_20001ddc = FUN_ram_0005db64;
  return;
}

