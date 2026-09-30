/* Address: CODE:a093; name: FUN_CODE_a093; body bytes: 14 */

char FUN_CODE_a093(char param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_440b();
  return (param_1 - (((0xe0 < bVar1) << 7) >> 7)) + '\x06';
}

