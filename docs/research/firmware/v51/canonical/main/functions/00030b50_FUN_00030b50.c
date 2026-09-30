/* Address: 00030b50; name: FUN_00030b50; body bytes: 734 */

void FUN_00030b50(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  uint uVar5;
  
  DAT_1ffe0450 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0450,uVar2,uVar1);
  uVar1 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0450,uVar1,0);
  FUN_0004ab24(DAT_1ffe0450,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0450,0);
  FUN_0004e822(DAT_1ffe0450,0);
  DAT_1ffe0454 = FUN_0004b384(DAT_1ffe0450);
  uVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe0454,0xb6,uVar1);
  FUN_0004ac0a(DAT_1ffe0454,8,0);
  FUN_0004ab24(DAT_1ffe0454,&DAT_1fffb958,0);
  FUN_0004ea1e(DAT_1ffe0454,2,0);
  DAT_1ffe0458 = FUN_0004a0b8(DAT_1ffe0454);
  FUN_0004e84a(DAT_1ffe0458,0xb6,0xd2);
  FUN_0004ac0a(DAT_1ffe0458,4,0);
  FUN_0004ab24(DAT_1ffe0458,&DAT_1fffb958,0);
  FUN_0004ea60(DAT_1ffe0458,8,0);
  FUN_0004ea3c(DAT_1ffe0458,8,0);
  FUN_0004e822(DAT_1ffe0458,0);
  uVar5 = 0;
  do {
    uVar1 = FUN_0004a094(DAT_1ffe0458,&DAT_00030e3c);
    FUN_0004ab24(uVar1,&DAT_1fffba48,0);
    uVar2 = FUN_00048d88(uVar1);
    FUN_0004eae2(uVar2,0x20);
    FUN_0004ea86(uVar2,2,0);
    FUN_000499de(uVar2,&DAT_00030e44,uVar5 + 1);
    uVar2 = FUN_00048d88(uVar1);
    FUN_0004ac0a(uVar2,0,0x25);
    FUN_000499de(uVar2,"%02d.%02d",(ushort)(&DAT_1fffa0f8)[uVar5 * 2] / 100,
                 (uint)(ushort)(&DAT_1fffa0f8)[uVar5 * 2] % 100);
    uVar3 = FUN_00048d88(uVar1);
    FUN_0004ac28(uVar3,uVar2,0x14,3,0);
    FUN_000499de(uVar3,&DAT_00030e58);
    uVar2 = FUN_00048d88(uVar1);
    FUN_0004ac28(uVar2,uVar3,0x14,0xc,0);
    FUN_000499de(uVar2,"%01d.%03d",(ushort)(&DAT_1fffa0fa)[uVar5 * 2] / 1000,
                 (uint)(ushort)(&DAT_1fffa0fa)[uVar5 * 2] % 1000);
    uVar3 = FUN_00048d88(uVar1);
    FUN_0004ac28(uVar3,uVar2,0x14,3);
    FUN_000499de(uVar3,&DAT_00030e68);
    FUN_0004aa6e(uVar1,2);
    uVar5 = uVar5 + 1 & 0xff;
  } while (uVar5 < 10);
  DAT_1ffe045c = FUN_0003e808(DAT_1ffe0454);
  FUN_0004e84a(DAT_1ffe045c,0xb2,0x1e);
  FUN_0004ac0a(DAT_1ffe045c,2,0);
  FUN_0004ab24(DAT_1ffe045c,&DAT_1fffb94c,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8e6(DAT_1ffe045c,uVar1,0);
  uVar1 = FUN_00048d88(DAT_1ffe045c);
  FUN_0004ac0a(uVar1,9,0);
  FUN_0004ab24(uVar1,&DAT_1fffb9c4,0);
  uVar2 = FUN_00015a5c(0);
  FUN_000499de(uVar1,&DAT_00030e74,uVar2);
  DAT_1ffe0460 = FUN_0003e808(DAT_1ffe0454);
  FUN_0004e84a(DAT_1ffe0460,0x58,0x1e);
  FUN_0004ac0a(DAT_1ffe0460,3,0xfffffffe);
  FUN_0004ab24(DAT_1ffe0460,&DAT_1fffb94c,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8e6(DAT_1ffe0460,uVar1,0);
  uVar1 = FUN_00048d88(DAT_1ffe0460);
  FUN_0004ac0a(uVar1,9,0);
  FUN_0004ab24(uVar1,&DAT_1fffb9c4,0);
  uVar2 = FUN_00015a5c(1);
  FUN_000499de(uVar1,&DAT_00030e74,uVar2);
  FUN_0004aa6e(DAT_1ffe0460,1);
  DAT_1ffe0464 = FUN_0003e808(DAT_1ffe0454);
  FUN_0004e84a(DAT_1ffe0464,0x58,0x1e);
  FUN_0004ac0a(DAT_1ffe0464,0,2);
  FUN_0004ab24(DAT_1ffe0464,&DAT_1fffb94c,0);
  uVar1 = FUN_0004037c(0x180026);
  FUN_0004e8e6(DAT_1ffe0464,uVar1,0);
  uVar1 = FUN_0004037c(0xedccff);
  FUN_0004e8b2(DAT_1ffe0464,uVar1,0);
  uVar1 = FUN_00047698(DAT_1ffe0464);
  if (DAT_1fffaadc == '\0') {
    puVar4 = &DAT_0007bc48;
  }
  else {
    puVar4 = &DAT_0007cc4c;
  }
  FUN_00047d8e(uVar1,puVar4);
  FUN_0004b128(uVar1);
  FUN_0004aa6e(DAT_1ffe0464,1);
  return;
}

