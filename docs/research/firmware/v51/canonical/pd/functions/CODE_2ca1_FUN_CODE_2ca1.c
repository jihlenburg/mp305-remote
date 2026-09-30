/* Address: CODE:2ca1; name: FUN_CODE_2ca1; body bytes: 553 */

void FUN_CODE_2ca1(byte param_1,char param_2,char param_3,undefined1 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  char cVar5;
  byte bVar6;
  undefined1 uVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  undefined1 uVar11;
  char in_PSW;
  undefined1 *puVar12;
  char *pcVar13;
  
  DAT_EXTMEM_04c6 = 0;
  FUN_CODE_9ef9();
  DAT_EXTMEM_04c8 = *(byte *)(CONCAT11(param_3,param_4) + 1);
  DAT_EXTMEM_04cc = param_3;
  DAT_EXTMEM_04cd = param_4;
  cVar5 = FUN_CODE_2eca();
  if (cVar5 == '\0') {
    FUN_CODE_33d6();
    bVar6 = FUN_CODE_33ef();
    if ((bVar6 >> 6 & 1) != 1) {
      puVar12 = (undefined1 *)0x4c8;
      FUN_CODE_939d(DAT_EXTMEM_04c8);
      if (-1 < in_PSW) {
        return;
      }
      goto LAB_CODE_2ebe;
    }
  }
  DAT_EXTMEM_04c9 = 0;
  bVar6 = FUN_CODE_34de();
  DAT_EXTMEM_04c7 = *(byte *)CONCAT11(param_3 - (((0xfb < bVar6) << 7) >> 7),bVar6 + 4);
  DAT_EXTMEM_04cb = DAT_EXTMEM_04c7 + 3;
  bVar6 = DAT_EXTMEM_04c8 & 0xe0;
  if (bVar6 == 0x60) {
    DAT_EXTMEM_04ca = 0xf;
  }
  else {
    DAT_EXTMEM_04ca = DAT_EXTMEM_04c8 & 0x1f;
  }
  if (bVar6 == 0x40) {
    DAT_EXTMEM_04c9 = 0x80;
    FUN_CODE_9800();
    uVar7 = FUN_CODE_34de();
    uVar11 = *(undefined1 *)(CONCAT11(bVar6,uVar7) + 2);
    puVar12 = (undefined1 *)(CONCAT11(bVar6,uVar7) + 3);
    uVar3 = *puVar12;
    FUN_CODE_33d6();
    FUN_CODE_3555();
    *puVar12 = uVar11;
    puVar12[1] = uVar3;
    if (*(char *)(CONCAT11(bVar6,uVar7) + 2) < '\0') {
      FUN_CODE_33d6();
      FUN_CODE_a9ae(0,0x14);
      FUN_CODE_a9ae(0,0x15);
      FUN_CODE_3478();
      uVar1 = BANK0_R3;
      uVar7 = BANK0_R2;
      uVar11 = BANK0_R1;
      FUN_CODE_33d6();
      uVar3 = BANK0_R1;
      bVar10 = param_1 + 0x16;
      BANK0_R1 = uVar11;
      BANK0_R2 = uVar7;
      BANK0_R3 = uVar1;
      FUN_CODE_a90e(uVar3,param_2 - (((0xe9 < param_1) << 7) >> 7),1);
      bVar4 = BANK0_R5;
      bVar6 = BANK0_R4;
      bVar8 = DAT_EXTMEM_04c7 + 2;
      bVar9 = bVar8 & 3;
      DAT_EXTMEM_04c7 = bVar8;
      if (bVar9 != 0) {
        FUN_CODE_33d6(((4 < bVar9) << 7) >> 7,'\x04' - bVar9);
        BANK0_R7 = bVar4;
        BANK0_R6 = bVar6;
        FUN_CODE_aefd((param_2 - (((0xeb < bVar10) << 7) >> 7)) -
                      ((CARRY1(bVar8,bVar10 + 0x14) << 7) >> 7),1,0);
      }
    }
    DAT_EXTMEM_04cb = DAT_EXTMEM_04cb + 2;
  }
  else {
    FUN_CODE_3478();
    uVar1 = BANK0_R3;
    uVar7 = BANK0_R2;
    uVar11 = BANK0_R1;
    FUN_CODE_33d6();
    uVar2 = BANK0_R3;
    uVar3 = BANK0_R1;
    BANK0_R1 = uVar11;
    BANK0_R2 = uVar7;
    BANK0_R3 = uVar1;
    FUN_CODE_a90e(uVar3,param_2 - (((0xeb < param_1) << 7) >> 7),uVar2);
  }
  DAT_EXTMEM_04cb = DAT_EXTMEM_04cb >> 2;
  DAT_EXTMEM_04c9 = DAT_EXTMEM_04c9 | DAT_EXTMEM_04cb << 4;
  pcVar13 = &DAT_EXTMEM_04c9;
  FUN_CODE_3457();
  bVar6 = BANK0_R7;
  DAT_EXTMEM_04c9 = *pcVar13 * '\x02' | DAT_EXTMEM_04c9;
  FUN_CODE_a6d9(*pcVar13);
  bVar10 = DAT_EXTMEM_04ca << 6;
  bVar4 = DAT_EXTMEM_04ca;
  DAT_EXTMEM_04ca = bVar6 | bVar10;
  FUN_CODE_33d6();
  FUN_CODE_33e2();
  FUN_CODE_a99c();
  uVar11 = FUN_CODE_34de();
  bVar6 = BANK0_R6;
  if (*(char *)CONCAT11(bVar10,uVar11) == '\x01') {
    FUN_CODE_33d6();
    bVar6 = FUN_CODE_33e2();
    FUN_CODE_a99c(bVar6 | 4);
  }
  else if (*(char *)CONCAT11(bVar10,uVar11) == '\0') {
    FUN_CODE_a6fd(DAT_EXTMEM_04c9);
    bVar8 = BANK0_R7;
    DAT_EXTMEM_04c9 = bVar6 | bVar4;
    FUN_CODE_a703();
    bVar10 = DAT_EXTMEM_04ca << 5;
    DAT_EXTMEM_04ca = bVar8 | bVar10;
  }
  bVar6 = DAT_EXTMEM_04c9;
  FUN_CODE_33d6(DAT_EXTMEM_04c9);
  FUN_CODE_a9ae(bVar6,0x12);
  FUN_CODE_a9ae(DAT_EXTMEM_04ca,0x13);
  uVar11 = FUN_CODE_34de();
  bVar6 = *(byte *)CONCAT11(bVar10,uVar11);
  cVar5 = CARRY1(bVar6,bVar6) << 7;
  FUN_CODE_a9ae(bVar6 * '\x02' | 0x30,0x58);
  puVar12 = (undefined1 *)0x4c8;
  FUN_CODE_939d(DAT_EXTMEM_04c8);
  if (-1 < cVar5) {
    cVar5 = FUN_CODE_2eca();
    if (cVar5 == '\0') {
      FUN_CODE_33d6();
      bVar6 = FUN_CODE_33ef();
      if ((bVar6 >> 6 & 1) != 1) {
        return;
      }
    }
    FUN_CODE_33d6();
    bVar6 = FUN_CODE_33df();
    FUN_CODE_a99c(bVar6 | 1);
  }
LAB_CODE_2ebe:
  FUN_CODE_34e9(DAT_INTMEM_b3 + -0x74);
  *puVar12 = 0;
  return;
}

