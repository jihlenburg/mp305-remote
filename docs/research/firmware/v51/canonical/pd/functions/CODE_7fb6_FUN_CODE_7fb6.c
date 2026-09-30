/* Address: CODE:7fb6; name: FUN_CODE_7fb6; body bytes: 63 */

char FUN_CODE_7fb6(char param_1,char param_2)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_04a8 = 0xb2;
  DAT_EXTMEM_04a9 = 0x71;
  bVar2 = 0;
  cVar1 = '\0';
  do {
    uVar3 = 2;
    uVar4 = FUN_CODE_aa83(0,0x4a8);
    if (*(byte *)CONCAT11(uVar4,uVar3) <
        (byte)(param_1 - (((((byte *)CONCAT11(uVar4,uVar3))[1] < param_2 + 1U) << 7) >> 7))) {
      return cVar1 + (-1 - (((0x27 < bVar2) << 7) >> 7));
    }
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while (bVar2 != 0xa4 || cVar1 != '\0');
  return '\0';
}

