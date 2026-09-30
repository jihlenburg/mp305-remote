/* Address: CODE:8401; name: FUN_CODE_8401; body bytes: 58 */

void FUN_CODE_8401(char param_1)

{
  if (DAT_INTMEM_b2 == '\x10') {
    if (DAT_INTMEM_b4 == '6') {
      return;
    }
    if (DAT_INTMEM_b4 == '\'') {
      return;
    }
  }
  else if ((DAT_INTMEM_b2 == '\x12') && (DAT_INTMEM_b4 != '\x01')) {
    if (DAT_INTMEM_b4 == '\x06') {
      FUN_CODE_a739();
      if (param_1 == '\a') {
        FUN_CODE_a03c(0x36);
      }
      return;
    }
    return;
  }
  return;
}

