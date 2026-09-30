/* Address: 0002f0f4; name: FUN_0002f0f4; body bytes: 602 */

void FUN_0002f0f4(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  
  FUN_0004b288(param_1);
  for (uVar6 = 0; uVar6 < (byte)(&DAT_1fffa3f4)[DAT_1fffa408]; uVar6 = uVar6 + 1 & 0xff) {
    uVar3 = FUN_0004a094(param_1,&DAT_0002f358);
    FUN_0004ab24(uVar3,&DAT_1fffba54,0);
    if (uVar6 == 0) {
      uVar4 = FUN_0004037c(0x261f00);
      FUN_0004e8b2(uVar3,uVar4,0);
      uVar4 = FUN_0004037c(0xffa600);
      FUN_0004e8e6(uVar3,uVar4,0);
    }
    uVar4 = FUN_00048d88(uVar3);
    FUN_0004eae2(uVar4,0x1e);
    FUN_0004ea86(uVar4,2,0);
    FUN_000499de(uVar4,&DAT_0002f368,uVar6 + 1);
    if ((&DAT_1fffa41c)[uVar6 * 3] == 0) {
      uVar4 = FUN_00048d88(uVar3);
      FUN_0004eae2(uVar4,0x39);
      FUN_0004ac0a(uVar4,0,0x3e);
      FUN_0004ea86(uVar4,2,0);
      uVar1 = FUN_00048d88(uVar3);
      FUN_0004eae2(uVar1,0x39);
      FUN_0004ac0a(uVar1,0,0x92);
      FUN_0004ea86(uVar1,2,0);
      uVar2 = FUN_00048d88(uVar3);
      FUN_0004eae2(uVar2,0x50);
      FUN_0004ac0a(uVar2,0,0xd9);
      FUN_0004ea86(uVar2,2,0);
      FUN_000499de(uVar2,&DAT_0002f368,(uint)(&DAT_1fffa41c)[uVar6 * 3] / 10);
      if ((&DAT_1fffa414)[uVar6 * 3] == 0) {
        FUN_00049974(uVar4,&DAT_0002f38c);
        FUN_00049974(uVar1,&DAT_0002f390);
        FUN_00049974(uVar2,&DAT_0002f390);
      }
      else {
        FUN_00049974(uVar4,&DAT_0002f384);
        FUN_000499de(uVar1,&DAT_0002f368,(uint)(&DAT_1fffa418)[uVar6 * 3] >> 0x18);
        if (((&DAT_1fffa418)[uVar6 * 3] & 0xffffff) == 0) {
          FUN_00049974(uVar2,&DAT_0002f390);
        }
        else {
          FUN_000499de(uVar2,&DAT_0002f368,(&DAT_1fffa418)[uVar6 * 3] & 0xffffff);
        }
        DAT_1fffab84 = (&DAT_1fffa418)[uVar6 * 3] & 0xffffff;
      }
    }
    else {
      uVar4 = FUN_00048d88(uVar3);
      FUN_0004eae2(uVar4,0x39);
      FUN_0004ac0a(uVar4,0,0x3e);
      FUN_0004ea86(uVar4,2,0);
      FUN_000499de(uVar4,"%02d.%02d",(*(ushort *)(&DAT_1fffa414 + uVar6 * 3) & 0x7fff) / 1000,
                   ((*(ushort *)(&DAT_1fffa414 + uVar6 * 3) & 0x7fff) / 10) % 100);
      uVar4 = FUN_00048d88(uVar3);
      FUN_0004eae2(uVar4,0x39);
      FUN_0004ac0a(uVar4,0,0x92);
      FUN_0004ea86(uVar4,2,0);
      FUN_000499de(uVar4,"%01d.%03d",(uint)(&DAT_1fffa418)[uVar6 * 3] / 1000,
                   (uint)(&DAT_1fffa418)[uVar6 * 3] % 1000);
      uVar4 = FUN_00048d88(uVar3);
      FUN_0004eae2(uVar4,0x39);
      FUN_0004ac0a(uVar4,0,0xe6);
      FUN_0004ea86(uVar4,2,0);
      FUN_000499de(uVar4,&DAT_0002f368,(uint)(&DAT_1fffa41c)[uVar6 * 3] / 10);
    }
    FUN_0004aa6e(uVar3,2);
  }
  for (uVar6 = 0; uVar5 = FUN_0004ba5c(DAT_1ffe04fc), uVar6 < uVar5; uVar6 = uVar6 + 1) {
    uVar3 = FUN_0004b9de(DAT_1ffe04fc,uVar6);
    uVar4 = FUN_0004b9de(DAT_1ffe04fc,uVar6);
    FUN_0004aa4c(uVar4,0x14f65,0,uVar3);
  }
  return;
}

