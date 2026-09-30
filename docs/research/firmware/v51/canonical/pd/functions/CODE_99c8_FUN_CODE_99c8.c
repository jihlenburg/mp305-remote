/* Address: CODE:99c8; name: FUN_CODE_99c8; body bytes: 23 */

void FUN_CODE_99c8(void)

{
  char in_PSW;
  
  FUN_CODE_4a3f();
  FUN_CODE_a518(3,0xe8);
  if (_2_1 != '\0') {
    FUN_CODE_a7fc();
    if (-1 < in_PSW) {
      _2_1 = '\0';
      _2_0 = 1;
    }
  }
  return;
}

