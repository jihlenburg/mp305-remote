/* Address: CODE:8a68; name: FUN_CODE_8a68; body bytes: 45 */

void FUN_CODE_8a68(void)

{
  char cVar1;
  char cVar2;
  char in_PSW;
  
  _1_4 = 0;
  cVar1 = '\0';
  FUN_CODE_7763();
  FUN_CODE_9983();
  FUN_CODE_a335();
  if (in_PSW < '\0') {
    FUN_CODE_a5bd();
    if (cVar1 == '\x0e') {
      FUN_CODE_37ff();
    }
    else if (cVar1 == '\n') {
      cVar2 = -0x80;
      cVar1 = '\0';
      FUN_CODE_9a0d();
      if (cVar2 == '\0' && cVar1 == '\0') {
        FUN_CODE_7069();
        return;
      }
    }
  }
  return;
}

