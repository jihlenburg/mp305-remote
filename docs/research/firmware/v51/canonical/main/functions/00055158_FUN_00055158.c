/* Address: 00055158; name: FUN_00055158; body bytes: 448 */

void FUN_00055158(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0253 = 0xff;
    return;
  }
  if (DAT_1ffe0253 == param_1) {
    return;
  }
  DAT_1ffe0253 = (byte)param_1;
  uVar2 = 0xff00;
  uVar3 = 0xcc00;
  if (param_1 == 1) {
    uVar1 = FUN_0004b9de(DAT_1ffe0350,2);
    FUN_0004e00e(uVar1,1);
    uVar1 = FUN_0004b9de(DAT_1ffe0360,2);
    FUN_0004aa6e(uVar1,1);
    uVar1 = FUN_0004037c(0xff00);
    FUN_0004e8b2(DAT_1ffe0350,uVar1,0);
  }
  else {
    if (param_1 == 2) {
      uVar3 = FUN_0004b9de(DAT_1ffe0350,2);
      FUN_0004aa6e(uVar3,1);
      uVar3 = FUN_0004b9de(DAT_1ffe0360,2);
      FUN_0004e00e(uVar3,1);
      uVar3 = FUN_0004037c(0xff00);
      FUN_0004e8b2(DAT_1ffe0350,uVar3,0);
      uVar3 = FUN_0004037c(0xcc00);
      uVar2 = FUN_0004b9de(DAT_1ffe0350,0);
      FUN_0004e8b2(uVar2,uVar3,0);
      uVar2 = 0xffa600;
      goto LAB_000552a8;
    }
    if (param_1 != 3) {
      uVar3 = FUN_0004037c(0x999999);
      FUN_0004e8b2(DAT_1ffe0350,uVar3,0);
      uVar3 = FUN_0004037c(0x999999);
      uVar2 = FUN_0004b9de(DAT_1ffe0350,0);
      FUN_0004e8b2(uVar2,uVar3,0);
      uVar3 = FUN_0004037c(0x999999);
      FUN_0004e8b2(DAT_1ffe0578,uVar3,0);
      uVar3 = FUN_0004b9de(DAT_1ffe0350,2);
      FUN_0004aa6e(uVar3,1);
      uVar3 = FUN_0004037c(0x999999);
      FUN_0004e8b2(DAT_1ffe0360,uVar3,0);
      uVar3 = FUN_0004037c(0x999999);
      uVar2 = FUN_0004b9de(DAT_1ffe0360,0);
      FUN_0004e8b2(uVar2,uVar3,0);
      uVar3 = FUN_0004b9de(DAT_1ffe0360,2);
      FUN_0004aa6e(uVar3,1);
      return;
    }
    uVar3 = FUN_0004b9de(DAT_1ffe0360,2);
    FUN_0004aa6e(uVar3,1);
    uVar3 = FUN_0004b9de(DAT_1ffe0350,2);
    FUN_0004aa6e(uVar3,1);
    uVar2 = 0xff66d1;
    uVar3 = FUN_0004037c(0xff66d1);
    FUN_0004e8b2(DAT_1ffe0350,uVar3,0);
    uVar3 = 0xff66d1;
  }
  uVar3 = FUN_0004037c(uVar3);
  uVar1 = FUN_0004b9de(DAT_1ffe0350,0);
  FUN_0004e8b2(uVar1,uVar3,0);
LAB_000552a8:
  uVar3 = FUN_0004037c(uVar2);
  FUN_0004e8b2(DAT_1ffe0578,uVar3,0);
  uVar3 = FUN_0004037c(0xffa600);
  FUN_0004e8b2(DAT_1ffe0360,uVar3,0);
  uVar3 = FUN_0004037c(0xf28100);
  uVar2 = FUN_0004b9de(DAT_1ffe0360,0);
  FUN_0004e8b2(uVar2,uVar3,0);
  return;
}

