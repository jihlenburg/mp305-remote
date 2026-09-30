/* Address: CODE:236b; name: FUN_CODE_236b; body bytes: 457 */

char FUN_CODE_236b(byte param_1)

{
  char cVar1;
  
  FUN_CODE_a5bd();
  BANK2_R6 = param_1;
  if ((0x30 < param_1) && (param_1 < 0x57)) {
    BANK2_R6 = 0;
  }
  BANK2_R7 = param_1;
  if (DAT_INTMEM_b2 == '\x03') {
    if (DAT_INTMEM_b4 == '\x04') {
      BANK2_R7 = 0x10;
    }
    else if (DAT_INTMEM_b4 == '\x1b') {
      BANK2_R7 = 0xe;
    }
    else {
      if (DAT_INTMEM_b4 != '\x0f') goto code_c0x2025;
      if ((BANK2_R6 != 2) && (BANK2_R6 != 6)) {
        if (BANK2_R6 == 0x12) {
          BANK2_R6 = 0;
          BANK2_R7 = 0x10;
        }
        else {
          BANK2_R6 = 0;
          BANK2_R7 = 0x12;
        }
      }
    }
  }
  else {
    cVar1 = (0xe < DAT_INTMEM_b2 - 3U) << 7;
    if (DAT_INTMEM_b2 == '\x12') {
      FUN_CODE_a739();
      cVar1 = param_1 - 0xd;
      if (0xc < param_1) {
        param_1 = 0x3a;
        FUN_CODE_a05a(cVar1);
      }
      if (DAT_INTMEM_b4 == '\r') {
        BANK2_R6 = 0;
        BANK2_R7 = 0x18;
      }
      else if (DAT_INTMEM_b4 == -0x80) {
        if (BANK2_R6 != 0x13) {
          BANK2_R7 = 0x11;
        }
      }
      else {
        cVar1 = (0x80 < DAT_INTMEM_b4 + 0x80U) << 7;
        if (DAT_INTMEM_b4 == '\x01') {
          FUN_CODE_a775();
          FUN_CODE_a727();
          if (param_1 != 2) goto LAB_CODE_25ca;
          FUN_CODE_7def();
        }
        else {
          FUN_CODE_9df1();
          if (-1 < cVar1) goto code_c0x2025;
          FUN_CODE_a17a();
        }
        if (cVar1 < '\0') goto code_c0x2025;
      }
    }
    else {
      FUN_CODE_a60e(8);
      if (((-1 < cVar1) || (BANK2_R6 == 0x1d)) || (BANK2_R6 == 0x1f)) {
code_c0x2025:
        FUN_CODE_ae53(BANK2_R6);
        nop();
        cVar1 = FUN_CODE_accc(0,0,0,0,0,BANK0_R3 & 0x40,0,0);
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
      if (BANK2_R6 != 0x13) {
        BANK2_R7 = 1;
        FUN_CODE_90d1(0xff,0xff);
      }
    }
  }
LAB_CODE_25ca:
  cVar1 = FUN_CODE_10b6(BANK2_R7,BANK2_R6);
  return cVar1;
}

