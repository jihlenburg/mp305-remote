/* Address: CODE:50fb; name: FUN_CODE_50fb; body bytes: 250 */

undefined1 FUN_CODE_50fb(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  
  uVar8 = BANK0_R7;
  uVar7 = BANK0_R6;
  uVar6 = BANK0_R5;
  uVar5 = BANK0_R4;
  uVar4 = BANK0_R3;
  uVar3 = BANK0_R2;
  uVar2 = BANK0_R1;
  uVar1 = BANK0_R0;
  DAT_EXTMEM_0551 = DAT_EXTMEM_2038;
  DAT_EXTMEM_0552 = DAT_EXTMEM_2039;
  if (((DAT_EXTMEM_2038 & 3) != 0) || ((DAT_EXTMEM_2039 & 3) != 0)) {
    FUN_CODE_a47b(0x203a);
    DAT_EXTMEM_0763 = 2;
    DAT_INTMEM_b9 = 0;
    FUN_CODE_957e(0x2f,5);
  }
  if ((DAT_EXTMEM_0551 & 0xc) != 0) {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a & 0xf3;
    DAT_INTMEM_b9 = 0;
    FUN_CODE_957e(0x31,5);
  }
  if (((DAT_EXTMEM_0551 & 0x30) != 0) || ((DAT_EXTMEM_0552 & 0xc) != 0)) {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a & 0xcf;
    DAT_EXTMEM_203b = DAT_EXTMEM_203b & 0xf3;
    DAT_EXTMEM_0764 = 2;
    DAT_INTMEM_b9 = 1;
    FUN_CODE_957e(0x2f,5);
  }
  if ((DAT_EXTMEM_0551 & 0xc0) != 0) {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a & 0x3f;
    DAT_INTMEM_b9 = 1;
    FUN_CODE_957e(0x31,5);
  }
  DAT_EXTMEM_2038 = DAT_EXTMEM_2038 & ~DAT_EXTMEM_0551;
  DAT_EXTMEM_2039 = DAT_EXTMEM_2039 & ~DAT_EXTMEM_0552;
  PT0 = 0;
  BANK0_R7 = uVar8;
  BANK0_R6 = uVar7;
  BANK0_R5 = uVar6;
  BANK0_R4 = uVar5;
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return param_1;
}

