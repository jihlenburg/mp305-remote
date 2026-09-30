/* Address: CODE:85c9; name: FUN_CODE_85c9; body bytes: 56 */

void FUN_CODE_85c9(void)

{
  char cVar1;
  
  cVar1 = (0xf < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x10) {
    if (DAT_INTMEM_b4 == '.') {
      FUN_CODE_a499();
    }
    else {
      cVar1 = (0xfc < DAT_INTMEM_b4 - 0x2eU) << 7;
      if (DAT_INTMEM_b4 == '+') {
        FUN_CODE_9490(5);
        FUN_CODE_a53c();
        if (cVar1 < '\0') {
          return;
        }
      }
    }
  }
  else {
    FUN_CODE_a6a8(0xe);
    if (cVar1 < '\0') {
      thunk_FUN_CODE_1046();
      FUN_CODE_a03c(0x2e);
    }
  }
  return;
}

