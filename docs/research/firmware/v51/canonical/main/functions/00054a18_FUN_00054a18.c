/* Address: 00054a18; name: FUN_00054a18; body bytes: 500 */

void FUN_00054a18(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (DAT_1ffe024d != param_1) {
    bVar1 = (byte)param_1;
    if (param_1 == 1) {
      uVar3 = FUN_0004037c(0xcc66);
      uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
      uVar4 = FUN_0004b9de(uVar4,0);
      FUN_0004e8b2(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0x2613);
      FUN_0004e8b2(DAT_1ffe059c,uVar3,0);
      uVar3 = FUN_0004037c(0xcc66);
      uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
      uVar4 = FUN_0004b9de(uVar4,1);
      FUN_0004e8b2(uVar4,uVar3,0);
      FUN_0004e00e(DAT_1ffe05a0,1);
      FUN_0004e00e(DAT_1ffe0598,1);
      FUN_0004aa6e(DAT_1ffe05a4,1);
      DAT_1ffe024d = bVar1;
      DAT_1ffe024e = 0xff;
      return;
    }
    FUN_0004aa6e(DAT_1ffe05a0,1);
    FUN_0004aa6e(DAT_1ffe0598,1);
    if (param_1 == 2) {
      uVar3 = FUN_0004037c(0x7f7f7f);
      uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
      uVar4 = FUN_0004b9de(uVar4,0);
      FUN_0004e8b2(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0x262626);
      FUN_0004e8b2(DAT_1ffe059c,uVar3,0);
      uVar3 = FUN_0004037c(0x7f7f7f);
      uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
      uVar4 = FUN_0004b9de(uVar4,1);
      FUN_0004e8b2(uVar4,uVar3,0);
      FUN_0004e00e(DAT_1ffe05a4,1);
      DAT_1ffe024d = bVar1;
      DAT_1ffe024e = 0xff;
      return;
    }
    FUN_0004aa6e(DAT_1ffe05a4,1);
    DAT_1ffe024d = bVar1;
  }
  if (param_1 != 0) {
    DAT_1ffe024e = 0xff;
    return;
  }
  uVar2 = (uint)DAT_1fffab06;
  if ((uVar2 < 0xb) && (DAT_1ffe024e != '\0')) {
    DAT_1ffe024e = 0;
    uVar5 = 0xff0000;
    uVar3 = FUN_0004037c(0xff0000);
    uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
    uVar4 = FUN_0004b9de(uVar4,0);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar3 = 0x260000;
  }
  else if ((uVar2 - 0xb < 10) && (DAT_1ffe024e != '\x01')) {
    uVar5 = 0xcca900;
    DAT_1ffe024e = 1;
    uVar3 = FUN_0004037c(0xcca900);
    uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
    uVar4 = FUN_0004b9de(uVar4,0);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar3 = 0x261f00;
  }
  else {
    if (uVar2 < 0x15) {
      return;
    }
    if (DAT_1ffe024e == '\x02') {
      return;
    }
    DAT_1ffe024e = 2;
    uVar5 = 0xcc66;
    uVar3 = FUN_0004037c(0xcc66);
    uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
    uVar4 = FUN_0004b9de(uVar4,0);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar3 = 0x2613;
  }
  uVar3 = FUN_0004037c(uVar3);
  FUN_0004e8b2(DAT_1ffe059c,uVar3,0);
  uVar3 = FUN_0004037c(uVar5);
  uVar4 = FUN_0004b9de(DAT_1ffe0590,5);
  uVar4 = FUN_0004b9de(uVar4,1);
  FUN_0004e8b2(uVar4,uVar3,0,param_4);
  return;
}

