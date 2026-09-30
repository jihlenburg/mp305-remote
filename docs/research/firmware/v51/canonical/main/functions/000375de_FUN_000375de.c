/* Address: 000375de; name: FUN_000375de; body bytes: 14 */

uint FUN_000375de(uint param_1)

{
  if (param_1 < 0x400) {
    return 1;
  }
  return param_1 >> 10;
}

