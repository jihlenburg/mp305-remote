/* Address: CODE:9281; name: FUN_CODE_9281; body bytes: 32 */

void FUN_CODE_9281(void)

{
  undefined1 uVar1;
  
  if (DAT_INTMEM_b9 == '\x01') {
    FUN_CODE_9c39(0x24);
    uVar1 = 0x22;
  }
  else {
    if (DAT_INTMEM_b9 != '\0') {
      return;
    }
    FUN_CODE_9c39(0x23);
    uVar1 = 0x21;
  }
  FUN_CODE_ae2a(0x717,uVar1);
  return;
}

