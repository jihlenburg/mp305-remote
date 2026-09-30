/* Address: 0001afe0; name: FUN_0001afe0; body bytes: 44 */

void FUN_0001afe0(int param_1)

{
  enter_critical();
  if ((param_1 == 0) || ((DAT_1fffaa54 != '\x02' && (DAT_1fffaa54 != '\x03')))) {
    DAT_1fffaa45 = 0;
  }
  else {
    DAT_1fffaa45 = (undefined1)param_1;
  }
  exit_critical();
  return;
}

