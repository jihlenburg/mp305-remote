/* Address: CODE:8558; name: FUN_CODE_8558; body bytes: 57 */

void FUN_CODE_8558(void)

{
  char cVar1;
  
  cVar1 = (0xf < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x10) {
    if (DAT_INTMEM_b4 == '0') {
      return;
    }
  }
  else {
    FUN_CODE_a6a1(0x80);
    if (cVar1 < '\0') {
      return;
    }
    FUN_CODE_a60e(0xd);
    if (cVar1 < '\0') {
      if ((DAT_INTMEM_cb & 3) == 0) {
        return;
      }
      FUN_CODE_9a39();
      FUN_CODE_a03c(0x30);
    }
  }
  return;
}

