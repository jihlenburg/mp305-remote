/* Address: ram:0004135c; name: FUN_ram_0004135c; body bytes: 52 */

void FUN_ram_0004135c(void)

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

