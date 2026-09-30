/* Address: 000200aa; name: FUN_000200aa; body bytes: 26 */

void FUN_000200aa(uint param_1)

{
  if (-1 < (int)param_1) {
    (&DAT_e000e100)[param_1 >> 5] = 1 << (param_1 & 0x1f);
  }
  return;
}

