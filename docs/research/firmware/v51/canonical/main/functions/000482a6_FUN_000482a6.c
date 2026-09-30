/* Address: 000482a6; name: FUN_000482a6; body bytes: 28 */

byte FUN_000482a6(char *param_1)

{
  if ((param_1 != (char *)0x0) && ((*param_1 == '\x01' || (*param_1 == '\x03')))) {
    return param_1[0x98] & 0xf;
  }
  return 0;
}

