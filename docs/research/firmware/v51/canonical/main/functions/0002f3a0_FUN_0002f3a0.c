/* Address: 0002f3a0; name: FUN_0002f3a0; body bytes: 296 */

void FUN_0002f3a0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  undefined1 auStack_3c [24];
  
  FUN_0004b288();
  bVar7 = 1;
  do {
    if (DAT_1fffa409 < bVar7) {
      for (uVar6 = 0; uVar5 = FUN_0004ba5c(DAT_1ffe0548), uVar6 < uVar5; uVar6 = uVar6 + 1 & 0xff) {
        uVar4 = FUN_0004b9de(DAT_1ffe0548,uVar6);
        FUN_0004aa4c(uVar4,0x59099,0);
      }
      return;
    }
    uVar4 = FUN_0004a094(param_1,&DAT_0002f4d0);
    FUN_0004ab24(uVar4,&DAT_1fffba60,0);
    uVar1 = FUN_00048d88(uVar4);
    FUN_0004eae2(uVar1,0x1e);
    FUN_0004ea86(uVar1,2,0);
    FUN_000499de(uVar1,&DAT_0002f4d8,bVar7);
    uVar2 = FUN_00048d88(uVar4);
    FUN_0004ac0a(uVar2,0,0x3e);
    uVar6 = 0;
    do {
      if ((&DAT_1fffa3fe)[uVar6] == bVar7) {
        FUN_0001046a(auStack_3c,&DAT_1fffa354 + uVar6 * 0x10,0x10);
        break;
      }
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < 10);
    FUN_000499de(uVar2,&DAT_0002f4dc,auStack_3c);
    FUN_0004aa6e(uVar4,2);
    if ((&DAT_1fffa3fe)[DAT_1fffa408] == bVar7) {
      uVar3 = 0xffa600;
    }
    else {
      uVar3 = 0x333333;
    }
    uVar3 = FUN_0004037c(uVar3);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar4 = 0xffffff;
    if ((&DAT_1fffa3fe)[DAT_1fffa408] == bVar7) {
      uVar4 = 0x333333;
    }
    uVar4 = FUN_0004037c(uVar4);
    FUN_0004ea90(uVar1,uVar4,0);
    uVar4 = 0xffffff;
    if ((&DAT_1fffa3fe)[DAT_1fffa408] == bVar7) {
      uVar4 = 0x333333;
    }
    uVar4 = FUN_0004037c(uVar4);
    FUN_0004ea90(uVar2,uVar4,0);
    bVar7 = bVar7 + 1;
  } while( true );
}

