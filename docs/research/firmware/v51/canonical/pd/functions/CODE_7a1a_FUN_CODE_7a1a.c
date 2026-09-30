/* Address: CODE:7a1a; name: FUN_CODE_7a1a; body bytes: 72 */

void FUN_CODE_7a1a(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  char in_PSW;
  
  _1_2 = 0;
  _1_3 = 0;
  FUN_CODE_a1f3();
  if (in_PSW < '\0') {
    FUN_CODE_a335();
    if (in_PSW < '\0') {
      FUN_CODE_a6eb();
      if (param_2 == '\x02') {
        _1_3 = 1;
      }
      else if (param_2 == '\x01') {
        _1_2 = 1;
      }
    }
  }
  _1_4 = _1_2 & 1;
  uVar1 = 3;
  FUN_CODE_7763();
  _1_4 = _1_3 & 1;
  DAT_EXTMEM_04a3 = param_1;
  DAT_EXTMEM_04a4 = uVar1;
  FUN_CODE_7763(4);
  FUN_CODE_2800(BANK0_R6,BANK0_R7,DAT_EXTMEM_04a3,DAT_EXTMEM_04a4);
  return;
}

