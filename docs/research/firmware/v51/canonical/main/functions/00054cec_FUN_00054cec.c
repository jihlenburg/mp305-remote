/* Address: 00054cec; name: FUN_00054cec; body bytes: 370 */

void FUN_00054cec(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_1ffe04f4 == 0) {
    DAT_1ffe0254 = 0xff;
    return;
  }
  if (DAT_1ffe0254 == param_1) {
    return;
  }
  DAT_1ffe0254 = (byte)param_1;
  if (param_1 == 1) {
    uVar1 = FUN_0004b9de(DAT_1ffe050c,2);
    FUN_0004e00e(uVar1,1);
    uVar1 = FUN_0004b9de(DAT_1ffe0510,2);
    FUN_0004aa6e(uVar1,1);
  }
  else {
    if (param_1 != 2) {
      if (param_1 != 3) {
        uVar1 = FUN_0004037c(0x999999);
        FUN_0004e8b2(DAT_1ffe050c,uVar1,0);
        uVar1 = FUN_0004037c(0x999999);
        uVar2 = FUN_0004b9de(DAT_1ffe050c,0);
        FUN_0004e8b2(uVar2,uVar1,0);
        uVar1 = FUN_0004b9de(DAT_1ffe050c,2);
        FUN_0004aa6e(uVar1,1);
        uVar1 = FUN_0004037c(0x999999);
        FUN_0004e8b2(DAT_1ffe0510,uVar1,0);
        uVar1 = FUN_0004037c(0x999999);
        uVar2 = FUN_0004b9de(DAT_1ffe0510,0);
        FUN_0004e8b2(uVar2,uVar1,0);
        uVar1 = FUN_0004b9de(DAT_1ffe0510,2);
        FUN_0004aa6e(uVar1,1);
        return;
      }
      uVar1 = FUN_0004b9de(DAT_1ffe0510,2);
      FUN_0004aa6e(uVar1,1);
      uVar1 = FUN_0004b9de(DAT_1ffe050c,2);
      FUN_0004aa6e(uVar1,1);
      uVar1 = FUN_0004037c(0xff66d1);
      FUN_0004e8b2(DAT_1ffe050c,uVar1,0);
      uVar1 = 0xff66d1;
      goto LAB_00054dee;
    }
    uVar1 = FUN_0004b9de(DAT_1ffe050c,2);
    FUN_0004aa6e(uVar1,1);
    uVar1 = FUN_0004b9de(DAT_1ffe0510,2);
    FUN_0004e00e(uVar1,1);
  }
  uVar1 = FUN_0004037c(0xff00);
  FUN_0004e8b2(DAT_1ffe050c,uVar1,0);
  uVar1 = 0xcc00;
LAB_00054dee:
  uVar1 = FUN_0004037c(uVar1);
  uVar2 = FUN_0004b9de(DAT_1ffe050c,0);
  FUN_0004e8b2(uVar2,uVar1,0);
  uVar1 = FUN_0004037c(0xffa600);
  FUN_0004e8b2(DAT_1ffe0510,uVar1,0);
  uVar1 = FUN_0004037c(0xf28100);
  uVar2 = FUN_0004b9de(DAT_1ffe0510,0);
  FUN_0004e8b2(uVar2,uVar1,0);
  return;
}

