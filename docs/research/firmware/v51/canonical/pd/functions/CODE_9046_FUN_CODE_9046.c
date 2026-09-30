/* Address: CODE:9046; name: FUN_CODE_9046; body bytes: 35 */

void FUN_CODE_9046(void)

{
  undefined1 uVar1;
  
  FUN_CODE_80bc();
  if (DAT_INTMEM_b3 == '\x01') {
    FUN_CODE_9c2f(0x24);
    uVar1 = 0x22;
  }
  else {
    if (DAT_INTMEM_b3 != '\0') {
      return;
    }
    FUN_CODE_9c2f(0x23);
    uVar1 = 0x21;
  }
  FUN_CODE_ae2a(0x71d,uVar1);
  return;
}

