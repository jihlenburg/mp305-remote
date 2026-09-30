/* Address: 00010bf0; name: FUN_00010bf0; body bytes: 12 */

int FUN_00010bf0(int param_1)

{
  if (param_1 - 0x41U < 0x1a) {
    param_1 = param_1 + 0x20;
  }
  return param_1;
}

