/* Address: 0001afb4; name: FUN_0001afb4; body bytes: 40 */

void FUN_0001afb4(int param_1)

{
  enter_critical();
  if ((param_1 == 0) || (DAT_1fffaa54 < 4)) {
    DAT_1fffaa44 = 0;
  }
  else {
    DAT_1fffaa44 = (undefined1)param_1;
  }
  exit_critical();
  return;
}

