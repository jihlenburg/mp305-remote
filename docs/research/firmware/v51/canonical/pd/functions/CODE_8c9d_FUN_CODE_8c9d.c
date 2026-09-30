/* Address: CODE:8c9d; name: FUN_CODE_8c9d; body bytes: 42 */

void FUN_CODE_8c9d(void)

{
  char cVar1;
  
  cVar1 = (0x11 < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x12) {
    if ((DAT_INTMEM_b4 == 'Q') || (DAT_INTMEM_b4 == '!')) {
      return;
    }
  }
  else {
    FUN_CODE_a607(0x24);
    if ((cVar1 < '\0') && ((DAT_INTMEM_cc == '\0' || (DAT_INTMEM_cc == '\t')))) {
      return;
    }
  }
  return;
}

