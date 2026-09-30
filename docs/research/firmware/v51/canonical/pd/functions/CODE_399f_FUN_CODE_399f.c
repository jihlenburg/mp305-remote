/* Address: CODE:399f; name: FUN_CODE_399f; body bytes: 313 */

char * FUN_CODE_399f(char *param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
                    byte param_7)

{
  bool bVar1;
  byte *pbVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  char *pcVar8;
  char *pcVar9;
  char cVar10;
  
  FUN_CODE_a5bd();
  BANK2_R6 = param_7;
  if (param_7 < 0x31) {
    BANK2_R6 = 0;
  }
  BANK2_R7 = param_7;
  if (DAT_INTMEM_b2 == '\x03') {
    if (DAT_INTMEM_b4 == '\x04') {
      BANK2_R7 = 0x38;
LAB_CODE_3b32:
      pcVar9 = (char *)FUN_CODE_10b6(BANK2_R7,BANK2_R6);
      return pcVar9;
    }
    cVar10 = (10 < DAT_INTMEM_b4 - 4U) << 7;
    if (DAT_INTMEM_b4 == '\x0f') {
      if (BANK2_R6 == 0x3c) {
        FUN_CODE_a03c(0x2c);
      }
      else {
        BANK2_R7 = 0x3c;
      }
      goto LAB_CODE_3b32;
    }
  }
  else {
    cVar10 = (0xe < DAT_INTMEM_b2 - 3U) << 7;
    if (DAT_INTMEM_b2 == '\x12') {
      if (DAT_INTMEM_b4 == '\r') {
        BANK2_R7 = 0x3d;
        goto LAB_CODE_3b32;
      }
      if (DAT_INTMEM_b4 == -0x80) {
        FUN_CODE_9a23(0,2);
        BANK2_R7 = 0x39;
        goto LAB_CODE_3b32;
      }
      cVar10 = (0x80 < DAT_INTMEM_b4 + 0x80U) << 7;
      if (DAT_INTMEM_b4 == '\x01') {
        FUN_CODE_a775();
        FUN_CODE_a727();
        if (param_7 != 2) goto LAB_CODE_3b32;
      }
      else {
        FUN_CODE_9df1();
        if ((cVar10 < '\0') && (FUN_CODE_a17a(), -1 < cVar10)) goto LAB_CODE_3b32;
      }
    }
    else {
      FUN_CODE_a60e(8);
      if (cVar10 < '\0') {
        BANK2_R7 = 0x31;
        FUN_CODE_90d1(0xff,0xff);
        goto LAB_CODE_3b32;
      }
      param_7 = 0x26;
      FUN_CODE_a607();
      if (cVar10 < '\0') {
        FUN_CODE_a17a();
      }
    }
  }
  pbVar2 = &BANK2_R6;
  cVar3 = FUN_CODE_ae53(BANK2_R6);
  bVar4 = cVar3 + (param_2 - (cVar10 >> 7));
  if (*pbVar2 == 0) {
    bVar1 = param_5 < 0x31;
    if (param_5 == 0x31) {
      _6_2 = 0;
      cVar10 = *param_1;
      *param_1 = bVar4 + param_2;
      bVar5 = cVar10 << 1 | CARRY1(bVar4,param_2);
      bVar4 = param_2 - (cVar10 >> 7);
      cVar10 = CARRY1(param_4,0x3a - ((CARRY1(bVar5,bVar4) << 7) >> 7)) << 7;
      bVar5 = func_0x3e35(bVar5 + bVar4);
      bVar4 = param_2 - (cVar10 >> 7);
      bVar6 = bVar5 + bVar4;
      bVar7 = bVar6 & 0xf0 | *pbVar2 & 0xf;
      *pbVar2 = *pbVar2 & 0xf0 | bVar6 & 0xf;
      bVar4 = *pbVar2 - ((CARRY1(bVar5,bVar4) << 7) >> 7);
      bVar5 = bVar7 + bVar4;
      bVar4 = param_2 - ((CARRY1(bVar7,bVar4) << 7) >> 7);
      cVar10 = CARRY1(bVar5,bVar4) << 7;
      bVar5 = bVar5 + bVar4;
      if (param_7 == 1) {
        bVar4 = param_2 - (cVar10 >> 7);
        cVar10 = CARRY1(bVar5 + bVar4,param_2 - ((CARRY1(bVar5,bVar4) << 7) >> 7)) << 7;
        cVar3 = func_0x3d39(uINTMEM38);
        bVar4 = cVar3 + (param_3 - (cVar10 >> 7));
        pcVar9 = param_1 + bVar4;
        bVar4 = param_2 - ((CARRY1(bVar4,(byte)param_1) << 7) >> 7);
        pcVar8 = pcVar9 + bVar4;
        bVar4 = param_2 - ((CARRY1((byte)pcVar9,bVar4) << 7) >> 7);
        *param_1 = cINTMEM3c;
        bVar5 = param_2 - ((_7_5 << 7) >> 7);
        pcVar9 = pcVar8 + (param_2 - ((CARRY1((byte)pcVar8,bVar4) << 7) >> 7)) + bVar4 + bVar5;
        param_6 = param_6 - ((CARRY1((byte)(pcVar8 + (param_2 -
                                                     ((CARRY1((byte)pcVar8,bVar4) << 7) >> 7)) +
                                                     bVar4),bVar5) << 7) >> 7);
        if (pcVar9 + (param_3 - ((CARRY1((byte)pcVar9,param_6) << 7) >> 7)) + param_6 == (char *)0x0
           ) {
          pcVar9 = (char *)FUN_CODE_984b(pcVar9);
        }
        else {
          pcVar9 = pcVar9 + (param_3 - ((CARRY1((byte)pcVar9,param_6) << 7) >> 7)) + param_6 +
                   '\x16';
          if (pcVar9 == (char *)0x0) {
            return (char *)0x0;
          }
        }
        return pcVar9;
      }
      goto code_c0x3a8d;
    }
  }
  else {
    bVar1 = CARRY1(bVar4 & (byte)pbVar2,param_2);
    bVar4 = (bVar4 & (byte)pbVar2) + param_2;
    *(byte *)ZEXT12(param_1) = bVar4;
  }
  bVar5 = param_2 - ((bVar1 << 7) >> 7);
  bVar4 = param_3 - ((CARRY1((byte)param_1 ^ param_2,
                             param_2 - ((CARRY1((bVar4 & (byte)param_1) + bVar5 & param_3,
                                                param_2 - ((CARRY1(bVar4 & (byte)param_1,bVar5) << 7
                                                           ) >> 7)) << 7) >> 7)) << 7) >> 7);
  bVar5 = (param_6 ^ param_3) + bVar4;
  cINTMEM7a = cINTMEM7a + -1;
  bVar4 = param_3 - ((CARRY1(param_6 ^ param_3,bVar4) << 7) >> 7);
  cVar10 = CARRY1(bVar5,bVar4) << 7;
  bVar5 = bVar5 + bVar4;
code_c0x3a8d:
  cINTMEM7b = cINTMEM7b + -1;
  bVar4 = param_3 - (cVar10 >> 7);
  bVar6 = bVar5 + bVar4;
  cINTMEM7d = cINTMEM7d + -1;
  bVar4 = param_3 - ((CARRY1(bVar5,bVar4) << 7) >> 7);
  bVar5 = bVar6 + bVar4;
  cINTMEM7e = cINTMEM7e + -1;
  bVar4 = param_3 - ((CARRY1(bVar6,bVar4) << 7) >> 7);
  bVar6 = bVar5 + bVar4;
  cVar10 = P0;
  P0 = cVar10 + -1;
  bVar4 = param_3 - ((CARRY1(bVar5,bVar4) << 7) >> 7);
  bVar5 = bVar6 + bVar4;
  bVar4 = param_3 - ((CARRY1(bVar6,bVar4) << 7) >> 7);
  cVar10 = DPXL;
  DPXL = cVar10 + -1;
  nop();
  nop();
  return (char *)(bVar5 + bVar4 + (param_3 - ((CARRY1(bVar5,bVar4) << 7) >> 7)));
}

