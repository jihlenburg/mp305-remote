/* Address: CODE:6de5; name: FUN_CODE_6de5; body bytes: 108 */

void FUN_CODE_6de5(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(DAT_INTMEM_b3 * '\x02' + -0x6a) ^ param_2;
  if (bVar1 == 0) {
    bVar1 = *(byte *)(DAT_INTMEM_b3 * '\x02' + -0x6b) ^ param_1;
  }
  DAT_EXTMEM_04b2 = param_1;
  DAT_EXTMEM_04b3 = param_2;
  if (bVar1 != 0) {
    if ((DAT_INTMEM_b3 == '\x01') &&
       (bVar1 = (param_1 + ('\x01' - (((0xb < param_2) << 7) >> 7))) -
                (((bINTMEM98 < param_2 - 0xb) << 7) >> 7), bVar1 <= bINTMEM97)) {
      _1_5 = 1;
      FUN_CODE_9436(bINTMEM97 - bVar1);
    }
    bVar1 = DAT_EXTMEM_04b2;
    FUN_CODE_1e41(DAT_INTMEM_b3 * '\x02' + -0x6b,DAT_EXTMEM_04b2,DAT_EXTMEM_04b3);
    FUN_CODE_1e7e(bVar1,0x5d,0xb1,0xff);
    FUN_CODE_87aa();
    FUN_CODE_937e(DAT_EXTMEM_04b2,DAT_EXTMEM_04b3);
  }
  return;
}

