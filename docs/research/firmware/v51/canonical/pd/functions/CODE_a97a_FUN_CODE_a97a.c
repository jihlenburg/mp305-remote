/* Address: CODE:a97a; name: FUN_CODE_a97a; body bytes: 34 */

char FUN_CODE_a97a(char param_1,char *param_2,undefined1 param_3,char param_4)

{
  char cVar1;
  
  if (param_4 == '\x01') {
    param_1 = *(char *)CONCAT11(param_3,param_2) + param_1;
    *(char *)CONCAT11(param_3,param_2) = param_1;
    return param_1;
  }
  if (param_4 == '\0') {
    cVar1 = *param_2;
    *param_2 = param_1 + cVar1;
    return param_1 + cVar1;
  }
  if (param_4 == -2) {
    cVar1 = *(char *)ZEXT12(param_2);
    *(char *)ZEXT12(param_2) = cVar1 + param_1;
    return cVar1 + param_1;
  }
  return *(char *)CONCAT11(param_3,param_2) + param_1;
}

