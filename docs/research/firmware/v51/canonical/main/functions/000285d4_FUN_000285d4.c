/* Address: 000285d4; name: FUN_000285d4; body bytes: 276 */

void FUN_000285d4(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  DAT_1ffe0770 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0770,uVar2,uVar1);
  uVar1 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0770,uVar1,0);
  FUN_0004ab24(DAT_1ffe0770,&DAT_1fffb940,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e8b2(DAT_1ffe0770,uVar1,0);
  FUN_0004e822(DAT_1ffe0770,0);
  uVar4 = 0;
  do {
    uVar1 = FUN_0003cd40(DAT_1ffe0770);
    FUN_0004e84a(uVar1,0x41);
    thunk_FUN_0003d6e0(uVar1,uVar4 * 0x48 + -0x73);
    FUN_0003d476(0,0x42480000,uVar1);
    FUN_0003d7bc(uVar1,0);
    FUN_0004b128(uVar1);
    FUN_0004e894(uVar1,0);
    uVar2 = FUN_0004037c(0x2626);
    FUN_0004e874(uVar1,uVar2,0);
    FUN_0004e0f6(uVar1,0,0x30000);
    FUN_0004e00e(uVar1,2);
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 5);
  uVar2 = FUN_00048d88(DAT_1ffe0770);
  FUN_0004ab24(uVar2,&DAT_1fffb9ac,0);
  uVar3 = FUN_00015a5c(0x29);
  FUN_000499de(uVar2,&DAT_000286fc,uVar3);
  FUN_0004ac28(uVar2,uVar1,0xe,0,10);
  return;
}

