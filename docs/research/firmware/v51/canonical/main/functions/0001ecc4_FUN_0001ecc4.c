/* Address: 0001ecc4; name: FUN_0001ecc4; body bytes: 614 */

void FUN_0001ecc4(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  if ((0x13 < DAT_1fffaae7) && (iVar1 = FUN_0004fe9c(), iVar1 != DAT_1ffe0590)) {
    iVar1 = FUN_0004cd1e(DAT_1ffe0774);
    if ((iVar1 != 0) && (DAT_1fffaae7 < 100)) {
      DAT_1fffaad3 = 1;
      DAT_1fffaad4 = 1;
      FUN_0004eb0e(DAT_1ffe0774,0);
    }
    iVar1 = FUN_00037604();
    uVar3 = (uint)DAT_1fffaae7;
    uVar2 = FUN_0004b9de(DAT_1ffe0774,1);
    FUN_0004eae2(uVar2,(int)((uVar3 - 0x14) * iVar1) / 0x50);
  }
  iVar1 = FUN_0004cd1e(DAT_1ffe0774);
  if (((iVar1 == 0) && (DAT_1fffaae7 == 0)) &&
     ((iVar1 = FUN_0004fe9c(), iVar1 == DAT_1ffe0590 ||
      ((iVar1 = FUN_0004fe9c(), iVar1 != DAT_1ffe0590 && (DAT_1fffaae1 == '\0')))))) {
    DAT_1fffaae1 = '\0';
    DAT_1fffaad3 = 0;
    DAT_1fffaad4 = 0;
    uVar2 = FUN_00037604();
    FUN_0004eb0e(DAT_1ffe0774,uVar2);
    uVar2 = FUN_0004b9de(DAT_1ffe0774,1);
    FUN_0004eae2(uVar2,0);
  }
  if (DAT_1fffaae5 < 4) {
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    if (DAT_1fffaae5 == 3) {
      DAT_1fffab90 = DAT_1fffab90 + 100;
      if ((DAT_1fffab90 < 60000) || (DAT_1fffab20 != 'd')) {
        if ((DAT_1fffab90 < 60000) && (DAT_1fffab20 != 'd')) {
          if (DAT_1fffab20 == '\0') {
            FUN_0003c11a();
          }
          DAT_1fffab20 = 'd';
          FUN_0001cd54(100);
          DAT_1fffab1b = 0;
          FUN_0001cb8c(0xf);
        }
      }
      else {
        DAT_1fffab1b = 1;
        if (DAT_1fffab06 < DAT_1fffaaf9) {
          DAT_1fffab20 = '\n';
        }
        else {
          DAT_1fffab20 = '\0';
          FUN_0003c102();
        }
        FUN_0001cd54(DAT_1fffab20);
      }
      goto LAB_0001ee20;
    }
  }
  else {
    if (DAT_1fffaafa == '\0') {
      DAT_1fffab88 = 0;
LAB_0001eda8:
      if (DAT_1fffab20 != 'd') {
        DAT_1fffab20 = 'd';
        FUN_0001cd54(100);
        DAT_1fffab1b = 0;
        FUN_0001cb8c(0xf);
      }
    }
    else {
      DAT_1fffab88 = DAT_1fffab88 + 100;
      if ((29999 < DAT_1fffab88) && (DAT_1fffab20 != '\n')) {
        DAT_1fffab20 = '\n';
        FUN_0001cd54();
        DAT_1fffab1b = 1;
      }
      if (DAT_1fffab88 < 30000) goto LAB_0001eda8;
    }
    if (DAT_1ffe0864 == 0) {
      DAT_1fffab8c = 0;
    }
    else {
      DAT_1fffab8c = DAT_1fffab8c + 100;
      if ((uint)((short)(ushort)(byte)(&DAT_1ffe077d)[DAT_1ffe0864] * 60000) <= DAT_1fffab8c) {
        FUN_0001afb4(1);
        DAT_1fffab1c = 0;
        DAT_1fff9550 = DAT_1fff9550 | 1;
      }
    }
  }
  DAT_1fffab90 = 0;
LAB_0001ee20:
  if (DAT_1fffab0d != '\0') {
    DAT_1fffab0d = '\0';
    FUN_0004e5a6(DAT_1ffe03c4,7,0);
  }
  FUN_00054390();
  FUN_00054940(DAT_1fffaad0);
  FUN_00055478(DAT_1fffab7a);
  FUN_00054f18(DAT_1fffab7a);
  FUN_00056f3c();
  FUN_00056e3c();
  FUN_00057b78(0);
  iVar1 = FUN_0004cd1e(DAT_1ffe072c);
  if (iVar1 != 0) {
    return;
  }
  if (DAT_1fffac8c == 0) {
    if (DAT_1fffac88 < 7) {
      FUN_000499de(DAT_1ffe0734,"Self-test ...  %d/%d",DAT_1fffac88,6);
      return;
    }
    if (DAT_1fffac88 != 8) {
      return;
    }
    FUN_000499de(DAT_1ffe0734,"Self-test All OK %d/%d",6,6,unaff_r4,unaff_lr);
  }
  else {
    FUN_000499de(DAT_1ffe0734,"Self-test Err %d");
  }
  FUN_0004e00e(DAT_1ffe0730,1);
  return;
}

