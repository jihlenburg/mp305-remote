/* Address: 000300d4; name: FUN_000300d4; body bytes: 238 */

void FUN_000300d4(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined1 auStack_34 [24];
  
  DAT_1ffe06e8 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe06e8,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe06e8,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe06e8,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe06e8,0);
  FUN_0004e00e(DAT_1ffe06e8,0x10);
  FUN_0004e822(DAT_1ffe06e8,0);
  DAT_1ffe06ec = FUN_0004a0b8(DAT_1ffe06e8);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe06ec,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe06ec,6,0);
  FUN_0004ab24(DAT_1ffe06ec,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe06ec,0);
  uVar3 = 0;
  do {
    FUN_00015a5c(0x55);
    uVar4 = FUN_00010a20((&DAT_1ffe0784)[uVar3]);
    FUN_00010920((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),0,0x408f4000);
    FUN_00020000(auStack_34,0x14,"%.1fV/0.1%s");
    uVar2 = FUN_0004a040(DAT_1ffe06ec,0,auStack_34);
    FUN_0004ab24(uVar2,&DAT_1fffba90,0);
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 10);
  FUN_0004e906(uVar2,0);
  return;
}

