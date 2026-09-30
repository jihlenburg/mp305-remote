/* Address: 0001cea8; name: FUN_0001cea8; body bytes: 60 */

void FUN_0001cea8(uint param_1)

{
  undefined4 uVar1;
  
  DAT_1fffa9b8 = (undefined2)param_1;
  if (param_1 < 0x3ff) {
    if (param_1 == 0) {
      uVar1 = 0x200;
    }
    else {
      FUN_0001df02(&DAT_4003a000,0,param_1);
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0x300;
  }
  FUN_0001decc(&DAT_4003a000,0,uVar1);
  return;
}

