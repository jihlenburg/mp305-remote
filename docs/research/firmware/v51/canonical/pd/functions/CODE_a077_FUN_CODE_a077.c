/* Address: CODE:a077; name: FUN_CODE_a077; body bytes: 14 */

char FUN_CODE_a077(char param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_440b();
  return (param_1 - (((0xd8 < bVar1) << 7) >> 7)) + '\x06';
}

