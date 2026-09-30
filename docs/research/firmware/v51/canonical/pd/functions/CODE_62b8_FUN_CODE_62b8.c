/* Address: CODE:62b8; name: FUN_CODE_62b8; body bytes: 169 */

void FUN_CODE_62b8(byte param_1)

{
  undefined1 uVar1;
  char in_PSW;
  
  FUN_CODE_a471();
  DAT_EXTMEM_04a6 = param_1;
  DAT_EXTMEM_04a7 = param_1;
  FUN_CODE_a68c(2);
  if (((-1 < in_PSW) && (DAT_INTMEM_cc != '\t')) && (FUN_CODE_a60e(8), -1 < in_PSW)) {
    FUN_CODE_a60e(0xf);
    if (in_PSW < '\0') {
      if (_0_2 != '\0') {
        FUN_CODE_a64d(10);
      }
    }
    else {
      uVar1 = 10;
      FUN_CODE_a60e();
      if (in_PSW < '\0') {
        if (_0_2 == '\0') {
LAB_CODE_6312:
          if (DAT_EXTMEM_04a6 < 8) {
            DAT_EXTMEM_04a6 = 0;
          }
          if (DAT_EXTMEM_04a6 != 9) {
            if (DAT_EXTMEM_04a6 == 10) {
              FUN_CODE_7000();
              DAT_EXTMEM_04a6 = uVar1;
              goto LAB_CODE_6354;
            }
            if (DAT_EXTMEM_04a6 == 0xb) {
              FUN_CODE_8d19();
              DAT_EXTMEM_04a6 = uVar1;
              goto LAB_CODE_6354;
            }
            if (DAT_EXTMEM_04a6 == 0xc) {
              FUN_CODE_7985();
              DAT_EXTMEM_04a6 = uVar1;
              goto LAB_CODE_6354;
            }
            if (DAT_EXTMEM_04a6 != 0) goto LAB_CODE_634e;
            FUN_CODE_a485();
          }
          FUN_CODE_6d09();
          DAT_EXTMEM_04a6 = uVar1;
          goto LAB_CODE_6354;
        }
      }
      else {
        uVar1 = 2;
        FUN_CODE_a60e();
        if ((-1 < in_PSW) || (FUN_CODE_9ddf(), in_PSW < '\0')) goto LAB_CODE_6312;
        FUN_CODE_a139(DAT_INTMEM_b3);
        if (in_PSW < '\0') {
          FUN_CODE_a223(0xf);
        }
      }
    }
  }
LAB_CODE_634e:
  DAT_EXTMEM_04a6 = 9;
LAB_CODE_6354:
  FUN_CODE_71a0(DAT_EXTMEM_04a6,DAT_EXTMEM_04a7);
  return;
}

