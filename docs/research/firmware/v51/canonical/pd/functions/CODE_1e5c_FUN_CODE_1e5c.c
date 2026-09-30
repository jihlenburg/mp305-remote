/* Address: CODE:1e5c; name: FUN_CODE_1e5c; body bytes: 22 */

byte FUN_CODE_1e5c(void)

{
  byte bVar1;
  
  bVar1 = DAT_EXTMEM_04ca;
  DAT_EXTMEM_04ca = DAT_EXTMEM_04ca | 0xc0;
  return bVar1 & 0xcf | 0xc0;
}

