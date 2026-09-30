/* Address: 00057064; name: FUN_00057064; body bytes: 284 */

void FUN_00057064(uint param_1,int param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe025b = 0xff;
    return;
  }
  if ((DAT_1ffe025b == param_1) && (param_2 == 0)) {
    return;
  }
  if ((((DAT_1fffaae4 & 1) == 0) || (DAT_1fffaad6 == '\0')) &&
     ((-1 < (int)((uint)DAT_1fffaae4 << 0x1e) || (DAT_1fffaad7 == '\0')))) {
    FUN_0004e00e(DAT_1ffe0440,1);
    if (DAT_1fffaad7 == '\0') {
      FUN_0004e00e(DAT_1ffe0444,1);
    }
    else {
      FUN_0004aa6e();
    }
    FUN_0004e0e6(DAT_1ffe0430,1);
    FUN_0004e0e6(DAT_1ffe0434,1);
    FUN_0004e0e6(DAT_1ffe0438,1);
    FUN_0004e0e6(DAT_1ffe043c,1);
    FUN_0004aa6e(DAT_1ffe0448,1);
  }
  else {
    FUN_0004aa6e(DAT_1ffe0440,1);
    FUN_0004aa6e(DAT_1ffe0444,1);
    FUN_0004aaf6(DAT_1ffe0430,1);
    FUN_0004aaf6(DAT_1ffe0434,1);
    FUN_0004aaf6(DAT_1ffe0438,1);
    FUN_0004aaf6(DAT_1ffe043c,1);
    uVar1 = FUN_00050710(DAT_1ffe03d8);
    FUN_0005833c(uVar1);
    if ((DAT_1fffab04 == '\0') || (DAT_1fffaad7 == '\0')) goto LAB_00057174;
    FUN_0004e00e(DAT_1ffe0448,1);
  }
  uVar2 = FUN_0004b9de(DAT_1ffe0448,0);
  FUN_0004aa6e(uVar2,1);
  uVar2 = FUN_0004b9de(DAT_1ffe0448,1);
  FUN_0004aa6e(uVar2,1);
LAB_00057174:
  DAT_1ffe025b = (char)param_1;
  return;
}

