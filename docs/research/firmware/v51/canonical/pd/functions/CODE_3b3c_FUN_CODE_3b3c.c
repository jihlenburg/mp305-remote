/* Address: CODE:3b3c; name: FUN_CODE_3b3c; body bytes: 241 */

void FUN_CODE_3b3c(byte param_1,byte param_2,byte param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  
  DAT_EXTMEM_04a4 = param_4;
  thunk_FUN_CODE_90f3();
  FUN_CODE_ae2a(0x4a5);
  FUN_CODE_a745(DAT_EXTMEM_04a4);
  FUN_CODE_82d6();
  FUN_CODE_aa99();
  bVar8 = (param_1 >> 5) << 7;
  if (param_1 >> 6 == 0) {
    FUN_CODE_aac4(2);
    bVar8 = param_1 >> 2;
    bVar2 = 0;
    bVar6 = FUN_CODE_aa99();
    bVar3 = 0;
    cVar1 = '\x06';
    bVar6 = bVar6 & 0xf;
    do {
      bVar7 = bVar6 << 1;
      bVar3 = bVar3 << 1 | bVar6 >> 7;
      cVar1 = cVar1 + -1;
      bVar6 = bVar7;
    } while (cVar1 != '\0');
    bVar3 = bVar3 | bVar2;
    bVar7 = bVar7 | bVar8;
    FUN_CODE_aed0(0,0x32);
    DAT_EXTMEM_04a8 = bVar3;
    DAT_EXTMEM_04a9 = bVar7;
    FUN_CODE_82d6();
    bVar8 = FUN_CODE_aac4(2);
    param_1 = param_1 & 3;
    FUN_CODE_aed0(0,10);
    DAT_EXTMEM_04aa = param_1;
    DAT_EXTMEM_04ab = bVar8;
    if (DAT_EXTMEM_04a4 == '\0') {
      thunk_FUN_CODE_a560();
      if (bVar8 >= 2) {
        bVar6 = DAT_EXTMEM_04aa << 7;
        DAT_EXTMEM_04aa = DAT_EXTMEM_04aa >> 1 | (bVar8 < 2) << 7;
        DAT_EXTMEM_04ab = DAT_EXTMEM_04ab >> 1 | bVar6;
      }
    }
    FUN_CODE_9d97(DAT_EXTMEM_04aa,DAT_EXTMEM_04ab,DAT_EXTMEM_04a8,DAT_EXTMEM_04a9);
    FUN_CODE_a646(2);
    FUN_CODE_54d6();
    FUN_CODE_82a1(0xa8,4);
    FUN_CODE_8faa();
    return;
  }
  FUN_CODE_82d6();
  FUN_CODE_ad03();
  uVar5 = 0;
  uVar4 = 0;
  bVar8 = bVar8 & 0xdd;
  FUN_CODE_acdd(0x11,param_2 & 1,param_3 & 0xfe);
  FUN_CODE_aba2(0,0,0,100);
  DAT_EXTMEM_04ac = uVar4;
  DAT_EXTMEM_04ad = uVar5;
  FUN_CODE_a153();
  if (-1 < (char)bVar8) {
                    /* WARNING: Subroutine does not return */
    FUN_CODE_adf3(0x4a5);
  }
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4a5);
}

