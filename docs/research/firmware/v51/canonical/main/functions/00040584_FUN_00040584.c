/* Address: 00040584; name: FUN_00040584; body bytes: 26 */

int FUN_00040584(uint param_1)

{
  return ((param_1 & 0xff00) - 0x1000000) + (param_1 & 0xff) + (param_1 & 0xff0000);
}

