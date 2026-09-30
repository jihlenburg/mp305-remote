/* Address: CODE:3442; name: FUN_CODE_3442; body bytes: 8 */

char FUN_CODE_3442(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}

