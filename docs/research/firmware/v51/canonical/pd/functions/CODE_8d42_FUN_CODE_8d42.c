/* Address: CODE:8d42; name: FUN_CODE_8d42; body bytes: 41 */

void FUN_CODE_8d42(void)

{
  char cVar1;
  
  cVar1 = (0xf < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x10) {
    if (DAT_INTMEM_b4 == '*') {
      FUN_CODE_6a27(0xd);
    }
    else if (DAT_INTMEM_b4 == '\x1c') {
      return;
    }
  }
  else {
    FUN_CODE_a6a1(3);
    if (cVar1 < '\0') {
      return;
    }
  }
  return;
}

