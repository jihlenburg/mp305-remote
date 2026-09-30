/* Address: CODE:1d0a; name: FUN_CODE_1d0a; body bytes: 21 */

char FUN_CODE_1d0a(undefined1 param_1)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  
  bVar1 = 99 < DAT_EXTMEM_04a8;
  cVar3 = DAT_EXTMEM_04a8 + 0x9c;
  DAT_EXTMEM_04a8 = DAT_EXTMEM_04a8 + 1;
  *(undefined1 *)CONCAT11('\x05' - ((bVar1 << 7) >> 7),cVar3) = param_1;
  bVar2 = DAT_EXTMEM_04a8;
  DAT_EXTMEM_04a8 = DAT_EXTMEM_04a8 + 1;
  return '\x05' - (((99 < bVar2) << 7) >> 7);
}

