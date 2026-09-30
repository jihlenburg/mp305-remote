/* Address: 000288a4; name: FUN_000288a4; body bytes: 918 */

void FUN_000288a4(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  DAT_1ffe04c8 = FUN_0004b384();
  uVar2 = FUN_000375f8();
  uVar3 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe04c8,uVar3,uVar2);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe04c8,uVar2,0);
  FUN_0004ab24(DAT_1ffe04c8,&DAT_1fffb940,0);
  uVar2 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe04c8,uVar2,0);
  FUN_0004e00e(DAT_1ffe04c8,0x10);
  FUN_0004e822(DAT_1ffe04c8,0);
  uVar2 = FUN_0004b384(DAT_1ffe04c8);
  FUN_0004e84a(uVar2,0x89,0x1e);
  FUN_0004ac0a(uVar2,1,2);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ab24(uVar3,&DAT_1fffb9c4,0);
  uVar4 = FUN_00015a5c(0x10);
  FUN_000499de(uVar3,&DAT_00028c48,uVar4);
  FUN_0004ac0a(uVar3,7,4,0);
  DAT_1ffe04cc = FUN_00048d88(uVar2);
  FUN_0004ab24(DAT_1ffe04cc,&DAT_1fffb9c4,0);
  FUN_000499de(DAT_1ffe04cc,&DAT_00028c50,DAT_1fffab06);
  FUN_0004ac0a(DAT_1ffe04cc,8,0xfffffffb);
  uVar3 = FUN_0004b384(DAT_1ffe04c8);
  iVar5 = FUN_00037604();
  FUN_0004e84a(uVar3,iVar5 + -4,2);
  FUN_0004ac0a(uVar3,2,0,0x1e);
  FUN_0004ab24(uVar3,&DAT_1fffb940,0);
  DAT_1ffe04d0 = FUN_0003e808(DAT_1ffe04c8);
  FUN_0004e84a(DAT_1ffe04d0,100,0x1a);
  FUN_0004ac0a(DAT_1ffe04d0,3,0xfffffffe);
  FUN_0004ab24(DAT_1ffe04d0,&DAT_1fffb970,0);
  uVar3 = FUN_0004037c(0x999999);
  FUN_0004e8e6(DAT_1ffe04d0,uVar3,0);
  uVar3 = FUN_00047698(DAT_1ffe04d0);
  FUN_00047d8e(uVar3,&DAT_0007bab4);
  FUN_0004b128(uVar3);
  FUN_0004e980(uVar3,0xff,0);
  uVar4 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar4,0);
  DAT_1ffe04d4 = FUN_0004a0b8(DAT_1ffe04c8);
  iVar5 = FUN_000375f8();
  iVar6 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe04d4,iVar6 + -4,iVar5 + -0x20);
  FUN_0004ac28(DAT_1ffe04d4,uVar2,0xd,0);
  FUN_0004ab24(DAT_1ffe04d4,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe04d4,0);
  FUN_0004e822(DAT_1ffe04d4,0);
  uVar2 = FUN_00015a5c(0x11);
  uVar2 = FUN_0004a094(DAT_1ffe04d4,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba3c,0);
  DAT_1ffe04d8 = FUN_00048d88(uVar2);
  FUN_0004ac0a(DAT_1ffe04d8,8,0);
  FUN_0004ab24(DAT_1ffe04d8,&DAT_1fffb9ac,0);
  uVar1 = DAT_1fffab4c;
  uVar7 = (uint)DAT_1fffab4e;
  if (uVar7 < 0x28) {
    FUN_000499de(DAT_1ffe04d8,&DAT_00028c6c);
    uVar1 = 0;
  }
  else {
    FUN_000499de(DAT_1ffe04d8,"%02d.%01dV/%dW",uVar7 / 10,uVar7 % 10);
  }
  uVar2 = FUN_00015a5c(0x12);
  uVar2 = FUN_0004a094(DAT_1ffe04d4,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba3c,0);
  DAT_1ffe04dc = FUN_00048d88(uVar2);
  FUN_0004ac0a(DAT_1ffe04dc,8,0);
  FUN_0004ab24(DAT_1ffe04dc,&DAT_1fffb9ac,0);
  FUN_000499de(DAT_1ffe04dc,&DAT_00028c84,DAT_1fffa128);
  uVar2 = FUN_00015a5c(0x13);
  uVar2 = FUN_0004a094(DAT_1ffe04d4,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba3c,0);
  DAT_1ffe04e0 = FUN_00048d88(uVar2);
  FUN_0004ac0a(DAT_1ffe04e0,8,0);
  FUN_0004ab24(DAT_1ffe04e0,&DAT_1fffb9ac,0);
  if (DAT_1fffab98 == 0xffffffff) {
    FUN_000499de(DAT_1ffe04e0,&DAT_00028cb0);
  }
  else {
    FUN_000499de(DAT_1ffe04e0,"%ldh%02ldmin",DAT_1fffab98 / 0xe10,(DAT_1fffab98 % 0xe10) / 0x3c);
  }
  uVar2 = FUN_00015a5c(0x14);
  uVar2 = FUN_0004a094(DAT_1ffe04d4,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba3c,0);
  DAT_1ffe04e4 = FUN_00048d88(uVar2);
  FUN_0004ac0a(DAT_1ffe04e4,8,0);
  FUN_0004ab24(DAT_1ffe04e4,&DAT_1fffb9ac,0);
  FUN_000499de(DAT_1ffe04e4,&DAT_00028c9c,(int)DAT_1fffab05,(DAT_1fffab05 * 9) / 5 + 0x20);
  uVar2 = FUN_00015a5c(0x15);
  uVar2 = FUN_0004a094(DAT_1ffe04d4,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba3c,0);
  DAT_1ffe04e8 = FUN_00048d88(uVar2);
  FUN_0004ac0a(DAT_1ffe04e8,8,0);
  FUN_0004ab24(DAT_1ffe04e8,&DAT_1fffb9ac,0);
  FUN_000499de(DAT_1ffe04e8,&DAT_00028ca8,DAT_1fffab4a);
  uVar2 = FUN_00015a5c(0x16);
  uVar2 = FUN_0004a094(DAT_1ffe04d4,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba3c,0);
  DAT_1ffe04ec = FUN_00048d88(uVar2);
  FUN_0004ac0a(DAT_1ffe04ec,8,0);
  FUN_0004ab24(DAT_1ffe04ec,&DAT_1fffb9ac,0);
  FUN_000499de(DAT_1ffe04ec,&DAT_00028c50,(&DAT_1ffe0778)[DAT_1ffe032c]);
  FUN_0004e906(uVar2,0,0,uVar1);
  return;
}

