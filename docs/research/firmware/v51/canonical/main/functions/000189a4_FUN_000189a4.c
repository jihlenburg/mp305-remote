/* Address: 000189a4; name: FUN_000189a4; body bytes: 42 */

uint FUN_000189a4(uint param_1,uint param_2,uint param_3)

{
  return param_1 & 7 | (param_2 / 10 & 0x3ff) << 6 | param_3 / 10 << 0x16;
}

