/* Address: 00020118; name: FUN_00020118; body bytes: 32 */

void FUN_00020118(uint param_1,char param_2)

{
  if (-1 < (int)param_1) {
    (&DAT_e000e400)[param_1] = param_2 << 4;
    return;
  }
  (&DAT_e000ed14)[param_1 & 0xf] = param_2 << 4;
  return;
}

