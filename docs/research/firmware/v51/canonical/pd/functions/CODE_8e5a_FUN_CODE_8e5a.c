/* Address: CODE:8e5a; name: FUN_CODE_8e5a; body bytes: 39 */

char FUN_CODE_8e5a(char *param_1)

{
  char cVar1;
  
  FUN_CODE_44df();
  cVar1 = *param_1;
  if (cVar1 == '\0') {
    FUN_CODE_44e1();
    *param_1 = *param_1 + '\x01';
    if (cVar1 == '\0') {
      return '\x04';
    }
  }
  return cVar1 + -1;
}

