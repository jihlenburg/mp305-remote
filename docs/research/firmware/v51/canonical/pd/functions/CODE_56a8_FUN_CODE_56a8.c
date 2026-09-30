/* Address: CODE:56a8; name: FUN_CODE_56a8; body bytes: 218 */

void FUN_CODE_56a8(byte param_1,byte param_2,undefined1 param_3)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  undefined1 uVar8;
  undefined1 *puVar9;
  byte *pbVar10;
  
  puVar9 = &DAT_EXTMEM_04b0;
  DAT_EXTMEM_04af = param_3;
  DAT_EXTMEM_04b0 = param_2;
  FUN_CODE_506b();
  *puVar9 = 0;
  DAT_EXTMEM_04b3 = 0;
  DAT_EXTMEM_04b4 = 0;
  cVar3 = (param_2 == 0) << 7;
  if (param_2 != 0) {
    DAT_EXTMEM_04b5 = 0;
    while( true ) {
      cVar3 = (DAT_EXTMEM_04b5 < DAT_EXTMEM_04b0) << 7;
      if (DAT_EXTMEM_04b5 >= DAT_EXTMEM_04b0) break;
      FUN_CODE_5782(DAT_EXTMEM_04b5 - DAT_EXTMEM_04b0,DAT_EXTMEM_04b5);
      bVar7 = BANK0_R7;
      bVar6 = BANK0_R6;
      thunk_FUN_CODE_90f3(0,DAT_EXTMEM_04b5);
      bVar5 = FUN_CODE_aa99();
      bVar4 = 0;
      cVar3 = '\x06';
      bVar5 = bVar5 & 0xf;
      do {
        bVar2 = bVar5 << 1;
        bVar4 = bVar4 << 1 | bVar5 >> 7;
        cVar3 = cVar3 + -1;
        bVar5 = bVar2;
      } while (cVar3 != '\0');
      bVar6 = bVar6 | bVar4;
      bVar7 = bVar7 | bVar2;
      FUN_CODE_aed0(0,0x32);
      bVar1 = bVar6 < 0x23U - (((bVar7 < 0x29) << 7) >> 7);
      cVar3 = bVar1 << 7;
      DAT_EXTMEM_04b1 = bVar6;
      DAT_EXTMEM_04b2 = bVar7;
      if (!bVar1) break;
      uVar8 = FUN_CODE_5782(DAT_EXTMEM_04b5);
      FUN_CODE_aed0(0,10,param_1 & 3,uVar8);
      bVar6 = DAT_EXTMEM_04b1;
      bVar7 = DAT_EXTMEM_04b2;
      FUN_CODE_79d0(0x27,0x10,BANK0_R6,BANK0_R7);
      if (DAT_EXTMEM_04b3 < bVar6 - (((DAT_EXTMEM_04b4 < bVar7 + 1) << 7) >> 7)) {
        pbVar10 = &DAT_EXTMEM_04b5;
        bVar5 = DAT_EXTMEM_04b5;
        DAT_EXTMEM_04b3 = bVar6;
        DAT_EXTMEM_04b4 = bVar7;
        FUN_CODE_506b();
        *pbVar10 = bVar5;
      }
      DAT_EXTMEM_04b5 = DAT_EXTMEM_04b5 + 1;
    }
  }
  FUN_CODE_a1c3(DAT_EXTMEM_04b0,DAT_EXTMEM_04af);
  FUN_CODE_a153();
  if (-1 < cVar3) {
    FUN_CODE_4d85(DAT_INTMEM_b3);
  }
  return;
}

