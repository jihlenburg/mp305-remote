/* Address: CODE:8136; name: FUN_CODE_8136; body bytes: 61 */

void FUN_CODE_8136(void)

{
  char cVar1;
  
  cVar1 = (0xf < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x10) {
    if (DAT_INTMEM_b4 == '\r') {
      FUN_CODE_a63f(0x20);
      return;
    }
    if (DAT_INTMEM_b4 == '\v') {
      FUN_CODE_a63f(0x21);
    }
  }
  else {
    FUN_CODE_a68c(1);
    if (((cVar1 < '\0') && (DAT_INTMEM_cc == '\x03')) && (DAT_INTMEM_b7 == '\x02')) {
      FUN_CODE_a223(0xd);
    }
  }
  return;
}

