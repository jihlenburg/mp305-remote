/* Address: CODE:5f2c; name: FUN_CODE_5f2c; body bytes: 183 */

void FUN_CODE_5f2c(byte param_1,char param_2)

{
  undefined1 *puVar1;
  byte bVar2;
  char cVar3;
  
  FUN_CODE_a521();
  if ((param_2 == '\x03') && (*(char *)(DAT_INTMEM_b3 - 0x3b) == '\0')) {
    bVar2 = DAT_INTMEM_b3;
    FUN_CODE_109e();
    bVar2 = 0x11 - (((bVar2 < 0x95) << 7) >> 7);
    cVar3 = (param_1 < bVar2) << 7;
    if (param_1 >= bVar2) {
      FUN_CODE_a403(param_1 - bVar2);
      FUN_CODE_5062(0xad,4);
      FUN_CODE_8a3b();
      if (cVar3 < '\0') {
        DAT_EXTMEM_04d6 = DAT_EXTMEM_04ad;
        DAT_EXTMEM_04d7 = DAT_EXTMEM_04ae;
        DAT_EXTMEM_04d8 = DAT_EXTMEM_04af;
        DAT_EXTMEM_04d9 = DAT_EXTMEM_04b0;
        FUN_CODE_87aa(0x7b,0xb8,0xff);
        if (DAT_EXTMEM_0af4 != '\0') {
          FUN_CODE_a64d(0xf);
          return;
        }
      }
      else {
        FUN_CODE_87aa(0x97,0xb8,0xff);
        FUN_CODE_9ba3(0xb);
        bVar2 = DAT_INTMEM_b3;
        FUN_CODE_109e();
        DAT_EXTMEM_04af = 8;
        DAT_EXTMEM_04b0 = 0x98;
        puVar1 = &DAT_INTMEM_b2;
        DAT_EXTMEM_04ad = param_1;
        DAT_EXTMEM_04ae = bVar2;
        FUN_CODE_5064(0xad,4,1,4,1);
        FUN_CODE_8faa();
        _1_5 = 1;
        FUN_CODE_9cca();
        FUN_CODE_9241(1,0xf4);
        FUN_CODE_50a1();
        *puVar1 = 1;
        FUN_CODE_84ad();
        FUN_CODE_5092();
        FUN_CODE_666b();
      }
    }
  }
  return;
}

