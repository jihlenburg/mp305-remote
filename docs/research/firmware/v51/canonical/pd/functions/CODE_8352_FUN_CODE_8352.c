/* Address: CODE:8352; name: FUN_CODE_8352; body bytes: 59 */

void FUN_CODE_8352(void)

{
  bool bVar1;
  char cVar2;
  
  cVar2 = (0x11 < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x12) {
    if (DAT_INTMEM_b4 == '\x01') {
      FUN_CODE_a7ae();
    }
    else {
      bVar1 = 2 < DAT_INTMEM_b4 - 1U;
      if ((DAT_INTMEM_b4 != '\x04') && (bVar1 = 7 < DAT_INTMEM_b4 - 4U, DAT_INTMEM_b4 != '\f')) {
        if (DAT_INTMEM_b4 - 1U != 2) {
          return;
        }
        return;
      }
      cVar2 = bVar1 << 7;
      FUN_CODE_a3a3();
      if (cVar2 < '\0') {
        return;
      }
    }
  }
  else {
    FUN_CODE_a607(0x1c);
    if (cVar2 < '\0') {
      return;
    }
  }
  return;
}

