/* Address: CODE:6d78; name: FUN_CODE_6d78; body bytes: 109 */

void FUN_CODE_6d78(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  cVar2 = '\0';
  bVar1 = 2 - (((param_2 < 0xc0) << 7) >> 7);
  cVar4 = (param_1 < bVar1) << 7;
  cVar3 = param_1 - bVar1;
  if (cVar4 < '\0') {
    bVar1 = 2 - (((param_2 < 0x40) << 7) >> 7);
    cVar4 = (param_1 < bVar1) << 7;
    cVar3 = param_1 - bVar1;
    if (cVar4 < '\0') {
      bVar1 = 1 - (((param_2 < 0x53) << 7) >> 7);
      cVar4 = (param_1 < bVar1) << 7;
      cVar3 = param_1 - bVar1;
      if (param_1 >= bVar1) {
        cVar2 = '\x01';
      }
    }
    else {
      cVar2 = '\x02';
    }
  }
  else {
    cVar2 = '\x03';
  }
  FUN_CODE_a093(cVar3);
  FUN_CODE_ae2a(0x4b0);
  DAT_EXTMEM_04af = FUN_CODE_a934();
  FUN_CODE_7f77(3,BANK0_R4,BANK0_R2,BANK0_R1);
  if (-1 < cVar4) {
    return;
  }
  if (cVar2 != '\x02') {
    if (cVar2 != '\0') {
      return;
    }
    FUN_CODE_4528(0xc);
    cVar4 = FUN_CODE_a94d();
    if ((cVar4 == BANK0_R4) && (cVar4 = FUN_CODE_44d1(), cVar4 != '\x01')) {
      return;
    }
  }
  FUN_CODE_4528();
  FUN_CODE_a9ae(cVar2);
  FUN_CODE_a64d();
  return;
}

