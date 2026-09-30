/* Address: 0002a13c; name: FUN_0002a13c; body bytes: 252 */

void FUN_0002a13c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  uStack_20 = param_2;
  uStack_1c = param_3;
  uStack_18 = param_4;
  DAT_1ffe0644 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0644,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0644,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe0644,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0644,0);
  FUN_0004e00e(DAT_1ffe0644,0x10);
  FUN_0004e822(DAT_1ffe0644,0);
  DAT_1ffe0648 = FUN_0004a0b8(DAT_1ffe0644);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe0648,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe0648,6,0);
  FUN_0004ab24(DAT_1ffe0648,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe0648,0);
  uVar4 = 0;
  do {
    FUN_00020000(&uStack_20,10,&DAT_0002a248,uVar4 + 1);
    uVar2 = FUN_0004a094(DAT_1ffe0648,&uStack_20);
    FUN_0004ab24(uVar2,&DAT_1fffba84,0);
    if ((byte)DAT_1fffac90 - 1 == uVar4) {
      uVar3 = FUN_0004037c(0xffa600);
      FUN_0004e8b2(uVar2,uVar3,0);
    }
    FUN_0004aa6e(uVar2,2);
    if (((DAT_1fffac94._2_1_ < 3) && (5 < uVar4)) || ((DAT_1fffac94._2_1_ == 3 && (7 < uVar4)))) {
      FUN_0004aa6e(uVar2,1);
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 0xc);
  FUN_0004e906(uVar2,0);
  return;
}

