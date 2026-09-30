/* Address: CODE:44e1; name: FUN_CODE_44e1; body bytes: 8 */

char FUN_CODE_44e1(void)

{
  char in_PSW;
  
  return '\x06' - (in_PSW >> 7);
}

