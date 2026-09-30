/* Address: CODE:1e0a; name: FUN_CODE_1e0a; body bytes: 17 */

char FUN_CODE_1e0a(void)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_04b2;
  DAT_EXTMEM_04b2 = DAT_EXTMEM_04b2 + '\x01';
  return cVar1 + -100;
}

