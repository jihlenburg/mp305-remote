/* Address: CODE:7b3a; name: FUN_CODE_7b3a; body bytes: 72 */

void FUN_CODE_7b3a(void)

{
  if (DAT_INTMEM_b2 == '\x10') {
    if (DAT_INTMEM_b4 == '\t') {
      if ((DAT_INTMEM_cc != 0) && (DAT_INTMEM_cc < 4)) {
        FUN_CODE_a63f(DAT_INTMEM_cc - 4,1);
      }
      return;
    }
    if (DAT_INTMEM_b4 == '\a') {
      if (DAT_INTMEM_cd >> 4 == 3) {
        FUN_CODE_9ba3(3);
        FUN_CODE_a223(9);
      }
      else {
        FUN_CODE_9ba3(2);
      }
      FUN_CODE_a0cb(0);
    }
  }
  return;
}

