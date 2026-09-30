/* Address: CODE:81ed; name: FUN_CODE_81ed; body bytes: 60 */

void FUN_CODE_81ed(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  char *pcVar5;
  
  DAT_EXTMEM_04c2 = 5;
  DAT_EXTMEM_04c3 = 0x9e;
  DAT_EXTMEM_059c = 0xaa;
  DAT_EXTMEM_059d = 0x21;
  cVar3 = '!';
  bVar2 = 0;
  while( true ) {
    pcVar5 = (char *)0x59e;
    bVar1 = (0xfe < DAT_EXTMEM_059e ^ 0x80U) - (((bVar2 < DAT_EXTMEM_059e + 1) << 7) >> 7);
    cVar4 = -0x80 - bVar1;
    if (bVar1 < 0x81) break;
    FUN_CODE_5469(cVar4);
    cVar3 = *pcVar5 + cVar3;
    bVar2 = bVar2 + 1;
  }
  FUN_CODE_5469(cVar4);
  *pcVar5 = cVar3;
  return;
}

