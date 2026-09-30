/* Address: 00035604; name: FUN_00035604; body bytes: 314 */

void FUN_00035604(undefined4 param_1)

{
  undefined4 uVar1;
  
  DAT_1ffe0350 = FUN_000354a8();
  FUN_0004e7c2(DAT_1ffe0350,2);
  DAT_1ffe0354 = FUN_0004b384(param_1);
  FUN_0004e84a(DAT_1ffe0354,0x84,0x1e);
  FUN_0004e7c2(DAT_1ffe0354,2,0x3e);
  FUN_0004ab24(DAT_1ffe0354,&DAT_1fffb940,0);
  uVar1 = FUN_0004037c(0x333333);
  FUN_0004e8b2(DAT_1ffe0354,uVar1,0);
  FUN_0004aa6e(DAT_1ffe0354,2);
  FUN_0004e9f0(DAT_1ffe0354,0xfffffffe);
  uVar1 = FUN_00048d88(DAT_1ffe0354);
  FUN_0004ab24(uVar1,&DAT_1fffb9a0,0);
  FUN_00049974(uVar1,"V-SET");
  FUN_0004ac0a(uVar1,7,6,0);
  uVar1 = FUN_00048d88(DAT_1ffe0354);
  FUN_0004ab24(uVar1,&DAT_1fffb9a0,0);
  FUN_0004ac0a(uVar1,8,0xfffffffc);
  FUN_000499de(uVar1,"%02d.%02d V",DAT_1fffab74 / 100,(uint)DAT_1fffab74 % 100);
  uVar1 = FUN_00048d88(DAT_1ffe0354);
  FUN_0004ab24(uVar1,&DAT_1fffb9b8,0);
  FUN_00049974(uVar1,"SET : ");
  FUN_0004ac0a(uVar1,8,0xfffffffc,0);
  FUN_0004aa6e(uVar1,1);
  DAT_1ffe0358 = FUN_00035774(param_1,"SET : ");
  FUN_0004e7c2(DAT_1ffe0358,2,0x3e);
  FUN_0004aa6e(DAT_1ffe0358,1);
  DAT_1ffe035c = FUN_0004b384(param_1);
  FUN_0004e84a(DAT_1ffe035c,0x84,0x5a);
  FUN_0004e7c2(DAT_1ffe035c,2);
  FUN_0004ab24(DAT_1ffe035c,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe035c,0);
  FUN_0004aa6e(DAT_1ffe035c,2);
  return;
}

