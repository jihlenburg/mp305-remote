/* Address: CODE:71a0; name: FUN_CODE_71a0; body bytes: 103 */

void FUN_CODE_71a0(byte param_1,byte param_2)

{
  char cVar1;
  
  if (param_1 == param_2) {
    DAT_EXTMEM_04a8 = param_1;
    return;
  }
  cVar1 = (9 < param_1) << 7;
  DAT_EXTMEM_04a8 = param_1;
  if (param_1 == 10) {
    FUN_CODE_9023(1);
    FUN_CODE_a0cb(0);
    FUN_CODE_a247(5);
  }
  else {
    if (param_1 == 0xb) {
      FUN_CODE_a22f();
      FUN_CODE_9ba3(3);
      FUN_CODE_a607(10);
      if (cVar1 < '\0') {
        DAT_EXTMEM_04a8 = 0xc;
        FUN_CODE_a63f(0x20);
        FUN_CODE_9023(2);
      }
      goto LAB_CODE_71fe;
    }
    if (param_1 != 9) goto LAB_CODE_71fe;
    if (DAT_INTMEM_cc != '\t') {
      FUN_CODE_9ba3(0);
    }
    FUN_CODE_a485();
    FUN_CODE_a22f();
    FUN_CODE_a3cf();
  }
  FUN_CODE_a16d();
LAB_CODE_71fe:
  FUN_CODE_a0bd(DAT_EXTMEM_04a8);
  return;
}

