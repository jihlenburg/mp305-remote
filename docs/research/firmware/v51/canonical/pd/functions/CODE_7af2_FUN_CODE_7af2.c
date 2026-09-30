/* Address: CODE:7af2; name: FUN_CODE_7af2; body bytes: 72 */

void FUN_CODE_7af2(char param_1,byte param_2)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  
  bVar2 = (byte)((ushort)DAT_INTMEM_b3 * 0x19);
  DAT_EXTMEM_04b4 = param_1;
  DAT_EXTMEM_04b5 = param_2;
  cVar3 = FUN_CODE_a94d(0x14,bVar2 + 0xbb,
                        ((char)((ushort)DAT_INTMEM_b3 * 0x19 >> 8) - (((0x44 < bVar2) << 7) >> 7)) +
                        '\x06',1);
  if (cVar3 != '\0') {
    bVar2 = FUN_CODE_a94d(0x10);
    if ((bVar2 & 1) != 0) {
      bVar1 = 0x9b < DAT_EXTMEM_04b5;
      DAT_EXTMEM_04b5 = DAT_EXTMEM_04b5 + 100;
      DAT_EXTMEM_04b4 = DAT_EXTMEM_04b4 - ((bVar1 << 7) >> 7);
    }
  }
  FUN_CODE_ab68(DAT_EXTMEM_04b4,2,DAT_EXTMEM_04b5);
  return;
}

