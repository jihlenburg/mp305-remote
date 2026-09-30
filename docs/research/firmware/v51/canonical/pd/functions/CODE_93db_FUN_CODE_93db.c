/* Address: CODE:93db; name: FUN_CODE_93db; body bytes: 31 */

void FUN_CODE_93db(void)

{
  char cVar1;
  
  cVar1 = (0x11 < DAT_INTMEM_ab) << 7;
  if (DAT_INTMEM_ab == 0x12) {
    FUN_CODE_a693();
    if (cVar1 < '\0') {
      return;
    }
  }
  else {
    FUN_CODE_9eb9(0x26,0x10);
  }
  return;
}

