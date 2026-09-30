/* Address: CODE:9508; name: FUN_CODE_9508; body bytes: 30 */

void FUN_CODE_9508(void)

{
  char cVar1;
  char in_PSW;
  
  cVar1 = 'P';
  FUN_CODE_a6a1();
  if (in_PSW < '\0') {
    FUN_CODE_9696();
    if (cVar1 == '\x04') {
      return;
    }
  }
  else {
    FUN_CODE_a607(0x39);
    if (in_PSW < '\0') {
      return;
    }
  }
  return;
}

