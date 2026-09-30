/* Address: CODE:6361; name: FUN_CODE_6361; body bytes: 165 */

void FUN_CODE_6361(char param_1)

{
  undefined1 *puVar1;
  
  FUN_CODE_a521();
  DAT_EXTMEM_04ac = param_1;
  if (DAT_INTMEM_be == '\x10') {
    if (DAT_INTMEM_c0 == 'J') {
      FUN_CODE_5f2c();
    }
    else if (DAT_INTMEM_c0 == 'I') {
      FUN_CODE_37fe();
    }
  }
  else if (DAT_INTMEM_be == '\x14') {
    if ((DAT_INTMEM_c0 != '\x01') && (DAT_INTMEM_c0 == '\b')) {
      FUN_CODE_8864();
    }
  }
  else if (DAT_INTMEM_be == '\t') {
    puVar1 = &DAT_INTMEM_c0;
    if ((DAT_INTMEM_c0 == '\a') || (DAT_INTMEM_c0 == '\t')) {
      FUN_CODE_a54e();
    }
    else if (DAT_INTMEM_c0 == '\v') {
      FUN_CODE_9645();
      FUN_CODE_50a1();
      *puVar1 = 0;
      FUN_CODE_87aa(0xa5,0xb8,0xff);
    }
    else if (DAT_INTMEM_c0 == '\f') {
      FUN_CODE_962a();
    }
    else if (DAT_INTMEM_c0 == '\n') {
      FUN_CODE_9221();
    }
  }
  if (DAT_EXTMEM_04ac == '\x01') {
    FUN_CODE_a187();
    DAT_EXTMEM_04ac = param_1;
  }
  else if (DAT_EXTMEM_04ac - 1U < 4) {
    FUN_CODE_8a0e();
    DAT_EXTMEM_04ac = param_1;
  }
  else if (DAT_EXTMEM_04ac - 1U == 0xff) {
    FUN_CODE_a31f();
    DAT_EXTMEM_04ac = param_1;
  }
  FUN_CODE_a521();
  FUN_CODE_726d(DAT_EXTMEM_04ac);
  return;
}

