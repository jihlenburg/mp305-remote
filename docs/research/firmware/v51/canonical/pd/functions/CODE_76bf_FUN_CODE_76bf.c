/* Address: CODE:76bf; name: FUN_CODE_76bf; body bytes: 23 */

void FUN_CODE_76bf(void)

{
  DAT_EXTMEM_1011 = DAT_EXTMEM_1011 & 0x3f | 0x40;
  DAT_EXTMEM_1010 = DAT_EXTMEM_1010 & 0xfc | 1;
  return;
}

