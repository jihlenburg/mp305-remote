/* Address: 0003325c; name: FUN_0003325c; body bytes: 674 */

void FUN_0003325c(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined1 auStack_38 [20];
  
  DAT_1ffe0608 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0608,uVar2,uVar1);
  uVar1 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0608,uVar1,0);
  FUN_0004ab24(DAT_1ffe0608,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0608,uVar1,0);
  FUN_0004e00e(DAT_1ffe0608,0x10);
  FUN_0004e822(DAT_1ffe0608,0);
  uVar1 = FUN_0004b384(DAT_1ffe0608);
  FUN_0004e84a(uVar1,100,0x1e);
  FUN_0004ac0a(uVar1,1,2);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  uVar1 = FUN_00048d88(uVar1);
  FUN_0004ab24(uVar1,&DAT_1fffb9c4,0);
  uVar2 = FUN_00015a5c(1);
  FUN_000499de(uVar1,&DAT_0003350c,uVar2);
  FUN_0004ea86(uVar1,2,0);
  FUN_0004b128(uVar1);
  DAT_1ffe060c = FUN_0003e808(DAT_1ffe0608);
  FUN_0004e84a(DAT_1ffe060c,100,0x1a);
  FUN_0004ac0a(DAT_1ffe060c,3,0xfffffffe);
  FUN_0004ab24(DAT_1ffe060c,&DAT_1fffb970,0);
  uVar1 = FUN_0004037c(0x999999);
  FUN_0004e8e6(DAT_1ffe060c,uVar1,0);
  uVar1 = FUN_00047698(DAT_1ffe060c);
  FUN_00047d8e(uVar1,&DAT_0007bab4);
  FUN_0004b128(uVar1);
  FUN_0004e980(uVar1,0xff,0);
  uVar9 = 0xffffff;
  uVar2 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar1,uVar2,0);
  uVar1 = FUN_0004b384(DAT_1ffe0608);
  iVar3 = FUN_00037604();
  FUN_0004e84a(uVar1,iVar3 + -4,2);
  FUN_0004ac0a(uVar1,2,0,0x1e);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  DAT_1ffe0610 = FUN_0004a0b8(DAT_1ffe0608);
  iVar3 = FUN_000375f8();
  iVar4 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0610,iVar4 + -4,iVar3 + -0x21);
  FUN_0004ac0a(DAT_1ffe0610,1,2,0x21);
  FUN_0004ab24(DAT_1ffe0610,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0610,0);
  uVar8 = 0;
  do {
    uVar1 = FUN_0004a094(DAT_1ffe0610,&DAT_00033524);
    FUN_0004ab24(uVar1,&DAT_1fffba60,0);
    uVar2 = FUN_00048d88(uVar1);
    FUN_0004eae2(uVar2,0x1e);
    FUN_0004ea86(uVar2,2,0);
    FUN_000499de(uVar2,&DAT_0003352c,uVar8 + 1);
    uVar5 = FUN_00048d88(uVar1);
    FUN_0004ac0a(uVar5,0,0x43);
    FUN_0004ea86(uVar5,2,0);
    FUN_0001046a(auStack_38,&DAT_1fffa138 + uVar8 * 0x10,0x10);
    FUN_000499de(uVar5,&DAT_0003350c,auStack_38);
    uVar6 = FUN_00048d88(uVar1);
    FUN_0004ac0a(uVar6,8,0xfffffff0,0);
    FUN_0004ea86(uVar6,2,0);
    FUN_000499de(uVar6,&DAT_00033530,(&DAT_1fffa340)[uVar8]);
    if (DAT_1fffa34a == uVar8) {
      uVar7 = 0xffa600;
    }
    else {
      uVar7 = 0x333333;
    }
    uVar7 = FUN_0004037c(uVar7);
    FUN_0004e8b2(uVar1,uVar7,0);
    uVar7 = uVar9;
    if (DAT_1fffa34a == uVar8) {
      uVar7 = 0x333333;
    }
    uVar7 = FUN_0004037c(uVar7);
    FUN_0004ea90(uVar2,uVar7,0);
    uVar2 = uVar9;
    if (DAT_1fffa34a == uVar8) {
      uVar2 = 0x333333;
    }
    uVar2 = FUN_0004037c(uVar2);
    FUN_0004ea90(uVar5,uVar2,0);
    uVar2 = uVar9;
    if (DAT_1fffa34a == uVar8) {
      uVar2 = 0x333333;
    }
    uVar2 = FUN_0004037c(uVar2);
    FUN_0004ea90(uVar6,uVar2,0);
    FUN_0004aa6e(uVar1,2);
    uVar8 = uVar8 + 1;
  } while ((int)uVar8 < 10);
  return;
}

