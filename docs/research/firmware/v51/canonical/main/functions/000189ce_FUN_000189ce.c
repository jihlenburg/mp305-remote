/* Address: 000189ce; name: FUN_000189ce; body bytes: 44 */

uint FUN_000189ce(uint param_1,uint param_2,uint param_3)

{
  return param_1 & 7 | (param_2 / 0x32 & 0x3ff) << 6 | param_3 / 10 << 0x16;
}

