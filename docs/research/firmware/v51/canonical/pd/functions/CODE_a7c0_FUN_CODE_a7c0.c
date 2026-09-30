/* Address: CODE:a7c0; name: FUN_CODE_a7c0; body bytes: 3 */

void FUN_CODE_a7c0(void)

{
  char in_PSW;
  
  _2_0 = 0;
  FIE1 = 0x5a;
  DAT_SFR_85 = 0x10;
  FIE1 = 0;
  do {
    DAT_EXTMEM_04a1 = DAT_EXTMEM_0760;
    if (DAT_EXTMEM_0760 == '\x01') {
      DAT_EXTMEM_04a2 = 2;
    }
    else if (DAT_EXTMEM_0760 == '\x02') {
      FUN_CODE_a7b8();
      FUN_CODE_5db7();
      if (in_PSW < '\0') {
        FUN_CODE_9e99();
      }
      FUN_CODE_89b2();
    }
    else {
      in_PSW = (0xfd < DAT_EXTMEM_0760 - 2U) << 7;
      if (DAT_EXTMEM_0760 - 2U == 0xfe) {
        DAT_EXTMEM_04a2 = 1;
      }
    }
    FUN_CODE_843b(DAT_EXTMEM_04a2,DAT_EXTMEM_04a1);
    FUN_CODE_104e();
  } while( true );
}

