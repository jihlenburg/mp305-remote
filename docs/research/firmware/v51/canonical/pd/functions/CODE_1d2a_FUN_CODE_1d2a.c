/* Address: CODE:1d2a; name: FUN_CODE_1d2a; body bytes: 2 */

char FUN_CODE_1d2a(void)

{
  char in_PSW;
  
  return '\x05' - (in_PSW >> 7);
}

