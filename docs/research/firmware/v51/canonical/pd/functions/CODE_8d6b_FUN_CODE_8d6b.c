/* Address: CODE:8d6b; name: FUN_CODE_8d6b; body bytes: 40 */

void FUN_CODE_8d6b(void)

{
  char in_PSW;
  
  FUN_CODE_a53c();
  if (in_PSW < '\0') {
    if (DAT_INTMEM_cc != '\t') {
      FUN_CODE_8e5a();
      FUN_CODE_a50f();
      return;
    }
  }
  else if (DAT_INTMEM_cc != '\t') {
    FUN_CODE_93fa(0xb,0xb8,0x13,0x88);
    FUN_CODE_866f();
  }
  return;
}

