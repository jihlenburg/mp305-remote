/* Address: CODE:7712; name: FUN_CODE_7712; body bytes: 81 */

void FUN_CODE_7712(undefined1 param_1)

{
  undefined1 uVar1;
  char in_PSW;
  
  _1_4 = 0;
  uVar1 = 1;
  FUN_CODE_7763();
  DAT_EXTMEM_04a3 = param_1;
  DAT_EXTMEM_04a4 = uVar1;
  FUN_CODE_8ea7();
  DAT_EXTMEM_04a7 = uVar1;
  FUN_CODE_a584();
  if (in_PSW < '\0') {
    DAT_EXTMEM_04a5 = DAT_EXTMEM_04a3;
    DAT_EXTMEM_04a6 = DAT_EXTMEM_04a4;
    DAT_EXTMEM_04a8 = DAT_EXTMEM_04a7;
  }
  else {
    _1_4 = 0;
    uVar1 = 2;
    FUN_CODE_7763();
    DAT_EXTMEM_04a5 = param_1;
    DAT_EXTMEM_04a6 = uVar1;
    FUN_CODE_8ea7();
    DAT_EXTMEM_04a8 = uVar1;
  }
  FUN_CODE_870e(DAT_EXTMEM_04a8,DAT_EXTMEM_04a7);
  return;
}

