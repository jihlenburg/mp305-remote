/* Address: CODE:a47b; name: FUN_CODE_a47b; body bytes: 10 */

void FUN_CODE_a47b(byte *param_1)

{
  *param_1 = *param_1 & 0xfc;
  param_1[1] = param_1[1] & 0xfc;
  return;
}

