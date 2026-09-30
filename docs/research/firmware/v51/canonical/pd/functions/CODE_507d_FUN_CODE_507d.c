/* Address: CODE:507d; name: FUN_CODE_507d; body bytes: 8 */

char FUN_CODE_507d(void)

{
  char in_PSW;
  
  return '\a' - (in_PSW >> 7);
}

