/* Address: CODE:7000; name: FUN_CODE_7000; body bytes: 105 */

void FUN_CODE_7000(void)

{
  char in_PSW;
  
  FUN_CODE_a607(10);
  if (in_PSW < '\0') {
    return;
  }
  FUN_CODE_a607(0xe);
  if (-1 < in_PSW) {
    FUN_CODE_a60e(0x11);
    if (in_PSW < '\0') {
      if (DAT_INTMEM_cd != '3') {
        FUN_CODE_a22f();
      }
    }
    else {
      FUN_CODE_a607(0xc);
      if (in_PSW < '\0') {
        FUN_CODE_a64d(10);
        return;
      }
      FUN_CODE_a68c(1);
      if (in_PSW < '\0') {
        FUN_CODE_a22f();
        if (DAT_INTMEM_cd == '\"') {
          FUN_CODE_a223(0xc);
        }
        else if (DAT_INTMEM_cd == '3') {
          FUN_CODE_a23b(10);
          return;
        }
        FUN_CODE_a3cf();
      }
      else {
        FUN_CODE_a607(5);
        if (in_PSW < '\0') {
          return;
        }
      }
    }
    return;
  }
  return;
}

