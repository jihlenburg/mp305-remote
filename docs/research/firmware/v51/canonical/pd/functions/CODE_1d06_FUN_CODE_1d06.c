/* Address: CODE:1d06; name: FUN_CODE_1d06; body bytes: 4 */

/* Inferred entry from 6 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_1d06(char param_1)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  
  bVar1 = 99 < DAT_EXTMEM_04a8;
  cVar3 = DAT_EXTMEM_04a8 + 0x9c;
  DAT_EXTMEM_04a8 = DAT_EXTMEM_04a8 + 1;
  *(undefined1 *)CONCAT11('\x05' - ((bVar1 << 7) >> 7),cVar3) = *(undefined1 *)(param_1 + '\x01');
  bVar2 = DAT_EXTMEM_04a8;
  DAT_EXTMEM_04a8 = DAT_EXTMEM_04a8 + 1;
  return '\x05' - (((99 < bVar2) << 7) >> 7);
}

