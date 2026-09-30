/* Address: 0002f4ec; name: FUN_0002f4ec; body bytes: 466 */

void FUN_0002f4ec(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  DAT_1ffe0540 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0540,uVar2,uVar1);
  uVar1 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0540,uVar1,0);
  FUN_0004ab24(DAT_1ffe0540,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0540,uVar1,0);
  FUN_0004e00e(DAT_1ffe0540,0x10);
  uVar1 = FUN_0004b384(DAT_1ffe0540);
  FUN_0004e84a(uVar1,100,0x1e);
  FUN_0004ac0a(uVar1,0,2);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  uVar1 = FUN_00048d88(uVar1);
  FUN_0004ab24(uVar1,&DAT_1fffb9c4,0);
  uVar2 = FUN_00015a5c(1);
  FUN_000499de(uVar1,&DAT_0002f6cc,uVar2);
  FUN_0004ea86(uVar1,2,0);
  FUN_0004b128(uVar1);
  DAT_1ffe0544 = FUN_0003e808(DAT_1ffe0540);
  FUN_0004e84a(DAT_1ffe0544,100,0x1a);
  FUN_0004ac0a(DAT_1ffe0544,3,0xfffffffe);
  FUN_0004ab24(DAT_1ffe0544,&DAT_1fffb970,0);
  uVar1 = FUN_0004037c(0x999999);
  FUN_0004e8e6(DAT_1ffe0544,uVar1,0);
  uVar1 = FUN_00047698(DAT_1ffe0544);
  FUN_00047d8e(uVar1,&DAT_0007bab4);
  FUN_0004b128(uVar1);
  FUN_0004e980(uVar1,0xff,0);
  uVar2 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar1,uVar2,0);
  uVar1 = FUN_0004b384(DAT_1ffe0540);
  iVar3 = FUN_00037604();
  FUN_0004e84a(uVar1,iVar3 + -4,2);
  FUN_0004ac0a(uVar1,2,0,0x1e);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  DAT_1ffe0548 = FUN_0004a0b8(DAT_1ffe0540);
  iVar3 = FUN_000375f8();
  iVar4 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0548,iVar4 + -4,iVar3 + -0x21);
  FUN_0004ac0a(DAT_1ffe0548,1,2,0x21);
  FUN_0004ab24(DAT_1ffe0548,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0548,0);
  DAT_1ffe054c = FUN_00048d88(DAT_1ffe0540);
  FUN_0004e7c2(DAT_1ffe054c,0x7c,0x74);
  FUN_0004ab24(DAT_1ffe054c,&DAT_1fffb9ac,0);
  uVar1 = FUN_00015a5c(0x2a);
  FUN_000499de(DAT_1ffe054c,&DAT_0002f6cc,uVar1);
  if (DAT_1fffa409 != '\0') {
    FUN_0004aa6e(DAT_1ffe054c,1);
    FUN_0004e00e(DAT_1ffe0548,1);
    FUN_0002f3a0(DAT_1ffe0548);
    return;
  }
  FUN_0004aa6e(DAT_1ffe0548,1);
  FUN_0004e00e(DAT_1ffe054c,1);
  return;
}

