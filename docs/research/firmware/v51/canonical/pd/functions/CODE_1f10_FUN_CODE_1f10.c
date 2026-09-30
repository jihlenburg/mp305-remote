/* Address: CODE:1f10; name: FUN_CODE_1f10; body bytes: 8 */

char FUN_CODE_1f10(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  *param_1 = cVar1 + '\x01';
  return cVar1 + -100;
}

