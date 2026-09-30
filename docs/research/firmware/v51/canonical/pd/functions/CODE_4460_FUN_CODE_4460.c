/* Address: CODE:4460; name: FUN_CODE_4460; body bytes: 8 */

char FUN_CODE_4460(void)

{
  char in_PSW;
  
  return '\x06' - (in_PSW >> 7);
}

