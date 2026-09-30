/* Address: 000599ac; name: FUN_000599ac; body bytes: 62 */

void FUN_000599ac(void)

{
  enter_critical();
  if (DAT_1ffe0040 == 0) {
    FUN_000656b6(&DAT_1ffe0e64);
    FUN_000656b6(&DAT_1ffe0e78);
    DAT_1ffe004c = &DAT_1ffe0e64;
    DAT_1ffe0050 = &DAT_1ffe0e78;
    DAT_1ffe0040 = FUN_000666c4(10,0x10,0);
    if (DAT_1ffe0040 != 0) {
      FUN_000657f0(DAT_1ffe0040,&LAB_000599f4);
    }
  }
  exit_critical();
  return;
}

