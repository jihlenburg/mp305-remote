/* Address: CODE:6c1b; name: FUN_CODE_6c1b; body bytes: 26 */

/* WARNING: Removing unreachable block (CODE,0x6c61) */

void FUN_CODE_6c1b(undefined1 *param_1)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  
  bVar1 = (byte)((ushort)DAT_INTMEM_b3 * 0x19);
  *param_1 = 1;
  param_1[1] = ((char)((ushort)DAT_INTMEM_b3 * 0x19 >> 8) - (((0x44 < bVar1) << 7) >> 7)) + '\x06';
  param_1[2] = bVar1 + 0xbb;
  _1_5 = 0;
  bVar2 = (byte)((ushort)DAT_INTMEM_b3 * 0x19);
  bVar1 = bVar2 + 0xbb;
  cVar3 = ((char)((ushort)DAT_INTMEM_b3 * 0x19 >> 8) - (((0x44 < bVar2) << 7) >> 7)) + '\x06';
  DAT_EXTMEM_04b1 = 1;
  DAT_EXTMEM_04b2 = cVar3;
  DAT_EXTMEM_04b3 = bVar1;
  FUN_CODE_a9ae(0,0x14,bVar1,cVar3,1);
  bVar1 = FUN_CODE_a934(bVar1 + 0x10,cVar3 - (((0xef < bVar1) << 7) >> 7));
  FUN_CODE_a99c(bVar1 | 4);
  return;
}

