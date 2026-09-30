/* Address: CODE:69a3; name: FUN_CODE_69a3; body bytes: 132 */

void FUN_CODE_69a3(char param_1,char param_2)

{
  undefined1 uVar1;
  
  if (param_1 == param_2) {
    DAT_EXTMEM_04a8 = param_1;
    return;
  }
  DAT_EXTMEM_04a8 = param_1;
  if (param_1 == '\x02') {
    FUN_CODE_a247(5);
    uVar1 = 2;
  }
  else if (param_1 == '\x03') {
    FUN_CODE_9023(4);
    FUN_CODE_a0cb(2);
    uVar1 = 6;
  }
  else if (param_1 == '\x04') {
    FUN_CODE_9023(5);
    FUN_CODE_a0cb(1);
    uVar1 = 7;
  }
  else {
    if (param_1 == '\x05') {
      FUN_CODE_9023(0);
      if (DAT_INTMEM_cc == '\x03') {
        uVar1 = 2;
      }
      else {
        uVar1 = 0;
      }
      FUN_CODE_a0cb(uVar1);
      goto LAB_CODE_6a1e;
    }
    if (param_1 != '\x06') {
      if (param_1 == '\x01') {
        thunk_FUN_CODE_a45d();
        FUN_CODE_a22f();
      }
      goto LAB_CODE_6a1e;
    }
    if ((DAT_INTMEM_cd & 0xf) == 2) {
      FUN_CODE_a63f(0x20);
      DAT_EXTMEM_04a8 = '\a';
      goto LAB_CODE_6a1e;
    }
    uVar1 = 0xb;
  }
  FUN_CODE_a223(uVar1);
LAB_CODE_6a1e:
  FUN_CODE_a0bd(DAT_EXTMEM_04a8);
  return;
}

