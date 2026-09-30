/* Address: 0002ea48; name: FUN_0002ea48; body bytes: 266 */

void FUN_0002ea48(undefined4 param_1)

{
  undefined4 uVar1;
  
  DAT_1ffe0370 = FUN_00048d88();
  FUN_0004e84a(DAT_1ffe0370,0x2d,0x1e);
  FUN_0004e7c2(DAT_1ffe0370,2,0xd0);
  FUN_0004ab24(DAT_1ffe0370,&DAT_1fffb9b8,0);
  FUN_00049974(DAT_1ffe0370,&DAT_0002eb5c);
  FUN_0004ab24(DAT_1ffe0370,&DAT_1fffb940,0);
  FUN_0004ea86(DAT_1ffe0370,2,0);
  FUN_0004ea3c(DAT_1ffe0370,4,0);
  DAT_1ffe0374 = FUN_00048d88(param_1);
  FUN_0004e84a(DAT_1ffe0374,0x58,0x1e);
  FUN_0004ac28(DAT_1ffe0374,DAT_1ffe0370,0x13,0);
  FUN_0004ab24(DAT_1ffe0374,&DAT_1fffb940,0);
  FUN_0004ab24(DAT_1ffe0374,&DAT_1fffb9dc,0);
  uVar1 = FUN_0004037c(0x333333);
  FUN_0004e8b2(DAT_1ffe0374,uVar1,0);
  FUN_0004ea86(DAT_1ffe0374,3,0);
  FUN_0004ea32(DAT_1ffe0374,0x1c,0);
  FUN_0004ea3c(DAT_1ffe0374,4,0);
  FUN_000499de(DAT_1ffe0374,"%03d.%02d",DAT_1fffab7c / 100,(uint)DAT_1fffab7c % 100);
  uVar1 = FUN_00048d88(DAT_1ffe0374);
  FUN_0004eae2(uVar1,0x3fffffff);
  FUN_0004ac0a(uVar1,8,0x16,0xfffffffe);
  FUN_0004ab24(uVar1,&DAT_1fffb988,0);
  FUN_0004ea86(uVar1,2,0);
  FUN_000499de(uVar1,&DAT_0002eb80);
  return;
}

