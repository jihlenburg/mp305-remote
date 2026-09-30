/* Address: CODE:93bc; name: FUN_CODE_93bc; body bytes: 31 */

void FUN_CODE_93bc(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    DAT_EXTMEM_06ed = 6;
    DAT_EXTMEM_06ee = 0xf9;
  }
  else if (DAT_INTMEM_b3 == '\0') {
    DAT_EXTMEM_06ed = 6;
    DAT_EXTMEM_06ee = 0xf1;
    return;
  }
  return;
}

