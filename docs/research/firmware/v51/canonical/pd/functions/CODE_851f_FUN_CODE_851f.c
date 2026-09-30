/* Address: CODE:851f; name: FUN_CODE_851f; body bytes: 57 */

void FUN_CODE_851f(void)

{
  char cVar1;
  char in_PSW;
  
  cVar1 = '\x01';
  FUN_CODE_a60e();
  if (in_PSW < '\0') {
    FUN_CODE_a6f7();
    if (cVar1 == '\x03') {
LAB_CODE_8552:
      thunk_FUN_CODE_103e();
      return;
    }
  }
  else {
    FUN_CODE_a60e(4);
    if (in_PSW < '\0') {
      FUN_CODE_a11f();
      if (in_PSW < '\0') goto LAB_CODE_8552;
    }
    else {
      cVar1 = '!';
      FUN_CODE_a6a1();
      if ((in_PSW < '\0') && (FUN_CODE_a6f7(), cVar1 == '\x03')) {
        return;
      }
    }
  }
  return;
}

