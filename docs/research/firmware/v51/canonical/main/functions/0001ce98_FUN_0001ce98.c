/* Address: 0001ce98; name: FUN_0001ce98; body bytes: 60 */

void FUN_0001ce98(uint param_1)

{
  undefined4 uVar1;
  
  DAT_1fffa9c0 = (undefined2)param_1;
  if (param_1 < 0x3ff) {
    if (param_1 == 0) {
      uVar1 = 0x200;
    }
    else {
      FUN_0001df02(&DAT_4003a000,3,param_1);
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0x300;
  }
  FUN_0001decc(&DAT_4003a000,3,uVar1);
  return;
}

