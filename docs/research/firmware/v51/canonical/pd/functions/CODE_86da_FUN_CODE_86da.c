/* Address: CODE:86da; name: FUN_CODE_86da; body bytes: 52 */

void FUN_CODE_86da(char *param_1)

{
  char in_PSW;
  
  FUN_CODE_82bd();
  if (_1_3 == '\0') {
    DAT_EXTMEM_04a4 = *param_1 + -1;
  }
  else {
    DAT_EXTMEM_04a4 = *param_1 + '\x01';
  }
  _1_4 = _1_3 != '\0';
  FUN_CODE_a000(DAT_EXTMEM_04a4);
  if (in_PSW < '\0') {
    _1_5 = _1_4 & 1;
    FUN_CODE_750e(DAT_EXTMEM_04a4);
    return;
  }
  FUN_CODE_9e49();
  return;
}

