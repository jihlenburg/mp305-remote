/* Address: CODE:8dbb; name: FUN_CODE_8dbb; body bytes: 40 */

void FUN_CODE_8dbb(char param_1)

{
  DAT_EXTMEM_0448 = 0;
  if (*(char *)(param_1 + '#') == '\x02') {
    DAT_INTMEM_b3 = param_1;
    FUN_CODE_8800(param_1,0x10,3);
    FUN_CODE_1e4f(DAT_INTMEM_b3);
    FUN_CODE_a638(3,2);
  }
  return;
}

