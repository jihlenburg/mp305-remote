/* Address: CODE:60b4; name: FUN_CODE_60b4; body bytes: 174 */

undefined1 FUN_CODE_60b4(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  
  DAT_EXTMEM_04b5 = '\0';
  DAT_EXTMEM_04b6 = '\0';
  DAT_EXTMEM_04b7 = 0;
  DAT_EXTMEM_04b8 = 0;
  DAT_EXTMEM_04b3 = DAT_INTMEM_b5 >> 4 & 7;
  DAT_EXTMEM_04b4 = 0;
  while( true ) {
    if (DAT_EXTMEM_04b3 <= DAT_EXTMEM_04b4) break;
    bVar1 = DAT_EXTMEM_04b4;
    FUN_CODE_3409();
    FUN_CODE_ad6d(0x4af);
    if ((bVar1 == 0) && ((DAT_EXTMEM_04af >> 5 & 1) != 0)) {
      DAT_EXTMEM_04b5 = '\0';
      DAT_EXTMEM_04b6 = '\x01';
    }
    if (DAT_EXTMEM_04af >> 6 == 0) {
      DAT_EXTMEM_04be = DAT_EXTMEM_04b7;
      DAT_EXTMEM_04bf = DAT_EXTMEM_04b8;
      FUN_CODE_4c77(0xaf,4,1,0xfe < DAT_EXTMEM_04b4,DAT_EXTMEM_04b4 + 1);
      DAT_EXTMEM_04b7 = param_1;
    }
    DAT_EXTMEM_04b4 = DAT_EXTMEM_04b4 + 1;
  }
  FUN_CODE_350b(DAT_EXTMEM_04b4 - DAT_EXTMEM_04b3,0x4b5,0xe4,0xb8);
  FUN_CODE_3541(0x4b7);
  FUN_CODE_87aa();
  cVar2 = DAT_EXTMEM_04b5;
  if (DAT_EXTMEM_04b5 == '\0') {
    cVar2 = DAT_EXTMEM_04b6;
  }
  if (cVar2 != '\0') {
    _1_4 = 1;
    FUN_CODE_9340();
  }
  FUN_CODE_a70f(DAT_EXTMEM_04b8);
  return DAT_EXTMEM_04b8;
}

