/* Address: CODE:99f6; name: FUN_CODE_99f6; body bytes: 23 */

void FUN_CODE_99f6(void)

{
  char in_PSW;
  
  FUN_CODE_a6a8(0x18);
  if (in_PSW < '\0') {
    FUN_CODE_9f89();
  }
  else {
    FUN_CODE_a7b3();
    if (in_PSW < '\0') {
      return;
    }
  }
  return;
}

