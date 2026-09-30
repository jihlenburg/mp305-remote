/* Address: CODE:7eb6; name: FUN_CODE_7eb6; body bytes: 65 */

void FUN_CODE_7eb6(char param_1)

{
  char cVar1;
  char in_PSW;
  
  FUN_CODE_a727();
  cVar1 = '\x01';
  DAT_EXTMEM_04c4 = param_1;
  FUN_CODE_a69a();
  if (in_PSW < '\0') {
    DAT_EXTMEM_04c4 = '\x01';
  }
  else if (DAT_EXTMEM_04c4 == '\x05') {
    FUN_CODE_993c();
    DAT_EXTMEM_04c4 = cVar1;
  }
  else if (DAT_EXTMEM_04c4 == '\a') {
    FUN_CODE_a0e7();
    DAT_EXTMEM_04c4 = cVar1;
  }
  else if (DAT_EXTMEM_04c4 == '\x02') {
    FUN_CODE_967b();
    DAT_EXTMEM_04c4 = cVar1;
  }
  FUN_CODE_5e73(DAT_EXTMEM_04c4);
  return;
}

