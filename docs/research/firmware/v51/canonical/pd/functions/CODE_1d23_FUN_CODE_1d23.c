/* Address: CODE:1d23; name: FUN_CODE_1d23; body bytes: 4 */

char FUN_CODE_1d23(byte *param_1)

{
  byte bVar1;
  
  bVar1 = *param_1;
  *param_1 = bVar1 + 1;
  return '\x05' - (((99 < bVar1) << 7) >> 7);
}

