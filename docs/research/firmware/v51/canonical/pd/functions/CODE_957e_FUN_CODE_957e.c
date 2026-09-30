/* Address: CODE:957e; name: FUN_CODE_957e; body bytes: 29 */

void FUN_CODE_957e(short param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  
  if (DAT_INTMEM_a4 < 0x20) {
    uVar1 = BANK0_R5;
    FUN_CODE_848e(DAT_INTMEM_a4 - 0x20,BANK0_R5);
    *(undefined1 *)(param_1 + 1) = DAT_INTMEM_b9;
    FUN_CODE_8474(uVar1,CONCAT11(param_2,param_3) + 2);
  }
  return;
}

