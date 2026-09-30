/* Address: CODE:8000; name: FUN_CODE_8000; body bytes: 26 */

void FUN_CODE_8000(char param_1,char param_2)

{
  DAT_EXTMEM_0390 = 0;
  FUN_CODE_ae53(param_2);
  if ((param_1 == '`') && (param_2 != 'f')) {
    DAT_EXTMEM_0390 = 1;
  }
  return;
}

