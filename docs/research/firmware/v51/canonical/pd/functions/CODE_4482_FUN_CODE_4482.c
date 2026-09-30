/* Address: CODE:4482; name: FUN_CODE_4482; body bytes: 8 */

char FUN_CODE_4482(void)

{
  char in_PSW;
  
  return '\x06' - (in_PSW >> 7);
}

