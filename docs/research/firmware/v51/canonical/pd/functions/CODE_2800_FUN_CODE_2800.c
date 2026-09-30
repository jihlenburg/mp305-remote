/* Address: CODE:2800; name: FUN_CODE_2800; body bytes: 277 */

void FUN_CODE_2800(undefined1 param_1,undefined1 param_2,byte param_3,undefined1 param_4)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  char in_PSW;
  char cVar7;
  byte *pbVar8;
  undefined1 *puVar9;
  byte *pbVar10;
  
  DAT_EXTMEM_04a9 = 0;
  DAT_EXTMEM_04a5 = param_3;
  DAT_EXTMEM_04a6 = param_4;
  DAT_EXTMEM_04a7 = param_1;
  DAT_EXTMEM_04a8 = param_2;
  FUN_CODE_9d61();
  FUN_CODE_ae2a(0x4ab);
  DAT_EXTMEM_04aa = FUN_CODE_a934();
  pbVar8 = (byte *)0x4aa;
  FUN_CODE_a335();
  if (in_PSW < '\0') {
    FUN_CODE_44e9();
    bVar4 = (byte)((ushort)*pbVar8 * 4);
    bVar5 = (char)((ushort)*pbVar8 * 4 >> 8) - (((0xdb < bVar4) << 7) >> 7);
    cVar6 = (0x47 < bVar5) << 7;
    bVar3 = 4;
    FUN_CODE_448e(0xae,bVar4 + 0x24,bVar5 + 0xb8,0xff,1);
    cVar7 = DAT_EXTMEM_04ae;
    cVar2 = DAT_EXTMEM_04af;
    bVar5 = FUN_CODE_4503(0x4a5);
    bVar5 = cVar7 - (((bVar5 < (byte)(cVar2 - (cVar6 >> 7))) << 7) >> 7);
    cVar6 = (bVar3 < bVar5) << 7;
    if (bVar3 < bVar5) {
      DAT_EXTMEM_04a9 = DAT_EXTMEM_04a9 | 1;
    }
    else {
      FUN_CODE_44b1(bVar3 - bVar5);
      if (cVar6 < '\0') {
        DAT_EXTMEM_04a9 = DAT_EXTMEM_04a9 | 4;
      }
    }
    puVar9 = &DAT_EXTMEM_04a7;
    bVar5 = FUN_CODE_4503();
    bVar5 = cVar7 - (((bVar5 < (byte)(cVar2 - (cVar6 >> 7))) << 7) >> 7);
    cVar6 = (bVar3 < bVar5) << 7;
    if (bVar3 < bVar5) {
      bVar5 = puVar9[1] | 2;
      puVar9[1] = bVar5;
    }
    else {
      bVar5 = FUN_CODE_44b1(bVar3 - bVar5);
      if (cVar6 < '\0') {
        bVar5 = DAT_EXTMEM_04a9 | 8;
        DAT_EXTMEM_04a9 = bVar5;
      }
    }
  }
  else {
    bVar5 = FUN_CODE_4468();
    bVar3 = 1 - (((bVar5 < 0x62) << 7) >> 7);
    cVar6 = param_3 - bVar3;
    pbVar10 = pbVar8;
    if (param_3 >= bVar3) {
      pbVar10 = pbVar8 + 2;
      bVar3 = 1 - (((*pbVar10 < 0x61U - (((param_3 < bVar3) << 7) >> 7)) << 7) >> 7);
      cVar6 = pbVar8[1] - bVar3;
      if (pbVar8[1] < bVar3) {
        pbVar8 = pbVar8 + 3;
        *pbVar8 = 4;
        FUN_CODE_9719();
        bVar5 = bVar5 | 4;
        *pbVar8 = bVar5;
        goto LAB_CODE_290d;
      }
    }
    bVar5 = FUN_CODE_4468(cVar6);
    bVar5 = 1 - (((bVar5 < 0x61) << 7) >> 7);
    cVar6 = param_3 - bVar5;
    bVar1 = false;
    pbVar8 = pbVar10;
    if (param_3 < bVar5) {
      param_3 = pbVar10[1];
      pbVar8 = pbVar10 + 2;
      bVar5 = *pbVar8;
      bVar3 = 1 - (((bVar5 < 0x62) << 7) >> 7);
      bVar1 = param_3 < bVar3;
      cVar6 = param_3 - bVar3;
      if (!bVar1) {
        pbVar10 = pbVar10 + 3;
        *pbVar10 = 8;
        FUN_CODE_9719();
        bVar5 = bVar5 | 8;
        *pbVar10 = bVar5;
        goto LAB_CODE_290d;
      }
    }
    cVar7 = bVar1 << 7;
    bVar3 = FUN_CODE_4468(cVar6);
    bVar5 = FUN_CODE_451a();
    if (cVar7 < '\0') {
      bVar3 = 1 - (((bVar3 < 0x61U - (cVar7 >> 7)) << 7) >> 7);
      bVar5 = param_3 - bVar3;
      if (param_3 >= bVar3) {
        bVar4 = pbVar8[1];
        bVar3 = 0xf - (((pbVar8[2] < 0x2cU - (((param_3 < bVar3) << 7) >> 7)) << 7) >> 7);
        bVar5 = bVar4 - bVar3;
        if ((bVar4 < bVar3) &&
           (bVar3 = 1 - (((pbVar8[2] < 0x62) << 7) >> 7), bVar5 = bVar4 - bVar3, bVar3 <= bVar4)) {
          pbVar8[3] = 0xc;
          bVar5 = FUN_CODE_4468();
          FUN_CODE_9719();
          bVar5 = bVar5 | 0xc;
          DAT_EXTMEM_04a9 = bVar5;
        }
      }
    }
  }
LAB_CODE_290d:
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(bVar5,0x4ab,5);
}

