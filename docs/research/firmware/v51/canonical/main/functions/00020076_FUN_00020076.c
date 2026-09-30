/* Address: 00020076; name: FUN_00020076; body bytes: 26 */

void FUN_00020076(uint param_1)

{
  if (-1 < (int)param_1) {
    (&DAT_e000e280)[param_1 >> 5] = 1 << (param_1 & 0x1f);
  }
  return;
}

