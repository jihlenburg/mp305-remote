/* Address: 0005e6e0; name: FUN_0005e6e0; body bytes: 78 */

void FUN_0005e6e0(void)

{
  FUN_0001ba58();
  FUN_0001814c();
  FUN_0004aa6e(DAT_1ffe0730,1);
  FUN_0004eb0e(DAT_1ffe072c,0);
  enter_critical();
  if ((3 < DAT_1fffaa54) && (DAT_1fffaa54 != 5)) {
    DAT_1fffaa55 = 0;
    DAT_1fffaa54 = 5;
  }
  exit_critical();
  return;
}

