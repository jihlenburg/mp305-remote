/* Address: CODE:89b2; name: FUN_CODE_89b2; body bytes: 46 */

void FUN_CODE_89b2(char param_1)

{
  byte bVar1;
  byte in_PSW;
  
  FUN_CODE_1096();
  DAT_EXTMEM_04a3 = param_1;
  while( true ) {
    if (DAT_EXTMEM_04a3 == '\0') {
      return;
    }
    bVar1 = SADEN;
    SADEN = bVar1 & 0x7f;
    in_PSW = in_PSW & 0xdd;
    FUN_CODE_8742();
    _1_2 = -((char)in_PSW >> 7);
    bVar1 = SADEN;
    SADEN = bVar1 | 0x80;
    if (_1_2 == '\0') break;
    FUN_CODE_a7b8();
    FUN_CODE_a4fd();
    FUN_CODE_73f7();
    DAT_EXTMEM_04a3 = DAT_EXTMEM_04a3 + -1;
  }
  return;
}

