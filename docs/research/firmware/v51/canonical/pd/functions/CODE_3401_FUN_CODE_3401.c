/* Address: CODE:3401; name: FUN_CODE_3401; body bytes: 8 */

char FUN_CODE_3401(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}

