/* Address: 000128a4; name: FUN_000128a4; body bytes: 492 */

void FUN_000128a4(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  byte bVar4;
  
  if (settings_dirty != '\0') {
    settings_dirty = '\0';
    if (DAT_1fffab02 == '\0') {
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe06cc,DAT_1ffe032c);
      FUN_0004e8b2(uVar2,uVar1,0);
      bVar4 = 0;
      do {
        uVar1 = FUN_0004037c(0xffffff);
        uVar2 = FUN_0004b9de(DAT_1ffe06d4,bVar4);
        FUN_0004e8b2(uVar2,uVar1,0);
        bVar4 = bVar4 + 1;
      } while (bVar4 < 4);
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe06dc,DAT_1fffaafa == '\0');
      FUN_0004e8b2(uVar2,uVar1,0);
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe06e4,DAT_1ffe0864);
      FUN_0004e8b2(uVar2,uVar1,0);
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe06ec,DAT_1ffe0865);
      FUN_0004e8b2(uVar2,uVar1,0);
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe06f4,DAT_1ffe0867);
      FUN_0004e8b2(uVar2,uVar1,0);
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe06fc,DAT_1ffe0866);
      FUN_0004e8b2(uVar2,uVar1,0);
      uVar3 = 0;
      do {
        if (DAT_1fffaaf9 <= (byte)(&DAT_1ffe0778)[uVar3]) {
          DAT_1ffe032c = (undefined1)uVar3;
          DAT_1fffaaf9 = (&DAT_1ffe0778)[uVar3];
          break;
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < 5);
      uVar3 = 0;
      do {
        if (DAT_1fffaaff <= (byte)(&DAT_1ffe077d)[uVar3]) {
          DAT_1ffe0864 = (undefined1)uVar3;
          DAT_1fffaaff = (&DAT_1ffe077d)[uVar3];
          break;
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < 6);
      uVar3 = 0;
      do {
        if (DAT_1fffab62 <= (ushort)(&DAT_1ffe0784)[uVar3]) {
          DAT_1ffe0865 = (undefined1)uVar3;
          DAT_1fffab62 = (&DAT_1ffe0784)[uVar3];
          break;
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < 10);
      uVar3 = 0;
      do {
        if (DAT_1fffab64 <= (ushort)(&DAT_1ffe0798)[uVar3]) {
          DAT_1ffe0867 = (undefined1)uVar3;
          DAT_1fffab64 = (&DAT_1ffe0798)[uVar3];
          break;
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < 6);
      uVar3 = 0;
      do {
        if (DAT_1fffab70 <= (ushort)(&DAT_1ffe07a4)[uVar3]) {
          DAT_1ffe0866 = (undefined1)uVar3;
          DAT_1fffab70 = (&DAT_1ffe07a4)[uVar3];
          break;
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < 0xb);
      FUN_000564b4();
      FUN_0005836c();
      FUN_00057204();
      FUN_00057288();
      FUN_00056fc0();
      FUN_00056d0c();
      FUN_000581ac();
    }
    else {
      DAT_1fffab1d = 1;
    }
    if (DAT_1fffab01 != '\0') {
      FUN_0004e5a6(DAT_1ffe0744,7,0);
      return;
    }
  }
  return;
}

