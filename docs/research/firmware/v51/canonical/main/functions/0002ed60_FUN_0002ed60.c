/* Address: 0002ed60; name: FUN_0002ed60; body bytes: 820 */

void FUN_0002ed60(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  DAT_1ffe0590 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0590,uVar2,uVar1);
  FUN_0004ab24(DAT_1ffe0590,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0590,uVar1,0);
  uVar1 = FUN_00048d88(DAT_1ffe0590);
  FUN_0004ac0a(uVar1,2,0,5);
  FUN_0004eab0(uVar1,&DAT_0006a6dc,0);
  uVar2 = FUN_0004037c(0x7d7d7d);
  FUN_0004ea90(uVar1,uVar2,0);
  FUN_000499de(uVar1,"POWER ON");
  FUN_0004aa6e(uVar1,1);
  uVar1 = FUN_0004b384(DAT_1ffe0590);
  FUN_0004e84a(uVar1,0,2);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  uVar2 = FUN_0004037c(0xd9d9d9);
  FUN_0004e8b2(uVar1,uVar2,0);
  uVar1 = FUN_00047698(DAT_1ffe0590);
  FUN_00047d8e(uVar1,&DAT_0007ea64);
  FUN_0004aa6e(uVar1,1);
  DAT_1ffe0594 = FUN_00048d88(DAT_1ffe0590);
  FUN_0004ac0a(DAT_1ffe0594,9,0,0xffffffd6);
  FUN_0004ab24(DAT_1ffe0594,&DAT_1fffb9a0,0);
  FUN_0004eab0(DAT_1ffe0594,&DAT_000730fc,0);
  FUN_000499de(DAT_1ffe0594,&DAT_0002f0c4,DAT_1fffab06);
  DAT_1ffe0598 = FUN_00048d88(DAT_1ffe0590);
  FUN_0004e84a(DAT_1ffe0598,0x41,0x17);
  FUN_0004ac28(DAT_1ffe0598,DAT_1ffe0594,0xe,0,5);
  FUN_0004ab24(DAT_1ffe0598,&DAT_1fffb97c,0);
  FUN_0004ea60(DAT_1ffe0598,2,0);
  uVar1 = FUN_0004037c(0x7d7d7d);
  FUN_0004e8e6(DAT_1ffe0598,uVar1,0);
  FUN_0004eab0(DAT_1ffe0598,&DAT_00075094,0);
  uVar1 = FUN_0004037c(0x7d7d7d);
  FUN_0004ea90(DAT_1ffe0598,uVar1,0);
  FUN_0004ea86(DAT_1ffe0598,2,0);
  FUN_0004ea3c(DAT_1ffe0598,0xffffffff);
  FUN_000499de(DAT_1ffe0598,&DAT_0002f0d4,DAT_1fffab4c);
  FUN_0004aa6e(DAT_1ffe0598,1);
  uVar1 = FUN_0004b384(DAT_1ffe0590);
  FUN_0004e84a(uVar1,0x3a,0x18);
  FUN_0004ac28(uVar1,DAT_1ffe0598,0xe,0,0x10);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  FUN_0004e8dc(uVar1,0);
  uVar2 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar2,0x36,0x18);
  FUN_0004ab24(uVar2,&DAT_1fffb958,0);
  FUN_0004ea60(uVar2,4,0);
  DAT_1ffe059c = FUN_0004b384(uVar2);
  FUN_0004e84a(DAT_1ffe059c,((short)(100 - (ushort)DAT_1fffab06) * 0x32) / 100,0x14);
  FUN_0004ac0a(DAT_1ffe059c,8,0xfffffffe);
  FUN_0004ab24(DAT_1ffe059c,&DAT_1fffb958,0);
  FUN_0004ea60(DAT_1ffe059c,3,0);
  uVar3 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar3,3,0xe);
  FUN_0004ab24(uVar3,&DAT_1fffb958,0);
  FUN_0004ea60(uVar3,1,0);
  FUN_0004ac0a(uVar3,8,0);
  if (DAT_1fffab06 < 0xb) {
    uVar5 = 0xff0000;
    uVar4 = FUN_0004037c(0xff0000);
    FUN_0004e8b2(uVar2,uVar4,0);
    uVar2 = 0x260000;
  }
  else if (DAT_1fffab06 - 0xb < 10) {
    uVar5 = 0xcca900;
    uVar4 = FUN_0004037c(0xcca900);
    FUN_0004e8b2(uVar2,uVar4,0);
    uVar2 = 0x261f00;
  }
  else {
    uVar5 = 0xcc66;
    uVar4 = FUN_0004037c(0xcc66);
    FUN_0004e8b2(uVar2,uVar4,0);
    uVar2 = 0x2613;
  }
  uVar2 = FUN_0004037c(uVar2);
  FUN_0004e8b2(DAT_1ffe059c,uVar2,0);
  uVar2 = FUN_0004037c(uVar5);
  FUN_0004e8b2(uVar3,uVar2,0);
  DAT_1ffe05a0 = FUN_00047698(DAT_1ffe0590);
  FUN_00047d8e(DAT_1ffe05a0,&DAT_0007e904);
  FUN_0004ac28(DAT_1ffe05a0,uVar1,2,0,0xfffffff1);
  FUN_0004aa6e(DAT_1ffe05a0,1);
  DAT_1ffe05a4 = FUN_00047698(DAT_1ffe0590);
  FUN_00047d8e(DAT_1ffe05a4,&DAT_000810b4);
  FUN_0004ac28(DAT_1ffe05a4,uVar1,2,0);
  FUN_0004aa6e(DAT_1ffe05a4,1);
  uVar1 = FUN_00048d88(DAT_1ffe0590);
  FUN_0004ac0a(uVar1,5,0,0xfffffffc);
  FUN_0004eab0(uVar1,&DAT_0006a6dc,0);
  uVar2 = FUN_0004037c(0x7d7d7d);
  FUN_0004ea90(uVar1,uVar2,0);
  FUN_000499de(uVar1,"MP305B");
  return;
}

