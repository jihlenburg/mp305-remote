/* Address: CODE:51f5; name: FUN_CODE_51f5; body bytes: 189 */

byte FUN_CODE_51f5(short param_1)

{
  undefined1 uVar1;
  byte bVar2;
  char cVar3;
  
  if (DAT_INTMEM_b2 == '\x03') {
    if (DAT_INTMEM_b4 != '\r') {
      if (DAT_INTMEM_b4 == '\x13') {
        return 0;
      }
      if (DAT_INTMEM_b4 == '\x14') {
        return 0;
      }
      if (DAT_INTMEM_b4 - 2U != 0) {
        return DAT_INTMEM_b4 - 2U;
      }
    }
    return 0;
  }
  cVar3 = (0xe < DAT_INTMEM_b2 - 3U) << 7;
  if (DAT_INTMEM_b2 == '\x12') {
    bVar2 = FUN_CODE_ae53(DAT_INTMEM_b4);
    bINTMEM47 = bINTMEM47 & bVar2;
    uVar1 = TR0;
    return *(byte *)(param_1 + 1) & 0xf;
  }
  bVar2 = FUN_CODE_a607(0x22);
  if (-1 < cVar3) {
    bVar2 = FUN_CODE_a607(0x39);
    if (-1 < cVar3) {
      return bVar2;
    }
    return bVar2;
  }
  return bVar2;
}

