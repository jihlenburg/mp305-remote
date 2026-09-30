/* Address: CODE:345c; name: FUN_CODE_345c; body bytes: 8 */

char FUN_CODE_345c(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}

