/* Address: CODE:8d93; name: FUN_CODE_8d93; body bytes: 40 */

void FUN_CODE_8d93(void)

{
  byte in_PSW;
  
  _1_4 = 1;
  FUN_CODE_7616();
  _1_3 = in_PSW >> 7;
  if ((((DAT_INTMEM_b4 == '\x0e') || (DAT_INTMEM_b4 == '\t')) && (DAT_EXTMEM_0af4 == '\0')) &&
     (DAT_EXTMEM_0af2 == '\0')) {
    FUN_CODE_a19f();
  }
  DAT_EXTMEM_074a = DAT_EXTMEM_074a + '\x01';
  return;
}

