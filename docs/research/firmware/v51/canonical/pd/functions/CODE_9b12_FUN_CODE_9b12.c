/* Address: CODE:9b12; name: FUN_CODE_9b12; body bytes: 21 */

void FUN_CODE_9b12(byte param_1)

{
  char cVar1;
  
  FUN_CODE_a521();
  cVar1 = (param_1 < 2) << 7;
  if (param_1 >= 2) {
    FUN_CODE_7a62(param_1 - 2);
    if (cVar1 < '\0') {
      FUN_CODE_8864();
      return;
    }
  }
  return;
}

