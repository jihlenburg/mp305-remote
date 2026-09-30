/* Address: CODE:81b0; name: FUN_CODE_81b0; body bytes: 61 */

void FUN_CODE_81b0(char param_1)

{
  char cVar1;
  
  cVar1 = (0x11 < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x12) {
    if (DAT_INTMEM_b4 == '\v') {
      return;
    }
    if (DAT_INTMEM_b4 == '*') {
      FUN_CODE_a283();
      if (param_1 == '\x03') {
        FUN_CODE_9f59();
        FUN_CODE_a73f(0xb);
        return;
      }
      FUN_CODE_9a23(0x80,0);
      return;
    }
  }
  else {
    FUN_CODE_a607(0x2f);
    if (cVar1 < '\0') {
      return;
    }
  }
  return;
}

