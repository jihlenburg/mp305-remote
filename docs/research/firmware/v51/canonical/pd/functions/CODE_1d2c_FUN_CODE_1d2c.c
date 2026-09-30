/* Address: CODE:1d2c; name: FUN_CODE_1d2c; body bytes: 6 */

char FUN_CODE_1d2c(void)

{
  char in_PSW;
  
  return '\x05' - (in_PSW >> 7);
}

