/* Address: CODE:451a; name: FUN_CODE_451a; body bytes: 7 */

char FUN_CODE_451a(byte param_1,char param_2)

{
  return param_2 - ('\x0f' - (((param_1 < 0x2c) << 7) >> 7));
}

