/* Address: 000126b8; name: FUN_000126b8; body bytes: 282 */

void FUN_000126b8(void)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  ushort uVar5;
  
  if (DAT_1ffe0620 == 0) {
    DAT_1fffab19 = '\0';
  }
  else if (DAT_1fffab19 != '\0') {
    DAT_1fffab19 = 0;
    uVar2 = FUN_0004037c(0xffffff);
    uVar3 = FUN_0004b9de(DAT_1ffe0638,DAT_1fffa0c7);
    FUN_0004e8b2(uVar3,uVar2,0);
    uVar2 = FUN_0004037c(0xffffff);
    uVar3 = FUN_0004b9de(DAT_1ffe0640,DAT_1ffe032d);
    FUN_0004e8b2(uVar3,uVar2,0);
    uVar2 = FUN_0004037c(0xffffff);
    uVar3 = FUN_0004b9de(DAT_1ffe0648,(byte)DAT_1fffac90 - 1);
    FUN_0004e8b2(uVar3,uVar2,0);
    uVar2 = FUN_0004037c(0xffffff);
    uVar3 = FUN_0004b9de(DAT_1ffe0650,DAT_1ffe032e);
    FUN_0004e8b2(uVar3,uVar2,0);
    if (DAT_1fffa0c7 != DAT_1fffac94._2_1_) {
      DAT_1fffa0c7 = DAT_1fffac94._2_1_;
      FUN_0005673c();
      FUN_000561e4();
    }
    uVar4 = 0;
    do {
      if ((ushort)DAT_1fffac94 <= (ushort)(&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + uVar4]) {
        DAT_1ffe032d = (undefined1)uVar4;
        DAT_1fffac94._0_2_ = (&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + uVar4];
        break;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < 0xb);
    uVar1 = 0;
    do {
      uVar5 = uVar1 + 1;
      if (DAT_1fffac90._2_2_ <= (ushort)(uVar5 * 100)) {
        DAT_1fffac90._2_2_ = uVar5 * 100;
        DAT_1ffe032e = (undefined1)uVar1;
        break;
      }
      uVar1 = uVar5 & 0xff;
    } while (uVar1 < 0x32);
    FUN_00056608();
    FUN_00056678();
    FUN_00056120();
    FUN_000567e0();
    return;
  }
  return;
}

