/* Address: CODE:8d19; name: FUN_CODE_8d19; body bytes: 41 */

void FUN_CODE_8d19(void)

{
  char in_PSW;
  
  FUN_CODE_a68c(1);
  if (in_PSW < '\0') {
    FUN_CODE_a22f();
    if (DAT_INTMEM_cd == '\"') {
      FUN_CODE_a223(0xc);
    }
  }
  else {
    FUN_CODE_a607(0xc);
    if (in_PSW < '\0') {
      FUN_CODE_a64d(10);
      return;
    }
  }
  return;
}

