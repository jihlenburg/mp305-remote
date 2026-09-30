/* Address: CODE:8832; name: FUN_CODE_8832; body bytes: 50 */

void FUN_CODE_8832(undefined1 param_1,undefined1 param_2)

{
  char in_PSW;
  
  DAT_EXTMEM_04b0 = param_1;
  DAT_EXTMEM_04b1 = param_2;
  FUN_CODE_79d0(0,10,0,0xb,BANK0_R4,BANK0_R5);
  FUN_CODE_9241(BANK0_R6,BANK0_R7);
  FUN_CODE_6de5(DAT_EXTMEM_04b0,DAT_EXTMEM_04b1);
  FUN_CODE_a335();
  if (in_PSW < '\0') {
    FUN_CODE_6406();
  }
  return;
}

