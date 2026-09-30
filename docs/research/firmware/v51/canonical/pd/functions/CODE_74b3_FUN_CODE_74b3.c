/* Address: CODE:74b3; name: FUN_CODE_74b3; body bytes: 91 */

void FUN_CODE_74b3(char param_1)

{
  char cVar1;
  
  if (DAT_INTMEM_b2 == '\x10') {
    if (DAT_INTMEM_b4 == 0x1c) {
      return;
    }
    if ((DAT_INTMEM_b4 == 0x2d) && (FUN_CODE_a595(), param_1 == '\0')) {
      return;
    }
  }
  else if (DAT_INTMEM_b2 == '\x12') {
    cVar1 = (0x21 < DAT_INTMEM_b4) << 7;
    if (DAT_INTMEM_b4 == 0x22) {
      FUN_CODE_a153();
      if (-1 < cVar1) {
        return;
      }
    }
    else {
      cVar1 = (6 < DAT_INTMEM_b4 - 0x22) << 7;
      if (DAT_INTMEM_b4 == 0x29) {
        FUN_CODE_a153();
        if (cVar1 < '\0') {
          return;
        }
      }
      else {
        if (DAT_INTMEM_b4 != 1) {
          return;
        }
        FUN_CODE_9ba3(9);
        FUN_CODE_a757();
        FUN_CODE_a763();
        FUN_CODE_a7ae();
        FUN_CODE_a29b();
      }
    }
  }
  return;
}

