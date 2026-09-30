/* Address: ram:200010ec; name: FUN_ram_200010ec; body bytes: 52 */

void FUN_ram_200010ec(void)

{
  gp = 0x20004000;
  while (((DAT_ram_20001e94 & 1) == 0 && ((DAT_ram_20001e95 & 1) == 0))) {
    if (*(int *)(DAT_ram_20001eb0 + 100) == 0) {
      DAT_ram_20001e99 = 0;
      return;
    }
  }
  gp = 0x20004000;
  DAT_ram_20001e98 = 0;
  DAT_ram_20001e99 = 0;
  return;
}

