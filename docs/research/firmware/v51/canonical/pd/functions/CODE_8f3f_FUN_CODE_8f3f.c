/* Address: CODE:8f3f; name: FUN_CODE_8f3f; body bytes: 37 */

void FUN_CODE_8f3f(char param_1)

{
  char cVar1;
  
  FUN_CODE_a5bd();
  _1_3 = '\0';
  if (2 < param_1 - 0x1dU) {
    cVar1 = (0x2d < param_1 - 0x20U) << 7;
    if (param_1 == 'N') {
      _1_3 = '\x01';
    }
    else {
      FUN_CODE_a53c();
      if (cVar1 < '\0') {
        _1_3 = '\x01';
      }
    }
  }
  if (_1_3 != '\0') {
    FUN_CODE_399f();
    return;
  }
  FUN_CODE_236b();
  return;
}

