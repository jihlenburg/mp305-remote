/* Address: 0005889c; name: FUN_0005889c; body bytes: 188 */

void FUN_0005889c(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  FUN_00054a18(DAT_1fffaada);
  FUN_000549cc(DAT_1fffab06);
  FUN_00056e14(DAT_1fffab4c);
  if (DAT_1fffaae7 < 100) {
    if (DAT_1fffaae7 == 0) {
      uVar1 = FUN_0004b9de(DAT_1ffe0590,0);
      FUN_0004aa6e(uVar1,1);
    }
    else {
      uVar1 = FUN_0004b9de(DAT_1ffe0590,0);
      FUN_0004e00e(uVar1,1);
    }
    iVar2 = FUN_00037604();
    uVar4 = (uint)DAT_1fffaae7;
    uVar1 = FUN_0004b9de(DAT_1ffe0590,1);
    FUN_0004eae2(uVar1,(uVar4 * iVar2) / 100);
  }
  if (3 < DAT_1fffaae5) {
    DAT_1fffaacd = 0;
    uVar1 = FUN_00037604();
    uVar3 = FUN_0004b9de(DAT_1ffe0590,1);
    FUN_0004eae2(uVar3,uVar1);
    FUN_0004fea8(DAT_1ffe0344);
    if (DAT_1ffe02c4 != 0) {
      FUN_000528ac();
      DAT_1ffe02c4 = 0;
    }
    if (DAT_1ffe04f4 == 0) {
      FUN_00018114(DAT_1ffe0348);
    }
    else {
      FUN_00017cf8();
    }
    DAT_1fffaad4 = 0;
    DAT_1fffab1b = 0;
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    DAT_1fffab90 = 0;
  }
  return;
}

