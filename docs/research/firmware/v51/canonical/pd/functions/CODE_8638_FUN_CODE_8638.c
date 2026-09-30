/* Address: CODE:8638; name: FUN_CODE_8638; body bytes: 55 */

void FUN_CODE_8638(void)

{
  char cVar1;
  
  cVar1 = (0x11 < DAT_INTMEM_b2) << 7;
  if (DAT_INTMEM_b2 == 0x12) {
    if ((DAT_INTMEM_b4 == '\x04') || (DAT_INTMEM_b4 == '\f')) {
      return;
    }
    if (DAT_INTMEM_b4 == '\x10') {
      return;
    }
    cVar1 = (0xf2 < DAT_INTMEM_b4 - 0x10U) << 7;
    if ((DAT_INTMEM_b4 == '\x03') && (FUN_CODE_a65b(), cVar1 < '\0')) {
      return;
    }
  }
  else {
    FUN_CODE_a607(0x1c);
    if (cVar1 < '\0') {
      return;
    }
  }
  return;
}

