/* Address: CODE:4f9c; name: FUN_CODE_4f9c; body bytes: 98 */

void FUN_CODE_4f9c(byte *param_1)

{
  byte bVar1;
  char in_PSW;
  char cVar2;
  
  FUN_CODE_9b12();
  if (in_PSW < '\0') {
    FUN_CODE_8a68();
    FUN_CODE_88c5();
  }
  bVar1 = DAT_INTMEM_b3;
  FUN_CODE_97db();
  cVar2 = (*param_1 == 0) << 7;
  if (cVar2 < '\0') {
    FUN_CODE_7a1a(*param_1 - 1);
  }
  else {
    cVar2 = (0xd4 < bVar1) << 7;
    FUN_CODE_97dd();
    *param_1 = *param_1 - 1;
  }
  if ((DAT_INTMEM_cc != '\t') && (DAT_INTMEM_cc != '\v')) {
    FUN_CODE_a139(DAT_INTMEM_b3);
    if (cVar2 < '\0') {
      FUN_CODE_97cc();
      bVar1 = 0x80 - (((param_1[1] < 0xc9) << 7) >> 7);
      if (bVar1 <= (*param_1 ^ 0x80)) {
        FUN_CODE_7712();
        return;
      }
      FUN_CODE_97cc((*param_1 ^ 0x80) - bVar1);
      FUN_CODE_aa6d(0,1);
      return;
    }
  }
  FUN_CODE_97cc();
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

