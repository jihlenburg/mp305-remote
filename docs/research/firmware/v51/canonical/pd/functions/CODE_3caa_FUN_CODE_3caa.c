/* Address: CODE:3caa; name: FUN_CODE_3caa; body bytes: 363 */

void FUN_CODE_3caa(void)

{
  byte bVar1;
  byte in_PSW;
  
  DAT_EXTMEM_04a4 = 0;
  DAT_EXTMEM_04a5 = DAT_INTMEM_b2;
  DAT_EXTMEM_04a6 = 0;
  DAT_EXTMEM_04a7 = DAT_INTMEM_b4;
  FUN_CODE_a139(DAT_INTMEM_b3);
  DAT_EXTMEM_04a9 = in_PSW >> 7;
  DAT_EXTMEM_04a8 = 0;
  FUN_CODE_a6f7();
  bVar1 = DAT_EXTMEM_04a4;
  if (DAT_EXTMEM_04a4 == 0) {
    bVar1 = DAT_EXTMEM_04a5 ^ 0x10;
  }
  if ((bVar1 != 0) ||
     ((((DAT_EXTMEM_04a7 != 0x4e || DAT_EXTMEM_04a6 != 0 &&
        (DAT_EXTMEM_04a7 != 0x11 || DAT_EXTMEM_04a6 != 0)) &&
       (DAT_EXTMEM_04a7 != 0x12 || DAT_EXTMEM_04a6 != 0)) &&
      ((DAT_EXTMEM_04a7 != 0x3f || DAT_EXTMEM_04a6 != 0 &&
       (DAT_EXTMEM_04a7 != 0x49 || DAT_EXTMEM_04a6 != 0)))))) {
    FUN_CODE_7d72(0,0xb3,0xb5,0xff);
    FUN_CODE_87aa();
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 0x12;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_52ef();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 0x11;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_4800();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 5;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_653b();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 3;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_6162();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 2;
    }
    if (bVar1 == 0) {
      bVar1 = DAT_EXTMEM_04a6;
      if (DAT_EXTMEM_04a6 == 0) {
        bVar1 = DAT_EXTMEM_04a7 ^ 1;
      }
      if (bVar1 != 0) {
        FUN_CODE_7d6d(0x4a6,0xc3,0xb5,0xff);
      }
    }
    else {
      bVar1 = DAT_EXTMEM_04a4;
      if (DAT_EXTMEM_04a4 == 0) {
        bVar1 = DAT_EXTMEM_04a5 ^ 0x10;
      }
      if (bVar1 == 0) {
        FUN_CODE_7d7a();
        FUN_CODE_4e91();
        return;
      }
      bVar1 = DAT_EXTMEM_04a4;
      if (DAT_EXTMEM_04a4 == 0) {
        bVar1 = DAT_EXTMEM_04a5 ^ 1;
      }
      if (bVar1 == 0) {
        FUN_CODE_7d6d(0x4a6,0xc9,0xb5,0xff);
        FUN_CODE_7d9f(0x4a8);
      }
      else {
        bVar1 = DAT_EXTMEM_04a4;
        if (DAT_EXTMEM_04a4 == 0) {
          bVar1 = DAT_EXTMEM_04a5 ^ 4;
        }
        if (bVar1 == 0) {
          bVar1 = DAT_EXTMEM_04a6;
          if (DAT_EXTMEM_04a6 == 0) {
            bVar1 = DAT_EXTMEM_04a7 ^ 3;
          }
          if (bVar1 != 0) {
            FUN_CODE_7d6d(0x4a6,0xe5,0xb5,0xff);
          }
        }
        else {
          if (DAT_EXTMEM_04a5 == 8 && DAT_EXTMEM_04a4 == 0) {
            return;
          }
          DAT_EXTMEM_04d6 = DAT_EXTMEM_04a4;
          DAT_EXTMEM_04d7 = DAT_EXTMEM_04a5;
          FUN_CODE_7d9f(0x4a6,0xed,0xb5,0xff);
        }
      }
    }
    FUN_CODE_87aa();
  }
  return;
}

