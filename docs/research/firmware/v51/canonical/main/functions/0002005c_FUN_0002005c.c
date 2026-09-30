/* Address: 0002005c; name: FUN_0002005c; body bytes: 26 */

void FUN_0002005c(uint param_1)

{
  if (-1 < (int)param_1) {
    (&DAT_e000e280)[param_1 >> 5] = 1 << (param_1 & 0x1f);
  }
  return;
}

