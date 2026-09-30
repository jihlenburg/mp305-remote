/* Address: CODE:7985; name: FUN_CODE_7985; body bytes: 75 */

void FUN_CODE_7985(void)

{
  char in_PSW;
  
  FUN_CODE_a68c(1);
  if (-1 < in_PSW) {
    FUN_CODE_a607(0xc);
    if (-1 < in_PSW) {
      return;
    }
    FUN_CODE_a64d(10);
    return;
  }
  if (DAT_INTMEM_cc != '\x04') {
    if ((DAT_INTMEM_cc != '\x03') ||
       (((DAT_INTMEM_cd != 'C' && (DAT_INTMEM_cd != 'D')) && (DAT_INTMEM_cd != '3'))))
    goto LAB_CODE_79ac;
    FUN_CODE_9ba3(4);
  }
  FUN_CODE_58e1();
LAB_CODE_79ac:
  if (DAT_INTMEM_cd == '\"') {
    FUN_CODE_a223(0xc);
  }
  else {
    FUN_CODE_a22f();
  }
  return;
}

