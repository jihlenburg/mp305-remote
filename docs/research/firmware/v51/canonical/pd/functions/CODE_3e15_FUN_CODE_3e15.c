/* Address: CODE:3e15; name: FUN_CODE_3e15; body bytes: 273 */

void FUN_CODE_3e15(char *param_1,char param_2,char param_3,char param_4,byte param_5)

{
  byte bVar1;
  undefined1 *puVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  char *pcVar8;
  
  if (DAT_INTMEM_b2 == '\x03') {
    if (DAT_INTMEM_b4 == '\x14') {
      return;
    }
    if (DAT_INTMEM_b4 == '\x1a') {
      FUN_CODE_984b();
    }
    else if (DAT_INTMEM_b4 == '\x04') {
      return;
    }
  }
  else if (DAT_INTMEM_b2 == '\x10') {
    if (DAT_INTMEM_b4 == '\x1c') {
      return;
    }
    if (DAT_INTMEM_b4 == '!') {
      return;
    }
    if (DAT_INTMEM_b4 == ':') {
      return;
    }
    if (DAT_INTMEM_b4 == '=') {
      FUN_CODE_6a27(7);
    }
  }
  else {
    cVar7 = (1 < DAT_INTMEM_b2 - 0x10U) << 7;
    if (DAT_INTMEM_b2 == '\x12') {
      puVar2 = &DAT_INTMEM_b4;
      bVar4 = FUN_CODE_ae53(DAT_INTMEM_b4);
      bVar1 = param_4 - (cVar7 >> 7);
      bVar5 = bVar4 + bVar1;
      bVar1 = param_4 - ((CARRY1(bVar4,bVar1) << 7) >> 7);
      bVar6 = (bVar5 + bVar1 ^ param_5) + 1;
      bVar1 = param_4 - ((CARRY1(bVar5,bVar1) << 7) >> 7);
      *param_1 = *param_1 + '\x01';
      bVar4 = param_4 - ((CARRY1(bVar6,bVar1) << 7) >> 7);
      bVar5 = BYTE_ARRAY_CODE_3e30[(ushort)(bVar6 + bVar1) + 0xb] + bVar4;
      BANK1_R0 = *puVar2;
      bVar1 = param_4 - ((CARRY1(BYTE_ARRAY_CODE_3e30[(ushort)(bVar6 + bVar1) + 0xb],bVar4) << 7) >>
                        7);
      bVar4 = bVar5 + bVar1;
      bVar1 = param_4 - ((CARRY1(bVar5,bVar1) << 7) >> 7);
      bVar5 = bVar4 + bVar1;
      bVar1 = param_4 - ((CARRY1(bVar4,bVar1) << 7) >> 7);
      bVar4 = bVar5 + bVar1;
      bVar1 = 1 - ((CARRY1(bVar5,bVar1) << 7) >> 7);
      BANK1_R1 = param_1;
      BANK1_R2 = param_1;
      if (_7_6 == '\0') {
        func_0x383e(param_3 + '\x01');
        *param_1 = *param_1 + -1;
        *param_1 = *param_1 + '\x01';
        uVar3 = TXDAT;
        pcVar8 = (char *)CONCAT11(DAT_EXTMEM_0754 - (((0xf9 < DAT_EXTMEM_0755) << 7) >> 7),
                                  DAT_EXTMEM_0755 + 6);
        bVar1 = pcVar8[1];
        FUN_CODE_ae2a(0x4ba,param_1 + bVar1,
                      param_2 + (*pcVar8 - ((CARRY1(bVar1,(byte)param_1) << 7) >> 7)),uVar3);
        FUN_CODE_908c(DAT_EXTMEM_04b5);
        uVar3 = DAT_EXTMEM_04b5;
        FUN_CODE_622b(DAT_EXTMEM_04b5);
        FUN_CODE_aa6d(0,uVar3);
        FUN_CODE_6293(0x754,DAT_EXTMEM_04b4);
        return;
      }
      _7_6 = 0;
      if ((bVar4 - bVar1) + (param_5 - (((bVar4 < bVar1) << 7) >> 7)) != param_5) {
        FUN_CODE_7d6d(0x4a6,0xe5,0xb5,0xff);
      }
      FUN_CODE_87aa();
      return;
    }
  }
  return;
}

