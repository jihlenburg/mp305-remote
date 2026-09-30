/* Address: CODE:34f4; name: FUN_CODE_34f4; body bytes: 8 */

char FUN_CODE_34f4(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}

