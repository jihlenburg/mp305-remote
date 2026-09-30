/* Address: CODE:3555; name: FUN_CODE_3555; body bytes: 8 */

char FUN_CODE_3555(char param_1)

{
  char in_PSW;
  
  return param_1 - (in_PSW >> 7);
}

