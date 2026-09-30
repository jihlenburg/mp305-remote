/* Address: CODE:6d09; name: FUN_CODE_6d09; body bytes: 111 */

void FUN_CODE_6d09(void)

{
  undefined1 uVar1;
  char in_PSW;
  
  FUN_CODE_a60e(10);
  if (in_PSW < '\0') {
    FUN_CODE_a485();
  }
  else {
    FUN_CODE_a60e(0xd);
    if (in_PSW < '\0') {
      if (_0_2 != '\0') {
        FUN_CODE_a223(0xe);
      }
    }
    else {
      FUN_CODE_a60e(0x11);
      if (-1 < in_PSW) {
        FUN_CODE_a607(0xe);
        if (in_PSW < '\0') {
          if (DAT_INTMEM_cc != '\0') {
            return;
          }
          uVar1 = 10;
        }
        else {
          FUN_CODE_a607(0xf);
          if (-1 < in_PSW) {
            FUN_CODE_a68c(1);
            if (-1 < in_PSW) {
              return;
            }
            if (DAT_INTMEM_cd != '2') {
              if (DAT_INTMEM_cd != '3') {
                return;
              }
              FUN_CODE_a23b(10);
            }
            FUN_CODE_a247(5);
            return;
          }
          if (DAT_EXTMEM_0af4 != '\0') {
            return;
          }
          if (DAT_EXTMEM_0af2 != '\0') {
            return;
          }
          uVar1 = 9;
        }
        FUN_CODE_a64d(uVar1);
      }
    }
  }
  return;
}

