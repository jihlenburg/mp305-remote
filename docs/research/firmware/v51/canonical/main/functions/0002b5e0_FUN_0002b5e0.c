/* Address: 0002b5e0; name: FUN_0002b5e0; body bytes: 254 */

void FUN_0002b5e0(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined8 uVar5;
  undefined1 auStack_28 [12];
  
  DAT_1ffe064c = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe064c,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe064c,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe064c,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe064c,0);
  FUN_0004e00e(DAT_1ffe064c,0x10);
  FUN_0004e822(DAT_1ffe064c,0);
  DAT_1ffe0650 = FUN_0004a0b8(DAT_1ffe064c);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe0650,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe0650,6,0);
  FUN_0004ab24(DAT_1ffe0650,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe0650,0);
  uVar4 = 0;
  do {
    uVar5 = FUN_00010a20(uVar4 + 1);
    FUN_00010920((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),0,0x40240000);
    FUN_00020000(auStack_28,10,"%.1fA");
    uVar2 = FUN_0004a094(DAT_1ffe0650,auStack_28);
    FUN_0004ab24(uVar2,&DAT_1fffba84,0);
    if (uVar4 == DAT_1ffe032e) {
      uVar3 = FUN_0004037c(0xffa600);
      FUN_0004e8b2(uVar2,uVar3,0);
    }
    FUN_0004aa6e(uVar2,2);
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 0x32);
  FUN_0004e906(uVar2,0);
  return;
}

