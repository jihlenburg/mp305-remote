/* Address: CODE:8e33; name: FUN_CODE_8e33; body bytes: 40 */

void FUN_CODE_8e33(void)

{
  if (DAT_INTMEM_b2 == '\x10') {
    if (DAT_INTMEM_b4 == 'M') {
      return;
    }
    if (DAT_INTMEM_b4 == 'N') {
      FUN_CODE_99c8();
      FUN_CODE_666b(0x5f,7,1,0x4e);
    }
    else if (DAT_INTMEM_b4 == 'L') {
      return;
    }
  }
  return;
}

