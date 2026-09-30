/* Address: 000370a2; name: FUN_000370a2; body bytes: 10 */

uint FUN_000370a2(uint param_1)

{
  param_1 = param_1 & 0xf;
  if (param_1 == 0) {
    param_1 = 1;
  }
  return param_1;
}

