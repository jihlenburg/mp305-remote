/* Address: 0002b350; name: FUN_0002b350; body bytes: 224 */

void FUN_0002b350(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  DAT_1ffe0634 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0634,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0634,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe0634,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0634,0);
  FUN_0004e00e(DAT_1ffe0634,0x10);
  FUN_0004e822(DAT_1ffe0634,0);
  DAT_1ffe0638 = FUN_0004a0b8(DAT_1ffe0634);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe0638,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe0638,6,0);
  FUN_0004ab24(DAT_1ffe0638,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe0638,0);
  uVar4 = 0;
  do {
    uVar2 = FUN_0004a094(DAT_1ffe0638,(&DAT_1ffe07bc)[uVar4]);
    FUN_0004ab24(uVar2,&DAT_1fffba84,0);
    if (DAT_1fffa0c7 == uVar4) {
      uVar3 = FUN_0004037c(0xffa600);
      FUN_0004e8b2(uVar2,uVar3,0);
    }
    FUN_0004aa6e(uVar2,2);
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 6);
  FUN_0004e906(uVar2,0);
  return;
}

