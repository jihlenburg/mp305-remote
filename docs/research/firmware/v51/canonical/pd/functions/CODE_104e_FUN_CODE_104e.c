/* Address: CODE:104e; name: FUN_CODE_104e; body bytes: 37 */

void FUN_CODE_104e(void)

{
  byte bVar1;
  char cVar2;
  
  bVar1 = 0xb - (((DAT_EXTMEM_05dd < 0xb9) << 7) >> 7);
  cVar2 = DAT_EXTMEM_05dc - bVar1;
  if (bVar1 <= DAT_EXTMEM_05dc) {
    DAT_EXTMEM_05dc = 0;
    DAT_EXTMEM_05dd = 0;
    FUN_CODE_9924();
    cVar2 = FUN_CODE_9e59(2,7);
  }
  FUN_CODE_a7a4(cVar2);
  FUN_CODE_8bc8(0);
  return;
}

