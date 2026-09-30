/* Address: 0002b448; name: FUN_0002b448; body bytes: 352 */

void FUN_0002b448(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined8 uVar5;
  undefined1 auStack_30 [12];
  
  DAT_1ffe063c = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe063c,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe063c,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe063c,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe063c,0);
  FUN_0004e00e(DAT_1ffe063c,0x10);
  FUN_0004e822(DAT_1ffe063c,0);
  DAT_1ffe0640 = FUN_0004a0b8(DAT_1ffe063c);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe0640,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe0640,6,0);
  FUN_0004ab24(DAT_1ffe0640,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe0640,0);
  uVar4 = 0;
  do {
    if (DAT_1fffa0c7 == 5) {
      FUN_00020000(auStack_30,10,&DAT_0002b5d8,*(undefined2 *)(&DAT_1ffe084e + uVar4 * 2));
    }
    else {
      uVar5 = FUN_00010a20((&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + uVar4]);
      FUN_00010920((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),0,0x408f4000);
      FUN_00020000(auStack_30,10,"%.2fV");
    }
    uVar2 = FUN_0004a094(DAT_1ffe0640,auStack_30);
    FUN_0004ab24(uVar2,&DAT_1fffba84,0);
    if (uVar4 == DAT_1ffe032d) {
      uVar3 = FUN_0004037c(0xffa600);
      FUN_0004e8b2(uVar2,uVar3,0);
    }
    if ((&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + uVar4] ==
        *(short *)((int)&DAT_1ffe07d4 + (uint)DAT_1fffa0c7 * 2)) {
      uVar3 = FUN_00047698(uVar2);
      FUN_00047d8e(uVar3,&DAT_0008231c);
      FUN_0004ac0a(uVar3,7,0);
    }
    FUN_0004aa6e(uVar2,2);
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 0xb);
  FUN_0004e906(uVar2,0);
  return;
}

