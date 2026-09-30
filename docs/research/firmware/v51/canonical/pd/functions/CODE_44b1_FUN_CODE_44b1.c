/* Address: CODE:44b1; name: FUN_CODE_44b1; body bytes: 14 */

char FUN_CODE_44b1(char param_1,byte param_2)

{
  return param_1 - (DAT_EXTMEM_04b0 - (((param_2 < DAT_EXTMEM_04b1) << 7) >> 7));
}

