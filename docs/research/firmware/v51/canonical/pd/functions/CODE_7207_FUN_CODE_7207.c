/* Address: CODE:7207; name: FUN_CODE_7207; body bytes: 102 */

void FUN_CODE_7207(void)

{
  char cVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_04c2 = '\0';
  DAT_EXTMEM_04c3 = '\x01';
  while (DAT_EXTMEM_05df != '\0') {
    if (DAT_EXTMEM_04c2 == '\0') {
      if (DAT_EXTMEM_05df != '\0') {
        if (DAT_EXTMEM_04c3 == '\0') {
          cVar1 = FUN_CODE_549d();
          if (cVar1 == -0x56) {
            DAT_EXTMEM_04c2 = '\x01';
            DAT_EXTMEM_05df = DAT_EXTMEM_05df + '\x01';
          }
        }
        DAT_EXTMEM_04c3 = '\0';
        uVar2 = FUN_CODE_549d();
        FUN_CODE_9137(uVar2);
        FUN_CODE_53f3(0x559);
        DAT_EXTMEM_05df = DAT_EXTMEM_05df + -1;
      }
    }
    else {
      FUN_CODE_9137(0xaa);
      DAT_EXTMEM_05df = DAT_EXTMEM_05df + -1;
      DAT_EXTMEM_04c2 = '\0';
    }
  }
  FUN_CODE_a7a4();
  FUN_CODE_8bc8(0);
  return;
}

