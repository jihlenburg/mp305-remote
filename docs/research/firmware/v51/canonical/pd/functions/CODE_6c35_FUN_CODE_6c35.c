/* Address: CODE:6c35; name: FUN_CODE_6c35; body bytes: 93 */

void FUN_CODE_6c35(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  
  bVar1 = (byte)((ushort)DAT_INTMEM_b3 * 0x19);
  bVar2 = bVar1 + 0xbb;
  cVar3 = ((char)((ushort)DAT_INTMEM_b3 * 0x19 >> 8) - (((0x44 < bVar1) << 7) >> 7)) + '\x06';
  DAT_EXTMEM_04b1 = 1;
  DAT_EXTMEM_04b2 = cVar3;
  DAT_EXTMEM_04b3 = bVar2;
  if (_1_5 == '\0') {
    FUN_CODE_a9ae(0,0x14,bVar2,cVar3,1);
    bVar2 = FUN_CODE_a934(bVar2 + 0x10,cVar3 - (((0xef < bVar2) << 7) >> 7));
    bVar2 = bVar2 | 4;
  }
  else {
    FUN_CODE_a9ae(1,0x14,1);
    bVar2 = FUN_CODE_a934(bVar2 + 0x10,cVar3 - (((0xef < bVar2) << 7) >> 7));
    bVar2 = FUN_CODE_a99c(bVar2 | 2);
    bVar2 = FUN_CODE_a99c(bVar2 & 0xfb);
    bVar2 = bVar2 & 0xf7;
  }
  FUN_CODE_a99c(bVar2);
  return;
}

