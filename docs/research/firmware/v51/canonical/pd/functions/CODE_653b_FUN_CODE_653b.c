/* Address: CODE:653b; name: FUN_CODE_653b; body bytes: 152 */

void FUN_CODE_653b(void)

{
  byte bVar1;
  
  FUN_CODE_7d83(0x4aa);
  FUN_CODE_87aa(0xc5,0xb4);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 0x2e;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 0xd;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 0x13;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 0xc;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0x1c;
            }
            if (bVar1 != 0) {
              FUN_CODE_7d6d(0x4aa,0x40,0xb4,0xff);
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

