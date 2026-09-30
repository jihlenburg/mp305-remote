/* Address: CODE:8317; name: FUN_CODE_8317; body bytes: 59 */

void FUN_CODE_8317(void)

{
  char cVar1;
  byte bVar2;
  
  FUN_CODE_6c1b(0x4ae);
  bVar2 = DAT_EXTMEM_04b0;
  cVar1 = DAT_EXTMEM_04af;
  FUN_CODE_a9ae(0,0x14,DAT_EXTMEM_04b0,DAT_EXTMEM_04af,DAT_EXTMEM_04ae);
  bVar2 = FUN_CODE_a934(bVar2 + 0x10,cVar1 - (((0xef < bVar2) << 7) >> 7));
  bVar2 = FUN_CODE_a99c(bVar2 & 0xfe);
  bVar2 = FUN_CODE_a99c(bVar2 & 0xef);
  bVar2 = FUN_CODE_a99c(bVar2 | 2);
  bVar2 = FUN_CODE_a99c(bVar2 & 0xf7);
  FUN_CODE_a99c(bVar2 | 4);
  return;
}

