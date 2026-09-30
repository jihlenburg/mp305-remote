/* Address: CODE:104b; name: thunk_FUN_CODE_5c3c; body bytes: 3 */

undefined1 thunk_FUN_CODE_5c3c(undefined1 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  byte *pbVar12;
  
  uVar11 = BANK0_R7;
  uVar10 = BANK0_R6;
  uVar9 = BANK0_R5;
  uVar8 = BANK0_R4;
  uVar7 = BANK0_R3;
  uVar6 = BANK0_R2;
  uVar5 = BANK0_R1;
  uVar4 = BANK0_R0;
  DAT_INTMEM_b9 = DAT_EXTMEM_0721;
  cVar3 = FIFLG_7;
  if (cVar3 != '\0') {
    if (DAT_INTMEM_d0 == '\x04') {
      if (DAT_INTMEM_ce == DAT_INTMEM_d1) {
        DAT_INTMEM_d0 = '\0';
      }
      else {
        FUN_CODE_770c();
        pbVar12 = (byte *)&DAT_INTMEM_ce;
        FUN_CODE_76ec(DAT_INTMEM_ce);
        *pbVar12 = *pbVar12 + 1;
        if (0xef < *pbVar12) {
          *pbVar12 = 0;
        }
      }
    }
    FIFLG_7 = 0;
  }
  cVar3 = FIFLG_6;
  if (cVar3 != '\0') {
    FIFLG_6 = 0;
  }
  cVar3 = FIFLG_5;
  if (cVar3 != '\0') {
    if (DAT_INTMEM_cf == '\x01') {
      DAT_INTMEM_d2 = 0;
      DAT_INTMEM_cf = '\x02';
    }
    if (DAT_INTMEM_cf == '\x02') {
      bVar1 = HPSTAT;
      HPSTAT = bVar1 | 0x10;
      uVar2 = EPCONFIG;
      FUN_CODE_66fd(uVar2);
    }
    else {
      DAT_INTMEM_ba = EPCONFIG;
    }
  }
  bVar1 = HPSTAT;
  if ((bVar1 >> 3 & 1) != 0) {
    DAT_INTMEM_d2 = 0;
    DAT_INTMEM_cf = '\x01';
    bVar1 = HPSTAT;
    HPSTAT = bVar1 & 0xe7;
  }
  bVar1 = FIFLG;
  if ((bVar1 & 5) != 0) {
    FUN_CODE_9b66();
  }
  DAT_SFR_c3 = 0xfb;
  BANK0_R7 = uVar11;
  BANK0_R6 = uVar10;
  BANK0_R5 = uVar9;
  BANK0_R4 = uVar8;
  BANK0_R3 = uVar7;
  BANK0_R2 = uVar6;
  BANK0_R1 = uVar5;
  BANK0_R0 = uVar4;
  return param_1;
}

