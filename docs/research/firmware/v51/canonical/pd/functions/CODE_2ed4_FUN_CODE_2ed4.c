/* Address: CODE:2ed4; name: FUN_CODE_2ed4; body bytes: 236 */

byte FUN_CODE_2ed4(short param_1)

{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char *pcVar6;
  undefined1 *puVar7;
  byte *pbVar8;
  
  bVar3 = DAT_INTMEM_ab - 0x12;
  if (bVar3 == 0) {
    cVar2 = DAT_INTMEM_ad;
    FUN_CODE_621e();
    pcVar6 = (char *)(param_1 + 2);
    *pcVar6 = cVar2;
    bVar3 = 0;
    bVar4 = DAT_INTMEM_b0 >> 3 & 0xf;
    if (bVar4 == 0) {
      FUN_CODE_6276();
      pcVar6 = pcVar6 + 2;
      FUN_CODE_6248();
      *pcVar6 = '\0';
      pcVar6[1] = '\0';
    }
    else {
      FUN_CODE_6266();
      bVar5 = pcVar6[1] ^ bVar4;
      if ((pcVar6[1] ^ bVar4) == 0) {
        bVar5 = bVar3;
      }
      if (bVar5 != 0) {
        return bVar5;
      }
    }
    DAT_EXTMEM_04a6 = (DAT_INTMEM_ae >> 4 & 7) * '\x04' + -2;
    FUN_CODE_9800(DAT_INTMEM_ae);
    if (DAT_INTMEM_ad == 'Q') {
      thunk_FUN_CODE_90f3(0);
      puVar7 = &DAT_EXTMEM_04a7;
      FUN_CODE_ae2a();
      FUN_CODE_620e();
      DAT_EXTMEM_04aa = *puVar7;
      DAT_EXTMEM_04ab = puVar7[1];
      DAT_EXTMEM_04ae = 0;
      if (DAT_EXTMEM_04a6 != '\0') {
        DAT_EXTMEM_04ac = DAT_EXTMEM_04aa;
        DAT_EXTMEM_04ad = DAT_EXTMEM_04ab;
        FUN_CODE_990c(DAT_EXTMEM_04aa,2);
                    /* WARNING: Subroutine does not return */
        FUN_CODE_adf3(0x4a7);
      }
    }
    uVar1 = DAT_EXTMEM_0753;
    pcVar6 = (char *)(CONCAT11(DAT_EXTMEM_0752,DAT_EXTMEM_0753) + 3);
    *pcVar6 = *pcVar6 + '\x01';
    pbVar8 = (byte *)0x4a6;
    cVar2 = DAT_EXTMEM_04a6;
    FUN_CODE_6215(uVar1,DAT_EXTMEM_04a6);
    FUN_CODE_aa6d(0,cVar2);
    FUN_CODE_620e();
    bVar4 = (DAT_INTMEM_b0 & 1) - (((pbVar8[1] < DAT_INTMEM_b1) << 7) >> 7);
    bVar3 = *pbVar8 - bVar4;
    if (bVar4 <= *pbVar8) {
      return bVar3;
    }
  }
  return bVar3;
}

