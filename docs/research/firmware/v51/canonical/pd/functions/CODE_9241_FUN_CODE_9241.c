/* Address: CODE:9241; name: FUN_CODE_9241; body bytes: 32 */

void FUN_CODE_9241(byte param_1,byte param_2)

{
  param_2 = *(byte *)(DAT_INTMEM_b3 * '\x02' + '.') ^ param_2;
  if (param_2 == 0) {
    param_2 = *(byte *)(DAT_INTMEM_b3 * '\x02' + '-') ^ param_1;
  }
  if (param_2 != 0) {
    FUN_CODE_1e41(DAT_INTMEM_b3 * '\x02' + '-');
    FUN_CODE_766b();
  }
  return;
}

