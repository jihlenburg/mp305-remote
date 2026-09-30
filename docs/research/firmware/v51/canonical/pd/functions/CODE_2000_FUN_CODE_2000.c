/* Address: CODE:2000; name: FUN_CODE_2000; body bytes: 152 */

char FUN_CODE_2000(byte param_1,char param_2)

{
  char cVar1;
  char in_PSW;
  
  FUN_CODE_a3ae();
  if (in_PSW < '\0') {
    thunk_FUN_CODE_9bcb();
  }
  else {
    thunk_FUN_CODE_a00f();
  }
  DAT_EXTMEM_04c1 = param_2;
  FUN_CODE_974d(0);
  FUN_CODE_ae2a(0x4ab);
  DAT_EXTMEM_04c0 = FUN_CODE_471f();
  FUN_CODE_ad03();
  cVar1 = FUN_CODE_accc(0,0,0,0,0,param_1 & 0x40,0,0);
  if (cVar1 != '\0') {
    FUN_CODE_9a23(0,8);
  }
  DAT_EXTMEM_04c3 = 0;
  DAT_EXTMEM_04c4 = DAT_EXTMEM_04c1;
  DAT_EXTMEM_04c5 = 0;
  DAT_EXTMEM_04c6 = DAT_EXTMEM_04c0;
  FUN_CODE_476c(0x4d6,8,0xb6,0xff);
  FUN_CODE_87aa();
  if (DAT_EXTMEM_04c0 == 0) {
    cVar1 = '\0';
  }
  else {
    cVar1 = DAT_EXTMEM_04c0 - (DAT_EXTMEM_04c1 + 1U);
    if ((DAT_EXTMEM_04c0 < DAT_EXTMEM_04c1 + 1U) << 7 < '\0') {
      FUN_CODE_9f09(DAT_EXTMEM_04c0 - 1);
      FUN_CODE_ae2a(0x4a8);
                    /* WARNING: Subroutine does not return */
      FUN_CODE_adf3(0x4a8);
    }
  }
  return cVar1;
}

