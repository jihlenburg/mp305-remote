/* Address: 0002e960; name: FUN_0002e960; body bytes: 208 */

void FUN_0002e960(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_2c [24];
  
  DAT_1ffe06f0 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe06f0,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe06f0,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe06f0,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe06f0,0);
  FUN_0004e00e(DAT_1ffe06f0,0x10);
  FUN_0004e822(DAT_1ffe06f0,0);
  DAT_1ffe06f4 = FUN_0004a0b8(DAT_1ffe06f0);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe06f4,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe06f4,6,0);
  FUN_0004ab24(DAT_1ffe06f4,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe06f4,0);
  uVar3 = 0;
  do {
    uVar2 = FUN_00015a5c(0x56);
    FUN_00020000(auStack_2c,0x14,"%d %s",(&DAT_1ffe0798)[uVar3],uVar2);
    uVar2 = FUN_0004a040(DAT_1ffe06f4,0,auStack_2c);
    FUN_0004ab24(uVar2,&DAT_1fffba90,0);
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 6);
  FUN_0004e906(uVar2,0);
  return;
}

