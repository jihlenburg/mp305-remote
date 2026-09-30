/* Address: CODE:7dac; name: FUN_CODE_7dac; body bytes: 67 */

void FUN_CODE_7dac(void)

{
  undefined1 uVar1;
  
  if (DAT_INTMEM_b2 == '\x10') {
    if (DAT_INTMEM_b4 == '\b') {
      return;
    }
    if (DAT_INTMEM_b4 == '\t') {
      FUN_CODE_9ba3(1);
      return;
    }
    if (DAT_INTMEM_b4 == '\x06') {
      DAT_EXTMEM_04a8 = DAT_INTMEM_cd & 0xf;
      FUN_CODE_a0cb(0);
      if (DAT_EXTMEM_04a8 == 3) {
        uVar1 = 8;
      }
      else {
        uVar1 = 9;
      }
      FUN_CODE_a223(uVar1);
    }
  }
  return;
}

