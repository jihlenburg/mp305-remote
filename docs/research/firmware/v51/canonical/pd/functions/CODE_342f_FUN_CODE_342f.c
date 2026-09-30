/* Address: CODE:342f; name: FUN_CODE_342f; body bytes: 8 */

char FUN_CODE_342f(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}

