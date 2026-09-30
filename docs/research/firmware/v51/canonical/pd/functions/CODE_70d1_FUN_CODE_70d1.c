/* Address: CODE:70d1; name: FUN_CODE_70d1; body bytes: 104 */

void FUN_CODE_70d1(char param_1)

{
  char cVar1;
  
  FUN_CODE_a467();
  cVar1 = (6 < DAT_INTMEM_b2) << 7;
  DAT_EXTMEM_04a4 = param_1;
  DAT_EXTMEM_04a5 = param_1;
  if (DAT_INTMEM_b2 == 7) {
    if (DAT_INTMEM_b4 == '\x01') {
      DAT_EXTMEM_04a6 = DAT_INTMEM_b5;
      DAT_EXTMEM_04a7 = 0;
      DAT_EXTMEM_04a8 = DAT_INTMEM_b5;
      DAT_EXTMEM_04d6 = 0;
      DAT_EXTMEM_04d7 = DAT_INTMEM_b5;
      FUN_CODE_87aa(0xb1,0xb9,0xff);
      DAT_EXTMEM_04a5 = DAT_EXTMEM_04a6 + -1;
      FUN_CODE_a0cb(DAT_EXTMEM_04a6,BANK0_R6);
    }
  }
  else {
    FUN_CODE_a60e(2);
    if (cVar1 < '\0') {
      FUN_CODE_a3c4();
      DAT_EXTMEM_04a5 = '\0';
    }
  }
  if (DAT_EXTMEM_04a4 != DAT_EXTMEM_04a5) {
    FUN_CODE_9dcd();
  }
  return;
}

