/* Address: CODE:4532; name: FUN_CODE_4532; body bytes: 297 */

void FUN_CODE_4532(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  
  FUN_CODE_ae2a(0x515);
  DAT_EXTMEM_0535 = 0;
  DAT_EXTMEM_0536 = '\0';
  DAT_EXTMEM_0537 = 0;
  DAT_EXTMEM_0538 = 0;
  DAT_EXTMEM_0518 = param_1;
  DAT_EXTMEM_0519 = param_2;
  DAT_EXTMEM_0539 = param_1;
  if (param_2 == 0 && param_1 == 0) {
    DAT_EXTMEM_0524 = 0x30;
    DAT_EXTMEM_0525 = 0;
    DAT_EXTMEM_053a = param_2;
    FUN_CODE_5410(0x24,5,1);
    FUN_CODE_54d0();
    FUN_CODE_55c0();
    return;
  }
  cVar2 = DAT_EXTMEM_051c;
  if (DAT_EXTMEM_051c == '\0') {
    cVar2 = DAT_EXTMEM_051d;
  }
  bVar1 = 0;
  DAT_EXTMEM_053a = param_2;
  if (cVar2 != '\0') {
    bVar1 = DAT_EXTMEM_051a;
    if (DAT_EXTMEM_051a == 0) {
      bVar1 = DAT_EXTMEM_051b ^ 10;
    }
    DAT_EXTMEM_053a = param_2;
    if (bVar1 == 0) {
      bVar1 = (param_1 ^ 0x80) + 0x80;
      DAT_EXTMEM_053a = param_2;
      if ((param_1 ^ 0x80) < 0x80) {
        DAT_EXTMEM_0536 = '\x01';
        bVar1 = -param_2;
        DAT_EXTMEM_0539 = -(param_1 - (((param_2 != 0) << 7) >> 7));
        DAT_EXTMEM_053a = bVar1;
      }
    }
  }
  DAT_EXTMEM_0535 = '\0';
  FUN_CODE_ae2a(bVar1,0x530,0x2f,5,1);
  FUN_CODE_a99c(0);
  while (DAT_EXTMEM_053a != 0 || DAT_EXTMEM_0539 != 0) {
    FUN_CODE_54aa();
    DAT_EXTMEM_0533 = param_1;
    DAT_EXTMEM_0534 = param_2;
    if (0x80U - (((param_2 < 10) << 7) >> 7) <= (param_1 ^ 0x80)) {
      FUN_CODE_aa6d(0x533,DAT_EXTMEM_0523 + -0x3a);
    }
    cVar2 = DAT_EXTMEM_0534 + 0x30;
    FUN_CODE_54b5(cVar2);
    FUN_CODE_a99c(cVar2);
    FUN_CODE_54aa();
  }
  cVar2 = DAT_EXTMEM_0535;
  if (DAT_EXTMEM_0535 == '\0') {
    cVar2 = DAT_EXTMEM_0536;
  }
  if (cVar2 != '\0') {
    cVar2 = DAT_EXTMEM_051e;
    if (DAT_EXTMEM_051e == '\0') {
      cVar2 = DAT_EXTMEM_051f;
    }
    if ((cVar2 == '\0') || ((DAT_EXTMEM_0521 >> 1 & 1) == 0)) {
      FUN_CODE_54b5(DAT_EXTMEM_053a);
      FUN_CODE_a99c(0x2d);
    }
    else {
      FUN_CODE_54d0();
      FUN_CODE_8b47(0,0x2d);
      FUN_CODE_53f3(0x537);
      FUN_CODE_5484(0x51e);
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x530);
}

