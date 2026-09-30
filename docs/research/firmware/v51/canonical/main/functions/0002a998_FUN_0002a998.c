/* Address: 0002a998; name: FUN_0002a998; body bytes: 194 */

void FUN_0002a998(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  uStack_20 = param_2;
  uStack_1c = param_3;
  uStack_18 = param_4;
  DAT_1ffe06c8 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe06c8,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe06c8,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe06c8,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe06c8,0);
  FUN_0004e00e(DAT_1ffe06c8,0x10);
  FUN_0004e822(DAT_1ffe06c8,0);
  DAT_1ffe06cc = FUN_0004a0b8(DAT_1ffe06c8);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe06cc,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe06cc,6,0);
  FUN_0004ab24(DAT_1ffe06cc,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe06cc,0);
  uVar3 = 0;
  do {
    FUN_00020000(&uStack_20,10,&DAT_0002aa68,(&DAT_1ffe0778)[uVar3]);
    uVar2 = FUN_0004a040(DAT_1ffe06cc,0,&uStack_20);
    FUN_0004ab24(uVar2,&DAT_1fffba90,0);
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 5);
  FUN_0004e906(uVar2,0);
  return;
}

