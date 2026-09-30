/* Address: CODE:8c1e; name: FUN_CODE_8c1e; body bytes: 43 */

void FUN_CODE_8c1e(void)

{
  char cVar1;
  char in_PSW;
  
  cVar1 = '*';
  FUN_CODE_a6a1();
  if (in_PSW < '\0') {
    FUN_CODE_a283();
    if (cVar1 == '\x02') {
      return;
    }
  }
  else {
    FUN_CODE_a607(0x1c);
    if ((-1 < in_PSW) && (FUN_CODE_a607(0x2f), -1 < in_PSW)) {
      return;
    }
  }
  FUN_CODE_a73f(9);
  return;
}

