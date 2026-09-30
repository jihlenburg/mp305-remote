/* Address: 00020138; name: FUN_00020138; body bytes: 32 */

void FUN_00020138(uint param_1,char param_2)

{
  if (-1 < (int)param_1) {
    (&DAT_e000e400)[param_1] = param_2 << 4;
    return;
  }
  (&DAT_e000ed14)[param_1 & 0xf] = param_2 << 4;
  return;
}

