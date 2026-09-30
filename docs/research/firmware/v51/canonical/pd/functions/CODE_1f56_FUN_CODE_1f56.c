/* Address: CODE:1f56; name: FUN_CODE_1f56; body bytes: 10 */

char FUN_CODE_1f56(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  *param_1 = cVar1 + '\x01';
  return cVar1 + -100;
}

