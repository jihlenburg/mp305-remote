/* Address: CODE:3469; name: FUN_CODE_3469; body bytes: 8 */

char FUN_CODE_3469(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}

