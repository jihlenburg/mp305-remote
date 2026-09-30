/* Address: CODE:9436; name: FUN_CODE_9436; body bytes: 30 */

void FUN_CODE_9436(void)

{
  if (DAT_INTMEM_b3 == '\0') {
    P0_5 = _1_5 & 1;
    DAT_EXTMEM_06b7 = _1_5 & 1;
    return;
  }
  CPRL2 = _1_5 & 1;
  DAT_EXTMEM_06b8 = _1_5 & 1;
  return;
}

