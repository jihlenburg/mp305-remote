/* Address: 000317f0; name: FUN_000317f0; body bytes: 214 */

void FUN_000317f0(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  byte bVar4;
  undefined1 auStack_28 [24];
  
  DAT_1ffe06d8 = FUN_0004b384();
  iVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe06d8,uVar2,iVar1 + -0x20);
  uVar2 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe06d8,uVar2,0x20);
  FUN_0004ab24(DAT_1ffe06d8,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe06d8,0);
  FUN_0004e00e(DAT_1ffe06d8,0x10);
  FUN_0004e822(DAT_1ffe06d8,0);
  DAT_1ffe06dc = FUN_0004a0b8(DAT_1ffe06d8);
  iVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe06dc,0x82,iVar1 + -0x20);
  FUN_0004ac0a(DAT_1ffe06dc,6,0);
  FUN_0004ab24(DAT_1ffe06dc,&DAT_1fffb958,0);
  FUN_0004e822(DAT_1ffe06dc,0);
  bVar4 = 0;
  do {
    puVar3 = (undefined1 *)FUN_00015a5c(0x46);
    while( true ) {
      uVar2 = FUN_0004a040(DAT_1ffe06dc,0,puVar3);
      FUN_0004ab24(uVar2,&DAT_1fffba90,0);
      bVar4 = bVar4 + 1;
      if (1 < bVar4) {
        FUN_0004e906(uVar2,0);
        return;
      }
      if (bVar4 == 0) break;
      uVar2 = FUN_00015a5c(0x55);
      FUN_00020000(auStack_28,0x14,"30 %s",uVar2);
      puVar3 = auStack_28;
    }
  } while( true );
}

