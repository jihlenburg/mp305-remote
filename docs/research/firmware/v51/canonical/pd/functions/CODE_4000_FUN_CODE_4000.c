/* Address: CODE:4000; name: FUN_CODE_4000; body bytes: 313 */

char FUN_CODE_4000(undefined1 param_1,byte param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined1 uVar4;
  char cVar5;
  
  FUN_CODE_a74b();
  cVar5 = (param_2 ^ 0x80) + 0x80;
  DAT_EXTMEM_04aa = param_2;
  if (0x7f < (param_2 ^ 0x80)) {
    thunk_FUN_CODE_90f3(param_2);
    DAT_EXTMEM_04a8 = BANK0_R2;
    DAT_EXTMEM_04a9 = BANK0_R1;
    DAT_EXTMEM_04aa = DAT_EXTMEM_04aa + 1;
    DAT_EXTMEM_04ab = *(byte *)CONCAT11(BANK0_R2,BANK0_R1) >> 6;
    cVar5 = (*(byte *)CONCAT11(BANK0_R2,BANK0_R1) >> 5) << 7;
    if (DAT_EXTMEM_04ab == 0) {
      FUN_CODE_46b2();
      uVar1 = BANK0_R7;
      uVar4 = BANK0_R6;
      bVar3 = BANK0_R5;
      uVar2 = BANK0_R4;
      FUN_CODE_46e6();
      FUN_CODE_475f();
      FUN_CODE_acf0(10);
      BANK0_R3 = uVar1;
      BANK0_R2 = uVar4;
      BANK0_R1 = bVar3;
      BANK0_R0 = uVar2;
      FUN_CODE_acbf();
      FUN_CODE_46e6(BANK0_R4,BANK0_R5,BANK0_R6,BANK0_R7);
      FUN_CODE_475f();
      FUN_CODE_46dd();
                    /* WARNING: Subroutine does not return */
      thunk_FUN_CODE_ad49();
    }
    if (DAT_EXTMEM_04ab == 3) {
      bVar3 = BANK0_R1;
      FUN_CODE_a153();
      if (cVar5 < '\0') {
        FUN_CODE_46cf(0xb5,0x19);
        FUN_CODE_acf0(param_1,9,bVar3 & 0xfc);
        uVar1 = BANK0_R7;
        uVar4 = BANK0_R6;
        bVar3 = BANK0_R5;
        uVar2 = BANK0_R4;
        FUN_CODE_46b2();
        BANK0_R3 = uVar1;
        BANK0_R2 = uVar4;
        BANK0_R1 = bVar3;
        BANK0_R0 = uVar2;
        FUN_CODE_acbf();
        uVar1 = BANK0_R7;
        uVar4 = BANK0_R6;
        bVar3 = BANK0_R5;
        uVar2 = BANK0_R4;
        FUN_CODE_46cb();
        BANK0_R3 = uVar1;
        BANK0_R2 = uVar4;
        BANK0_R1 = bVar3;
        BANK0_R0 = uVar2;
        FUN_CODE_46dd();
                    /* WARNING: Subroutine does not return */
        thunk_FUN_CODE_ad49();
      }
      FUN_CODE_46d7(0x14,0,0,DAT_INTMEM_b5,DAT_INTMEM_b6);
      FUN_CODE_acf0(9);
      uVar1 = BANK0_R7;
      uVar4 = BANK0_R6;
      bVar3 = BANK0_R5;
      uVar2 = BANK0_R4;
      FUN_CODE_46b2();
      BANK0_R3 = uVar1;
      BANK0_R2 = uVar4;
      BANK0_R1 = bVar3;
      BANK0_R0 = uVar2;
      FUN_CODE_acbf();
      uVar1 = BANK0_R7;
      uVar4 = BANK0_R6;
      bVar3 = BANK0_R5;
      uVar2 = BANK0_R4;
      FUN_CODE_46cb();
      BANK0_R3 = uVar1;
      BANK0_R2 = uVar4;
      BANK0_R1 = bVar3;
      BANK0_R0 = uVar2;
      FUN_CODE_acbf();
      FUN_CODE_ad6d(0x4ac);
      FUN_CODE_a3a3();
      if (cVar5 < '\0') {
        uVar2 = 2;
      }
      else {
        uVar2 = 6;
      }
      FUN_CODE_a73f(uVar2);
    }
    FUN_CODE_4789();
    FUN_CODE_9d03();
    FUN_CODE_a153();
    FUN_CODE_4789();
    if (cVar5 < '\0') {
      FUN_CODE_89e0();
      FUN_CODE_89e0(0xb0,4,1);
      FUN_CODE_4789();
      uVar2 = 8;
      uVar4 = 0x29;
    }
    else {
      uVar2 = 4;
      uVar4 = 0x22;
    }
    cVar5 = FUN_CODE_95d5(uVar2,uVar4);
  }
  return cVar5;
}

