/* Address: CODE:4512; name: FUN_CODE_4512; body bytes: 8 */

char FUN_CODE_4512(void)

{
  char in_PSW;
  
  return '\x05' - (in_PSW >> 7);
}

