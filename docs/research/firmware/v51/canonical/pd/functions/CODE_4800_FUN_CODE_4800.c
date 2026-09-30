/* Address: CODE:4800; name: FUN_CODE_4800; body bytes: 288 */

void FUN_CODE_4800(byte param_1,byte param_2)

{
  byte bVar1;
  
  DAT_EXTMEM_04aa = param_1;
  DAT_EXTMEM_04ab = param_2;
  FUN_CODE_96ff();
  FUN_CODE_7d83(0x4ac);
  FUN_CODE_87aa(0x45,0xb4);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 1;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 3;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 4;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 0x10;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0xd;
            }
            if (bVar1 != 0) {
              bVar1 = DAT_EXTMEM_04aa;
              if (DAT_EXTMEM_04aa == 0) {
                bVar1 = DAT_EXTMEM_04ab ^ 0xc;
              }
              if (bVar1 != 0) {
                bVar1 = DAT_EXTMEM_04aa;
                if (DAT_EXTMEM_04aa == 0) {
                  bVar1 = DAT_EXTMEM_04ab ^ 5;
                }
                if (bVar1 != 0) {
                  bVar1 = DAT_EXTMEM_04aa;
                  if (DAT_EXTMEM_04aa == 0) {
                    bVar1 = DAT_EXTMEM_04ab ^ 6;
                  }
                  if (bVar1 != 0) {
                    bVar1 = DAT_EXTMEM_04aa;
                    if (DAT_EXTMEM_04aa == 0) {
                      bVar1 = DAT_EXTMEM_04ab ^ 8;
                    }
                    if (bVar1 != 0) {
                      bVar1 = DAT_EXTMEM_04aa;
                      if (DAT_EXTMEM_04aa == 0) {
                        bVar1 = DAT_EXTMEM_04ab ^ 10;
                      }
                      if (bVar1 != 0) {
                        bVar1 = DAT_EXTMEM_04aa;
                        if (DAT_EXTMEM_04aa == 0) {
                          bVar1 = DAT_EXTMEM_04ab ^ 9;
                        }
                        if (bVar1 != 0) {
                          FUN_CODE_7d69(0x4aa,0xff);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_CODE_87aa();
  FUN_CODE_7d6d(0x4ac,0xbe,0xb4,0xff);
  FUN_CODE_87aa();
  return;
}

