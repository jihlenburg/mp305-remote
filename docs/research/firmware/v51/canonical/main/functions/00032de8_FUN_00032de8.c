/* Address: 00032de8; name: FUN_00032de8; body bytes: 230 */

void FUN_00032de8(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_2c [24];
  
  DAT_1ffe06e0 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe06e0,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe06e0,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe06e0,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe06e0,0);
  FUN_0004e00e(DAT_1ffe06e0,0x10);
  FUN_0004e822(DAT_1ffe06e0,0);
  DAT_1ffe06e4 = FUN_0004a0b8(DAT_1ffe06e0);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe06e4,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe06e4,6,0);
  FUN_0004ab24(DAT_1ffe06e4,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe06e4,0);
  uVar3 = 0;
  do {
    uVar2 = FUN_00015a5c(0x46);
    FUN_00020000(auStack_2c,0x14,&DAT_00032ee8,uVar2);
    while( true ) {
      uVar2 = FUN_0004a040(DAT_1ffe06e4,0,auStack_2c);
      FUN_0004ab24(uVar2,&DAT_1fffba90,0);
      uVar3 = uVar3 + 1 & 0xff;
      if (5 < uVar3) {
        FUN_0004e906(uVar2,0);
        return;
      }
      if (uVar3 == 0) break;
      uVar2 = FUN_00015a5c(0x57);
      FUN_00020000(auStack_2c,0x14,"%d %s",(&DAT_1ffe077d)[uVar3],uVar2);
    }
  } while( true );
}

