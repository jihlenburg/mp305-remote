/* Address: 000200c4; name: FUN_000200c4; body bytes: 26 */

void FUN_000200c4(uint param_1)

{
  if (-1 < (int)param_1) {
    (&DAT_e000e100)[param_1 >> 5] = 1 << (param_1 & 0x1f);
  }
  return;
}

