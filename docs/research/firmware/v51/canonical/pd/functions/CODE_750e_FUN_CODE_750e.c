/* Address: CODE:750e; name: FUN_CODE_750e; body bytes: 90 */

void FUN_CODE_750e(undefined1 param_1,undefined1 param_2)

{
  undefined1 uVar1;
  char in_PSW;
  undefined1 *puVar2;
  
  DAT_EXTMEM_04a5 = param_2;
  FUN_CODE_a000();
  if (in_PSW < '\0') {
    puVar2 = &DAT_EXTMEM_04a5;
    uVar1 = DAT_EXTMEM_04a5;
    FUN_CODE_82bd();
    *puVar2 = uVar1;
    DAT_INTMEM_a7 = BANK0_R7;
    FUN_CODE_a638(1,7);
    uVar1 = DAT_EXTMEM_04a5;
    FUN_CODE_a0a1();
    DAT_EXTMEM_04a6 = param_1;
    DAT_EXTMEM_04a7 = uVar1;
    FUN_CODE_a0af(DAT_EXTMEM_04a5);
    FUN_CODE_93fa(BANK0_R6,BANK0_R7,DAT_EXTMEM_04a6,DAT_EXTMEM_04a7);
    if (_1_5 != '\0') {
      FUN_CODE_6ba4(DAT_EXTMEM_04a6,DAT_EXTMEM_04a7);
      FUN_CODE_9fe9(0x43);
    }
  }
  return;
}

