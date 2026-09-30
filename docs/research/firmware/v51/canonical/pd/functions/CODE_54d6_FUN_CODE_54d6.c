/* Address: CODE:54d6; name: FUN_CODE_54d6; body bytes: 128 */

void FUN_CODE_54d6(char param_1,undefined1 param_2)

{
  char cVar1;
  char in_PSW;
  byte *pbVar2;
  
  thunk_FUN_CODE_a557();
  DAT_EXTMEM_04b2 = 0;
  DAT_EXTMEM_04b3 = param_2;
  thunk_FUN_CODE_a560();
  pbVar2 = (byte *)0x4b2;
  FUN_CODE_55aa(0xb1,0xb8,0xff);
  FUN_CODE_a153();
  if (in_PSW < '\0') {
    FUN_CODE_557a();
                    /* WARNING: Subroutine does not return */
    FUN_CODE_ad49();
  }
  cVar1 = FUN_CODE_5590(0);
  if (cVar1 == '\0') {
    FUN_CODE_5049();
    do {
      param_1 = param_1 + -1;
    } while (param_1 != '\0');
    FUN_CODE_5000();
    FUN_CODE_5561(0xbc,0xb8);
  }
  cVar1 = FUN_CODE_5590(1);
  if (cVar1 == '\0') {
    FUN_CODE_5049();
    do {
      param_1 = param_1 + -1;
    } while (param_1 != '\0');
    FUN_CODE_5000();
    FUN_CODE_5561(0xc5,0xb8);
  }
  FUN_CODE_557a();
  if (*pbVar2 >> 6 == 0) {
    cVar1 = FUN_CODE_5049();
    do {
      cVar1 = cVar1 << 1;
      param_1 = param_1 + -1;
    } while (param_1 != '\0');
    FUN_CODE_5000(cVar1);
    FUN_CODE_55aa(0x4b6,0xce,0xb8);
  }
  return;
}

