/* Address: CODE:94ea; name: FUN_CODE_94ea; body bytes: 30 */

void FUN_CODE_94ea(void)

{
  char in_PSW;
  
  FUN_CODE_a6a1(6);
  if (in_PSW < '\0') {
    return;
  }
  FUN_CODE_a607(0x38);
  if ((in_PSW < '\0') && (FUN_CODE_a53c(), in_PSW < '\0')) {
    return;
  }
  return;
}

