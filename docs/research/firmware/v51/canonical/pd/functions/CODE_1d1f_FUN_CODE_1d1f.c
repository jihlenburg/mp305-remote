/* Address: CODE:1d1f; name: FUN_CODE_1d1f; body bytes: 3 */

char FUN_CODE_1d1f(void)

{
  byte bVar1;
  
  bVar1 = DAT_EXTMEM_04a8;
  DAT_EXTMEM_04a8 = DAT_EXTMEM_04a8 + 1;
  return '\x05' - (((99 < bVar1) << 7) >> 7);
}

