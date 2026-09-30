/* Address: CODE:1800; name: FUN_CODE_1800; body bytes: 878 */

void FUN_CODE_1800(undefined1 param_1,char param_2)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  undefined1 uVar7;
  byte bVar8;
  char cVar9;
  undefined1 uVar10;
  byte bVar11;
  undefined1 uVar12;
  undefined2 uVar13;
  byte *pbVar14;
  undefined1 *puVar15;
  undefined1 *puVar16;
  undefined2 uStack_1;
  
  DAT_EXTMEM_04ce = '\0';
  DAT_EXTMEM_04cf = '\0';
  DAT_EXTMEM_04d0 = 0;
  DAT_EXTMEM_04d1 = '\0';
  cVar6 = DAT_INTMEM_b3 * '(' + 0x4d;
  cVar3 = '\x04' - (((0xb2 < DAT_INTMEM_b3 * '(') << 7) >> 7);
  DAT_EXTMEM_04c8 = cVar3;
  DAT_EXTMEM_04c9 = cVar6;
  if (DAT_INTMEM_b3 == 0) {
    uVar13 = 0x4c8;
    if (DAT_INTMEM_5e == 'A' && DAT_INTMEM_5d == '\0') {
      FUN_CODE_1e02();
      FUN_CODE_1dbe(0x44d);
      FUN_CODE_ad92();
      uStack_1 = CONCAT11(cVar3,cVar6);
      FUN_CODE_1e02();
      FUN_CODE_1dbe(uStack_1);
      FUN_CODE_ad92();
      uVar7 = FUN_CODE_1dcb();
      uStack_1 = CONCAT11(cVar3,uVar7);
      FUN_CODE_1e02();
      FUN_CODE_1dbe(uStack_1);
      FUN_CODE_ad92();
      uStack_1 = CONCAT11(cVar3,uVar7);
      FUN_CODE_1e02();
      FUN_CODE_1dbe(uStack_1);
      FUN_CODE_ad92();
      uVar7 = FUN_CODE_1dcb();
      uStack_1 = CONCAT11(cVar3,uVar7);
      FUN_CODE_1e02();
      FUN_CODE_1dbe(uStack_1);
      FUN_CODE_ad92();
      uStack_1 = CONCAT11(cVar3,uVar7);
      FUN_CODE_1e02();
      FUN_CODE_1dbe(uStack_1);
      FUN_CODE_ad92();
      DAT_EXTMEM_04cf = DAT_EXTMEM_04ce + -1;
    }
    else {
      FUN_CODE_1ea7();
      FUN_CODE_1e02();
      FUN_CODE_1dbe(uVar13);
      FUN_CODE_ad92();
      DAT_EXTMEM_04cf = DAT_EXTMEM_04ce;
    }
    FUN_CODE_1f4c(DAT_EXTMEM_04ce);
    *(undefined1 *)(param_2 + -0x77) = BANK0_R7;
    return;
  }
  bVar5 = 0;
  uVar7 = FUN_CODE_1dcb(0x28);
  bVar4 = 1;
  FUN_CODE_aefd(uVar7,1);
  DAT_EXTMEM_04d2 = 0;
  do {
    bVar11 = (DAT_EXTMEM_04d2 < 7) << 7;
    if (DAT_EXTMEM_04d2 >= 7) {
      FUN_CODE_a786(DAT_EXTMEM_04d2 - 7);
      if (((char)bVar11 < '\0') && (bVar11 = bVar11 & 0xdd, (DAT_EXTMEM_040e & 7) == 3)) {
        FUN_CODE_1ea4();
                    /* WARNING: Subroutine does not return */
        FUN_CODE_ad49();
      }
      FUN_CODE_a786();
      bVar4 = DAT_INTMEM_b3;
      if (((char)bVar11 < '\0') && ((DAT_EXTMEM_0412 & 7) == 4)) {
        FUN_CODE_1ea4();
                    /* WARNING: Subroutine does not return */
        FUN_CODE_ad49();
      }
      *(undefined1 *)(DAT_INTMEM_b3 + 0x89) = BANK0_R7;
      *(undefined1 *)(bVar4 + 0x8d) = BANK0_R7;
      *(char *)CONCAT11('\x03' - (((0x12 < bVar4) << 7) >> 7),bVar4 - 0x13) = DAT_EXTMEM_04d1 + '\a'
      ;
      return;
    }
    bVar11 = DAT_EXTMEM_04d2;
    FUN_CODE_1d56(DAT_EXTMEM_04d2);
    bVar8 = FUN_CODE_1dfa();
    if ((bVar8 & 7) == 1) {
      cVar3 = '\x06';
      do {
        bVar5 = bVar5 >> 1;
        cVar3 = cVar3 + -1;
      } while (cVar3 != '\0');
      cVar9 = FUN_CODE_1d6e();
      cVar6 = cVar3;
      if (_1_7 == '\x01') {
LAB_CODE_1984:
        cVar3 = cVar6;
        FUN_CODE_1f60(cVar9);
        uVar2 = BANK0_R3;
        uVar10 = BANK0_R2;
        uVar12 = BANK0_R1;
        uVar7 = BANK0_R0;
        FUN_CODE_1d3e(DAT_EXTMEM_04d2);
        do {
          bVar5 = bVar5 >> 1;
          cVar3 = cVar3 + -1;
        } while (cVar3 != '\0');
        FUN_CODE_1ed2();
        BANK0_R0 = uVar7;
        BANK0_R1 = uVar12;
        BANK0_R2 = uVar10;
        BANK0_R3 = uVar2;
        FUN_CODE_ab95();
      }
      else {
        bVar11 = FUN_CODE_1d3e(DAT_EXTMEM_04d2);
        do {
          bVar8 = bVar5 >> 1;
          bVar11 = bVar11 >> 1 | bVar5 << 7;
          cVar3 = cVar3 + -1;
          bVar5 = bVar8;
        } while (cVar3 != '\0');
        bVar5 = bVar8 & 3;
        bVar8 = 1 - (((bVar11 < 0x2d) << 7) >> 7);
        cVar9 = bVar5 - bVar8;
        cVar6 = '\0';
        if ((bVar5 < bVar8) << 7 < '\0') goto LAB_CODE_1984;
        FUN_CODE_1efd();
        bVar1 = 0xd3 < bVar11;
        bVar11 = bVar11 + 0x2c;
        bVar5 = bVar5 + ('\x01' - ((bVar1 << 7) >> 7));
      }
      FUN_CODE_1d87();
      uVar7 = FUN_CODE_1dc5();
      uStack_1 = CONCAT11(param_1,uVar7);
      FUN_CODE_1f18();
      FUN_CODE_1dbf(bVar4,uStack_1);
      FUN_CODE_ad6d();
      DAT_EXTMEM_04cf = DAT_EXTMEM_04cf + '\x01';
      bVar4 = 0xff;
      param_1 = 0xb1;
      puVar16 = (undefined1 *)0x4d2;
      FUN_CODE_1d56(0x92);
      FUN_CODE_1d49();
      do {
        bVar5 = bVar5 >> 1;
        cVar3 = cVar3 + -1;
      } while (cVar3 != '\0');
      FUN_CODE_1d32();
      do {
        bVar5 = bVar5 >> 1;
        cVar3 = cVar3 + -1;
      } while (cVar3 != '\0');
      uVar7 = FUN_CODE_1f20();
LAB_CODE_1aca:
      *puVar16 = uVar7;
      puVar16[1] = bVar11;
LAB_CODE_1b66:
      FUN_CODE_87aa();
    }
    else {
      uVar12 = 0xd2;
      bVar8 = DAT_EXTMEM_04d2;
      uVar7 = FUN_CODE_1d56(DAT_EXTMEM_04d2);
      if ((*(byte *)(CONCAT11(uVar7,uVar12) + 1) & 7) == 2) {
        FUN_CODE_ad92(0x4ca);
        DAT_EXTMEM_04ca = DAT_EXTMEM_04ca | 0xc0;
        puVar16 = &DAT_EXTMEM_04cb;
        FUN_CODE_1de3(bVar8);
        uVar7 = *puVar16;
        bVar4 = puVar16[1];
        FUN_CODE_1e31(uVar7,DAT_EXTMEM_04cd);
        pbVar14 = (byte *)0x4cb;
        cVar3 = FUN_CODE_1f38(DAT_EXTMEM_04cb & 1,DAT_EXTMEM_04ca & 0xfe | CARRY1(bVar4,bVar4),
                              bVar4 * '\x02');
        uVar12 = SUB21(pbVar14,0);
        if (_1_7 == '\x01') {
LAB_CODE_1a6c:
          uVar10 = SUB21(pbVar14,0);
          uVar12 = FUN_CODE_1d52(cVar3);
          bVar11 = DAT_EXTMEM_04cd & 0x80 | *(byte *)CONCAT11(uVar12,uVar10) >> 1;
        }
        else {
          uVar10 = FUN_CODE_1d52();
          pbVar14 = (byte *)CONCAT11(uVar10,uVar12);
          cVar6 = (*pbVar14 >> 1 < 0x3d) << 7;
          cVar3 = cVar6 >> 7;
          if ((cVar6 < '\0') << 7 < '\0') goto LAB_CODE_1a6c;
          bVar11 = DAT_EXTMEM_04cd & 0x80 | 0x3c;
        }
        bVar5 = DAT_EXTMEM_04cc;
        FUN_CODE_1e2f(bVar11);
        uVar12 = FUN_CODE_1dc5();
        uStack_1 = CONCAT11(uVar7,uVar12);
        FUN_CODE_1f18();
        FUN_CODE_1f03(uStack_1);
        param_1 = 0xb1;
        puVar16 = &DAT_EXTMEM_04d2;
        FUN_CODE_1de3(DAT_EXTMEM_04d2,0x9d);
        puVar15 = puVar16 + 1;
        FUN_CODE_1e7e(0,*puVar16);
        puVar15[1] = 0;
        puVar15 = puVar15 + 2;
        *puVar15 = BANK0_R5;
        uVar7 = FUN_CODE_1d52();
        bVar11 = *(byte *)CONCAT11(uVar7,(char)puVar15) >> 1;
        puVar16 = &DAT_EXTMEM_04da;
        uVar7 = 0;
        goto LAB_CODE_1aca;
      }
      FUN_CODE_1d52();
      bVar8 = FUN_CODE_1dfa();
      if ((bVar8 & 7) == 5) {
        cVar3 = '\x06';
        do {
          bVar5 = bVar5 >> 1;
          cVar3 = cVar3 + -1;
        } while (cVar3 != '\0');
        FUN_CODE_1d6e();
        FUN_CODE_1f60();
        uVar2 = BANK0_R3;
        uVar10 = BANK0_R2;
        uVar12 = BANK0_R1;
        uVar7 = BANK0_R0;
        FUN_CODE_1d3e(DAT_EXTMEM_04d2);
        do {
          bVar5 = bVar5 >> 1;
          cVar3 = cVar3 + -1;
        } while (cVar3 != '\0');
        FUN_CODE_1ed2();
        BANK0_R0 = uVar7;
        BANK0_R1 = uVar12;
        BANK0_R2 = uVar10;
        BANK0_R3 = uVar2;
        FUN_CODE_ab95();
        FUN_CODE_1d87();
        bVar8 = FUN_CODE_1e5c();
        DAT_EXTMEM_04ca = bVar8 | 0x20;
        DAT_EXTMEM_04cb = bVar11;
        uVar7 = FUN_CODE_1dc5();
        uStack_1 = CONCAT11(param_1,uVar7);
        FUN_CODE_1f18();
        FUN_CODE_1f03(uStack_1);
        param_1 = 0xb1;
        puVar16 = (undefined1 *)0x4d2;
        FUN_CODE_1d56(0xab);
        FUN_CODE_1d49();
        do {
          bVar5 = bVar5 >> 1;
          cVar3 = cVar3 + -1;
        } while (cVar3 != '\0');
        FUN_CODE_1d32();
        do {
          bVar5 = bVar5 >> 1;
          cVar3 = cVar3 + -1;
        } while (cVar3 != '\0');
        uVar7 = FUN_CODE_1f20();
        *puVar16 = uVar7;
        puVar16[1] = bVar11;
        FUN_CODE_1efd();
        FUN_CODE_ad6d(0x4da);
        goto LAB_CODE_1b66;
      }
    }
    DAT_EXTMEM_04d2 = DAT_EXTMEM_04d2 + 1;
  } while( true );
}

