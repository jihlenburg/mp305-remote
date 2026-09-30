/* Address: CODE:6162; name: FUN_CODE_6162; body bytes: 172 */

void FUN_CODE_6162(void)

{
  byte bVar1;
  
  FUN_CODE_7d83(0x4aa);
  FUN_CODE_87aa(0xff,0xb4);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 0xe;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 0xf;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 0x13;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 10;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0x1a;
            }
            if (bVar1 != 0) {
              bVar1 = DAT_EXTMEM_04aa;
              if (DAT_EXTMEM_04aa == 0) {
                bVar1 = DAT_EXTMEM_04ab ^ 6;
              }
              if (bVar1 != 0) {
                FUN_CODE_7d6d(0x4aa,0x40,0xb4,0xff);
              }
            }
          }
        }
      }
    }
  }
  FUN_CODE_87aa();
  FUN_CODE_7d98();
  FUN_CODE_87aa();
  return;
}

