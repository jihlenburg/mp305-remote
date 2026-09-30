/* Address: 00056d80; name: FUN_00056d80; body bytes: 142 */

void FUN_00056d80(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0255 = 0xff;
  }
  else if (DAT_1ffe0255 != param_1) {
    FUN_0003cb2a(&DAT_1fffbbc8,DAT_1ffe03a0);
    uVar1 = FUN_0004cd44(DAT_1ffe03a0);
    if (param_1 == 0) {
      uVar2 = 2;
    }
    else {
      uVar2 = 0x20;
    }
    FUN_0003cb1e(&DAT_1fffbbc8,uVar1,uVar2);
    FUN_0003cafa(&DAT_1fffbbc8,0x2385d);
    FUN_0003cb6c(&DAT_1fffbbc8);
    if (param_1 == 0) {
      FUN_0004aaf6(DAT_1ffe03a4,1);
      FUN_0004e0e6(DAT_1ffe03a8,1);
    }
    else {
      FUN_0004e0e6();
      FUN_0004aaf6(DAT_1ffe03a8,1);
    }
    DAT_1ffe0255 = (char)param_1;
    enter_critical();
    DAT_1fffaa36 = (char)param_1;
    exit_critical();
    return;
  }
  return;
}

