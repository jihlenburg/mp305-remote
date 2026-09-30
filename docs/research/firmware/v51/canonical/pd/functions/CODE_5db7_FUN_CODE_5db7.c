/* Address: CODE:5db7; name: FUN_CODE_5db7; body bytes: 188 */

void FUN_CODE_5db7(byte param_1,undefined1 param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  char cVar6;
  short sVar7;
  byte *pbVar8;
  byte *pbVar9;
  
  bVar4 = T2MOD;
  T2MOD = bVar4 & 0xfb;
  if (BANK2_R5 == '\0') {
    bVar4 = T2MOD;
    T2MOD = bVar4 | 4;
    return;
  }
  DAT_EXTMEM_04a5 = '\0';
  DAT_EXTMEM_04a6 = BANK2_R5;
  BANK2_R5 = 0;
  bVar4 = T2MOD;
  T2MOD = bVar4 | 4;
  if (BANK1_R2 != '\0') {
    for (BANK2_R6 = 0; BANK2_R6 < 0xc; BANK2_R6 = BANK2_R6 + 1) {
      bVar4 = BANK2_R6;
      uVar5 = FUN_CODE_8b2b(BANK2_R6 - 0xc);
      DAT_EXTMEM_04a3 = uVar5;
      DAT_EXTMEM_04a4 = bVar4;
      if (*(char *)CONCAT11(param_2,bVar4) != '\0') {
        pbVar8 = (byte *)CONCAT11(4,bVar4 + 5);
        FUN_CODE_8b1b(bVar4);
        param_2 = uVar5;
        if (*pbVar8 == param_1) {
          sVar7 = 0x4a3;
          FUN_CODE_8b40();
          bVar4 = *(byte *)(sVar7 + 3);
          param_1 = *(byte *)(sVar7 + 4);
          pbVar8 = (byte *)0x4a6;
          bVar1 = DAT_EXTMEM_04a5 - (((param_1 < DAT_EXTMEM_04a6 + 1U) << 7) >> 7);
          cVar6 = (bVar4 < bVar1) << 7;
          if (bVar4 >= bVar1) {
            cVar2 = DAT_EXTMEM_04a5;
            cVar3 = DAT_EXTMEM_04a6;
            FUN_CODE_8b24();
            pbVar9 = pbVar8 + 2;
            bVar4 = cVar3 - (cVar6 >> 7);
            cVar6 = (char)((ushort)pbVar9 >> 8);
            if ((char)pbVar9 == '\0') {
              cVar6 = cVar6 + -1;
            }
            pbVar8[1] = *(char *)CONCAT11(cVar6,(char)pbVar9 + -1) -
                        (cVar2 - (((*pbVar9 < bVar4) << 7) >> 7));
            pbVar8[2] = *pbVar9 - bVar4;
            param_2 = uVar5;
            goto LAB_CODE_5e6c;
          }
          FUN_CODE_8b3b(bVar4 - bVar1);
          param_1 = *pbVar8;
          pbVar8 = pbVar8 + 1;
          FUN_CODE_8800(*pbVar8,0x10);
          param_2 = uVar5;
        }
        FUN_CODE_8b3b();
        *pbVar8 = 0;
        if (BANK1_R2 != '\0') {
          BANK1_R2 = BANK1_R2 + -1;
        }
        if (BANK1_R2 == '\0') {
          return;
        }
      }
LAB_CODE_5e6c:
    }
  }
  return;
}

