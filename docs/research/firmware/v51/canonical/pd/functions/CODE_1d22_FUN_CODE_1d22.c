/* Address: CODE:1d22; name: FUN_CODE_1d22; body bytes: 1 */

char FUN_CODE_1d22(byte *param_1)

{
  byte bVar1;
  
  bVar1 = *param_1;
  *param_1 = bVar1 + 1;
  return '\x05' - (((99 < bVar1) << 7) >> 7);
}

