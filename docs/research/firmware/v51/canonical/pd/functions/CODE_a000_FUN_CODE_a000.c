/* Address: CODE:a000; name: FUN_CODE_a000; body bytes: 15 */

char FUN_CODE_a000(byte param_1)

{
  char cVar1;
  
  cVar1 = param_1 - 2;
  if ((1 < param_1) && (cVar1 = param_1 - 4, param_1 < 4)) {
    return cVar1;
  }
  return cVar1;
}

